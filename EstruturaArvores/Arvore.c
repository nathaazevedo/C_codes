#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Arvore.h"

int tamanho = 0;	 // eh o numero de elementos que tem a arvore
int profundidade = 0, count = 0; 
bool profund_test = false;

//=============================
// ** INSERIR ELEMENTO NA ARVORE **
//=============================
void inserir(Arvore **atual, int val){
	Arvore *novo;
	Arvore *atualaux; 

    if(tamanho == 0){ // Raiz = Caso seja o primeiro elemento da arvore
		novo = ((Arvore*)malloc(sizeof(Arvore)));
		novo->valor = val;
		novo->cima = NULL;
		novo->pp = NULL;
		novo->aa = NULL;
		*atual = novo; // Define como atual
	} else { 		//  Folha = Caso nao seja o primeiro elemento da arvore
		while((*atual)->cima != NULL){
			*atual = (*atual)->cima;
		}
	
		novo = ((Arvore*)malloc(sizeof(Arvore)));
		novo->valor = val;

		while(*atual != NULL){	
			if((*atual)->valor > val){	
				atualaux = *atual;
				*atual = (*atual)->aa;
			} else if((*atual)->valor < val){
				atualaux = *atual;
				*atual = (*atual)->pp;
			} else if((*atual)->valor == val){
				printf("\nValor existente!\n");
				system("pause");
			}
		}
		
		if(atualaux->valor > val){
			atualaux->aa = novo;
		} else if(atualaux->valor < val){
			atualaux->pp = novo;
		}
		novo->cima = atualaux;
		novo->aa = NULL;
		novo->pp = NULL;
	
		*atual = novo;
	}

	tamanho++;
	
	printf("\nValor inserido!\n\n");
//	system("pause");
}
//=============================
// ** REMOVER ELEMENTO NA ARVORE **
//=============================
void removeFolha(Arvore **atual){
	Arvore *aux;
	aux = *atual;
	
	if(aux->valor > aux->cima->valor){
		aux->cima->pp = NULL;
	} else {
		aux->cima->aa = NULL;
	}
	
	*atual = aux->cima;
	free(aux);
	tamanho--;
}

void removerGalho(Arvore **atual){
	Arvore *aux;
	Arvore *raiz;
	
	raiz = *atual;
	
	while(raiz->cima != NULL){
		raiz = raiz->cima;
	}
	
	aux = *atual;
	
	if(aux->valor > raiz->valor){
		if(aux->pp == NULL){
			aux->cima->pp = aux->aa;
			aux->aa->cima = aux->cima;
		} else {
			aux->cima->pp = aux->pp;
			aux->pp->cima = aux->cima;
		}
	} else if(aux->valor < raiz->valor){
		if(aux->pp == NULL){
			aux->cima->aa = aux->aa;
			aux->aa->cima = aux->cima;	
		} else {
			aux->cima->aa = aux->pp;
			aux->pp->cima = aux->cima;
		}
	}
		
	*atual = aux->cima;
	free(aux);
	tamanho--;
}

void removerNo(Arvore **atual){
	Arvore *aux;
	Arvore *trocar;
	Arvore *auxatual;
	
	int m1;
	int m2;
	int i = 0;
	
	m1 = 0;
	m2 = 0;
	
	trocar = *atual;
	aux = *atual;
	auxatual = *atual;	

	if(aux->pp != NULL){
		auxatual = aux;
		aux = aux->pp;
		i = 1;
		while(aux->aa != NULL){
			auxatual = aux;
			aux = aux->aa;
			i = 0;
		}
		m1++; 
	} else {
		auxatual = aux;
		aux = aux->aa;
		i = 1;
		while(aux->pp != NULL){
			auxatual = aux;
			aux = aux->pp;
			i = 0;
		}		
		m2++;
	}

		if(m1 != 0){
			if(i == 1){
				if(aux->pp == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = NULL;
				} else if(aux->pp != NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = aux->pp;
					aux->pp->cima = aux->cima;
				}
			}else{
				if(aux->pp == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->aa = NULL;
				} else if(aux->pp != NULL){
					trocar->valor = aux->valor;
					aux->cima->aa = aux->pp;
					aux->pp->cima = aux->cima;
				}
			}
		}else if(m2 != 0){
			if(i == 1){
				if(aux->aa == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->aa = NULL;
				} else if(aux->aa != NULL){
					trocar->valor = aux->valor;
					aux->cima->aa = aux->aa;
					aux->aa->cima = aux->cima;
				}
			}else {
				if(aux->aa == NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = NULL;
				} else if(aux->aa != NULL){ 
					trocar->valor = aux->valor;
					aux->cima->pp = aux->aa;
					aux->aa->cima = aux->cima;
				}
			}
	}
		free(aux);
		tamanho--;
}
//=============================
// ** VISITAR RAIZ DA ARVORE **
//=============================
Arvore* visitar_raiz(Arvore *atual){
	Arvore *aux;
	Arvore *raiz;

	raiz = atual;
	
	while(raiz->cima != NULL){
		raiz = raiz->cima;
	}
	
	return raiz;
}
//=============================
// ** NUMERO DE ELEMENTOS DA ARVORE **
//=============================
int tamanho_arv(){
	return tamanho;
}
//=============================
// ** PROFUNDIDADE DA ARVORE **
//=============================
int profund_arv(Arvore *atual){
	profundidade = 0;
	profund_test = true;
	if(tamanho == 0){
		profund_test = false;
		return profundidade;
	} else {
		Arvore *aux;
		//Visitar raiz
		aux = visitar_raiz(atual);

		count = 0;
		red(aux->aa); // Percorrer Esquerda
		red(aux->pp); // Percorrer Direita
	
		profund_test = false;
		return profundidade;
	}
}
//=============================
//    *** PRE - ORDEM ***
//=============================
void preordem(Arvore **atual){
	Arvore *aux;

	//Visitar raiz
	aux = visitar_raiz(*atual);
	
	printf("\n %d, ", aux->valor);

	red(aux->aa); // Percorrer Esquerda
	red(aux->pp); // Percorrer Direita

	printf("\n");
}

void red(Arvore *atual){
	Arvore *aux;
	aux = atual;
	if(aux != NULL){
		count++;
		if(profund_test == false){
			printf(" %d, ", aux->valor);
		}
		red(aux->aa);
	} 
	if(count > profundidade){
		profundidade = count;
	}
	aux = atual;
	if(aux !=NULL){
		red(aux->pp);
		count--;
	} 
}
//=============================
//    *** EM - ORDEM ***
//=============================
void emordem(Arvore **atual){
	Arvore *aux;

	aux = visitar_raiz(*atual);

	printf("\n");
	erd(aux->aa); // Percorrer Esquerda
	aux = visitar_raiz(*atual);
	printf(" %d, ", aux->valor);
	erd(aux->pp); // Percorrer Direita

	printf("\n");
}

void erd(Arvore *atual){
	Arvore *aux;
	aux = atual;
	if(aux != NULL){
		erd(aux->aa);
		printf(" %d, ", aux->valor);
	} 
	aux = atual;
	if(aux !=NULL){
		erd(aux->pp);
	} 
}
//=============================
//    *** POS - ORDEM ***
//=============================
void posordem(Arvore **atual){
	Arvore *aux;

	aux = visitar_raiz(*atual);

	printf("\n");
	edr(aux->aa); // Percorrer Esquerda
	edr(aux->pp); // Percorrer Direita
	aux = visitar_raiz(*atual);
	printf(" %d, \n", aux->valor);
}

void edr(Arvore *atual){
	Arvore *aux;
	aux = atual;
	if(aux != NULL){
		edr(aux->aa);
	} 
	aux = atual;
	if(aux !=NULL){
		edr(aux->pp);
		printf(" %d, ", aux->valor);
	} 
}
//=============================
//    *** DESBALANCEADO ***
//=============================
int desbalanceado(Arvore **atual){
	Arvore *aux;
	aux = *atual;
	
	profundidade = 0;
	profund_test = true;
	if(tamanho == 0 || aux->aa != NULL && aux->pp != NULL){
		profund_test = false;
		return 0;
	} else {
		count = 0;
		int lado = 0;
		if(aux->aa == NULL){// Esquerda igual a nula
			lado++;
		} else{				// Direita igual a nula
			lado--;
		}

		red(aux->aa); // Percorrer Esquerda
		red(aux->pp); // Percorrer Direita
	
		profund_test = false;
		
		return profundidade * lado;
	}
}
/*  NIVEL
int desbalanceado(Arvore **atual){
	profundidade = 0;
	profund_test = true;
	if(tamanho == 0){
		profund_test = false;
		return profundidade;
	} else {
		Arvore *aux;
	
		aux = *atual;

		count = 0;
		red(aux->aa); // Percorrer Esquerda
		red(aux->pp); // Percorrer Direita
	
		profund_test = false;
		return profundidade;
	}
}
*/
