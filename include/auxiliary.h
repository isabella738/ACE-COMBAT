#include "settings.h"

void limpar_buffer();

void pausa();

void informacoes_finais();

void mensagem_de_mudanca_de_nivel();

//

int imprimir_entidade(int x, int y, Entidade entidade, char sprite[][2][ALTURA][LARGURA]);

int imprimir_projeteis(int x, int y, Entidade entidade);

void imprimir_em_cima(int altura, int largura, char imagem[altura][largura], int dx, int dy, int cor, float tempo);

void imprimir_barra_de_vida();

void imprimir_mapa();

//


void mudar_terminal();
void restaurar_terminal();

