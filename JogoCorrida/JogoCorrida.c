#include <stdio.h>		
#include <stdlib.h>
#include <stdbool.h>	// Biblioteca para usar boleanos em C
#include <time.h>		// Biblioteca para pegar o tempo em C
#include <pthread.h>	// Biblioteca para implementar threads em C
// Simbolos ANSCII
#define QUADRADO 219	// Quadrado para logo e para ser o carro
#define LINHA_H 205		// Desenhar limite horizontal da tela
#define LINHA_V 186		// Desenhar limite vertical da tela
#define CANTO1 201		// Desenhar canto sup. esquerdo da tela
#define CANTO2 187		// Desenhar canto sup. direito da tela
#define CANTO3 200		// Desenhar canto inf. esquerdo da tela
#define CANTO4 188		// Desenhar canto inf. direito da tela
#define FAIXA 179		// Faixa da pista
#define SETA 175 		// Caracter seta do menu
// Teclas ANSCII
#define DIREITA 77		// Seta direita do teclado
#define ESQUERDA 75		// Seta esquerda do teclado
#define ACIMA 72		// Seta cima do teclado
#define ABAIXO 80		// Seta abaixo do teclado
#define ENTER 13		// Tecla enter do teclado
//================================
// Variaveis Globais
//================================
int pontos, pontos_max = 0, pos_y;  // para pontucao e posicao y do carro
float gasolina;						// gasolina do carro
bool start = false;					// boleana para diferenciar quando esta no menu e quando esta em jogo
//========================================
// Matrizes 
//========================================
// Desenha a logo CORRIDA
int logo[4][33] = {
1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0,1,1,0,0,0,1,1,1,
1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,1,
1,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,1,1,0,0,0,0,1,0,0,1,0,1,0,0,1,1,1,
1,1,1,0,0,1,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0,1,1,0,0,0,1,0,1
};
// Base para desenhar os limites de tela
int jogo_base[20][35] = {
3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6
};
// Matriz onde o jogo acontece
int jogo[20][35];
//========================================
// Printar bandeira de corrida na logo
//========================================
void desenha_bandeira(){
	int i, j;
	
	for(i = 0; i<3; i++){
		printf("\t");
		for(j = 0; j < 25; j++){
			if(i % 2){
				printf(" %c", QUADRADO);	
			}else {
				printf("%c ", QUADRADO);	
			}
		}
		printf("\n");
	}
}
//========================================
// Printar a logo
//========================================
void desenha_logo(){
    int i, j;
    printf("\n");
    for (i = 0; i < 4; i++) {
    	printf("\t\t");
       	for (j = 0; j < 33; j++) {
        	if (logo[i][j] == 0){
            		printf(" ");
        	} else if (logo[i][j] == 1){
           	 	printf("%c", QUADRADO);
           	}
		}
        printf("\n");
    }
}
//========================================
// Printar o jogo
//========================================
void desenha_jogo(){
    int i, j; // Variaveis para itera??o 

	system("cls"); // Limpar tela
	// Printar os pontos e a gasolina
	printf("\t\t\t\tPontos: %d\tGasolina:", pontos);
	for(i = 0; i < gasolina; i++){
		printf(" %c", QUADRADO);	
	}
	printf("\n");
	// Percorre a matriz numerica que representa o jogo e traduz ela para caracteres
    for (i = 0; i < 20; i++) {
    	printf("\t\t\t\t");
       	for (j = 0; j < 35; j++) {
        	if (jogo[i][j] == 0){			// Se for 0 ? espa?o em branco
            	printf(" ");
        	} else if (jogo[i][j] == 1){	// Se for 1 ? limite horizontal da tela
           	 	printf("%c", LINHA_H);
           	} else if (jogo[i][j] == 2){	// Se for 2 ? limite vertical da tela
           	 	printf("%c", LINHA_V);
           	} else if (jogo[i][j] == 3){	// Se for 3 ? limite sup. esquerdo da tela
           	 	printf("%c", CANTO1);
           	} else if (jogo[i][j] == 4){	// Se for 4 ? limite sup. direito
           	 	printf("%c", CANTO2);
			} else if (jogo[i][j] == 5){	// Se for 5 ? limite inf. esquerdo da tela
           	 	printf("%c", CANTO3);
		   	} else if (jogo[i][j] == 6){	// Se for 6 ? limite inf. direito da tela
           	 	printf("%c", CANTO4);
        	} else if (jogo[i][j] == 7){  	// Se for 7 ? faixa entre as pistas
           	 	printf("%c", FAIXA);
           	} else if (jogo[i][j] == 8){  	// Se for 8 ? carro
           		printf("%c", QUADRADO);
           	} else if (jogo[i][j] == 9){  	// Se for 9 ? obstaculo 1
               	printf("#");
			} else if (jogo[i][j] == 10){ 	// Se for 10 ? obstaculo 2
               	printf("@");
			} else if (jogo[i][j] == 11){ 	// Se for 11 ? obstaculo 2
               	printf("&");
			} else if (jogo[i][j] == 12){ 	// Se for gasolina
               	printf("G");
			} 
		}
        printf("\n");
    }
}
//========================================
// Thread para leitura do teclado
//========================================
void *teclado(){
	int tecla; // Variavel para guardar o valor ANSCII da tecla
	
	while(start){ 		// Enquanto estiver em jogo (nao no menu)
		fflush(stdin); 	// Limpar buffer do teclado
		tecla = getch();// Capturar tecla apertada
		
		if(tecla == ESQUERDA) { 		// Se a tecla for a esquerda,
			pos_y = pos_y - 5;			// Desloca o carro 5 posicoes da matriz p/ esquerda
       	} else if(tecla == DIREITA) { 	// Se a tecla for a direita,
       		pos_y = pos_y + 5;			// Desloca o carro 5 posicoes da matriz p/ direita
		}
	}
}
//========================================
// Game  Over
//========================================
void game_over(){
	start = false;				// Avisar que volta para o menu, sendo assim a thread do teclado morre
	if(pontos > pontos_max){	// Salvar nova pontucao se ela for a mais alta
 		pontos_max = pontos;
	}
	system("pause");	// Aguardar que o usuario pressione alguma tecla p/ voltar ao menu
}
//========================================
// O jogo
//========================================
void em_jogo(){
	int i, j, ciclo = 3, vel, tempo, random, obst, gas;
	bool help = true;
	// Setar variaveis
	pos_y = 18;
	pontos = 0;
	gasolina = 5;
	// Setar matriz base
	for(i = 0; i < 20; i++){
		for(j = 0; j < 35; j++){
			jogo[i][j] = jogo_base[i][j];
		}
	}
	// Flog comecar jogo
	start = true;
	// Criar thread para ler o teclado
	pthread_t threads[1];
    pthread_create(&threads[0], NULL, teclado, NULL);
    // zerar semente
	srand(time(NULL));
	// loop infinito
	while(1){
		help = !help;	 // varia o desenho da pista p/ sensacao de movimento
		tempo = clock(); //come?a a contar o tempo
		//==================	
		// Criar obstaculos
		//==================
		if(ciclo == 0){ 		// ciclos de tela variam de 3 a 8 para o spawn de obstaculos
			random = rand() % 8;// sortear 8 posibilidades de spawn, possibilidade de 1 carro eh maior que a de 2 carros
			gas = rand() % 100; // sortear spawn da gasolina
			if(gas < 35){ 	//35% de chance de spawnar gasolina
				obst = 12; 	// sorteou gasolina
			} else {
				obst = rand() % 3 + 9;  // sortear o tipo de carro do obstaculo, 3 carros diferentes
			}
			if(random == 0 || random == 6){
				jogo[2][13] = obst; // criar obstaculo
			} else if (random == 1 || random == 7){
				jogo[2][18] = obst; // criar obstaculo
			} else if (random == 2 || random == 8){
				jogo[2][23] = obst; // criar obstaculo
			} else if (random == 3){
				jogo[2][13] = obst; // criar obstaculo
				jogo[2][18] = obst; // criar obstaculo
			} else if (random == 4){
				jogo[2][13] = obst; // criar obstaculo
				jogo[2][23] = obst; // criar obstaculo
			} else if (random == 5){
				jogo[2][18] = obst; // criar obstaculo
				jogo[2][23] = obst; // criar obstaculo
			}
			ciclo = random + 3; // recomecar contagem variando de 3 a 11 ciclos 
		}
		//==================
		// Movimentos da pista
		//==================
		for(i = 1; i < 19; i=i+3){
			if(help){
				jogo[i+1][10] = 2;
				jogo[i+1][25] = 2;
				jogo[i+2][10] = 0;
				jogo[i+2][25] = 0;
				jogo[i][10] = 2;
				jogo[i][25] = 2;
			} else {
				jogo[i+1][10] = 0;
				jogo[i+1][25] = 0;
				jogo[i+2][10] = 2;
				jogo[i+2][25] = 2;
				jogo[i][10] = 2;
				jogo[i][25] = 2;			
			}
			jogo[i][15] = 7;
			jogo[i][20] = 7;
		}
		// For ao contrario pras linhas da matriz descerem
		for(i = 18; i > 1; i--){
			for(j = 13; j <= 23; j=j+5){
				jogo[i][j] = jogo[i-1][j]; 	// transforma a linha de baixo igual a linha de cima da matriz
				if ((jogo[18][j] == 9 || jogo[18][j] == 10 || jogo[18][j] == 11) && (jogo[18][pos_y] != 9 && jogo[18][pos_y] != 10 && jogo[18][pos_y] != 11)){ // passar e nao colidir com carro
					pontos++;				// Aumenta a pontucao cada vez que nao colide
				} else if (jogo[18][pos_y] == 12){ // Colidir com gasolina
					gasolina = 5;	// Enche o tanque
				}
			}
		}
		//==================
		// Game Over
		//==================
		if(jogo[18][pos_y] == 9 || jogo[18][pos_y] == 10 || jogo[18][pos_y] == 11){ // condicao com carro
			jogo[18][pos_y] = 8;// redesenhar carro
			desenha_jogo();		// atualiza tela
			printf("\t\t\t\t\t    Voce colidiu! \n\t\t\t     ");
			game_over();		// chama funcao gameover
			break;				// sai do loop infinito
		} else if(pos_y < 13 || pos_y > 23){ // condicao sair da pista
			if(pos_y < 13){
				jogo[18][13] = 0;// apagar carro
				jogo[18][8] = 8; // redesenhar carro
			} else{
				jogo[18][23] = 0; // apagar carro
				jogo[18][28] = 8; // redesenhar carro
			}
			desenha_jogo();	// atualiza tela
			printf("\t\t\t\t\t Voce saiu da pista! \n\t\t\t     ");
			game_over();	// chama funcao gameover
			break;			// sai do loop infinito
		} else if (gasolina <= 0){
			printf("\t\t\t\t\tSua gasolina acabou! \n\t\t\t     ");
		    game_over();	// chama funcao gameover
			break;			// sai do loop infinito
		}
		//==================
		jogo[18][pos_y] = 8; // redesenhar carro
		//==================
		if(pontos < 50){
			vel = 250; // tempo em ms q a tela atualiza
		} else if (pontos >= 50 && pontos < 300){
			vel = 100;
		} else if (pontos >= 300 && pontos < 600){
			vel = 50;
		} else {
			vel = 25;
		}
		//==================
		while(clock() - tempo < vel){ // delay para atualizar tela
		}
		desenha_jogo();	// atualiza tela
		ciclo--;		// cada vez que acontecer o processo todo
		gasolina = gasolina - 0.1; // Cada 10 ciclos diminui uma gasolina
	}
}
//========================================
// Como jogar
//========================================
void instrucao(){
	system("cls");		// Limpar tela
		
	printf("\n");		// Quebrar linha
	desenha_bandeira(); // Desenhar a matriz da bandeira
	printf("\t");		// Tabulacao
	desenha_logo();		// Desenhar a logo CORRIDA
	printf("\n");		// Quebrar linha
	desenha_bandeira();	// Desenhar a matriz da bandeira
	// Instrucoes de como se joga
	printf("\n\t\tObjetivo: Desvie dos outros carros \n\t\t\t  para pontuar. \n\t\t\t  Quao longe voce consegue ir? \n\n");
	printf("\t\tControles:\n \t\t   *Seta direita : move o carro p/ direita\n \t\t   *Seta esquerda: move o carro p/ esquerda \n\n");
	printf("\t\t %c = Seu carro \n\t\t # = Carro inimigo/obstaculo \n\t\t @ = Carro inimigo/obstaculo \n\t\t & = Carro inimigo/obstaculo \n\t\t G = Gasolina", QUADRADO);
	printf("\n\n\t   ");
	system("pause"); // Aguardar que o usuario pressione alguma tecla p/ voltar ao menu  
}
//========================================
// Main
//========================================
void main(){
	system("title Jogo de Corrida"); // Setar titulo do programa

	int i, j;		// Variaveis de iteracao
	int menu = 0;	// Comecar o menu na opcao 0
	int tecla;		// Variavel para capturar o valor ANSCII da telca

	while(1){		// loop infinito
		// Condicoes para que o jogador so varie entre as 3 opcoes do menu
		if(menu < 0){
			menu = 0;
		} else if (menu > 2){
			menu = 2;
		} else {
			system("cls"); 		// limpar tela
			printf("\n");  		// quebra linha
			desenha_bandeira(); // desenhar a matriz da bandeira
			printf("\t");		// tabulacao
			desenha_logo();		// desenha a matriz da logo
			printf("\n");		// quebra linha
			desenha_bandeira();	// desenhar a matriz da bandeira
			printf("\n\n\n\t\t\t");
			// Verifica e desenha qual a opcao do menu esta seleciona
			if(menu == 0){
				printf("%c", SETA);
			}
			printf("  Iniciar Jogo \n\n\t\t\t");
			if(menu == 1){
				printf("%c", SETA);
			}
			printf("  Como Jogar \n\n\t\t\t");
			if(menu == 2){
				printf("%c", SETA);
			}
			printf("  Sair \n\n");
	
			printf("\n\n\n\n Pontos Max: %d\t\tDesenvolvido por: Natha V. de Azevedo", pontos_max);
		}

		tecla = getch(); // Aguarda a captura de teclado
			
		if(tecla == ACIMA) { // Se teclar seta para cima a selecao sobe
			menu--;
       	} else if(tecla == ABAIXO) { 	// Se teclar seta para baixo a selecao desce
        	menu++;
       	} else if(tecla == ENTER){ 		// Se teclar enter seleciona a opcao
       		if (menu == 0){
       			em_jogo();				// Comeca o jogo
			} else if (menu == 1){
				instrucao();			// Mostra as intrucoes de como jogar
			} else if (menu == 2){
				exit(0);				// Encerra o programa
			}
	   	}
	}
}
