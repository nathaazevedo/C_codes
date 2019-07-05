#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista *inicializa_lista(){
	Lista *lista = (Lista *)malloc(sizeof(Lista));
	if (lista == NULL){
		printf("Erro ao tentar alocar memoria!\n");
			exit(1);
	}
	lista->inicio = NULL;
	lista->nlem = 0;
	return lista;
}

void insere_lista(Lista *lista, int v){
	
   	NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
  	if (novo == NULL){
 		printf("Erro ao tentar alocar memoria!\n");
   		exit(1);
 	}
   	novo->valor = v;
   	novo->prox = NULL;
 	
  	if (lista->inicio == NULL){
 		lista->inicio = novo;
   	} else {
   		NoLista *atual = lista->inicio;
   		while (atual->prox != NULL){
  			atual = atual->prox;
   		}	
   		atual->prox = novo;
   	}
   		lista->nlem++;
}

void mostra_lista(Lista *lista){
	NoLista *atual = lista->inicio;
	while (atual != NULL){
		printf("%d,", atual->valor);
		atual = atual->prox;
 	}
  		printf("\n");
   	}

void libera_lista(Lista *lista){
 	NoLista *atual = lista->inicio;
	while (atual != NULL){
		NoLista *n = atual;
		atual = atual->prox;
   		free(n);
	}
   	free(lista);
}

  	void remove_valor_lista(Lista *lista, int v){	
		NoLista *atual = lista->inicio, *ant = NULL;
		while(atual != NULL){		
			if (atual->valor == v){
				NoLista *excluir = atual;
			if (atual == lista->inicio){
				lista->inicio = lista->inicio->prox;
			} else {
				ant->prox = atual->prox;
			}
			ant = atual;
			atual = atual->prox;	
			free(excluir);	
			lista->nlem--;
		} else {
			ant = atual;
			atual = atual->prox;
		}
	}	
}
