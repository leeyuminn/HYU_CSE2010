#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS	256

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

typedef char VtxData;
int adj[MAX_VTXS][MAX_VTXS];
int vsize;
VtxData vdata[MAX_VTXS];

int is_empty_graph() { return (vsize == 0); }
int is_full_graph() { return (vsize >= MAX_VTXS); }

void insert_vertex(VtxData name) {
	if (is_full_graph())
		error("Error: 그래프 정점의 개수 초과\n");
	else
		vdata[vsize++] = name;
}

void insert_edge(int u, int v, int val) {
	adj[u][v] = val;
}

void insert_edge2(int u, int v, int val) {
	adj[u][v] = adj[v][u] = val;
}

void print_graph(char* msg)
{
	int i, j;
	printf("%s", msg);
	printf("%d\n", vsize);
	for (i = 0; i < vsize; i++) {
		printf("%c	", vdata[i]);
		for (j = 0; j < vsize; j++)
			printf(" %3d", adj[i][j]);
		printf("\n");
	}
}

void load_graph(char* filename) {
	int i, j, val, n;
	char str[80];
	FILE* fp = fopen(filename, "r");
	if (fp != NULL) {
		init_graph();
		fscanf(fp, "%d", &n); // vertax의 개수 = n에 받아오기
		for (i = 0; i < n; i++) {
			fscanf(fp, "%s", str);
			insert_vertex(str[0]);
			for (j = 0; j < n; j++) {
				fscanf(fp, "%d", &val);
				if (val != 0)
					insert_edge(i, j, val); //어차피 모든 vertax를 head로 하고 다 돌거라서 insert_edge2가 아님
			}
		}
		fclose(fp);
	}
}

int visited[MAX_VTXS];

void reset_visited()
{
	int i;
	for (i = 0; i < vsize; i++)
		visited[i] = 0;
}

#define MAX_QUEUE_SIZE 100
#define ELement int
#define printf_elem(e)	printf("[%d] ",e)	

Element data[MAX_QUEUE_SIZE];
int front;
int rear;

oid init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }

void enqueue(Element val) {
	if (is_full())
		error("	 큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}

Element dequeue()
{
	if (is_empty())
		error("	 큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}

void BFS(int v)
{
	int w;
	visited[v] = 1;
	printf("%c ", vdata[v]);
	init_queue();
	enqueue(v);
	while (!is_empty()) {
		v = dequeue();
		for (w = 0; w < vsize; w++) {
			if (adj[v][w] != 0 && visited[w] == 0) {
				visited[w] = 1;
				printf("%c ", vdata[w]);
				enqueue(w);
			}
		}
	}
}

int main()
{
	load_graph("graph2.txt");
	reset_visited();
	printf("BFS ==> ");
	BFS(0);
	printf("\n");
}