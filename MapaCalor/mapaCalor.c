#include <stdio.h>
#include <stdlib.h>
#include "conio.c"
/*
	(x) utilizar vetores e/ou matrizes
	(x) utilizar estruturas de repetição
	(x) implementar utilizando modularização
		(um de procedimento e dois de ação)
	(x) utilizar passagem de parametro por valor
	
	
	https://code-reference.com/c/conio.h/textcolor
	https://www.ricardoarrigoni.com.br/tabela-ascii-completa/
*/

// Tamanho da matriz
#define N_LINHA 15
#define N_COLUNA 15
// Caracter do quadrado na tabela ASCII
#define QUADRADO 220

int mapa[N_LINHA][N_COLUNA]; // matriz como variavel global para ser acessada pelas funcoes

// modulo de procedimento
void imprime_mapa(){ 	// funcao que imprime o mapa de calor
	int i, j;			// Variaveis para iteracao da matriz
	
	for(i = 0; i < N_LINHA; i++){		// Percorrer linhas da matriz
		for(j = 0; j < N_COLUNA; j++){  // Percorres colunas da matriz
			if(mapa[i][j] == 5){		// Se o nivel de calor for 5
				textcolor(15);			// Cor Branca
			} else if(mapa[i][j] == 4){	// Se o nivel de calor for 4
				textcolor(14);			// Cor Amarelar
			} else if (mapa[i][j] == 3){// Se o nivel de calor for 3
				textcolor(4);			// Cor Vermelha
			} else if (mapa[i][j] == 2){// Se o nivel de calor for 2
				textcolor(3);			// Cor ciano - azul fraco
			} else if (mapa[i][j] == 1){// Se o nivel de calor for 1
				textcolor(1);			// Cor azul forte
			}
			printf("%c ", QUADRADO); 	// Desenha o quadrado na matriz
			textcolor(7);			 	// Cor cinza - padrão
		}
		printf("\n"); // quebrar uma linha
	}
	
}
// modulo de acao
void desenha_mapa(int pont_x, int pont_y){ // funcao que imprime o mapa de calor
	int i, j, k;
	int quadrante1, quadrante2, nivel_calor;

	mapa[pont_x][pont_y] = 5; // definir todos os pontos como 0
	
	for(i = 1; i < 7; i++){ // fazer a distancia
		// Setar nivel de calor
		if(i <= 2){
			nivel_calor = 4;
		} else if(i <= 4){
			nivel_calor = 3;
		} else if(i <= 5){
			nivel_calor = 2;
		} else {
			nivel_calor = 1;
		}
		for(j = 0; j < 4; j++){ // fazer 4 quadrantes
			// Setar quadrante para desenhar
			if(j == 0){ 		// -x e -y
				quadrante1 = 1;
				quadrante2 = 1;
			} else if (j == 1){ // x e -y
			//	quadrante1 = 1;	
				quadrante2 = -1;
			} else if (j == 2){ // -x e y
				quadrante1 = -1;
			//	quadrante2 = -1;
			} else {			// x e y
			//	quadrante1 = -1;
				quadrante2 = 1;
			}
			// Numerar matriz
			for(k = 1; k <= 6-nivel_calor; k++){
				if(pont_y+k*quadrante2 < N_COLUNA && pont_y+k*quadrante2 >= 0){	// Condicao para nao desenhar fora da matriz
					mapa[pont_x+i*quadrante1][pont_y+k*quadrante2] = nivel_calor;
				}
				if (pont_y+i*quadrante2 < N_COLUNA && pont_y+i*quadrante2 >= 0){ // Condicao para nao desenhar fora da matriz
					mapa[pont_x+k*quadrante1][pont_y+i*quadrante2] = nivel_calor;
					mapa[pont_x+i*quadrante1][pont_y] = nivel_calor; // Horizontal
					mapa[pont_x][pont_y+i*quadrante2] = nivel_calor; // Vertical
					if(i == 3 || i == 5 || i == 6){ // cantos p/ dentro
						mapa[pont_x+i*quadrante1-quadrante1][pont_y+(i-1)*quadrante2] = nivel_calor;	
					}
				}	
			}
		}
	}
}

void zerar_matriz(){
	int i, j;
	
	for(i = 0; i < N_LINHA; i++){		// Percorrer linhas da matriz
		for(j = 0; j < N_COLUNA; j++){	// Percorres colunas da matriz
			mapa[i][j] = 0; 			// Definir todos os pontos como 0
		}
	}
}

int main(){
	int i, j; 			// variaveis para iteração da matriz
	int coordenadas[2]; // vetor do ponto (x,y) de calor;
	
	zerar_matriz();

	printf("Define o as coordenadas de calor");
	printf("\nx: ");
	scanf("%i", &coordenadas[0]);	// Coordenada X
	printf("\ny: ");
	scanf("%i", &coordenadas[1]);	// Coordenada Y
	
	// Desenhar mapa de calor de acordo com as coordenadas
	desenha_mapa( coordenadas[0]-1, coordenadas[1]-1);
	
	printf("\n A matriz de calor gerada eh: \n");
	imprime_mapa(); // imprimir o mapa de calor

	return(0);
}
