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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Modularização

void iniciarBanco(tpBD **BD,char str[])
{
	*BD = (tpBD*) malloc(sizeof(tpBD));
	int i=0,j;
	char bd[20];
	for(j=0;j<2;i++)
		if(str[i]==' ')
			j++;
	for(j=0;str[i]!=';';i++,j++)
		bd[j] = str[i];
	bd[j] = '\0';
	strcpy((*BD)->bdName,bd);
	(*BD)->tabs = NULL;
}

void criarTabela(tpBD **BD,char tab[])
{
	
	tpTabela *nova = (tpTabela*) malloc(sizeof(tpTabela)),*aux;
	strcpy(nova->tabName,tab);
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
	for(j=0;str[i]!=' ';j++,i++)
		(*camp)->Campo[j] = str[i];
	(*camp)->Campo[j]= '\0';
	i++;
	for(j=0;str[i]!=' ';j++,i++)
			aux[j] = str[i];
	aux[j] = '\0';
	if(strcmp(aux,"INTERGER")==0)
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
