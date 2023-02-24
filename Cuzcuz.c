#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int cartas;
	int jogando;
	int A;
	char S;
	struct Node *next;
} Node;

Node *createNode(Node *newNode, int newA, char newS);

/* Funcoes da pilha: */
Node *stackPush(Node *head, int newA, char newS);
Node *stackPop(Node *head);

/* Funcoes de fila */
Node *enqueue(Node *head, Node *tail, int newA, char newS);
Node *dequeue(Node *head, Node *tail);

int main(void) {
	int R = 0, N, newA, vencedor = -1, vencedorCartas = -1;
	char newS, opr[4];
	
	scanf("%d", &N);
	Node *s = createNode(s, -1, ' ');
	s->cartas = 0;
	Node **jogadores_head = (Node **) malloc(N * sizeof(Node *));
	Node **jogadores_tail = (Node **) malloc(N * sizeof(Node *));
	for(int i = 0; i < N; i++) {
		jogadores_head[i] = (Node *) malloc(sizeof(Node));
		jogadores_head[i]->jogando = 1;
		jogadores_head[i]->cartas = 0;
		jogadores_tail[i] = (Node *) malloc(sizeof(Node));
	}

	while(strcmp(opr, "END") != 0) {
		scanf("%s", opr);

		if(strcmp(opr, "DEA") == 0) {
			for(int i = 0; i < N; i++) {
				if(jogadores_head[i]->jogando == 1){
					scanf("%d %c", &newA, &newS);
					jogadores_tail[i] = enqueue(jogadores_head[i], jogadores_tail[i], newA, newS); 
				}
			}
		}
			
		else if(strcmp(opr, "RND") == 0) {
			int A = 0, jogador = -1, cartas = 0, empate = 0;
			char S = 'A';
	
			do { // Enquanto não houver empate
				jogador = -1;
				empate = 0;
				A = 0;
				S = 'A';
				for(int i = 0; i < N; i++) { // Percorre todos os jogadores
					if(jogadores_head[i]->jogando == 1) { // Mas verifica as mãos apenas dos que ainda estão jogando
						s = stackPush(s, jogadores_head[i]->next->A, jogadores_head[i]->next->S); // Adiciona à pilha a mão do jogador i
						Node *topo = s->next;
						if(topo->A > A) { // Verifica se é a maior. Se sim, atualiza!
							jogador = i;
							A = topo->A;
							S = topo->S;
							empate = 0;
						}
						else if(topo->A == A) { // Se for igual, verifica o nipe:
							if(topo->S > S) { // Se o nipe for maior, atualiza!
								jogador = i;
								A = topo->A;
								S = topo->S;
								empate = 0;
							}
							else if (topo->S == S) { // Se for igual, marca um empate!
								empate = 1;
							}
						}
						
						jogadores_head[i] = dequeue(jogadores_head[i], jogadores_tail[i]); // Remove as cartas da mão do jogaor!
					}
				}	
				
				cartas = s->cartas;
				if(empate != 1 && jogador != -1) {
					while(s->next != NULL) {
						jogadores_tail[jogador] = enqueue(jogadores_head[jogador], jogadores_tail[jogador], s->next->A, s->next->S);
						s = stackPop(s);
					}
					vencedor = jogador;
                    jogadores_head[jogador]->jogando = 1;
				}
			} while(empate == 1);

			int temp = 0;
			for(int i = 0; i < N; i++) {
				if(jogadores_head[i]->cartas > temp) {
					temp = jogadores_head[i]->cartas;
					vencedorCartas = i;
				}
			}
			
			if(vencedor != -1) {
				printf("%d %d %d\n", R, vencedor, cartas);
			}
			else {
				printf("-1 -1 -1\n-1\n");
				return 0;
			}
			R++;

			/* for(int i = 0; i < N; i++) {
				Node *aux = jogadores_head[i]->next;
                printf("StatusJogando[%d]:%d\n", i, jogadores_head[i]->jogando);
				printf("Cartas do jogador %d: ", i);
				while(aux != NULL) {
					printf("%d%c ", aux->A, aux->S);
					aux = aux->next;
				} printf("\n");
			} */
		}
	}

	printf("%d\n", vencedorCartas);
	
	return 0;
}

Node *createNode(Node *newNode, int newA, char newS) {
	newNode = (Node *) malloc(sizeof(Node));
	newNode->A = newA;
	newNode->S = newS;
	newNode->next = NULL;

	return newNode;
}

/* Funcoes da pilha: */
Node *stackPush(Node *head, int newA, char newS) {
	/*
		Cria um novo nó que recebe o novo dado
		A referência para o próx do novo nó é o top da pilha
		Atualiza a referência para o novo topo da pilha
		Retorna o sentinela
	*/
	Node *newNode = createNode(newNode, newA, newS);

	newNode->next = head->next;
	head->next = newNode;
	head->cartas++;
	
	return head;
}

Node *stackPop(Node *head) {
	/*
		Verificar se a pilha existe!
		"Capturar" o primeiro elemento da pilha (topo)
		Atualizar a referência para o novo topo da pilha usando o próx do topo
		*********Limpa a memória do antigo topo (elemento removido)
		Retorna o sentinela
	*/
	if(head->next == NULL) {
		return head;
	}

	Node *top = head->next;
	head->next = top->next;
	head->cartas--;
	
	return head;
}

/* Funcoes de fila */
Node *enqueue(Node *head, Node *tail, int newA, char newS) {
	/*
		Cria um novo nó que recebe o novo dado
		Verifica se a fila está vazia
			-> Se sim, o elemento é o início e o fim da fila.
			-> Se não, segue...
		Ultimo elemento aponta para o novo nó
		Atualiza a referência para o novo final da fila
		Retorna o sentinela para o final da fila (tail)
	*/
	Node *newNode = createNode(newNode, newA, newS);

	if(head->next == NULL) {
		head->next = newNode;
		tail->next = newNode;
	}
	else {
		Node *lastElement = tail->next;
		lastElement->next = newNode;
		tail->next = newNode;
	}
	head->cartas++;
	
	return tail;
}

Node *dequeue(Node *head, Node *tail) {
	/*
		Verifica se a fila existe!
		"Captura" o primeiro elemento da fila
		Atualiza a referência para o novo início da fila usando o próx do início
		*********Limpa a memória do antigo início da fia (elemento removido)
		* Verifica se a fila ficou vazia após a remocao!!!
			-> Se sim, o tail e o head apontam para NULL
			-> Se não, segue..
		Retorna o sentinela para o inicio da fila (head)
	*/
	if(head->next == NULL) {
		return head;
	}

	Node *firstElement = head->next;
	head->next = firstElement->next;
	if(head->next == NULL) {
		head->jogando = 0;
		tail->next = head->next;
	}
	head->cartas--;

	return head;
}