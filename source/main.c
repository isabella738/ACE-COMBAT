/*
    O main contem o loop onde de fato o jogo roda.
    Segue-se o seguinte algoritmo:

    0. Inicializar variaveis (configurações de fase, player, numeros inteiros)
    Dentro do while:
        1. Decrescer cooldowns e suas acoes (estados de entidade, spawn de objetos)
        2. Mudar estados das entidades
        3. Player: movimentacao propria e de seus projeteis
        4. Inimigos: movimentacao propria e de seus projeteis
        5. Colisoes
        6. Impressao
    
    Todos esses passos consistem em uma serie de calculos que resultam em 1 frame.
    Ao final da impressao, o cursor volta para o inicio da tela e, depois de mais um loop, imprime
    um novo frame na tela, dando a impressao de movimento.

    Este codigo possui 2 funcoes:
        - main_game: modo de fases, encerra quando o player chega a um certo numero de abates
        - arcade: modo infinito, spawna inimigos de diferentes fases. encerra quando o player morre.
        
*/

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