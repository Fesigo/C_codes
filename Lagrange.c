//Felipe Siqueira Godoy RA:190337
// Método: Forma de Lagrange
#include<stdio.h>
#include<stdlib.h>

void receber(float *x, float *fx, int q);
void lagrange(float *xi, float *fx, int q);

int main()
{
	int quant;
	
	printf("Quantos valores de X e f(X) serao digitados?\n");
	scanf("%i", &quant);
	
	float x[quant], fx[quant];
	
	receber(x, fx, quant);
	
	lagrange(x, fx, quant);
	
	system("PAUSE");
	
	return 0;
}

void receber(float *x, float *fx, int q)
{
	int i;
	
	// receber os valores de x
	for(i=0; i<q; i++, x++)
	{
		printf("Valor de X%i: ", i);
		scanf("%f", x);
	}
	
	printf("\n");
	
	// receber os valores de f(x)
	for(i=0; i<q; i++, fx++)
	{
		printf("Valor de f(X%i): ", i);
		scanf("%f", fx);
	}
	printf("\n");
	
}

void lagrange(float *xi, float *fx, int q)
{
	int i, j;
	float x, li[q], *l, maior, menor;
	char op;
	
	l = li;
	
	
	// os proximos 3 "for's" sao para printar os pontos em tabela
	for(i=0; i<q; i++)
	{
		printf("\tX(%i)", i);
	}
	printf("\n");
	
	printf("X");
	for(i=0; i<q; i++)
	{
		printf("\t%.2f", *(xi+i));
	}
	
	printf("\n");
	printf("f(X)");
	for(i=0; i<q; i++)
	{
		printf("\t%.2f", *(fx+i));
	}
	printf("\n");
	
	// validação dos intervalos
	for(i=0; i<q; i++)
	{
		if(i==0)
		{
			maior = *xi;
			menor = *xi;
		}
		else if(*(xi+i) > maior) maior = *(xi+i);
		else if(*(xi+i) < menor) menor = *(xi+i); 
	}
	
	// do while para que o usuario possa digitar mais de um valor de x
	do
	{
		
		printf("\n-------- Forma de Lagrange --------\n");
		
		// inicialização do vetor
		for(i=0; i<q; i++, l++)
		{
			*l = 1;
		}
		
		l -= i;
		
		// verificar se o ponto está no intervalo da tabela
		
		do
		{
			printf("\nDigite um valor entre %.2f e %.2f para ser interpolado\n", menor, maior);
			scanf("%f", &x);
			
			if(x < menor || x > maior) printf("O valor digitado nao se encontra no intervalo\n");
		}while(x < menor || x > maior);
		
		printf("\n");
		
		// forma de lagrange
		for(i=0; i<q; i++, l++)
		{
			for(j=0; j<q; j++)
			{
				if(i != j)
				{
					*l *= (x - *(xi+j))/(*(xi+i) - *(xi+j));
				}
			}
			printf("L%i = %.3f\n", i, *l);
		}
		
		l -= i;
		
		float p=0;
		
		// Cálculo do polinômio interpolador
		for(i=0; i<q; i++, l++)
		{
			p += ((*l)**(fx+i));
		}
		l -= i;
		
		printf("\np(%.2f) = %.2f\n", x, p);
		
		printf("\nDeseja interpolar outro valor? (S - Sim / N - Nao)\n");
		fflush(stdin);
		scanf("%c", &op);
		
	}while(op == 's' || op =='S');
}

/*
3
0
1
3
-5
1
25
2
*/
