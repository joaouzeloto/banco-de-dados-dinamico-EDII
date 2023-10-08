#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TADBD.h"

int main()
{
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	separaPalavras(&d,"	valor_total NUMERIC(6,2) ,");
	printf("%s",d->inicio);
}
