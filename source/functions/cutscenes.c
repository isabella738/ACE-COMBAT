/*
    Algoritmos para "animacoes" em momentos especiais do jogo
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "settings.h"
#include "sprites.h"
#include "auxiliary.h"
#include "terminal.h"

void gameover(){
        
    while(player.p.y <= ALTURA){
        printf(VOLTAR"\n");
        imprimir_mapa();
        player.p.y++;
        sleep_ms(0.5*SEGUNDOS);
    }
    sleep_ms(3*SEGUNDOS);
    limpar_tela();
    imprimir_em_cima(9, 18, tela_mudanca_de_nivel[0], 2, 6, 2, 0.01);
}

void Boss_Entering(){
    limpar_tela();
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

        
        sleep_ms(SEGUNDOS);
    }
    sleep_ms(2*SEGUNDOS);
}

void Boss_Exit(){
    limpar_tela();
    while(inimigo[0].p.y >= -6){
        printf(VOLTAR"\n");
        
        imprimir_mapa();

        inimigo[0].p.y--;
        sleep_ms(SEGUNDOS);
    }
    sleep_ms(2*SEGUNDOS);
}

void subida_de_nivel(){
    limpar_buffer();
    int a = 0;

    while(1){
        printf(VOLTAR); sleep_ms(SEGUNDOS*0.5);
        imprimir_em_cima(9, 20, level_up[nivel][a], 1, 6, 3, 0);
        a++;
        if(a==4)a=0;

        char c;
        if(ler_teclado(&c)) break;

        mensagem_de_mudanca_de_nivel();

        printf("\nPressione qualquer tecla para continuar.\n\n");
    }
    limpar_tela();
}
