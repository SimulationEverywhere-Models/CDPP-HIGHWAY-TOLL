/*******************************************************************
*
*  DESCRIPTION: Atomic Model Despachador
*
*  AUTHOR: Matias Brunstein Macri 
*
*  EMAIL: mailto://mbmacri@dc.uba.ar
*
*  DATE: 23/9/2003
*
*******************************************************************/
/** include files **/
#include "despachador.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "strutil.h"       // str2Value( ... )
#include "distri.h"

/** public functions **/

/*******************************************************************
* Function Name: Queue
* Description: 
********************************************************************/
Despachador::Despachador( const string &name )
: Atomic( name )
, autoOut( addOutputPort( "autoOut" ) )
, autoIn( addInputPort( "autoIn" ) )
, libreIn( addInputPort( "libreIn" ) )
, stopIn( addInputPort( "stopIn" ) )
, preparationTime( 0, 0, 0, 10 )
{
	// Carga los par?metros
	string paramTime( MainSimulator::Instance().getParameter( description(), "preparacion" ) ) ;
	if( paramTime != "" ){
		preparationTime = paramTime ;
	}
	
	auxTime = Time::Zero;

    string paramRnd( MainSimulator::Instance().getParameter( description(), "random" ) ) ;
    random = (paramRnd == "yes");

	dist = Distribution::create( "poisson" );
	MASSERT( dist ) ;
	dist->setVar( 0, preparationTime.asMsecs() ) ;
};

/*******************************************************************
* Function Name: prepTime
* Description: Calcula y devuelve el tiempo de preparaci?n seg?n los
* par?metros del modelo.
********************************************************************/
const Time &Despachador::prepTime(void){
	if (random) {
		auxTime = Time( static_cast< float >( fabs( distribution().get() )/1000));
		return auxTime;
	} else {
		return preparationTime;
	}
}
/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Despachador::initFunction()
{
	q = 0;
	R = libre;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Despachador::externalFunction( const ExternalMessage &msg )
{
	int n = static_cast< int >(msg.value());
	// Actualiza el estado
	if (msg.port() == autoIn){
		q += n;
	} else if (msg.port() == stopIn) {
		q += n;
		R = stop;
	} else if (msg.port() == libreIn) {
		R = libre;
	}

	// Ejecuta la transici?n y encola eventos internos
	if (q > 0 && R == libre){
		if (state() == passive)
			holdIn( active, prepTime() ) ;
		if (state() == active)
			holdIn( active, nextChange() ) ;
	} else 
		passivate();

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: Funcion de transicion por un evento interno.
********************************************************************/
Model &Despachador::internalFunction( const InternalMessage & )
{
	q = 0;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: Funcion lambda.
********************************************************************/
Model &Despachador::outputFunction( const InternalMessage &msg )
{
	if (q > 0)	sendOutput( msg.time(), autoOut, q );
	return *this ;
}

Despachador::~Despachador()
{
	delete dist;
}
