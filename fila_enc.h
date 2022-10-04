#ifndef _FILA_ENC_H_
#define _FILA_ENC_H_

#include "lista_enc.h"

typedef struct FilaEnc{
   struct nodoLEnc *ini;
   struct nodoLEnc *fim;
} FilaEnc;

// Funcao que cria uma fila
FilaEnc* criaFila();

// Funcao que destroi uma fila
void destroiFila(FilaEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFila(FilaEnc *fila, Info info);

// Funcao que remove um elemento da fila
Info desenfileiraFila(FilaEnc *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFila(FilaEnc* fila);

// Função que inverte fila
void inverteFila(FilaEnc *fila);

#endif
