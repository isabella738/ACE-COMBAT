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

Entidade inimigo[MAX_INIMIGOS]; //def
Entidade player; //def
Boss boss; //def
Coordenada vida; //def
Config config; //def
int nivel=1, vitoria=0, pontos = 0, abates_totais=0, max_inm=0; //def
