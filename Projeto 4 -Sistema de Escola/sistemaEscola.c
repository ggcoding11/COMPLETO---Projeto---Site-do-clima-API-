#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

#define MAX_NOMETURMA 50
#define MAX_NOMEALUNO 100
#define MAX_NOMEMATERIA 50

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

typedef struct{
	char nome[MAX_NOMEMATERIA];
	float nota1;
	float nota2;
	
	float media;
} Materia;

char materias[9][] = {"Hist�ria", "Sociologia", "Geografia", "Filosofia", "Literatura", "Matem�tica", "F�sica", "Biologia", "Qu�mica"};

void listarAlunos();
void pesquisarAlunos();
void cadastrarAlunos();
void lancarNotas();

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
		printf("4 - Lan�ar notas\n");
		printf("5 - Cadastrar aluno\n");
		printf("6 - Criar turma nova\n");
		printf("7 - Alterar notas do aluno\n");
		printf("8 - Alterar dados do aluno\n");
		printf("0 - Sair\n\n");
		
		printf("Op��o: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				listarAlunos();
			break;
			
			case 3:
				pesquisarAlunos();
			break;
			
			case 4:
				lancarNotas();
			break;
			
			case 5:
				cadastrarAlunos();
			break;
			
			case 0:
				printf("\nObrigado por utilizar o meu sistema!");
			break;
			
			default:
				printf("\nOp��o inv�lida!");
				
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
		printf("Sem turmas dispon�veis!\n");
		
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
		return;
	}
	
	Turma turma;
	
	while(fscanf(listaTurmas, "%d %50[^\n]", &turma.id, turma.nome) == 2){
		printf("%d - %s\n", turma.id, turma.nome);
	}
	
	int turmaValida;
	
	int idEscolhido;
	
	do {
		rewind(listaTurmas);
		
		turmaValida = 0;
		
		printf("\nQual a turma?: ");
		scanf("%d", &idEscolhido);
		
		while(fscanf(listaTurmas, "%d %*[^\n]", &turma.id) == 1){
			if (idEscolhido == turma.id){
				turmaValida = 1;
				break;
			}
		}
		
		if (!turmaValida){
			printf("Turma n�o encontrada!\n");
		}
	} while (!turmaValida);
	
	fclose(listaTurmas);
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	
	if (!listaAlunos){
		printf("Arquivo n�o encontrado!\n\n");
		
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
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	
	if(!listaAlunos){
		printf("Arquivo n�o encontrado!\n\n");
		
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
		
		return;
	}
	
	printf("1 - Por ID\n");
	printf("2 - Por nome\n\n");
	
	int opcao;
	
	printf("Op��o: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 1: {
			fflush(stdin);
			
			int idEscolhido;
			
			printf("Qual o ID do estudante?: ");
			scanf("%d", &idEscolhido);	
			
			printf("\n");
			
			char nomeArquivo[30];
			
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
				printf("Aluno n�o encontrado!\n\n");		
			}
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
				printf("Aluno n�o encontrado!\n\n");		
			}	
		}
		
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
		
		break;
	}
	
	fclose(listaAlunos);
}

void cadastrarAlunos(){
	system("cls");
	
	printf("CADASTRO DE ALUNOS\n\n");
	
	FILE *listaTurmas = fopen("listaTurmas.txt", "r");
	
	if (!listaTurmas){
		printf("Sem turmas dispon�veis!\n");
		
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
		return;
	}
	
	Aluno aluno;
	
	FILE *listaAlunos = fopen("Alunos.txt", "a+");
	
	if(!listaAlunos){
		printf("Arquivo n�o encontrado!\n\n");
		
		fflush(stdin);
	
		printf("Pressione qualquer tecla para continuar!");
		getchar();
		
		return;
	}
	
	rewind(listaAlunos);
	
	int repetido;
	
	do {
		repetido = 0;
		
		printf("Qual o ID do estudante?: ");
		scanf("%d", &aluno.id);
		
		if (aluno.id <= 0){
			printf("ID inv�lido!!\n\n");
		}
		
		int idCadastrado;
		
		while (fscanf(listaAlunos, "%d|%*[^|]|%*[^|]|%*[^|]|%*[^\n]", &idCadastrado) == 1){
			if (idCadastrado == aluno.id){
				printf("ID de estudante j� cadastrado!\n\n");
				repetido = 1;
				
				break;
			}	
		}	
		
		rewind(listaAlunos);
	} while (repetido || aluno.id <= 0);
	
	fflush(stdin);
	
	printf("Qual o nome do aluno(a)?: ");
	fgets(aluno.nome, sizeof(aluno.nome), stdin);
	
	strtok(aluno.nome, "\n");
	
	printf("Qual a data de nascimento?: ");
	fgets(aluno.dataNasc, sizeof(aluno.dataNasc), stdin);
	
	strtok(aluno.dataNasc, "\n");
	
	printf("Qual a idade?: ");
	scanf("%d", &aluno.idade);
	
	printf("Qual a turma?: \n\n");
	
	Turma turma;
	
	while(fscanf(listaTurmas, "%d %50[^\n]", &turma.id, turma.nome) == 2){
		printf("%d - %s\n", turma.id, turma.nome);
	}
	
	int turmaValida;
	
	do {
		rewind(listaTurmas);
		
		turmaValida = 0;
		
		printf("Op��o: ");
		scanf("%d", &aluno.turma);	
		
		while(fscanf(listaTurmas, "%d %*[^\n]", &turma.id) == 1){
			if (aluno.turma == turma.id){
				turmaValida = 1;
				break;
			}
		}
	} while (!turmaValida);

	fclose(listaTurmas);
	
	fprintf(listaAlunos, "%d|%s|%d|%d|%s\n", aluno.id, aluno.nome, aluno.turma, aluno.idade, aluno.dataNasc);
	
	printf("Aluno cadastrado!!\n\n");
				
	fclose(listaAlunos);
	
	fflush(stdin);
	
	printf("Pressione qualquer tecla para continuar!");
	getchar();
}

void lancarNotas(){
	system("cls");
	
	printf("LAN�AMENTO DE NOTAS\n\n");
	
	Aluno aluno;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &aluno.id);
	
	printf("Mat�rias: \n");
	printf("1 - Hist�ria\n");
	printf("2 - Sociologia\n");
	printf("3 - Geografia\n");
	printf("4 - Filosofia\n");
	printf("5 - Literatura\n");
	printf("6 - Matem�tica\n");
	printf("7 - F�sica\n");
	printf("8 - Biologia\n");
	printf("9 - Qu�mica\n\n");
	
	int opcao;
	
	do {
		printf("Qual a mat�ria?: ");
		scanf("%d", &opcao);	
	} while (opcao <= 0 && opcao > 9);

	Materia materia;
	
	strcpy(materia.nome, materia[opcao - 1]);
	
	strtok(materia.nome, "\n");	
}
