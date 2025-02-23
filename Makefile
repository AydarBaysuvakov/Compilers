CFLAGS=-g -O0 -Wall
O_FILES= main.o stack.o list.o syntax.o lex.yy.o node.o

all: analysis clean

analysis: $(O_FILES)
	gcc $(O_FILES) -o analysis $(CFLAGS)

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: ./src/lexer.l
	flex ./src/lexer.l

syntax.o: ./src/syntax.c
	gcc -c ./src/syntax.c

node.o: ./src/node.c
	gcc -c ./src/node.c

list.o: ./src/list.c
	gcc -c ./src/list.c

stack.o: ./src/stack.c
	gcc -c ./src/stack.c

main.o: ./src/main.c
	gcc -c ./src/main.c

clean:
	rm -rf *.o lex.yy.c