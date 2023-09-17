#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TADBD.h"

int main()
{
	int i;
	tpBD *banco;
	iniciarBanco(&banco,"bancoProj");
	printf("\nNome do banco: %s",banco->bdName);
	criarTabela(&banco,"Cliente");
	criarTabela(&banco,"Veiculos");	
	printf("\nTABELA: %s",banco->tabs->tabName);
	criarCampos(&banco,"id_cliente INTEGER NOT NULL","Cliente");
	criarCampos(&banco,"nome CHARACTER(20)","Cliente");
	printf("\nCampo: %s Tipo: %c",banco->tabs->campos->Campo,banco->tabs->campos->Tipo);
	printf("\nCampo: %s Tipo: %c",banco->tabs->campos->prox->Campo,banco->tabs->campos->prox->Tipo);
	adicionaPK(&banco,"CONSTRAINT PK_aluguel PRIMARY KEY (id_cliente)","Cliente");
	printf("\nCampo: %s PK: %c",banco->tabs->campos->Campo,banco->tabs->campos->PK);
}
