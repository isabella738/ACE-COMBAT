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

    pre_processamento();
    max_inm=0; 
    int vitoria=0;
    int abates=abates_totais;

    if(nivel == MAX_NIVEIS) inicializar_boss1();

    while(1){
        printf(VOLTAR);
        usleep(SEGUNDOS/FPS);

        printf("Nivel: %d\n", nivel);

        if(player.estado == 1) player.estado = 0;
        for(int i=0; i<max_inm; i++) switch_estados(&inimigo[i]);

        cd_jogo();    
        player_acoes();
        inimigos_acoes();

        imprimir_mapa();
        imprimir_barra_de_vida(player.vida, inicializar_player[nivel-1].vida);
        printf("Pontos: %d\n", pontos);
        printf("Baixas: %d\n", abates_totais - abates);

        if(player.vida <= 0){
            player.estado = 2;
            printf(VOLTAR"\n");
            imprimir_mapa();
            break;
        }
        if(abates_totais - abates >= config.abates_minimos){
            vitoria=1; break;
        }

        //info_para_debug();
        //pausa();
    }

    if(nivel == MAX_NIVEIS){
        sleep(2);
        Boss_Exit();
    }

    usleep(1.5*SEGUNDOS);
    return vitoria;
}

void arcade(){
    max_inm = 0;
    nivel = 2;
    player = inicializar_player[2];
    config = configuracoes_de_fase[1];
    config.ativar_VidaExtra = 0;
    
    while(1){
        printf(VOLTAR);
        usleep(SEGUNDOS/FPS);

        printf("Modo Infinito\n");

        if(player.estado == 1) player.estado = 0;
        for(int i=0; i<max_inm; i++) switch_estados(&inimigo[i]);

        cd_jogo();    
        player_acoes();
        inimigos_acoes();

        imprimir_mapa();
        imprimir_barra_de_vida(player.vida, inicializar_player[nivel-1].vida);
        printf("Pontos: %d\n", pontos);
        printf("Baixas: %d\n", abates_totais);

        if(player.vida <= 0){
            player.estado = 2;
            printf(VOLTAR"\n");
            imprimir_mapa();
            break;
        }
        info_para_debug();
    }

    gameover();
    informacoes_finais();
}

#endif