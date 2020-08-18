#FLAGS:= -O0 -Wall -g -fno-stack-protector
FLAGS:= -O0 -Wall -g

all:clean test

SrcFiles=$(wildcard *.c)
ObjFiles=$(patsubst %.c,%.o,$(SrcFiles))

test:$(ObjFiles)
	gcc $(FLAGS) -o test $<
	objdump -D test > test.dis
#main.o:main.c
#	gcc $(FLAGS) -c main.c

%.o:%.c
	gcc $(FLAGS) -c $<

.PHONY:clean all

clean:
	rm -f *.o test *.dis
