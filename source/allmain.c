/*
    É no AllMain onde algumas das configurações externas ao jogo, como mudança de fase e controle
    de vitoria, são gerenciadas.
    Contem a função main do projeto.
*/

#include "settings.h"
#include "auxiliary.h"
#include "main.h"
#include "definitions.h"
#include "cutscenes.h"
#include "general_funcions.h"
#include "sprites.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

extern struct termios novo_terminal;
extern struct termios velho_terminal;

int main(){
    system("clear");
    srand(time(NULL));
    mudar_terminal();
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    int vitoria=0;

    subida_de_nivel(); nivel++;
    system("clear");
    printf("Dica: Use awsd para se movimentar e k para atirar.\n"); 
    pausa(); system("clear");

    printf("Iniciar modo de fases(1) ou modo infinito(2)?\n");
    while(1){
        char c;
        if(read(STDIN_FILENO, &c, 1) > 0){
            if(c == '1'){ modo_infinito = 0; break;}
            else if(c == '2'){ modo_infinito = 1; break;}
        }
    }
    system("clear");

    if(modo_infinito){
        arcade();
        return 0;
    }
    else while(1){
        imprimir_em_cima(9, 18, tela_mudanca_de_nivel[nivel], 2, 6, 4, 0.01);
        pausa(); system("clear");

        vitoria = main_game();

        system("clear");
        limpar_buffer();
        if(vitoria){
            subida_de_nivel();
            if(nivel == MAX_NIVEIS) break;
            nivel++;
        }
        else{
            gameover();
            break;
        }
    }

    if(!vitoria){
        informacoes_finais();
        printf("Os ceus nao foram salvos, mas este ainda nao e o fim da historia.\nBom Jogo!\n");
    }
    restaurar_terminal();
    return 0;
}