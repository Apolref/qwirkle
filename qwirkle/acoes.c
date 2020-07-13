#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"cores.h"
#include"config.h"

#define MAXNOME 128

void trocar(int pos, jogadores *jogador, char *entrada, int tiles[36][3]){
	int i;
	int guardiao[6];
	for(i = 0; i < 6; i++){
		guardiao[i] = jogador[pos].tiles[i];
	}
	int guardiao2[36][3];
	for(i = 0; i < 36; i++){
		int j;
		for(j = 0; j < 3; j++){
			guardiao2[i][j] = tiles[i][j];
		}
	}
	int cont = 0;
	int cont_nump = 0;
	for(i = 0; entrada[i] != ' '; i++);
    while(entrada[i] != '\0'){
		int valor = entrada[i + 1] - 49;
		if(valor > 5 || valor < 0){
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			for(i = 0; i < 36; i++){
				int j;
				for(j = 0; j < 3; j++){
					tiles[i][j] = guardiao2[i][j];
				}
			}
			for(i = 0; i < 6; i++){
				jogador[pos].tiles[i] = guardiao[i];
			}
			return;
		}
		if(entrada[i + 2] == 'A' || entrada[i + 2] == 'a'){
		} else{
			if(entrada[i + 2] == 'B' || entrada[i + 2] == 'b'){
				valor += 10;
			} else{		
				if(entrada[i + 2] == 'C' || entrada[i + 2] == 'c'){
					valor += 20;
				} else{
					if(entrada[i + 2] == 'D' || entrada[i + 2] == 'd'){
						valor += 30;
					} else{
						if(entrada[i + 2] == 'E' || entrada[i + 2] == 'e'){
							valor += 40;
						} else{
							if(entrada[i + 2] == 'F' || entrada[i + 2] == 'f'){
								valor += 50;
							} else{
								vermelho();
								printf("Entrada Invalida...\n");
								padrao();
								for(i = 0; i < 36; i++){
									int j;
									for(j = 0; j < 3; j++){
										tiles[i][j] = guardiao2[i][j];
									}
								}
								for(i = 0; i < 6; i++){
									jogador[pos].tiles[i] = guardiao[i];
								}
								return;
							}
						}
					}
				}
			}
		}
		int j;
		for(j = 0; j < 6; j++){
			if(jogador[pos].tiles[j] == valor){
				int k;
				int flag = 1;
				for(k = 0; k < 36 && flag; k++){
					int l;
					for(l = 0; l < 3; l++){
						if(tiles[k][l] == -1 * valor){
							tiles[k][l] = -1 * valor;
							flag = 0;
							break;
						}
					}
				}
				flag = 1;
				while(flag){
					k = rand() % 36;
					int l;
					for(l = 0; l < 3; l++){
						if(tiles[k][l] >= 0){
							jogador[pos].tiles[j] = tiles[k][l];
							flag = 0;
							tiles[k][l] = -1*tiles[k][l];
							break;
						}
					}
				}
				cont_nump++;
				break;
			}
		}
		i++;
		for(i; entrada[i] != ' ' && entrada[i] != '\0'; i++);
		if(cont >= 6){
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			for(i = 0; i < 36; i++){
				int j;
				for(j = 0; j < 3; j++){
					tiles[i][j] = guardiao2[i][j];
				}
			}
			for(i = 0; i < 6; i++){
				jogador[pos].tiles[i] = guardiao[i];
			}
			return;
		}
		cont++;
	}
	if(cont_nump == 0){
		vermelho();
		printf("Entrada Invalida...\n");
		padrao();
	}
} 


int jogar(int pos, jogadores *jogador, char *entrada, int **board, int x, int y, int *value, int num_jogadas, int cont_jogada_vez, int cood_jogadas[7][2], int cheat){
	//cood jogada
	int lin;
	int col;
	int i;
	int j;
	//leitura peca
	for(i = 0; entrada[i] != ' '; i++);
	int valor = entrada[i + 1] - 49;
	if(valor > 5 || valor < 0){
		vermelho();
		printf("Entrada Invalida...\n");
		padrao();
		return -1;
	}
	if(entrada[i + 2] == 'A' || entrada[i + 2] == 'a'){
		} else{
			if(entrada[i + 2] == 'B' || entrada[i + 2] == 'b'){
				valor += 10;
			} else{		
				if(entrada[i + 2] == 'C' || entrada[i + 2] == 'c'){
					valor += 20;
				} else{
					if(entrada[i + 2] == 'D' || entrada[i + 2] == 'd'){
						valor += 30;
					} else{
						if(entrada[i + 2] == 'E' || entrada[i + 2] == 'e'){
							valor += 40;
						} else{
							if(entrada[i + 2] == 'F' || entrada[i + 2] == 'f'){
								valor += 50;
							} else{
								vermelho();
								printf("Entrada Invalida...\n");
								padrao();
								return -1;
						}
					}
				}
			}
		}
	}
	//verificacao se o jogador possui aquela peca
	int pos_tile = -1;
	for(j = 0; j < 6; j++){
		if(jogador[pos].tiles[j] == valor){
			pos_tile = j;
			break;
		}
	}
	if(entrada[i + 3] != ' '){
		vermelho();
		printf("Entrada Invalida...\n");
		padrao();
		return -1;
	}
	if(pos_tile == -1 && cheat == 0){
		vermelho();
		printf("Entrada Invalida...\n");
		padrao();
		return -1;
	}
	//leitura linha e coluna
	if(entrada[i + 5] != ' '){
		lin = (entrada[i + 5] - 48) + 10 * (entrada[i + 4] - 48);
		if(entrada[i + 8] != ' '){
			col = (entrada[i + 8] - 48) + 10 * (entrada[i + 7] - 48);
		} else{
			col = entrada[i + 7] - 48;
		}
	} else{
		lin = entrada[i + 4] - 48;
		if(entrada[i + 7] != ' ' && entrada[i + 7] != '\0'){
			col = (entrada[i + 7] - 48) + 10 * (entrada[i + 6] - 48);
		} else{
			col = entrada[i + 6] - 48;
		}
	}
	if(num_jogadas == 0){
		*value = valor;
		jogador[pos].tiles[pos_tile] = -1;
		cood_jogadas[0][0] = lin - 1;
		cood_jogadas[0][1] = col - 1;
		return 0;
	}
	if(lin > x || col > y || lin < 0 || col < 0 || board[lin - 1][col - 1] != -1){
		vermelho();
		printf("Entrada Invalida...\n");
		padrao();
		return -1;
	}
	//vereficar se ele esta tentando jogar numa casa valida
	//Verefica se a casa que ele esta jogando tem adjacentes validas e se tem alguma repetida na linha/coluna
	board[lin - 1][col - 1] = valor;
	//verificacao de para onde expandir e afericao jogada
	int flag_cima = 0;
	int flag_baixo = 0;
	int flag_direita = 0;
	int flag_esquerda = 0;
	for(i = 0; i < x; i++){
		if(board[i][0] != -1){
			//para esquerda
			flag_esquerda = 1;
			if(board[lin - 1][col] % 10 == valor % 10 || board[lin - 1][col] - board[lin - 1][col] % 10 == valor - valor % 10){
				for(j = col; board[lin - 1][j] != -1; j++){
					if(board[lin - 1][j] == valor){
						board[lin - 1][col - 1] = -1;
						vermelho();
						printf("Entrada Invalida...\n");
						padrao();
						return -1;
					}
				}
			} else{
				board[lin - 1][col - 1] = -1;
				vermelho();
				printf("Entrada Invalida...\n");
				padrao();
				return -1;
			}
		}
		if(board[i][y - 1] != -1){
			//para direita
			flag_direita = 1;
			if(board[lin - 1][col - 2] % 10 == valor % 10 || board[lin - 1][col - 2] - board[lin - 1][col - 2] % 10 == valor - valor % 10){
				for(j = col - 2; board[lin- 1][j] != -1; j--){
					if(board[lin - 1][j] == valor){
						board[lin - 1][col - 1] = -1;
						vermelho();
						printf("Entrada Invalida...\n");
						padrao();
						return -1;
					}
				}
			} else{
				board[lin - 1][col - 1] = -1;
				vermelho();
				printf("Entrada Invalida...\n");
				padrao();
				return -1;
			}
		}
	}
	for(i = 0; i < y; i++){
		if(board[0][i] != -1){
			//para cima
			flag_cima = 1;
			if(board[lin][col - 1] % 10 == valor % 10 || board[lin][col - 1] - board[lin][col -1] % 10 == valor - valor % 10){
				for(j = lin; board[j][col - 1] != -1; j++){
					if(board[j][col - 1] == valor){
						board[lin - 1][col - 1] = -1;
						vermelho();
						printf("Entrada Invalida...\n");
						padrao();
						return -1;
					}
				}
			} else{
				board[lin - 1][col - 1] = -1;
				vermelho();
				printf("Entrada Invalida...\n");
				padrao();
				return -1;
			}
		}
		if(board[x - 1][i] != -1){
			//Para baixo
			flag_baixo = 1;
			if(board[lin - 2][col - 1] % 10 == valor % 10 || board[lin - 2][col - 1] - board[lin - 2][col - 1] % 10 == valor - valor % 10){
				for(j = lin - 2; board[j][col - 1] != -1; j--){
					if(board[j][col - 1] == valor){
						board[lin - 1][col - 1] = -1;
						vermelho();
						printf("Entrada Invalida...\n");
						padrao();
						return -1;
					}
				}
			} else{
				board[lin - 1][col - 1] = -1;
				vermelho();
				printf("Entrada Invalida...\n");
				padrao();
				return -1;
			}
		}
	}
	if(!flag_direita && !flag_esquerda && !flag_cima && !flag_baixo){
		if(board[lin - 2][col - 1] == -1 && board[lin][col - 1] == -1 && board[lin - 1][col - 2] == -1 && board[lin - 1][col] == -1){
			board[lin - 1][col - 1] = -1;
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			return -1;
		}
		if(board[lin][col - 1] % 10 == valor % 10 || board[lin][col - 1] - board[lin][col -1] % 10 == valor || board[lin][col - 1] == -1){
			if(board[lin - 2][col - 1] % 10 == valor % 10 || board[lin - 2][col - 1] - board[lin - 2][col - 1] % 10 == valor - valor % 10 || board[lin - 2][col - 1] == -1){
				if(board[lin - 1][col] % 10 == valor % 10 || board[lin - 1][col] - board[lin - 1][col] % 10 == valor - valor % 10 || board[lin - 1][col] == -1){
					if(board[lin - 1][col - 2] % 10 == valor % 10 || board[lin - 1][col - 2] - board[lin - 1][col - 2] % 10 == valor - valor % 10 || board[lin - 1][col - 2] == -1){
						for(i = lin; i > 0 && i < x && board[i][col - 1] != -1; i++){
							if(board[i][col - 1] == valor){
								board[lin - 1][col - 1] = -1;
								vermelho();
								printf("Entrada Invalida...\n");
								padrao();
								return -1;
							}
						}
						for(i = lin - 2; i > 0 && i < x && board[i][col] != -1; i--){
							if(board[i][col] == valor){
								board[lin - 1][col - 1] = -1;
								vermelho();
								printf("Entrada Invalida...\n");
								padrao();
								return -1;
							}
						}
						for(i = col; i > 0 && i < y && board[lin - 1][i] != -1; i++){
							if(board[lin - 1][i] == valor){
								board[lin - 1][col - 1] = -1;
								vermelho();
								printf("Entrada Invalida...\n");
								padrao();
								return -1;
							}
						}
						for(i = col - 2; i > 0 && i < y && board[lin - 1][i] != -1; i--){
							if(board[lin - 1][i] == valor){
								board[lin - 1][col - 1] = -1;
								vermelho();
								printf("Entrada Invalida...\n");
								padrao();
								return -1;
							}
						}
					} else{
						board[lin - 1][col - 1] = -1;
						vermelho();
						printf("Entrada Invalida...\n");
						padrao();
						return -1;
					}
				} else{
					board[lin - 1][col - 1] = -1;
					vermelho();
					printf("Entrada Invalida...\n");
					padrao();
					return -1;
				}
			} else{
				board[lin - 1][col - 1] = -1;
				vermelho();
				printf("Entrada Invalida...\n");
				padrao();
				return -1;
			}
		} else{
			board[lin - 1][col - 1] = -1;
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			return -1;
		}
	}
	//Todas as pecas na linha/coluna tem o mesmo tipo?
	for(i = lin - 1;i < x && board[i][col - 1] != -1; i++){
		if(board[i][col - 1] % 10 != valor % 10 && board[i][col - 1] - board[i][col - 1] % 10 != valor - valor % 10){
			board[lin - 1][col - 1] = -1;
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			return -1;
		}
	}
	for(j = lin - 1; j > 0 && board[j][col - 1] != -1; j--){
		if(board[j][col - 1] % 10 != valor % 10 && board[j][col - 1] - board[j][col - 1] % 10 != valor - valor % 10){
			board[lin - 1][col - 1] = -1;
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			return -1;
		}
	}
	for(i = col - 1; i < y && board[lin - 1][i] != -1; i++){
		if(board[lin - 1][i] % 10 != valor % 10 && board[lin - 1][i] - board[lin - 1][i] % 10 != valor - valor % 10){
			board[lin - 1][col - 1] = -1;
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			return -1;
		}
	}
	for(i = col - 1; i > 0  && board[lin - 1][i] != -1; i--){
		if(board[lin - 1][i] % 10 != valor % 10 && board[lin - 1][i] - board[lin - 1][i] % 10 != valor - valor % 10){
			board[lin - 1][col - 1] = -1;
			vermelho();
			printf("Entrada Invalida...\n");
			padrao();
			return -1;
		}
	}
	//afericao se ele esta jogando numa mesma linha em sua vez
	if(cont_jogada_vez == 0){
		cood_jogadas[0][0] = lin - 1;
		cood_jogadas[0][1] = col - 1;
	} else{
		if(cont_jogada_vez == 1){
			if(lin - 1 == cood_jogadas[0][0] + 1 && cood_jogadas[0][1] == col - 1){
				cood_jogadas[1][0] = lin - 1;
				cood_jogadas[1][1] = col - 1;
				cood_jogadas[6][0] = -1;
				cood_jogadas[6][1] = col - 1;
			} else{
				if(lin - 1 == cood_jogadas[0][0] - 1 && cood_jogadas[0][1] == col - 1){
					cood_jogadas[1][0] = lin - 1;
					cood_jogadas[1][1] = col - 1;
					cood_jogadas[6][0] = -1;
					cood_jogadas[6][1] = col - 1;
				} else{
					if(col - 1 == cood_jogadas[0][1] + 1 && cood_jogadas[0][0] == lin - 1){
						cood_jogadas[1][0] = lin - 1;
						cood_jogadas[1][1] = col - 1;
						cood_jogadas[6][0] = lin - 1;
						cood_jogadas[6][1] = -1;
					} else{
						if(col - 1 == cood_jogadas[0][1] - 1 && cood_jogadas[0][0] == lin - 1){
							cood_jogadas[1][0] = lin - 1;
							cood_jogadas[1][1] = col - 1;
							cood_jogadas[6][0] = lin - 1;
							cood_jogadas[6][1] = -1;
						} else{
							board[lin - 1][col - 1] = -1;
							vermelho();
							printf("Entrada Invalida...\n");
							padrao();
							return -1;
						}
					}
				}
			}
		} else{
			if(lin - 1 == cood_jogadas[6][0]){
				if(cood_jogadas[cont_jogada_vez - 1][1] == col || cood_jogadas[cont_jogada_vez - 1][1] == col - 2){
					cood_jogadas[cont_jogada_vez][0] = lin - 1;
					cood_jogadas[cont_jogada_vez][1] = col - 1;
				} else{
					board[lin - 1][col - 1] = -1;
					vermelho();
					printf("Entrada Invalida...\n");
					padrao();
					return -1;
				}
			} else{
				if(col - 1 == cood_jogadas[6][1]){
					if(cood_jogadas[cont_jogada_vez - 1][0] == lin || cood_jogadas[cont_jogada_vez - 1][0] == lin - 2){
						cood_jogadas[cont_jogada_vez][0] = lin - 1;
						cood_jogadas[cont_jogada_vez][1] = col - 1;
					}else{
						board[lin - 1][col - 1] = -1;
						vermelho();
						printf("Entrada Invalida...\n");
						padrao();
						return -1;
					}
				}else{
					board[lin - 1][col - 1] = -1;
					vermelho();
					printf("Entrada Invalida...\n");
					padrao();
					return -1;
				}
			}
		}
	}
	if(pos_tile != -1){
		jogador[pos].tiles[pos_tile] = -1;
	}
	if(flag_cima){
		return 1;
	}
	if(flag_baixo){
		return 2;
	}
	if(flag_esquerda){
		return 3;
	}
	if(flag_direita){
		return 4;
	}
	return 0;
}

void print_board(int **board, int x, int y){
	int i, j, z;
	printf("  ");
	for (i=0; i<y; i++){
		printf (" %d ", i+1);
	}
	printf("\n");
	for (i=0; i<x ;i++){
		printf("%d |", i + 1);
		for(j=0 ; j<y ; j++){
			if(board[i][j]==-1){
				printf("  |");
			} else {
				if(board[i][j] < 10){
					vermelho();
					printf("%dA", board[i][j] + 1);
					padrao();
					printf("|");
				} else{
					if(board[i][j] < 20){
						verde();
						printf("%dB", board[i][j] - 9);
						padrao();
						printf("|");
					} else {
						if(board[i][j] < 30){
							roxo();
							printf("%dC", board[i][j] - 19);
							padrao();
							printf("|");
						} else {
							if(board[i][j] < 40){
								azul_claro();
								printf("%dD", board[i][j] - 29);
								padrao();
								printf("|");
							} else{
								if(board[i][j] < 50){
									azul();
									printf("%dE", board[i][j] - 39);
									padrao();
									printf("|");
								} else {
									if(board[i][j] < 60){
										laranja();
										printf("%dF", board[i][j] - 49);
										padrao();
										printf("|");
									}
								}
							}
						}
					}
				}
				
			}
			
		}
		printf(" %d", i + 1);
		printf("\n");
		for (z=0;i != x - 1 && z<y;z++){
			printf("----");
		}
		if(i != x - 1){
			printf("\n");
		}
	}
	printf("  ");
	for (i=0; i<y; i++){
		printf (" %d ", i+1);
	}
	printf("\n");
}


void score(int pos, jogadores *jogador, int x, int y, int **board, int cood_jogadas[7][2]){
	int **aux_board = (int **) calloc(x, sizeof(int *));
	if(aux_board == NULL){
		vermelho();
		printf("Erro de Alocacao...\n");
		padrao();
		exit(1);
	}
	int i, j;
	for(i = 0; i < x; i++){
		aux_board[i] = (int *) calloc(y, sizeof(int));
		if(aux_board[i] == NULL){
			vermelho();
			printf("Erro de Alocacao...\n");
			padrao();
			exit(1);
		}
	}
	for(i = 0; i < 6; i++){
		if(cood_jogadas[i][0] != -1){
			for(j = cood_jogadas[i][0]; j < x; j++){
				if(board[j][cood_jogadas[i][1]] != -1){
					aux_board[j][cood_jogadas[i][1]] = 1;
				} else{
					break;
				}
			}
			for(j = cood_jogadas[i][0]; j >= 0; j--){
				if(board[j][cood_jogadas[i][1]] != -1){
					aux_board[j][cood_jogadas[i][1]] = 1;
				} else{
					break;
				}
			}
			for(j = cood_jogadas[i][1]; j < y; j++){
				if(board[cood_jogadas[i][0]][j] != -1){
					aux_board[cood_jogadas[i][0]][j] = 1;
				} else{
					break;
				}
			}
			for(j = cood_jogadas[i][1]; j >= 0; j--){
				if(board[cood_jogadas[i][0]][j] != -1){
					aux_board[cood_jogadas[i][0]][j] = 1;
				} else{
					break;
				}
			}
		}
	}
	int score = 0;
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			if(aux_board[i][j] == 1){
				jogador[pos].score++;
				score++;
			}
		}
	}
	int cont = 0;
	int num_quirkle = 0;
	int col_quirkle = -1;
	int lin_quirkle = -1;
	for(i = 0; i < 6; i++){
		if(cood_jogadas[i][0] != -1){
			for(j = cood_jogadas[i][0] ; aux_board[j][cood_jogadas[i][1]] != 0 && col_quirkle != cood_jogadas[i][1]; j++){
				cont++;
				if(cont == 6){
					num_quirkle++;
					col_quirkle = cood_jogadas[i][1];
				}
			}
			cont = 0;
			for(j = cood_jogadas[i][0]; aux_board[j][cood_jogadas[i][1]] != 0 && col_quirkle != cood_jogadas[i][1]; j--){
				cont++;
				if(cont == 6){
					num_quirkle++;
					col_quirkle = cood_jogadas[i][1];
				}
			}
			cont = 0;
			for(j = cood_jogadas[i][1]; aux_board[cood_jogadas[i][0]][j] != 0 && lin_quirkle != cood_jogadas[i][0]; j++){
				cont++;
				if(cont == 6){
					num_quirkle++;
					lin_quirkle = cood_jogadas[i][0];
				}
			}
			cont = 0;
			for(j = cood_jogadas[i][1]; aux_board[cood_jogadas[i][0]][j] != 0 && lin_quirkle != cood_jogadas[i][0]; j--){
				cont++;
				if(cont == 6){
					num_quirkle++;
					lin_quirkle = cood_jogadas[i][0];
				}
			}
			cont = 0;
		}
	}
	jogador[pos].score = jogador[pos].score + num_quirkle * 6;
	for(i = 0; i < x; i++){
		free(aux_board[i]);
	}
	free(aux_board);
	printf("****************************************\npontuacao %s: %d/ acumulada: %d\n****************************************\n", jogador[pos].nome, score + num_quirkle * 6, jogador[pos].score);
}