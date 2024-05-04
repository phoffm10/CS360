CC = gcc 
INCLUDES = -I/home/jplank/cs360/include -pthread
CFLAGS = $(INCLUDES)
LIBDIR = /home/jplank/cs360/lib
LIBS = $(LIBDIR)/libfdr.a $(LIBDIR)/sockettome.o

EXECUTABLES = chat_server

all: $(EXECUTABLES)

chat_server: chat_server.c
	$(CC) $(CFLAGS) -g -o chat_server chat_server.c $(LIBS)

clean:
	rm -f $(EXECUTABLES)
