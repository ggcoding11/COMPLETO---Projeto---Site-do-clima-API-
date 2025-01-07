#include <stdio.h>
#include <locale.h>
#include <conio.h>

int main(){
	setlocale(LC_ALL, "Portuguese");
	
	printf("O que o jogador fará?: \n\n");
	
	printf("(1) Recarregar\n");
	printf("(2) Defender\n");
	
	char tecla;
	
	tecla = getch();
	
	
	switch(tecla){
		case '1':
			printf("Recarregou!");
		break;
		
		case '2':
			printf("Defendeu!");
		break;
	}

	return 0;
}
