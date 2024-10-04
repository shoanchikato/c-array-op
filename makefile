t: # run tests
	gcc -Wall -I./include -o ./bin/test ./src/*.c ./test/test.c && ./bin/test

run:
	gcc -Wall -I./include -o ./bin/app main.c && ./bin/app

build:
	gcc -Wall -I./include -o ./bin/app main.c

lib:
	gcc -Wall -I./include -o ./bin/array_op.o -c ./include/array_op.h

asm:
	gcc -Wall -S -I./include -o ./bin/array_op.s main.c

debug:
	gcc -Wall -g -I./include -o ./bin/app main.c && ./bin/app
