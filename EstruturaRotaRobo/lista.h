 #include <stdio.h>
#include <stdlib.h>

/* define um nodo de uma lista de encadeamento simples para frente */
typedef struct _nolista {
	int valor;
	struct _nolista *prox;
} NoLista;

typedef struct {
	NoLista *inicio;
	int nlem;	
} Lista;

/* inicializa os metadados da lista  e retorna o ponteiro para a struct do tipo Lista inicializada*/
Lista *inicializa_lista();

/* insere o valor v na lista */
void insere_lista(Lista *lista, int v);

/* mostra a lista inteira */
void mostra_lista(Lista *lista);

/* libera a memoria alocada para a lista */
void libera_lista(Lista *lista);

/* exclui todas as ocorrencias do valor v na lista */
void remove_valor_lista(Lista *lista, int v);
