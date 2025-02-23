#include <stdio.h>
#include <locale.h>
#include <unistd.h>

#define MAX_NOMETURMA 50

typedef struct {
	int id;
	char nome[MAX_NOMETURMA];
} Turma;


void listarAlunos();

int main(){
	setlocale(LC_ALL, "Portuguese");
	
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
	
	int opcao;
	
	printf("Opção: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 1:
			listarAlunos();
		break;
		
		case 0:
			printf("\nMuito obrigado por usar o meu programa!");
			exit(0);
		break;
	}
	
	return 0;
}

void listarAlunos(){
	system("cls");
	
	printf("LISTAGEM DE ALUNOS\n\n");

	FILE *file = fopen("listaTurmas.txt", "r");
	
	if (!file){
		printf("Erro ao abrir o arquivo!\n");
		return;
	}
	
	Turma turma;
	
	while(fscanf(file, "%d %50[^\n]", &turma.id, turma.nome) == 2){
		printf("%d - %s\n", turma.id, turma.nome);
	}
	
	int idTemp;
	
	printf("\nQual a turma?: ");
	scanf("%d", &idTemp);
}
