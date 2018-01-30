/*

A module for working with weighted graphs.

*/

#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph Graph;
typedef struct vertex Vertex;
typedef struct edge Edge;

struct graph {
	int n, size;
	Vertex** vertices;
};

struct vertex {
	char* label;
	Edge* first_edge;
};

struct edge {
	int u, v;
	float w;
	Edge* next_edge;
};

Graph* new_graph(int n);

void free_graph(Graph* graph);


void graph_add_vertex(Graph* graph, const char* name);

void graph_add_undirected_edge(Graph* graph, int u, int v, float w);

void graph_add_directed_edge(Graph* graph, int u, int v, float w);

#endif
