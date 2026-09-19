#include "settings.h"
#include "inicializacoes.h"
#include "general_funcions.h"
#include <unistd.h>

void spawn_player(){
    player = inicializar_player[nivel-1];
}

void pegar_vida(){
    if(colisao(vida, player)){
        player.vida += config.vida_extra;
        config.ativar_VidaExtra = -1;
        config.desativar_VidaExtra = configuracoes_de_fase[nivel-1].desativar_VidaExtra;
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

void colisao_player_inimigo(){
    for(int i=0; i<player.n_projeteis; i++){
        for(int j=0; j<max_inm; j++){

            if(colisao(player.projetil[i], inimigo[j])){
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
}
