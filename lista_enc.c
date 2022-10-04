#include "lista_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma lista
ListaEnc* criaLista(){
	ListaEnc *lista = (ListaEnc*)malloc(sizeof(ListaEnc));
	lista->prim = NULL;
	return lista;
}

// Funcao que destroi uma lista
void destroiLista(ListaEnc *lista){
	NodoLEnc *aux = lista->prim;
	while(aux != NULL){
		NodoLEnc *tmp = aux->prox;
		free(aux); // Cuidar ordem do free
		aux = tmp;
	}
	free(lista);
}

// Funcao que imprime todos os nodos de uma lista
void imprimeLista(ListaEnc *lista){
	NodoLEnc *aux;
	printf("-----------------------------------------\n");
	for(aux = lista->prim; aux != NULL; aux = aux->prox)
		printf("%s\n", aux->info.estado);
	printf("-----------------------------------------\n");
}

// Funcao que insere um nodo no inicio de uma lista
int insereInicioLista(ListaEnc *lista, Info info){
	NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
	if (novo == NULL) // Nao ha espaco em memoria
		return 0;
	novo->info = info;
	novo->prox = lista-> prim;
	lista->prim = novo;
	return 1;
}

// Funcao que resgata um nodo com uma informacao de uma lista
NodoLEnc* buscaInfoLista(ListaEnc* lista, int matricula){
	// TODO
	return NULL; 
}

// Funcao que remove um nodo com uma informacao de uma lista
int removeInfoLista(ListaEnc* lista, int matricula){
	// TODO
	return 0;
}

