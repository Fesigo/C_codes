// Felipe Siqueira Godoy 		RA: 190337
// Guilherme Machado Crespo		RA: 190501

// Método Simplex

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct variaveis{
	int n;
	char cat[6]; //VB ou VNB
	int line;
}variaveis;

void aloca_float(float **p, int tam); // Função de alocação para variáveis float
void aloca_struct(variaveis **p, int tam); // Função de alocação para variáveis struct

int cont_linhas(); // Função que retorna a quantidade de linhas de restrições

void inicializa_matriz(float *m, int lin, int col); // Inicializa a matriz com 0's
void inicializa_var(variaveis *v, int vd, int rest); // Inicializa as variáveis com VB ou VNB (variáveis básicas e não básicas)

void tabela(float *m, int lin, int col, float *r, int vd, float *d); // Função para montar a tabela
void simplex(float *m, int lin, int col, variaveis *v); // Método Simplex

int coluna_pivo(float *m, int lin, int col); // Função para selecionar a coluna pivô
int linha_p(float *m, int lin, int col, int c); // Função para achar a linha onde entrará a variável da coluna pivô

void troca_base(variaveis *v, int lin, int col, int qtd_col); // Coloca e tira variáveis da base

int main()
{
	int cont_vd = 0, i, j, tam, cont_rest = 0, linhas, lin, col;
	float *var_decisao = NULL, auxf, *restricoes = NULL;
	char vd[100], *l = NULL;
	variaveis *var = NULL;
	FILE *fptr = NULL;
	
	if((fptr=fopen("entrada.txt", "r")) == NULL) // Abrindo o arquivo para leitura
		printf("\nArquivo nao encontrado\n");
	else
	{
		// Lendo a primeira linha para pegar os valores das variáveis de decisão
		l = fgets(vd, 100, fptr);
		
		tam = strlen(l);
		
		// Convertendo os valores de uma string para float e salvando em um vetor
		for(i=0; i<tam; i++)
		{
			auxf = strtof(l, &l);
			
			if(auxf == 0)
				break;
			
			aloca_float(&var_decisao, cont_vd+1);
			*(var_decisao+cont_vd) = auxf;
			cont_vd++;	
		}
		
		linhas = cont_linhas();
		lin = linhas+1;
		col = cont_vd+linhas+1;
		
		// Lendo as linhas de restrições e salvando em um vetor
		for(i=0; i<linhas; i++)
		{
			l = fgets(vd, 100, fptr);
			
			tam = strlen(l);
			
			for(j=0; j<cont_vd+1; j++)
			{
				auxf = strtof(l, &l);
				
				aloca_float(&restricoes, cont_rest+1);
				*(restricoes+cont_rest) = auxf;
				cont_rest++;
			}
		}
		
		fclose(fptr);
		
		float mat[linhas+1][cont_vd+linhas+1];
		inicializa_matriz(*mat, lin, col);
		
		tabela(*mat, linhas+1, cont_vd+linhas+1, restricoes, cont_vd, var_decisao);
		
		aloca_struct(&var, cont_vd+linhas);
		inicializa_var(var, cont_vd, linhas);
		
		simplex(*mat, lin, col, var);
	}
	
	system("pause");
	
	return 0;
}

void aloca_float(float **p, int tam) // Função de alocação para variáveis float
{
	if((*p=(float*)realloc(*p, tam*sizeof(float)))==NULL)
	{
		printf("\nErro de alocacao\n");
		exit(1);
	}
}

void aloca_struct(variaveis **p, int tam) // Função de alocação para variáveis struct
{
	if((*p=(variaveis*)realloc(*p, tam*sizeof(variaveis)))==NULL)
	{
		printf("\nErro de alocacao\n");
		exit(1);
	}
}

int cont_linhas() // Função que retorna a quantidade de linhas de restrições
{
	int cont = 0;
	char c;
	FILE *fptr = NULL;
	
	if((fptr=fopen("entrada.txt", "r")) == NULL)
		printf("\nArquivo nao encontrado\n");
	else
	{
		for (c = getc(fptr); c != EOF; c = getc(fptr)) 
        if (c == '\n')
            cont = cont + 1;
        
        fclose(fptr);
	}
	return cont;
}

void inicializa_matriz(float *m, int lin, int col) // Inicializa a matriz com 0's
{
	int i, j;
	
	for(i=0; i<lin; i++)
	{
		for(j=0; j<col; j++)
		{
			*(m+j*col+i) = 0;
		}
	}
}

void inicializa_var(variaveis *v, int vd, int rest) // Inicializa as variáveis com VB ou VNB (variáveis básicas e não básicas)
{
	int i;
	
	for(i=0; i<=vd+rest; i++)
	{
		(v+i)->n = i;
		
		if(i<vd)
		{
			strcpy((v+i)->cat, "VNB");
			(v+i)->line = -1;
		}
		else
		{
			strcpy((v+i)->cat, "VB");
			(v+i)->line = i - vd;
		}
	}
}

void tabela(float *m, int lin, int col, float *r, int vd, float *d) //Função para montar a tabela
{
	int i, j, k=0;
	
	for(i=0; i<lin; i++)
	{
		for(j=0; j<col; j++) // Atribuindo os valores das variáveis na matriz, em seus respectivos lugares
		{
			if(j < vd || j == col-1)
			{
				if(i == lin-1)
				{
					*(m+j*col+i) = *(d + j) * (-1);
				}
				else
				{
					*(m+j*col+i) = *(r + k);
					k++;
				}
			}
			else
			{
				if(j == i+vd)
					*(m+j*col+i) = 1;
				else
					*(m+j*col+i) = 0;
			}
		}
	}
	
	*(m+(col-1)*col+(lin-1)) = 0;
}

void simplex(float *m, int lin, int col, variaveis *v) // Método Simplex
{
	int i, j, linha, coluna;
	float divisor, razao;
	
	printf("\nSimplex\n");
	
	do{
		coluna = coluna_pivo(m, lin, col);
		
		if(coluna == -1) // Verificando se há valores negativos na linha do Z
			break;
		
		linha = linha_p(m, lin, col, coluna);
		
		troca_base(v, linha, coluna, col);
		
		divisor = *(m+coluna*col+linha);
		
		for(j=0; j<col; j++) // Dividindo os valores da linha para que o valor na coluna pivô fique igual a 1
		{
			*(m+j*col+linha) = (*(m+j*col+linha)) / divisor;
		}
		
		for(i=0; i<lin; i++) // Multiplicando e somando os valores da linha que sairá da base às outras linhas, tornando os outros valores da coluna pivô igual a 0
		{
			if(*(m+coluna*col+i) != 0 && i != linha)
			{
				razao = (*(m+coluna*col+i)) * (-1);
				
				for(j=0; j<col; j++)
				{
					*(m+j*col+i) += (*(m+j*col+linha)) * razao;
				}
			}
		}
		
	}while(coluna != -1);
	
	printf("\nVariaveis basicas:");
	for(i=0; i<lin+1; i++)
	{
		if(strcmp((v+i)->cat, "VB") == 0)
		{
			printf("\nX%i = %.2f", (v+i)->n + 1, *(m+(col-1)*col+(v+i)->line));
		}
	}
	
	printf("\n\nVariaveis nao basicas:");
	
	for(i=0; i<lin+1; i++)
	{
		if(strcmp((v+i)->cat, "VNB") == 0)
		{
			printf("\nX%i = 0.00", (v+i)->n + 1);
		}
	}
	
	printf("\n\nFuncao Objetivo:\nZ: %.2f\n\n", *(m+(col-1)*col+(lin-1)));
	
}

int coluna_pivo(float *m, int lin, int col) // Função para selecionar a coluna pivô
{
	int i, j, c;
	float menor;
	
	i = lin-1;
	
	for(j=0; j<col; j++){
		if(j==0)
		{
			menor = *(m+j*col+i);
			c = 0;
		}
		else if(*(m+j*col+i) < menor)
		{
			menor = *(m+j*col+i);
			c = j;
		}
	}
	
	if(menor < 0)
		return c;
	else
		return -1;
}

int linha_p(float *m, int lin, int col, int c) // Função para achar a linha onde entrará a variável da coluna pivô
{
	int i, j, l, cont=0;
	float menor;
	
	for(i=0; i<lin-1; i++)
	{
		if(*(m+c*col+i) != 0)
		{
			if(i==0 || cont==0)
			{
				menor = (*(m+(col-1)*col+i)) / (*(m+c*col+i));
				l = i;
				cont++;
			}
			else if((*(m+(col-1)*col+i)) / (*(m+c*col+i)) < menor)
			{
				menor = (*(m+(col-1)*col+i)) / (*(m+c*col+i));
				l = i;
			}
		}
	}
	
	return l;
}

void troca_base(variaveis *v, int lin, int col, int qtd_col) // Coloca e tira variáveis da base
{
	int i;
	
	for(i=0; i<qtd_col; i++)
	{
		if((v+i)->line == lin)
		{
			strcpy((v+i)->cat, "VNB");
			(v+i)->line = -1;
			break;
		}
	}
	
	strcpy((v+col)->cat, "VB");
	(v+col)->line = lin;
	
}

/* Entrada
3 5
1 0 4
0 2 12
3 2 18
*/
