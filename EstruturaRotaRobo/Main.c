#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "fila.h"
#include "pilha.h"
#include "arvore.h"
#include <time.h>
//==================================================
// Delay
//==================================================
void wait(int secs) {
    unsigned int retTime = time(0) + secs;   
    while (time(0) < retTime);               
}
//==================================================
// Limpar String
//==================================================
void limpar_string(char* str){
	int i = 0;
	for(i = 0; i<50; i++){
		str[i] = ' ';
	}
}
//==================================================
// Alocar Matriz Dinamicamente
//==================================================
int **cria_matriz(int tam_x, int tam_y){
	int i, **matriz;
    matriz = (int**) malloc(sizeof(int*) * tam_x);
    
    for(i = 0; i < tam_x; i++){
		matriz[i] = (int*) malloc(sizeof(int) * tam_y);    
	}

    return matriz;
}
//==================================================
// Imprimir a Matriz
//==================================================
void print_matriz(int **matriz,int x,int y){
	int i = 0, j = 0;
   //Imprime Matriz
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			printf("%d", matriz[i][j]);
		}
		printf("\n");
	}
}
//==================================================
// Salvar a Saida
//==================================================
void save(int **matriz,int x,int y, int pos_x, int pos_y){
	FILE *arq;
	arq = fopen("Saida.txt", "w+");
//	char *sda;
	int i = 0, j = 0;
	
	if (arq == NULL){
     	printf("Problemas na criacao do arquivo\n");
     	return;
  	} else {
		for(i = 0; i < x; i++){
			for(j = 0; j < y; j++){
				fprintf(arq, "%d", matriz[i][j]);
			}
			fprintf(arq, "\n", matriz[i][j]);
		}
	}
	fprintf(arq, "\nx = %d, y = %d\n", pos_x, pos_y);
	fclose(arq);
	wait(1);
	printf("Arquivo salvo");
}
//==================================================
// Mover o robo
//==================================================
void mover_robo(int comando, int **matriz, int *x, int *y,int tam_x,int tam_y){
	int i, j;
	// Mover Abaixo
	if(comando == 1){
		if(*x+1 < tam_x){
			*x = *x+1;
		}else{
			printf("\nComando invalido\n");
		}
	// Mover Acima	
	} else if(comando == 2){
		if(*x-1 >= 0){
			*x = *x-1;
		}else{
			printf("\nComando invalido\n");
		}
	// Mover a Direita
	} else if(comando == 3){
		if(*y+1 < tam_y){
			*y = *y+1;
		}else{
			printf("\nComando invalido\n");
		}
	// Mover a Esquerda
	} else if(comando == 4){
		if(*y-1 >= 0){
			*y = *y-1;
		}else{
			printf("\nComando invalido\n");
		}
	// Salvar	
	} else if (comando == 6){
		save(matriz, tam_x, tam_y, *y, *x);	
	}
	matriz[*x][*y] = 1;
	printf("\nx = %d, y = %d\n",*x,*y);
	wait(1);          // Esperar 1seg
	system("cls");    // Limpar tela
}
//==================================================
// Ler acoes no arquivo
//==================================================
void pick_acao(Fila *fila, int number_action, char *ch, char *pont_ler){
	int i, n_vezes = 0;
	char num[50];
	
	for(i = 3; i>0; i++){  //Ler depois que abre o parenteses(posicao 3 do vetor de caracteres)
		if(ch[i] == ')'){  //For com loop infinito até encontrar ) que indica o final do comando
			break;
		}else{
			*(pont_ler++); 	   //Ir descolando o ponteiro para o lado
			num[i-3] = ch[i];  //Ir pegando os caracteres apontados pelo ponteiro e criar uma nova string
		}
	}
	if(number_action == 6){
		n_vezes = 1;
	}else{
		n_vezes = atoi(num);      //Tranformar esta nova string com um inteiro com o numero de vezes que eh para executar a acao
	//	mostra_fila(fila);
    }
	for(i = 0; i < n_vezes; i++){
		push_fila(fila, number_action);
	}
	//Limpar a string para nao obter problemas na proxima vez que executar o processo acima 
	limpar_string(num);
}
//==================================================
// Ler ações e tranformar em comandos (numeros)
//==================================================
void pegar_acoes(Fila *fila, char *ch, char *pont_ler){
	//========================================
    //Pegar acoes | Comando AB() == 1 na fila
    //========================================
	if(ch[0] == 'A' && ch[1] == 'B' || ch[0] == 'a' && ch[1] == 'b'){    
		pick_acao(fila, 1, ch, pont_ler);
		//========================================
		//Pegar acoes | Comando AC() == 2 na fila
		//========================================
	} else if(ch[0] == 'A' && ch[1] == 'C' || ch[0] == 'a' && ch[1] == 'c'){
		pick_acao(fila, 2, ch, pont_ler);
		//========================================
		//Pegar acoes | Comando DI() == 3 na fila
		//========================================
	} else if(ch[0] == 'D' && ch[1] == 'I' || ch[0] == 'd' && ch[1] == 'i'){
		pick_acao(fila, 3, ch, pont_ler);			
		//========================================
		//Pegar acoes | Comando ES() == 4 na fila
		//========================================
	} else if(ch[0] == 'E' && ch[1] == 'S' || ch[0] == 'e' && ch[1] == 's'){
		pick_acao(fila, 4, ch, pont_ler);	
		//========================================
		//Pegar acoes | Comando VO() == 5 na fila
		//========================================
	} else if(ch[0] == 'V' && ch[1] == 'O' || ch[0] == 'v' && ch[1] == 'o'){
		pick_acao(fila, 5, ch, pont_ler);	
	    //=============================
   	    //Pegar acoes | Comando SA()
        //=============================
	} else if(ch[0] == 'S' && ch[1] == 'A' || ch[0] == 's' && ch[1] == 'a'){
		pick_acao(fila, 6, ch, pont_ler);
	}
}
//==================================================
// Voltar ações
//==================================================
int voltar(Pilha *pi){
	int voltar = 0;
	voltar = peek_pilha(pi);
	// Tratamento para fazer os comandos ao contrario
	if(voltar == 1){ 
		voltar = 2;
	}else if(voltar == 2){
		voltar = 1;
	}else if(voltar == 3){
		voltar = 4;
	}else if(voltar == 4){
		voltar = 3;
	}//============================================
	return voltar;
}
//==================================================
// Funcao Principal (Main)
//==================================================
int main(){
	
	FILE *arq;
	arq = fopen("Robo.txt", "r");  // Abre o arquivo
  	char linha[100];
  	char *ch;
  	int i, j, num_linha = 1, x_matriz = 0, y_matriz = 0, comand = 0, back = 0;
  	int x_robo = 0, y_robo = 0;
    Fila *acoes = inicializa_fila();
    Pilha *acoes_exec = inicializa_pilha();
  
  	if (arq == NULL){
     	printf("Problemas na abertura do arquivo\n");
     	return;
  	}
	while (!feof(arq)){
		ch = fgets(linha, 100, arq);
      	if (ch){					 // Se eh possível ler
     		if (ch[0] != '#' && ch[0] != '\n'){  // Ignorar linhas com # 
     		    //=============================
     		    //Pegar primeiras configurações
     		    //=============================
     	   	    if(comand == 0){
     				x_matriz = atoi(linha);
     				comand++;
				}else if (comand == 1){
					y_matriz = atoi(linha);
					comand++;
				}else if (comand == 2){
					x_robo = atoi(linha);
					comand++;
				}else if (comand == 3){
					y_robo = atoi(linha);
					comand++;
				}
			    pegar_acoes(acoes, ch, linha);
			}
		}
      	num_linha++;
  	}
	fclose(arq);
	
	int **matrz = cria_matriz(x_matriz, y_matriz); 
    // Setar 0 em todas a posicoes da matriz
	for(i = 0; i < x_matriz; i++){
		for(j = 0; j < y_matriz; j++){
			matrz[i][j] = 0;
		}
	}
	//Comeco
	matrz[x_robo][y_robo] = 1;
	wait(1);
	print_matriz(matrz, x_matriz, y_matriz);

    while(peek_fila(acoes) != -1){    // Executar comandos enquanto ouver comandos
    	if(peek_fila(acoes) != 5){    // Se o comando da fila for diferente de voltar (que eh o comando 5)
    		mover_robo(peek_fila(acoes), matrz, &x_robo, &y_robo, x_matriz, y_matriz);
			print_matriz(matrz, x_matriz, y_matriz);
			push_pilha(acoes_exec, peek_fila(acoes));  // Adicionar acao executada a pilha
		} else if(peek_pilha(acoes_exec) != -1){       // Executar comandos voltarem se existir comandos para voltar
			back = voltar(acoes_exec);
			matrz[x_robo][y_robo] = 0;  // Apagar local onde o robo passou
			mover_robo(back, matrz, &x_robo, &y_robo, x_matriz, y_matriz);	
			print_matriz(matrz, x_matriz, y_matriz);
			pop_pilha(acoes_exec);
		}
		pop_fila(acoes);
	}
	
	printf("Digite acoes a serem executadas (digite 0 caso queira parar): \n");
	gets(ch);
	while(ch[0] != '0'){
		pegar_acoes(acoes, ch, linha);		
    	while(peek_fila(acoes) != -1){    // Executar comandos enquanto ouver comandos
    		if(peek_fila(acoes) != 5){    // Se o comando da fila for diferente de voltar (que eh o comando 5)
    			mover_robo(peek_fila(acoes), matrz, &x_robo, &y_robo, x_matriz, y_matriz);
				print_matriz(matrz, x_matriz, y_matriz);
				push_pilha(acoes_exec, peek_fila(acoes));  // Adicionar acao executada a pilha
			} else if(peek_pilha(acoes_exec) != -1){       // Executar comandos voltarem se existir comandos para voltar
				back = voltar(acoes_exec);
				matrz[x_robo][y_robo] = 0;  // Apagar local onde o robo passou
				mover_robo(back, matrz, &x_robo, &y_robo, x_matriz, y_matriz);	
				print_matriz(matrz, x_matriz, y_matriz);
				pop_pilha(acoes_exec);
			}
			pop_fila(acoes);
		}
		printf("\nProximo comando (0 para parar): \n");
		gets(ch);
	}

	libera_fila(acoes);
	acoes = NULL;
	libera_pilha(acoes_exec);
	acoes_exec = NULL;

	system("pause");
} 
