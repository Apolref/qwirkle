#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"cores.h"
#include"config.h"
#include"acoes.h"

#define MAXNOME 128

void main(){
	//*Definições*
	printf("Numero de jogadores: ");
	int numj;
	scanf("%d", &numj);
	getc(stdin); //remove o lixo no buffer do teclado
	jogadores *jogador = malloc (numj * sizeof(jogadores));
	int i, j, k;
	for (i = 0; i < numj; i++){
		printf("Digite o nome do jogador #%d: ", i + 1);
		fgets(jogador[i].nome, MAXNOME, stdin);
		for(j = 0; jogador[i].nome[j] != '\n'; j++);
		jogador[i].nome[j] = '\0';
	}
	int cheat_mode;
	while(1){
		char aux;
		cheat_mode = -1;
		printf("Cheat mode (s/n): ");
		aux = getc(stdin);
		setbuf(stdin, NULL); //Caso o usuario digite mais de um caracter
		switch (aux){
			case 'S':
			case 's':
				cheat_mode = 1;
				break;
			case 'N':
			case 'n':
				cheat_mode = 0;
				break;
			default:
				break;
		}
		if(cheat_mode != -1){
			break;
		} else{
			printf("Entrada invalida...\n");
		}
	}
	//"Saquinho de pecas"
	int tiles[36][3];
	config_iniciais(tiles, numj, jogador);
	
	int **board = (int **) malloc (sizeof(int*));
	if(board == NULL){
		vermelho();
		printf("Erro de Alocacao...\n");
		padrao();
		exit(1);
	}
	board[0] = (int *) malloc(sizeof(int));
	if(board[0] == NULL){
		vermelho();
		printf("Erro de Alocacao...\n");
		padrao();
		exit(1);
	}
	board[0][0] = -1;
	int x = 1;
	int y = 1;

    int num_jogadas = 0;
	int cont_jogadas_rodada = 0;
    int escolha = 0;
    int expandir = 0;
	int cood_jogadas[7][2];
	for(i = 0; i < 7; i++){
		for(j = 0; j < 2; j++){
			cood_jogadas[i][j] = -1;
		}
	}
    while(num_jogadas < 108){
        for(i = 0; i < numj; i++){
			if(cont_jogadas_rodada == 0 && num_jogadas != 0){
				int g, h;
				int cont_tiles = 0;
				for(g = 0; g < 36; g++){
					for(h = 0; h < 3; h++){
						if(tiles[g][h] >= 0){
							cont_tiles++;
						}
					}
				}
				for(j = 0; j < 6 && cont_tiles != 0; j++){
					if(jogador[i].tiles[j] == -1){
						k = rand() % 36;
						int l;
						for(l = 0; l < 3 && cont_tiles != 0; l++){
							if(tiles[k][l] >= 0){
								jogador[i].tiles[j] = tiles[k][l];
								tiles[k][l] = -1*tiles[k][l];
								cont_tiles--;
								break;
							}
						}
					}
				}
			}
			while(1){
				for(j = 0; j < numj; j++){
					printf("Jogador %s (Score %d)\n", jogador[j].nome, jogador[j].score);
				}
				printf("=========================================\n");
				printf("Jogada do(a) jogador(a): %s\n", jogador[i].nome);
				print_board(board, x, y);
				printf("Pecas disponiveis: ");
				print_pecas(jogador[i]);
				if(cont_jogadas_rodada == 0){
					printf("opcoes: trocar p1[p2 p3 ...] | jogar p1 x y | passar\n");
				} else{
					printf("opcoes: jogar p1 x y | passar\n");
				}
				char entrada[MAXNOME];
				setbuf(stdin, NULL);
				fgets(entrada, MAXNOME, stdin);
				for(j = 0; entrada[j] != '\n'; j++);
				entrada[j] = '\0';
				escolha = leitura(entrada);
				if(escolha == 1){
					if(cont_jogadas_rodada == 0){
						trocar(i, jogador, entrada, tiles);
					} else{
						vermelho();
						printf("Entrada Invalida...\n");
						padrao();
					}
				}
				if(escolha == 2){
					int value = -1;
					expandir = jogar(i, jogador, entrada, board, x, y, &value, num_jogadas, cont_jogadas_rodada, cood_jogadas, cheat_mode);
					if(num_jogadas == 0){
						for(j = 0; j < x; j++){
							free(board[i]);
						}
						free(board);
						x = 3;
						y = 3;
						board = (int **) malloc(x * sizeof(int *));
						if(board == NULL){
							vermelho();
							printf("Erro de Alocacao...\n");
							padrao();
							exit(1);
						}
						for(j = 0; j < x; j++){
							board[j] = (int *) malloc(y * sizeof(int));
							if(board[j] == NULL){
								vermelho();
								printf("Erro de Alocacao...\n");
								padrao();
								exit(1);
							}
						}
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								board[j][k] = -1;
							}	
						}
						board[1][1] = value;
						for(j = 0; j < 7; j++){
							for(k = 0; k < 2; k++){
								if(cood_jogadas[j][k] != -1){
									cood_jogadas[j][k] += 1;
								}
							}
						}
					}
					//para cima
					if(expandir == 1){
						int aux_board[x][y];
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								aux_board[j][k] = board[j][k];
							}
							free(board[j]);
						}
						free(board);
						x++;
						board = (int **) malloc(x * sizeof(int *));
						if(board == NULL){
							vermelho();
							printf("Erro de Alocacao...\n");
							padrao();
							exit(1);
						}
						for(j = 0; j < x; j++){
							board[j] = (int *) malloc(y * sizeof(int));
							if(board[j] == NULL){
								vermelho();
								printf("Erro de Alocacao...\n");
								padrao();
								exit(1);
							}
						}
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								board[j][k] = -1;
							}	
						}
						for(j = 0; j < x - 1; j++){
							for(k = 0; k < y; k++){
								board[j + 1][k] = aux_board[j][k];
							}
						}
						for(j = 0; j < 7; j++){
							if(cood_jogadas[j][0] != -1){
								cood_jogadas[j][0] += 1;
							}
						}
					}
					//Para baixo
					if(expandir == 2){
						int aux_board[x][y];
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								aux_board[j][k] = board[j][k];
							}
							free(board[j]);
						}
						free(board);
						x++;
						board = (int **) malloc(x * sizeof(int *));
						if(board == NULL){
							vermelho();
							printf("Erro de Alocacao...\n");
							padrao();
							exit(1);
						}
						for(j = 0; j < x; j++){
							board[j] = (int *) malloc(y * sizeof(int));
							if(board[j] == NULL){
								vermelho();
								printf("Erro de Alocacao...\n");
								padrao();
								exit(1);
							}
						}
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								board[j][k] = -1;
							}	
						}
						for(j = 0; j < x - 1; j++){
							for(k = 0; k < y; k++){
								board[j][k] = aux_board[j][k];
							}
						}
					}
					//Para esquerda
					if(expandir == 3){
						int aux_board[x][y];
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								aux_board[j][k] = board[j][k];
							}
							free(board[j]);
						}
						free(board);
						y++;
						board = (int **) malloc(x * sizeof(int *));
						if(board == NULL){
							vermelho();
							printf("Erro de Alocacao...\n");
							padrao();
							exit(1);
						}
						for(j = 0; j < x; j++){
							board[j] = (int *) malloc(y * sizeof(int));
							if(board[j] == NULL){
								vermelho();
								printf("Erro de Alocacao...\n");
								padrao();
								exit(1);
							}
						}
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								board[j][k] = -1;
							}	
						}
						for(j = 0; j < x; j++){
							for(k = 0; k < y - 1; k++){
								board[j][k + 1] = aux_board[j][k];
							}
						}
						for(j = 0; j < 7; j++){
							if(cood_jogadas[j][1] != -1){
								cood_jogadas[j][1] += 1;
							}
							
						}
					}
					//Para direita
					if(expandir == 4){
						int aux_board[x][y];
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								aux_board[j][k] = board[j][k];
							}
							free(board[j]);
						}
						free(board);
						y++;
						board = (int **) malloc(x * sizeof(int *));
						if(board == NULL){
							vermelho();
							printf("Erro de Alocacao...\n");
							padrao();
							exit(1);
						}
						for(j = 0; j < x; j++){
							board[j] = (int *) malloc(y * sizeof(int));
							if(board[j] == NULL){
								vermelho();
								printf("Erro de Alocacao...\n");
								padrao();
								exit(1);
							}
						}
						for(j = 0; j < x; j++){
							for(k = 0; k < y; k++){
								board[j][k] = -1;
							}	
						}
						for(j = 0; j < x; j++){
							for(k = 0; k < y - 1; k++){
								board[j][k] = aux_board[j][k];
							}
						}
					}
					if(expandir != -1){
						num_jogadas++;
						cont_jogadas_rodada++;
					}
				}
				if(escolha == 3){
					score(i, jogador, x, y, board, cood_jogadas);
					
					cont_jogadas_rodada = 0;
					for(j = 0; j < 7; j++){
						for(k = 0; k < 2; k++){
							cood_jogadas[j][k] = -1;
						}
					}
					break;
				}
				int cont_tiles = 0;
				int g,h;
				for(g = 0; g < 36; g++){
					for(h = 0; h < 3; h++){
						if(tiles[g][h] >= 0){
							cont_tiles++;
						}
					}
				}
				h = 0;
				for(g = 0; g < 6; g++){
					if(jogador[i].tiles[g] != -1){
						h++;
					}
				}
				if(h == 0 && cont_tiles == 0){
					jogador[i].score += 6;
					break;
				}
			}
        }
    }
	for(j = 0; j < numj; j++){
		printf("Jogador %s (Score %d)\n", jogador[j].nome, jogador[j].score);
	}
	free(jogador);
}
