CFLAGS= -Wall -g -O2 -pthread
EXTRA_CFLAGS= #-fsanitize=address -fno-omit-frame-pointer
%.o: %.cpp
	g++ -cpp -o $@ $< $(CFLAGS) $(EXTRA_CFLAGS)
all: my_factory3

my_factory3: my_factory3.o
	g++ -o my_factory3 my_factory3.cpp $(CFLAGS) $(EXTRA_CFLAGS)
clean:
	rm -f *.o
	rm factory3
	rm osy06.tgz
zip:
	tar czf osy06.tgz Makefile *.[ch]
