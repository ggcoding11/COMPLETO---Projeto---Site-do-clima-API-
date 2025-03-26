#include <stdio.h>
#include <string.h>
#include <time.h>

void menuPrincipal();
void menuAlunos();
void menuNotas();

int qntdAlunos = 0;
int qntdNotas = 0;

void cadastrarAluno();
void alterarDadosAluno();
void removerAluno();
void listarAluno();

void cadastrarNota();
void alterarNota();
void removerNota();
void listarNota();

int verificarID(int id);
int verificarNota(int id, char materia[]);

typedef struct{
	char materia[21];
	float n1, n2, media;
} Nota;

typedef struct{
	int id;
	char nome[61];
	int diaNasc, mesNasc, anoNasc, idade;
	
	Nota nota;
} Aluno;

int main(){
	system("color 17");
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	
	if (listaAlunos){
		int id;
		
		while (fscanf(listaAlunos, "%d|%*[^|]|%*d/%*d/%*d|%*d", &id) == 1) {
			qntdAlunos++;
		}
		
		fclose(listaAlunos);
	}
	
	FILE *listaNotas = fopen("Notas.txt", "r");
	
	if (listaNotas){
		char texto[100];
		
		while (fgets(texto, sizeof(texto), listaNotas) != NULL){
			qntdNotas++;
		}
		
		fclose(listaNotas);
	}
		
	menuPrincipal();
	
	return 0;
}

int verificarID(int id) {
    if (id > 0) {
        FILE *listaAlunos = fopen("Alunos.txt", "r");

        int idLido;
	
        while (fscanf(listaAlunos, "%d|%*[^|]|%*d/%*d/%*d|%*d", &idLido) == 1) {
            if (idLido == id) {
                fclose(listaAlunos);
                return 1;        
            }
        }

        fclose(listaAlunos);
        
        return 0;
    } else {
        return 2;
    }
}

int verificarNota(int id, char materia[]) {
    
    FILE *listaNotas = fopen("Notas.txt", "r");

    int idLido;
    char materiaLida[21];

    while (fscanf(listaNotas, "%d|%20[^|]|%*f|%*f|%*f", &idLido, materiaLida) == 2) {
        if ((idLido == id) && (strcmp(materiaLida, materia) == 0)) {
            fclose(listaNotas);
            return 1;        
        }
    }

    fclose(listaNotas);
    return 0;
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
			
			system("pause");
			
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
	
	printf("ALUNOS | %d cadastrado(s) |\n\n", qntdAlunos);
	
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
		
		case 3:
			removerAluno();
		break;
		
		case 4:
			listarAluno();
		break;
		
		default:
			menuAlunos();
		break;
	}
}

void cadastrarAluno(){
	system("cls");
	
	printf("CADASTRO DE ESTUDANTES\n\n");
	
	FILE *listaAlunos = fopen("Alunos.txt", "a");
	
	if (!listaAlunos){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuAlunos();
		
		return;
	}
	
	Aluno aluno;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &aluno.id);
	
	switch(verificarID(aluno.id)){
		case 0:
			fflush(stdin);
			
			printf("Qual o nome do estudante?: ");
			scanf("%60[^\n]", aluno.nome);
			
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			
			int anoAtual = tm.tm_year + 1900;
			int mesAtual = tm.tm_mon + 1;
			int diaAtual = tm.tm_mday;
			
			do {
				printf("Qual a data de nascimento (DD MM AA)?: ");
				scanf("%d %d %d", &aluno.diaNasc, &aluno.mesNasc, &aluno.anoNasc);	
			} while (aluno.anoNasc >= anoAtual);
			
			aluno.idade = anoAtual - aluno.anoNasc;
			
			if ((aluno.mesNasc > mesAtual) || (aluno.mesNasc == mesAtual && diaAtual < aluno.diaNasc)){
				aluno.idade--;
			}
		
			fprintf(listaAlunos, "%d|%s|%d/%d/%d|%d\n", aluno.id, aluno.nome, aluno.diaNasc, aluno.mesNasc, aluno.anoNasc, aluno.idade);
			
			printf("Estudante cadastrado!\n\n");
			
			qntdAlunos++;
		break;
		
		case 1:
			printf("ID ja cadastrado\n\n");
		break;
		
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaAlunos);
	
	system("pause");
	
	menuAlunos();
}

void alterarDadosAluno(){
	system("cls");
	
	printf("ALTERACAO DOS DADOS\n\n");
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	
	if (!listaAlunos){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuAlunos();
		
		return;
	}
	
	Aluno aluno;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &aluno.id);
	
	switch(verificarID(aluno.id)){
		case 0:
			printf("ID nao cadastrado\n\n");
		break;
		
		case 1:{
			fflush(stdin);
			
			printf("Qual o nome do estudante?: ");
			scanf("%60[^\n]", aluno.nome);
			
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			
			int anoAtual = tm.tm_year + 1900;
			int mesAtual = tm.tm_mon + 1;
			int diaAtual = tm.tm_mday;
			
			do {
				printf("Qual a data de nascimento (DD MM AA)?: ");
				scanf("%d %d %d", &aluno.diaNasc, &aluno.mesNasc, &aluno.anoNasc);	
			} while (aluno.anoNasc >= anoAtual);
			
			aluno.idade = anoAtual - aluno.anoNasc;
			
			if ((aluno.mesNasc > mesAtual) || (aluno.mesNasc == mesAtual && diaAtual < aluno.diaNasc)){
				aluno.idade--;
			}
		
			Aluno estudantes[qntdAlunos];
			
			int cont = 0;
			
			while(fscanf(listaAlunos, "%d|%60[^|]|%d/%d/%d|%d", &estudantes[cont].id, estudantes[cont].nome, &estudantes[cont].diaNasc, &estudantes[cont].mesNasc, &estudantes[cont].anoNasc, &estudantes[cont].idade) == 6){
				if (aluno.id == estudantes[cont].id){
					estudantes[cont] =  aluno;
				}
				
				cont++;	
			}
			
			FILE *listaAlunosNova = fopen("Alunos.txt", "w");
			
			int i;
			
			for (i = 0; i < cont; i++){
				fprintf(listaAlunosNova, "%d|%s|%d/%d/%d|%d\n", estudantes[i].id, estudantes[i].nome, estudantes[i].diaNasc, estudantes[i].mesNasc, estudantes[i].anoNasc, estudantes[i].idade);
			}
			
			fclose(listaAlunosNova);
			
			printf("Alteracoes bem sucedidas!\n\n");	
		}
		
		break;
		
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaAlunos);
	
	system("pause");
	
	menuAlunos();
}

void removerAluno(){
	system("cls");
	
	printf("REMOCAO DE ESTUDANTE\n\n");
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	
	if (!listaAlunos){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuAlunos();
		
		return;
	}
	
	int idRemovido;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &idRemovido);
	
	switch(verificarID(idRemovido)){
		case 0:
			printf("ID nao cadastrado\n\n");
		break;
		
		case 1:{
			fflush(stdin);
			
			Aluno aluno;
			
			Aluno estudantes[qntdAlunos];
			
			int cont = 0;
		
			while(fscanf(listaAlunos, "%d|%60[^|]|%d/%d/%d|%d", &aluno.id, aluno.nome, &aluno.diaNasc, &aluno.mesNasc, &aluno.anoNasc, &aluno.idade) == 6){
				if (idRemovido != aluno.id){
					estudantes[cont] = aluno;
					cont++;
				}
			}
			
			FILE *listaAlunosNova = fopen("Alunos.txt", "w");
			
			int i;
			
			for (i = 0; i < cont; i++){
				fprintf(listaAlunosNova, "%d|%s|%d/%d/%d|%d\n", estudantes[i].id, estudantes[i].nome, estudantes[i].diaNasc, estudantes[i].mesNasc, estudantes[i].anoNasc, estudantes[i].idade);
			}
			
			fclose(listaAlunosNova);	
			
			printf("Remocao de estudante bem sucedida!\n\n");
			
			qntdAlunos--;
		}
		
		break;
	
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaAlunos);
	
	system("pause");
	
	menuAlunos();
}

void listarAluno(){
	system("cls");
	
	printf("LISTAGEM DE ESTUDANTES\n\n");
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
					
	if (!listaAlunos){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuAlunos();
		
		return;
	}
	
	int opcao;
	
	printf("1 - Listagem individual\n");
	printf("2 - Listagem geral\n\n");
	
	printf("Opcao: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 1:{
			system("cls");
						
			int idLido;
			
			printf("Qual o ID do estudante?: ");
			scanf("%d", &idLido);
			
			switch(verificarID(idLido)){
				
				case 0:
					printf("ID nao cadastrado\n\n");
				break;
				
				case 1:{
					fflush(stdin);
					
					Aluno aluno;
					
					while(fscanf(listaAlunos, "%d|%60[^|]|%d/%d/%d|%d", &aluno.id, aluno.nome, &aluno.diaNasc, &aluno.mesNasc, &aluno.anoNasc, &aluno.idade) == 6){	
						if (idLido == aluno.id){
							printf("ID: %d\n", aluno.id);
							printf("Nome: %s\n", aluno.nome);
							printf("Data de nascimento: %d/%d/%d\n", aluno.diaNasc, aluno.mesNasc, aluno.anoNasc);
							printf("Idade: %d\n\n", aluno.idade);
							
							break;
						}
					}
				}
				
				break;
			
				case 2:
					printf("ID invalido\n\n");
				break;
			}
		}
			
		break;
		
		case 2:{
			system("cls");
			
			fflush(stdin);
			
			Aluno aluno;
			
			int encontrou = 0;
			
			while(fscanf(listaAlunos, "%d|%60[^|]|%d/%d/%d|%d", &aluno.id, aluno.nome, &aluno.diaNasc, &aluno.mesNasc, &aluno.anoNasc, &aluno.idade) == 6){	
				printf("ID: %d\n", aluno.id);
				printf("Nome: %s\n", aluno.nome);
				printf("Data de nascimento: %d/%d/%d\n", aluno.diaNasc, aluno.mesNasc, aluno.anoNasc);
				printf("Idade: %d\n\n", aluno.idade);
				
				encontrou = 1;
			}
			
			if (!encontrou){
				printf("Nenhum estudante cadastrado!\n\n");
			}
		}
		
		break;
		
		default:
			printf("Opcao invalida!\n\n");
		break;
		
	}
	
	fclose(listaAlunos);
	
	system("pause");
			
	menuAlunos();
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
		
		case 1:
			cadastrarNota();
		break;
		
		case 2:
			alterarNota();
		break;
		
		case 3:
			removerNota();
		break;
		
		case 4:
			listarNota();
		break;
		
		default:
			menuNotas();
		break;
	}
}

void cadastrarNota(){
	system("cls");
	
	printf("CADASTRO DE NOTAS\n\n");
	
	FILE *listaNotas = fopen("Notas.txt", "a");
	
	if (!listaNotas){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuNotas();
		
		return;
	}
	
	Aluno aluno;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &aluno.id);
	
	switch(verificarID(aluno.id)){
		case 0:
			printf("ID nao cadastrado\n\n");
		break;
		
		case 1:{
			printf("Qual a materia?: \n\n");
	
			printf("1 - Historia\n");
			printf("2 - Filosofia\n");
			printf("3 - Sociologia\n");
			printf("4 - Geografia\n");
			printf("5 - Fisica\n");
			printf("6 - Matematica\n");
			printf("7 - Quimica\n");
			printf("8 - Biologia\n\n");
			
			int opcao;
			
			do {
				printf("Opcao: ");
				scanf("%d", &opcao);
				
				switch(opcao){
					case 1:
						strcpy(aluno.nota.materia, "Historia");
					break;
					
					case 2:
						strcpy(aluno.nota.materia, "Filosofia");
					break;
					
					case 3:
						strcpy(aluno.nota.materia, "Sociologia");
					break;
					
					case 4:
						strcpy(aluno.nota.materia, "Geografia");
					break;
					
					case 5:
						strcpy(aluno.nota.materia, "Fisica");
					break;
					
					case 6:
						strcpy(aluno.nota.materia, "Matematica");
					break;
					
					case 7:
						strcpy(aluno.nota.materia, "Quimica");
					break;
					
					case 8:
						strcpy(aluno.nota.materia, "Biologia");
					break;
					
					default:
						printf("Opcao invalida!\n\n");
					break;
				}	
			} while (opcao < 1 || opcao > 8);
			
			switch(verificarNota(aluno.id, aluno.nota.materia)){
				case 0:
					fflush(stdin);
					
					do { 
						printf("Qual a primeira nota?: ");
						scanf("%f", &aluno.nota.n1);
					} while (aluno.nota.n1 < 0 || aluno.nota.n1 > 10);
					
					
					do { 
						printf("Qual a segunda nota?: ");
						scanf("%f", &aluno.nota.n2);
					} while (aluno.nota.n2 < 0 || aluno.nota.n2 > 10);
					
					aluno.nota.media = (aluno.nota.n1 + aluno.nota.n2)/2;
			
					fprintf(listaNotas, "%d|%s|%f|%f|%f\n", aluno.id, aluno.nota.materia, aluno.nota.n1, aluno.nota.n2, aluno.nota.media);
					
					printf("Nota cadastrada!\n\n");
					
					qntdNotas++;
				break;
				
				case 1:
					printf("Nota ja cadastrada\n\n");
				break;
			}
		}
		
		break;
	
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaNotas);
	
	system("pause");
	
	menuNotas();
}

void alterarNota(){
	system("cls");
	
	printf("ALTERACAO DE NOTA\n\n");
	
	FILE *listaNotas = fopen("Notas.txt", "r");
	
	if (!listaNotas){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuNotas();
		
		return;
	}
	
	Aluno aluno;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &aluno.id);
	
	switch(verificarID(aluno.id)){
		case 0:
			printf("ID nao cadastrado\n\n");
		break;
		
		case 1:{
			fflush(stdin);
			
			printf("Qual a materia?: \n\n");
	
			printf("1 - Historia\n");
			printf("2 - Filosofia\n");
			printf("3 - Sociologia\n");
			printf("4 - Geografia\n");
			printf("5 - Fisica\n");
			printf("6 - Matematica\n");
			printf("7 - Quimica\n");
			printf("8 - Biologia\n\n");
			
			int opcao;
			
			do {
				printf("Opcao: ");
				scanf("%d", &opcao);
				
				switch(opcao){
					case 1:
						strcpy(aluno.nota.materia, "Historia");
					break;
					
					case 2:	
						strcpy(aluno.nota.materia, "Filosofia");
					break;
					
					case 3:
						strcpy(aluno.nota.materia, "Sociologia");
					break;
					
					case 4:
						strcpy(aluno.nota.materia, "Geografia");
					break;
					
					case 5:
						strcpy(aluno.nota.materia, "Fisica");
					break;
					
					case 6:
						strcpy(aluno.nota.materia, "Matematica");
					break;
					
					case 7:
						strcpy(aluno.nota.materia, "Quimica");
					break;
					
					case 8:
						strcpy(aluno.nota.materia, "Biologia");
					break;
					
					default:
						printf("Opcao invalida!\n\n");
					break;
				}	
			} while (opcao < 1 || opcao > 8);
			
			switch(verificarNota(aluno.id, aluno.nota.materia)){
				case 0:
					printf("Nota nao cadastrada!\n\n");
				break;
				
				case 1: {
					do { 
						printf("Qual a primeira nota?: ");
						scanf("%f", &aluno.nota.n1);
					} while (aluno.nota.n1 < 0 || aluno.nota.n1 > 10);
					
					
					do { 
						printf("Qual a segunda nota?: ");
						scanf("%f", &aluno.nota.n2);
					} while (aluno.nota.n2 < 0 || aluno.nota.n2 > 10);
					
					aluno.nota.media = (aluno.nota.n1 + aluno.nota.n2)/2;
					
					Aluno estudantes[qntdNotas];
			
					int cont = 0;
					
					while(fscanf(listaNotas, "%d|%20[^|]|%f|%f|%f", &estudantes[cont].id, estudantes[cont].nota.materia, &estudantes[cont].nota.n1, &estudantes[cont].nota.n2, &estudantes[cont].nota.media) == 5){
						if ((aluno.id == estudantes[cont].id) && (strcmp(aluno.nota.materia, estudantes[cont].nota.materia) == 0)){
							estudantes[cont] =  aluno;
						}
						
						cont++;	
					}	
					
					FILE *listaNotasNova = fopen("Notas.txt", "w");
			
					int i;
					
					for (i = 0; i < cont; i++){
						fprintf(listaNotasNova, "%d|%s|%f|%f|%f\n", estudantes[i].id, estudantes[i].nota.materia, estudantes[i].nota.n1, estudantes[i].nota.n2, estudantes[i].nota.media);
					}
					
					fclose(listaNotasNova);
					
					printf("Alteracoes bem sucedidas!\n\n");
				}
				
				break;
			}	
		}	
	
		break;
		
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaNotas);
	
	system("pause");
	
	menuNotas();
}

void removerNota(){
	system("cls");
	
	printf("REMOCAO DE NOTA\n\n");
	
	FILE *listaNotas = fopen("Notas.txt", "r");
	
	if (!listaNotas){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuNotas();
		
		return;
	}
	
	int idRemovido;
	char materiaRemovida[21];
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &idRemovido);
	
	switch(verificarID(idRemovido)){
		case 0:
			printf("ID nao cadastrado\n\n");
		break;
		
		case 1:{
			fflush(stdin);
			
			printf("Qual a materia?: \n\n");
	
			printf("1 - Historia\n");
			printf("2 - Filosofia\n");
			printf("3 - Sociologia\n");
			printf("4 - Geografia\n");
			printf("5 - Fisica\n");
			printf("6 - Matematica\n");
			printf("7 - Quimica\n");
			printf("8 - Biologia\n\n");
			
			int opcao;
			
			do {
				printf("Opcao: ");
				scanf("%d", &opcao);
				
				switch(opcao){
					case 1:
						strcpy(materiaRemovida, "Historia");
					break;
					
					case 2:	
						strcpy(materiaRemovida, "Filosofia");
					break;
					
					case 3:
						strcpy(materiaRemovida, "Sociologia");
					break;
					
					case 4:
						strcpy(materiaRemovida, "Geografia");
					break;
					
					case 5:
						strcpy(materiaRemovida, "Fisica");
					break;
					
					case 6:
						strcpy(materiaRemovida, "Matematica");
					break;
					
					case 7:
						strcpy(materiaRemovida, "Quimica");
					break;
					
					case 8:
						strcpy(materiaRemovida, "Biologia");
					break;
					
					default:
						printf("Opcao invalida!\n\n");
					break;
				}	
			} while (opcao < 1 || opcao > 8);
			
			switch(verificarNota(idRemovido, materiaRemovida)){
				case 0:
					printf("Nota nao cadastrada!\n\n");
				break;
				
				case 1: {
					fflush(stdin);
			
					Aluno aluno;
					
					Aluno estudantes[qntdNotas];
					
					int cont = 0;
				
					while(fscanf(listaNotas, "%d|%20[^|]|%f|%f|%f", &aluno.id, aluno.nota.materia, &aluno.nota.n1, &aluno.nota.n2, &aluno.nota.media) == 5){
						if ((idRemovido != aluno.id) || (strcmp(materiaRemovida, aluno.nota.materia) != 0)){
							estudantes[cont] = aluno;
							
							cont++;
						}
					}	
					
					FILE *listaNotasNova = fopen("Notas.txt", "w");
			
					int i;
					
					for (i = 0; i < cont; i++){
						fprintf(listaNotasNova, "%d|%s|%f|%f|%f\n", estudantes[i].id, estudantes[i].nota.materia, estudantes[i].nota.n1, estudantes[i].nota.n2, estudantes[i].nota.media);
					}
					
					fclose(listaNotasNova);
					
					printf("Remocao de nota bem sucedida!\n\n");
					
					qntdNotas--;
				}
				
				break;
			}	
		}	
	
		break;
		
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaNotas);
	
	system("pause");
	
	menuNotas();	
}

void listarNota(){
	system("cls");
	
	printf("LISTAGEM DO BOLETIM\n\n");
	
	FILE *listaAlunos = fopen("Alunos.txt", "r");
	FILE *listaNotas = fopen("Notas.txt", "r");
			
	if ((!listaAlunos) || (!listaNotas)){
		printf("Erro na abertura do arquivo!\n");
		system("pause");
		
		menuNotas();
		
		return;
	}
		
	int idProcurado;
	
	printf("Qual o ID do estudante?: ");
	scanf("%d", &idProcurado);
	
	switch(verificarID(idProcurado)){
		case 0:
			printf("ID nao cadastrado\n\n");
		break;
		
		case 1:{
			fflush(stdin);
			
			Aluno aluno;
			
			while (fscanf(listaAlunos, "%d|%60[^|]|%*d/%*d/%*d|%*d", &aluno.id, aluno.nome) == 2) {
				if (idProcurado == aluno.id) {
				    break;
				}
			}
			
			printf("\nBoletim escolar: \n");
			printf("ID: %d\n", aluno.id);
			printf("Aluno: %s\n\n", aluno.nome);
			
			printf("MATERIA           | NOTA 1 | NOTA 2 | MEDIA FINAL | RESULTADO\n");
			printf("-------------------------------------------------------------\n");
			
			while(fscanf(listaNotas, "%*d|%20[^|]|%f|%f|%f", aluno.nota.materia, &aluno.nota.n1, &aluno.nota.n2, &aluno.nota.media) == 4){
				char resultado[] = "Aprovado";
				
				if (aluno.nota.media < 6){
					strcpy(resultado, "Reprovado");
				}
				
				printf("%s", aluno.nota.materia);
				
				int numeroEspacos = 18 - strlen(aluno.nota.materia);
				
				int i;
				
				for (i = 0; i < numeroEspacos; i++){
					printf(" ");
				}	
				
				printf("| %.2f   | %.2f   |     %.2f    | %s\n", aluno.nota.n1, aluno.nota.n2, aluno.nota.media, resultado);
			}
			
			printf("\n");	
		}
		
		break;
		
		case 2:
			printf("ID invalido\n\n");
		break;
	}
	
	fclose(listaAlunos);
	fclose(listaNotas);
	
	system("pause");
	
	menuNotas();
}
