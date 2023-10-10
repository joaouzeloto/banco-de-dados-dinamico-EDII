////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ESTRUTURAS

union valorTab;
struct tpValor;

struct listCampos 
{
	struct tpValor *head,*tail;
};
typedef struct listCampos ListCps;

union valorTab
{
	char data[11];
	char valorT[20];
	char valorC;
	float floatT;
	int intT;
	ListCps *next;
};

struct tpCamposTab
{
	char Campo[20],Tipo,PK;
	struct tpCamposTab *FK,*prox;
	ListCps *no,*pAtual;	 	
};
typedef struct tpCamposTab tpCampos;

struct tpValor
{
	char tp; 
	union valorTab dados;
};
typedef struct tpValor tpValores;

struct tpTabelaBanco
{
	char tabName[20];
	tpCampos *campos;
	struct tpTabelaBanco *prox,*ant;
};
typedef struct tpTabelaBanco tpTabela;

struct tpBanco
{
	char bdName[20];
	tpTabela *tabs;
};
typedef struct tpBanco tpBD;

struct tpAuxiliar
{
	char palavra[20];
	struct tpAuxiliar *prox,*ant;
};
typedef struct tpAuxiliar tpAux;

struct descAux
{
	tpAux *inicio,*final;
};
typedef struct descAux dAux;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Modularização

void Moldura(int CI,int LI,int CF,int LF,int cor)
{
	long long int i;
	textcolor(cor);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1;i<CF;i++)
	{
		gotoxy(i,LI);
		printf("%c",205);
		gotoxy(i,LF);
		printf("%c",205);
	}
	for(i=LI+1;i<LF;i++)
	{
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	textcolor(7);
}

void inicializa(dAux **D)
{
	(*D)->inicio = (*D)->final = NULL;
}

void inserePalavra(dAux **aux,char palavra[])
{
	tpAux *novo = (tpAux*) malloc(sizeof(tpAux));
	strcpy(novo->palavra,palavra);
	novo->prox = NULL;
	if((*aux)->inicio==NULL)
	{
		novo->ant = NULL;
		(*aux)->inicio = (*aux)->final =novo;
	}
	else
	{
		novo->ant = (*aux)->final;
		(*aux)->final->prox = novo;
		(*aux)->final = novo;
	}
}

void excluirDesc(dAux **D)
{
	tpAux *garbage,*aux = (*D)->inicio;
	while(aux!=NULL)
	{
		garbage = aux;
		aux = aux->prox;
		free(garbage);
	}
	inicializa(&(*D));
}

void separaPalavras(dAux **D,char linha[])
{
	char pala[20];
	int i=0,j;
	while(linha[i] != '\n')
	{
		if(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=','&&linha[i]!='\n')
		{
			j=0;
			while(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=','&&linha[i]!='\n')
			{
				pala[j]= linha[i];
				i++;
				j++;
			}
			pala[j]='\0';
			inserePalavra(&(*D),pala);
			i--;
		}
		i++;
	}
}

void separaPalavras2(dAux **D,char linha[])
{
	char pala[20];
	int i=0,j;
	while(linha[i] != '\n')
	{
		if(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=','&&linha[i]!='\n'&&linha[i]!='('&&linha[i]!=')'&&linha[i]!=39)
		{
			j=0;
			while(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=','&&linha[i]!='\n'&&linha[i]!='('&&linha[i]!=')'&&linha[i]!=39)
			{
				pala[j]= linha[i];
				i++;
				j++;
			}
			pala[j]='\0';
			inserePalavra(&(*D),pala);
			i--;
		}
		i++;
	}
}

void separaPalavras3(dAux **D,char linha[])
{
	char pala[20];
	int i=0,j;
	while(linha[i] != '\0'&&linha[i] != '\n')
	{
		if(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=','&&linha[i]!='\n'&&linha[i]!='\0')
		{
			j=0;
			while(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=','&&linha[i]!='\n'&&linha[i]!='\0')
			{
				pala[j]= linha[i];
				i++;
				j++;
			}
			pala[j]='\0';
			inserePalavra(&(*D),pala);
			i--;
		}
		i++;
	}
}

void iniciarBanco(tpBD **BD,char str[])
{
	dAux *d = (dAux*) malloc(sizeof(dAux));
	*BD = (tpBD*) malloc(sizeof(tpBD));
	inicializa(&d);
	separaPalavras(&d,str);
	strcpy((*BD)->bdName,d->final->palavra);
	excluirDesc(&d);
	free(d);
	(*BD)->tabs = NULL;
}

void criarTabela(tpBD **BD,char tab[])
{
	dAux *d = (dAux*) malloc(sizeof(dAux));
	tpTabela *nova = (tpTabela*) malloc(sizeof(tpTabela)),*aux;
	inicializa(&d);
	separaPalavras(&d,tab);
	strcpy(nova->tabName,d->final->ant->palavra);
	nova->prox = NULL;
	nova->campos = NULL;
	if((*BD)->tabs==NULL)
	{
		nova->ant = NULL;
		(*BD)->tabs = nova;	
	}
	else
	{
		aux = (*BD)->tabs;
		while(aux->prox!=NULL)
			aux = aux->prox;
		aux->prox = nova;
		nova->ant = aux;
	}
}

void criarCaixaCamp(char str[],tpCampos **camp)
{
	int i=0,j;
	char aux[20];
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	separaPalavras(&d,str);
	strcpy((*camp)->Campo,d->inicio->palavra);
	strcpy(aux,d->inicio->prox->palavra);
	if(strcmp(aux,"INTEGER")==0)
		(*camp)->Tipo ='I';
	else
		if(strcmp(aux,"CHARACTER(20)")==0)
			(*camp)->Tipo ='T';
		else
			if(strcmp(aux,"DATE")==0)
				(*camp)->Tipo ='D';
			else
				if(strcmp(aux,"NUMERIC(6.2)")==0)
					(*camp)->Tipo ='N';
				else
					if(strcmp(aux,"CHARACTER(1)")==0)
						(*camp)->Tipo ='C';
	(*camp)->PK ='N';
	(*camp)->FK = NULL;
	(*camp)->no= NULL;
	(*camp)->pAtual= NULL;
	(*camp)->prox =NULL;
}

void criarCampos(tpBD **BD,char str[],char nomeT[20])
{
	tpTabela *aux= (*BD)->tabs;
	tpCampos *novo = (tpCampos*) malloc(sizeof(tpCampos)),*auxCamp;
	while(aux!=NULL&&strcmp(aux->tabName,nomeT)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		criarCaixaCamp(str,&novo);
		if(aux->campos==NULL)
			aux->campos = novo;
		else
		{
			auxCamp = aux->campos;
			while(auxCamp->prox!=NULL)
				auxCamp = auxCamp->prox;
			auxCamp->prox = novo;
		}
	}
}

void adicionaPK(tpBD **BD,char str[],char nomeT[20])
{
	int i=0,j;
	char campo[20];
	tpTabela *aux = (*BD)->tabs;
	tpCampos *auxCamp;
	while(strcmp(aux->tabName,nomeT)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		while(str[i]!='(')
			i++;
		i++;
		for(j=0;str[i]!=')';i++,j++)
			campo[j] = str[i];
		i++;
		campo[j]='\0';
		auxCamp = aux->campos;
		while(auxCamp->prox!=NULL&&strcmp(auxCamp->Campo,campo)!=0)
			auxCamp = auxCamp->prox;
		if(auxCamp!=NULL)
			auxCamp->PK = 'S';
	}
}

void adicionaFK(tpBD **BD,char str[],FILE *ptr)
{
	char linha2[100];
	char tab[20],fk[20],tabO[20];
	dAux *d = (dAux*) malloc(sizeof(dAux)),*d2 = (dAux*) malloc(sizeof(dAux));
	tpTabela *ende,*ori,*aux=(*BD)->tabs; 
	tpCampos *auxCamp, *auxDest;
	inicializa(&d);
	separaPalavras(&d,str);
	fgets(linha2,100,ptr);
	inicializa(&d2);
	separaPalavras2(&d2,linha2);
	strcpy(tab,d->inicio->prox->prox->palavra);
	strcpy(tabO,d2->inicio->prox->prox->prox->prox->palavra);
	strcpy(fk,d2->final->palavra);
	while(strcmp(aux->tabName,tab)!=0)
		aux = aux->prox;
	if(aux!=NULL)
		ende = aux;
	aux=(*BD)->tabs;
	while(strcmp(aux->tabName,tabO)!=0)
		aux = aux->prox;
	if(aux!=NULL)
		ori = aux;
	auxCamp = ori->campos;
	while(strcmp(auxCamp->Campo,fk)!=0)
		auxCamp = auxCamp->prox;
	if(auxCamp!=NULL)
	{
		auxDest = ende->campos;
		while(strcmp(auxDest->Campo,fk)!=0)
			auxDest = auxDest->prox;
		if(auxDest!=NULL)
			auxDest->FK = auxCamp;
	}
}

int stringToInt(const char *str) {
    int result = 0;
    int sign = 1; 

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str) {
        if (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');
        } else {
            return 0;
        }
        str++; 
    }

    result *= sign;

    return result;
}

void criaCaixaInt(int result,tpCampos **auxCamp)
{
	ListCps *nc = (ListCps*) malloc(sizeof(ListCps));
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	novo->dados.intT = result;
	novo->tp = 'I';
	nc->head = novo;
	nc->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		//printf("\nlugar certo");
		(*auxCamp)->no = nc;	
		(*auxCamp)->pAtual = nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = nc;
	}
	
}

void criaCaixaString(char result[],tpCampos **auxCamp)
{
	ListCps *nc = (ListCps*) malloc(sizeof(ListCps));
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	strcpy(novo->dados.valorT,result);
	novo->tp = 'T';
	nc->head = novo;
	nc->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = nc;	
		(*auxCamp)->pAtual = nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = nc;
	}
	
}

void criaCaixaChar(char result,tpCampos **auxCamp)
{
	ListCps *nc = (ListCps*) malloc(sizeof(ListCps));
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	novo->dados.valorC = result;
	novo->tp = 'C';
	nc->head = novo;
	nc->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = nc;	
		(*auxCamp)->pAtual = nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = nc;
	}
	
}

void criaCaixaData(char result[],tpCampos **auxCamp)
{
	ListCps *nc = (ListCps*) malloc(sizeof(ListCps));
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	strcpy(novo->dados.data,result);
	novo->tp = 'D';
	nc->head = novo;
	nc->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = nc;	
		(*auxCamp)->pAtual = nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = nc;
	}
}
float stringToFloat(const char *str) {
    float result = 0.0;
    int decimalFound = 0;
    int sign = 1; 
    if (*str == '-') {
        sign = -1;
        str++; 
    }

    while (*str) {
        if (*str >= '0' && *str <= '9') {
            result = result * 10.0 + (*str - '0');
            if (decimalFound) {
                decimalFound *= 10;
            }
        } else if (*str == '.') {
            decimalFound = 1;
        } else {
            return 0.0;
        }
        str++; 
    }

    result /= decimalFound;
    result *= sign;

    return result;
}

void criaCaixaFloat(float result,tpCampos **auxCamp)
{
	ListCps *nc = (ListCps*) malloc(sizeof(ListCps));
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	novo->dados.floatT = result;
	novo->tp = 'N';
	nc->head = novo;
	nc->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = nc;	
		(*auxCamp)->pAtual = nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = nc;
	}
}

void insert(tpBD **BD,char linha[])
{
	float auxFloat;
	int valor;
	char tabNome[20],auxP[20];
	tpTabela *tabAux = (*BD)->tabs;
	tpCampos *auxCamp;
	dAux *d = (dAux*) malloc(sizeof(dAux));
	tpAux *perco;
	inicializa(&d);
	separaPalavras2(&d,linha);
	strcpy(tabNome,d->inicio->prox->prox->palavra);
	while(strcmp(tabAux->tabName,tabNome)!=0)
		tabAux = tabAux->prox;
	if(tabAux!=NULL)
	{
		perco = d->inicio;
		while(strcmp(perco->palavra,"values")!=0)
			perco = perco ->prox;
		//printf("\n%s",perco->palavra);
		if(perco!=NULL)
		{
			perco = perco->prox;
			auxCamp = tabAux->campos;
			while(auxCamp!=NULL)
			{
				//printf("\n%s",perco->palavra);
				switch(auxCamp->Tipo)
				{
					case 'I':
						valor = stringToInt(perco->palavra);
						criaCaixaInt(valor,&auxCamp);
						//printf("\n%s",auxCamp->Campo);
						//printf("\n%d",auxCamp->no->head->dados.intT);
						break;
					case 'T':
						criaCaixaString(perco->palavra,&auxCamp);
						break;
					case 'C':
						criaCaixaChar(perco->palavra[0],&auxCamp);
						break;
					case 'D':
						criaCaixaData(perco->palavra,&auxCamp);
						break;
					case 'N':
						auxFloat = stringToFloat(perco->palavra);
						criaCaixaFloat(auxFloat,&auxCamp);
						break;						
				}
				auxCamp = auxCamp->prox;
				perco = perco->prox;
			}
		}
	}
}

void update(tpBD **BD,char linha[])
{//UPDATE peca SET estoque = 0 WHERE id_peca = 8;
	tpTabela *aux = (*BD)->tabs;
	ListCps *list;
	tpCampos *auxCamp1,*auxCamp2;
	char tab[20],ind[20],muda[20];
	int compare,cont=0,nvoV;
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	separaPalavras(&d,linha);
	strcpy(tab,d->inicio->prox->palavra);
	while(aux!=NULL&&strcmp(aux->tabName,tab)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		auxCamp1 = aux->campos;
		strcpy(ind,d->final->ant->ant->palavra);
		while(auxCamp1!=NULL&&strcmp(auxCamp1->Campo,ind)!=0)
			auxCamp1 = auxCamp1 ->prox;
		if(auxCamp1!=NULL)
		{
				auxCamp2 = aux->campos;
				strcpy(muda,d->inicio->prox->prox->prox->palavra);
				while(auxCamp2!=NULL&&strcmp(auxCamp2->Campo,ind)!=0)
					auxCamp2 = auxCamp2 ->prox;
				if(auxCamp2!=NULL)
				{
					compare = stringToInt(d->final->palavra);
					list = auxCamp1->no;
					while(list!=NULL && list->head->dados.intT!=compare)
					{
						cont++;
						list = list->tail->dados.next;
					}
	
					if(list!=NULL)
					{
						nvoV = stringToInt(d->inicio->prox->prox->prox->prox->prox->palavra);
						list = auxCamp2->no;
						for(;cont>0;cont--)
							list = list->tail->dados.next;
						//printf("\n%d",list->head->dados.intT);
						list->head->dados.intT = nvoV;
						//printf("\n%d",list->head->dados.intT);
					}
						
				}
		}	
	}
}

void exibeTab(tpBD *BD,char pala[])
{
	clrscr();
	Moldura(1,1,120,30,3);
	tpTabela *aux = BD->tabs;
	tpCampos *auxCamp;
	int lin,col;
	ListCps *list;
	while(aux!=NULL&&strcmp(aux->tabName,pala)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		gotoxy(45,2);
		printf("TABELA: %s", aux->tabName);
		auxCamp = aux->campos;
		lin = 4;
		col =2;
		while(auxCamp!=NULL)
		{
			gotoxy(col,lin);
			printf("%s",auxCamp->Campo);
			list = auxCamp->no;
			lin++;
			while(list!=NULL)
			{
				switch(list->head->tp)
				{
					case 'I': 
						gotoxy(col,lin);
						printf("%d",list->head->dados.intT);
						break;
					case 'T': 
						gotoxy(col,lin);
						printf("%s",list->head->dados.valorT);
						break;
					case 'D': 
						gotoxy(col,lin);
						printf("%s",list->head->dados.data);
						break;
					case 'N': 
						gotoxy(col,lin);
						printf("%.2f",list->head->dados.floatT);
						break;
					case 'C':
						gotoxy(col,lin);
						printf("%c",list->head->dados.valorC);
						break;
				}
				if(list->tail!=NULL)
					list = list->tail->dados.next;
				else
					list = NULL;
				lin++;
			}
			col = col + 15;
			lin = 4;
			auxCamp = auxCamp->prox;
		}
	}
	getch();
}

void exibeTabBetween(tpBD *BD,int min,int max,tpAux *a,char indice[])
{
	clrscr();
	Moldura(1,1,120,30,3);
	char tab[20];
	ListCps *perc,*perc2;
	tpCampos *auxCamp,*ind;
	tpTabela *aux = BD->tabs;
	int lin,col,v;
	int cont,contL;
	while(strcmp(a->palavra,"FROM")!=0)
		a = a->prox;
	a = a->prox;
	strcpy(tab,a->palavra);
	while(aux!=NULL&&strcmp(aux->tabName,tab)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
			gotoxy(45,2);
			printf("TABELA: %s", aux->tabName);
			getch();
			lin = 4;
			col =2;
			auxCamp = aux->campos;
			while(auxCamp!=NULL)
			{
				gotoxy(col,lin);
				printf("%s",auxCamp->Campo);
				auxCamp = auxCamp->prox;
				col = col + 15;
			}
			col = 2;
			lin++;
			auxCamp = aux->campos;
			while(auxCamp!=NULL&&strcmp(auxCamp->Campo,indice)!=0)
				auxCamp = auxCamp->prox;
			if(auxCamp!=NULL)
			{
				ind =auxCamp;
				perc = ind->no;
				cont = 0;
				while(perc!=NULL)
				{
					cont++;
					v = perc->head->dados.intT;
					printf("\n%d",v);
					if(v>=max&&v<=min)
					{
						printf("\nentrei");
						getch();
						auxCamp = aux->campos;
						while(auxCamp!=NULL)
						{
							perc2 = auxCamp->no;
							for(contL = cont;perc!=NULL&&contL>0;cont--)
								if(perc2->tail!=NULL)
									perc2 = perc2->tail->dados.next;
								else
									perc2 =NULL;
							if(perc2!=NULL)
							{
								switch(perc2->head->tp)
								{
									case 'I': 
										gotoxy(col,lin);
										printf("%d",perc2->head->dados.intT);
										break;
									case 'T': 
										gotoxy(col,lin);
										printf("%s",perc2->head->dados.valorT);
										break;
									case 'D': 
										gotoxy(col,lin);
										printf("%s",perc2->head->dados.data);
										break;
									case 'N': 
										gotoxy(col,lin);
										printf("%.2f",perc2->head->dados.floatT);
										break;
									case 'C':
										gotoxy(col,lin);
										printf("%c",perc2->head->dados.valorC);
										break;
								}
							}
							col = col + 15;
							auxCamp = auxCamp->prox;			
						}
						col=2;
						lin++;
					}
					if(perc->tail!=NULL)
						perc = perc2->tail->dados.next;
					else
						perc =NULL;
				}
			}
	}
}

void selectTudo(tpBD *BD,char linha[])
{
	char auxPala[20];
	int min,max;
	dAux *d = (dAux*) malloc(sizeof(dAux));
	tpAux *perc;
	inicializa(&d);
	separaPalavras3(&d,linha);
	if(strcmp(d->final->ant->palavra,"AND")==0)
	{
		strcpy(auxPala,d->final->ant->ant->ant->ant->palavra);
		min = stringToInt(d->final->palavra);
		max = stringToInt(d->final->ant->ant->palavra);
		perc = d->inicio;
		exibeTabBetween(BD,min,max,d->inicio,auxPala);
	}
	else
	{
		perc = d->inicio->prox->prox->prox;
		while(perc!=NULL)
		{
			strcpy(auxPala,perc->palavra);
			exibeTab(BD,auxPala);
			perc = perc->prox;
		}
	}
}

void exibePartTab(tpBD *BD, char tab[],tpAux *a)
{
	clrscr();
	Moldura(1,1,120,30,3);
	tpTabela *aux = BD->tabs;
	tpCampos *auxCamp;
	int lin,col;
	ListCps *list;
	while(aux!=NULL&&strcmp(aux->tabName,tab)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		gotoxy(45,2);
		printf("TABELA: %s", aux->tabName);
		auxCamp = aux->campos;
		lin = 4;
		col =2;
		while(strcmp(a->palavra,"FROM")!=0)
		{
			while(auxCamp!=NULL&&strcmp(auxCamp->Campo,a->palavra)!=0)
				auxCamp = auxCamp->prox;
			if(auxCamp!=NULL)
			{
				gotoxy(col,lin);
				printf("%s",auxCamp->Campo);
				list = auxCamp->no;
				lin++;
				while(list!=NULL)
				{
					switch(list->head->tp)
					{
						case 'I': 
							gotoxy(col,lin);
							printf("%d",list->head->dados.intT);
							break;
						case 'T': 
							gotoxy(col,lin);
							printf("%s",list->head->dados.valorT);
							break;
						case 'D': 
							gotoxy(col,lin);
							printf("%s",list->head->dados.data);
							break;
						case 'N': 
							gotoxy(col,lin);
							printf("%.2f",list->head->dados.floatT);
							break;
						case 'C':
							gotoxy(col,lin);
							printf("%c",list->head->dados.valorC);
							break;
					}
					if(list->tail!=NULL)
						list = list->tail->dados.next;
					else
						list = NULL;
					lin++;
				}
				col = col + 15;
				lin = 4;	
			}
			a = a->prox;
			auxCamp = aux->campos;
		}
	}
	getch();
}

void selectPartes(tpBD *BD,char linha[])
{
	char auxPala[20];
	dAux *d = (dAux*) malloc(sizeof(dAux));
	tpAux *perc;
	inicializa(&d);
	separaPalavras3(&d,linha);
	strcpy(auxPala,d->final->palavra);
	perc = d->inicio->prox;
	exibePartTab(BD,auxPala,perc);
}

void select(tpBD *BD,char linha[])
{
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	separaPalavras3(&d,linha);
	if(d->inicio->prox->palavra[0]=='*')
	{
		selectTudo(BD,linha);
	}
	else
	{
		selectPartes(BD,linha);
	}
}

void deleteI(tpBD **BD,char linha[])
{//DELETE FROM veiculo WHERE id_veiculo = 2;
	tpTabela *aux = (*BD)->tabs;
	ListCps *list,*anterior=NULL;
	tpCampos *auxCamp1,*auxCamp2;
	char tab[20],ind[20],muda[20];
	int compare,cont=0,nvoV;
	dAux *d = (dAux*) malloc(sizeof(dAux));
	inicializa(&d);
	separaPalavras3(&d,linha);
	strcpy(tab,d->inicio->prox->prox->palavra);
	while(aux!=NULL&&strcmp(aux->tabName,tab)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		auxCamp1 = aux->campos;
		strcpy(ind,d->final->ant->ant->palavra);
		while(auxCamp1!=NULL&&strcmp(auxCamp1->Campo,ind)!=0)
			auxCamp1 = auxCamp1 ->prox;
		if(auxCamp1!=NULL)
		{
					compare = stringToInt(d->final->palavra);
					list = auxCamp1->no;
					while(list!=NULL && list->head->dados.intT!=compare)
					{
						cont++;
						list = list->tail->dados.next;
					}
					nvoV = cont;
					if(list!=NULL)
					{
						auxCamp2 = aux->campos;
						list = auxCamp2->no;
						while(auxCamp2!=NULL)
						{
							for(cont=nvoV;list!=NULL&&cont>0;cont--)
							{
								anterior = list;
								if(list->tail!=NULL)
									list = list->tail->dados.next;
								else
									list->tail = NULL;
							}
							if(anterior==NULL)
							{
								if(list->tail!=NULL)
									auxCamp2->no = list->tail->dados.next;
								else
								{
									auxCamp2->no = NULL;
									auxCamp2->pAtual = NULL;
								}
							}
							else
							{
								if(list->tail!=NULL)
									anterior->tail->dados.next = list->tail->dados.next;
								else
								{
									auxCamp2->pAtual = anterior;
									anterior->tail = NULL;
								}
							}
							free(list);		
							auxCamp2 = auxCamp2->prox;
							if(auxCamp2!=NULL)
								list = auxCamp2->no;
						}
						
					}
						
				
		}	
	}
}
