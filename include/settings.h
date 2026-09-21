#ifndef SETTINGS

#define SETTINGS

#define LARGURA 21 
#define ALTURA 21
#define LINHA_LIMITE 12
#define MAX_INIMIGOS 20
#define MAX_PROJETEIS 10
#define MAX_ATAQUES 2 
#define MAX_TPS 3 //tiros por segundo
#define MAX_NIVEIS 3

#define SEGUNDOS 1000000
#define FPS 20 //1 frame dura 1/20 = 0.05 segundos

#define VOLTAR "\033[H"

#define VERMELHO "\033[031m"
#define VERDE  "\033[032m"
#define AMARELO "\033[033m"
#define AZUL "\033[34m"
#define BRANCO "\033[37m"
#define CINZA "\033[90m"
#define RESET  "\033[0m"

typedef struct{
    int x, y;
}Coordenada;

typedef struct{
    Coordenada p;
    Coordenada direcao; 
    Coordenada spawn;
    int dano;
    int cor;
    char c;
}Projetil;

typedef struct{
    Coordenada p;
    int vida;
    int largura;
    int altura;
    int estado; // 0. Normal; 1. Tomou Dano; 2. Morto
    
    Projetil projetil[MAX_ATAQUES][MAX_TPS][MAX_PROJETEIS];
    int indices[MAX_ATAQUES][MAX_TPS];
    int tiros_ps[MAX_ATAQUES];
    int q_ataques;
    int ataque_ativo;

    //Exclusivo dos inimigos
    int cd_ataque;
    int cd_andar;
    int cd_atirar;
}Entidade;

typedef struct{
    int spawn_inimigo;
    int ativar_VidaExtra;
    int desativar_VidaExtra;
    int vida_extra;
    int pontos_minimos;
    int pontos_por_abate;
}Config;

extern Entidade inimigo[MAX_INIMIGOS]; 
extern Entidade player; 
extern Entidade boss; 
extern Coordenada vida; 
extern Config config; 
extern int nivel;
extern int pontos;
extern int abates_totais;
extern int max_inm;
extern char cores[][10];

#endif