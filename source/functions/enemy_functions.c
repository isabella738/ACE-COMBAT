#include "settings.h"
#include "inicializacoes.h"
#include "general_funcions.h"
#include <stdlib.h>

int switch_estados(Entidade *p, int i){
    switch(p->estado){
        case 1:
            p->estado = 0;
            break;
        case 2:
            p->estado++;
            player.abates++;
            pontos += config.pontos_por_abate;
            break;
        case 3:
            p->estado++;
            break;
        case 4:
            apagar_entidade(inimigo, i, &max_inm);
            return 1;
    }
    return 0;
}

void cd_inimigos(){
    for(int i=0; i < max_inm; i++){
        inimigo[i].cd_andar--;
        inimigo[i].cd_atirar--;
        if(switch_estados(&inimigo[i], i)) i--;
    }
}

void spawn_inimigo(Entidade *p){
    (*p) = inicializar_inimigo[nivel-1];

    int a;
    p->largura <= 5 ? (a = 3) : (a=2);
    int n = rand()%a;

    if(a == 2){
        switch(n){
            case 0: p->p.x = 3; break;
            case 1: p->p.x = 11; break;
        }
    }
    if(a == 3){
        switch(n){
            case 0: p->p.x = 2; break;
            case 1: p->p.x = 8; break;
            case 2: p->p.x = 14; break;
        }
    }

    max_inm++;
}

void movimentacao_inimigos(Entidade *p){
    if(p->ativo && p->p.y < LINHA_LIMITE && !p->cd_andar){
        int continuar=1;

        for(int i=0; i<max_inm; i++){
            if(inimigo[i].ativo 
            && p->p.y + p->altura + 1 == inimigo[i].p.y
            && p->p.x >= inimigo[i].p.x && p->p.x < inimigo[i].p.x + inimigo[i].largura){
                continuar = 0; break;
            }
        }
        if(continuar) p->p.y++;
        p->cd_andar = inicializar_inimigo[nivel-1].cd_andar;
    }
}

void colisao_inimigo_player(){
    for(int i=0; i<max_inm; i++){
        for(int j=0; j<inimigo[i].n_projeteis; j++){

            if (colisao(inimigo[i].projetil[j], player)){
                
                apagar_projetil(inimigo[i].projetil, j, &inimigo[i].n_projeteis);

                player.vida -= inimigo[i].dano;
            }
        }
    }
}