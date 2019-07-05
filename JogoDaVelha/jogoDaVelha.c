
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//#############################
// Funcao para desenhar o mapa
//#############################
void desenharMap(char mapa[11][11]){
	int i, j;	   // variaveis auxiliares
	system("cls"); // limpar tela
	// Desenhar tudo
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			printf("%c", mapa[i][j]);
		}
		printf("\n");
	}
}
//#############################
// Funcao para salvar txt
//#############################
void arquivo(char mapa[11][11]){
  	FILE *file;			// variavel do arquivo
	int i, j;			// variaveis auxiliares para percorrer a matriz
	char dateStr[20];	// variavel auxiliar para pegar a data
    char timeStr[9];	// variavel auxiliar para pegar a hora

	_strdate(dateStr);			// pegar data do sistema
    _strtime(timeStr);  		// pagar hora do sistema
    strcat(dateStr, "-");	  	// juntar Strings
    strcat(dateStr, timeStr); 	// juntar strings

   	file = fopen("log.txt", "a+");		// salvar arquivo com o nome da data e hora

   	fprintf(file, "\n %s \n", dateStr); // escrever data do jogo
  	// Desenhar todo o mapa
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			fprintf(file, "%c", mapa[i][j]); // escrever a matriz no arquivo
		}
		fprintf(file, "\n"); // escrever uma quebra de linha no arquivo
	}
   	fclose(file);	// fechar arquivo
   	system("cls");  // limpar tela
   	printf("Arquivo salvo com sucesso \nFim de jogo!");
}
//#############################
// Funcao para testar se ganhou o jogo da velha
//#############################
int ganhou(char mapa[11][11]){
	if((mapa[1][1] == mapa[1][5] && mapa[1][1] == mapa[1][9] && mapa[1][5] == mapa[1][9]) || // Se a primeira linha for igual ou
		(mapa[5][1] == mapa[5][5] && mapa[5][1] == mapa[5][9] && mapa[5][5] == mapa[5][9])|| // Se a segunda linha for igual ou
		(mapa[5][1] == mapa[5][5] && mapa[5][1] == mapa[5][9] && mapa[5][5] == mapa[5][9])|| // Se a terceira linha for igual ou
		(mapa[1][1] == mapa[5][1] && mapa[1][1] == mapa[9][1] && mapa[5][1] == mapa[5][1])|| // Se a primeira coluna for igual ou
		(mapa[1][5] == mapa[5][5] && mapa[1][5] == mapa[9][5] && mapa[5][5] == mapa[9][5])|| // Se a segunda coluna for igual ou
		(mapa[5][1] == mapa[5][5] && mapa[5][1] == mapa[5][9] && mapa[5][5] == mapa[5][9])|| // Se a terceira coluna for igual  ou
		(mapa[1][1] == mapa[5][5] && mapa[1][1] == mapa[9][9] && mapa[5][5] == mapa[9][9])|| // Se a primeira diagonal for igual
		(mapa[1][9] == mapa[5][5] && mapa[1][9] == mapa[9][1] && mapa[5][5] == mapa[9][1])){ // Se a segunda diagonal for igual
			return 1;	// Se a condicao acima for verdadeira a funcao retorna verdadeiro
	}
	return 0; // Caso nenhuma das condicoes acima seja verdadeira a funcao retorna falso
}
//#############################
// Funcao principal
//#############################
int main(){
	system("title Jogo da Velha");
	char mapa[11][11];  // Matriz para criar o mapa do jogo da velha
	int i,j;			// Variaveis auxiliares
	int jogadas = 0;    // Numero de jogadas
	int jogou_pos;      // Posicao da jogada
	int jogou[9]; 		// Salvar posicoes jogadas
	int carac;			// Variavel auxiliar para X e O
	char save;			// Variavel auxiliar para pedir pra salvar, sim ou nao
	// zerar jogadas
	for(i = 0; i < 9; i++){
		jogou[i] = 0;
	}
	// Setar tudo
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
		 	mapa[i][j] = 32;	// valor numerico do " " na tabela ASCII
		}
	}
	// Setar linhas e colunas
	for(i = 0; i < 11; i++){
		mapa[3][i] = 177;  		// valor da barra preta na tabela ASCII
		mapa[7][i] = 177;		// valor da barra preta na tabela ASCII
		mapa[i][3] = 177;		// valor da barra preta na tabela ASCII
		mapa[i][7] = 177;		// valor da barra preta na tabela ASCII
	}
	// Setar numeros
	mapa[1][1] = 49; // numero "1" na tabela ASCII
	mapa[1][5] = 50; // numero "2" na tabela ASCII
	mapa[1][9] = 51; // numero "3" na tabela ASCII
	mapa[5][1] = 52; // numero "4" na tabela ASCII
	mapa[5][5] = 53; // numero "5" na tabela ASCII
	mapa[5][9] = 54; // numero "6" na tabela ASCII
	mapa[9][1] = 55; // numero "7" na tabela ASCII
	mapa[9][5] = 56; // numero "8" na tabela ASCII
	mapa[9][9] = 57; // numero "9" na tabela ASCII

	desenharMap(mapa); // Chama funcao para printar o mapa
	while(jogadas < 9){// loop enquanto o numero max de jogadas nao for execido
		desenharMap(mapa); // redesenha o mapa
		if(jogadas % 2){	 // Se o resto da divisão por 2 for 0, fala para O jogar
			printf("\nO => Realize a jogada:");
		} else {		   	 // Se o resto da divisão por 2 for diferente de 0, fala para o X jogar
			printf("\nX => Realize a jogada:");
		}
		scanf("%i", &jogou_pos);
		if(jogadas % 2){ // Se o resto da divisão por 2 for 0, Jogar O
			carac = 79;
		} else { 	   	 // Se o resto da divisão por 2 for diferente de 0, Jogar X
			carac = 88;
		}
		// Teste a posicao jogada
		switch(jogou_pos-1){ // posicao jogada -1 para corigir a indexacao
			case 0: // Caso jogue na posicao 1
				if(jogou[jogou_pos-1] == 0){	// teste se ja nao houve uma jogada nesta posicao
					mapa[1][1] = carac;			// desenha X ou O
					jogou[jogou_pos-1] = 1;		// marca que ja houve uma jogada nesta posicao
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;	// desconsiderar jogada caso a posicao ja tenha sido jogada
				}
				break;
			case 1:  // Caso jogue na posicao 2
				if(jogou[jogou_pos-1] == 0){
					mapa[1][5] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			case 2:  // Caso jogue na posicao 3
				if(jogou[jogou_pos-1] == 0){
					mapa[1][9] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			case 3: // Caso jogue na posicao 4
				if(jogou[jogou_pos-1] == 0){
					mapa[5][1] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			case 4:  // Caso jogue na posicao 5
				if(jogou[jogou_pos-1] == 0){
					mapa[5][5] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			case 5:  // Caso jogue na posicao 6
				if(jogou[jogou_pos-1] == 0){
					mapa[5][9] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			case 6:  // Caso jogue na posicao 7
				if(jogou[jogou_pos-1] == 0){
					mapa[9][1] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			case 7:  // Caso jogue na posicao 8
				if(jogou[jogou_pos-1] == 0){
					mapa[9][5] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			case 8:  // Caso jogue na posicao 9
				if(jogou[jogou_pos-1] == 0){
					mapa[9][9] = carac;
					jogou[jogou_pos-1] = 1;
				} else {
					printf("Esta poscicao numero %i ja foi jogada\n", jogou_pos-1);
					jogadas--;
				}
				break;
			default:
				printf("Esta poscicao numero %i nao existe\n", jogou_pos-1);
				jogadas--; // desconsiderar jogada caso insira uma posicao que nao existe
		}
		// Tratar fim de jogo
		if(ganhou(mapa)){ 		  // Caso algum jogador tenha vencido
			desenharMap(mapa); // redesenha o mapa
			if(jogadas % 2){  	  // Se o resto da divisão por 2 for 0, Jogar O
				printf("\nO => Ganhou!");
			} else {
				printf("\nX => Ganhou!"); // Se o resto da divisão por 2 for diferente de 0, Jogar X
			}
			break;
		} else if(jogadas == 8){ // Se foram realizadas todas as jogadas e ninguem ganhou
			printf("\nEmpate!");
		}
		jogadas++; // Jogada realizada com sucesso
	}
	fflush(stdin); // corrigir problema do buffer que estava salvando enter como pressionado
	printf("\nDeseja salvar este jogo em txt? (y/n)\n");
	scanf("%c", &save);
	if(save == 121 || save == 89){ //comparar com y e Y, segundo a tabela ASCII
		arquivo(mapa);			   // salvar log de jogadas
	} else {
		system("cls"); 			   // limpar tela
		printf("Fim de jogo!");
	}
	return 0;
}
// link tabela ASCII: http://ic.unicamp.br/~everton/aulas/hardware/tabelaASCII.pdf
