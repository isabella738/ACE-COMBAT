#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "settings.h"
#include "sprites.h"
#include "definitions.h"
#include "auxiliary.h"
#include "general_funcions.h"
#include "player_functions.h"
#include "enemy_functions.h"
#include "cutscenes.h"

/*
    Ordem de Execucao

    1. Decrescer cooldowns e suas acoes (estados de entidade, spawn de objetos)
    2. Player: movimentacao propria e de seus projeteis
    3. Inimigos: movimentacao propria e de seus projeteis
    4. Colisoes
    5. Impressao

*/

#ifdef SETTINGS

int main_game(){

    max_inm=0; 
    int vitoria=0;

    while(1){
        printf(VOLTAR);
        usleep(SEGUNDOS/FPS);

        printf("Nivel: %d\n", nivel);
        printf("Pontos: %d\n", pontos);

        cd_jogo();    
        player_acoes();
        inimigos_acoes();

        imprimir_mapa();
        imprimir_barra_de_vida(player.vida, inicializar_player[nivel-1].vida);

        if(player.vida <= 0){
            player.estado = 2;
            printf(VOLTAR"\n\n");
            imprimir_mapa();
            break;
        }
        if(pontos >= config.pontos_minimos){
            vitoria=1; break;
        }

        //info_para_debug();
    }

    usleep(1.5*SEGUNDOS);
    return vitoria;
}

int boss_fight(){

    int vitoria=0;
    Boss_Entering();
    
    while(1){
        printf(VOLTAR);
        usleep(SEGUNDOS/FPS);

        printf("Nivel: %d\n", nivel);
        printf("Pontos: %d\n", pontos);

        
        
        
        imprimir_mapa();
        imprimir_barra_de_vida(player.vida, inicializar_player[nivel-1].vida);

        if(player.vida <= 0){
            player.estado = 2;
            printf(VOLTAR"\n\n");
            imprimir_mapa();
            break;
        }
        if(boss.vida <= 0){
            printf(VOLTAR"\n\n");
            Boss_Exit();
            break;
        }
    }

    if(vitoria) Boss_Exit();
    return vitoria;
}

#endif