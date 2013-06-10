#ifndef PONTE_H
#define PONTE_H

#include <stdlib.h>
#include "semaforoBidimensional.h"
#include "crianca.h"

typedef struct _Ponte{
	SemaforoBidimensional *semaforo;
}Ponte;

Ponte * ponte_create(){
	Ponte *ponte = malloc(sizeof(Ponte));
	ponte->semaforo = semaforoBidimensional_create();
}



#endif
