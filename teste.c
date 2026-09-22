#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define VOLTAR "\033[H"
#define SEGUNDOS 1000000
#define LARGURA 21 
#define ALTURA 21
#define VERMELHO "\033[031m"
#define VERDE  "\033[032m"
#define AMARELO "\033[033m"
#define AZUL "\033[34m"
#define BRANCO "\033[37m"
#define CINZA "\033[90m"
#define RESET  "\033[0m"

char mapa[21][21+1]={
    "_____________________",//0
    "|                   |",
    "|                   |",
    "|                   |",
    "|                   |",
    "|                   |",//5
    "|                   |",
    "|                   |",
    "|                   |",
    "|                   |",
    "|                   |",//10
    "|                   |",
    "|                   |",//12 - limite de area entre player e inimigos
    "|                   |",
    "|                   |",
    "|                   |",//15
    "|                   |",
    "|                   |",
    "|                   |",
    "|                   |",
    "#####################",//20
//   0    1    2    3    4
};

char cores[][10] = {
    RESET,
    BRANCO,
    VERMELHO,
    AMARELO,
    VERDE,
    AZUL,
    CINZA
};

void imprimir_em_cima(int altura, int largura, char imagem[altura][largura], int dx, int dy, int cor, float tempo){

    for(int y=0; y<ALTURA; y++){
        printf(CINZA"%s\n"RESET, mapa[y]);
    }
    printf(VOLTAR);

    for(int y=0; y<ALTURA; y++){
        for(int x=0; x<LARGURA; x++){
            
            if(x >= dx && x < dx + largura && y >= dy && y < dy + altura){
                printf("%s%c"RESET, cores[cor], imagem[y-dy][x-dx]);
                if(tempo)fflush(stdout);
                usleep(SEGUNDOS*tempo);
            }
            else printf(CINZA"%c"RESET, mapa[y][x]);

        }
        printf("\n");
    }
}

char level_up[][4][9][20] = {//escrever em (1x, 6y)
    {//tela inicial
        {
            "     + SUPER +     ",
            "   + AIR ACTION +  ",
            "     + 3000! +     ",
            "         A         ",
            "  ____^-/|\\-^____  ",
            "  '+__|_:*:_|__+'  ",
            "       __|__       ",
            "       'v=v'       ",
            "     * * * * *     ",
        },
        {
            "   +   SUPER    +  ",
            "   + AIR ACTION +  ",
            "   +   3000!    +  ",
            "         A         ",
            "  ____^-/|\\-^____  ",
            "  '+__|_:*:_|__+'  ",
            "       __|__       ",
            "       'v=v'       ",
            "     * * * * *     ",
        },
        {
            " +     SUPER      +",
            "   + AIR ACTION +  ",
            " +     3000!      +",
            "         A         ",
            "  ____^-/|\\-^____  ",
            "  '+__|_:*:_|__+'  ",
            "       __|__       ",
            "       'v=v'       ",
            "     * * * * *     ",
        },
        {
            "   +   SUPER    +  ",
            "   + AIR ACTION +  ",
            "   +   3000!    +  ",
            "         A         ",
            "  ____^-/|\\-^____  ",
            "  '+__|_:*:_|__+'  ",
            "       __|__       ",
            "       'v=v'       ",
            "     * * * * *     ",
        },
    },
    {//level up do 1 para o 2
        {
            "                   ",
            "   + + +   + + +   ",
            "     LEVEL UP!     ",
            "   +           +   ",
            "   +   _.A._   +   ",
            "   +   '-+-'   +   ",
            "        =!=        ",
            "   + + +   + + +   ",
            "                   ",
        },
        {
            "                   ",
            "     + + +   + +   ",
            "   + LEVEL UP! +   ",
            "   +               ",
            "   +   _.A._   +   ",
            "       '-+-'   +   ",
            "   +    =!=    +   ",
            "   + +   + + +     ",
            "                   ",
        },
        {
            "                   ",
            "   +   + + +   +   ",
            "   + LEVEL UP! +   ",
            "   +           +   ",
            "       _.A._       ",
            "   +   '-+-'   +   ",
            "   +    =!=    +   ",
            "   +   + + +   +   ",
            "                   ",
        },
        {
            "                   ",
            "   + +   + + +     ",
            "   + LEVEL UP! +   ",
            "               +   ",
            "   +   _.A._   +   ",
            "   +   '-+-'       ",
            "   +    =!=    +   ",
            "     + + +   + +   ",
            "                   ",
        },
    },
    {//level up do 2 para o 3
        {
            "                   ",
            "   + + +   + + +   ",
            "     LEVEL UP!     ",
            "   +           +   ",
            "   +   _A.A_   +   ",
            "   +   \\{+}/   +   ",
            "        :I:        ",
            "   + + +   + + +   ",
            "                   ",
        },
        {
            "                   ",
            "     + + +   + +   ",
            "   + LEVEL UP! +   ",
            "   +               ",
            "   +   _A.A_   +   ",
            "       \\{+}/   +   ",
            "   +    :I:    +   ",
            "   + +   + + +     ",
            "                   ",
        },
        {
            "                   ",
            "   +   + + +   +   ",
            "   + LEVEL UP! +   ",
            "   +           +   ",
            "       _A.A_       ",
            "   +   \\{+}/   +   ",
            "   +    :I:    +   ",
            "   +   + + +   +   ",
            "                   ",
        },
        {
            "                   ",
            "   + +   + + +     ",
            "   + LEVEL UP! +   ",
            "               +   ",
            "   +   _A.A_   +   ",
            "   +   \\{+}/      ",
            "   +    :I:    +   ",
            "     + + +   + +   ",
            "                   ",
        },
    },
    {//Fim de jogo (vitoria)
        {
            "                   ",
            "   + + +   + + +   ",
            "      VITORIA      ",
            "   +           +   ",
            "   +    _A_    +   ",
            "   +   /_!_\\   +   ",
            "         ^         ",
            "   + + +   + + +   ",
            "                   ",
        },
        {
            "                   ",
            "     + + +   + +   ",
            "   +  VITORIA  +   ",
            "   +               ",
            "   +   _.A._   +   ",
            "       '-+-'   +   ",
            "   +    =!=    +   ",
            "   + +   + + +     ",
            "                   ",
        },
        {
            "                   ",
            "   +   + + +   +   ",
            "   +  VITORIA  +   ",
            "   +           +   ",
            "       _A.A_       ",
            "   +   \\{+}/   +   ",
            "   +    :I:    +   ",
            "   +   + + +   +   ",
            "                   ",
        },
        {
            "                   ",
            "   + +   + + +     ",
            "   +  VITORIA  +   ",
            "               +   ",
            "   +   _A.A_   +   ",
            "   +   \\{+}/       ",
            "   +    :I:    +   ",
            "     + + +   + +   ",
            "                   ",
        },
    },
};

struct termios velho_terminal, novo_terminal;
void mudar_terminal(){
    tcgetattr(STDIN_FILENO, &velho_terminal);
    novo_terminal = velho_terminal;

    novo_terminal.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &novo_terminal);
}

void subida_de_nivel(int nivel){
    int a = 0;

    while(1){
        printf(VOLTAR); usleep(SEGUNDOS*0.5);
        imprimir_em_cima(9, 20, level_up[nivel][a], 1, 6, 3, 0);
        a++;
        if(a==4)a=0;

        char c;
        if(read(STDIN_FILENO, &c, 1) > 0) break;

        printf("\nPressione qualquer tecla para continuar.\n\n");
    }
    system("clear");
}


int main(){
    mudar_terminal();
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    subida_de_nivel(3);
    return 0;
}