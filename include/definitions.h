/*
    Referencia as variaveis de inicialização
    Incluir "definitions.h" a qualquer arquivo é suficiente para que ele reconheça todas estas
    variaveis.
*/

#include "settings.h" 

#ifdef SETTINGS

extern Config configuracoes_de_fase[MAX_NIVEIS];

extern Entidade inicializar_inimigo[MAX_NIVEIS];

extern Projetil inicializar_projetil_inimigo[MAX_NIVEIS][MAX_ATAQUES][MAX_TPS];

extern Entidade inicializar_player[MAX_NIVEIS];

extern Projetil inicializar_projetil_player[MAX_NIVEIS][MAX_ATAQUES][MAX_TPS];

#endif