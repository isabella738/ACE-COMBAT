/*
    Define valores para variaveis externas às entidades durante a execução do jogo

    Obs: variaveis de cooldowns são o produto de um inteiro por uma macro FPS. Significa que este
    inteiro diz respeito aos segundos deste cooldown.
*/

#include "settings.h"

Config configuracoes_de_fase[] = {
    /*
        int spawn_inimigo;
        int ativar_VidaExtra;
        int desativar_VidaExtra;
        int vida_extra;
        int abates_minimos;
        int pontos_por_abate;

        Obs: para fases com inimigos unicos, tipo as de chefao, colocar 'spawn_inimigo' como -1
    */

    {//fase 1
        FPS*3,
        FPS*10,
        FPS*10,
        1,
        10,
        10
    },
    {//fase 2
        FPS*5,
        FPS*10,
        FPS*10,
        2,
        15,
        15,
    },
    {//fase 3 (Boss)
        -1,
        FPS*10,
        FPS*10,        
        3,
        1,
        300
    }
};
