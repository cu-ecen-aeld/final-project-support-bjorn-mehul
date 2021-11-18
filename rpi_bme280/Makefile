CROSS_COMPILE=

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS= -lgpiod -pthread -lrt
endif

all: main 
default: main

bme280 : bme280.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o bme280 bme280.o $(LDFLAGS)
	
bme280.o : bme280.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c bme280.c $(LDFLAGS)

main : main.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o main main.o $(LDFLAGS)
		
main.o : main.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c main.c $(LDFLAGS)
	
main : main.o bme.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o main main.o $(LDFLAGS)
	
clean :
	rm -f main *.o
