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
#include "mytools.h"
#include "time.h"

int max(int a, int b){
	if (a > b){
		return a;
	} else {
		return b;
	}
}

int max(int a, int b, int c){
	return max(a, max(b, c));
}

int min(int a, int b){
	if (a < b){
		return a;
	} else {
		return b;
	}
}

int min(int a, int b, int c){
	return min(a, min(b, c));
}

int min(Time times[], int c){
	Time minT = Time::Inf;
	int minI = 0;
	for (int i = 0; i < c; i++){
		if (times[i] < minT) {
			minT = times[i];
			minI = i;
		}
	}
	return minI;
}

int max(Time times[], int c){
	Time maxT = Time::Zero;
	int maxI = 0;
	for (int i = 0; i < c; i++){
		if (times[i] > maxT) {
			maxT = times[i];
			maxI = i;
		}
	}
	return maxI;
}

const Time &max(const Time &a, const Time &b){
	if (a > b){
		return a;
	} else {
		return b;
	}
}

const Time &min(const Time &a, const Time &b){
	if (a < b){
		return a;
	} else {
		return b;
	}
}
