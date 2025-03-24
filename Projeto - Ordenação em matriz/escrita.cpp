#include <iostream>
#include <stdio.h>

using namespace std;
	
void preencherMatriz(int matriz[][50], int N){
	
	int Ltopo = 0;
	int Lbaixo = N-1;
	int Cesquerda = 0;
	int Cdireita = N-1;
	
	int num;
	
	int cont = 0;
	
	while (cont < (N * N)){
		
		//Esquerda para a direita
		for (int i = Cesquerda; i <= Cdireita; i++){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[Ltopo][i] = num;
			cont++;
		}
		
		Ltopo++;
		
		//Cima pra baixo
		for (int i = Ltopo; i <= Lbaixo; i++){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[i][Cdireita] = num;
			cont++;
		}
		
		Cdireita--;
		
		//Direita para a esquerda
		
		for (int i = Cdireita; i >= Cesquerda; i--){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[Lbaixo][i] = num;
			cont++;
		}
		
		Lbaixo--;
		
		//Baixo para cima
		
		for (int i = Lbaixo; i >= Ltopo; i--){
			printf("Digite um numero: ");
			scanf("%d", &num);
			
			matriz[i][Cesquerda] = num;
			cont++;	
		}
		
		Cesquerda++;
	}
}

int main(){
	int ordem;
	
	printf("Qual a ordem da matriz?: ");
	scanf("%d", &ordem);
	
	int matriz[ordem][50];
	
	system("cls");
	
	preencherMatriz(matriz, ordem);
	
	printf("\n");
	
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
	
	return 0;
}

