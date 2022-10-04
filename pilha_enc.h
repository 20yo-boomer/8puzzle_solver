#ifndef _PILHA_ENC_H_
#define _PILHA_ENC_H_

#include "lista_enc.h"

typedef struct pilhaEnc{
   struct nodoLEnc *topo;
} PilhaEnc;

// Funcao que cria uma pilha
PilhaEnc* criaPilha();

// Funcao que destroi uma pilha
void destroiPilha(PilhaEnc *pilha);

// Funcao que insere um elemento na pilha
void empilhaPilha(PilhaEnc *pilha, Info info);

// Funcao que remove um elemento da pilha
Info desempilhaPilha(PilhaEnc *pilha);

// Funcao que determina se uma pilha eh vazia
int vaziaPilha(PilhaEnc* pilha);

// Função que inverte uma pilha
void invertePilha(PilhaEnc *pilha);

#endif
