#include "simulador.h"
#include "tradutor.h"

int n = 20;
void inicializar(){
	inicializarLista(&listaExecucao);
	inicializarLista(&listaIssue);
	inicializarLista(&listaRead);
	inicializarLista(&listaWriteB);
	inicializarFila();
	inicializaMemoria();
}

int main(){
	unsigned int palavra[4];
	inicializar();




	tradutor();

	escritaMemoria();
	inicializarRegistradores();
	buscaPipeline(); 
	//buscaPipeline();
	//inicializarFila();
	// unsigned int palavra[4];
	// FILA fila;

	//buscaPipeline();
	//exibirFila();
	//inicializa_bar();

	// for (int i = 0; i < n/4; i++){

	// 	buscaMemoria(palavra, memoria, pc);
	// 	decodificacao(palavra);
	// 	//op = descobrirOperacao();

	// }

	return 0;
	
}