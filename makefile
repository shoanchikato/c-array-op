lib:
	gcc -Wall -I. -o ./bin/app.o -c main.c

t: # run tests
	gcc -Wall -I. -o ./bin/test test.c && ./bin/test

asm:
	gcc -Wall -S -I. -o ./bin/app.s main.c

debug:
	gcc -Wall -g -I. -o ./bin/app main.


