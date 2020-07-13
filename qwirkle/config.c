#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"cores.h"

#define MAXNOME 128

void config_iniciais(int tiles[36][3], int numj, jogadores *jogador){
	int i;
	int cont = 0;;
	int j = 0;
	int k;
	for(i = 0; i < 36; i++){
		for(k = 0; k < 3; k++){
			tiles[i][k] = j;
		}
		cont++;
		if(cont == 6){
			j += 4;
			cont = 0;
		}
		j++;

	}
	
	srand(time(NULL));
	for(i = 0; i < numj; i++){
		jogador[i].score = 0;
		for(j = 0; j < 6; j++){
			int flag = 1;
			while(flag){
				k = rand() % 36;
				int l;
				for(l = 0; l < 3; l++){
					if(tiles[k][l] >= 0){
						jogador[i].tiles[j] = tiles[k][l];
						flag = 0;
						tiles[k][l] = -1*tiles[k][l];
						break;
					}
				}
			}
		}
	}
}

void print_pecas(jogadores jogador){
	int i;
	printf("%s: ", jogador.nome);
	for(i = 0; i < 6; i++){
		if(jogador.tiles[i] >= 0){
			if(jogador.tiles[i] < 10){
				vermelho();
				printf("%dA ", jogador.tiles[i] + 1);
				padrao();
				continue;
			}
			if(jogador.tiles[i] < 20){
				verde();
				printf("%dB ", jogador.tiles[i] - 9);
				padrao();
				continue;
			}
			if(jogador.tiles[i] < 30){
				roxo();
				printf("%dC ", jogador.tiles[i] - 19);
				padrao();
				continue;
			}
			if(jogador.tiles[i] < 40){
				azul_claro();
				printf("%dD ", jogador.tiles[i] - 29);
				padrao();
				continue;
			}
			if(jogador.tiles[i] < 50){
				azul();
				printf("%dE ", jogador.tiles[i] -39);
				padrao();
				continue; 
			}
			if(jogador.tiles[i] < 60){
				laranja();
				printf("%dF ", jogador.tiles[i] - 49);
				padrao();
			}
		}
	}
	printf("\n");
}

int leitura(char *aux){
    int i;
    for(i = 0; aux[i] != ' '; i++);
    char primeira_palavra[MAXNOME];
    strcpy(primeira_palavra, aux);
    primeira_palavra[i] = '\0';
    if(!strcmp(primeira_palavra, "trocar") || !strcmp(primeira_palavra, "t") || !strcmp(primeira_palavra, "Trocar") || !strcmp(primeira_palavra, "T")){
        return 1;
    }
    if(!strcmp(primeira_palavra, "jogar") || !strcmp(primeira_palavra, "j") || !strcmp(primeira_palavra, "J") || !strcmp(primeira_palavra, "Jogar")){
        return 2;
    }
    if(!strcmp(primeira_palavra, "passar") || !strcmp(primeira_palavra, "p") || !strcmp(primeira_palavra, "P") || !strcmp(primeira_palavra, "Passar")){
        return 3;
    }
	vermelho();
	printf("Entrada Invalida...\n");
	padrao();
    return 0;
}
