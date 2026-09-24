# ACE-COMBAT
Jogo de combate aéreo com aviões em terminal, inspirado em Ace Combat

Para executar:
1. Baixe e descompacte os arquivos do projeto  
2. Abra a pasta no terminal  
3. Digite: make && ./acecombat  

## Resumo
O jogo possui um modo de niveis e um modo infinito.  
No modo de níveis, existem 3 fases, sendo a última dedicada ao Boss Final.  
Cada fase possui configurações próprias de inimigos, player e nivel.  
Além disso, uma vida extra (simbolizada por um @ verde) spawna ocasionalmente no mapa, dando mais hp ao jogador.  

O modo infinito gera inimigos de todos os niveis e só termina quando o jogador morre.  

As variáveis são divididas entre entidades, projeteis e configurações

### Das Entidades
Entidades são elementos moveis e de durabilidade temporária, ou seja os projeteis e os proprios aviões.  

Existem dois tipos de aviões: o player (quem o jogador controla) e os inimigos (que atacam o jogador).  

Cada avião tem sua propria sprite (modelo do aviao) e configurações guardadas numa struct denominada Entidade. Cada fase possui uma configuração diferente de aviões.  

As seguintes informações são relativas a todos os avioes:
- Nivel ao qual pertence
- Coordenada atual
- Vida
- Largura e altura
- Estado (normal, levou dano, morto)

O player e os inimigos compartilham da mesma struct, apesar do player não usar todos os elementos.  
As seguintes informações são relativas somente aos inimigos:
- Posições possiveis de spawn (relativas somente à coordenada x, pois todos os inimigos nascem obrigatoriamente fora da tela)
- Cooldown de troca de ataque
- Cooldown de disparo
- Cooldown de movimentação  

Os aviões possuem um certo numero de ataques que variam com o tempo, e cada ataque gera certo numero de projeteis por turno.
As seguintes informações são relativas à forma e ataque de todos os aviões:
- Quantidade de ataques
- Ataque ativo
- Quantidade de projeteis gerada por cada ataque (vetor unidimensional)
- Vetor tridimensional de projeteis
- Vetor bidimensional que guarda a quantidade de projeteis sendo utilizados para cada ataque e cada posição.
  
No vetor de projeteis, a primeira dimensão diz respeito ao tipo de ataque, a segunda diz sobre os projeteis que são disparados por turno, e a terceira é um projetil singular.  

Por exemplo, em um avião que possui ataque único de disparo duplo, disparando um projetil pela esquerda (0) e outro pela direita (1), a estrutura aviao.projetil[0][1] acessa o vetor de todos os projeteis que são gerados pela direita, e avião.projetil[0][0] acessa o vetor dos que são gerados pela esquerda.  

Em outro exemplo, para um aviao que possui 2 ataques: o primeiro sendo um único disparo reto, o segundo sendo dois disparos diagonais (0 e 1) e um reto (2), a estrutura aviao.projetil[0][0] acessa o vetor dos projeteis deste primeiro ataque, aviao.projetil[1][1] acessa o vetor de um dos dois disparos diagonais do segundo ataque e aviao.projetil[1][2] acessa o do disparo reto do segundo ataque.  
Observe que, apesar de pertencerem ao mesmo tipo de ataque, os projeteis podem ter configurações diferentes, ou seja, fazer trajetorias distintas, causar diferentes quantidades de dano, etc, pois cada um tem uma estrutura própria.  

A partir destas configurações, é possível gerenciar inimigos simples e grandes chefões a partir das mesmas funções no código fonte.  

### Dos Projeteis
Projeteis são um tipo de entidade, mas com struct propria. Possuem informações personalizaveis para se adequar a qualquer modelo de aviao, que são as seguintes:
- Coordenada atual
- Direção da trajetória
- Coordenada do spawn (relativa ao aviao)
- Quantidade de dano que gera
- Cor
- Caractere que simboliza seu formato

### Das configurações
Controla variáveis externas às entidades, que são as seguintes:
- Cooldown de spawn de inimigos
- Tempo enquanto a vida extra está ativa
- Tempo enquanto a vida extra está inativa
- Quantidade de hp que uma vida extra recupera
- Pontos conquistados por abate
- Abates minimos para passar de nivel

## O Codigo Fonte
O código está organizado nas seguintes pastas:
- Include: possui o cabeçalho das funções e, em settings, referencias às princiapis variaveis, structs e macros do código.
- Source: dividido na pasta definitions (configurações de entidades, de nível, sprites, definição de variáveis globais), pasta functions (cálculos realizados durante a execução do jogo), o arquivo main (onde ocorre o jogo) e o arquivo allmain (gerencia a mudança de fases e é onde está o int main).
- Objects: arquivos objetos relativos aos arquivos em C de source.

Informações mais detalhadas são encontradas no topo dos próprios arquivos.  
