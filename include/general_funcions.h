#include "settings.h"
//Config
void cd_jogo();//

void inicializar_constantes();//

//Spawns
void spawn_vida();

void spawn_projetil(int direcao, Entidade *p);

//Apagar
void apagar_projetil(Coordenada vetor[], int x, int *max);

void apagar_entidade(Entidade vetor[], int x, int *max);

//Jogo
void movimentacao_projeteis(Entidade *p, int direcao);//

int colisao(Coordenada projetil, Entidade entidade);
