#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "settings.h"
#include "sprites.h"
#include "auxiliary.h"

#ifdef SETTINGS

void gameover(){
        
    while(player.p.y <= ALTURA){
        printf(VOLTAR"\n\n");
        imprimir_mapa();
        player.p.y++;
        usleep(0.5*SEGUNDOS);
    }
    usleep(3*SEGUNDOS);
    system("clear");
    imprimir_em_cima(9, 18, tela_mudanca_de_nivel[0], 2, 6, 2, 0.01);
}

void Boss_Entering(){
    while(boss.p.y < 1){
        printf(VOLTAR);
        imprimir_em_cima(6, 20, sprite_boss[0], 1, -6, 1, 0);
        boss.p.y++;
        usleep(SEGUNDOS);
    }
    usleep(3*SEGUNDOS);
}

void Boss_Exit(){
    while(boss.p.y > -6){
        printf(VOLTAR);
        imprimir_em_cima(6, 20, sprite_boss[0], 1, -6, 1, 0.01);
        boss.p.y++;
        usleep(SEGUNDOS*0.01);
    }
    usleep(3*SEGUNDOS);
}

#endif