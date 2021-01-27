#CC=gcc-10
#CFLAGS=-I.
OBJ = nullpointer.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

nullpointer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -rf *.o nullpointer
