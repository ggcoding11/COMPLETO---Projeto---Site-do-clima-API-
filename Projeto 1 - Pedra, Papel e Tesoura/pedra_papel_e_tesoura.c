#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void gerarResposta(int opcao, char resposta[30]){
	switch(opcao){
		case 1:
			strcpy(resposta, "Pedra");
		break;
		
		case 2:
			strcpy(resposta, "Papel");
		break;
		
		case 3:
			strcpy(resposta, "Tesoura");
		break;
	}
}

void realizarDuelo(char j1[30], char j2[30]){
	printf(" %s      X      %s\n", j1, j2);
	printf("(Player)          (Maquina)\n\n");
	
	if (!(strcmp(j1, j2))){
		printf("          EMPATE!\n");
	} else {
		if ((strcmp(j1, "Tesoura") == 0 && strcmp(j2, "Pedra") == 0) || 
            (strcmp(j1, "Pedra") == 0 && strcmp(j2, "Papel") == 0) || 
            (strcmp(j1, "Papel") == 0 && strcmp(j2, "Tesoura") == 0)) {
        	printf("     Maquina vence!\n");
        } else {
			printf("     Jogador vence!\n");
		}
	}
}

int main(){
	srand(time(NULL));
	
	int opcaoPlayer, opcaoCPU;
	char jogadaPlayer[30], jogadaCPU[30];
	char reiniciar;
	
	do {
		do { 
			limparTela();
					
			printf("PEDRA, PAPEL E TESOURA, por JeeJ\n\n");
		
			printf("Prepare - se...\n\n");
			
			printf("1 - Pedra\n");
			printf("2 - Papel\n");
			printf("3 - Tesoura\n\n");
			
			printf("Opcao: ");
			scanf("%d", &opcaoPlayer);
			
			printf("\n");
		} while ((opcaoPlayer < 1) || (opcaoPlayer > 3));
		
		gerarResposta(opcaoPlayer, jogadaPlayer);
		
		opcaoCPU = (rand() % 3) + 1;
		
		gerarResposta(opcaoCPU, jogadaCPU);
		
		realizarDuelo(jogadaPlayer, jogadaCPU);
		
		printf("\n");
		
		getchar();
		
		printf("Recomecar? [S/N]: ");
		scanf("%c", &reiniciar);	
	} while (reiniciar == 'S' || reiniciar == 's');
	
	return 0;
}
