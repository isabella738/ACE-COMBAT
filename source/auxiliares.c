#include "settings.h"
#include "sprites.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifdef SETTINGS

void apagar_projetil(Coordenada p[], int x, int *max){
    for(int i=x; i<(*max); i++){
        p[i] = p[i+1];
    }
    (*max)--;
}

void apagar_entidade(Entidade p[], int x, int (*max)){
    for(int i=x; i<(*max); i++){
        p[i] = p[i+1];
    }
    (*max)--;
}

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

void imprimir_em_cima(int altura, int largura, char imagem[altura][largura], int dx, int dy, int cor){
    for(int y=0; y<ALTURA; y++){
        for(int x=0; x<LARGURA; x++){
            if(x >= dx && x < dx + largura
            && y >= dy && y < dy + altura){
                printf("%s%c"RESET, cores[cor], imagem[y-dy][x-dx]);
            }
            else printf(CINZA"%c"RESET, mapa[y][x]);
            
            usleep(SEGUNDOS/10);
        }
        printf("\n");
    }
}

void pausa(){
    printf("Pressione qualquer tecla para continuar.\n");
    char c;
    while(1){
        if(read(STDIN_FILENO, &c, 1) > 0) break;
    }
}

void apagar_tela(){
    printf(APAGAR);
}

void imprimir_barra_de_vida(int x, int max){
    for(int i=0; i < max/x; i++){
        printf("%c", barra_de_vida[i]);
        printf("                   ");
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