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

int escolhaJogador();
int escolhaMaquina();
int duelo(int pEscolha, int mEscolha);
void gerarResultado();
void limpaTela();

int main(){
	setlocale(LC_ALL, "Portuguese");
	srand(time(NULL));
	
	int numeroRodadas;
	
	do {
		limpaTela();
		
		printf("Jogo do DEFENDER, RECARREGAR E ATIRAR\n\n");
	
		printf("Quantos duelos serão realizados?: ");
		scanf("%d", &numeroRodadas);
	} while (numeroRodadas <= 0);
	
	printf("\n");
	
	while (contDuelo <= numeroRodadas){
		limpaTela();
		
		printf("DUELO n°%d  \n\n", contDuelo);
	
		gerarResultado();
	}
	
	limpaTela();
	
	printf("Resultado final: ");
	
	if (pontosPlayer > pontosCPU){
		printf("Jogador venceu o jogo!");
	} else {
		if (pontosPlayer < pontosCPU){
			printf("CPU venceu o jogo!");
		} else {
			printf("Empate no jogo!");
		}
	}
	
	return 0;
}

void limpaTela() {
    system("cls"); // Limpa a tela no Windows
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
				printf("RODADA EMPATADA!");
			break;
			
			case 2:
				printf("JOGADOR VENCEU A RODADA!!");
				pontosPlayer++;
			break;
			
			case 3:
				printf("JOGADOR PERDEU A RODADA");
				pontosCPU++;
			break;
		}
		
		mRecarregado = 0;
		pRecarregado = 0;	
		
		printf("\n\n");
		
		printf("PLACAR - ( %d  X  %d )\n\n", pontosPlayer, pontosCPU);
		
		contDuelo++;
	}
	
	printf("Pressione qualquer tecla para continuar...");
	getch();
}

int escolhaJogador(){
	printf("O que o jogador fará?: \n\n");
	
	if (!pRecarregado){
		printf("(1) Recarregar\n");
	}
	
	printf("(2) Defender\n");
	
	if (pRecarregado){
		printf("(3) Atirar\n");
	}
	
	char tecla = getch();
	
	printf("\n");
	
	switch(tecla){
		case '1':
			if (!pRecarregado){
				printf("PLAYER recarregou!");
				pRecarregado = 1;
			} else {
				printf("PLAYER já está carregado!");
			}
	
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
		escolha = (rand() % 2) + 2;
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
		return 1; //Empate
	}
	
	if (pEscolha == 3 && mEscolha != 2){
		return 2; //Jogador vence
	}
		
	if (mEscolha == 3 && pEscolha != 2){
		return 3; //Máquina vence
	}
	
	return 0; //Precisa estar aqui para que não hajam valores imprevisíveis no duelo()
}
