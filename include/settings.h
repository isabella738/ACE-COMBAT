//#include <termios.h>

#ifndef SETTINGS

#define SETTINGS

#define LARGURA 21
#define ALTURA 21
#define LINHA_LIMITE 12
#define MAX_INIMIGOS 20
#define MAX_PROJETEIS 50

#define SEGUNDOS 1000000

#define APAGAR "\033[H"

#define VERMELHO "\033[031m"
#define VERDE  "\033[032m"
#define AMARELO "\033[033m"
#define AZUL "\033[34m"
#define BRANCO "\033[37m"
#define CINZA "\033[90m"
#define RESET  "\033[0m"

char cores[][10] = {
    RESET,
    BRANCO,
    VERMELHO,
    AMARELO,
    VERDE,
    AZUL,
    CINZA
};

typedef struct{
    int x, y;
}Coordenada;

typedef struct{
    /*
        Informacoes da entidade
    */
    Coordenada p;
    int vida;
    int largura;
    int altura;
    int estado; // 0. Normal; 1. Tomou Dano; 2. Morto
    int ativo;
    int abates;
    
    /*
        Informacoes dos projeteis
    */
    int dano; //Dano causado por 1 projetil
    int projetil_duplo; //Indica se o modelo do aviao permite lancar dois projeteis de vez
    int n_projeteis;
    Coordenada projetil[MAX_PROJETEIS];

    /*
        Cooldowns (somente para inimigos)
    */
    int cd_andar;
    int cd_atirar;
}Entidade;

typedef struct{
    Coordenada p;
    int vida;
    int estado;
    int dano;
    int ataque;

    Coordenada projetil1[MAX_PROJETEIS];
    Coordenada projetil2[MAX_PROJETEIS];
}Boss;

typedef struct{
    int spawn_inimigo;
    int ativar_VidaExtra;
    int desativar_VidaExtra;
    int andar_inimigo; //interno
    int atirar_inimigo; //interno
}Cooldowns;

typedef struct{
    int vida_extra;
    int pontos_minimos;
    int pontos_por_abate;
}Config;

Entidade inimigo[MAX_INIMIGOS]; //settings
Entidade player; //settings
Entidade boss; //settings
Coordenada vida; //settings
Cooldowns cd; //settings
Config config; //settings

#endif