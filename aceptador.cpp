/*******************************************************************
*
*  DESCRIPTION: Atomic Model Aceptador
*
*  AUTHOR: Matias Brunstein Macri 
*
*  EMAIL: mailto://mbmacri@dc.uba.ar
*
*  DATE: 23/9/2003
*
*******************************************************************/
/** include files **/
#include "aceptador.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "strutil.h"       // str2Value( ... )

/** public functions **/

/*******************************************************************
* Function Name: Queue
* Description: 
********************************************************************/
Aceptador::Aceptador( const string &name )
: Atomic( name )
, autoIn( addInputPort( "autoIn" ) )
, autoOut( addOutputPort( "autoOut" ) )
, libreOut( addOutputPort( "libreOut" ) )
, stopOut( addOutputPort( "stopOut" ) )
, controlA( addInputPort( "controlA" ) )
, controlR( addInputPort( "controlR" ) )
, sonda( addInputPort( "sonda" ) )
, preparationTime( 0, 0, 0, 10 )
{
	q = 0;
	r = 0;
	s = 0;
	l = 0;
	lstCtrl = libre;
	// Carga los par?metros
	string time( MainSimulator::Instance().getParameter( description(), "preparacion" ) ) ;
	if( time != "" )
		preparationTime = time ;
	M = str2Int( MainSimulator::Instance().getParameter( description(), "capacidad" ) );
};

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Aceptador::initFunction()
{
	q = 0;
	r = 0;
	s = 0;
	l = 0;
	lstCtrl = libre;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Aceptador::externalFunction( const ExternalMessage &msg )
{
	int n = static_cast< int >(msg.value());
	switch(state()){
		case passive:
			if (msg.port() == autoIn){
				if (n + q > M){ 
					r = (n + q) - max(M, q); 
					s = max(0, M - q); 
					q = max(M, q);
				} else {
					s = n; q = q + n;
				}

			} else if (msg.port() == controlR) {
				q = q + n;
	
			} else if (msg.port() == controlA) {
				q = q - n;
				l = 1;
			}
			holdIn( active, preparationTime ) ;

			break;
		case active:
			if (msg.port() == autoIn){
				if (n + q > M){ 
					r += (n + q) - max(M, q); 
					s += max(0, M - q); 
					q = max(M, q);
				} else {
					s += n; q = q + n;
				}

			} else if (msg.port() == controlR) {
				q = q + n - min(s, n);
				r = r + min(s, n);
				s = max(0, s - n);
	
			} else if (msg.port() == controlA) {
				q = q - n + min(r, n);
				s = s + min(r, n);
				r = max(0, r - n);
				l = 1;
			}
			holdIn( active, nextChange() ) ;
			break;
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: Funcion de transicion por un evento interno.
********************************************************************/
Model &Aceptador::internalFunction( const InternalMessage & )
{
	if (q < M && l == 1) lstCtrl = libre;
	if (r > 0) lstCtrl = stop;
	s = 0; r = 0; l = 0;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: Funcion lambda.
********************************************************************/
Model &Aceptador::outputFunction( const InternalMessage &msg )
{
	if (s > 0)	sendOutput( msg.time(), autoOut, s );
	if (r > 0)	sendOutput( msg.time(), stopOut, r );
	if (q < M && l == 1 && lstCtrl == stop) sendOutput( msg.time(), libreOut, 0 );
	sendOutput( msg.time(), sonda, q );
	return *this ;
}
