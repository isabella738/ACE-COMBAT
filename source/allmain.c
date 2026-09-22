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

    imprimir_em_cima(9, 20, level_up[0], 1, 6, 1, 0);
    pausa(); system("clear");
    
    while(1){
        system("clear");
        config = configuracoes_de_fase[nivel-1];
        

        if(nivel==1){
            printf("Dica: Use awsd para se movimentar e k para atirar.\n"); pausa(); system("clear");
        }
        
        pre_processamento();
        if(nivel == 3) vitoria = boss_fight();
        else vitoria = main_game();

        system("clear");
        if(vitoria){
            imprimir_em_cima(9, 20, level_up[nivel], 1, 6, 5, 0.1);
            if(nivel == 3) break;

            printf("- Novo Aviao!\n- + Vida!\n- + Dano!\n\n"); 
            getchar();
            pausa();
            nivel++;
        }
        else{
            gameover();
            break;
        }
    }
    informacoes_finais(pontos, abates_totais, nivel);
    printf("\nBom Jogo!\n");

    restaurar_terminal();
    return 0;
}