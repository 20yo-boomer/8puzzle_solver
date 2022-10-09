#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include "lista_enc.h"
#include "fila_enc.h"

typedef int hashtable[362880];

// Imprime um tabuleiro como uma matriz bonitinha
void imprime_estado(char* estado);

// Dado um estado e um movimento, descobre qual o novo estado
char* realiza_movimento(char* estado, char acao);

// Dado um estado (Info), retorna uma lista com os possíveis sucessores (Info)
// Usada para montar o grafo
ListaEnc* sucessores(Info estado);

// As funções a seguir recebem um estado e realizam o respectivo algoritmo para encontrar
// o objetivo. (Talvez no futuro receber estado inicial + objetivo para achar o caminho.)
// Elas retornam o caminho a ser realizado para chegar do estado inicial ao objetivo.
FilaEnc* bfs(char* estado);
FilaEnc* dfs(char* estado);
FilaEnc* astar_hamming(char* estado);
FilaEnc* astar_manhattan(char* estado);

// Recebe uma configuração (e.g. "2_3541687") e retorna o índice dela em um vetor.
// Ou seja, recebe uma permutação de "_012345678" e retorna um valor único dela.
int hash(char* string);

// Recebe um estado e retorna o número de peças com o número errado
int hamming(char* string);

// Recebe um estado e retorna a soma das distâncias Manhattan de cada peça do tabuleiro
// atual até a coordenada em que ela deveria estar.
int manhattan(char* string);

#endif
