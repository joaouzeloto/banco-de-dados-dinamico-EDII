//Criando as structs 
struct intTab
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

union valorTab
{
	valorDT *data;
	valorT *strM;
	valorC *letr;
	floatT	*salario;
	intT *qtde;
};

struct tpCamposTab
{
	char Campo[20],Tipo,PK;
	struct tpCamposTab *FK,*prox;
	union valorTab no;	 	
};
typedef struct tpCamposTab tpCampos;

struct listCampos 
{
	tpCampos *head,*tale;
};
typedef struct listCampos ListCps;
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

void iniciarBanco(tpBD **BD,char nome[20])
{
	*BD = (tpBD*) malloc(sizeof(tpBD));
	strcpy((*BD)->bdName,nome);
	(*BD)->tabs = NULL;
}
