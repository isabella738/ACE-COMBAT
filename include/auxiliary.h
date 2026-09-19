#include "settings.h"

int imprimir_entidade(int x, int y, Entidade entidade, char sprite[][2][3][8], int nivel);

int imprimir_projeteis(int x, int y, Entidade entidade, int cor);

void imprimir_em_cima(int altura, int largura, char imagem[altura][largura], int dx, int dy, int cor, float tempo);

void imprimir_barra_de_vida(int x, int max);

void imprimir_mapa();

//

void pausa();

void informacoes_finais(int pontos, int abates_totais, int nivel);

//

void mudar_terminal();
void restaurar_terminal();

