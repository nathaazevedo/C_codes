#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

Arvore *insere_arvore(Arvore *arv, int x){
 	
	if (arv == NULL){
		arv = (Arvore *)malloc(sizeof(Arvore));
		arv->valor = x;
		arv->fd = NULL;
		arv->fe = NULL;		
	} else {
   		if (x < arv->valor){
 			arv->fe = insere_arvore(arv->fe,x);
   		} else {
  			arv->fd = insere_arvore(arv->fd,x);
   		}
	}
   	return arv;
  	}

   	void mostra_arvore(Arvore *arv, int desloc){
   		int i;
 		if (arv != NULL){
   			for (i = 0; i < desloc*5; i++){
   				if (i > desloc*5 -5){
   					printf("-");
   				} else {
  					printf(" ");
   				}
   			}
  			printf(">%d\n", arv->valor);
  			desloc++;
   			mostra_arvore(arv->fe, desloc);
   			mostra_arvore(arv->fd, desloc);
   		}
   }
  
   void libera_arvore(Arvore *arv){
  		if(arv->fe != NULL){
  			libera_arvore(arv->fe);
  			arv->fe = NULL;
   		}
   	 	if (arv->fd != NULL){
   			libera_arvore(arv->fd);
   			arv->fd = NULL;
 		}
  	
   		if(arv->fe == NULL && arv->fd == NULL){
   			//printf("Liberando: %d\n",arv->valor);
   			free(arv);
   		}
	}

   	int altura_arvore(Arvore *arv){
  	  	int esq, dir;
   		if (arv == NULL)
    		return -1;
    	if (arv->fe == NULL && arv->fd == NULL){
    		return 0;
    	}
    	esq = altura_arvore(arv->fe);
 	  	dir = altura_arvore(arv->fd);
  		return esq > dir ? esq+1 : dir+1; 
    }
