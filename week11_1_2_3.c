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

void init_graph() {
	int i, j;
	vsize = 0;
	for (i = 0; i < MAX_VTXS; i++)
		for (j = 0; j < MAX_VTXS; j++) 
			adj[i][j] = 0;
}

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
	for(i = 0; i < vsize; i++) {
		printf("%c	", vdata[i]);
		for (j = 0; j < vsize; j++) 
			printf(" %3d", adj[i][j]);
		printf("\n");
	}
}

void main() {
	int i;
	init_graph();
	for (i = 0; i < 4; i++)
		insert_vertex('A' + i);

	insert_edge2(0, 1, 1); 
	insert_edge2(0, 3, 1); 
	insert_edge2(1, 2, 1); 
	insert_edge2(1, 3, 1); 
	insert_edge2(2, 3, 1);
	print_graph("그래프(인접행렬)\n");
}

//lab2
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


void main() {
	load_graph("graph.txt");
	print_graph(stdout, "그래프(인접행렬)\n");
}

//lab3
#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS	256

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

typedef struct GraphNode {
	int id; // 정점의 id 
	struct GraphNode* link; // 다음 노드의 포인터
} GNode;

typedef char VtxData;
int vsize;
VtxData vdata[MAX_VTXS]; 
GNode* adj[MAX_VTXS];

int is_empty_graph() { return (vsize == 0); }
int is_full_graph() { return (vsize >= MAX_VTXS); } 

void init_graph() {
	int i;
	vsize = 0;
	for (i = 0; i < MAX_VTXS; i++)
		adj[i] = NULL;
}

void reset_graph() {
	int i;
	GNode* n;
	for (i = 0; i < vsize; i++) {
		while (adj[i] != NULL) {
			n = adj[i];
			adj[i] = n->link;
			free(n);
		}
	}
	vsize = 0;
}

void insert_vertex(char name) {
	if (is_full_graph())
		error("Error: 그래프 정점의 개수 초과\n");
	else
		vdata[vsize++] = name;
}

void insert_edge(int u, int v) {
	GNode* n = (GNode*)malloc(sizeof(GNode));
	n->link = adj[u];
	n->id = v;
	adj[u] = n;
}

void print_graph(char* msg)
{
	int i;
	GNode* v;
	printf("%s%d\n", msg, vsize);
	for (i = 0; i < vsize; i++) {
		printf("%c	", vdata[i]);

		for (v = adj[i]; v != NULL; v = v->link)
			printf("	%c", vdata[v->id]);
		printf("\n");
	}

}

void load_graph(char* filename)
{
	int i, j, val, n;
	char str[80];
	FILE* fp = fopen(filename, "r"); //r운 읽겠다!
	if (fp != NULL) {
		init_graph();
		fscanf(fp, "%d", &n); // vertax의 개수 = n에 받아오기
		for (i = 0; i < n; i++) {
			fscanf(fp, "%s", str);
			insert_vertex(str[0]);
			for (j = 0; j < n; j++) {
				fscanf(fp, "%d", &val);
				if (val != 0)
					insert_edge(i, j); //어차피 모든 vertax를 head로 하고 다 돌거라서 insert_edge2가 아님
			}
		}
		fclose(fp);
	}

}

void main() {
	load_graph("graph.txt"); 
	print_graph("그래프(인접리스트)\n");
	reset_graph();
}