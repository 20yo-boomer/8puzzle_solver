#include "pilha_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma pilha
PilhaEnc* criaPilha(){
   PilhaEnc *pilha = (PilhaEnc*)malloc(sizeof(PilhaEnc));
   pilha->topo = NULL;
   return pilha;
}

// Funcao que destroi uma pilha
void destroiPilha(PilhaEnc *pilha){
   NodoLEnc *aux = pilha->topo;
   while(aux != NULL){
       NodoLEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(pilha);
}

// Funcao que insere um elemento na pilha
void empilhaPilha(PilhaEnc *pilha, Info info){
   NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
   novo->info = info;
   novo->prox = pilha->topo;
   pilha->topo = novo;
}

// Funcao que remove um elemento da pilha
Info desempilhaPilha(PilhaEnc* pilha){
   NodoLEnc *aux = pilha->topo; 
   /* Aqui assumimos que desempilha eh 
   chamada apenas se a pilha nao eh vazia */
   Info info = aux->info;
   pilha->topo = aux->prox;
   free(aux);
   return info;
}

// Funcao que determina se uma pilha eh vazia
int vaziaPilha(PilhaEnc *pilha){
   return (pilha->topo == NULL);
}

// Função que inverte uma pilha
void invertePilha(PilhaEnc *pilha){
	PilhaEnc* pilha_aux;
	pilha_aux = criaPilha();
	// Simplesmente vai passando o topo da pilha original para o chão da
	// pilha auxiliar, depois põe o conteúdo da pilha auxiliar na pilha
	// original.
	while(!vaziaPilha(pilha)){
		empilhaPilha(pilha_aux, desempilhaPilha(pilha));
	}
	*pilha = *pilha_aux;
	free(pilha_aux);
}
