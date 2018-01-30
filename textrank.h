#ifndef TEXTRANK_H
#define TEXTRANK_H

#include "graph.h"

#define N 2
#define MAX_LINE_LENGTH 2000
#define MAX_NUM_LINES 1000
#define D 0.85
#define DELTA 0.0001

typedef struct {
  double score;
  int sentence;
} scored_sentence;


Graph* construct_sentence_graph(char *fname);

void print_summary(Graph *g, scored_sentence *scores, int num_sentences);

scored_sentence* construct_initial_scores(int n);

void add_lines_graph(Graph* graph, FILE* file);

void add_edges_sentence_graph(Graph *g);

int count_words(char *string);

void calculate_scores(scored_sentence scores[], Graph* g);

int cmp(const void *x, const void *y);


#endif
