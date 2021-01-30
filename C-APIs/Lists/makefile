CC=gcc
CFLAGS=-O2 -W -Wall -pedantic

teste: assert.a except.a memory.a list.a teste.c
	$(CC) $(CFLAGS) -c teste.c 
	$(CC) teste.o list.a memory.a assert.a except.a -o teste

assert.a: assert.c
	$(CC) $(CFLAGS) -c assert.c
	ar rcs assert.a assert.o
	ranlib assert.a

except.a: assert.a except.c
	$(CC) $(CFLAGS) -c except.c
	ar rcs except.a assert.a except.o
	ranlib except.a

memory.a: assert.a except.a checking.c
	$(CC) $(CFLAGS) -c checking.c
	ar rcs memory.a assert.a except.a checking.o
	ranlib memory.a

list.a: assert.a memory.a list.c
	$(CC) $(CFLAGS) -c list.c
	ar rcs list.a assert.a memory.a list.o
	ranlib list.a

.PHONY: clean

clean:
	rm *.o
	rm teste
