//Felipe Siqueira Godoy RA: 190337
// Projeto Imobiliária
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct endereco{
	char logradouro[80];
	char bairro[20];
	char CEP[10];
	char cidade[20];
	char estado[20];
	char fone[15];
	char cel[15];
	char email[30];
}endereco;

typedef struct info_casa{
	int num_casa;
	char status_casa;
}info_casa;

typedef struct prop{
	int reg_prop;
	char nome[80];
	char CPF[15];
	endereco end_prop;
	int qtd_casa;
	info_casa casa[5];
}prop;

typedef struct adress{
	char logradouro[80];
	char bairro[20];
	char CEP[10];
	char cidade[20];
}adress;

typedef struct info_loc{
	char sigla;
	int reg_loc;
}info_loc;

typedef union dados{
	char sigla;
	info_loc loc;
}dados;

typedef struct imovel{
	int reg_imov;
	adress end_imov;
	float area;
	int quartos;
	float valor;
	dados status;
}imovel;

typedef struct locatario{
	int reg_loc;
	char nome[80];
	char CPF[15];
	endereco end_loc;
	int reg_imov;
	int dia_venc;
	char inicio[15];
	char termino[15];
}locatario;

void aloca_prop(prop **p, int tam);
void aloca_imovel(imovel **im, int tam);
void aloca_loc(locatario **l, int tam);
void aloca_char(char **p, int tam);
void maiuscula(char *p);
int verifica_prop(); //Verifica a quantidade de proprietários registrados
int verifica_im(); //Verifica a quantidade de imóveis cadastrados
int verifica_loc(); //Verifica a quantidade de locatários cadastrados

void cadastro_prop(prop *p, int qreg); //Cadastro de proprietários
void grava_prop(prop *p); //Grava o cadastro dos proprietários no arquivo
void mostra_prop(prop *p, int qreg);
void mostra_prop_parcial(prop *p, int qreg);
int cadastro_imovel(imovel *im, int qim, prop *p, int qreg); //Cadastro de imóveis
void grava_im(imovel *im); //Grava o cadastro dos imóveis no arquivo
void mostra_im(imovel *im, int qreg, int op);
void mostra_im_parcial(imovel *im, int qreg);
int cadastro_loc(locatario *l, int qloc, prop *p, int qprop, imovel *im, int qim); //Cadastro de locatários
void grava_loc(locatario *l); //Grava o cadastro dos locatários no arquivo
void mostra_loc(locatario *l, int qloc);
void mostra_loc_parcial(locatario *l, int qloc, int nreg);

void alteracao(prop *p, int qprop, imovel *im, int qim, locatario *l, int qloc); //Alterações de cadastros
void altera_prop(prop *p, int qprop, int nreg, int op); //Alterações no arquivo dos proprietários
void altera_im(imovel *im, int qim, int pos, locatario *l, int op); //Alterações no aquivo dos imóveis
void altera_loc(locatario *l, int qloc, int pos, int op, int qprop, int qim); //Alterações no arquivo dos locatários

int busca_prop(prop *p, int qprop); //Faz a busca do proprietário que passará pela alteração
int busca_im(imovel *im, int qim, int nreg); //Faz a busca do imóvel que passará pela alteração
int busca_loc(locatario *l, int qloc); //Faz a busca do locatário que passará pela alteração

void termino_contrato(prop *p, int qprop, imovel *im, int qim, locatario *l, int qloc); //Realiza o término do contrato
void relatorio(prop *p, int qprop, imovel *im, int qim, locatario *l, int qloc); //Relatório
int verifica_arroba(locatario *l, int qloc); //Retorna a posição de um locatário com @ no CPF
int conta_arroba(locatario *l, int qloc); //Função para verificar se há locatários cadastrados sem @ no CPF

int main()
{
	prop *p=NULL;
	imovel *im=NULL;
	locatario *l=NULL;
	int op, qprop, qim, qloc, verif=-1;
	
	aloca_prop(&p, 1);
	aloca_imovel(&im, 1);
	aloca_loc(&l, 1);
	qprop = verifica_prop(); //Verifica a quantidade de proprietários cadastrados
	qim = verifica_im(); //Verifica a quantidade de imóveis cadastrados
	qloc = verifica_loc(); //Verifica a quantidade de locatários cadastrados
	
	do
	{
		system("cls");
		
		//Menu
		printf("[1] Cadastro de proprietarios");
		printf("\n[2] Consulta de proprietarios");
		printf("\n[3] Consulta de proprietarios parcial");
		printf("\n[4] Cadastro de imoveis");
		printf("\n[5] Consulta de imoveis");
		printf("\n[6] Consulta de imoveis parcial");
		printf("\n[7] Aluguel");
		printf("\n[8] Consulta de locatarios");
		printf("\n[9] Termino de contrato");
		printf("\n[10] Relatorio");
		printf("\n[11] Alteracao de cadastros");
		printf("\n[12] Fim\n\n");
		scanf("%i", &op);
		
		if(op==1)
		{
			cadastro_prop(p, qprop+1); //cadastra os proprietarios
			qprop++;
		}
		else if(op==2)
			mostra_prop(p, qprop); //mostra todos os proprietários
		else if(op==3)
			mostra_prop_parcial(p, qprop); //mostra o proprietário de acordo com o CPF digitado
		else if(op==4)
		{
			verif= -1; //variável para verificar se foi possível realizar o cadastro
			verif = cadastro_imovel(im, qim+1, p, qprop); //Cadastra os imoveis
			
			if(verif != -1)
				qim++;
		}
		else if(op==5)
			mostra_im(im, qim, 0); //mostra todos os imóveis livres ou alugados, depende da escolha do usuário
		else if(op==6)
			mostra_im_parcial(im, qim); //mostra todos os imóveis que correspondam aos requisitos de área útil, n° de quartos ou bairro digitado pelo usuário
		else if(op==7)
		{
			verif = verifica_arroba(l, qloc);
			
			if(verif==-1)
			{
				verif = cadastro_loc(l, qloc+1, p, qprop, im, qim); //Cadastra os locatários
				
				if(verif != -1)
					qloc++;
			}
			else
				altera_loc(l, qloc, verif, 2, qprop, qim);
		}
		else if(op==8)
			mostra_loc(l, qloc); //mostra todos os locatários
		else if(op==9)
			termino_contrato(p, qprop, im, qim, l, qloc);
		else if(op==10)
			relatorio(p, qprop, im, qim, l, qloc);
		else if(op==11)
			alteracao(p, qprop, im, qim, l, qloc);
		else if(op>12 || op<1)
			printf("\nDigite uma opcao valida\n");
		
		system("pause");
		
	}while(op!=12);
	
	return 0;
}

void aloca_prop(prop **p, int tam)
{
	if((*p=(prop*)realloc(*p, tam*sizeof(prop)))==NULL)
	{
		printf("\nErro de alocacao\n");
		exit(1);
	}
}

void aloca_imovel(imovel **im, int tam)
{
	if((*im=(imovel*)realloc(*im, tam*sizeof(imovel)))==NULL)
	{
		printf("\nErro na alocacao\n");
		exit(1);
	}
}

void aloca_loc(locatario **l, int tam)
{
	if((*l=(locatario*)realloc(*l, tam*sizeof(locatario)))==NULL)
	{
		printf("\nErro na alocacao\n");
		exit(1);
	}
}

void aloca_char(char **p, int tam)
{
	if((*p=(char*)realloc(*p, tam*sizeof(char)))==NULL)
	{
		printf("\nErro de alocacao\n");
		exit(1);
	}
}

void maiuscula(char *p)
{
	int i;
	
	for(i=0; i<strlen(p); i++)
	{
		if(*(p+i) >= 'a' && *(p+i) <= 'z')
			*(p+i) -= 32;
	}
}

int verifica_prop() //Verifica a quantidade de proprietários registrados
{
	long int cont=0;
	FILE *fptr=NULL;
	
	if((fptr=(fopen("proprietario.bin", "rb")))==NULL)
		return cont;
	else
	{
		fseek(fptr, 0, 2);
		cont = ftell(fptr)/sizeof(prop);
		return cont;
	}
}

int verifica_im() //Verifica a quantidade de imóveis cadastrados
{
	long int cont=0;
	FILE *fptr=NULL;
	
	if((fptr=(fopen("imovel.bin", "rb")))==NULL)
		return cont;
	else
	{
		fseek(fptr, 0, 2);
		cont = ftell(fptr)/sizeof(imovel);
		return cont;
	}
}

int verifica_loc() //Verifica a quantidade de locatários cadastrados
{
	long int cont=0;
	FILE *fptr=NULL;
	
	if((fptr=(fopen("locatario.bin", "rb")))==NULL)
		return cont;
	else
	{
		fseek(fptr, 0, 2);
		cont = ftell(fptr)/sizeof(locatario);
		return cont;
	}
}

void cadastro_prop(prop *p, int qreg) //Cadastro de proprietários
{
	p->reg_prop = qreg;
	printf("\nN de registro: %i", p->reg_prop);
	
	printf("\nNome: ");
	fflush(stdin);
	gets(p->nome);
	
	printf("CPF: ");
	fflush(stdin);
	gets(p->CPF);
	
	printf("Logradouro: ");
	fflush(stdin);
	gets(p->end_prop.logradouro);
	
	printf("Bairro: ");
	fflush(stdin);
	gets(p->end_prop.bairro);
	
	printf("CEP: ");
	fflush(stdin);
	gets(p->end_prop.CEP);
	
	printf("Cidade: ");
	fflush(stdin);
	gets(p->end_prop.cidade);
	
	printf("Estado: ");
	fflush(stdin);
	gets(p->end_prop.estado);
	
	printf("Fone: ");
	fflush(stdin);
	gets(p->end_prop.fone);
	
	printf("Cel: ");
	fflush(stdin);
	gets(p->end_prop.cel);
	
	printf("email: ");
	fflush(stdin);
	gets(p->end_prop.email);
	
	p->qtd_casa = 0;
	
	(p->casa)->num_casa = -1;
	(p->casa)->status_casa = 'L';
	
	grava_prop(p);
}

void grava_prop(prop *p) //Grava o cadastro dos proprietários no arquivo
{
	FILE *fptr=NULL;
	
	//Rotina para gravar os proprietários
	if((fptr=(fopen("proprietario.bin", "ab")))==NULL)
		printf("\nErro ao abrir o arquivo");
	else
		fwrite(p, sizeof(prop), 1, fptr);
	
	fclose(fptr);
}

void mostra_prop(prop *p, int qreg)
{
	int i, j;
	FILE *fptr=NULL;
	
	system("cls");
	
	//Rotina para ler todos os proprietários
	if((fptr=(fopen("proprietario.bin", "rb")))==NULL)
		printf("\nNao ha proprietarios cadastrados\n");
	else
	{
		for(i=0; i<qreg; i++)
		{
			fseek(fptr, i*sizeof(prop), 0);
			fread(p, sizeof(prop), 1, fptr);
			printf("PROPRIETARIO\nN de registro: %i\nNome: %s\nCPF: %s\n", p->reg_prop, p->nome, p->CPF);
			printf("\nENDERECO\nLogradouro: %s\nBairro: %s\nCEP: %s\n", p->end_prop.logradouro, p->end_prop.bairro, p->end_prop.CEP);
			printf("Cidade: %s\nEstado: %s\nFone: %s\nCel: %s\nemail: %s\n", p->end_prop.cidade, p->end_prop.estado, p->end_prop.fone, p->end_prop.cel, p->end_prop.email);
			printf("\nQuantidade de imoveis: %i\n", p->qtd_casa);
			
			if(p->qtd_casa > 0)
			{
				for(j=0; j<(p->qtd_casa); j++)
					printf("\nCasa - %i\nN: %i\nStatus: %c\n", j+1, (p->casa + j)->num_casa, (p->casa + j)->status_casa); //(p->casa+i)->status_casa
			}
			printf("\n---------------------------------------\n\n");
		}
		fclose(fptr);
	}
}

void mostra_prop_parcial(prop *p, int qreg)
{
	FILE *fptr=NULL;
	int i, j, vdd=0;
	char aux[15];
	
	system("cls");
	
	//Rotina para ler o proprietario com determinado CPF
	if((fptr=(fopen("proprietario.bin", "rb")))==NULL)
		printf("\nNao ha proprietarios cadastrados\n");
	else
	{
		printf("Digite o CPF do proprietario: ");
		fflush(stdin);
		gets(aux);
		
		for(i=0; i<qreg; i++)
		{
			fseek(fptr, i*sizeof(prop), 0);
			fread(p, sizeof(prop), 1, fptr);
			
			if(strcmp(aux, p->CPF)==0)
			{
				vdd++;
				
				printf("\nPROPRIETARIO\nN de registro: %i\nNome: %s\nCPF: %s\n", p->reg_prop, p->nome, p->CPF);
				printf("\nENDERECO\nLogradouro: %s\nBairro: %s\nCEP: %s\n", p->end_prop.logradouro, p->end_prop.bairro, p->end_prop.CEP);
				printf("Cidade: %s\nEstado: %s\nFone: %s\nCel: %s\nemail: %s\n", p->end_prop.cidade, p->end_prop.estado, p->end_prop.fone, p->end_prop.cel, p->end_prop.email);
				printf("\nQuantidade de imoveis: %i\n", p->qtd_casa);
				
				if(p->qtd_casa > 0)
				{
					for(j=0; j<(p->qtd_casa); j++)
						printf("\nCasa - %i\nN: %i\nStatus: %c\n", j+1, (p->casa + j)->num_casa, (p->casa + j)->status_casa); //(p->casa+i)->status_casa
				}
				break;
			}
		}
		fclose(fptr);
		
		if(vdd==0)
			printf("\nNao ha nenhum proprietario cadastrado com esse CPF\n");
	}
}

int cadastro_imovel(imovel *im, int qim, prop *p, int qreg) //Cadastro de imóveis
{
	FILE *fptr=NULL, *fptr2=NULL;
	int i, vdd=0, q, numreg;
	
	system("cls");
	
	if(qreg == 0)
	{
		printf("\nNao ha proprietarios cadastrados\n");
		return -1;
	}
	
	//Rotina para ler o proprietario com determinado número de registro
	if((fptr=(fopen("proprietario.bin", "rb")))==NULL)
		printf("\nNao ha proprietarios cadastrados\n");
	else
	{
		printf("\nDigite o numero de registro do proprietario do imovel que sera cadastrado: ");
		fflush(stdin);
		scanf("%i", &numreg);
		
		for(i=0; i<qreg; i++)
		{
			fseek(fptr, i*sizeof(prop), 0);
			fread(p, sizeof(prop), 1, fptr);
			
			if(numreg == p->reg_prop)
			{
				if(p->qtd_casa == 5)
				{
					printf("\nEsse proprietario ja possui o maximo de imoveis cadastrados permitido (5)\n");
					return -1;
				}
				
				vdd++;
				
				im->reg_imov = qim;
				printf("\nN de registro: %i", im->reg_imov);
			
				printf("\nLogradouro: ");
				fflush(stdin);
				gets(im->end_imov.logradouro);
				maiuscula(im->end_imov.logradouro);
				
				printf("Bairro: ");
				fflush(stdin);
				gets(im->end_imov.bairro);
				maiuscula(im->end_imov.bairro);
				
				printf("CEP: ");
				fflush(stdin);
				gets(im->end_imov.CEP);
				
				printf("Cidade: ");
				fflush(stdin);
				gets(im->end_imov.cidade);
				maiuscula(im->end_imov.cidade);
				
				printf("Area util (em m^2): ");
				fflush(stdin);
				scanf("%f", &(im->area));
				
				printf("Quantidade de quartos: ");
				scanf("%i", &(im->quartos));
				
				printf("Valor do aluguel: ");
				scanf("%f", &(im->valor));
				
				im->status.sigla = 'L';
				
				q = p->qtd_casa;
				
				if((fptr2=(fopen("proprietario.bin", "rb+")))==NULL) //Alteração do arquivo do proprietário, gravando as informações sobre seu imóvel
					printf("\nErro na alteracao\n");
				else
				{
					fseek(fptr2,i*sizeof(prop),SEEK_SET);
					fread(p,sizeof(prop),1,fptr2);
					fseek(fptr2,i*sizeof(prop),SEEK_SET);
					
					(p->casa + q)->num_casa = im->reg_imov;
					(p->casa + q)->status_casa = 'L';
					p->qtd_casa++;
					
					fwrite(p, sizeof(prop), 1, fptr2);
				}
				fclose(fptr2);
				
				break;
			}
		}
		fclose(fptr);
		
		if(vdd==0)
		{
			printf("\nNao ha nenhum proprietario com esse numero de registro\n");
			return -1;
		}

	}
	
	grava_im(im);
	return 0;
}

void grava_im(imovel *im) //Grava o cadastro dos imóveis no arquivo
{
	FILE *fptr=NULL;
	
	//Rotina para gravar os imóveis
	if((fptr=(fopen("imovel.bin", "ab")))==NULL)
		printf("\nErro ao abrir o arquivo");
	else
		fwrite(im, sizeof(imovel), 1, fptr);
	
	fclose(fptr);
}

void mostra_im(imovel *im, int qreg, int op)
{
	FILE *fptr=NULL;
	int i, vdd=0;
	char aux;
	
	system("cls");
	
	//Rotina para ler os imóveis livres ou alugados, dependendo da escolha do usuário
	if((fptr=(fopen("imovel.bin", "rb")))==NULL)
		printf("\nNao ha imoveis cadastrados\n");
	else
	{
		if(op==0)
		{
			do
			{
				printf("[1] Livre\n[2] Alugado\n");
				scanf("%i", &op);
				
				if(op<1 || op>2)
				{
					printf("\nDigite uma opcao valida\n");
					system("pause");
					system("cls");
				}
			}while(op<1 || op>2);
		}
	 	else
	 	{
	 		op = 1;
	 		printf("\nImoveis disponiveis para aluguel:\n");
		}
	 	
		if(op==1)
			aux = 'L';
		else if(op==2)
			aux = 'A';
		
		
		for(i=0; i<qreg; i++)
		{
			fseek(fptr, i*sizeof(imovel), 0);
			fread(im, sizeof(imovel), 1, fptr);
			
			if(im->status.sigla == aux)
			{
				vdd++;
				
				printf("\nN de registro: %i\nLogradouro: %s\nBairro: %s\n", im->reg_imov, im->end_imov.logradouro, im->end_imov.bairro);
				printf("CEP: %s\nCidade: %s\nArea util: %.2fm^2\n", im->end_imov.CEP, im->end_imov.cidade, im->area);
				printf("Quantidade de quartos: %i\n", im->quartos);
				
				if(aux == 'A')
					printf("Status: A - %i\n", im->status.loc.reg_loc);
				else
					printf("Status: L\n");
			}
		}
		fclose(fptr);
		
		if(vdd==0)
			printf("Na ha imoveis com esse status\n");
	}
}

void mostra_im_parcial(imovel *im, int qreg)
{
	FILE *fptr=NULL;
	int i, op, vdd=0;
	
	system("cls");
	
	//Rotina para ler os imóveis que possuem o requisito escolhido pelo usuário
	if((fptr=(fopen("imovel.bin", "rb")))==NULL)
		printf("\nNao ha imoveis cadastrados\n");
	else
	{
		do
		{
			printf("Escolha o criterio de busca:\n[1] Area util\n[2] Quantidade de quartos\n[3] Bairro\n\n");
			scanf("%i", &op);
			
			if(op<1 || op>3)
			{
				printf("\nDigite uma opcao valida\n");
				system("pause");
				system("cls");
			}
		}while(op<1 || op>3);
		
		if(op==1)
		{
			float a;
			printf("Digite a area util desejada: ");
			scanf("%f", &a);
			
			for(i=0; i<qreg; i++)
			{
				fseek(fptr, i*sizeof(imovel), 0);
				fread(im, sizeof(imovel), 1, fptr);
				
				if(im->status.sigla == 'L' && im->area == a) //Busca por área útil
				{
					vdd++;
					
					printf("\nN de registro: %i\nLogradouro: %s\nBairro: %s\n", im->reg_imov, im->end_imov.logradouro, im->end_imov.bairro);
					printf("CEP: %s\nCidade: %s\nArea util: %.2fm^2\n", im->end_imov.CEP, im->end_imov.cidade, im->area);
					printf("Quantidade de quartos: %i\nValor do aluguel: R$%.2f\n", im->quartos, im->valor);
				}
			}
			fclose(fptr);
		}
		else if(op==2)
		{
			int q;
			printf("Digite a quantidade de quartos desejada: ");
			scanf("%i", &q);
			
			for(i=0; i<qreg; i++)
			{
				fseek(fptr, i*sizeof(imovel), 0);
				fread(im, sizeof(imovel), 1, fptr);
				
				if(im->status.sigla == 'L' && im->quartos == q) //Busca por quantidade de quartos
				{
					vdd++;
					
					printf("\nN de registro: %i\nLogradouro: %s\nBairro: %s\n", im->reg_imov, im->end_imov.logradouro, im->end_imov.bairro);
					printf("CEP: %s\nCidade: %s\nArea util: %.2fm^2\n", im->end_imov.CEP, im->end_imov.cidade, im->area);
					printf("Quantidade de quartos: %i\nValor do aluguel: R$%.2f\n", im->quartos, im->valor);
				}
			}
			fclose(fptr);
		}
		else if(op==3)
		{
			char b[20];
			printf("Digite o bairro desejado: ");
			fflush(stdin);
			gets(b);
			maiuscula(b);
			
			for(i=0; i<qreg; i++)
			{
				fseek(fptr, i*sizeof(imovel), 0);
				fread(im, sizeof(imovel), 1, fptr);
				
				if(im->status.sigla == 'L' && strcmp(b, im->end_imov.bairro)==0) //Busca por bairro
				{
					vdd++;
					
					printf("\nN de registro: %i\nLogradouro: %s\nBairro: %s\n", im->reg_imov, im->end_imov.logradouro, im->end_imov.bairro);
					printf("CEP: %s\nCidade: %s\nArea util: %.2fm^2\n", im->end_imov.CEP, im->end_imov.cidade, im->area);
					printf("Quantidade de quartos: %i\nValor do aluguel: R$%.2f\n", im->quartos, im->valor);
				}
			}
			fclose(fptr);
		}
		if(vdd==0)
			printf("Nao ha imoveis com os requisitos digitados\n");
	}
}

int cadastro_loc(locatario *l, int qloc, prop *p, int qprop, imovel *im, int qim) //Cadastro de locatários
{
	FILE *fptr=NULL;
	int nreg, i, dia, mes, ano, pos, vdd=0, contlivre=0;
	
	if(qim == 0)
	{
		system("cls");
		printf("\nNao ha imoveis cadastrados para aluguel\n");
		return -1;
	}
	
	mostra_im(im, qim, 1);
	
	//Rotina para ler o imóvel com determinado numero de registro
	if((fptr=(fopen("imovel.bin", "rb")))==NULL)
		printf("\nNao ha imoveis cadastrados\n");
	else
	{
		for(i=0; i<qim; i++) //verificando se ha imoveis livres para aluguel
		{
			fseek(fptr, i*sizeof(imovel), 0);
			fread(im, sizeof(imovel), 1, fptr);
			
			if(im->status.sigla == 'L')
				contlivre++;
		}
		
		if(contlivre==0)
		{
			system("cls");
			printf("\nNao ha imoveis livres para aluguel\n");
			return -1;
		}
		
		
		printf("\nDigite o numero de registro do imovel desejado: ");
		fflush(stdin);
		scanf("%i", &nreg);
		
		if(nreg > qim)
		{
			printf("\nNao ha nenhum imovel com esse numero de registro\n");
			return -1;
		}
		
		for(i=0; i<qim; i++)
		{
			fseek(fptr, i*sizeof(imovel), 0);
			fread(im, sizeof(imovel), 1, fptr);
			
			if(nreg == im->reg_imov)
			{
				if(im->status.sigla == 'A')
				{
					printf("\nESSE IMOVEL JA SE ENCONTRA ALUGADO\n");
					mostra_loc_parcial(l, qloc, nreg);
					vdd = 0;
					break;
				}
				
				l->reg_imov = im->reg_imov;
				
				l->reg_loc = qloc;
				printf("\nN de registro: %i", l->reg_loc);
				
				printf("\nNome: ");
				fflush(stdin);
				gets(l->nome);
				
				printf("CPF: ");
				fflush(stdin);
				gets(l->CPF);
				
				printf("Logradouro: ");
				fflush(stdin);
				gets(l->end_loc.logradouro);
				
				printf("Bairro: ");
				fflush(stdin);
				gets(l->end_loc.bairro);
				
				printf("CEP: ");
				fflush(stdin);
				gets(l->end_loc.CEP);
				
				printf("Cidade: ");
				fflush(stdin);
				gets(l->end_loc.cidade);
				
				printf("Estado: ");
				fflush(stdin);
				gets(l->end_loc.estado);
				
				printf("Fone: ");
				fflush(stdin);
				gets(l->end_loc.fone);
				
				printf("Cel: ");
				fflush(stdin);
				gets(l->end_loc.cel);
				
				printf("email: ");
				fflush(stdin);
				gets(l->end_loc.email);
				
				printf("\nN de registro do imovel: %i\n", l->reg_imov);
				
				printf("Digite o dia de vencimento do aluguel: ");
				fflush(stdin);
				scanf("%i", &(l->dia_venc));
				
				printf("Data de inicio do contrato (D/M/A):\n");
				fflush(stdin);
				
				scanf("%i/%i/%i", &dia, &mes, &ano);
				fflush(stdin);
				
				sprintf(l->inicio, "%i/%i/%i", dia, mes, ano);
				sprintf(l->termino, "%i/%i/%i", dia, mes, ano+1);
				
				printf("Data de termino do contrato:\n%s\n", l->termino);
				
				altera_prop(p, qprop, nreg, 0);
				pos = busca_im(im, qim, nreg);
				altera_im(im, qim, pos, l, 0);
				grava_loc(l);
				
				vdd = 1;
			}
		}
		fclose(fptr);
		
		if(vdd==0)
			return -1;
	}
}

void grava_loc(locatario *l) //Grava o cadastro dos locatários no arquivo
{
	FILE *fptr=NULL;
	
	//Rotina para gravar os locatários
	if((fptr=(fopen("locatario.bin", "ab")))==NULL)
		printf("\nErro ao abrir o arquivo");
	else
		fwrite(l, sizeof(locatario), 1, fptr);
	
	fclose(fptr);
}

void mostra_loc(locatario *l, int qloc)
{
	FILE *fptr=NULL;
	int i, cont=0;
	
	system("cls");
	
	//Rotina para ler os locatários
	if((fptr=(fopen("locatario.bin", "rb")))==NULL)
		printf("\nNao ha locatarios cadastrados\n");
	else
	{
		for(i=0; i<qloc; i++)
		{
			fseek(fptr, i*sizeof(locatario), 0);
			fread(l, sizeof(locatario), 1, fptr);
			
			if(strcmp(l->CPF, "@")!=0)
			{
				printf("LOCATARIO\nN de registro: %i\nNome: %s\nCPF: %s\n", l->reg_loc, l->nome, l->CPF);
				printf("\nENDERECO\nLogradouro: %s\nBairro: %s\nCEP: %s\n", l->end_loc.logradouro, l->end_loc.bairro, l->end_loc.CEP);
				printf("Cidade: %s\nEstado: %s\nFone: %s\nCel: %s\nemail: %s\n", l->end_loc.cidade, l->end_loc.estado, l->end_loc.fone, l->end_loc.cel, l->end_loc.email);
				printf("\nALUGUEL\nReg do imovel: %i\nDia de vencimento do aluguel: %i\nInicio: %s\nTermino: %s\n", l->reg_imov, l->dia_venc, l->inicio, l->termino);
				printf("\n---------------------------------------\n\n");
				
				cont++;
			}
		}
		fclose(fptr);
		
		if(cont==0)
		{
			printf("\nNao ha locatarios cadastrados\n");
		}
	}
}

void mostra_loc_parcial(locatario *l, int qloc, int nreg)
{
	FILE *fptr=NULL;
	int i;
	
	//Rotina para ler o locatário de determinado imóvel
	if((fptr=(fopen("locatario.bin", "rb")))==NULL)
		printf("\nNao ha locatarios cadastrados\n");
	else
	{
		for(i=0; i<qloc; i++)
		{
			fseek(fptr, i*sizeof(locatario), 0);
			fread(l, sizeof(locatario), 1, fptr);
			
			if(nreg == l->reg_imov)
			{
				printf("LOCATARIO\nN de registro: %i\nNome: %s\nCPF: %s\n", l->reg_loc, l->nome, l->CPF);
				printf("\nENDERECO\nLogradouro: %s\nBairro: %s\nCEP: %s\n", l->end_loc.logradouro, l->end_loc.bairro, l->end_loc.CEP);
				printf("Cidade: %s\nEstado: %s\nFone: %s\nCel: %s\nemail: %s\n", l->end_loc.cidade, l->end_loc.estado, l->end_loc.fone, l->end_loc.cel, l->end_loc.email);
				printf("\nALUGUEL\nReg do imovel: %i\nDia de vencimento do aluguel: %i\nInicio: %s\nTermino: %s\n", l->reg_imov, l->dia_venc, l->inicio, l->termino);
				
				break;
			}
		}
		fclose(fptr);
	}
}

void alteracao(prop *p, int qprop, imovel *im, int qim, locatario *l, int qloc) //Alteração de cadastros
{
	FILE *fptr=NULL;
	int op, pos, nreg, arroba;
	
	if(qprop==0)
	{
		system("cls");
		printf("\nNao ha cadastros para serem alterados\n");
		return;
	}
	
	printf("\nO que deseja alterar?\n[1] Proprietario\n[2] Imovel\n[3] Locatario\n[4] Voltar\n");
	scanf("%i", &op);
	
	if(op==1) //Alteração do proprietário
	{
		pos = busca_prop(p, qprop);
		if(pos!=-1)
			altera_prop(p, qprop, pos, 2);
	}
	else if(op==2) //Alteração do imóvel
	{
		if(qim==0)
		{
			system("cls");
			printf("\nNao ha imoveis cadastrados para serem alterados\n");
			return;
		}
		printf("\nDigite o numero de registro do imovel: ");
		scanf("%i", &nreg);
		
		pos = busca_im(im, qim, nreg);
		if(pos!=-1)
			altera_im(im, qim, pos, l, 2);
	}
	else if(op==3) //Alteração do locatário
	{
		if(qloc==0 || conta_arroba(l, qloc)==qloc)
		{
			system("cls");
			printf("\nNao ha locatarios cadastrados para serem alterados\n");
			return;
		}
		
		pos = busca_loc(l, qloc);
		if(pos!=-1)
		altera_loc(l, qloc, pos, 1, qprop, qim);
	}
	else
		return;
}

void altera_prop(prop *p, int qprop, int nreg, int op) //Alterações no arquivo dos proprietários
{
	FILE *fptr=NULL;
	int i, j, posi, posj;
	
	if(op==0 || op==1)
	{
		//Leitura para encontrar o proprietário de determinado imóvel
		if((fptr=(fopen("proprietario.bin", "rb")))==NULL)
			printf("\nErro na busca\n");
		else
		{
			for(i=0; i<qprop; i++)
			{
				fseek(fptr,i*sizeof(prop),SEEK_SET);
				fread(p,sizeof(prop),1,fptr);
				
				for(j=0; j<(p->qtd_casa); j++)
				{
					if(nreg == (p->casa+j)->num_casa)
					{
						posi = i;
						posj = j;
						i = qprop;
						j = (p->qtd_casa);
					}
				}
						
			}
			fclose(fptr);
		}
		
		if((fptr=(fopen("proprietario.bin", "rb+")))==NULL) //Alteração do arquivo do proprietário
			printf("\nErro na alteracao\n");
		else
		{
			fseek(fptr,posi*sizeof(prop),SEEK_SET);
			fread(p,sizeof(prop),1,fptr);
			fseek(fptr,posi*sizeof(prop),SEEK_SET);
			
			if(op==0)
				(p->casa + posj)->status_casa = 'A';
			else if(op==1)
				(p->casa + posj)->status_casa = 'L';
			
			fwrite(p, sizeof(prop), 1, fptr);
		}
		fclose(fptr);
	}
	else if(op==2)
	{
		if((fptr=(fopen("proprietario.bin", "rb+")))==NULL) //Alteração do arquivo do proprietário
			printf("\nErro na alteracao\n");
		else
		{
			fseek(fptr, nreg*sizeof(prop), SEEK_SET);
			fread(p, sizeof(prop), 1, fptr);
			fseek(fptr, nreg*sizeof(prop), SEEK_SET);
			
			do
			{
				system("cls");
				printf("\nO que deseja alterar?\n[1] Logradouro\n[2] Bairro\n[3] CEP\n[4] Cidade\n[5] Estado\n[6] Fone\n[7] Cel\n[8] Email\n[9] Voltar\n");
				scanf("%i", &op);
				
				if(op<1 || op>9)
				{
					printf("\nDigite uma opcao valida\n");
					system("pause");
				}
			}while(op<1 || op>9);
			
			if(op==1)
			{
				printf("\nNovo logradouro: ");
				fflush(stdin);
				gets(p->end_prop.logradouro);
			}
			else if(op==2)
			{
				printf("\nNovo bairro: ");
				fflush(stdin);
				gets(p->end_prop.bairro);
			}
			else if(op==3)
			{
				printf("\nNovo CEP: ");
				fflush(stdin);
				gets(p->end_prop.CEP);
			}
			else if(op==4)
			{
				printf("\nNova cidade: ");
				fflush(stdin);
				gets(p->end_prop.cidade);
			}
			else if(op==5)
			{
				printf("\nNovo estado: ");
				fflush(stdin);
				gets(p->end_prop.estado);
			}
			else if(op==6)
			{
				printf("\nNovo fone: ");
				fflush(stdin);
				gets(p->end_prop.fone);
			}
			else if(op==7)
			{
				printf("\nNovo cel: ");
				fflush(stdin);
				gets(p->end_prop.cel);
			}
			else if(op==8)
			{
				printf("\nNovo email: ");
				fflush(stdin);
				gets(p->end_prop.email);
			}
			else if(op==9)
				return;
			
			fwrite(p, sizeof(prop), 1, fptr);
		}
		fclose(fptr);
	}
}

void altera_im(imovel *im, int qim, int pos, locatario *l, int op) //Alterações no arquivo dos imóveis
{
	
	FILE *fptr=NULL;
	
	if(op==0 || op==1)
	{
		if((fptr=(fopen("imovel.bin", "rb+")))==NULL) //Alteração do arquivo de imóveis
			printf("\nErro na alteracao\n");
		else
		{
			fseek(fptr,pos*sizeof(imovel),SEEK_SET);
			fread(im,sizeof(imovel),1,fptr);
			fseek(fptr,pos*sizeof(imovel),SEEK_SET);
			
			if(op==0)
			{
				im->status.loc.reg_loc = l->reg_loc;
				im->status.loc.sigla = 'A';
			}
			else if(op==1)
				im->status.sigla = 'L';
			
			fwrite(im, sizeof(imovel), 1, fptr);
		}
		fclose(fptr);
	}
	else if(op==2)
	{
		if((fptr=(fopen("imovel.bin", "rb+")))==NULL) //Alteração do arquivo de imóveis
			printf("\nErro na alteracao\n");
		else
		{
			fseek(fptr, pos*sizeof(imovel), SEEK_SET);
			fread(im, sizeof(imovel), 1, fptr);
			fseek(fptr, pos*sizeof(imovel), SEEK_SET);
			
			do
			{
				system("cls");
				printf("\nO que deseja alterar?\n[1] Logradouro\n[2] Bairro\n[3] CEP\n[4] Cidade\n[5] Area util\n[6] N de quartos\n[7] Valor do aluguel\n[8] Voltar\n");
				scanf("%i", &op);
				
				if(op<1 || op>8)
				{
					printf("\nDigite uma opcao valida\n");
					system("pause");
				}
			}while(op<1 || op>8);
			
			if(op==1)
			{
				printf("\nNovo logradouro: ");
				fflush(stdin);
				gets(im->end_imov.logradouro);
			}
			else if(op==2)
			{
				printf("\nNovo bairro: ");
				fflush(stdin);
				gets(im->end_imov.bairro);
			}
			else if(op==3)
			{
				printf("\nNovo CEP: ");
				fflush(stdin);
				gets(im->end_imov.CEP);
			}
			else if(op==4)
			{
				printf("\nNova cidade: ");
				fflush(stdin);
				gets(im->end_imov.cidade);
			}
			else if(op==5)
			{
				printf("\nNova area util: ");
				fflush(stdin);
				scanf("%f", &im->area);
			}
			else if(op==6)
			{
				printf("\nNovo numero de quartos: ");
				fflush(stdin);
				scanf("%i", &im->quartos);
			}
			else if(op==7)
			{
				printf("\nNovo valor de aluguel: ");
				fflush(stdin);
				scanf("%f", &im->valor);
			}
			else if(op==8)
				return;
			
			fwrite(im, sizeof(imovel), 1, fptr);
		}
		fclose(fptr);
	}
}

void altera_loc(locatario *l, int qloc, int pos, int op, int qprop, int qim) //Alterações no arquivo dos locatários
{
	FILE *fptr=NULL, *fptr2=NULL;
	prop *p=NULL;
	imovel *im=NULL;
	int i, contlivre=0, nreg, vdd, dia, mes, ano;
	
	aloca_prop(&p, 1);
	aloca_imovel(&im, 1);
	
	
	if(op==0)
	{
		if((fptr=(fopen("locatario.bin", "rb+")))==NULL) //Alteração do arquivo de locatários
			printf("\nErro na alteracao\n");
		else
		{
			fseek(fptr, pos*sizeof(locatario), SEEK_SET);
			fread(l, sizeof(locatario), 1, fptr);
			fseek(fptr, pos*sizeof(locatario), SEEK_SET);
			
			strcpy(l->CPF, "@");
	
			fwrite(l, sizeof(locatario), 1, fptr);
		}
		fclose(fptr);
	}
	else if(op==1)
	{
		if((fptr=(fopen("locatario.bin", "rb+")))==NULL) //Alteração do arquivo de locatários
			printf("\nErro na alteracao\n");
		else
		{
			fseek(fptr, pos*sizeof(locatario), SEEK_SET);
			fread(l, sizeof(locatario), 1, fptr);
			fseek(fptr, pos*sizeof(locatario), SEEK_SET);
			
			do
			{
				system("cls");
				printf("\nO que deseja alterar?\n[1] Logradouro\n[2] Bairro\n[3] CEP\n[4] Cidade\n[5] Estado\n[6] Fone\n[7] Cel\n[8] Email\n");
				printf("[9] Dia de vencimento do aluguel\n[10] Voltar\n");
				scanf("%i", &op);
				
				if(op<1 || op>10)
				{
					printf("\nDigite uma opcao valida\n");
					system("pause");
				}
			}while(op<1 || op>10);
			
			if(op==1)
			{
				printf("\nNovo logradouro: ");
				fflush(stdin);
				gets(l->end_loc.logradouro);
			}
			else if(op==2)
			{
				printf("\nNovo Bairro: ");
				fflush(stdin);
				gets(l->end_loc.bairro);
			}
			else if(op==3)
			{
				printf("\nNovo CEP");
				fflush(stdin);
				gets(l->end_loc.CEP);
			}
			else if(op==4)
			{
				printf("\nNova cidade: ");
				fflush(stdin);
				gets(l->end_loc.cidade);
			}
			else if(op==5)
			{
				printf("\nNovo estado: ");
				fflush(stdin);
				gets(l->end_loc.estado);
			}
			else if(op==6)
			{
				printf("\nNovo fone: ");
				fflush(stdin);
				gets(l->end_loc.fone);
			}
			else if(op==7)
			{
				printf("\nNovo cel: ");
				fflush(stdin);
				gets(l->end_loc.cel);
			}
			else if(op==8)
			{
				printf("\nNovo email: ");
				fflush(stdin);
				gets(l->end_loc.email);
			}
			else if(op==9)
			{
				printf("\nNovo dia de vencimento do aluguel: ");
				fflush(stdin);
				scanf("%i", &l->dia_venc);
			}
			else
				return;
			
			fwrite(l, sizeof(locatario), 1, fptr);
		}
		fclose(fptr);
	}
	else if(op==2)
	{
		if((fptr=(fopen("locatario.bin", "rb+")))==NULL) //Alteração do arquivo de locatários
			printf("\nErro na alteracao\n");
		else
		{
			fseek(fptr, pos*sizeof(locatario), SEEK_SET);
			fread(l, sizeof(locatario), 1, fptr);
			fseek(fptr, pos*sizeof(locatario), SEEK_SET);
			
			mostra_im(im, qim, 1);
			
			//Rotina para ler o imóvel com determinado numero de registro
			if((fptr2=(fopen("imovel.bin", "rb")))==NULL)
				printf("\nNao ha imoveis cadastrados\n");
			else
			{
				printf("\nDigite o numero de registro do imovel desejado: ");
				fflush(stdin);
				scanf("%i", &nreg);
				
				if(nreg > qim)
				{
					printf("\nNao ha nenhum imovel com esse numero de registro\n");
					return;
				}
				
				for(i=0; i<qim; i++)
				{
					fseek(fptr2, i*sizeof(imovel), 0);
					fread(im, sizeof(imovel), 1, fptr2);
					
					if(nreg == im->reg_imov)
					{
						if(im->status.sigla == 'A')
						{
							printf("\nESSE IMOVEL JA SE ENCONTRA ALUGADO\n");
							mostra_loc_parcial(l, qloc, nreg);
							vdd = 0;
							break;
						}
						
						l->reg_imov = im->reg_imov;
						
						l->reg_loc = pos+1;
						printf("\nN de registro: %i", l->reg_loc);
						
						printf("\nNome: ");
						fflush(stdin);
						gets(l->nome);
						
						printf("CPF: ");
						fflush(stdin);
						gets(l->CPF);
						
						printf("Logradouro: ");
						fflush(stdin);
						gets(l->end_loc.logradouro);
						
						printf("Bairro: ");
						fflush(stdin);
						gets(l->end_loc.bairro);
						
						printf("CEP: ");
						fflush(stdin);
						gets(l->end_loc.CEP);
						
						printf("Cidade: ");
						fflush(stdin);
						gets(l->end_loc.cidade);
						
						printf("Estado: ");
						fflush(stdin);
						gets(l->end_loc.estado);
						
						printf("Fone: ");
						fflush(stdin);
						gets(l->end_loc.fone);
						
						printf("Cel: ");
						fflush(stdin);
						gets(l->end_loc.cel);
						
						printf("email: ");
						fflush(stdin);
						gets(l->end_loc.email);
						
						printf("\nN de registro do imovel: %i\n", l->reg_imov);
						
						printf("Digite o dia de vencimento do aluguel: ");
						fflush(stdin);
						scanf("%i", &(l->dia_venc));
						
						printf("Data de inicio do contrato (D/M/A):\n");
						fflush(stdin);
						
						scanf("%i/%i/%i", &dia, &mes, &ano);
						fflush(stdin);
						
						sprintf(l->inicio, "%i/%i/%i", dia, mes, ano);
						sprintf(l->termino, "%i/%i/%i", dia, mes, ano+1);
						
						printf("Data de termino do contrato:\n%s\n", l->termino);
						
						altera_prop(p, qprop, nreg, 0);
						pos = busca_im(im, qim, nreg);
						altera_im(im, qim, pos, l, 0);
						
						vdd = 1;
						
						fwrite(l, sizeof(locatario), 1, fptr);
					}
				}
				fclose(fptr2);
					
				if(vdd==0)
					return;
			}
		}
		fclose(fptr);
	}
}

int busca_prop(prop *p, int qprop) //Faz a busca do proprietário que passará pela alteração
{
	FILE *fptr=NULL;
	int i;
	char aux[15];
	
	printf("\nDigite o CPF do proprietario: ");
	fflush(stdin);
	gets(aux);
	
	if((fptr=(fopen("proprietario.bin", "rb")))==NULL)
		printf("\nErro ao abrir o arquivo de proprietarios\n");
	else
	{
		for(i=0; i<qprop; i++)
		{
			fseek(fptr, i*sizeof(prop), SEEK_SET);
			fread(p, sizeof(prop), 1, fptr);
			
			if(strcmp(p->CPF, aux)==0)
				return i;
		}
	}
	fclose(fptr);
	
	printf("\nNao foi encontrado nenhum proprietario cadastrado com esse CPF\n");
	system("pause");
	return -1;
}

int busca_im(imovel *im, int qim, int nreg) //Faz a busca do imóvel que passará pela alteração
{
	FILE *fptr=NULL;
	int i;
	
	if((fptr=(fopen("imovel.bin", "rb")))==NULL)
		printf("\nErro na busca\n");
	else
	{
		for(i=0; i<qim; i++)
		{
			fseek(fptr,i*sizeof(imovel),SEEK_SET);
			fread(im,sizeof(imovel),1,fptr);
		
			if(nreg == im->reg_imov)
				return i;
		}
		fclose(fptr);
	}
	
}

int busca_loc(locatario *l, int qloc) //Faz a busca do locatário que passará pela alteração
{
	FILE *fptr=NULL;
	int i;
	char aux[15];
	
	printf("\nDigite o CPF do locatario: ");
	fflush(stdin);
	gets(aux);
	
	if((fptr=(fopen("locatario.bin", "rb")))==NULL)
		printf("\nErro ao abrir o arquivo de locatarios\n");
	else
	{
		for(i=0; i<qloc; i++)
		{
			fseek(fptr, i*sizeof(locatario), SEEK_SET);
			fread(l, sizeof(locatario), 1, fptr);
			
			if(strcmp(l->CPF, aux)==0)
				return i;
		}
	}
	fclose(fptr);
	
	printf("\nNao foi encontrado nenhum locatario cadastrado com esse CPF\n");
	system("pause");
	return -1;
}

void termino_contrato(prop *p, int qprop, imovel *im, int qim, locatario *l, int qloc) //Realiza o término do contrato
{
	FILE *fptr=NULL, *fptr2=NULL;
	int i, j, vdd=0, dia, mes, ano, d, m, a, cont=0, data, pos;
	char *aux = NULL;
	
	aloca_char(&aux, 9);
	
	system("cls");
	
	if(qloc == 0)
	{
		printf("\nNao ha locatarios cadastrados\n");
		return;
	}
	
	//Rotina para ler o locatario com determinado CPF
	if((fptr=(fopen("locatario.bin", "rb")))==NULL)
		printf("\nNao ha locatarios cadastrados\n");
	else
	{
		printf("\nDigite o CPF do locatario que tera seu contrato finalizado: ");
		fflush(stdin);
		gets(aux);
		
		for(i=0; i<qloc; i++)
		{
			fseek(fptr, i*sizeof(locatario), 0);
			fread(l, sizeof(locatario), 1, fptr);
			
			if(strcmp(aux, l->CPF)==0)
			{
				mostra_loc_parcial(l, qloc, l->reg_imov);
				
				printf("\nDigite a data atual (D/M/A):");
				fflush(stdin);
				scanf("%i/%i/%i", &dia, &mes, &ano);
				
				// O for a seguir passa os valores de data do tipo char para o tipo inteiro
				d = atoi(l->termino);
				for(j=0; j<strlen(l->termino); j++)
				{
					if(*(l->termino+j) == '/')
					{
						cont++;
						
						*aux = *(l->termino+j+1);
						if(*(l->termino+j+2) != '/')
							*(aux+1) = *(l->termino+j+2);
						else
							*(aux+1) = '\0';
						
						if(cont==1)
							m = atoi(aux);
						else if(cont==2)
							a = atoi(aux);
					}
				}
				
				//Comparação das datas
				if (ano != a)
    				data = ano - a;
				else if (mes != m)
    				data = mes - m;
				else
    				data = dia - d;
				
				pos = busca_im(im, qim, l->reg_imov);
								
				if(data < 0) //Contrato está sendo cancelado antes da data de término
				{
					if((fptr=(fopen("imovel.bin", "rb")))!=NULL)
					{
						fseek(fptr2, pos*sizeof(imovel), SEEK_SET);
						fread(im, sizeof(imovel), 1, fptr2);
						printf("\nO contrato esta sendo cancelado antes da data de termino estabelecida!\nPor conta disso sera cobrado uma multa no valor de R$%.2f\n\n", im->valor);
					}
					fclose(fptr2);
				}
				else if(data > 0) //O contrato está sendo cancelado depois da data de término
					printf("\nO contrato esta sendo cancelado depois da data de termino estabelecida, portanto nao sera cobrada nenhuma multa\n\n");
				else
					printf("\nO contrato esta sendo cancelado na data de termino estabelecida, portanto nao sera cobrada nenhuma multa\n\n");
				
				altera_prop(p, qprop, l->reg_imov, 1);
				altera_im(im, qim, pos, l, 1);
				
				vdd = 1;
				
				vdd++;
				break;
			}
		}
		fclose(fptr);
		
		altera_loc(l, qloc, i, 0, qprop, qim);
		
		if(vdd==0)
		{
			printf("\nNao ha nenhum proprietario cadastrado com esse CPF\n");
			return;
		}
	}
}

void relatorio(prop *p, int qprop, imovel *im, int qim, locatario *l, int qloc) //Relatório
{
	FILE *fptr=NULL, *fptr2=NULL;
	int dia, i, j, k, arroba, cont=0;
	
	arroba = conta_arroba(l, qloc);
	
	if(qloc==0 || arroba==qloc)
	{
		system("cls");
		printf("\nNao ha locatarios cadastrados\n");
		return;
	}
	
	printf("\nDia de vencimento do alguel: ");
	scanf("%i", &dia);
	
	if((fptr=(fopen("locatario.bin", "rb")))==NULL) //Arquivo dos locatários
		printf("\nErro ao abrir o arquivo de locatarios\n");
	else
	{
		printf("\n");
		for(i=0; i<qloc; i++)
		{
			fseek(fptr, i*sizeof(locatario), SEEK_SET);
			fread(l, sizeof(locatario), 1, fptr);
			
			if(l->dia_venc == dia && strcmp(l->CPF, "@")!=0)
			{
				printf("IMOVEL\nN de registro: %i\n", l->reg_imov);
				
				if((fptr2=(fopen("imovel.bin", "rb")))==NULL) //Arquivo dos imóveis
					printf("\nErro ao abrir o arquivo de imoveis\n");
				else
				{
					for(j=0; j<qim; j++)
					{
						fseek(fptr2, j*sizeof(imovel), SEEK_SET);
						fread(im, sizeof(imovel), 1, fptr2);
						
						if(l->reg_imov == im->reg_imov)
						{
							printf("Valor: R$%.2f\n", im->valor);
							
						}
					}
				}
				fclose(fptr2);
				
				printf("\nLOCATARIO\nN de registro: %i\nNome: %s\nCPF: %s\n", l->reg_loc, l->nome, l->CPF);
				
				if((fptr2=(fopen("proprietario.bin", "rb")))==NULL) //Arquivo dos proprietários
					printf("\nErro ao abrir o arquivo de proprietarios\n");
				else
				{
					for(j=0; j<qprop; j++)
					{
						fseek(fptr2, j*sizeof(prop), SEEK_SET);
						fread(p, sizeof(prop), 1, fptr2);
						
						for(k=0; k<p->qtd_casa; k++)
						{
							if(l->reg_imov == (p->casa+k)->num_casa)
							{
								printf("\nPROPRIETARIO\nN de registro: %i\nNome: %s\nCPF: %s\n", p->reg_prop, p->nome, p->CPF);
							}
						}
					}
				}
				fclose(fptr2);
				cont++;
				printf("\n---------------------------------------\n\n");
			}
		}
		if(cont==0)
			printf("\nNao ha alugueis para esse dia\n");
	}
}

int verifica_arroba(locatario *l, int qloc) //Retorna a posição de um locatário com @ no CPF
{
	FILE *fptr=NULL;
	int i;
	
	if((fptr=(fopen("locatario.bin", "rb")))==NULL)
		return -1;
	else
	{
		for(i=0; i<qloc; i++)
		{
			fseek(fptr, i*sizeof(locatario), SEEK_SET);
			fread(l, sizeof(locatario), 1, fptr);
			
			if(strcmp(l->CPF, "@")==0)
				return i;
		}
	}
	fclose(fptr);
	
	return -1;
}

int conta_arroba(locatario *l, int qloc) //Função para verificar se há locatários cadastrados sem @ no CPF
{
	FILE *fptr=NULL;
	int i, cont=0;
	
	if((fptr=(fopen("locatario.bin", "rb")))==NULL)
		printf("\nErro\n");
	else
	{
		for(i=0; i<qloc; i++)
		{
			fseek(fptr, i*sizeof(locatario), SEEK_SET);
			fread(l, sizeof(locatario), 1, fptr);
			
			if(strcmp(l->CPF, "@")==0)
				cont++;
		}
		
	}
	fclose(fptr);
	
	return cont;
}
