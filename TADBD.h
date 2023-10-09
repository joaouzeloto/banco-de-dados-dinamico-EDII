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
				if(strcmp(aux,"NUMERIC(6,2)")==0)
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

void criaCaixaInt(int result,ListCps **nc,tpCampos **auxCamp)
{
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	novo->dados.intT = result;
	novo->tp = 'I';
	(*nc)->head = novo;
	(*nc)->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = *nc;	
		(*auxCamp)->pAtual = *nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = *nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = *nc;
	}
	
}

void criaCaixaString(char result[],ListCps **nc,tpCampos **auxCamp)
{
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	strcpy(novo->dados.valorT,result);
	novo->tp = 'T';
	(*nc)->head = novo;
	(*nc)->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = *nc;	
		(*auxCamp)->pAtual = *nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = *nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = *nc;
	}
	
}

void criaCaixaChar(char result,ListCps **nc,tpCampos **auxCamp)
{
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	novo->dados.valorC = result;
	novo->tp = 'C';
	(*nc)->head = novo;
	(*nc)->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = *nc;	
		(*auxCamp)->pAtual = *nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = *nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = *nc;
	}
	
}

void criaCaixaData(char result[],ListCps **nc,tpCampos **auxCamp)
{
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	strcpy(novo->dados.data,result);
	novo->tp = 'D';
	(*nc)->head = novo;
	(*nc)->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = *nc;	
		(*auxCamp)->pAtual = *nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = *nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = *nc;
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

void criaCaixaFloat(float result,ListCps **nc,tpCampos **auxCamp)
{
	tpValores *novo = (tpValores*) malloc(sizeof(tpValores)),*novo2 = (tpValores*) malloc(sizeof(tpValores));
	novo->dados.floatT = result;
	novo->tp = 'D';
	(*nc)->head = novo;
	(*nc)->tail = NULL;
	if((*auxCamp)->no==NULL)
	{
		(*auxCamp)->no = *nc;	
		(*auxCamp)->pAtual = *nc;
	}
	else
	{
		novo2->tp = 'E';
		novo2->dados.next = *nc;
		(*auxCamp)->pAtual->tail = novo2;
		(*auxCamp)->pAtual = *nc;
	}
}

void insert(tpBD **BD,char linha[])
{
	float auxFloat;
	ListCps *nova = (ListCps*) malloc(sizeof(ListCps));
	int valor;
	char vet[10];
	char tabNome[20],auxP[20];
	tpTabela *tabAux = (*BD)->tabs;
	tpCampos *auxCamp;
	dAux *d = (dAux*) malloc(sizeof(dAux));
	tpAux *perco;
	inicializa(&d);
	separaPalavras2(&d,linha);
	strcpy(tabNome,d->inicio->prox->prox->palavra);
	while(strcmp(tabAux->tabName,tabNome)==0)
		tabAux = tabAux->prox;
	if(tabAux!=NULL)
	{
		perco = d->inicio;
		while(strcmp(perco->palavra,"values")!=0)
			perco = perco ->prox;
		if(perco!=NULL)
		{
			perco = perco->prox;
			auxCamp = tabAux->campos;
			while(auxCamp!=NULL)
			{
				switch(auxCamp->Tipo)
				{
					case 'I':
						valor = stringToInt(perco->palavra);
						criaCaixaInt(valor,&nova,&auxCamp);
						break;
					case 'T':
						criaCaixaString(perco->palavra,&nova,&auxCamp);
						break;
					case 'C':
						criaCaixaChar(perco->palavra[0],&nova,&auxCamp);
						break;
					case 'D':
						criaCaixaData(perco->palavra,&nova,&auxCamp);
						break;
					case 'F':
						auxFloat = stringToFloat(perco->palavra);
						criaCaixaFloat(auxFloat,&nova,&auxCamp);
						break;						
				}
				perco = perco->prox;
			}
		}
	}
}
