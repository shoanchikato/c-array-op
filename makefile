t: # run tests
	gcc -Wall -I./includes -o ./bin/test ./test/test.c && ./bin/test

lib:
	gcc -Wall -I./includes -o ./bin/app.o -c array_op.h

asm:
	gcc -Wall -S -I./includes -o ./bin/app.s array_op.h

debug:
	gcc -Wall -g -I./includes -o ./bin/app array_op.h


