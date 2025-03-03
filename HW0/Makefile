CFLAGS=-g -O0 -Wall
O_FILES= main.o stack.o list.o syntax.o lex.yy.o node.o
TEST_FILES= test.o stack.o list.o syntax.o lex.yy.o node.o

all: analysis clean

analysis: $(O_FILES)
	gcc $(O_FILES) -o analysis $(CFLAGS)

test: $(TEST_FILES)
	gcc $(TEST_FILES) -o test $(CFLAGS)
	rm -rf *.o lex.yy.c

test_all:
	for i in $(shell seq 1 24); do ./test $$i > ./tests/res$$i; done

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: ./src/lexer.l
	flex --header-file=./include/lex.yy.h ./src/lexer.l

syntax.o: ./src/syntax.c ./include/syntax.h
	gcc -c ./src/syntax.c

node.o: ./src/node.c ./include/node.h
	gcc -c ./src/node.c

list.o: ./src/list.c ./include/list.h
	gcc -c ./src/list.c

stack.o: ./src/stack.c ./include/stack.h
	gcc -c ./src/stack.c

main.o: ./src/main.c
	gcc -c ./src/main.c

test.o: ./src/test.c ./include/test.h
	gcc -c ./src/test.c

clean:
	rm -rf *.o lex.yy.c