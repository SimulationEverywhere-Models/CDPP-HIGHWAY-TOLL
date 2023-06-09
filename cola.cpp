/*******************************************************************
*
*  DESCRIPTION: Atomic Model Cola
*
*  AUTHOR: Matias Brunstein Macri 
*
*  EMAIL: mailto://mbmacri@dc.uba.ar
*
*  DATE: 23/9/2003
*
*******************************************************************/
/** include files **/
#include "cola.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include "strutil.h"       // str2Value( ... )

/** public functions **/

/*******************************************************************
* Function Name: Queue
* Description: 
********************************************************************/
Cola::Cola( const string &name )
: Atomic( name )
, autoIn( addInputPort( "autoIn" ) )
, autoOut( addOutputPort( "autoOut" ) )
, libre( addInputPort( "libre" ) )
, stop( addInputPort( "stop" ) )
, sonda( addOutputPort( "sonda" ) )
, preparationTime( 0, 0, 0, 10 )
{
	q = 0;
	// Carga los par?metros
	string time( MainSimulator::Instance().getParameter( description(), "preparacion" ) ) ;
	if( time != "" )
		preparationTime = time ;
    C = str2Int( MainSimulator::Instance().getParameter( description(), "carriles" ) );
	M = str2Int( MainSimulator::Instance().getParameter( description(), "capacidad" ) );
};

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Cola::initFunction()
{
	q = 0;
	E = vacio;
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: externalFunction
* Description: Funcion de transicion por un evento externo.
********************************************************************/
Model &Cola::externalFunction( const ExternalMessage &msg )
{
	switch(E){
		case vacio:
			// Si el mensaje llego por el puerto AutoIn
			if (msg.port() == autoIn){
				// Agrega vehiculos a la cola
				q += static_cast< int >(msg.value());
				if (q > M) q = M;
				// Pasa al estado Circulando y encola un evento interno.
				E = circulando;
				holdIn( active, preparationTime ) ;
//printf("<vacio>: autoIn <- %1.0f\n",msg.value());

			// Si el mensaje llego por el puerto Stop
			} else if (msg.port() == stop) {
				// Agrega a la cola los vehiculos rechazados
				q += static_cast< int >(msg.value());
				// Pasa al estado Parado y queda esperando un evento externo.
				E = parado;
				passivate();
			}
			break;
		case circulando:
			// Si el mensaje llego por el puerto AutoIn
			if (msg.port() == autoIn){
				// Agrega vehiculos a la cola
				q += static_cast< int >(msg.value());
				if (q > M) q = M;
//printf("<circulando>: autoIn <- %1.0f\n", msg.value());
				// Se mantiene en el mismo estado y encola un evento interno para el tiempo restante.
				holdIn( active, nextChange() ) ;
				// Si el mensaje llego por el puerto Stop
				} else if (msg.port() == stop) {
					// Agrega a la cola los vehiculos rechazados
					q += static_cast< int >(msg.value());
					// Pasa al estado Parado y queda esperando un evento externo.
					E = parado;
					passivate();
				}
				break;
		case parado:
			// Si el mensaje llego por el puerto AutoIn
			if (msg.port() == autoIn){
				// Agrega vehiculos a la cola
				q += static_cast< int >(msg.value());
				if (q > M) q = M;
				// SE mantiene en el mismo estado
//printf("<parado>: autoIn <- %1.0f\n", msg.value());
				passivate();

			// Si el mensaje llego por el puerto Libre
			} else if (msg.port() == libre) {
				// Pasa al estado Circulando y encola un evento interno.
				E = circulando;
				holdIn( active, preparationTime ) ;
			}
			break;
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: Funcion de transicion por un evento interno.
*              S?lo valida cuando el estado E es Circulando.
********************************************************************/
Model &Cola::internalFunction( const InternalMessage & )
{
	// Disminuye la cantidad de vehiculos en la cola y pasa al
	// estado Parado si ya no hay vehiculos.
	if (E == circulando) {
		if (q > C){
			q -= C;
			holdIn( active, preparationTime ) ;
		} else {
			q = 0;
			E = vacio;
			passivate();
		}
	} else {
		printf("Error: Solo se puede recibir un evento interno estando en el estado Circulando");
	}
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: Funcion lambda. S?lo est? definda cuando
*              el estado E es Circulando.
********************************************************************/
Model &Cola::outputFunction( const InternalMessage &msg )
{
	if (E == circulando) {
		if (q > C){
			sendOutput( msg.time(), autoOut, C );
		} else {
			sendOutput( msg.time(), autoOut, q );
		}
		sendOutput( msg.time(), sonda, q );
	} else {
		printf("Error: Solo se puede recibir un evento interno estando en el estado Circulando");
	}

	return *this ;
}
