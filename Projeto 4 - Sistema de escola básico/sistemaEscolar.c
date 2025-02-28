#include <stdio.h>

void menuPrincipal();
void menuAlunos();
void menuNotas();

int main(){
	
	menuPrincipal();
	
	
	return 0;
}

void menuPrincipal(){
	int opcao;
	
	printf("CCIM - Sistema escolar (Por Mr. JeeJ)\n\n");
	
	printf("1 - Alunos\n");
	printf("2 - Notas\n");
	printf("0 - Sair\n\n");
	
	printf("Opcao: ");
	scanf("%d", &opcao);
	
	switch(opcao){
		case 1:
		
		case 0:
			printf("Saindo...");
			return;
		break;
	}
}
