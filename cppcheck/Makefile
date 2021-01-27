CC=gcc-10
CFLAGS=-I.
OBJ = nullpointer.o
CPPCHECK=cppcheck
CHECKFLAGS=-q --error-exitcode=1

.PHONY: cppcheck.out clean


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

nullpointer: $(OBJ) cppcheck.out
	$(CC) -o $@ $^ $(CFLAGS)

cppcheck.out:
	$(CPPCHECK) $(CHECKFLAGS) nullpointer.c > $@

clean:
	rm -rf *.o nullpointer


