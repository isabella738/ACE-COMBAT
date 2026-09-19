#include "settings.h"
/*
    O valores de cooldown sao o tempo em segundos.

    Struct Entidade

    Coordenada p;
    int vida;
    int vida_max;
    int largura;
    int altura;
    int estado; 
    int ativo;
    int abates;
    int dano; 
    int projetil_duplo;
    int n_projeteis;
    Coordenada projetil[MAX_PROJETEIS];
    int cd_andar;
    int cd_atirar;
*/

Entidade inicializar_player[] = {
    {//nivel 1
        {8, 17},
        20, 
        5,  
        3,  
        0,  
        1,
        0,
        1,  
        0,  
        0,
        {0},
        0,
        0
    },
    {//nivel 2
        {8, 17},
        30,
        5,
        3,
        0,
        1,
        0,
        2,
        0,
        0,
        {0},
        0,
        0
    },
    {//nivel 3
        {8, 17},
        50,
        5,
        3,
        0,
        1,
        0,
        2,
        1,
        0,
        {0},
        0,
        0
    }
};

Entidade inicializar_inimigo[] = {
    {//nivel 1
        {0, -5},
        10,
        5,
        3,
        0,
        1,
        0,
        2,
        0,
        0,
        {0},
        1*FPS,
        1*FPS,
    },
    {//nivel 2
        {0, -5},
        20,
        7,
        3,
        0,
        1,
        0,
        2,
        1,
        0,
        {0},
        1*FPS,
        1*FPS
    },
};

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
        FPS*10,
        FPS*10,
        FPS*10,
        1,
        100,
        10
    },
    {//fase 2
        FPS*5,
        FPS*10,
        FPS*10,
        2,
        300,
        15,
    },
    {//fase 3 (Boss)
        FPS*10,
        FPS*10,
        FPS*10,        
        3,
        0,
        150
    }
};

