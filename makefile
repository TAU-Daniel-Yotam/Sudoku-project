CC = gcc
OBJS = main.o Game.o Solver.o MainAux.o Parser.o Exceptions.o List.o GameAux.o stack.o
EXEC = sudoku-console
COMP_FLAG = -ansi -O3 -Wall -Wextra \
-Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
main.o: main.c MainAux.h Game.h Parser.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
Game.o: Game.c Game.h Solver.h List.h GameAux.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
MainAux.o: MainAux.c MainAux.h Exceptions.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
Parser.o: Parser.c Parser.h Exceptions.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
Solver.o: Solver.c Solver.h stack.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
Exceptions.o: Exceptions.c Exceptions.h Game.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
List.o: List.c List.h Exceptions.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
GameAux.o: GameAux.c Exceptions.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
stack.o: stack.c stack.h Exceptions.h
	$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
