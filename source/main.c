#include "settings.h"
#include "sprites.h"
#include "inicializacoes.h"
#include "auxiliares.h"
#include <unistd.h>
#include <stdlib.h>

#ifdef SETTINGS

extern Entidade inimigo[];
extern Entidade player;
extern Coordenada vida;
extern Cooldowns cd;
extern Config config;
extern int nivel;
extern int pontos;

void spawn_player(){
    player = inicializar_player[nivel-1];
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
}

void spawn_vida(){
    int x, y;
    while(1){
        x = rand()%(LARGURA-2) + 1;
        y = rand()%(ALTURA - LINHA_LIMITE) + LINHA_LIMITE;
        
        if(x >= player.p.x && x < player.p.x + player.largura
        && y >= player.p.y && y < player.p.y + player.altura){
            continue;
        }
        else break;
    }
}

void spawn_projetil(int tipo, Entidade *p){//tipo 1 = player; 0 = inimigo

    if(p->n_projeteis >= MAX_PROJETEIS-3) return;

    int meio = p->largura/2;
    int n = p->n_projeteis;
    int x;
    if(tipo) x = -1;
    else x = 1;


    if(p->projetil_duplo){
        p->projetil[n] = (Coordenada){meio-1, p->p.y + x};
        p->projetil[n+1] = (Coordenada){meio+1, p->p.y + x};
        p->n_projeteis += 2;
    }
    else{ 
        p->projetil[n] = (Coordenada){meio, p->p.y + x};
        p->n_projeteis++;
    }
}

void inicializar_constantes(){
    cd = inicializar_cooldowns[nivel-1];
    cd.andar_inimigo = inicializar_inimigo[nivel-1].cd_andar;
    cd.atirar_inimigo = inicializar_inimigo[nivel-1].cd_atirar;
};

//

int switch_estados(Entidade *p, int i, int max){
    if(p->estado == 1) p->estado = 0;
    else if(p->estado == 2){
        p->estado++;
        player.abates++;
        pontos += config.pontos_por_abate;
    }
    else if(p->estado > 2) p->estado++;
    else if(p->estado == 10){
        apagar_entidade(inimigo, i, max);
        return 1;
    }
    return 0;
}

void decrescer_cooldowns(int *max){
    if(player.estado == 1) player.estado = 0;

    cd.spawn_inimigo--;
    if(!cd.spawn_inimigo){
        cd.spawn_inimigo = inicializar_cooldowns[nivel-1].spawn_inimigo;

        spawn_inimigo(&inimigo[(*max)]);
        (*max)++;
    }

    if(cd.ativar_VidaExtra && cd.desativar_VidaExtra < 0) cd.ativar_VidaExtra--;
    else if(cd.desativar_VidaExtra && cd.ativar_VidaExtra < 0) cd.desativar_VidaExtra--;
    else if(!cd.desativar_VidaExtra){
        spawn_vida();
        cd.desativar_VidaExtra = -1;
        cd.ativar_VidaExtra = inicializar_cooldowns[nivel-1].ativar_VidaExtra;
    }
    else if(!cd.ativar_VidaExtra){
        vida = (Coordenada){-1, -1};
        cd.ativar_VidaExtra = -1;
        cd.desativar_VidaExtra = inicializar_cooldowns[nivel-1].desativar_VidaExtra;
    }

    for(int i=0; i < (*max); i++){
        inimigo[i].cd_andar--;
        inimigo[i].cd_atirar--;
        if(switch_estados(&inimigo[i], i, max)) i--;
    }
}

//

int colisao(Coordenada projetil, Entidade entidade){
    if(projetil.x >= entidade.p.x && projetil.x < entidade.p.x + entidade.largura
    && projetil.y >= entidade.p.y && projetil.y < entidade.p.y + entidade.altura){
        return 1;
    }
    return 0;
}

void pegar_vida(){
    if(colisao(vida, player)){
        player.vida += config.vida_extra;
        cd.ativar_VidaExtra = -1;
        cd.desativar_VidaExtra = inicializar_cooldowns[nivel-1].desativar_VidaExtra;
    }
}

void dano_ao_inimigo(Coordenada *projetil, int max, int i){//verifica se o projetil acertou algum inimigo
    for(int j=0; j<max; j++){
        if(colisao((*projetil), inimigo[j])){
            pontos++;

            apagar_projetil(player.projetil, i, &player.n_projeteis);
            
            inimigo[j].estado = 1;
            inimigo[j].vida -= player.dano;

            if(!inimigo[j].vida){
                inimigo[j].estado = 2;
                inimigo[j].ativo = 0;
            }

        }
    }

}

//

void movimentacao_player(int *atirar){
    int x = player.p.x;
    int y = player.p.y;

    char comando;
    if(read(STDIN_FILENO, &comando, 1) > 0){
        switch(comando){
            case 'a':
                if(x > 1) player.p.x--;
                break;
            case 'w':
                if(y > LINHA_LIMITE) player.p.y--;
                break;
            case 's':
                if(y < ALTURA - 2 - player.altura) player.p.y++;
                break;
            case 'd':
                if(x < LARGURA - 2 - player.largura) player.p.x++;
                break;
            case 'k':
                (*atirar) = 1;
                break;
        }
    }
}

void movimentacao_inimigos(Entidade *p, int max){
    if(p->ativo && p->p.y < LINHA_LIMITE){
        int continuar=1;
        for(int i=0; i<max; i++){
            if(inimigo[i].ativo 
            && p->p.y + p->altura + 1 == inimigo[i].p.y
            && p->p.x >= inimigo[i].p.x && p->p.x < inimigo[i].p.x + inimigo[i].largura){
                continuar = 0; break;
            }
        }
        if(continuar) p->p.y++;
    }
}

int movimentacao_projeteis(Entidade *p, int tipo, int max){//tipo 1 = player; 0 = inimigo
    int n=0;
    for(int i=0; i<p->n_projeteis; i++){
        if(tipo){//o projetil é do player
            p->projetil[i].y--;
            if(p->projetil[i].y < 1) apagar_projetil(p->projetil, i, p->n_projeteis);

            dano_ao_inimigo(&player.projetil[i], max, i);
        }
        else{//o projetil é do inimigo
            p->projetil[i].y++;
            if(p->projetil[i].y > ALTURA-1) apagar_projetil(p->projetil, i, p->n_projeteis);
            
            if(colisao(p->projetil[i], player)) n++;
        }
    }
    return n;
}

//

void imprimir_mapa(int max){
    for(int y=0; y < ALTURA; y++){
        for(int x=0; x < LARGURA; x++){

            int imp=0; //indica se aquela celula já foi impressa

            //Player
            imp = imprimir_entidade(x, y, player, sprite_player, nivel);
            if(!imp) imp = imprimir_projeteis(x, y, player);

            //Inimigos
            if(!imp) for(int i=0; i < max || imp == 0; i++){
                imp = imprimir_entidade(x, y, inimigo[i], sprite_inimigos, nivel);
            }
            if(!imp) for(int i=0; i < max || imp == 0; i++){
                imp = imprimir_projeteis(x, y, inimigo[i]);
            }

            if(!imp) if(vida.x == x && vida.y == y){
                printf(VERDE "@" RESET); imp = 1;
            }

            if(!imp) printf(CINZA "%c" RESET, mapa[y][x]);
        }
        printf("\n");
    }
}

int main_game(int nivel){
    imprimir_em_cima(tela_mudanca_de_nivel[nivel], 2, 6, 9, 18, 5);
    pausas();

    spawn_player(nivel);
    inicializar_constantes(nivel);

    int max_inm=0, vitoria=0;

    while(1){
        apagar_tela();
        printf("Nivel: %d\n\n", nivel);
        printf("Pontos: %d\n", pontos);

        int atirar=0, dano=0;
        
        decrescer_cooldowns(max_inm);

        movimentacao_player(&atirar);
        movimentacao_projeteis(&player, 1, max_inm);

        pegar_vida();

        for(int i=0; i<max_inm; i++){
            movimentacao_inimigos(&inimigo[i], max_inm);
            dano += movimentacao_projeteis(&inimigo[i], 0, max_inm);
        }

        if(atirar) spawn_projetil(1, &player);
        if(dano){
            player.vida -= dano*inicializar_inimigo[nivel-1].dano;
            player.estado = 1;
        }

        if(player.vida == 0) break;
        if(player.abates == config.pontos_minimos){
            vitoria=1; break;
        }
        imprimir_mapa(max_inm);
        imprimir_barra_de_vida(player.vida, inicializar_player[nivel].vida);
    }

    system("clear");
    usleep(2*SEGUNDOS);
    return vitoria;
}

int boss_fight(Boss boss){
    imprimir_em_cima(tela_mudanca_de_nivel[nivel], 2, 6, 9, 18, 5);
    apausas();

    spawn_player(nivel);
    inicializar_constantes(nivel);

    int vitoria=0;
    int ataque1 = 0, ataque2=100;

    /*
    while(1){
        apagar_tela();
        printf("Nivel: %d\n\n", nivel);
        printf("Pontos: %d\n", pontos);

        int atirar=0, dano=0;

        movimentacao_player(&atirar);
        if(atirar) spawn_projetil(1, &player);

        for(int i=0; i<player.n_projeteis; i++){
            if(player.projetil[i].y < 5){
                boss.vida -= player.dano;
            }
        }
    }
    */
}

/*
0. Inicialização de variaveis
1. Cooldowns; mudança de estados 1->0; morte de inimigos; aparecimento de vida
2. Movimentar player
3. Movimentar projeteis do player; dar dano ao inimigo; alterar estado para 2
4. Pegar vida
5. Movimentar inimigos
6. Movimentar projeteis do inimigo; 
7. Gerar projeteis do player
8. Tirar dano do player
9. Imprimir
*/

#endif