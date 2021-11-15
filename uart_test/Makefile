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

all: uart_test
default: uart_test

uart_test : uart_test.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o uart_test uart_test.o $(LDFLAGS)
	
uart_test.o : uart_test.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c uart_test.c $(LDFLAGS)
clean :
	rm -f uart_test *.o
