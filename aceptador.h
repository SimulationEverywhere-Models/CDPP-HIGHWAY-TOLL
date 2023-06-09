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
#ifndef __ACEPTADOR_H
#define __ACEPTADOR_H

#include "atomic.h"     // class Atomic

class Aceptador : public Atomic
{
public:
	Aceptador( const string &name = "Aceptador" ); //Default constructor	
	virtual string className() const;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );
	
private:
	const Port &autoIn;
	Port &autoOut;
	Port &libreOut;
	Port &stopOut;
	const Port &controlA;
	const Port &controlR;
	Port &sonda;

	enum StFlujo{
		libre,
		stop
	};
	
	// Parametros
	Time preparationTime;
	int M;  // Capacidad maxima del sistema

	// Estas variables representan el estado
	int q;
	int r;
	int s;
	int l;
	StFlujo lstCtrl;
	
};	// class Aceptador

// ** inline ** // 
inline string Aceptador::className() const
{
	return "Aceptador" ;
}

#endif