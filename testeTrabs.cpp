#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TADBD.h"

int main()
{
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	separaPalavras(&d,"CREATE DATABASE db_oficina;\n");
	printf("%s",d->inicio);
}
