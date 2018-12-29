all:
	@gcc -pedantic -Wall src/*.c -o contextFree

clean: all
	@rm -f *.o

test: clean
	@./contextFree