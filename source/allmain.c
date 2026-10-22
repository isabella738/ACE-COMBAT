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
#include "general_functions.h" 
#include "sprites.h"
#include "terminal.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#if defined(LINUX)
    #include <fcntl.h>
    #include <unistd.h>
#endif

int main(){
    limpar_tela();
    srand(time(NULL));
    #if defined(LINUX)
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
        mudar_terminal();
        system("clear");
    #else
        system("cls");
    #endif

    int vitoria=0;

    subida_de_nivel(); nivel++;
    limpar_tela();
    printf("Dica: Use awsd para se movimentar e k para atirar.\n"); 
    pausa(); 
    limpar_tela();

    printf("Iniciar modo de fases(1) ou modo infinito(2)?\n");
    while(1){
        char c;
        if(ler_teclado(&c)){
            if(c == '1'){ modo_infinito = 0; break;}
            else if(c == '2'){ modo_infinito = 1; break;}
        }
    }
    limpar_tela();

    if(modo_infinito){
        arcade();
        return 0;
    }
    else while(1){
        imprimir_em_cima(9, 18, tela_mudanca_de_nivel[nivel], 2, 6, 4, 0.01);
        limpar_buffer();
        pausa();
        limpar_tela();

        vitoria = main_game();

        limpar_tela();
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
    return 0;
}