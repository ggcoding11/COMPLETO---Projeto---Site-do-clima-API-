#include <stdio.h>

int main(){
	
	int numeros[] = {1,2,3,4,5,19,7,8,6,9,4,6,7,12,6,4,46,7,7,4,3,67,67};
		
	//Código para definir quantas linhas e colunas o código terá
	//Tudo se baseia em quadrados perfeitos

	int i = 0;
	
	int qntdElementos = sizeof(numeros)/sizeof(numeros[0]);
	
	while (qntdElementos > (i*i)){
		i++;
	}
	
	printf("%d x %d", i, i);
	

	return 0;
}

