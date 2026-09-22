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
    
    while(1){
        system("clear");
        config = configuracoes_de_fase[nivel-1];

        if(nivel==1){
            printf("Dica: Use awsd para se movimentar e k para atirar.\n"); pausa(); system("clear");
        }
        
        pre_processamento();
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

    if(!vitoria)
        printf("Os ceus nao foram salvos, mas este ainda nao e o fim da historia.\nBom Jogo!\n");

    restaurar_terminal();
    return 0;
}