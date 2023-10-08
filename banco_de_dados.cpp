#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TADBD.h"

void executaSqlEstrutural(tpBD **BD,FILE *ptr)
{
	char linha[100],auxP1[20],auxP2[20],auxP3[20],tabAux[20];
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	fgets(linha,100,ptr);
	separaPalavras(&d,linha);
	while(!feof(ptr))
	{
		if(d->inicio!=NULL)
		{
			strcpy(auxP1,d->inicio->palavra);
			if(strcmp(auxP1,"CREATE")==0)
			{
					strcpy(auxP2,d->inicio->prox->palavra);
					if(strcmp(auxP2,"DATABASE")==0)
						iniciarBanco(&(*BD),linha);
					else
					{
						if(strcmp(auxP2,"TABLE")==0){
							strcpy(tabAux,d->inicio->prox->prox->palavra);
							criarTabela(&(*BD),linha);
							fgets(linha,100,ptr);
							excluirDesc(&d);
							separaPalavras(&d,linha);
							strcpy(auxP3,d->inicio->palavra);
							while(strcmp(d->inicio->palavra,")")!=0)
							{
								if(strcmp(auxP3,"CONSTRAINT")==0)
									adicionaPK(&(*BD),linha,tabAux);
								else
									criarCampos(&(*BD),linha,tabAux);
								fgets(linha,100,ptr);
								excluirDesc(&d);
								separaPalavras(&d,linha);
								strcpy(auxP3,d->inicio->palavra);
							}
						}	
					}
			}
			else
			{
				if(strcmp(auxP1,"ALTER")==0)
				{
					adicionaFK(&(*BD),linha,ptr);
				}
			}
		}
		fgets(linha,100,ptr);
		excluirDesc(&d);
		separaPalavras(&d,linha);
	}
	printf("\nSQL ESTRUTURAL FEITO!!");
}

int main()
{
	FILE *ptr = fopen("scriptdboficina.txt","r");
	tpBD *banco;
	tpTabela *aux;
	tpCamposTab *auxT;
	executaSqlEstrutural(&banco,ptr);
	fclose(ptr);
}
