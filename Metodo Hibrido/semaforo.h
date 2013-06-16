#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <iostream>

using namespace std;

class Semaforo
{
public:
	virtual void up() = 0;
	virtual void down() = 0;
	virtual int getValue() = 0;
	
	virtual ~Semaforo()
	{
	}
};


#endif
