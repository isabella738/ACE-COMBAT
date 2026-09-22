#include "settings.h"
#include "definitions.h"
#include "general_funcions.h" 
#include <stdlib.h>

void random_spawn(Entidade *p){
    if(max_inm >= MAX_INIMIGOS - 1) return;

    int a = rand()%(MAX_NIVEIS - 1);
    (*p) = inicializar_inimigo[a];

    int max = p->spawn[0];
    int n = rand()%max + 1;
    p->p.x = p->spawn[n];

    max_inm++;
}

void spawn_inimigo(Entidade *p){
    if(max_inm >= MAX_INIMIGOS - 1) return;

    (*p) = inicializar_inimigo[nivel-1];

    int max = p->spawn[0];
    int n = rand()%max + 1;
    p->p.x = p->spawn[n];

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

        p->cd_ataque = inicializar_inimigo[p->nivel-1].cd_ataque;
    }
}

void movimentacao_inimigos(Entidade *p, int x){
    if(p->p.y < LINHA_LIMITE - p->altura && !p->cd_andar){
        int continuar=1;
        int dx = p->direcao.x, dy = p->direcao.y;

        //Verifica se nao esbarra em parede
        if(
            p->p.x + dx <= 0 || p->p.x + dx >= LARGURA ||
            p->p.y + dy >= ALTURA
        ){
            continuar = 0;
        }

        //verifica se não esbarra em ninguem
        for(int i=0; i<max_inm && continuar == 1; i++){
            if(x == i) continue;
            if(colisao_matrizes
                (
                    (Coordenada){p->p.x + dx, p->p.y + dy}, 
                    p->altura, 
                    p->largura, 
                    inimigo[i].p, 
                    inimigo[i].altura, 
                    inimigo[i].largura
                )
            ){
                continuar=0;
            }
        }

        if(continuar){
            p->p.y += dy;
            p->p.x += dx;
        }
        p->cd_andar = inicializar_inimigo[p->nivel-1].cd_andar;
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
        movimentacao_inimigos(&inimigo[i], i);

        if(saiu_do_mapa(inimigo[i])){
            apagar_entidade(inimigo, i, &max_inm);
            i--;
            continue;
        }
        
        if(!inimigo[i].cd_atirar){
            spawn_projetil(&inimigo[i], 0);
            inimigo[i].cd_atirar = inicializar_inimigo[inimigo[i].nivel-1].cd_atirar;
        }

        if(inimigo[i].vida <=0 && inimigo[i].estado < 2){
            inimigo[i].estado = 2;
        }
        
        projeteis_acoes(&inimigo[i], 1);

        if(inimigo[i].estado >= 5){//significa que o aviao vai ficar "explodido" por 3 frames
            abates_totais++;
            if(nivel == 3) return;

            apagar_entidade(inimigo, i, &max_inm);
            i--;
            continue;
        }

    }
}