#include "settings.h"

char cores[][10] = {
    RESET,
    BRANCO,
    VERMELHO,
    AMARELO,
    VERDE,
    AZUL,
    CINZA
};

Entidade inimigo[MAX_INIMIGOS]; //allmain
Entidade player; //allmain
Boss boss; //allmain
Coordenada vida; //allmain
Cooldowns cd; //allmain
Config config; //allmain
int nivel, vitoria, pontos = 0, abates_totais; //allmain
