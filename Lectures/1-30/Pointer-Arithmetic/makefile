EXECUTABLES = bin/quiz bin/iptr bin/sptr bin/cptr bin/dptr

all: $(EXECUTABLES)

clean:
	rm -f core bin/* a.out

bin/iptr: src/iptr.c
	$(CC) $(CFLAGS) -o bin/iptr src/iptr.c

bin/sptr: src/sptr.c
	$(CC) $(CFLAGS) -o bin/sptr src/sptr.c

bin/dptr: src/dptr.c
	$(CC) $(CFLAGS) -o bin/dptr src/dptr.c

bin/cptr: src/cptr.c
	$(CC) $(CFLAGS) -o bin/cptr src/cptr.c

bin/quiz: src/quiz.c
	$(CC) $(CFLAGS) -o bin/quiz src/quiz.c

