#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char marca[30];
	char modelo[30];
	char cor[20];
	int anoModelo;
	int anoFabricacao;
	char combustivel[30];
	char placa[20];
} Carro;

int contCarro = 0;
Carro carros[5];

void cadastrarCarro();
void pesquisarCarro();

int main(){
	
	int opcao;
	
	do {
		system("cls");
		
		printf("Sistema de cadastro de carros - Por Mr.JeeJ\n\n");
		printf("1 - Cadastro de carro\n");
		printf("2 - Pesquisa de carro\n");
		printf("0 - Sair\n\n");
		
		printf("Opcao: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				cadastrarCarro();
			break;
			
			case 2:
				pesquisarCarro();
			break;
			
			case 0:
				printf("\nSaindo...");
			break;
		}	
	} while(opcao);
	
	return 0;
}

void cadastrarCarro(){
	system("cls");
	
	if (contCarro < 5){
		printf("CADASTRO DE CARRO\n");
		
		printf("Qual a marca do carro?: ");
		scanf("%29s", &carros[contCarro].marca);
		
		printf("Qual o modelo?: ");
		scanf("%29s", &carros[contCarro].modelo);
		
		printf("Qual a cor?: ");
		scanf("%19s", &carros[contCarro].cor);
		
		printf("Qual o ano do modelo?: ");
		scanf("%d", &carros[contCarro].anoModelo);
		
		printf("Qual o ano de fabricacao?: ");
		scanf("%d", &carros[contCarro].anoFabricacao);
		
		printf("Qual o tipo de combustivel?: \n\n");
		
		int opcao;
		
		do {
			printf("Opcoes: \n");
		
			printf("1 - Gasolina\n");
			printf("2 - Etanol\n");
			printf("3 - Flex\n");
			printf("4 - Eletrico\n");
			printf("5 - Hibrido\n");
			printf("6 - Diesel\n\n");
			
			printf("Opcao: ");
			scanf("%d", &opcao);
			
			switch(opcao){
				case 1:
					strcpy(carros[contCarro].combustivel, "Gasolina");
				break;
				
				case 2:
					strcpy(carros[contCarro].combustivel, "Etanol");
				break;
				
				case 3:
					strcpy(carros[contCarro].combustivel, "Flex");
				break;
				
				case 4:
					strcpy(carros[contCarro].combustivel, "Eletrico");
				break;
				
				case 5:
					strcpy(carros[contCarro].combustivel, "Hibrido");
				break;
				
				case 6:
					strcpy(carros[contCarro].combustivel, "Diesel");
				break;
				
				default:
					printf("Opcao invalida!\n\n");
				break;
			}
		} while (opcao < 1 || opcao > 6);
		
		printf("Qual a placa do carro?: ");
		scanf("%19s", &carros[contCarro].placa);
		
		printf("\nVEICULO CADASTRADO!\n");
		contCarro++;
	} else {
		printf("Numero maximo de carros cadastrados atingido!\n");
	}
	
	fflush(stdin);
		
	printf("Pressione qualquer tecla para continuar!");
	
	getchar();
}

void pesquisarCarro(){
	system("cls");
	
	printf("PESQUISA DE CARRO\n\n");
	
	char placaProcurada[20];
	
	printf("Informe a placa do carro: ");
	scanf("%19s", &placaProcurada);
	
	int i, encontrou = 0;
	
	for (i = 0; i < 5; i++){
		if (!(strcmp(placaProcurada, carros[i].placa))){
			printf("Marca: %s\n", carros[i].marca);
			printf("Modelo: %s\n", carros[i].modelo);
			printf("Cor: %s\n", carros[i].cor);
			printf("Ano do modelo: %d\n", carros[i].anoModelo);
			printf("Ano de fabricacao: %d\n", carros[i].anoFabricacao);
			printf("Tipo do combustivel: %s\n", carros[i].combustivel);
			encontrou = 1;
		} 
	}
	
	if (!encontrou){
		printf("VEICULO NAO LOCALIZADO!\n");
	}
	
	fflush(stdin);
		
	printf("Pressione qualquer tecla para continuar!");
	getchar();
}
