#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int acessoPermitido;
int tentativas = 3;

char usuarioAtual[10][50];
char senhaAtual[10][50];

int chavesCriptoSenha[10];
char senhaCriptografada[50];

char usuarioDigitado[50];
char senhaDigitada[50];

int espacosDisponiveis = 10;

void limparTela();
void gerarChavesCriptografia();
void criptografarSenha(char senhaDigitada[50], char senhaCriptografada[50], int casa);
void realizarLogin();
void validarLogin();
void mostrarMenu();

void listarUsuarios();
void cadastrarUsuarios();
void alterarUsuarios();
void removerUsuarios();
void voltarProLogin();

void gravarNoArquivo();
void lerDoArquivo();

int main() {
    setlocale(LC_ALL, "Portuguese");

    lerDoArquivo(); 
    if (espacosDisponiveis == 10) {
        gerarChavesCriptografia(); 
        mostrarMenu();
    } else {
        realizarLogin();
    }

    return 0;
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void gerarChavesCriptografia() {
    srand(time(NULL));
    
    int casa;
	
	for (casa = 0; casa < 10; casa++) {
        chavesCriptoSenha[casa] = (rand() % 20) + 1;
    }
}

void criptografarSenha(char senhaDigitada[50], char senhaCriptografada[50], int casa) {
    int i;

    for (i = 0; i < strlen(senhaDigitada); i++) {
        senhaCriptografada[i] = senhaDigitada[i] + chavesCriptoSenha[casa];
    }
    senhaCriptografada[i] = '\0';
}

void realizarLogin() {
    limparTela();

    acessoPermitido = 0;

    usuarioDigitado[0] = '\0';
    senhaDigitada[0] = '\0';

    printf("Sistema de gerenciamento de usu�rios\n\n");

    printf("Usu�rio (SEM ESPA�OS): ");
    scanf("%s", usuarioDigitado);

    printf("Senha (SEM ESPA�OS): ");
    scanf("%s", senhaDigitada);

    validarLogin();
}

void validarLogin() {
    int espacoChaveCripto;

    for (espacoChaveCripto = 0; espacoChaveCripto < 10; espacoChaveCripto++) {
        criptografarSenha(senhaDigitada, senhaCriptografada, espacoChaveCripto);

        if ((strcmp(usuarioAtual[espacoChaveCripto], usuarioDigitado) == 0) && (strcmp(senhaAtual[espacoChaveCripto], senhaCriptografada) == 0)) {
            acessoPermitido = 1;
            break;
        }
    }

    if (acessoPermitido) {
        mostrarMenu();
    } else {
        tentativas--;

        if (tentativas > 0) {
            printf("\nCadastro incorreto - %d tentativa(s) restando", tentativas);
            sleep(2);
            realizarLogin();
        } else {
            printf("\nTentativas esgotadas - Cadastro bloqueado");
            exit(0);
        }
    }
}

void mostrarMenu() {
    limparTela();

    int opcao;

    printf("1 - Listagem de usu�rios\n");
    printf("2 - Cadastro de usu�rios\n");
    printf("3 - Altera��o de usu�rios\n");
    printf("4 - Remo��o de usu�rios\n");
    printf("5 - Voltar pro login\n\n");

    printf("Op��o: ");
    scanf("%d", &opcao);

    limparTela();

    switch(opcao) {
        case 1:
            listarUsuarios();
        break;

        case 2:
            cadastrarUsuarios();
        break;

        case 3:
            alterarUsuarios();
        break;

        case 4:
            removerUsuarios();
        break;

        case 5:
            voltarProLogin();
        break;
    }
}

void listarUsuarios() {
    printf("Lista de usu�rios cadastrados: \n\n");

    int vazio = 1;
	int i;

    for (i = 0; i < 10; i++) {
        if (strcmp(usuarioAtual[i], "") != 0) {
            printf("%d- %s\n", i, usuarioAtual[i]);
            vazio = 0;
        }
    }

    if (vazio) {
        printf("Sem usu�rios cadastrados!");
    }

    sleep(2);
    mostrarMenu();
}

void cadastrarUsuarios() {
    int espacoCadastro;

    printf("Espa�os dispon�veis: %d\n", espacosDisponiveis);
    printf("Qual espa�o vai utilizar para o cadastro (0-9)?: ");
    scanf("%d", &espacoCadastro);

    if ((espacoCadastro < 0) || (espacoCadastro > 9)) {
        printf("\nEspa�o inv�lido!");
    } else {
        if (strcmp(usuarioAtual[espacoCadastro], "") == 0) {
            printf("Usu�rio (SEM ESPA�OS): ");
            scanf("%s", &usuarioAtual[espacoCadastro]);

            printf("Senha (SEM ESPA�OS): ");
            scanf("%s", &senhaDigitada);

            criptografarSenha(senhaDigitada, senhaCriptografada, espacoCadastro);

            strcpy(senhaAtual[espacoCadastro], senhaCriptografada);

            espacosDisponiveis--;

            printf("\nUsu�rio cadastrado!");
            gravarNoArquivo();  
        } else {
            printf("\nEspa�o j� cadastrado!");
        }
    }

    sleep(2);
    mostrarMenu();
}

void alterarUsuarios() {
    int espacoAlterado;

    printf("Qual usu�rio ser� alterado (0-9)?: ");
    scanf("%d", &espacoAlterado);

    if ((espacoAlterado < 0) || (espacoAlterado > 9)) {
        printf("\nEspa�o inv�lido!");
    } else {
        if (strcmp(usuarioAtual[espacoAlterado], "") == 0) {
            printf("\nUsu�rio n�o cadastrado!");
        } else {
            printf("Usu�rio (SEM ESPA�OS): ");
            scanf("%s", &usuarioAtual[espacoAlterado]);

            printf("Senha (SEM ESPA�OS): ");
            scanf("%s", &senhaDigitada);

            criptografarSenha(senhaDigitada, senhaCriptografada, espacoAlterado);

            strcpy(senhaAtual[espacoAlterado], senhaCriptografada);

            printf("\nUsu�rio alterado!");

            gravarNoArquivo();
        }
    }

    sleep(2);
    mostrarMenu();
}

void removerUsuarios() {
    int espacoRemovido;

    printf("Qual usu�rio ser� removido (0-9)?: ");
    scanf("%d", &espacoRemovido);

    if ((espacoRemovido < 0) || (espacoRemovido > 9)) {
        printf("\nEspa�o inv�lido!");
    } else {
        if (strcmp(usuarioAtual[espacoRemovido], "") == 0) {
            printf("\nUsu�rio n�o cadastrado!");
        } else {
            strcpy(usuarioAtual[espacoRemovido], "");
            strcpy(senhaAtual[espacoRemovido], "");

            espacosDisponiveis++;

            printf("\nUsu�rio removido!");

            gravarNoArquivo(); 
        }
    }

    sleep(2);
    mostrarMenu();
}

void voltarProLogin() {
    if (espacosDisponiveis == 10) {
        printf("Cadastre um usu�rio primeiro!");

        sleep(2);
        mostrarMenu();
    } else {
        tentativas = 3;
        realizarLogin();
    }
}

void gravarNoArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro na grava��o dos dados!\n");
        return;
    }

    fprintf(arquivo, "%d\n", espacosDisponiveis);

    int i;
	
	for (i = 0; i < 10; i++) {
        fprintf(arquivo, "%d ", chavesCriptoSenha[i]);
    }
    fprintf(arquivo, "\n");

    for (i = 0; i < 10; i++) {
        fprintf(arquivo, "%s %s\n", usuarioAtual[i], senhaAtual[i]);
    }

    fclose(arquivo);
}

void lerDoArquivo() {
    FILE *arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro na leitura do arquivo!\n");
        return;
    }

    fscanf(arquivo, "%d\n", &espacosDisponiveis);

    int i;
	
	for (i = 0; i < 10; i++) {
        fscanf(arquivo, "%d ", &chavesCriptoSenha[i]);
    }
    fscanf(arquivo, "\n");
	
	for (i = 0; i < 10; i++) {
        fscanf(arquivo, "%s %s\n", usuarioAtual[i], senhaAtual[i]);
    }

    fclose(arquivo);
}
