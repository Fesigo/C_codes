// Felipe Siqueira Godoy  RA:190337
// Guilherme Siqueira  RA:190501
// Integração Numérica – Método dos Trapézios
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void aloca(float **p, int tam);
void recebe_func(float *eq, int g);
void recebe_info(float *i1, float *i2, int *n);
void trapezio(float *eq, int g, int n, float i1, float i2);
float calc_polin(float *eq, float num, int g);
void integral(float *poli, float h, int n);
void mostra(float *eq, int g, int n, float i1, float i2);

int main()
{
	int grau, n;
	float *eq = NULL, i1, i2;
	char op;
	
	do // Repetir o metodo caso o usuário deseje
	{
		do // Receber e validar o grau da equação
		{
			printf("------- Metodo dos Trapezios -------\n\n");
			printf("Digite o grau da equacao (MAX 10): ");
			scanf("%i", &grau);
			
			if(grau>10 || grau<1)
			{
				system("CLS");
				printf("Valor invalido, digite novamente\n");
			}
		}while(grau>10 || grau<1);
		
		aloca(&eq, grau+1);
		recebe_func(eq, grau);
		recebe_info(&i1, &i2, &n);
		trapezio(eq, grau, n, i1, i2);
		
		printf("Deseja repetir o processo?  <S/N>\n");
		fflush(stdin);
		scanf("%c", &op);
		printf("\n");
		
		if(op != 'N' && op != 'n')
			system("CLS");
	}while(op != 'N' && op != 'n');
	
	system("PAUSE");
	
	return 0;
}

// Alocação dinâmica
void aloca(float **p, int tam)
{
	if((*p = (float*)realloc(*p,tam*sizeof(float))) == NULL)
	{
		printf("Espaco insuficiente\n");
		exit(1);
	}
}

// Receber f(X)
void recebe_func(float *eq, int g)
{
	int i;
	
	printf("\n");
	
	for(i=0; i<=g; i++)
	{
		if(i!=g && i!=g-1) printf("Digite o coeficiente de X^%i: ", g-i);	
		else if(i==g-1) printf("Digite o coeficiente de X: ");
		else printf("Digite o coeficiente independente: ");
		
		scanf("%f", eq+i);
		fflush(stdin);
	}
	printf("\n");
}

// Receber o intervalo e o número de trapézios
void recebe_info(float *i1, float *i2, int *n)
{
	float aux;
	
	do
	{
		printf("Digite o intervalo:\n");
		scanf("%f", i1);
		scanf("%f", i2);
		
		if(*i1 == *i2)
			printf("Intervalo invalido, digite novamente\n");
		
	}while(*i1 == *i2);
	
	if(*i1 > *i2)
	{
		aux = *i1;
		*i1 = *i2;
		*i2 = aux;
	}
	
	printf("\nDigite o numero de divisoes\n");
	scanf("%i", n);
	printf("\n");
}

// Função para realizar o método (basicamente isso)
void trapezio(float *eq, int g, int n, float i1, float i2)
{
	int i;
	float h, num, *poli = NULL;
	
	aloca(&poli, n+1);
	
	h = (i2 - i1) / n;
	num = i1;
	
	for(i=0; i<=n; i++)
	{
		*(poli+i) = calc_polin(eq, num, g);
		num+=h;
	}
	
	num = i1;
	
	mostra(eq, g, n, i1, i2);
	
	for(i=0; i<n+1; i++)
	{
		printf("f(%.1f) = %.2f\n", num, *(poli+i));
		num+=h;
	}
	
	integral(poli, h, n);
}

// Função para calcular os polinômios
float calc_polin(float *eq, float num, int g)
{
	int i;
	float r=0;
	
	for(i=0; i<=g; i++)
	{
		r += pow(num,g-i)**(eq+i);
	}
	
	return r;
}

// Cálculo da integral
void integral(float *poli, float h, int n)
{
	int i;
	float itr, soma=0;
	
	for(i=1; i<n; i++)
		soma += *(poli+i);
	
	soma *= 2;
	
	itr = (h/2) * (*poli + *(poli+n) + soma);
	
	printf("\nItr = %.2f\n\n", itr);
	printf("------------------------------------\n\n");
}

// Mostrar todos os dados recebidos
void mostra(float *eq, int g, int n, float i1, float i2)
{
	int i;
	
	system("CLS");

	printf("------------------------------------\n\n");
	printf("f(X) = ");
	
	for(i=0; i<=g; i++)
	{
		if(i<g-1)
			printf("%.2fX^%i + ", *(eq+i), g-i);
		else if(i==g-1)
			printf("%.2fX + ", *(eq+i));
		else
			printf("%.2f", *(eq+i));
	}
	printf("\n\nIntervalo\n[%.2f, %.2f]\n\n", i1, i2);
	printf("Numero de trapezios: %i\n\n", n);
	printf("------------------------------------\n\n");
}

/* Entrada
3
4
10
0
5
-0.5
1.5
4
*/
