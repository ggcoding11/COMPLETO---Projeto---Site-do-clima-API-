#include <iostream>
#include <stdio.h>

void preencherMatriz(int matriz[][50], int N){
	
	int Ltopo = 0;
	int Lbaixo = N-1;
	int Cesquerda = 0;
	int Cdireita = N-1;
	
	int num;
	
	int cont = 0;
	
	while (cont < (N * N)){
		
		//Esquerda para a direita
		for (int i = Cesquerda; i < Cdireita; i++){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[Ltopo][i] = num;
			cont++;
		}
		
		
		
		//Cima pra baixo
		for (int i = Ltopo; i < Lbaixo; i++){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[i][Cdireita] = num;
			cont++;
		}
		
		
		
		//Direita para a esquerda
		
		for (int i = Cdireita; i > Cesquerda; i--){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[Lbaixo][i] = num;
			cont++;
		}
		
		
		
		//Baixo para cima
		
		for (int i = Lbaixo; i > Ltopo; i--){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[i][Cesquerda] = num;
			cont++;	
		}
		
		Ltopo++;
		
		Cdireita--;
		
		Lbaixo--;
		
		Cesquerda++;
		
		
		//Isso se tiver alguém no meio, claro...
		if (Ltopo == Lbaixo && Cesquerda == Cdireita) {
	            printf("Digite um numero: ");
	            scanf("%d", &num);
	            matriz[Ltopo][Cesquerda] = num;
	            
	            cont++;
	        }
	}
}

void mostrarMatriz(int matriz[][50], int ordem){
	for (int i = 0; i < ordem; i++){
		for (int j = 0; j < ordem; j++){
			if (matriz[i][j] < 10){
				printf("  ");
			} else {
				printf(" ");
			}
			
			printf("%d", matriz[i][j]);
		}
		
		printf("\n");
	}	
}

void ordenarMatriz(){
	//Em progresso
}

int main(){
	int ordem;
	
	do {
		printf("Qual a ordem da matriz?: ");
		scanf("%d", &ordem);	
	} while (ordem <= 0);
	
	int matriz[ordem][50];
	
	system("cls");
	
	preencherMatriz(matriz, ordem);
	
	printf("\n");
	
	mostrarMatriz(matriz, ordem);
	
	return 0;
}

