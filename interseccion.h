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
#ifndef __INTERSECCION_H
#define __INTERSECCION_H

#include "atomic.h"     // class Atomic

class Interseccion : public Atomic
{
public:
	Interseccion( const string &name = "Interseccion" ); //Default constructor	
	virtual string className() const;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );
	
private:
	const Port &autoA;
	const Port &autoB;
	Port &autoOut;
	Port &libreA;
	Port &libreB;
	Port &stopA;
	Port &stopB;

	enum Estado {
		activo,
		pasivo,
		reiniciando,
		rechazando
	};
	
	// Parametros
	Time preparationTime;
	Time reinitTime;
	int C;

	// Estas variables representan el estado
	Estado E;
	int q;
	int ra;
	int rb;
	Time nextTime;
	int sla;
	int slb;

};	// class Despachador

// ** inline ** // 
inline string Interseccion::className() const
{
	return "Interseccion" ;
}

#endif