#include "settings.h"

void spawn_player(); //define as configuracoes iniciais do player no inicio de cada fase

void pegar_vida(); //verifica colisao player-vida

void movimentacao_player(int *atirar);

void dano_ao_inimigo(Coordenada *projetil, int max, int i); //verifica se o projetil acertou algum inimigo

void colisao_player_inimigo();