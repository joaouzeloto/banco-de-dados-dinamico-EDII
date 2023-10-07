#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"TADBD.h"

/*void executaSqlEstrutural(tpBD **BD,FILE *ptr)
{
	int i,j;
	char linha[50],auxP1[20],auxP2[20],auxP3[20],tabAux[20];
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	fgets(linha,50,ptr);
	separaPalavras(&d,linha);
	while(!feof(ptr))
	{
		if(d->inicio!=NULL)
		{
			strcpy(auxP1,d->inicio->palavra);
			if(strcmp(auxP1,"CREATE")==0)
			{
					strcmp(auxP2,d->inicio->prox->palavra)
					if(strcmp(auxP2,"DATABASE")==0)
						iniciarBanco(BD,linha);
					else
					{
						for(j=0;j<1;i++)
							if(linha[i]==' ')
								j++;
						for(j=0;linha[i]!=' ';i++,j++)
							tabAux[j] = linha[i];
						tabAux[j] = '\0';
						criarTabela(BD,tabAux);
						fgets(linha,50,ptr);
						while(strcmp(linha,");\n")!=0)
						{
							i=0;
							for(j=0;linha[i]!=' ';i++,j++)
								auxP3[j] = linha[i];
							auxP3[j] = '\0';
							if(strcmp(auxP3,"CONSTRAINT")==0)
								adicionaPK(BD,linha,tabAux);
							else
								criarCampos(BD,linha,tabAux);
							fgets(linha,50,ptr);
						}
					}
			}
		}
		fgets(linha,50,ptr);
	}
}*/

int main()
{
	int i;
	char tab[50];
	FILE *ptr = fopen("scriptdboficina.txt","r");
	tpBD *banco;
	iniciarBanco(&banco,fgets(tab,50,ptr));
	printf("\nNome do banco: %s",banco->bdName);
	fgets(tab,50,ptr);
	criarTabela(&banco,fgets(tab,50,ptr));
	printf("\nNome da tabela: %s",banco->tabs->tabName);
	criarCampos(&banco,fgets(tab,50,ptr),banco->tabs->tabName);
	printf("\nNome da campo: %s",banco->tabs->campos->Campo);
	printf("\nTipo do campo: %c",banco->tabs->campos->Tipo);
	fclose(ptr);
}

/*iniciarBanco(&banco,"bancoProj");
	printf("\nNome do banco: %s",banco->bdName);
	criarTabela(&banco,"Clientes");
	criarTabela(&banco,"Veiculos");	
	printf("\nTABELA: %s",banco->tabs->tabName);
	criarCampos(&banco,"id_cliente INTEGER NOT NULL","Clientes");
	criarCampos(&banco,"nome CHARACTER(20)","Clientes");
	criarCampos(&banco,"id_cliente INTEGER NOT NULL","Veiculos");
	printf("\nCampo: %s Tipo: %c",banco->tabs->campos->Campo,banco->tabs->campos->Tipo);
	printf("\nCampo: %s Tipo: %c",banco->tabs->campos->prox->Campo,banco->tabs->campos->prox->Tipo);
	adicionaPK(&banco,"CONSTRAINT PK_aluguel PRIMARY KEY (id_cliente)","Cliente");
	printf("\nCampo: %s PK: %c",banco->tabs->campos->Campo,banco->tabs->campos->PK);
	adicionaFK(&banco,"ALTER TABLE Veiculos ADD CONSTRAINT cliente_aluguel FOREIGN KEY (id_cliente) REFERENCES Clientes (id_cliente);");
	printf("\nFK:%s",banco->tabs->prox->campos->FK->Campo);
*/
