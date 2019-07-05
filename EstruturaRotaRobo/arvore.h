#include <stdio.h>
#include <stdlib.h>

/* define o tipo Arvore que representa um nodo */
typedef struct noarv {
   	int valor;	
   	struct noarv *fe;
   	struct noarv *fd;
    } Arvore;
  
/* insere um elemento na arvore binaria e retorna o nodo raiz da arvore*/
Arvore *insere_arvore(Arvore *arv, int x);

/* mostra os elementos da arvore formatada horizontalmente */ 
void mostra_arvore(Arvore *arv, int desloc);
 
/* desaloca a memoria alocada para a arvore */
void libera_arvore(Arvore *arv);
  
/* retorna a altura da arvore */
int altura_arvore(Arvore *arv);
