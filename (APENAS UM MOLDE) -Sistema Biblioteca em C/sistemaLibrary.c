#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

#define MAX_TITULO 100
#define MAX_AUTOR 100

typedef struct {
	int id;
	char titulo[MAX_TITULO];
	char autor[MAX_AUTOR];
} Livro;


void adicionarLivro();
void listarLivros();
void buscarLivro();
void removerLivro();

int main(){
	
	setlocale(LC_ALL, "Portuguese");
	
	int opcao;
	
	do {
		system("cls");
		
		printf("Sistema de biblioteca - por Mr JeeJ\n\n");
		printf("1 - Adicionar livro\n");
		printf("2 - Listar livros\n");
		printf("3 - Buscar livro\n");
		printf("4 - Remover livro\n");
		printf("0 - Sair\n\n");
		printf("Escolha uma op��o: ");
		scanf("%d", &opcao); 
		
		switch(opcao){
			case 1:
				adicionarLivro();
				break;
			case 2:
				listarLivros();
				break;
			case 3:	
				buscarLivro();
				break;			
			case 4:
				removerLivro();
				break;
			case 0:
				printf("Saindo...\n");
				break;
			default:	
				printf("Op��o inv�lida!\n");
		}
		
	} while (opcao);
	
	return 0;
}

void adicionarLivro(){
	system("cls");
	
	FILE *file = fopen("biblioteca.txt", "a+");
	
	if (!file){
		printf("Erro ao abrir o arquivo!\n");
		return;
	}
	
	Livro livro;
	
	printf("ID do livro: ");
	scanf("%d", &livro.id);
	
	getchar();
	
	int repetido = 0;
	int idExistente;
	
	rewind(file);  //Nesse modo, focado em concatenar, o ponteiro fica no final do arquivo, por isso o rewind
	
	while (fscanf(file, "%d|%*[^|]|%*[^\n]", &idExistente) == 1){
		if (livro.id == idExistente){
			repetido = 1;
			break;
		}
	}
	
	if (repetido){
		printf("ID j� cadastrado!");
	} else {
		printf("T�tulo: ");
		fgets(livro.titulo, MAX_TITULO, stdin);
		
		strtok(livro.titulo, "\n"); //Remove o \n como delimitador
		
		printf("Autor: ");
		fgets(livro.autor, MAX_AUTOR, stdin);
		
		strtok(livro.autor, "\n"); //Remove o \n o ajustando como delimitador
		
		fprintf(file, "%d|%s|%s\n", livro.id, livro.titulo, livro.autor);
		
		printf("\nLivro adicionado com sucesso!");
	}
	
	fclose(file);
	
	sleep(1);
}

void listarLivros(){
	FILE *file = fopen("biblioteca.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Livro livro;
    printf("Lista de livros:\n");
    
    //Esse [^|] quer dizer ler at� 99 caracteres at� encontrar o |
    
    while (fscanf(file, "%d|%99[^|]|%99[^\n]", &livro.id, livro.titulo, livro.autor) == 3){
    	printf("ID: %d, T�tulo: %s, Autor: %s\n", livro.id, livro.titulo, livro.autor);
	}
 	
	sleep(3);   
}
void buscarLivro(){
	FILE *file = fopen("biblioteca.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    printf("Qual o ID do livro?: ");
    int id;
    scanf("%d", &id);
    
    Livro livro;
    
    while (fscanf(file, "%d|%99[^|]|%99[^\n]", &livro.id, livro.titulo, livro.autor) == 3){
    	if (livro.id == id){
    		printf("Livro encontrado: ID: %d, T�tulo: %s, Autor: %s\n", livro.id, livro.titulo, livro.autor);
    		
    		sleep(3);
    		
    		fclose(file);
    		return;
		} 
	}
}

void removerLivro() {
    FILE *file = fopen("biblioteca.txt", "r");
    if (!file) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    int id, encontrado = 0;
    printf("Digite o ID do livro que deseja remover: ");
    scanf("%d", &id);
    getchar();  // Evita problemas com buffer

    // Criamos um buffer para armazenar os dados que queremos manter
    Livro livros[100]; // Supondo no m�ximo 100 livros, pode ser ajustado
    int count = 0;

    Livro livro;
    while (fscanf(file, "%d|%99[^|]|%99[^\n]", &livro.id, livro.titulo, livro.autor) == 3) {
        if (livro.id == id) {
            encontrado = 1; // Marcamos que o livro foi encontrado
        } else {
            livros[count++] = livro; 
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Livro n�o encontrado.\n");
        return;
    }

    file = fopen("biblioteca.txt", "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

	int i;

    for (i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s\n", livros[i].id, livros[i].titulo, livros[i].autor);
    }

    fclose(file);

    printf("Livro removido com sucesso!\n");
}
