#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void receber(double *v, int g);
double equacao(double v[], double n, int g);
void dicotomia(double vet[], int grau);

int main()
{
	int grau;
	
	printf("Digite o grau da equacao: ");
	scanf("%i", &grau);
	
	double vet[grau+1];
	
	receber(vet, grau);

	dicotomia(vet, grau);
	
	system("PAUSE");
	
	return 0;
}

void receber(double *v, int g)
{
	int i;
	
	for(i=0; i<=g; i++, v++)
	{
		if(i!=g && i!=g-1) printf("Digite o coeficiente de X^%i: ", g-i);	
		else if(i==g-1) printf("Digite o coeficiente de X: ");
		else printf("Digite o coeficiente independente: ");
		
		scanf("%lf", v);
		fflush(stdin);
	}
	printf("\n");
}

double equacao(double v[], double n, int g)
{
	int i;
	double r=0;
	
	for(i=0; i<=g; i++)
	{
		r += pow(n,g-i)*v[i];
	}
	
	return r;
}

void dicotomia(double vet[], int grau)
{
	double a, b, m, fa, fb, fm, e, mod, k;
	int i;
	
	do
	{
		printf("Digite o intervalo\n");
		scanf("%lf %lf", &a, &b);
		//float f_rounded3 = round(f * 1000.0)/1000.0;
		fa = round((equacao(vet, a, grau)*1000.0)/1000.0);
		fb = round((equacao(vet, b, grau)*1000.0)/1000.0);
		
		if(fa*fb>=0)
		{
			system("CLS");
			printf("Esse intervalo nao eh valido, digite um novo intervalo\n");
		}
	}while(fa*fb>=0);
	
	
	printf("Digite o erro\n");
	scanf("%lf", &e);
	
	m = (a+b)/2;
	fm = equacao(vet, m, grau);
	mod = fm;
	k = (log10(b-a)-log10(e))/log10(2);
	if(mod<0) mod *= (-1);
	
	
	printf("\ni\ta\tm\tb\tf(a)\tf(m)\tf(b)\n");
	
	for(i=0; mod>e; i++)
	{
		m = (a+b)/2;
		//fa = equacao(vet, a, grau);
		//fb = equacao(vet, b, grau);
		fa = round((equacao(vet, a, grau)*1000.0)/1000.0);
		fb = round((equacao(vet, b, grau)*1000.0)/1000.0);
		fm = equacao(vet, m, grau);
		printf("%i\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n", i, a, m, b, fa, fm, fb);
		
		if(fm>0) b = m;
		else if(fm<0) a = m;
		
		mod = fm;
	
		if(mod<0) mod *= (-1);
		
		//sleep(1);
	}
	
	printf("\nA raiz eh %.3lf com erro de +- %.3f\n\n", m, fm);
	printf("A quantida de iteracoes eh aproximadamente %i (k = %.2lf)\n\n", i, k);
}
