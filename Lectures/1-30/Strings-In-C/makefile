CC = gcc
EXECUTABLES = \
        bin/strcat  \
        bin/strcat2  \
        bin/strchr  \
        bin/strchr2  \
        bin/strcpy3  \
        bin/strcpy  \
        bin/strcpy2  \
        bin/strlen  \
        bin/makej  \
        bin/strcat3  \
        bin/strcat4  \
        bin/sscanf1  \
        bin/scanf1  \
        bin/scanf2  \
        bin/scanf3 \

all: $(EXECUTABLES)

clean:
	rm -f core bin/* a.out

bin/strcat: src/strcat.c
	$(CC) -o bin/strcat src/strcat.c

bin/strcat2: src/strcat2.c
	$(CC) -o bin/strcat2 src/strcat2.c

bin/strchr: src/strchr.c
	$(CC) -o bin/strchr src/strchr.c

bin/strchr2: src/strchr2.c
	$(CC) -o bin/strchr2 src/strchr2.c

bin/strcpy3: src/strcpy3.c
	$(CC) -o bin/strcpy3 src/strcpy3.c

bin/strcpy: src/strcpy.c
	$(CC) -o bin/strcpy src/strcpy.c

bin/strcpy2: src/strcpy2.c
	$(CC) -o bin/strcpy2 src/strcpy2.c

bin/strlen: src/strlen.c
	$(CC) -o bin/strlen src/strlen.c

bin/makej: src/makej.cpp
	g++ -o bin/makej src/makej.cpp

bin/strcat3: src/strcat3.c
	$(CC) -o bin/strcat3 src/strcat3.c

bin/strcat4: src/strcat4.c
	$(CC) -o bin/strcat4 src/strcat4.c

bin/sscanf1: src/sscanf1.c
	$(CC) -o bin/sscanf1 src/sscanf1.c

bin/scanf1: src/scanf1.c
	$(CC) -o bin/scanf1 src/scanf1.c

bin/scanf2: src/scanf2.c
	$(CC) -o bin/scanf2 src/scanf2.c

bin/scanf3: src/scanf3.c
	$(CC) -o bin/scanf3 src/scanf3.c

