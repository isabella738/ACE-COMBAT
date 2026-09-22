#include "settings.h"
#include "definitions.h"
#include "general_funcions.h"
#include <unistd.h>
#include <string.h> 

void spawn_player(){
    player = inicializar_player[nivel-1];
}

void pegar_vida(){
    if(colisao(vida, player)){
        if(player.vida < inicializar_player[nivel-1].vida) player.vida += config.vida_extra;
        config.ativar_VidaExtra = 0;
    }
}

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
                if(y < ALTURA - player.altura -1) player.p.y++;
                break;
            case 'd':
                if(x < LARGURA - 1 - player.largura) player.p.x++;
                break;
            case 'k':
                (*atirar) = 1;
                break;
        }
    }
}

void player_acoes(){
    int atirar=0;
    
    movimentacao_player(&atirar);

    if(atirar) spawn_projetil(&player, 1);
    projeteis_acoes(&player, 0);

    pegar_vida();
}