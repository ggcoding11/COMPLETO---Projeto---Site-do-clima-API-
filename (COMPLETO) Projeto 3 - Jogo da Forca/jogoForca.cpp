#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

using namespace std;

char palavras[][50] = { "carro", "aviao", "banana", "cachorro", "computador", "janela", "guitarra", "oceano", "montanha", "bicicleta",  
	"elefante", "telefone", "historia", "caderno", "caneta", "churrasco", "diamante", "esmeralda", "girassol", "hotel",  
	"ilha", "jardim", "lixeira", "morango", "navio", "oculos", "pinguim", "quadro", "raquete", "sabonete",  
	"tapete", "universo", "violino", "xadrez", "zebra", "abacaxi", "borboleta", "cavalo", "dragao", "escada",  
	"foguete", "gorila", "helicoptero", "igreja", "jiboia", "koala", "lampada", "maracuja", "nuvem", "ornitorrinco"
};

int qntdPalavras = sizeof(palavras)/ sizeof(palavras[0]);
char palavraEscolhida[50];
int escolhaCPU;
int tamanhoPalavra;
char espacoVazio[50];
char letrasErradas[50];
int contLetrasErradas;
int vitoriasConsec;
int palavrasRestantes;

void iniciarJogo();
void escolherPalavra();
void escreverTracejado();
void mostrarErros();
void desenharBoneco();
void verificarTentativa();
void mostrarResultado();

int main(){
	
	srand(time(NULL));
	
	setlocale(LC_ALL, "Portuguese");
	
	vitoriasConsec = 0;
	
	palavrasRestantes = qntdPalavras;
	
	iniciarJogo();
	
	return 0;
}

void iniciarJogo(){
	escolherPalavra();
	
	escreverTracejado();
	
	contLetrasErradas = 0;
	
	while (strcmp(espacoVazio, palavraEscolhida) && contLetrasErradas < 6){
		cout << "JOGO DE FORCA - Feito por Mr JeeJ" << endl << endl;
		
		desenharBoneco();
		
		cout << endl << endl << espacoVazio << endl;
	
		mostrarErros();
		
		verificarTentativa();		
		
		system("cls");
	}
	
	mostrarResultado();
	
	if (palavrasRestantes == 0){
		cout << endl << "Jogo zerado - Muito obrigado por jogar!";	
	} else {
	
		char opcao;
	
		do {
			cout << endl << "Iniciar outra rodada? [s/n]: ";
		
			cin >> opcao;	
		} while (opcao != 's' && opcao != 'n');
		
		if (opcao == 's'){
			system("cls");
			iniciarJogo();
		}	
	}
}

void escolherPalavra(){
	do {
		escolhaCPU = rand() % qntdPalavras;
	} while (strcmp(palavras[escolhaCPU], "") == 0);
	
	strcpy(palavraEscolhida, palavras[escolhaCPU]);
	
	tamanhoPalavra = strlen(palavraEscolhida);
	
	palavraEscolhida[tamanhoPalavra] = '\0'; //Removi o terminador para comparar as duas palavras;
}

void escreverTracejado(){	
	for (int i = 0; i < tamanhoPalavra; i++){
		espacoVazio[i] = '_';
	} 
	
	espacoVazio[tamanhoPalavra] = '\0'; //Adiciona o terminador na última casa
}

void desenharBoneco(){
	switch(contLetrasErradas){
		case 1:
			cout << "    _____    " << endl;
			cout << "   |     |   " << endl;
			cout << "   |     O   " << endl;
			cout << "   |         " << endl;
			cout << "   |         " << endl;
			cout << "   |         " << endl;
			cout << "  ----       " << endl;
		break;
		
		case 2:
			cout << "    _____    " << endl;
			cout << "   |     |   " << endl;
			cout << "   |     O   " << endl;
			cout << "   |     |    " << endl;
			cout << "   |         " << endl;
			cout << "   |         " << endl;
			cout << "  ----       " << endl;
		break;
		
		case 3:
			cout << "    _____    " << endl;
			cout << "   |     |   " << endl;
			cout << "   |     O   " << endl;
			cout << "   |    /|   " << endl;
			cout << "   |         " << endl;
			cout << "   |         " << endl;
			cout << "  ----       " << endl;
		break;
		
		case 4:
			cout << "    _____    " << endl;
			cout << "   |     |   " << endl;
			cout << "   |     O   " << endl;
			cout << "   |    /|\\ " << endl;
			cout << "   |         " << endl;
			cout << "   |         " << endl;
			cout << "  ----       " << endl;
		break;
		
		case 5:
			cout << "    _____    " << endl;
			cout << "   |     |   " << endl;
			cout << "   |     O   " << endl;
			cout << "   |    /|\\ " << endl;
			cout << "   |    /    " << endl;
			cout << "   |         " << endl;
			cout << "  ----       " << endl;
		break;
		
		case 6:
			cout << "    _____    " << endl;
			cout << "   |     |   " << endl;
			cout << "   |     O   " << endl;
			cout << "   |    /|\\ " << endl;
			cout << "   |    / \\ " << endl;
			cout << "   |         " << endl;
			cout << "  ----       " << endl;
		break;
	}
}

void mostrarErros(){
	cout << endl << endl << "Erros: "; 
		
	for (int i = 0; i < contLetrasErradas; i++){
		
		if (!i){
			cout << letrasErradas[i];
		} else {
			cout << ", " << letrasErradas[i];
		}
	}
}

void verificarTentativa(){
	char caractereTentativa;
	
	cout << endl << "Tentativa: ";
	cin >> caractereTentativa;
	
	caractereTentativa = tolower(caractereTentativa);
	
	if (isalpha(caractereTentativa)){
		int acertouLetra = 0;
	
		for (int i = 0; i < tamanhoPalavra; i++){
			if (caractereTentativa == palavraEscolhida[i]){
				espacoVazio[i] = caractereTentativa;
				acertouLetra = 1;
			}
		}
		
		if (!acertouLetra){
			int erroRepetido = 0;
			
			for (int i = 0; i < contLetrasErradas; i++){
				if (caractereTentativa == letrasErradas[i]){
					erroRepetido = 1;
				}
			}
			
			if (!erroRepetido){
				letrasErradas[contLetrasErradas] = caractereTentativa;
				letrasErradas[contLetrasErradas + 1] = '\0';		
				contLetrasErradas++;	
			}
		}	
	}
}

void mostrarResultado(){
	if (contLetrasErradas == 6){
		desenharBoneco();
				
		cout << endl << "Perdeu! - Fim de jogo";
		
		vitoriasConsec = 0;
	} else {
		cout << "PALAVRA FINAL: " << espacoVazio << endl << endl;
	
		cout << "Acertou! - Fim de jogo" << endl;
		
		vitoriasConsec++;
		
		cout << "Vitorias consecutivas: " << vitoriasConsec << endl;
		
		strcpy(palavras[escolhaCPU], "");
		
		palavrasRestantes--;
	}
}
