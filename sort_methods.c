#include<stdio.h>
#include<stdlib.h>

void bubblesort(int *v, int tam);
void selectionsort(int *v, int tam);
void insertionsort(int *v, int tam);
void mergesort(int *v, int tam);
void sort(int *v, int ini, int fim, int *aux);
void merge(int *v, int ini, int fim, int *aux);
void quicksort(int *v, int ini, int fim);

int main()
{
	int i, vet[5] = {2, 3, 1, 5, 4};
	
//	bubblesort(vet, 5);
//	selectionsort(vet, 5);
//	insertionsort(vet, 5);
//	mergesort(vet, 5);
	quicksort(vet, 0, 4);
	
	for(i=0; i<5; i++)
		printf("vet[%i]: %i\n", i, *(vet+i));
	
	return 0;
}

void bubblesort(int *v, int tam)
{
	int i, aux, trocou = 0;
	
	do
	{
		trocou = 0;
		for(i=0; i<tam-1; i++)
		{
			if(*(v+i) > *(v+i+1))
			{
				aux = *(v+i);
				*(v+i) = *(v+i+1);
				*(v+i+1) = aux;
				trocou = 1;
			}
		}
	}while(trocou == 1);
}

void selectionsort(int *v, int tam)
{
	int i, j, menor, aux;
	
	for(i=0; i<tam; i++)
	{
		menor = i;
		for(j=i+1; j<tam; j++)
		{
			if(*(v+j) < *(v+menor))
				menor = j;
		}
		aux = *(v+menor);
		*(v+menor) = *(v+i);
		*(v+i) = aux;
	}
}

void insertionsort(int *v, int tam)
{
	int i, j, aux;
	
	for(i=1; i<tam; i++)
	{
		j = i;
		while(j>0 && *(v+j) < *(v+j-1))
		{
			aux = *(v+j);
			*(v+j) = *(v+j-1);
			*(v+j-1) = aux;
			j--;
		}
	}
}

void mergesort(int *v, int tam)
{
	int aux[tam];
	
	sort(v, 0, tam-1, aux);
}

void sort(int *v, int ini, int fim, int *aux)
{
	if(ini >= fim)
		return;
	int m = ini + (fim - ini) / 2;
	sort(v, ini, m, aux);
	sort(v, m+1, fim, aux);
	merge(v, ini, fim, aux);
}

void merge(int *v, int ini, int fim, int *aux)
{
	int m = ini + (fim - ini) / 2;
	int i = ini;
	int j = m+1;
	int k = ini;
	
	while(i <= m && j <= fim)
	{
		if(v[i] < v[j])
			aux[k++] = v[i++];
		else
			aux[k++] = v[j++];
	}
	
	while(i <= m)
		aux[k++] = v[i++];
	while(j <= fim)
		aux[k++] = v[j++];
	for(k=ini; k<=fim; k++)
	{
		v[k] = aux[k];
	}
}

void quicksort(int *v, int ini, int fim)
{
	int i, j, pivo, aux;
	
	pivo = ini + (fim-ini)/2;
//	printf("pivo pos = %i\n", pivo);
	pivo = *(v + pivo);
//	printf("pivo val = %i\n\n", pivo);
	
	i = ini;
	j = fim;
	
	do
	{
		while(*(v+i) < pivo)
			i++;
		while(*(v+j) > pivo)
			j--;
		if(i<=j)
		{
			aux = *(v+i);
			*(v+i) = *(v+j);
			*(v+j) = aux;
			i++;
			j--;
		}
	}while(j>i);
	
	if(ini < j)
		quicksort(v, ini, j);
	if(i < fim)
		quicksort(v, i, fim);
}
