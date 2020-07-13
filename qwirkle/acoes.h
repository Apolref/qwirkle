void trocar(int pos, jogadores *jogador, char *entrada, int tiles[36][3]);
int jogar(int pos, jogadores *jogador, char *entrada, int **board, int x, int y, int *value, int num_jogadas, int cont_jogada_vez, int cood_jogadas[7][2], int cheat);
void print_board(int **board, int x, int y);
void score(int pos, jogadores *jogador, int x, int y, int **board, int cood_jogadas[7][2]);
