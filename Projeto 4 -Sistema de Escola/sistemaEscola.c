#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

#define MAX_NOMETURMA 50
#define MAX_NOMEALUNO 100

typedef struct {
	int id;
	char nome[MAX_NOMETURMA];
} Turma;

typedef struct{
	int id;
	char nome[MAX_NOMEALUNO];
	int idade;
	char dataNasc[11];
	int turma;
} Aluno;


void listarAlunos();
void pesquisarAlunos();
void cadastrarAlunos();

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	int opcao;
	
	do {
		system("cls");
		
		printf("Sistema CCIM - Feito por Mr.JeeJ  |\n");
	
		int i;
		
		for (i = 0; i < 35; i++){
			printf("-");
		}
		
		printf("\n");
		
		printf("1 - Listagem de alunos\n");
		printf("2 - Mostrar boletim pelo ID\n");
		printf("3 - Pesquisar aluno\n");
		printf("4 - Lançar notas\n");
		printf("5 - Cadastrar aluno\n");
		printf("6 - Criar turma nova\n");
		printf("7 - Alterar notas do aluno\n");
		printf("8 - Alterar dados do aluno\n");
		printf("0 - Sair\n\n");
		
		printf("Opção: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				listarAlunos();
			break;
			
			case 3:
				pesquisarAlunos();
			break;
			
			case 0:
				printf("\nObrigado por utilizar o meu sistema!");
			break;
			
			default:
				printf("\nOpção inválida!");
				
				sleep(1);
			break;
		}
		
	} while (opcao);
	
	return 0;
}

void listarAlunos(){
	system("cls");
	
	printf("LISTAGEM DE ALUNOS\n\n");

	FILE *listaTurmas = fopen("listaTurmas.txt", "r");
	
	if (!listaTurmas){
		printf("Erro ao abrir o arquivo!\n");
		return;
	}
	
	Turma turma;
	
	while(fscanf(listaTurmas, "%d %50[^\n]", &turma.id, turma.nome) == 2){
		printf("%d - %s\n", turma.id, turma.nome);
	}

	fclose(listaTurmas);
	
	int idEscolhido;
	
	printf("\nQual a turma?: ");
	scanf("%d", &idEscolhido);
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	
	if (!listaAlunos){
		printf("Turma não encontrada!\n");
		
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
			
		return;
	}
	
	printf("Alunos: \n\n");
	
	Aluno aluno;
	
	while (fscanf(listaAlunos, "%d|%99[^|]|%d|%d|%10s", &aluno.id, aluno.nome, &aluno.turma, &aluno.idade, aluno.dataNasc) == 5){
		if (aluno.turma == idEscolhido){
			printf("ID: %d\n", aluno.id);
			printf("Nome: %s\n", aluno.nome);
			printf("Idade: %d\n", aluno.idade);
			printf("Data de nascimento: %s\n", aluno.dataNasc);
			
			printf("\n");	
		}
	}
	
	fclose(listaAlunos);
	
	fflush(stdin);
	
	printf("Pressione qualquer tecla para continuar!");
	getchar();
}

void pesquisarAlunos(){
	system("cls");
	
	printf("PESQUISA DE ALUNOS\n\n");
	
	printf("1 - Por ID\n");
	printf("2 - Por nome\n\n");
	
	int opcao;
	
	printf("Opção: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 1: {
			fflush(stdin);
			
			int idEscolhido;
			
			printf("Qual o ID do aluno?: ");
			scanf("%d", &idEscolhido);	
			
			printf("\n");
			
			char nomeArquivo[30];
			
			FILE *listaAlunos = fopen("Alunos.txt", "r");
			
			Aluno aluno;
			
			int encontrou = 0;
				
			while (fscanf(listaAlunos, "%d|%99[^|]|%*[^|]|%d|%10s", &aluno.id, aluno.nome, &aluno.idade, aluno.dataNasc) == 4){
				if (idEscolhido == aluno.id){
					encontrou = 1;
					break;
				}	
			}
			
			if (encontrou){
				printf("ID: %d\n", aluno.id);
				printf("Nome: %s\n", aluno.nome);
				printf("Idade: %d\n", aluno.idade);
				printf("Data de nascimento: %s\n", aluno.dataNasc);
				
				printf("\n");	
			} else {
				printf("Aluno não encontrado!\n\n");		
			}
			
			fclose(listaAlunos);
		}
	
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
		
		break;
		
		case 2: {
			fflush(stdin);
			
			char nomeParcial[MAX_NOMEALUNO];
			
			printf("Escreva o nome do estudante: ");
			fgets(nomeParcial, sizeof(nomeParcial), stdin);
			
			printf("\n");
			
			strtok(nomeParcial, "\n");
			
			FILE *listaAlunos = fopen("Alunos.txt", "r");
			
			Aluno aluno;
			
			int encontrou = 0;
			
			while (fscanf(listaAlunos, "%d|%99[^|]|%*[^|]|%d|%10s", &aluno.id, aluno.nome, &aluno.idade, aluno.dataNasc) == 4){
				strtok(aluno.nome, "\n");
				
				char *ptr = strstr(aluno.nome, nomeParcial);
				
				if (ptr){
					encontrou = 1;
					
					printf("ID: %d\n", aluno.id);
					printf("Nome: %s\n", aluno.nome);
					printf("Idade: %d\n", aluno.idade);
					printf("Data de nascimento: %s\n", aluno.dataNasc);
			
					printf("\n");		
				}
			}	
			
			if (!encontrou){
				printf("Aluno não encontrado!\n\n");		
			} 
			
			fclose(listaAlunos);
		}
		
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
		
		break;
	}
}

void cadastrarAlunos(){
	system("cls");
	
	printf("CADASTRO DE ALUNOS\n\n");
	
	Aluno aluno;
}
