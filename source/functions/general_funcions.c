#include "settings.h"
#include "inicializations.h"
#include "enemy_functions.h"
#include "player_functions.h"
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

void spawn_projetil(int y, Entidade *p){

    if(p->n_projeteis >= MAX_PROJETEIS-3) return;

    int meio = p->largura/2;
    int n = p->n_projeteis;

    if(p->projetil_duplo){
        p->projetil[n] = (Coordenada){meio + p->p.x -1, y};
        p->projetil[n+1] = (Coordenada){meio + p->p.x +1, y};
        p->n_projeteis += 2;
    }
    else{ 
        p->projetil[n] = (Coordenada){meio + p->p.x, y};
        p->n_projeteis++;
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

//Apagar
void apagar_projetil(Coordenada vetor[], int x, int *max){
    for(int i=x; i<(*max); i++){
        vetor[i] = vetor[i+1];
    }
    (*max)--;
}

void apagar_entidade(Entidade vetor[], int x, int (*max)){
    for(int i=x; i<(*max); i++){
        vetor[i] = vetor[i+1];
    }
    (*max)--;
}

//Jogo
void movimentacao_projeteis(Entidade *p, int direcao){
    for(int i=0; i<p->n_projeteis; i++){

        p->projetil[i].y += direcao;
        
        if(p->projetil[i].y <= 0 || p->projetil[i].y >= ALTURA){
            apagar_projetil(p->projetil, i, &p->n_projeteis);
        }
    }
}

int colisao(Coordenada projetil, Entidade entidade){
    if(projetil.x >= entidade.p.x && projetil.x < entidade.p.x + entidade.largura
    && projetil.y >= entidade.p.y && projetil.y < entidade.p.y + entidade.altura){
        return 1;
    }
    return 0;
}

void info_para_debug(){
    printf("\n");
    printf("numero de inimigos: %d     \n", max_inm);
    printf("spawn_inimigo: %d      \n", config.spawn_inimigo);

    //printf("\n");
    //printf("inimigo[0] = (%d, %d)\n", inimigo[0].p.x, inimigo[0].p.y);
    //printf("cd_atirar inm[0] = %d\n", inimigo[0].cd_atirar);
    //printf("n_projeteis = %d\n", inimigo[0].n_projeteis);
    //printf("prj = (%d, %d)\n", inimigo[0].projetil[0].x, inimigo[0].projetil[0].y);

    //printf("ativar vida: %d     \n", config.ativar_VidaExtra);
    //printf("vida: (%d, %d)\n", vida.x, vida.y);
    //printf("desativar vida: %d     \n", config.desativar_VidaExtra);


}