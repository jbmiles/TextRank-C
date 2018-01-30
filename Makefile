
CC     = gcc
CFLAGS = -Wall
EXE    = TextRank
OBJ    = main.o graph.o textrank.o

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: graph.h textrank.h
graph.o: graph.h
textrank.o: textrank.h graph.h

clean:
	rm -f $(OBJ) $(EXE)
