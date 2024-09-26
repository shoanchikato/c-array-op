br: build run

run:
	./bin/app

build:
	gcc -Wall -I. -o ./bin/app main.c

lib:
	gcc -Wall -I. -o ./bin/app.o -c main.c

asm:
	gcc -Wall -S -I. -o ./bin/app.s main.c

debug:
	gcc -Wall -g -I. -o ./bin/app main.c


