/*
    Definições das informações dos inimigos, por nível. Cada nivel possui um inimigo proprio.
    Contem 3 estruturas que permitem personalizar inimigos novos e ja existentes. Todas as chaves
    mais externas dizem respeito a configuração de 1 nivel

        - spawn: o 1o elemento diz respeito ao tamanho do vetor -1. Contem as coordenadas x possiveis
        para o inimigo spawnar

        - inicializar_inimigo: informações da entidade conforme a struct Entidade (ver settings)

        - inicializar_projetil: informações dos projeteis deste inimigo, conforme a sturct Projeteis
        (ver settings).
        Cada inimigo tem n ataques, que contem m projeteis por vez, que contem suas proprias informacoes.

    Criar um novo inimigo consiste em seguir este padrao, abrindo novas chaves no local do nivel
    correspondente. Espaços não utilizados, como usar menos ataques doq o maximo permitido por exemplo,
    devem ser preenchidos com {0}.
    (Lembrar de acrescentar a sprite nova e aumentar o MAX_NIVEIS em 1 tambem)

    Obs: variaveis de cooldowns são o produto de um inteiro por uma macro FPS. Significa que este
    inteiro diz respeito aos segundos deste cooldown.
*/

#include "settings.h"

int spawn[][10] = { //o 1o elemento é o tamanho do array - 1
    {3, 2, 8, 14},
    {2, 3, 11},
    {1, 1},
};
 
Entidade inicializar_inimigo[] = {
    {//nivel 1
        1,
        {0, -3},
        {0, 1},
        spawn[0],
        10,
        5,
        3,
        0,

        {0},
        {0},
        {1, 0},
        1,
        0,

        0*FPS,
        1*FPS,
        1*FPS
    },
    {//nivel 2
        2,
        {0, -3},
        {0, 1},
        spawn[1],
        20,
        7,
        3,
        0,

        {0},
        {0},
        {2, 0},
        1,
        0,

        0*FPS,
        1*FPS,
        1*FPS
    },
    {//nivel 3 BOSS
        3,
        {1, -6},
        {0, 1},
        spawn[2],
        150,
        19,
        6,
        1,

        {0},
        {0},
        {3, 3},
        2,
        0,

        10*FPS,
        0*FPS,
        1*FPS
    }
};

Projetil inicializar_projetil_inimigo[][MAX_ATAQUES][MAX_TPS]= {
    {//nivel 1
        {//ataque 1
            {//p1
                {0},
                {0, 1},
                {2, 1},
                1,
                2,
                '+',
            },
            {0},
            {0}, 
        },
        {0},
    },
    {//nivel 2
        {//ataque 1
            {//p1
                {0},
                {0, 1},
                {2, 1},
                1,
                2,
                '+',
            },
            {//p2
                {0},
                {0, 1},
                {4, 1},
                1,
                2,
                '+',
            },
            {0},
        },
        {0},
    },
    {//nivel 3
        {//ataque 1
            {//p1
                {0},
                {0, 1},
                {2, 4},
                2,
                2,
                '|'
            },
            {//p2
                {0},
                {0, 1},
                {9, 6},
                2,
                2,
                '|'
            },
            {//p3
                {0},
                {0, 1},
                {16, 4},
                2,
                2,
                '|'
            }
        },
        {//ataque 2
            {//p1
                {0},
                {1, 1},
                {2, 4},
                3,
                2,
                '&'
            },
            {//p2
                {0},
                {-1, 1},
                {16, 4},
                3,
                2,
                '@'
            },
            {//p3
                {0},
                {0, 1},
                {9, 6},
                2,
                2,
                '|'
            },
        }
    }
};
