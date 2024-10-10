ASAN = address,undefined,bounds,alignment,null,shift,signed-integer-overflow,object-size,vla-bound,float-divide-by-zero,return

t: # run tests
	gcc -Wall -fsanitize=$(ASAN) -O1 -I./include -I./test -o ./bin/test ./src/*.c ./test/*.c && ./bin/test

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

clean:
	rm -rf bin/*
