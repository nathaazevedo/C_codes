#include <stdio.h>
#include <stdlib.h>

typedef struct nopilha {
 	int valor;
   	struct nopilha *prox;
   } NoPilha;
 
typedef struct {
   	NoPilha *inicio;
   	int nelem;
} Pilha;

/* inicializa uma estrutura de pilha e retorna o ponteiro para esta estrutura */
Pilha *inicializa_pilha();

/* insere um elemento na pilha */
void push_pilha(Pilha *pilha, int v);

/* mostra os elementos da lista que armazena a pilha */
void mostra_pilha(NoPilha *ini);

/* retorna o elemento que esta no topo da pilha */
int peek_pilha(Pilha *pilha);

/* remove o elemento que esta no topo da pilha e retorna o seu valor */
int pop_pilha(Pilha *pilha);

/* desaloca a memoria usada para a pilha */
void libera_pilha(Pilha *pilha);
