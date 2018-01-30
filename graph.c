/* * * * * * *
 * Module for working with weighted graphs
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graph.h"


Vertex* new_vertex(const char* name);

Edge* new_edge(int u, int v, int w);

void free_vertex(Vertex* vertex);


Graph* new_graph(int n) {
	Graph* g = malloc(sizeof (*g));
	assert(g);

	g->n = 0;
	g->size = n;

	g->vertices = malloc(n * sizeof (Vertex*));
	assert(g->vertices);

	return g;
}

Vertex* new_vertex(const char* label) {
	Vertex* v;
	assert(label);

	v = malloc(sizeof (*v));
	assert(v);

	v->label = malloc((1 + strlen(label)) * sizeof (char));
	assert(v->label);
	strcpy(v->label, label);

	v->first_edge = NULL;

	return v;
}

Edge* new_edge(int u, int v, int w) {
	Edge* e = malloc(sizeof (*e));
	assert(e);

	e->u = u;
	e->v = v;
	e->w = w;

	e->next_edge = NULL;

	return e;
}

void free_graph(Graph* graph) {
	if (graph) {
		int i;
		for (i = 0; i < graph->n; i++) {
			free_vertex(graph->vertices[i]);
		}

		free(graph->vertices);
		free(graph);
	}
}

void free_vertex(Vertex* vertex) {
	if (vertex) {
		while (vertex->first_edge) {
			Edge* edge = vertex->first_edge;
			vertex->first_edge = vertex->first_edge->next_edge;
			free(edge);
		}
		free(vertex->label);
		free(vertex);
	}
}

void graph_add_vertex(Graph* graph, const char* name) {
	if (graph->n < graph->size) {
		graph->vertices[graph->n] = new_vertex(name);
		graph->n++;
	} else {
		fprintf(stderr, "hey! adding new vertex to full graph\n");
	}
}

void graph_add_undirected_edge(Graph* graph, int u, int v, float w) {
	graph_add_directed_edge(graph, u, v, w);
	graph_add_directed_edge(graph, v, u, w);
}

void graph_add_directed_edge(Graph* graph, int u, int v, float w) {
	if(u < graph->n && u >= 0 && v < graph->n && v >= 0) {
		Edge* edge = new_edge(u, v, w);
		edge->next_edge = graph->vertices[u]->first_edge;
		graph->vertices[u]->first_edge = edge;
	} else {
		fprintf(stderr, "Those nodes dont exist!\n");
	}
}
