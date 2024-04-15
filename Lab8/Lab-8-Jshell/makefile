CC = gcc

INCLUDES = -I/home/jplank/cs360/include
LIBDIR = /home/jplank/cs360/lib

CFLAGS = $(INCLUDES)
LIBS = $(LIBDIR)/libfdr.a

EXECUTABLES = bin/jshell

all: $(EXECUTABLES)

testers: bin/cattostde \
         bin/strays \
         bin/strays-files \
         bin/strays-fsleep \
         bin/strays-sleep \

bin/jshell: src/jshell.c
	$(CC) $(CFLAGS) -o bin/jshell src/jshell.c $(LIBS)

bin/strays: src/strays.c
	$(CC) -o bin/strays src/strays.c

bin/cattostde: src/cattostde.c
	$(CC) -o bin/cattostde src/cattostde.c

bin/strays-files: src/strays-files.c
	$(CC) -o bin/strays-files src/strays-files.c

bin/strays-fsleep: src/strays-fsleep.c
	$(CC) -o bin/strays-fsleep src/strays-fsleep.c

bin/strays-sleep: src/strays-sleep.c
	$(CC) -o bin/strays-sleep src/strays-sleep.c
