#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila *inicializa_fila(){
	Fila *fila = (Fila *)malloc(sizeof(Fila));
		if (fila == NULL){
			printf("Erro ao tentar alocar memoria!\n");
			exit(1);
		}
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->nelem = 0;
	return fila;
}

void push_fila(Fila *fila, int v){
// alocar memoria para o novo n?
	NoFila *novo = (NoFila *)malloc(sizeof(NoFila));		
	if (novo == NULL){
		printf("Erro ao tentar alocar memoria!\n");
		exit(1);
	}
	
// armazenar os valores 
	novo->valor = v;
	novo->prox = NULL;
	// ligar os ponteiros;
	if (fila->inicio == NULL){
		fila->inicio = novo;
		fila->fim = novo;
	} else {
		NoFila *ult = fila->fim;
		ult->prox = novo;
		fila->fim = novo;
 	}	
	fila->nelem++;	
}

void mostra_fila(NoFila *ini){
 	NoFila *aux = ini;
	while (aux != NULL){
		printf("%d,",aux->valor);
		aux = aux->prox;
  	}
	printf("\n");
}

int peek_fila(Fila *fila){
		if (fila->nelem == 0){
			printf("\nTodos os comandos foram executados com sucesso!\n");
 			return -1;
		}	
		return fila->inicio->valor;
}

int pop_fila(Fila *fila){
	int toret = fila->inicio->valor;
	if (fila->nelem == 1){		
		free(fila->inicio);
		fila->inicio = NULL;
		fila->fim = NULL;
	}else{
		NoFila *tofree = fila->inicio;
		fila->inicio = tofree->prox;
  		free(tofree);
   	}
	fila->nelem--;
  	return toret;	
}

void libera_fila(Fila *fila){
	NoFila *aux = fila->inicio;
	while(aux != NULL){
		NoFila *tofree = aux;
		aux = aux->prox;
		free(tofree);
	}
	free(fila);
}
