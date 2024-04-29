all: bonding-example-1 bonding-example-2 bonding

clean:
	rm -f bonding bonding-example-1 bonding-example-2

INCLUDE = -I/home/jplank/cs360/include
LIBFDR = /home/jplank/cs360/objs/libfdr.a 

bonding: bonding.c bonding.h bonding-driver.c
	gcc -o bonding $(INCLUDE) bonding.c bonding-driver.c $(LIBFDR) -lpthread
	
bonding-example-1: bonding-example-1.c bonding.h bonding-driver.c
	gcc -o bonding-example-1 $(INCLUDE) bonding-example-1.c bonding-driver.c $(LIBFDR) -lpthread
	
bonding-example-2: bonding-example-2.c bonding.h bonding-driver.c
	gcc -o bonding-example-2 $(INCLUDE) bonding-example-2.c bonding-driver.c $(LIBFDR) -lpthread
	
