#include "settings.h"
//Config
void cd_jogo();//

void inicializar_constantes();//

//Spawns
void spawn_vida();

void spawn_projetil(Entidade *p, int tipo);

//Apagar
void apagar_projetil(Projetil vetor[], int x, int *max);

void apagar_entidade(Entidade vetor[], int x, int *max);

//Jogo
void pre_processamento();//impressao na tela e inicializacao do player e de fase

int movimentacao_projeteis(Projetil *p);//

int colisao(Coordenada projetil, Entidade entidade);

void projeteis_acoes(Entidade *e, int tipo);//tipo 0: entidade é player; tipo 1: entidade é inimigo

//
void info_para_debug();