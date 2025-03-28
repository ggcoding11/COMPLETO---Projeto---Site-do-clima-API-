#include <iostream>
#include <stdio.h>

void preencherMatriz(int matriz[][50], int N){
	for (int i = 0; i < N; i++){
		for (int j = 0;  j < N; j++){
			printf("Digite o numero: ");
			scanf("%d", &matriz[i][j]);
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

void trocar(int *n1, int *n2){
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void percorrerMatriz(int matriz[][50], int l, int c, int N){
	int Ltopo = 0;
	int Lbaixo = N-1;
	int Cesquerda = 0;
	int Cdireita = N-1;
	
	int cont = 0;
	
	while (cont < (N*N)){
		for (int i = Cesquerda; i <= Cdireita; i++){
			if (matriz[l][c] < matriz[Ltopo][i]){
				trocar(&matriz[l][c], &matriz[Ltopo][i]);
			}
			
			cont++;
		}
		
		Ltopo++;
		
		//Cima pra baixo
		for (int i = Ltopo; i <= Lbaixo; i++){
			if (matriz[l][c] < matriz[i][Cdireita]){
				trocar(&matriz[l][c], &matriz[i][Cdireita]);
			}
			
			cont++;
		}
		
		Cdireita--;
		
		//Direita para a esquerda
		
		for (int i = Cdireita; i >= Cesquerda; i--){
			if (matriz[l][c] < matriz[Lbaixo][i]){
				trocar(&matriz[l][c], &matriz[Lbaixo][i]);
			}
			
			cont++;
		}
		
		Lbaixo--;
		
		//Baixo para cima
		
		for (int i = Lbaixo; i >= Ltopo; i--){
			if (matriz[l][c] < matriz[i][Cesquerda]){
				trocar(&matriz[l][c], &matriz[i][Cesquerda]);
			}
			
			cont++;	
		}
		
		Cesquerda++;
	}
}

void ordenarMatriz(int matriz[][50], int N){
	int Ltopo = 0;
	int Lbaixo = N-1;
	int Cesquerda = 0;
	int Cdireita = N-1;
	
	int cont = 0;
	
	while (cont < (N * N)){
		
		//Esquerda pra direita
		
		for (int i = Cesquerda; i <= Cdireita; i++){			
			percorrerMatriz(matriz, Ltopo, i, N);

			
			cont++;
		}
		
		Ltopo++;
		
		//Cima pra baixo
		
		for (int i = Ltopo; i <= Lbaixo; i++){
			percorrerMatriz(matriz, i, Cdireita, N);
			
			cont++;
		}
		
		Cdireita--;
		
		//Direita para a esquerda
		
		for (int i = Cdireita; i >= Cesquerda; i--){
			percorrerMatriz(matriz, Lbaixo, i, N);
			
			cont++;
		}
		
		Lbaixo--;
		
		//Baixo para cima
		
		for (int i = Lbaixo; i >= Ltopo; i--){
			percorrerMatriz(matriz, i, Cesquerda, N);
			
			cont++;	
		}
		
		Cesquerda++;
	}
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
	
	ordenarMatriz(matriz, ordem);
	
	printf("\n");
	
	mostrarMatriz(matriz, ordem);
	
	return 0;
}

