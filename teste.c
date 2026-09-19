#include <stdio.h>
#include <unistd.h>
#define VOLTAR "\033[H"
#define SEGUNDOS 1000000

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

char teste[9][20]={
    "     + SUPER +     ",
    "   + AIR ACTION +  ",
    "     + 3000! +     ",
    "         A         ",
    "  ____^-/|\\-^____  ",
    "  '+__|_:*:_|__+'  ",
    "       __|__       ",
    "       'v=v'       ",
    "     * * * * *     ",
};

void imprimir_em_cima(int altura, int largura, char imagem[altura][largura], int dx, int dy, int cor, float tempo){
    for(int y=0; y<21; y++){
        for(int x=0; x<21; x++) printf("%c", mapa[y][x]);
        printf("\n");
    }
    printf(VOLTAR);

    printf("\033[%dB", dy);

    for(int y=0; y<altura; y++){
        printf("\033[%dC", dx);

        for(int x=0; x<largura; x++){
            printf("%c", imagem[y][x]);
            if(imagem[y][x] != ' '){
                fflush(stdout);
                usleep(SEGUNDOS*tempo);
            }
        }
        printf("\n");
    }
    printf("\033[%dB", 21-altura-dy);
}

int main(){
    imprimir_em_cima(9, 20, teste, 1, 6, 0, 0.01);
    
    
    return 0;
}