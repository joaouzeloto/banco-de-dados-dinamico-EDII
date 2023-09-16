#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TADBD.h"

int main()
{
	tpBD *banco;
	iniciarBanco(&banco,"bancoProj");
	printf("\nNome do banco: %s",banco->bdName);
	
}
