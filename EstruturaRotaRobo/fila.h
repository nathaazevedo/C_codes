#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int valor;
   	struct no *prox;
  	} NoFila;

typedef struct {
	NoFila *inicio, *fim;
	int nelem;
} Fila;

/* inicializa uma estrutura de fila e retorna o ponteiro para esta estrutura */
Fila *inicializa_fila();

/* insere um elemento na fila */
void push_fila(Fila *fila, int v);

/* mostra os elementos da lista que armazena a fila */
void mostra_fila(NoFila *ini);

/* retorna o elemento que esta no inicio da fila */
int peek_fila(Fila *fila);

/* remove o elemento que esta no inicio da fila e retorna o seu valor */
int pop_fila(Fila *fila);

/* desaloca a memoria usada para a fila */
void libera_fila(Fila *fila);
