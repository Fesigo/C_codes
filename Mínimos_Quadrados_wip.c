#include<stdio.h>
#include<stdlib.h>

void receber(float *matriz, int tam);
void mostrar_sist(float *matriz, int tam);
void mostrar_matriz(float *matriz, int tam);
void zerar(float *matriz, int tam);

int main()
{
	int tam;
	
	printf("Numero de equacoes no sistema: ");
	scanf("%i", &tam);
	
	float matriz[tam][tam+1];
	
	receber(*matriz, tam);
	
	mostrar_sist(*matriz, tam);
	mostrar_matriz(*matriz, tam);
	
	system("PAUSE");
	
	return 0;
}

void receber(float *matriz, int tam)
{
	int i, j;
	
	for(i=0; i<tam; i++)
	{
		printf("\n%i^a equacao\n", i+1);
		for(j=0; j<tam+1; j++)
		{
			if(j<tam)
				printf("Coeficiente de x%i: ", j+1);
			else
				printf("Resultado: ");
			scanf("%f", matriz+i*(tam+1)+j);  //scanf("%i",m+i*coluna+j);
		}
	}
}

void mostrar_sist(float *matriz, int tam)  //printf("%i\t",*(m+i*coluna+j));
{
	int i, j;
	
	printf("\nSistema:\n");
	
	for(i=0; i<tam; i++)
	{
		for(j=0; j<tam+1; j++)
		{
			if(j < tam-1)
				printf("%.1fx%i + ", *(matriz+i*(tam+1)+j), j+1);
			else if(j == tam-1)
				printf("%.1fx%i = ", *(matriz+i*(tam+1)+j), j+1);
			else
				printf("%.1f", *(matriz+i*(tam+1)+j), j+1);
		}
		printf("\n");
	}
}

void mostrar_matriz(float *matriz, int tam)  //printf("%i\t",*(m+i*coluna+j));
{
	int i, j;
	
	printf("\nMatriz:\n");
	
	for(i=0; i<tam; i++)
	{
		for(j=0; j<tam+1; j++)
		{
			printf("%.1f\t", *(matriz+i*(tam+1)+j));
		}
		printf("\n");
	}	
}

//wip
/*
	TODO:
	- multiplicadores
	- verificação de onde tem 0s
	- verificação de quantas eqs serão usadas, para calcular m1 e m2
*/
void zerar(float *matriz, int tam)
{
	int i, j;
	float pivo;
	
	for(i=0; i<tam; i++)
	{
		if((*(matriz+i*tam+j)) != 0)
		{
			pivo = *(matriz+i*tam+j);
			break;
		}
	}
}
