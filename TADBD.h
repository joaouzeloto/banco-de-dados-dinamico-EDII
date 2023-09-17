//Criando as structs 
/*struct intTab
{
	int num;
	struct intTab *prox;	
};
typedef struct intTab intT;

struct floatTab
{
	float num;	
	struct floatTab *prox;
};
typedef struct floatTab floatT;

struct svalorDT
{
	char dat[10];
	struct svalorDT *prox;	
};
typedef struct svalorDT valorDT;

struct svalorT
{
	char str[20];
	struct svalorT *prox;	
};
typedef struct svalorT valorT;

struct svalorC
{
	char letra;
	struct svalorC *prox;	
};
typedef struct svalorC valorC;
*/
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

void iniciarBanco(tpBD **BD,char nome[])
{
	*BD = (tpBD*) malloc(sizeof(tpBD));
	strcpy((*BD)->bdName,nome);
	(*BD)->tabs = NULL;
}

void criarTabela(tpBD **BD,char nome[])
{
	
	tpTabela *nova = (tpTabela*) malloc(sizeof(tpTabela)),*aux;
	strcpy(nova->tabName,nome);
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
	if(strcmp(aux,"CHARACTER(20)")==0)
		(*camp)->Tipo ='T';
	if(strcmp(aux,"DATE")==0)
		(*camp)->Tipo ='D';
	if(strcmp(aux,"NUMERIC")==0)
		(*camp)->Tipo ='N';
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
			while(auxCamp!=NULL)
				auxCamp = auxCamp->prox;
			auxCamp->prox = novo;
		}
	}
}
