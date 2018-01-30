#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "textrank.h"

#define OUTPUT_LENGTH 3
#define NUMBER_KEYWORDS 5


int main(int argc, char *argv[]) {
  Graph* text_graph = NULL;
  char* command = argv[1];
  char* filename = argv[2];
  scored_sentence* scores;

  if(strcmp(command, "summarise") == 0 || strcmp(command, "summarize") == 0 || strcmp(command, "s") == 0) {
    //Summarising the file
    text_graph = construct_sentence_graph(filename);

    scores = construct_initial_scores(text_graph->n);

    calculate_scores(scores, text_graph);

    qsort(scores, text_graph->n, sizeof(scored_sentence), cmp);

    print_summary(text_graph, scores, OUTPUT_LENGTH);
  }
  else if (strcmp(command, "keywords") == 0 || strcmp(command, "keys") == 0 || strcmp(command, "k") == 0) {
    //Get keywords

    // TODO

    // text_graph = construct_keyword_graph(filename);
    //
    // scores = construct_intial_scores(text_graph->n);
    //
    // qsort(scores, text_graph->n, sizeof(scored_sentence), cmp);
    //
    // print_keywords(text_graph, scores, NUMBER_KEYWORDS):
    fprintf(stderr, "This feature hasn't been completed yet!");
  }
  else {
    fprintf(stderr, "Wrong command! Try summarise or keywords!");
  }

  // See scores here
  // for (i = 0; i < text_graph->n; i++) {
  //   printf("%f - %d\n", scores[i].score, scores[i].sentence);
  // }

  return 0;
}
