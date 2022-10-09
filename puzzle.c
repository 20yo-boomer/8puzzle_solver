#include "puzzle.h"
#include "lista_enc.h"
#include "pilha_enc.h"
#include "fila_enc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void imprime_estado(char* estado){
	/* Dado um estado no formato char[9], imprime ele na forma de um 8-puzzle,
	 * uma matriz 3x3 com um espaço em branco. */
	printf(" _____ \n");
	printf("|%c %c %c|\n", estado[0], estado[1], estado[2]);
	printf("|%c %c %c|\n", estado[3], estado[4], estado[5]);
	printf("|%c %c %c|\n", estado[6], estado[7], estado[8]);
	printf(" ‾‾‾‾‾ \n");
}

char* realiza_movimento(char* estado, char acao){
	/* estado: Um ponteiro para uma string representando um estado. Por exemplo, "2_3541687".
	 * acao: Uma das possíveis ações: 'B', 'C', 'D', 'E' (baixo, cima, direita, esquerda).
	 * retorno: O estado resultante de realizar essa ação nesse estado inicial. */
	char* novo_estado = strdup(estado); // Duplicata de 'estado' p/ não mexer no objeto original
	int movimento;
	// 'movimento' é o movimento que o '_' vai fazer. Se ele está na posição p, vai trocar
	// com o caractere na posição p+movimento.
	if(acao == 'B') movimento = 3;
	else if(acao == 'C') movimento = -3;
	else if(acao == 'D') movimento = 1;
	else if(acao == 'E') movimento = -1;
	// Realiza a troca
	char* espaco = strchr(novo_estado, '_'); // strchr retorna um ponteiro p/ localização de '_'
	*espaco = *(espaco+movimento);
	*(espaco+movimento) = '_';
	return novo_estado;
}

// Dado um estado (Info), retorna uma lista encadeada com seus possíveis sucessores (Infos)
ListaEnc* sucessores(Info nodo){
	// Inicializa variáveis
	ListaEnc* lista = NULL;
	lista = criaLista();
	bool pode_mover[4] = {true, true, true, true};
	char acoes[4] = {'B', 'C', 'D', 'E'};
	char* estado = nodo.estado;
	int posicao_do_espaco = (int)(strchr(estado, '_') - estado);
	
	// Lembrando que as posições são como desenhado abaixo, temos:
	// 0, 1, 2
	// 3, 4, 5
	// 6, 7, 8
	if (posicao_do_espaco / 3 == 2) pode_mover[0] = false; // 6, 7, 8
	if (posicao_do_espaco / 3 == 0) pode_mover[1] = false; // 0, 1, 2
	if (posicao_do_espaco % 3 == 2) pode_mover[2] = false; // 2, 5, 8
	if (posicao_do_espaco % 3 == 0) pode_mover[3] = false; // 0, 3, 6
	// Usando o vetor pode_mover, faz a lista de nodos sucessores
	for(int i = 3; i >= 0; i--){
		// i começa em 3 e termina em 0 para que o início da lista (o último adicionado)
		// acompanhe o início do vetor acoes. Mas seria mais elegante fazer i = 0; i < 4
		// e usar insereFimLista com uma lista que tem um ponteiro apontando para o
		// fim, em vez de uma lista encadeada simples.
		// TODO: Usar fila em vez de lista e inserir no fim da fila
		if(pode_mover[i]){
			char* novo_estado = realiza_movimento(estado, acoes[i]);
			// Lembrando que Info tem atributos 'estado', 'pai', 'acao' e 'custo':
			Info novo_nodo = {novo_estado, &nodo, acoes[i], nodo.custo + 1};
			insereInicioLista(lista, novo_nodo);
		}
	}
	return lista; // Aonde que se destroi a lista?
}

// Funções auxiliares (factorial, hash, manhattan, hamming)
int factorial(int n){
	switch(n){
		case 0:
			return 1;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 6;
			break;
		case 4:
			return 24;
			break;
		case 5:
			return 120;
			break;
		case 6:
			return 720;
			break;
		case 7:
			return 5040;
			break;
		case 8:
			return 40320;
			break;
	}
}

int hash(char* string){
	int numbers[9];
	// Converte "123_" para {1, 2, 3, 0}
	for(int i = 0; i < 9; i++){
		if(string[i] == '_'){
			numbers[i] = 0;
		} else {
			numbers[i] = string[i] - '0'; // e.g. '4' - '0' = 4
		}
	}
	int result = 0;
	int n_de_menores = 0;
	for(int i = 0; i < 9; i++){
		for(int j = i; j < 9; j++) if(numbers[j] < numbers[i]) n_de_menores++;
		result += factorial(8-i) * n_de_menores;
		n_de_menores = 0;
	}
	return result;
}

// As duas funções a seguir acabaram não sendo usadas, mas o plano era aplicar
// na busca heurística.
int hamming(char* string){
	char* objetivo = "12345678_";
	int result = 0;
	for(int i = 0; i < strlen(string); i++){
		if(string[i] != objetivo[i]){
			result++;
		}
	}
	// Se o espaço vazio está na posição errada, não nos importamos.
	return result - (string[8] != '_');
}
int manhattan(char* string){
	char* objetivo = "12345678_";
	int soma_das_distancias = 0;
	for(int i = 0; i < strlen(string); i++){
		if(string[i] == '_') continue;
		// char to int
		int s = string[i] - '1';
		int o = i; // TODO: fazer "o" ser dependente da vairável objetivo, tipo objetivo[i]
		// Posição em que string[i] deveria estar:
		int x_s = s % 3;
		int y_s = s / 3;
		int x_o = o % 3;
		int y_o = o / 3;
		// Distância Manhattan: abs(x_s - x_o) + abs(y_s - y_o)
		// printf("Distância do %d: x: %d, y: %d\n", s+1, abs(x_s - x_o), abs(y_s - y_o));
		soma_das_distancias += abs(x_s - x_o) + abs(y_s - y_o);
	}
	return soma_das_distancias;
}

// Implementa BFS. Dado um estado (string) retorna o caminho percorrido (lista de nodos).
FilaEnc* bfs(char* estado){
	// Inicializa variáveis
	Info nodo = {estado, NULL, 'N', 0}; // Raiz do grafo, não tem pai nem ação
	// Para o BFS usamos uma fila (first in, first out)
	FilaEnc* fila;
	fila = criaFila(); // Os nodos esperando para ser explorados vão ir aqui
	enfileiraFila(fila, nodo); // A começar pela raiz
	ListaEnc* explorados;
	explorados = criaLista(); // Todos nós explorados até agora
	hashtable tabela_de_explorados = {0};
	Info v; // O nó a ser explorado em cada iteração do loop
	ListaEnc* filhos;
	Info* endereco_do_pai;
	// Loop
	while(1){
		// Caso sem solução
		if(vaziaFila(fila)){
			printf("\nNão há solução para o estado fornecido.\n");
			return NULL;
		}
		// Examina o nodo mais antigo na fila
		v = desenfileiraFila(fila);
		// Adiciona v nos explorados
		insereInicioLista(explorados, v);
		tabela_de_explorados[hash(v.estado)] = 1;
		// Guarda o endereço do nó na lista de explorados, para o filho poder referenciar
		// na hora de pegar o caminho percorrido
		endereco_do_pai = &explorados->prim->info;
		// Para fins de teste, imprime o custo do nodo examinado (deve ser crescente)
		printf("\rCusto do nodo analisado: %d", v.custo);
		fflush(stdout);
		//printf("%s %p %c %d\n", v.estado, v.pai, v.acao, v.custo);
		// Se for o vértice objetivo, retorna o caminho
		if(strcmp(v.estado, "12345678_") == 0){ // comparação de strings
			printf("\nObjetivo encontrado!\n");
			FilaEnc* caminho;
			caminho = criaFila();
			for(Info* aux = &v; aux != NULL; aux = aux->pai){
				enfileiraFila(caminho, *aux);
			}
			// Imprime o caminho
			// TODO: Transformar isso aqui em uma função imprimeFila
			for(NodoLEnc* aux = caminho->ini; aux != NULL; aux = aux->prox){
				printf("estado: %s  acao: %c  custo: %d  \n", aux->info.estado,
										                      aux->info.acao,
								                              aux->info.custo);
			}
			return caminho;
		}
		// Verifica os filhos de v, e, se não estiverem na lista de explorados, põe na
		// fila dos que vão ser explorados
		filhos = sucessores(v);
		for(NodoLEnc* aux = filhos->prim; aux != NULL; aux = aux->prox){
			Info filho = aux->info;
			filho.pai = endereco_do_pai;
			// Verifica se ele já foi explorado.
			bool contem = tabela_de_explorados[hash(filho.estado)];
			if(!contem){
				enfileiraFila(fila, filho);
			}
		}
	}
}

// Implementa DFS. Dado um estado (string) retorna o caminho percorrido (lista de nodos).
FilaEnc* dfs(char* estado){
	// Inicializa variáveis
	Info nodo = {estado, NULL, 'N', 0}; // Raiz do grafo, não tem pai nem ação
	// Para o DFS usamos uma pilha (last in, first out)
	PilhaEnc* pilha;
	pilha = criaPilha(); // Os nodos esperando para ser explorados vão ir aqui
	empilhaPilha(pilha, nodo); // A começar pela raiz
	ListaEnc* explorados;
	explorados = criaLista(); // Todos nós explorados até agora
	hashtable tabela_de_explorados = {0};
	Info v; // O nó a ser explorado em cada iteração do loop
	ListaEnc* filhos;
	Info* endereco_do_pai;
	// Loop
	while(1){
		// Caso sem solução
		if(vaziaPilha(pilha)){
			printf("Não há solução para o estado fornecido.\n");
			return NULL;
		}
		// Examina o nodo mais antigo na fila
		v = desempilhaPilha(pilha);
		// Adiciona v nos explorados
		insereInicioLista(explorados, v);
		tabela_de_explorados[hash(v.estado)] = 1;
		// Guarda o endereço do nó na lista de explorados, para o filho poder referenciar
		// na hora de pegar o caminho percorrido
		endereco_do_pai = &explorados->prim->info;
		// Para fins de teste, imprime o custo do nodo examinado (deve ser crescente)
		printf("\rCusto do nodo analisado: %d", v.custo);
		fflush(stdout);
		//printf("%s %p %c %d\n", v.estado, v.pai, v.acao, v.custo);
		// Se for o vértice objetivo, retorna o caminho
		if(strcmp(v.estado, "12345678_") == 0){ // comparação de strings
			printf("Objetivo encontrado!\n");
			FilaEnc* caminho;
			caminho = criaFila();
			for(Info* aux = &v; aux != NULL; aux = aux->pai){
				enfileiraFila(caminho, *aux);
			}
			// Imprime o caminho
			// TODO: Transformar isso aqui em uma função imprimeFila
			for(NodoLEnc* aux = caminho->ini; aux != NULL; aux = aux->prox){
				printf("estado: %s  pai: %p  acao: %c  custo: %d  \n", aux->info.estado,
						                                               aux->info.pai,
										                               aux->info.acao,
								                                       aux->info.custo);
			}
			return caminho;
		}
		// Verifica os filhos de v, e, se não estiverem na lista de explorados, põe na
		// fila dos que vão ser explorados
		filhos = sucessores(v);
		for(NodoLEnc* aux = filhos->prim; aux != NULL; aux = aux->prox){
			Info filho = aux->info;
			filho.pai = endereco_do_pai;
			// Verifica se ele já foi explorado.
			bool contem = tabela_de_explorados[hash(filho.estado)];
			if(!contem){
				empilhaPilha(pilha, filho);
			}
		}
	}
}
