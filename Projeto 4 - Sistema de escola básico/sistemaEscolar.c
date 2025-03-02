#include <stdio.h>
#include <time.h>

void menuPrincipal();
void menuAlunos();
void menuNotas();

int verificarID(int *id);
void finalizar();

void cadastrarAluno();
void alterarDadosAluno();

typedef struct{
	int id;
	char nome[61];
	int diaNasc, mesNasc, anoNasc;
	int idade;
} Aluno;

int main(){
	
	menuPrincipal();
	
	return 0;
}

void finalizar(){
	fflush(stdin);
	
	printf("Pressione qualquer tecla para continuar!");
	
	getchar();
}

int verificarID(int *id){
	if (*id > 0){
		FILE *listaAlunos = fopen("Alunos.txt", "r");
	
		Aluno aluno;
		
		while (fscanf(listaAlunos, "%d|%*[^|]|%*[^\n]", &aluno.id) == 1){
			if (aluno.id == *id){
				return 1;		
			}
		}
		
		fclose(listaAlunos);
		
		return 0;
	} else {
		return 2;
	}
}

void menuPrincipal(){
	system("cls");

	printf("CCIM - Sistema escolar (Por Mr. JeeJ)\n\n");
	
	int opcao;
		
	printf("1 - Alunos\n");
	printf("2 - Notas\n");
	printf("0 - Sair\n\n");
	
	printf("Opcao: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 0:
			printf("Saindo...");
			return;
		break;
		
		case 1:
			menuAlunos();
		break;
		
		case 2:
			menuNotas();
		break;
		
		default:
			menuPrincipal();
		break;
	}
}

void menuAlunos(){
	system("cls");
	
	printf("ALUNOS\n\n");
	
	int opcao;
	
	printf("1 - Cadastro de estudante\n");
	printf("2 - Alteracao dos dados do estudante\n");
	printf("3 - Remocao de um estudante\n");
	printf("4 - Listagem de estudantes\n");
	printf("0 - Voltar para o menu principal\n\n");
	
	printf("Opcao: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 0:
			menuPrincipal();
		break;
		
		case 1:
			cadastrarAluno();
		break;
		
		case 2:
			alterarDadosAluno();
		break;
		
		default:
			menuAlunos();
		break;
	}
}

void menuNotas(){
	system("cls");
	
	printf("NOTAS\n\n");
	
	int opcao;
	
	printf("1 - Cadastro de notas\n");
	printf("2 - Alteracao das notas do estudante\n");
	printf("3 - Remocao das notas\n");
	printf("4 - Listagem do boletim do estudante\n");
	printf("0 - Voltar para o menu principal\n\n");
	
	printf("Opcao: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 0:
			menuPrincipal();
		break;
		
		default:
			menuNotas();
		break;
	}
}

void cadastrarAluno(){
	system("cls");
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	int anoAtual = tm.tm_year + 1900;
	int mesAtual = tm.tm_mon + 1;
	int diaAtual = tm.tm_mday;
	
	printf("CADASTRO DE ESTUDANTES\n\n");
	
	FILE *listaAlunos = fopen("Alunos.txt", "a");
	
	if (!listaAlunos){
		printf("Erro na abertura do arquivo!\n");
		finalizar();
		
		return;
	}
	
	Aluno aluno;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &aluno.id);
	
	switch(verificarID(&aluno.id)){
		case 0:
			fflush(stdin);
			
			printf("Qual o nome do estudante?: ");
			scanf("%60[^\n]", &aluno.nome);
			
			do {
				printf("Qual a data de nascimento (DD MM AA)?: ");
				scanf("%d %d %d", &aluno.diaNasc, &aluno.mesNasc, &aluno.anoNasc);	
			} while (aluno.anoNasc >= anoAtual);
			
			aluno.idade = anoAtual - aluno.anoNasc;
			
			if ((aluno.mesNasc > mesAtual) || (aluno.mesNasc == mesAtual && diaAtual < aluno.diaNasc)){
				aluno.idade--;
			}
		
			fprintf(listaAlunos, "%d|%s|%d/%d/%d|%d\n", aluno.id, aluno.nome, aluno.diaNasc, aluno.mesNasc, aluno.anoNasc, aluno.idade);
			
			printf("Estudante cadastrado!\n");
		break;
		
		case 1:
			printf("ID ja cadastrado\n\n");
		break;
		
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaAlunos);
	
	finalizar();
	
	menuAlunos();
}

void alterarDadosAluno(){
	system("cls");
	
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	int anoAtual = tm.tm_year + 1900;
	int mesAtual = tm.tm_mon + 1;
	int diaAtual = tm.tm_mday;
	
	printf("ALTERACAO DOS DADOS\n\n");
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	
	if (!listaAlunos){
		printf("Erro na abertura do arquivo!\n");
		finalizar();
		
		return;
	}
	
	Aluno aluno;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &aluno.id);
	
	switch(verificarID(&aluno.id)){
		case 0:
			printf("ID nao cadastrado\n\n");
		break;
		
		case 1:
			fflush(stdin);
			
			printf("Qual o nome do estudante?: ");
			scanf("%60[^\n]", &aluno.nome);
			
			do {
				printf("Qual a data de nascimento (DD MM AA)?: ");
				scanf("%d %d %d", &aluno.diaNasc, &aluno.mesNasc, &aluno.anoNasc);	
			} while (aluno.anoNasc >= anoAtual);
			
			aluno.idade = anoAtual - aluno.anoNasc;
			
			if ((aluno.mesNasc > mesAtual) || (aluno.mesNasc == mesAtual && diaAtual < aluno.diaNasc)){
				aluno.idade--;
			}
		
			//Estabelecer quantidade maxima de estudantes com o define para eu criar o vetor
		
		break;
		
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	finalizar();
	
	menuAlunos();
}
