#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha *inicializa_pilha(){
	Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  	if (pilha == NULL){
		printf("Erro ao tentar alocar memoria!\n");
		exit(1);
  	}
 	pilha->inicio = NULL;
	pilha->nelem = 0;
  	return pilha;
}

void push_pilha(Pilha *pilha, int v){
// alocar memoria para o novo n?
	NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));		
	if (novo == NULL){
		printf("Erro ao tentar alocar memoria!\n");
		exit(1);
	}
// armazenar os valores 
	novo->valor = v;
	novo->prox = NULL;
// ligar os ponteiros;
	if (pilha->inicio == NULL){
		pilha->inicio = novo;		
	} else {
		novo->prox = pilha->inicio;
		pilha->inicio = novo;
	}	
	pilha->nelem++;	
}

void mostra_pilha(NoPilha *ini){
	NoPilha *aux = ini;
	while (aux != NULL){
		printf("%d,",aux->valor);
  		aux = aux->prox;
	}
 	printf("\n");	
}
   
int peek_pilha(Pilha *pilha){
	if (pilha->nelem == 0){
//		printf("Pilha vazia!\n");
		return -1;
	}	
   	return pilha->inicio->valor;
}

int pop_pilha(Pilha *pilha){
	int toret = pilha->inicio->valor;
   	if (pilha->nelem == 1){		
		free(pilha->inicio);
  		pilha->inicio = NULL;
  	}else{
		NoPilha *tofree = pilha->inicio;
		pilha->inicio = tofree->prox;
		free(tofree);
	}
	pilha->nelem--;
	return toret;	
}

void libera_pilha(Pilha *pilha){
	NoPilha *aux = pilha->inicio;
	while(aux != NULL){
 		NoPilha *tofree = aux;
		aux = aux->prox;
		free(tofree);
	}
	free(pilha);
}
