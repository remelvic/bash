CFLAGS= -Wall -g -O2 -pthread
EXTRA_CFLAGS= #-fsanitize=address -fno-omit-frame-pointer
%.o: %.c
	gcc -c -o $@ $< $(CFLAGS) $(EXTRA_CFLAGS)
all: factory

factory: factory.o
	gcc -o factory factory.c $(CFLAGS) $(EXTRA_CFLAGS)
clean:
	rm -f *.o
	rm factory
	rm osy06.tgz
zip:
	tar czf osy06.tgz Makefile *.[ch]
