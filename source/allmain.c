#include "settings.h"
#include "auxiliares.h"
#include "main.h"
#include "inicializacoes.h"
#include "cutscenes.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

extern struct termios novo_terminal;
extern struct termios velho_terminal;

int main(){
    srand(time(NULL));
    mudar_terminal();
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    extern Entidade player;
    extern Entidade inimigo[];
    extern Coordenada vida;
    extern Cooldowns cd;
    extern Config config;
    extern Boss boss;
    int nivel, vitoria, pontos = 0, abates_totais;

    while(1){
        system("clear");
        config = configuracoes_de_fase[nivel-1];

        imprimir_em_cima(level_up[0], 1, 6, 9, 20, 1);
        pausa(); apagar_tela();

        if(nivel==0){
            printf("Dica: Use awsd para se movimentar e k para atirar.\n"); pausa(); apagar_tela();
        }

        if(nivel == 3) vitoria = boss_fight(boss);
        else vitoria = main_game(nivel);

        abates_totais += player.abates;

        if(vitoria){
            imprimir_em_cima(level_up[nivel], 1, 6, 9, 20, 5);
            if(nivel == 3) break;

            printf("- Novo Aviao!\n- + Vida!\n- + Dano!\n\n"); pausa();
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