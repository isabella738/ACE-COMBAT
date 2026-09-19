#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "settings.h"
#include "sprites.h"
#include "inicializations.h"
#include "auxiliary.h"
#include "general_funcions.h"
#include "player_functions.h"
#include "enemy_functions.h"

/*
    Ordem de Execucao

    0. Definir configuracoes de fase
    1. Decrescer cooldowns e suas acoes (estados de entidade, spawn de objetos)
    2. Player: movimentacao propria e de seus projeteis
    3. Inimigos: movimentacao propria e de seus projeteis
    4. Colisoes
    5. Impressao
*/

#ifdef SETTINGS

int main_game(){
    imprimir_em_cima(9, 18, tela_mudanca_de_nivel[nivel], 2, 6, 5, 0.01);
    pausa(); system("clear");

    spawn_player(nivel);
    inicializar_constantes(nivel);

    max_inm=0; 
    int vitoria=0;

    while(1){
        printf(VOLTAR);
        usleep(SEGUNDOS/FPS);

        printf("Nivel: %d\n", nivel);
        printf("Pontos: %d\n", pontos);

        int atirar=0;

        cd_jogo();
        cd_inimigos();
    
        movimentacao_player(&atirar);
        movimentacao_projeteis(&player, -1);
        if(atirar) spawn_projetil(player.p.y-1, &player);

        for(int i=0; i<max_inm; i++){
            movimentacao_inimigos(&inimigo[i]);
            movimentacao_projeteis(&inimigo[i], 1);

            if(inimigo[i].cd_atirar < 0){
                inimigo[i].cd_atirar = inicializar_inimigo[nivel-1].cd_atirar;
                spawn_projetil(inimigo[i].p.y + inimigo[i].altura, &inimigo[i]);
            }
        }

        colisao_player_inimigo();
        colisao_inimigo_player();
        pegar_vida();

        imprimir_mapa();
        imprimir_barra_de_vida(player.vida, inicializar_player[nivel-1].vida);

        if(player.vida <= 0){
            player.estado = 2;
            printf(VOLTAR"\n\n");
            imprimir_mapa();
            break;
        }
        if(pontos == config.pontos_minimos){
            vitoria=1; break;
        }

        //info_para_debug();
    }

    usleep(1.5*SEGUNDOS);
    return vitoria;
}

int boss_fight(){
    imprimir_em_cima(9, 18, tela_mudanca_de_nivel[nivel], 2, 6, 5, 0.01);
    pausa();

    spawn_player(nivel);
    inicializar_constantes(nivel);

    int vitoria=0;

}

#endif