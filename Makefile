CFLAGS = -Wall -Wextra
PROG = main
SRC = main.c mymemory.c
OBJ = $(SRC:.c=.o)
STATIC_LIB = mymemory.a
DYNAMIC_LIB = mymemory.so

mymemory.o: mymemory.c
	$(CC) $(CFLAGS) -fPIC -c mymemory.c -o mymemory.o

$(STATIC_LIB): mymemory.o
	ar rcs $(STATIC_LIB) mymemory.o

$(DYNAMIC_LIB): mymemory.o
	gcc -shared -o $(DYNAMIC_LIB) mymemory.o

static: $(STATIC_LIB) $(PROG)

dynamic: $(DYNAMIC_LIB) $(PROG)

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ)

run: $(PROG)
	./$(PROG)

clean:
	rm -f *.o *.so *.a $(PROG)