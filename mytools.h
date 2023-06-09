/*******************************************************************
*
*  DESCRIPTION: Algunas funciones auxiliares
*
*  AUTHOR: Matias Brunstein Macri 
*
*  EMAIL: mailto://mbmacri@dc.uba.ar
*
*  DATE: 29/9/2003
*
*******************************************************************/
#ifndef _MYTOOLS__H
#define _MYTOOLS__H
#include "time.h"

 	int max(int a, int b);
	int max(int a, int b, int c);
	int min(int a, int b);
	int min(int a, int b, int c);
	
	int min(Time times[], int c);
	int max(Time times[], int c);
	const Time& min(const Time &, const Time &);
	const Time& min(const Time &, const Time &);
	
#endif