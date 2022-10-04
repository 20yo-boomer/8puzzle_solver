#include "fila_enc.h"
#include "pilha_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma fila
FilaEnc* criaFila(){
   FilaEnc *fila = (FilaEnc*)malloc(sizeof(FilaEnc));
   fila->ini = NULL;
   fila->fim = NULL;
   return fila;
}

// Funcao que destroi uma fila
void destroiFila(FilaEnc *fila){
   NodoLEnc *aux = fila->ini;
   while(aux != NULL){
       NodoLEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(fila);
}

// Funcao que insere um elemento na fila
void enfileiraFila(FilaEnc *fila, Info info){
   NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
   novo->info = info;
   novo->prox = NULL;
   if (fila->fim != NULL)
      fila->fim->prox = novo;
   else
      fila->ini = novo;
   fila->fim = novo;
}

// Funcao que remove um elemento da fila
Info desenfileiraFila(FilaEnc *fila){
   NodoLEnc *aux = fila->ini; 
   Info info = aux->info;
   fila->ini = aux->prox;
   if (fila->ini == NULL)
      fila->fim = NULL;
   free(aux);
   return info;
}

// Funcao que determina se uma fila eh vazia
int vaziaFila(FilaEnc *fila){
   return (fila->ini == NULL);
}

// Função que inverte fila
void inverteFila(FilaEnc *fila){
	/*                                 ALGORITMO
	  Digamos que a fila original é fila.ini -> F1 -> F2 -> F3 -> NULL, com fila.fim -> F3
	  Faz-se uma pilha auxiliar e põe a fila nela. Agora a pilha é
	  pilha.topo -> F1 -> F2 -> F3 -> NULL
	  Coloca-se a pilha numa fila. A fila é fila.ini -> F3 -> F2 -> F1 -> NULL.
	*/

	// Pilha auxiliar
	PilhaEnc* pilha_aux;
	pilha_aux = criaPilha();
	// Fila auxiliar
	FilaEnc* fila_aux;
	fila_aux = criaFila();
	// Copiar da fila original para a pilha
	while(!vaziaFila(fila)){
		empilhaPilha(pilha_aux, desenfileiraFila(fila));
	}
	// Copiar da pilha auxiliar para a fila auxiliar
	while(!vaziaPilha(pilha_aux)){
		enfileiraFila(fila_aux, desempilhaPilha(pilha_aux));
	}

	*fila = *fila_aux;
	free(fila_aux);
	free(pilha_aux);
}
