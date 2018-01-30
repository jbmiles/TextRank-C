#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "textrank.h"
#include "graph.h"

//Implementing TextRank for summarisation in C.

int cmp(const void *x, const void *y)
{
  scored_sentence* a = (scored_sentence *)x;
  scored_sentence* b = (scored_sentence *)y;
  if (a->score < b->score) return 1;
  if (a->score > b->score) return  -1;
  return 0;
}

scored_sentence* construct_initial_scores(int n) {
  int i;
  scored_sentence *scores = malloc(n * sizeof(scored_sentence));
  assert(scores);
  for (i = 0; i < n; i++) {
    scores[i].score = 1.0/n;
    scores[i].sentence = i;
  }
  return scores;
}

void print_summary(Graph* g, scored_sentence *scores, int num_sentences) {
  int i;
  
  for (i = 0; i < num_sentences; i++) {
    printf("%s ", g->vertices[scores[i].sentence]->label);
  }
}


Graph* construct_sentence_graph(char *fname) {
  FILE *file = fopen(fname, "r");

  Graph *text_graph = new_graph(MAX_NUM_LINES);
  add_lines_graph(text_graph, file);
  add_edges_sentence_graph(text_graph);

  return text_graph;
}

void add_edges_sentence_graph(Graph *g) {
  //Calculating similarity scores.
  Vertex *v1, *v2;
  char label1[MAX_LINE_LENGTH];
  int i, j;
  double similarity = 0;
  int words_in_both;
  for (i = 0; i < g->n; i++) {
    v1 = g->vertices[i];
    for (j = i+1; j < g->n; j++) {
      strcpy(label1, v1->label);
      words_in_both = 0;
      v2 = g->vertices[j];
      char *word = strtok(label1, " ");
      while (word != NULL) {
        if (strstr(v2->label, word)) {
        // match
        words_in_both++;
        }
        word = strtok(NULL,  " ");
      }
      similarity = words_in_both / (log(count_words(v1->label)) +
                                    log(count_words(v2->label)));
      if (words_in_both != 0) {
        graph_add_undirected_edge(g, i, j, similarity);
      }
    }
  }
}

//Get number of words in sentence.
int count_words(char *string) {
  int i, out = 1;
  for (i=0; i < strlen(string); i++) {
    if (string[i] == ' ') {
      out++;
    }
  }
  return out;
}


//Calculating scores for each node.
void calculate_scores(scored_sentence scores[], Graph* g) {

  int iter_quant = 0, i, convergence_achieved, k, neighbours_sum;
  double rank;

  Edge *neighbour, *neighbour2;
  for (k=0; k < 100; k++) {
    iter_quant++;
    convergence_achieved = 0;
    for (i=0; i<g->n; i++) {
      rank = 1 - D;
      neighbour = g->vertices[i]->first_edge;
      while (neighbour != NULL) {
        neighbours_sum = 0;
        neighbour2 = g->vertices[neighbour->v]->first_edge;
        while (neighbour2 != NULL) {
          neighbours_sum += neighbour2->w;
          neighbour2 = neighbour2->next_edge;
        }
        if (neighbours_sum != 0) {
          rank += (D * scores[neighbour->u].score * neighbour->w) / neighbours_sum;
        }

        if (abs(scores[i].score - rank) <= DELTA) {
          convergence_achieved += 1;
        }
        neighbour = neighbour -> next_edge;
        scores[i].score = rank;
      }
    }

    if (convergence_achieved == g->n) {
      break;
    }

  }
  return;
}


void add_lines_graph(Graph* graph, FILE* file) {
  char line_read[MAX_LINE_LENGTH];
  int line_size = 0;
  char c;

  // Adding each line
  while ((c = getc(file)) && c != EOF) {
    if (c == '.') {
      line_read[line_size] = c;
      c = getc(file);
      if (c == ' ' || c == '\n' || c == EOF) {
        line_read[++line_size] = '\0';
        graph_add_vertex(graph, line_read);
        line_size = 0;
      }
      else if (c == EOF) {
        line_read[line_size] = c;
        line_size++;
      }
    }
    else if (c == '\n') {
      if (line_size != 0) {
        line_read[line_size] = ' ';
        line_size++;
      }
    }
    else {
      line_read[line_size] = c;
      line_size++;
    }
  }
}
