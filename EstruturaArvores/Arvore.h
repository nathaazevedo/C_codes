#include <stdio.h>
#include <stdlib.h>

// Estrutura de um folha
typedef struct ar{
	int valor;		//valor da folha
	struct ar *pp;  //folha de direita
	struct ar *aa;	//folha da esquerda
	struct ar *cima;//folha da cima
}Arvore;

// Funcao para inserir elemento
void inserir(Arvore **atual, int val);
// Remover elemento 
void removeFolha(Arvore **atual);
void removerGalho(Arvore **atual);
void removerNo(Arvore **atual);
// Mostrar numero de elementos na arvore
int tamanho_arv();
// Mostrar a profundidade do menor nó
int profund_arv(Arvore *atual);
// Visitar o elemento raiz da arvore
Arvore* visitar_raiz(Arvore *atual);
// Ordenar elementos em pre ordem
void preordem(Arvore **atual);
void red(Arvore *atual);
// Ordenar elementos em ordem
void emordem(Arvore **atual);
void erd(Arvore *atual);
// Ordenar elementos em pos ordem
void posordem(Arvore **atual);
void edr(Arvore *atual);
// Mostrar o quanto o no esta desbalanceado
int desbalanceado(Arvore **atual);
