#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include "lista_enc.h"
#include "fila_enc.h"

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
ListaEnc* dfs(char* estado);
ListaEnc* astar_hamming(char* estado);
ListaEnc* astar_manhattan(char* estado);

#endif
