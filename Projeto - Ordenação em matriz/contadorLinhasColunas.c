#include <stdio.h>

int main(){
	int qntdElementos;
	
	//Código para definir quantas linhas e colunas o código terá
	//Tudo se baseia em quadrados perfeitos
	
	printf("Quantidade de elementos: \n");
	scanf("%d", &qntdElementos);
	
	int tam = 0;
	
	while (qntdElementos > (tam*tam)){
		tam++;
	}
	
	int i = 0;
	int l, c;
	
	int matriz[tam][tam];
	
	
	for (l = 0; (l < tam && i < qntdElementos); l++){
		for (c = 0; (c < tam && i < qntdElementos); c++, i++){
			printf("Digite um numero: ");
			scanf("%d", &matriz[l][c]);
		}
	}

	
	
	
	
	

	return 0;
}

