#include "settings.h"

Config configuracoes_de_fase[] = {
    /*
        int spawn_inimigo;
        int ativar_VidaExtra;
        int desativar_VidaExtra;
        int vida_extra;
        int pontos_minimos;
        int pontos_por_abate;
    */

    {//fase 1
        FPS*3,
        FPS*10,
        FPS*10,
        1,
        //100,
        10,
        10
    },
    {//fase 2
        FPS*5,
        FPS*10,
        FPS*10,
        2,
        //300,
        20,
        15,
    },
    {//fase 3 (Boss)
        0,
        FPS*10,
        FPS*10,        
        3,
        0,
        150
    }
};
