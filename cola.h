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
#ifndef __COLA_H
#define __COLA_H

#include "atomic.h"     // class Atomic

class Cola : public Atomic
{
public:
	Cola( const string &name = "Cola" );					//Default constructor	
	virtual string className() const;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );
	
private:
	const Port &autoIn;
	Port &autoOut;
	const Port &libre;
	const Port &stop;
	Port &sonda;

	enum Estado {
		vacio,
		circulando,
		parado
	};
	// Parametros
	Time preparationTime;
	int C;	// Cantidad de carriles
	int M;  // Capacidad maxima

	// Estas variables representan el estado
	int q;
	Estado E;
	
	// Variables auxiliares
	Time leftTime;

};	// class Cola

// ** inline ** // 
inline string Cola::className() const
{
	return "Cola" ;
}

#endif