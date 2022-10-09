#include <stdio.h>
#include <string.h>
#include "fila_enc.h"
#include "pilha_enc.h"
#include "lista_enc.h"
#include "puzzle.h"

void testa_realiza_movimento(char* estado, char movimento);
void testa_sucessores(Info nodo);

int main(){
	// Testar função 'realiza_movimento'
	//testa_realiza_movimento(estado, 'B');
	//testa_realiza_movimento(estado, 'D');
	//testa_realiza_movimento(estado, 'E');
	
	//printf("-----------------------\n\n");

	// Testar função 'sucessores'
	//testa_sucessores(nodo);
	
	//printf("-----------------------\n");
	
	// Testar BFS
	//printf("Caminho curto: \n");
	//imprime_estado("1234567_8");
	//bfs("1234567_8");

	//printf("\nCaminho de tamanho 25:\n");
	//bfs("874_26351");

	printf("\nTabuleiro impossível: 12345687_\n");
	dfs("12345687_");

	return 0;
}





















void testa_realiza_movimento(char* estado, char movimento){
	char* novo_estado;
	novo_estado = realiza_movimento(estado, movimento);
	printf("Movimento realizado: %c\n", movimento);
	printf("Estado após o movimento:\n");
	imprime_estado(novo_estado);
}

void testa_sucessores(Info nodo){
	ListaEnc* lista;
	lista = sucessores(nodo);
	printf("Possíveis sucessores do estado inicial:\n");
	for(NodoLEnc* aux = lista->prim; aux != NULL; aux = aux->prox){
		imprime_estado(aux->info.estado);
	}
	// Imprimir só as strings:
	printf("-----------------------\n");
	printf("Impressos como nodos:\n\n");
	for(NodoLEnc* aux = lista->prim; aux != NULL; aux = aux->prox){
		printf("estado: %s\npai: %p\nacao: %c\ncusto: %d\n\n", aux->info.estado,
				                                               aux->info.pai,
				                                               aux->info.acao,
				                                               aux->info.custo);
	}
}
