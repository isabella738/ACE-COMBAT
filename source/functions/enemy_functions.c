#include "settings.h"
#include "definitions.h"
#include "general_funcions.h" 
#include <stdlib.h>

void spawn_inimigo(Entidade *p){
    if(max_inm >= MAX_INIMIGOS - 1) return;

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

void cd_inimigos(Entidade *p){
    p->cd_andar--;
    p->cd_atirar--;
    if(p->q_ataques > 1) p->cd_ataque--;
}

void alternar_ataque(Entidade *p){
    if(p->q_ataques > 1 && !p->cd_ataque){
        int n = rand()%(p->q_ataques);
        p->ataque_ativo = n;

        p->cd_ataque = inicializar_inimigo[nivel-1].cd_ataque;
    }
}

void movimentacao_inimigos(Entidade *p){
    if(p->p.y < LINHA_LIMITE - p->altura && !p->cd_andar){
        int continuar=1;

        for(int i=0; i<max_inm; i++){
            if(
                p->p.y + p->altura + 1 == inimigo[i].p.y && 
                p->p.x >= inimigo[i].p.x && 
                p->p.x < inimigo[i].p.x + inimigo[i].largura
            ){
                continuar = 0; break;
            }
        }
        if(continuar) p->p.y++;
        p->cd_andar = inicializar_inimigo[nivel-1].cd_andar;
    }
}

int switch_estados(Entidade *p){
    switch(p->estado){
        case 0: break;
        case 1:
            p->estado = 0;
            break;
        case 2:
            p->estado++;
            pontos += config.pontos_por_abate;
            abates_totais ++;
            break;
        default:
            p->estado++;
            break;
    }
    return 0;
}

void inimigos_acoes(){
    for(int i=0; i<max_inm; i++){
        
        cd_inimigos(&inimigo[i]);

        alternar_ataque(&inimigo[i]);
        movimentacao_inimigos(&inimigo[i]);
        
        if(!inimigo[i].cd_atirar){
            spawn_projetil(&inimigo[i], 0);
            inimigo[i].cd_atirar = inicializar_inimigo[nivel-1].cd_atirar;
        }

        if(!inimigo[i].vida){
            inimigo[i].estado = 2;
        }
        
        projeteis_acoes(&inimigo[i], 1);

        switch_estados(&inimigo[i]);

        if(inimigo[i].estado >= 7){//significa que o aviao vai ficar "explodido" por 5 frames
            apagar_entidade(inimigo, i, &max_inm);
            i--;
        }

    }
}