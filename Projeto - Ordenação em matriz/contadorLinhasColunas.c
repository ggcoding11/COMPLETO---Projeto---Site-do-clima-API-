#include <stdio.h>

int main(){
	int qntdElementos;
	
	//Código para definir quantas linhas e colunas o código terá
	//Tudo se baseia em quadrados perfeitos
	
	printf("Quantidade de elementos: \n");
	scanf("%d", &qntdElementos);
	
	int i = 0;
	
	while (qntdElementos > (i*i)){
		i++;
	}
	
	printf("%d x %d", i, i);
	
	

	return 0;
}

