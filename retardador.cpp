/*******************************************************************
*
*  DESCRIPTION: Atomic Model Retardador
*
*  AUTHOR: Matias Brunstein Macri 
*
*  EMAIL: mailto://mbmacri@dc.uba.ar
*
*  DATE: 23/9/2003
*
*******************************************************************//** include files **/
#include "retardador.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "strutil.h"       // str2Value( ... )
#include "mytools.h"       // str2Value( ... )

/** public functions **/

/*******************************************************************
* Function Name: Queue
* Description: 
********************************************************************/
Retardador::Retardador( const string &name )
: Atomic( name )
, autoIn( addInputPort( "autoIn" ) )
, autoOut( addOutputPort( "autoOut" ) )
{
	// Carga los par?metros
	string time( MainSimulator::Instance().getParameter( description(), "tiempo" ) ) ;
	string dist( MainSimulator::Instance().getParameter( description(), "distancia" ) ) ;
	Tiempo = time ;
	Distancia = dist ;
    C = str2Int( MainSimulator::Instance().getParameter( description(), "carriles" ) );
};

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Retardador::initFunction()
{
	Q.erase(Q.begin(), Q.end());
	for (int i = 0; i<C; i++) lh[i] = Time::Zero;
	s = 0;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Retardador::externalFunction( const ExternalMessage &msg )
{
	// Encola tantos vehículos como hallan entrado asegurandose
	// de no encolar nunca más de C vehículos al mismo tiempo.
	int n = static_cast< int >(msg.value());
	Time t = msg.time();
	while (n > 0){
		encolarEntrada(t);
		n--;
	}

	// Calcula y encola la salida de la proxima tanda de vehiculos.
	if (state() == active)
		holdIn( active, nextChange() ) ;
	else
		prepararSalida( msg.time() );

	return *this;
}

/*******************************************************************
* Function Name: prepararSalida
* Description: Funcion que calcula cuando y de cuantos vehiculos
*              debera ser la proxima salida y encola el evento
* 			   interno correspondiente.
********************************************************************/
void Retardador::prepararSalida( const Time &t ){
	s = 0;
	if (!Q.empty()){
		const Time nextTime = Q.front();
		while (!Q.empty() && Q.front() == nextTime){
			s++;
			Q.pop_front();
		}
		holdIn(active, nextTime - t);
	} else {
		passivate();
	}
}

/*******************************************************************
* Function Name: encolarEntrada
* Description: Registra el ingreso de un vehículo a la vía y lo
*              acomoda de forma tal de minimizar el tiempo
*              desperdiciado.
********************************************************************/
void Retardador::encolarEntrada( const Time &t ){
	// Calcula el tiempo de salida para el vehículo
	Time tSalida = max(lh[min(lh, C)] + Distancia, t + Tiempo);
	// Recalcula la lista de las ultimas entradas
	lh[min(lh, C)] = tSalida;
	for (int i = 0; i < C; i++){
		if (lh[i] < tSalida - Distancia){
			lh[i] = tSalida - Distancia;
		}
	}
	// encola la salida
	Q.push_back(tSalida);
}
/*******************************************************************
* Function Name: internalFunction
* Description: Funcion de transicion por un evento interno.
********************************************************************/
Model &Retardador::internalFunction( const InternalMessage &msg )
{
	prepararSalida(msg.time());
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: Funcion lambda. S?lo est? definda cuando
*              el estado E es Circulando.
********************************************************************/
Model &Retardador::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), autoOut, s );
	return *this ;
}
