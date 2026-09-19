#include "settings.h"
#include "sprites.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifdef SETTINGS

int imprimir_entidade(int x, int y, Entidade entidade, char sprite[][2][3][8], int nivel){
    if(x >= entidade.p.x && x < entidade.p.x + entidade.largura
    && y >= entidade.p.y && y < entidade.p.y + entidade.altura){
        switch(entidade.estado){
            case 0: 
                printf("%c", sprite[nivel-1][0][y - entidade.p.y][x - entidade.p.x]);
                break;
            case 1: 
                printf(VERMELHO "%c" RESET, sprite[nivel-1][0][y - entidade.p.y][x - entidade.p.x]);
                break;
            case 2: 
                printf(AMARELO "%c" RESET, sprite[nivel-1][1][y - entidade.p.y][x - entidade.p.x]);
                break;
        }
        return 1;
    }
    return 0;
}

int imprimir_projeteis(int x, int y, Entidade entidade){
    for(int i=0; i < entidade.n_projeteis; i++){
        if(entidade.projetil[i].x == x && entidade.projetil[i].y == y){
            printf(AMARELO "*" RESET);
            return 1;
        }
    }
    return 0;
}

void imprimir_em_cima(int altura, int largura, char imagem[altura][largura], int dx, int dy, int cor, float tempo){
    
    for(int y=0; y<ALTURA; y++){
        printf(CINZA"%s\n"RESET, mapa[y]);
    }
    printf(VOLTAR);

    printf("\033[%dB", dy);

    for(int y=0; y<altura; y++){
        printf("\033[%dC", dx);

        for(int x=0; x<largura; x++){
            printf("%s%c"RESET, cores[cor], imagem[y][x]);
            if(imagem[y][x] != ' '){
                fflush(stdout);
                usleep(SEGUNDOS*tempo);
            }
        }
        printf("\n");
    }
    printf("\033[%dB", ALTURA - altura - dy);
}

void imprimir_barra_de_vida(int x, int max){
    for(int i=0; i < max/x; i++){
        printf("%c", barra_de_vida[i]);
        printf("                   ");
    }
}

void imprimir_mapa(int max){
    for(int y=0; y < ALTURA; y++){
        for(int x=0; x < LARGURA; x++){

            int imp=0; //indica se aquela celula já foi impressa

            //Player
            imp = imprimir_entidade(x, y, player, sprite_player, nivel);
            if(!imp) imp = imprimir_projeteis(x, y, player);

            //Inimigos
            if(!imp) for(int i=0; i < max || imp == 0; i++){
                imp = imprimir_entidade(x, y, inimigo[i], sprite_inimigos, nivel);
            }
            if(!imp) for(int i=0; i < max || imp == 0; i++){
                imp = imprimir_projeteis(x, y, inimigo[i]);
            }

            if(!imp) if(vida.x == x && vida.y == y){
                printf(VERDE "@" RESET); imp = 1;
            }

            if(!imp) printf(CINZA "%c" RESET, mapa[y][x]);
        }
        printf("\n");
    }
}

//

void pausa(){
    printf("Pressione qualquer tecla para continuar.\n");
    char c;
    while(1){
        if(read(STDIN_FILENO, &c, 1) > 0) break;
    }
}

void informacoes_finais(int pontos, int abates_totais, int nivel){
    printf("\nPontuacao final: %d\n", pontos);
    printf("Numero de avioes abatidos: %d\n", abates_totais);
    printf("Nivel mais alto: %d\n", nivel);
}

struct termios velho_terminal, novo_terminal;
void mudar_terminal(){
    tcgetattr(STDIN_FILENO, &velho_terminal);
    novo_terminal = velho_terminal;

    novo_terminal.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &novo_terminal);
}
void restaurar_terminal(){
    tcsetattr(STDIN_FILENO, TCSANOW, &velho_terminal);
}

#endif