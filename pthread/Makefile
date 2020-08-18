FLAGS:= -O0 -Wall -g -lpthread -fno-stack-protector 
#FLAGS:= -O0 -Wall -g -lpthread

all: clean test

SrcFiles=$(wildcard *.c)
ObjFiles=$(patsubst %.c,%.o,$(SrcFiles))

test:$(ObjFiles)
	gcc -o $@ $< $(FLAGS)
	objdump -D test > test.dis
#main.o:main.c
#	gcc $(FLAGS) -c main.c

%.o:%.c
	gcc -c $< -o $@ $(FLAGS)

.PHONY:clean all

clean:
	rm -f *.o test *.dis
