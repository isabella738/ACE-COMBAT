#include <stdio.h>
#include <unistd.h>
#include "settings.h"
#include "sprites.h"
#include "auxiliares.h"

#ifdef SETTINGS

void gameover(){
    while(player.p.y < ALTURA){
        imprimir_em_cima(player.altura, player.largura, sprite_player[nivel][1], player.p.x, player.p.y, 3);
        player.p.y--;
        usleep(SEGUNDOS);
    }
    usleep(3*SEGUNDOS);
    imprimir_em_cima(9, 18, tela_mudanca_de_nivel[0], 2, 6, 1);
}

void Boss_Entering(){
    while(boss.p.y < 1){
        imprimir_em_cima(6, 20, sprite_boss[0], 1, -6, 1);
        boss.p.y++;
        usleep(SEGUNDOS);
    }
    usleep(3*SEGUNDOS);
}

void Boss_Exit(){
    while(boss.p.y > -6){
        imprimir_em_cima(6, 20, sprite_boss[0], 1, -6, 1);
        boss.p.y++;
        usleep(SEGUNDOS);
    }
    usleep(3*SEGUNDOS);
}

#endif