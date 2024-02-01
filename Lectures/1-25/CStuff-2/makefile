CC = gcc

EXECUTABLES = \
       bin/endian \
       bin/p3 \
       bin/p4 \
       bin/p5 \
       bin/p5a \
       bin/p8 \
       bin/p9 \
       bin/pa \
       bin/pc \
       bin/pd \
       bin/pm \
       bin/click

all: $(EXECUTABLES)

clean:
	rm -f a.out bin/*

bin/endian: src/endian.c
	$(CC) -o bin/endian src/endian.c

bin/p3: src/p3.c
	$(CC) -o bin/p3 src/p3.c

bin/p4: src/p4.c
	$(CC) -o bin/p4 src/p4.c

bin/p5: src/p5.c
	$(CC) -o bin/p5 src/p5.c

bin/p5a: src/p5a.c
	$(CC) -o bin/p5a src/p5a.c

bin/p8: src/p8.c
	$(CC) -o bin/p8 src/p8.c

bin/p9: src/p9.c
	$(CC) -o bin/p9 src/p9.c

bin/pa: src/pa.c
	$(CC) -o bin/pa src/pa.c

bin/pc: src/pc.c
	$(CC) -o bin/pc src/pc.c

bin/pd: src/pd.c
	$(CC) -o bin/pd src/pd.c

bin/pm: src/pm.c
	$(CC) -o bin/pm src/pm.c

bin/click: src/click.c
	$(CC) -o bin/click src/click.c

