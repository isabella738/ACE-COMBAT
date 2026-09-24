/*
    Define as informacoes da variavel 'player', por nivel. Cada nivel possui um player proprio.
    Todas as chaves mais externas dizem respeito a configuração de 1 nivel.

    Contem as seguintes estruturas:

    - inicializar_player: informacoes da entidade em si, conforme a struct Entidade (ver settings)

    - inicializar projeteis: informacoes dos projeteis de um modelo especifico, conforme a struct
    Projeteis (ver settings)

    Criar um novo modelo consiste em seguir este padrao, abrindo novas chaves no local do nivel
    correspondente. Espaços não utilizados, como usar menos ataques doq o maximo permitido por exemplo,
    devem ser preenchidos com {0}.
    (Lembrar de acrescentar a sprite nova tambem)
*/

#include "settings.h"

Entidade inicializar_player[] = {
    {//nivel 1
        1,
        {8, 17}, 
        {0},
        0,
        20,  
        5,  
        3,
        0,

        {0},
        {0},
        {1, 0},
        1,
        0,

        0,
        0,
        0
    },
    {//nivel 2
        2,
        {8, 17}, 
        {0},
        0,
        30,
        5,
        3,
        0,

        {0},
        {0},
        {1, 0},
        1,
        0,

        0,
        0,
        0
    },
    {//nivel 3
        3,
        {8, 17},
        {0},
        0,
        50,
        5,
        3,
        0,

        {0},
        {0},
        {2, 0},
        1,
        0,

        0,
        0,
        0,
    },
};

Projetil inicializar_projetil_player[][MAX_ATAQUES][MAX_TPS] = {
    {//nivel 1
        {
            {
                {0},
                {0, -1},
                {2, -1},
                1,
                3,
                '*',
            },
            {0},
            {0},
        },
        {0},
    },
    {//nivel 2
        {
            {
                {0},
                {0, -1},
                {2, -1},
                2,
                3,
                '+',
            },
            {0},
            {0},
        },
        {0},
    },
    {//nivel 3
        {
            {
                {0},
                {0, -1},
                {1, -1},
                2,
                3,
                '+',
            },
            {
                {0},
                {0, -1},
                {3, -1},
                2,
                3,
                '+',
            },
            {0},
        },
        {0}
    }
};
