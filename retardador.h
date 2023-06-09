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
*******************************************************************/
#ifndef __RETARDADOR_H
#define __RETARDADOR_H

#include <list>
#include "time.h"     // class Atomic
#include "atomic.h"     // class Atomic

class Retardador : public Atomic
{
public:
	Retardador( const string &name = "Retardador" );					//Default constructor	
	virtual string className() const;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );
	
private:
	const Port &autoIn;
	Port &autoOut;

	// Parametros
	Time Tiempo;
	Time Distancia;
	int C;	// Cantidad de carriles

	// Estas variables representan el estado
	typedef list<Time> ListaTiempos ;
	ListaTiempos Q ;
	Time lh[100];
	int s;

	void prepararSalida( const Time & );
	void encolarEntrada( const Time & );
	
};	// class Cola

// ** inline ** // 
inline string Retardador::className() const
{
	return "Retardador" ;
}

#endif