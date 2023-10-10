#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<conio2.h>
#include"TADBD.h"

void Moldura(int CI,int LI,int CF,int LF,int cor);

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
	clrscr();
	Moldura(1,1,120,30,3);
	Moldura(40,7,78,18,7);
	gotoxy(48,12);
	printf("SQL ESTRUTURAL FEITO!!");
	getch();
}

void executaComandosSql(tpBD **BD,FILE *ptr)
{
	char linha[250],auxP1[20],auxP2[20],auxP3[20],tabAux[20];
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	fgets(linha,250,ptr);
	separaPalavras(&d,linha);
	while(!feof(ptr))
	{
		if(d->inicio!=NULL)
		{
			strcpy(auxP1,d->inicio->palavra);
			if(strcmp(auxP1,"INSERT")==0)
					insert(&(*BD),linha);
			else
				if(strcmp(auxP1,"UPDATE")==0)
					update(&(*BD),linha);
				else
					if(strcmp(auxP1,"SELECT")==0)
						select(*BD,linha);
					else
						if(strcmp(auxP1,"DELETE")==0)
							deleteI(&(*BD),linha);
		}
		fgets(linha,250,ptr);
		excluirDesc(&d);
		separaPalavras(&d,linha);
	}
	clrscr();
	Moldura(1,1,120,30,3);
	Moldura(40,7,78,18,7);
	gotoxy(48,12);
	printf("SQL DE COMANDO FEITO!!");
	getch();
}

void digitarComand(tpBD **BD,char linha[])
{
		char auxP1[20];
		dAux *d = (dAux*) malloc(sizeof(dAux));
		inicializa(&d);
		separaPalavras3(&d,linha);
		if(d->inicio!=NULL)
		{
			strcpy(auxP1,d->inicio->palavra);
			if(strcmp(auxP1,"INSERT")==0)
					insert(&(*BD),linha);
			else
				if(strcmp(auxP1,"UPDATE")==0)
					update(&(*BD),linha);
				else
					if(strcmp(auxP1,"SELECT")==0)
						select(*BD,linha);
					else
						if(strcmp(auxP1,"DELETE")==0)
							deleteI(&(*BD),linha);
		}
}

char menu(void)
{
	clrscr();
	Moldura(1,1,120,30,3);
	Moldura(40,7,78,18,7);
	gotoxy(45,10);
	printf("[A] CRIAR ESTRUTURAS");
	gotoxy(45,11);
	printf("[B] LER COMANDOS SQL");
	gotoxy(45,12);
	printf("[C] DIGITAR COMANDOS SQL");
	gotoxy(45,13);
	printf("[ESC] SAIR");
	gotoxy(45,15);
	printf("ESCOLHA: ");
	return toupper(getch());
}

void executar(void)
{
	char op;
	char lin[250];
	int bancoAtivo=0,comandosAti=1;
	FILE *ptr = fopen("scriptdboficina.txt","r");
	FILE *ptr2 = fopen("INSERT UPDATE DELETE e SELECT.txt","r");
	tpBD *banco;
	op = menu();
	while(op!=27)
	{
		switch(op)
		{
			case'A':
				if(bancoAtivo==0)
				{
					executaSqlEstrutural(&banco,ptr);
					bancoAtivo = 1;
					comandosAti=0;
				}
				break;
			case'B':
				if(comandosAti==0)
				{
					executaComandosSql(&banco,ptr2);
					comandosAti = 1;	
				}
				break;
			case'C':
				if(bancoAtivo==1)
				{
					clrscr();
					Moldura(1,1,120,30,3);
					Moldura(40,7,78,18,7);
					gotoxy(45,12);
					printf("DIGITE O COMANDO: ");
					gotoxy(45,15);
					fflush(stdin);
					gets(lin);
					if(strcmp(lin,"")!=0)
					{
						digitarComand(&banco,lin);
					}
				}
				break;
		}
		op = menu();
	}
	fclose(ptr);
	fclose(ptr2);
	
}

int main()
{
	executar();
}
