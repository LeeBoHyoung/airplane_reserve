#define _CRT_SECURE_NO_WARNINGS
#include "final.h"

char arr_city[30][20];
graph G[15] = { 0 };
int Visited[15] = { 0 };
char stack[15] = { '0' }; top = -1, r = 0;

void add_vertex(graph* arr, char item) {
	int i = 0;
	graph newnode = (graph)malloc(sizeof(node));
	newnode->vertex = item;
	newnode->vertex_link = NULL;
	newnode->edge_link = NULL;
	if (*arr == NULL)
		*arr = newnode;
	else {
		while (arr[i] != 0) {
			if (arr[i]->vertex == item)
				return;
			i++;
		}
		arr[i] = newnode;
	}
}

void add_edge(graph v1, graph v2, int weight) {
	graph new = (graph)malloc(sizeof(node));
	new->vertex = v2->vertex;
	new->weight = weight;
	new->vertex_link = v2->edge_link;
	new->edge_link = NULL;
	if (v1->edge_link == NULL)
		v1->edge_link = new;
	else {
		graph temp = v1;
		while (temp->edge_link != NULL)
			temp = temp->edge_link;
		temp->edge_link = new;
	}
}

int index_vertex(graph* arr, char vertex) {
	int i = 0;
	while (arr[i]->vertex != vertex)
		i++;
	return i;
}

void DFS(int vertex) {
	int v = index_vertex(G, vertex);
	graph w;
	Visited[v] = 1;
	printf("%c ", vertex);
	for (w = G[v]; w; w = w->edge_link) {
		int temp = index_vertex(G, w->vertex);
		if (Visited[temp] == 0)
			DFS(w->vertex);
	}

}

void DFS_route(char v, char goal) {
	int v_index = index_vertex(G, v);
	graph w = G[v_index];
	Visited[v_index] = 1;
	stack[++top] = v;

	if (v == goal) {
		//if (top <= 4) {
			for (int i = 0; i <= top; i++) {
				arr_city[r][i] = stack[i];
			}
		//}	
		top--; r++;
		return;
	}

	while (w != NULL) {
		int temp = index_vertex(G, w->vertex);
		if (Visited[temp] == 0) {
			DFS_route(w->vertex, goal);
			Visited[temp] = 0;
		}
		w = w->edge_link;
	}
	top--;
}

void make_graph() {
	add_vertex(G, 'I');
	add_vertex(G, 'J');
	add_vertex(G, 'K');
	add_vertex(G, 'O');
	add_vertex(G, 'L');
	add_vertex(G, 'A');
	add_vertex(G, 'N');
	add_vertex(G, 'M');
	add_vertex(G, 'E');
	add_vertex(G, 'C');
	add_vertex(G, 'F');
	add_vertex(G, 'D');
	add_vertex(G, 'B');
	add_vertex(G, 'H');
	add_vertex(G, 'G');

	add_edge(G[0], G[1], 150);
	add_edge(G[0], G[3], 500);
	add_edge(G[0], G[12], 300);
	add_edge(G[0], G[14], 100);
	add_edge(G[1], G[0], 150);
	add_edge(G[1], G[2], 200);
	add_edge(G[2], G[1], 200);
	add_edge(G[2], G[3], 150);
	add_edge(G[3], G[0], 500);
	add_edge(G[3], G[2], 150);
	add_edge(G[3], G[4], 500);
	add_edge(G[3], G[6], 1000);
	add_edge(G[4], G[3], 500);
	add_edge(G[4], G[5], 200);
	add_edge(G[5], G[4],  200);
	add_edge(G[5], G[6], 100);
	add_edge(G[6], G[3], 1000);
	add_edge(G[6], G[5], 100);
	add_edge(G[6], G[7], 400);
	add_edge(G[6], G[9], 750);
	add_edge(G[7], G[6], 400);
	add_edge(G[7], G[8], 150);
	add_edge(G[8], G[7], 150);
	add_edge(G[8], G[9], 200);
	add_edge(G[9], G[6], 200);
	add_edge(G[9], G[8], 750);
	add_edge(G[9], G[10], 200);
	add_edge(G[9], G[12], 1000);
	add_edge(G[10], G[9], 200);
	add_edge(G[10], G[11], 400);
	add_edge(G[11], G[10], 400);
	add_edge(G[11], G[12], 300);
	add_edge(G[12], G[9], 1000);
	add_edge(G[12], G[11], 300);
	add_edge(G[12], G[13], 100);
	add_edge(G[12], G[0], 300);
	add_edge(G[13], G[12], 100);
	add_edge(G[13], G[14], 100);
	add_edge(G[14], G[13], 100);
	add_edge(G[14], G[0], 100);

}

// 그래프 전역 변수 초기화
void var_init() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			arr_city[i][j] = '\0';
		}
	}
	for (int i = 0; i < 15; i++) {
		stack[i] = '0';
	}
	for (int i = 0; i < 15; i++)
		Visited[i] = 0;
	r = 0;
	top = -1;
}

void swap(char** arr_city, int a, int b) {
	char temp[20];
	strcpy(temp, arr_city[a]);
	strcpy(arr_city[a], arr_city[b]);
	strcpy(arr_city[b], temp);
}

//비행경로 환승 수 오름차순 정렬
void route_sorting() {
	char temp[20];
		for (int k = 0; k < r-1; k++) {
			int min = k;
			for (int i = k; i < r; i++) {
				if (strlen(arr_city[min]) > strlen(arr_city[i])) min = i;
			}
			strcpy(temp, arr_city[min]);
			strcpy(arr_city[min], arr_city[k]);
			strcpy(arr_city[k], temp);
		}
}
