#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Arvore.h"

int main(){
	Arvore *atual = NULL;
	
	int i = 0;
	int op;
	int aux = 0;
	int val;
	
	while(1){
		system("cls");
		//setlocale(LC_ALL,"Portuguese");
		printf("Estrutura de Dados - Arvore Binaria\n");
		
		printf("\n1 - Inserir\n2 - Remover\n3 - Valor Acima\n4 - Esquerda\n5 - Direita\n6 - Profundidade\n7 - Pre-Ordem\n8 - Pos-Ordem\n9 - Ordem\n0 - Sair \n10 - Numero de elementos \n11 - Desbalanceamento do elemento\n12 - Arvore exemplo\n\n");
	
		if(tamanho_arv() == 0){
			printf("Árvore vazia!\nOpção:");
		}else{
			printf("Valor atual:%i\n",atual->valor);
			printf("Opcao:");
		}
		
		scanf("%d", &op);	
		if(op == 1){
			printf("\nDigite um valor inteiro:");
			scanf("%d", &val);
			inserir(&atual, val);
		}else if(op == 2){
			if(tamanho_arv() == 0){ 
				printf("\nArvore vazia!\n\n");
				system("pause");		
			} else {
				if(atual->aa == NULL && atual->pp == NULL && atual->cima != NULL){
					removeFolha(&atual);
				} else if(atual->aa != NULL && atual->pp == NULL && atual->cima != NULL){
					removerGalho(&atual);		
				}else if(atual->aa == NULL && atual->pp != NULL && atual->cima != NULL){	
					removerGalho(&atual);			
				} else if(atual->aa != NULL && atual->pp != NULL && atual->cima != NULL){
					removerNo(&atual);	
				}
				if(atual->cima == NULL){
					printf("\nNao é possivel remover a raiz\n");	
				} else {
					printf("\nValor removido!\n");	
				}
				system("pause");
			}
		}else if(op == 3){
			if(atual->cima != NULL){ //&& atual->valor != 0        atual->valor != NULL){
				atual = atual->cima;
			} else {
				printf("\nRaiz!\n");
				system("pause");	
			}
		}else if(op == 4){	
			if(atual->aa != NULL){
				atual = atual->aa;
			} else {
				printf("\nEsquerda vazia!\n");
				system("pause");	
			}
		}else if(op == 5){	
			if(atual->pp != NULL){			
				atual = atual->pp;
			}else{
				printf("\n Direita vazia!\n");
				system("pause");	
			}			
		}else if(op == 6){
			printf("\nA profundidade da arvore eh: %d \n", profund_arv(atual));
			system("pause");
		}else if(op == 7){ // pré ordem	
			if(tamanho_arv() == 0){
				printf("arvore vazia!\nOpcaoo:");
			} else {
				preordem(&atual);
			}
			system("pause");
		}else if(op == 8){ // pos ordem
			if(tamanho_arv() == 0){
				printf("Árvore vazia!\nOpcaoo:");
			} else {
				posordem(&atual);
			}
			system("pause");
		}else if(op == 9){ // em ordem
			if(tamanho_arv() == 0){
				printf("Árvore vazia!\nOpcaoo:");
			} else {
				emordem(&atual);
			}
			system("pause");
		}else if(op == 0){
			printf("\nFinalizando");
			for(i=0;i<3;i++){
			printf(".");
			}
			break;
		} else if(op == 10){
			printf("O numero de elementos na arvore eh: %d\n", tamanho_arv());
			system("pause");
		} else if(op == 11){
			printf("Este elemento esta %d desbalanceado\n", desbalanceado(&atual));
			system("pause");
		}else if(op==12){
			inserir(&atual, 5);
			inserir(&atual, 3);
			inserir(&atual, 4);
			inserir(&atual, 1);
			inserir(&atual, 0);
			inserir(&atual, 2);
			inserir(&atual, 8);
			inserir(&atual, 6);
			inserir(&atual, 7);
			inserir(&atual, 9);
		}else{
			printf("\nOpcao invalida, tente novamente!\n");
			system("pause");
		}
	}
	
	return 0;
}
