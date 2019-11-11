// Felipe Siqueira Godoy  RA: 190337
//Método: Mínimos Quadrados
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void reta();
void parab();
void receber(float *x, float *y,int tam);
void mostrar_xy(float *x, float *y, int tam);
void construir_reta(float *x, float *u0, float *u1, int tam);
void construir_parab(float *x, float *u0, float *u1, float *u2, int tam);
void mostrar(float *u, int tam);
void sist_esc_reta(float mat[2][3], int tam, float *u0, float *u1, float *y);
void sist_esc_parab(float mat[3][4], int tam, float *u0, float *u1, float *u2, float *y);
float prod_esc(float *a1, float *a2, int tam);
void gauss_reta(float mat[2][3], int tam);
void gauss_parab(float mat[3][4], int tam);

int main()
{
	int grau, qtd;
	
	printf("Digite o grau da equacao: ");
	scanf("%i", &grau);
	
	if(grau==1)
		reta();
	else if(grau==2)
		parab();
	
	system("PAUSE");
	
	return 0;
}

// Função "main" da reta
void reta()
{
	int qtd;
	float mat[2][3];
	
	printf("Quantos pontos de X e Y deseja digitar?\n");
	scanf("%i", &qtd);
	
	float x[qtd], y[qtd], u0[qtd], u1[qtd];
	
	receber(x, y, qtd);
	mostrar_xy(x, y, qtd);
	construir_reta(x, u0, u1, qtd);
	sist_esc_reta(mat, qtd, u0, u1, y);
	gauss_reta(mat, qtd);
}

// Função "main" da parábola
void parab()
{
	int qtd;
	float mat[3][4];
	
	printf("Quantos pontos de X e Y deseja digitar?\n");
	scanf("%i", &qtd);
	
	float x[qtd], y[qtd], u0[qtd], u1[qtd], u2[qtd];
	
	receber(x, y, qtd);
	mostrar_xy(x, y, qtd);
	construir_parab(x, u0, u1, u2, qtd);
	sist_esc_parab(mat, qtd, u0, u1, u2, y);
	gauss_parab(mat, qtd);
}

// Recebendo valores de X e Y
void receber(float *x, float *y, int tam)
{
	int i;
	
	printf("\nValores de X\n");
	for(i=0; i<tam; i++, x++)
		scanf("%f", x);
	
	printf("\nValores de Y\n");
	for(i=0; i<tam; i++, y++)
		scanf("%f", y);
}

// Função para mostrar a tabela de X e Y
void mostrar_xy(float *x, float *y, int tam)
{
	int i;
	
	system("CLS");
	
	printf("X:");
	for(i=0; i<tam; i++, x++)
		printf("\t%.0f", *x);
	
	printf("\n");
	
	printf("Y:");
	for(i=0; i<tam; i++, y++)
		printf("\t%.0f", *y);
}

// Função para construir os vetores u0 e 01
void construir_reta(float *x, float *u0, float *u1, int tam)
{
	int i;
	
	for(i=0; i<tam; i++)
	{
		*(u0+i) = pow(*(x+i), 0);
	}
	
	for(i=0; i<tam; i++)
	{
		*(u1+i) = pow(*(x+i), 1);
	}
	
	// Prints dos u's
	printf("\n\nU0: ");
	mostrar(u0, tam);
	printf("U1: ");
	mostrar(u1, tam);
	
}

// Função para construir os vetores u0, u1 e u2
void construir_parab(float *x, float *u0, float *u1, float *u2, int tam)
{
	int i;
	
	for(i=0; i<tam; i++)
	{
		*(u0+i) = pow(*(x+i), 0);
	}
	
	for(i=0; i<tam; i++)
	{
		*(u1+i) = pow(*(x+i), 1);
	}
	
	for(i=0; i<tam; i++)
	{
		*(u2+i) = pow(*(x+i), 2);
	}
	
	// Prints dos u's
	printf("\n\nU0: ");
	mostrar(u0, tam);
	printf("U1: ");
	mostrar(u1, tam);
	printf("U2: ");
	mostrar(u2, tam);
}

// Função para printar os vetores u's
void mostrar(float *u, int tam)
{
	int i;
	
	for(i=0; i<tam; i++, u++)
	{
		printf("\t%.0f", *u);
	}
	printf("\n");
}

// Cálculo do produto escalar para a reta
void sist_esc_reta(float mat[2][3], int tam, float *u0, float *u1, float *y)
{
	int i, j;
		
	for(i=0; i<2; i++)
	{
		for(j=0; j<3; j++)
		{
			if(i==0 && j==0)
				*(*(mat+i)+j) = prod_esc(u0, u0, tam);
			else if(i==0 && j==1)
				*(*(mat+i)+j) = prod_esc(u0, u1, tam);
			else if(i==1 && j==0)
				*(*(mat+i)+j) = prod_esc(u1, u0, tam);
			else if(i==1 && j==1)
				*(*(mat+i)+j) = prod_esc(u1, u1, tam);
			else if(i==0 && j==2)
				*(*(mat+i)+j) = prod_esc(u0, y, tam);
			else if(i==1 && j==2)
				*(*(mat+i)+j) = prod_esc(u1, y, tam);
		}
	}
	
	printf("\nSistema Linear\n");
	
	// Printando o sistema linear
	for(i=0; i<2; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("%.0f    ", *(*(mat+i)+j));
		}
		printf("\n\n");
	}
}

// Cálculo do prduto escalar
float prod_esc(float *a1, float *a2, int tam)
{
	int i, p=0;
	
	for(i=0; i<tam; i++)
		p += (*(a1+i) * *(a2+i));
	
	return p;
}

// Cálculo do produto escalar para a parábola
void sist_esc_parab(float mat[3][4], int tam, float *u0, float *u1, float *u2, float *y)
{
	int i, j;
		
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			if(i==0 && j==0)
				*(*(mat+i)+j) = prod_esc(u0, u0, tam);
			else if(i==0 && j==1)
				*(*(mat+i)+j) = prod_esc(u0, u1, tam);
			else if(i==1 && j==0)
				*(*(mat+i)+j) = prod_esc(u1, u0, tam);
			else if(i==1 && j==1)
				*(*(mat+i)+j) = prod_esc(u1, u1, tam);
			else if(i==0 && j==2)
				*(*(mat+i)+j) = prod_esc(u0, u2, tam);
			else if(i==1 && j==2)
				*(*(mat+i)+j) = prod_esc(u1, u2, tam);
			else if(i==2 && j==0)
				*(*(mat+i)+j) = prod_esc(u2, u0, tam);
			else if(i==2 && j==1)
				*(*(mat+i)+j) = prod_esc(u2, u1, tam);
			else if(i==2 && j==2)
				*(*(mat+i)+j) = prod_esc(u2, u2, tam);
			else if(i==0 && j==3)
				*(*(mat+i)+j) = prod_esc(u0, y, tam);
			else if(i==1 && j==3)
				*(*(mat+i)+j) = prod_esc(u1, y, tam);
			else if(i==2 && j==3)
				*(*(mat+i)+j) = prod_esc(u2, y, tam);
		}
	}
	
	printf("\nSistema Linear\n");
	
	// Printando o sistema linear
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			printf("%.0f    ", *(*(mat+i)+j));
		}
		printf("\n\n");
	}
}

// Função para realizar a eliminação de Gauss
void gauss_reta(float mat[2][3], int tam)
{
	int i, j;
	float m, a0, a1;
	
	printf("---Eliminacao de Gauss---\n\n");
	
	m = *(*(mat+1)) / *(*(mat));
	
	// Escalonando o sistema
	for(i=0; i<3; i++)
	{
		*(*(mat+1)+i) = (-1*m**(*(mat)+i)) + *(*(mat+1)+i);
	}
	
	printf("Sistema Escalonado\n");
	
	//Printando o sistema escalonado
	for(i=0; i<2; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("%.0f    ", *(*(mat+i)+j));
		}
		printf("\n\n");
	}
	
	// Cálculo de a0 e a1
	a1 = *(*(mat+1)+2) / *(*(mat+1)+1);
	a0 = (*(*(mat)+2) - a1**(*(mat)+1)) / *(*(mat));
	
	printf("A reta que melhor aproxima a funcao tabelada eh p(x) = %.3f + %.3fx\n\n", a0, a1);
}

void gauss_parab(float mat[3][4], int tam)
{
	int i, j;
	float m1, m2, a0, a1, a2;
	
	printf("---Eliminacao de Gauss---\n\n");
	
	m1 = *(*(mat+1)) / *(*(mat));
	m2 = *(*(mat+2)) / *(*(mat));
	
	for(i=0; i<4; i++)
	{
		for(j=0; j<2; j++)
		{
			if(j==0)
				*(*(mat+1)+i) = (-1*m1**(*(mat)+i)) + *(*(mat+1)+i);
			else
				*(*(mat+2)+i) = (-1*m2**(*(mat)+i)) + *(*(mat+2)+i);
		}
	}
	
	printf("Sistema Escalonado - Primeiro escalonamento\n");
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			printf("%.3f    ", *(*(mat+i)+j));
		}
		printf("\n\n");
	}
	
	m2 = *(*(mat+2)+1) / *(*(mat+1)+1);
	
	for(i=0; i<4; i++)
	{
		*(*(mat+2)+i) = (-1*m2**(*(mat+1)+i)) + *(*(mat+2)+i);
	}
	
	printf("Sistema Escalonado - Segundo escalonamento\n");
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<4; j++)
		{
			printf("%.3f    ", *(*(mat+i)+j));
		}
		printf("\n\n");
	}
	
	a2 = *(*(mat+2)+3) / *(*(mat+2)+2);
	a1 = (*(*(mat+1)+3) - a2**(*(mat+1)+2)) / *(*(mat+1)+1);
	a0 = (*(*(mat)+3) - a2**(*(mat)+2) - a1**(*(mat)+1)) / *(*(mat));
	
	printf("A parabola que melhor aproxima a funcao tabelada eh p(x) = %.3f + %.3fx + %.3fx^2\n\n", a0, a1, a2);
}

/* INPUT 1°grau
1
5
0
1
2
3
4
0
1
1
4
4
*/

/* INPUT 2°grau
2
5
-3
-1
1
2
3
-1
0
1
1
-1
*/

/* INPUT 2°grau - 2
2
4
-1
0
1
2
0
-1
0
7
*/
