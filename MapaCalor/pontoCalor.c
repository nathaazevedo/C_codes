#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "conio.c"	// Biblioteca para cores
// Tamanho da matriz
#define DIM 15
// Caracter do quadrado na tabela ASCII
#define QUADRADO 220
// Funcoes
void imprime_numerica(int matriz[DIM][DIM]);
void imprime_mapa_colorido(int matriz[DIM][DIM], int temp);
void zerar_matriz(int matriz[DIM][DIM]);
// Funcao principal
int main(){
	int u1[DIM][DIM]; // matriz inicial
	int u2[DIM][DIM]; // matriz para gerar o mapa de calor
	
	zerar_matriz(u1);
	zerar_matriz(u2);
	
	int temp;			// Usuario informa a maior temperatura do mapa
	float min;			// Tempo em minutos das amostras
	
	printf("Informe a temperatura central: ");
	scanf("%d", &temp);
	printf("Informe o tempo (min) de variacao de temperatura:");
	scanf("%f", &min);
	
	int iy, ix; 			// variaveis para iteração da matriz

	for(iy = 1; iy < DIM; iy++){
		for(ix = 1; ix < DIM; ix++){
			u1[ix][iy] = ix * ( DIM - ix - 1) * iy * ( DIM - iy - 1); // Gerar matriz base
		}
	}
	printf("\nMatriz Base:\n\n");
	imprime_numerica(u1); // Imprimir matriz numerica
	printf("\n\nMatrizes Calculadas:\n\n");
	
	int amostras;		// iteracao nº de amostragem do mapa
	int menor_numero = u1[1][1];

	for(amostras = 0; amostras < min; amostras++){
		for(iy = 1; iy < DIM - 1; iy++){
			for(ix = 1; ix < DIM -1 ; ix++){
				u2[ix][iy] = u1[ix][iy] + amostras *(u1[ix+1][iy] + u1[ix-1][iy] - 2. * u1[ix][iy]) + 
									  	  amostras *(u1[ix][iy+1] + u1[ix][iy-1] - 2. * u1[ix][iy]) ; 
				
				u2[ix][iy] =  temp + (u2[ix][iy]/menor_numero) - (DIM-1);
			}
		}
		printf("\n\nAponos %d minutos: \n", amostras);
		imprime_mapa_colorido(u2, temp);
		printf("\n");
		imprime_numerica(u2); // Imprimir matriz numerica
		printf("\n\n");
	}

	return(0);
}
//  ========================================
//		funcao para zerar matrizes
//  ========================================
void zerar_matriz(int matriz[DIM][DIM]){
	int i, j;						// Variaveis para iteracao da matriz
	
	for(i = 0; i < DIM; i++){		// Percorrer linhas da matriz
		for(j = 0; j < DIM; j++){   // Percorres colunas da matriz
			matriz[i][j] = 0;
		}
	}
}
//  ========================================
//		funcao para imprimir matrizes numericas
//  ========================================
void imprime_numerica(int matriz[DIM][DIM]){ 	// funcao que imprime o mapa de calor
	int i, j;			// Variaveis para iteracao da matriz
	
	for(i = 0; i < DIM; i++){		// Percorrer linhas da matriz
		for(j = 0; j < DIM; j++){   // Percorres colunas da matriz
			printf("%i\t", matriz[i][j]); 
		}
		printf("\n"); // quebrar uma linha
	}
}
//  ========================================
//		funcao para imprimir desenho
//  ========================================
void imprime_mapa_colorido(int matriz[DIM][DIM],int temp){ 	// funcao que imprime o mapa de calor
	int i, j;			// Variaveis para iteracao da matriz
	
	for(i = 1; i < DIM-1; i++){		// Percorrer linhas da matriz
		for(j = 1; j < DIM-1; j++){  // Percorres colunas da matriz
			if(matriz[i][j] >= temp){		// Se o nivel de calor for 5
				textcolor(15);			// Cor Branca
			} else if(matriz[i][j] > temp-(DIM-3)/4){	// Se o nivel de calor for 4
				textcolor(14);			// Cor Amarelar
			} else if (matriz[i][j] > temp-((DIM-1)/2)){// Se o nivel de calor for 3
				textcolor(4);			// Cor Vermelha
			} else if (matriz[i][j] > temp-(DIM-4)){// Se o nivel de calor for 2
				textcolor(3);			// Cor ciano - azul fraco
			} else if (matriz[i][j] > temp-(DIM-1)){// Se o nivel de calor for 1
				textcolor(1);			// Cor azul forte
			}
			printf("%c ", QUADRADO); 	// Desenha o quadrado na matriz
			textcolor(7);	// cor cinza padrao
		}
		printf("\n"); // quebrar uma linha
	}
}
/*
	https://code-reference.com/c/conio.h/textcolor
	https://www.ricardoarrigoni.com.br/tabela-ascii-completa/
*/
