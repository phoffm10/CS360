all: f mysort

clean:
	rm -f core *.o f mysort

f: f.o f1.o f2.o
	gcc -g -o f f.o f1.o f2.o

f1.o: f.h f1.c
	gcc -c -g f1.c

f2.o: f.h f2.c
	gcc -c -g f2.c

f.o: f.c
	gcc -c -g f.c

mysort: mysort.o /home/jplank/cs360/objs/libfdr.a
	gcc -g -o mysort mysort.o /home/jplank/cs360/objs/libfdr.a 

mysort.o: mysort.c
	gcc -c -g -I/home/jplank/cs360/include mysort.c
