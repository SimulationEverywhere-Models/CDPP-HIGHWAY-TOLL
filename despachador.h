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
#ifndef __DESPACHADOR_H
#define __DESPACHADOR_H

#include "atomic.h"     // class Atomic
#include "distri.h"

class Despachador : public Atomic
{
public:
	Despachador( const string &name = "Despachador" ); //Default constructor	
	~Despachador();
	virtual string className() const;

protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );
	
private:
	Port &autoOut;
	const Port &autoIn;
	const Port &libreIn;
	const Port &stopIn;

	enum StFlujo{
		libre,
		stop
	};
	
	// Parametros
	Time preparationTime;
	int random;

	// Estas variables representan el estado
	int q;
	StFlujo R;

	// Variables auxiliares
	Time auxTime;
	const Time &Despachador::prepTime(void);

	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}

};	// class Despachador

// ** inline ** // 
inline string Despachador::className() const
{
	return "Despachador" ;
}

#endif