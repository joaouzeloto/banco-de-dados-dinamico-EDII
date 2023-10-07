////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	ESTRUTURAS

union valorTab;

struct listCampos 
{
	valorTab *head,*tale;
};
typedef struct listCampos ListCps;

union valorTab
{
	char data[10];
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
		if(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=',')
		{
			j=0;
			while(linha[i]!=' '&&linha[i]!=';'&&linha[i]!=',')
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
				if(strcmp(aux,"NUMERIC")==0)
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

void adicionaFK(tpBD **BD,char str[])
{
	int i=0,j;
	tpTabela *ende,*ori,*aux=(*BD)->tabs; 
	tpCampos *auxCamp,*auxAcha;
	char tab[20],fk[20],tabO[20];
	for(j=0;j<2;i++)
		if(str[i]==' ')
			j++;
	for(j=0;str[i]!=' ';i++,j++)
		tab[j] = str[i];
	tab[j]='\0';
	for(;str[i]!='(';)
		i++;
	i++;
	for(j=0;str[i]!=')';i++,j++)
		fk[j] = str[i];
	fk[j]='\0';
	for(j=0;j<2;i++)
		if(str[i]==' ')
			j++;
	for(j=0;str[i]!=' ';i++,j++)
		tabO[j] = str[i];
	tabO[j]='\0';
	while(aux!=NULL&&strcmp(aux->tabName,tab)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		ende = aux;
		aux=(*BD)->tabs;
		while(aux!=NULL&&strcmp(aux->tabName,tabO)!=0)
			aux = aux->prox;
		if(aux!=NULL)
		{
			ori = aux;
			auxCamp = ori->campos;
			while(auxCamp!=NULL&&strcmp(auxCamp->Campo,fk)!=0)
				auxCamp = auxCamp->prox;
		
			if(auxCamp!=NULL)
			{
				auxAcha = ende->campos;
				while(auxAcha!=NULL&&strcmp(auxAcha->Campo,fk)!=0)
					auxAcha = auxCamp->prox;
				if(auxAcha!=NULL)
					auxAcha->FK = auxCamp;
			}	
		}
	}
}
