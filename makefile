ASAN = address,undefined,bounds,alignment,null,shift,signed-integer-overflow,object-size,vla-bound,float-divide-by-zero,return

SRC = ./src/*.c
OBJ = ./bin/libarray_op.o
LIB = ./bin/libarray_op.a

.PHONY: test
test: # run tests
	mkdir -p bin
	gcc -Wall -fsanitize=$(ASAN) -O1 -I./include -I./test -o ./bin/test ./test/*.c $(SRC) && ./bin/test

.PHONY: lib
lib:
	mkdir -p bin
	gcc -Wall -I./include -c -o $(OBJ) $(SRC) && ar rcs $(LIB) $(OBJ)

.PHONY: clean
clean:
	rm -rf bin
