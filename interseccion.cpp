/*******************************************************************
*
*  DESCRIPTION: Atomic Model Interseccion
*
*  AUTHOR: Matias Brunstein Macri 
*
*  EMAIL: mailto://mbmacri@dc.uba.ar
*
*  DATE: 23/9/2003
*
*******************************************************************/
/** include files **/
#include "interseccion.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "strutil.h"       // str2Value( ... )
#include "mytools.h"

/** public functions **/

/*******************************************************************
* Function Name: Queue
* Description: 
********************************************************************/
Interseccion::Interseccion( const string &name )
: Atomic( name )
, autoA( addInputPort( "autoA" ) )
, autoB( addInputPort( "autoB" ) )
, autoOut( addOutputPort( "autoOut" ) )
, libreA( addInputPort( "libreA" ) )
, libreB( addInputPort( "libreB" ) )
, stopA( addInputPort( "stopA" ) )
, stopB( addInputPort( "stopB" ) )
, preparationTime( 0, 0, 0, 10 )
{
	// Carga los par?metros
	string preptime( MainSimulator::Instance().getParameter( description(), "preparacion" ) ) ;
	string ritime( MainSimulator::Instance().getParameter( description(), "reinicio" ) ) ;
	preparationTime = preptime ;
	reinitTime = ritime ;
    C = str2Int( MainSimulator::Instance().getParameter( description(), "carriles" ) );
};

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Interseccion::initFunction()
{
	q = 0;
	ra = 0;
	rb = 0;
	sla = 0;
	slb = 0;
	E = pasivo;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Interseccion::externalFunction( const ExternalMessage &msg )
{
	int n = static_cast< int >(msg.value());
	// Actualiza el estado
	if (msg.port() == autoA){
		ra += max(0, n + q - C);
		q = min(q+n, C);
	} else if (msg.port() == autoB){
		rb += max(0, n + q - C);
		q = min(q+n, C);
	}
	sla = (ra > 0) || sla;
	slb = (rb > 0) || slb;
	
	// Ejecuta la transici?n y encola eventos internos
	if (q > 0 || ra >0 || rb > 0){
		if (E == pasivo){
			if ( ra >0 || rb > 0 ){
				E = rechazando;
				nextTime = preparationTime - reinitTime;
				holdIn( active, reinitTime ) ;
			} else {
				E = activo;
				holdIn( active, preparationTime ) ;
			}
		} else if (E == activo){
			if ( (ra >0 || rb > 0) && (nextChange() > reinitTime) ){
				nextTime = nextChange() - reinitTime;
				E = rechazando;
				holdIn( active, reinitTime ) ;
			} else {
				holdIn( active, nextChange() ) ;
			}
		}
	} else {
		E = pasivo;
		passivate();
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: Funcion de transicion por un evento interno.
********************************************************************/
Model &Interseccion::internalFunction( const InternalMessage & )
{
	if (E == activo){
		q = 0;
		if (sla || slb) {
			E = reiniciando;
			holdIn(active, reinitTime);
		} else {
			E = pasivo;
			passivate();
		}
	} else if (E == reiniciando){
		ra = 0; rb = 0;
		sla = 0; slb = 0;
		E = pasivo;
		passivate();
	} else if (E == rechazando){
		ra = 0; rb = 0;
		E = activo;
		holdIn(active, nextTime);
	}
	return *this ;
}
/*******************************************************************
* Function Name: outputFunction
* Description: Funcion lambda.
********************************************************************/
Model &Interseccion::outputFunction( const InternalMessage &msg )
{
	if (E == activo){
		if (q > 0)	sendOutput( msg.time(), autoOut, q );
		if (ra > 0) sendOutput( msg.time(), stopA, ra );
		if (rb > 0) sendOutput( msg.time(), stopB, rb );
	} else if (E == reiniciando) {
		if (sla) sendOutput( msg.time(), libreA, 0 );
		if (slb) sendOutput( msg.time(), libreB, 0 );
	} else if (E == rechazando) {
		if (ra > 0) sendOutput( msg.time(), stopA, ra );
		if (rb > 0) sendOutput( msg.time(), stopB, rb );
	}
	return *this ;
}
