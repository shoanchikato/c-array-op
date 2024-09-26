t: # run tests
	gcc -Wall -I./include -o ./bin/test ./test/test.c && ./bin/test

lib:
	gcc -Wall -I./include -o ./bin/app.o -c array_op.h


asm:
	gcc -Wall -S -I./include -o ./bin/app.s array_op.h

debug:
	gcc -Wall -g -I./include -o ./bin/app array_op.h


