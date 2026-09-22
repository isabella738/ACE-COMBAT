#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "settings.h"
#include "sprites.h"
#include "auxiliary.h"

#ifdef SETTINGS

void gameover(){
        
    while(player.p.y <= ALTURA){
        printf(VOLTAR"\n");
        imprimir_mapa();
        player.p.y++;
        usleep(0.5*SEGUNDOS);
    }
    usleep(3*SEGUNDOS);
    system("clear");
    imprimir_em_cima(9, 18, tela_mudanca_de_nivel[0], 2, 6, 2, 0.01);
}

void Boss_Entering(){
    system("clear");
    while(inimigo[0].p.y < 1){
        inimigo[0].p.y++;

        printf(VOLTAR);
        
        imprimir_em_cima(
            inimigo[0].altura, 
            inimigo[0].largura+2, 
            sprite_inimigos[nivel-1][0], 
            inimigo[0].p.x, 
            inimigo[0].p.y, 
            2, 
            0
        );

        
        usleep(SEGUNDOS);
    }
    usleep(2*SEGUNDOS);
}

void Boss_Exit(){
    system("clear");
    while(inimigo[0].p.y >= -6){
        printf(VOLTAR"\n");
        
        imprimir_mapa();

        inimigo[0].p.y--;
        usleep(SEGUNDOS);
    }
    usleep(2*SEGUNDOS);
}

void subida_de_nivel(){
    limpar_buffer();
    int a = 0;

    while(1){
        printf(VOLTAR); usleep(SEGUNDOS*0.5);
        imprimir_em_cima(9, 20, level_up[nivel][a], 1, 6, 3, 0);
        a++;
        if(a==4)a=0;

        char c;
        if(read(STDIN_FILENO, &c, 1) > 0) break;

        mensagem_de_mudanca_de_nivel();

        printf("\nPressione qualquer tecla para continuar.\n\n");
    }
    system("clear");
}

#endif