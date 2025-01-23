#include <stdio.h>
#include <locale.h>
#include <conio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int contDuelo = 1;
int pontosCPU = 0;
int pontosPlayer = 0;
int pRecarregado = 0; 
int mRecarregado = 0;

int escolhaJogador(){
	printf("O que o jogador fará?: \n\n");
	
	printf("(1) Recarregar\n");
	printf("(2) Defender\n");
	
	if (pRecarregado){
		printf("(3) Atirar\n");
	}
	
	char tecla = getch();
	
	printf("\n");
	
	switch(tecla){
		case '1':
			printf("PLAYER recarregou!");
			pRecarregado = 1;
			return 1;
		break;
		
		case '2':
			printf("PLAYER defendeu!");
			return 2;
		break;
		
		case '3':
			if (pRecarregado){
				printf("PLAYER atirou!");
				pRecarregado = 0;
				return 3;
			} else {
				printf("PLAYER não tem balas");
				return 4;
			}	
		
		break;
			
		default:
			printf("PLAYER não fez nada");
			return 0;
		break;
	}	
}

int escolhaMaquina(){
	int escolha;

	if (!mRecarregado){
		escolha = (rand() % 2) + 1;	
	} else {
		escolha = (rand() % 3) + 1;
	}
	
	switch(escolha){
		case 1:
			printf("CPU recarregou!");
			mRecarregado = 1;
			return 1;
		break;
		
		case 2:
			printf("CPU defendeu!");
			return 2;
		break;
		
		case 3:
			printf("CPU atirou!");
			mRecarregado = 0;
			return 3;
		break;
	}
}

int duelo(int pEscolha, int mEscolha){
	if (pEscolha == 3 && mEscolha == 3){
		return 1;
	} else {
		if (pEscolha == 3 && mEscolha == 1){
			return 2;
		}
		
		if (mEscolha == 3 && (pEscolha == 1 || pEscolha == 4 || pEscolha == 0)){
			return 3;
		}
	}
	
	return 0; //Precisa estar aqui para que não hajam valores imprevisíveis no duelo()
}

void gerarResultado(){
	int pEscolha = escolhaJogador(&pRecarregado);
	
	printf(" X ");
	
	int mEscolha = escolhaMaquina(&mRecarregado);
	
	printf("\n\n");
	
	int resultadoDuelo = duelo(pEscolha, mEscolha);
		
	if (resultadoDuelo){
		switch(resultadoDuelo){
			case 1:
				printf("EMPATE - OS DOIS MORRERAM!");
				contDuelo++;
			break;
			
			case 2:
				printf("JOGADOR VENCEU!!");
				contDuelo++;
				pontosPlayer++;
			break;
			
			case 3:
				printf("JOGADOR PERDEU");
				contDuelo++;
				pontosCPU++;
			break;
		}
		
		mRecarregado = 0;
		pRecarregado = 0;	
		
		printf("\n\n");
	}
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));
	
	int numeroRodadas;
	
	printf("Quantas rodadas?: ");
	scanf("%d", &numeroRodadas);

	printf("\n");
	
	while (contDuelo <= numeroRodadas){
		system("cls");
		
		printf("DUELO n°%d  \n\n", contDuelo);
	
		gerarResultado();
		
		printf("PLACAR - ( %d  X  %d )", pontosPlayer, pontosCPU);
		
		sleep(1);
	}
	
	return 0;
}
