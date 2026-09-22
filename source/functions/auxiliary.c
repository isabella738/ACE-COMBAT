#include "settings.h"
#include "sprites.h"
#include "definitions.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifdef SETTINGS

void limpar_buffer(){
    char c;
    while (read(STDIN_FILENO, &c, 1) > 0);
}

void pausa(){
    printf("Pressione qualquer tecla para continuar.\n");
    char c;
    while(1){
        if(read(STDIN_FILENO, &c, 1) > 0) break;
    }
}

int imprimir_entidade(int x, int y, Entidade entidade, char sprite[][2][ALTURA][LARGURA]){
    if(x >= entidade.p.x && x < entidade.p.x + entidade.largura
    && y >= entidade.p.y && y < entidade.p.y + entidade.altura){
        switch(entidade.estado){
            case 0: 
                printf("%c", sprite[nivel-1][0][y - entidade.p.y][x - entidade.p.x]);
                break;
            case 1: 
                printf(VERMELHO "%c" RESET, sprite[nivel-1][0][y - entidade.p.y][x - entidade.p.x]);
                break;
            default: 
                printf(AMARELO "%c" RESET, sprite[nivel-1][1][y - entidade.p.y][x - entidade.p.x]);
                break;
        }
        return 1;
    }
    return 0;
}

int imprimir_projeteis(int x, int y, Entidade e){

    for(int i=0; i < e.q_ataques; i++){
        for(int j=0; j < e.tiros_ps[i]; j++){
            for(int k=0; k < e.indices[i][j]; k++){
                
                Projetil prj = e.projetil[i][j][k];

                if(x == prj.p.x && y == prj.p.y){
                    printf("%s%c"RESET, cores[prj.cor], prj.c);
                    return 1;
                }

            }
        }
    }

    return 0;
}

void imprimir_em_cima(int altura, int largura, char imagem[altura][largura], int dx, int dy, int cor, float tempo){

    for(int y=0; y<ALTURA; y++){
        printf(CINZA"%s\n"RESET, mapa[y]);
    }
    printf(VOLTAR);

    for(int y=0; y<ALTURA; y++){
        for(int x=0; x<LARGURA; x++){
            
            if(x >= dx && x < dx + largura && y >= dy && y < dy + altura){
                printf("%s%c"RESET, cores[cor], imagem[y-dy][x-dx]);
                if(tempo)fflush(stdout);
                usleep(SEGUNDOS*tempo);
            }
            else printf(CINZA"%c"RESET, mapa[y][x]);

        }
        printf("\n");
    }
}

void imprimir_barra_de_vida(){
    int x = player.vida, max = inicializar_player[nivel-1].vida;

    int a;
    if(x*100/max > 50) a = 4;
    else if(x*100/max >25) a = 3;
    else a = 2;

    printf("%d %s", x, cores[a]);
    for(int i=0; i < 20*x/max; i++){
        printf("%c", barra_de_vida[i]);
    }
    printf(RESET"                   \n");
}

void imprimir_mapa(){
    for(int y=0; y < ALTURA; y++){
        for(int x=0; x < LARGURA; x++){
            int imp=0; //indica se aquela celula já foi impressa

            //Player
            imp = imprimir_entidade(x, y, player, sprite_player);
            if(!imp) imp = imprimir_projeteis(x, y, player);
            
            //Inimigos
            for(int i=0; i < max_inm && imp == 0; i++){
                imp = imprimir_entidade(x, y, inimigo[i], sprite_inimigos);
            }

            //Projeteis
            for(int i=0; i < max_inm && imp == 0; i++){
                imp = imprimir_projeteis(x, y, inimigo[i]);
            }

            //Vida extra
            if(!imp && vida.x == x && vida.y == y){
                imp = 1; printf(VERDE "@" RESET);
            }

            //Mapa
            if(!imp) printf(CINZA "%c" RESET, mapa[y][x]);
        }
        printf("\n");
    }
}

//
void informacoes_finais(){
    printf("\nPontuacao final: %d\n", pontos);
    printf("Numero de avioes abatidos: %d\n", abates_totais);
    printf("Nivel mais alto: %d\n", nivel);
}

void mensagem_de_mudanca_de_nivel(){
    switch(nivel){
        case 1:
            printf("VIDA +10\n");
            printf("DANO +1\n");
            printf("AVIAO + PODEROSO!\n");
            break;
        case 2:
            printf("VIDA +10\n");
            printf("TIRO DUPLO!\n");
            printf("AVIAO + PODEROSO!\n");
            break;
        case 3:
            informacoes_finais();
            printf("\nPor sua causa, os ceus agora estao a salvo!\nBom jogo!");
            break;
    }
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