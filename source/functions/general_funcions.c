#include "settings.h"
#include "definitions.h"
#include "enemy_functions.h"
#include "player_functions.h"
#include "sprites.h"
#include "auxiliary.h"
#include <stdlib.h>
#include <stdio.h> 

//Spawns
void spawn_vida(){
    int x, y;
    while(1){
        x = rand()%(LARGURA-2) + 1;
        y = rand()%(ALTURA - LINHA_LIMITE - 1) + LINHA_LIMITE - 1;
        
        if(x >= player.p.x && x < player.p.x + player.largura
        && y >= player.p.y && y < player.p.y + player.altura){
            continue;
        }
        else break;
    }
    vida.x = x;
    vida.y = y;
}

void spawn_projetil(Entidade *e, int tipo){//tipo = 1, entidade é player

    int n = e->ataque_ativo;

    for(int i = 0; i < e->tiros_ps[n]; i++){

        int j = e->indices[n][i];
        if(j >= MAX_PROJETEIS) continue;
        
        int max = e->indices[n][i];
        if(tipo){
            e->projetil[n][i][max] = inicializar_projetil_player[nivel-1][n][i];
        }
        else{
            e->projetil[n][i][max] = inicializar_projetil_inimigo[nivel-1][n][i];
        }

        e->projetil[n][i][max].p.x += e->p.x + e->projetil[n][i][j].spawn.x;
        e->projetil[n][i][max].p.y += e->p.y + e->projetil[n][i][j].spawn.y;
        e->indices[n][i]++;
    }

}

//Apagar
void apagar_projetil(Projetil vetor[], int x, int *max){
    for(int i=x; i<(*max); i++){
        vetor[i] = vetor[i+1];
    }
    (*max)--;
}

void apagar_entidade(Entidade vetor[], int x, int *max){
    for(int i=x; i<(*max); i++){
        vetor[i] = vetor[i+1];
    }
    (*max)--;
}

//Jogo

int movimentacao_projeteis(Projetil *p){

    p->p.x += p->direcao.x;
    p->p.y += p->direcao.y;

    if(
        p->p.x <= 0 || p->p.x >= LARGURA || p->p.y <= 0 || p->p.y >= ALTURA
    ){
        return 1;
    }

    return 0;
}

int colisao(Coordenada projetil, Entidade entidade){
    if(
        projetil.x >= entidade.p.x && projetil.x < entidade.p.x + entidade.largura && 
        projetil.y >= entidade.p.y && projetil.y < entidade.p.y + entidade.altura
    ){
        return 1;
    }
    return 0;
}

void projeteis_acoes(Entidade *e, int tipo){

    for(int n = 0; n < e->q_ataques; n++){

        for(int i = 0; i < e->tiros_ps[n]; i++){
            
            for(int j = 0; j < e->indices[n][i]; j++){

                if(movimentacao_projeteis(&e->projetil[n][i][j])){
                    apagar_projetil(e->projetil[n][i], j, &e->indices[n][i]);
                    j--; continue;
                }

                if(tipo){
                    if(colisao(e->projetil[n][i][j].p, player)){

                        player.vida -= e->projetil[n][i][j].dano;

                        apagar_projetil(e->projetil[n][i], j, &e->indices[n][i]);

                    }
                }
                else{
                    for(int k = 0; k < max_inm; k++){
                        if(colisao(e->projetil[n][i][j].p, inimigo[k])){

                            inimigo[k].vida -= e->projetil[n][i][j].dano;

                            pontos++;

                            apagar_projetil(e->projetil[n][i], j, &e->indices[n][i]);

                            break;
                        }
                    }
                }

            }
        }
    }
}

//Config
void cd_jogo(){

    //Spawn de novos inimigos
    config.spawn_inimigo--;
    if(!config.spawn_inimigo){
        spawn_inimigo(&inimigo[max_inm]); 
        
        config.spawn_inimigo = configuracoes_de_fase[nivel-1].spawn_inimigo;
    }

    //Da Vida Extra
    if(config.ativar_VidaExtra && config.desativar_VidaExtra < 0){
        config.ativar_VidaExtra--;
    } 
    else if(config.desativar_VidaExtra && config.ativar_VidaExtra < 0){
        config.desativar_VidaExtra--;
    }
    else if(!config.desativar_VidaExtra){
        spawn_vida();
        config.desativar_VidaExtra = -1;
        config.ativar_VidaExtra = configuracoes_de_fase[nivel-1].ativar_VidaExtra;
    }
    else if(!config.ativar_VidaExtra){
        vida = (Coordenada){-1, -1};
        config.ativar_VidaExtra = -1;
        config.desativar_VidaExtra = configuracoes_de_fase[nivel-1].desativar_VidaExtra;
    }
}

void inicializar_constantes(){
    config = configuracoes_de_fase[nivel-1];
    config.ativar_VidaExtra = 0;
};

void pre_processamento(){
    imprimir_em_cima(9, 18, tela_mudanca_de_nivel[nivel], 2, 6, 5, 0.01);
    pausa(); system("clear");

    spawn_player();
    inicializar_constantes(); 
}

//
void info_para_debug(){
    printf("\n");
    printf("coord player: (%d, %d)     \n", player.p.x, player.p.y);

    
    
    
    
    //printf("inimigo[0].projetil[0][0][0] = (%d, %d)\n", inimigo[0].projetil[0][0][0].p.x, inimigo[0].projetil[0][0][0].p.y);
    //printf("inimigo[0].projetil[0][1][0] = (%d, %d)\n", inimigo[0].projetil[0][1][0].p.x, inimigo[0].projetil[0][1][0].p.y);

    /*
    printf("dano player: %d         \n", player.projetil[0][0][0].dano);
    printf("dano inm: %d               \n", inimigo[0].projetil[0][0][0].dano);

    printf("\n");
    printf("numero de inimigos: %d     \n", max_inm);
    printf("spawn_inimigo: %d      \n", config.spawn_inimigo);

    printf("\n");
    printf("inimigo[0] = (%d, %d)\n", inimigo[0].p.x, inimigo[0].p.y);
    printf("dano %d      \n", inimigo[0].projetil[0][0][0].dano);
    printf("direcoes = (%d, %d)\n", inimigo[0].projetil[0][0][0].direcao.x, inimigo[0].projetil[0][0][0].direcao.y);
    printf("Vida = %d               \n", inimigo[0].vida);
    */
    
    //printf("estado = %d\n", inimigo[0].estado);
    //printf("cd_atirar = %d\n", inimigo[0].cd_atirar);
    //printf("n_projeteis = %d\n", inimigo[0].indices[0][0]);

    //printf("ativar vida: %d     \n", config.ativar_VidaExtra);
    //printf("vida: (%d, %d)\n", vida.x, vida.y);
    //printf("desativar vida: %d     \n", config.desativar_VidaExtra);


}