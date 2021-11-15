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

all: serial_server_test
default: serial_server_test

serial_server_test : serial_server_test.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o serial_server_test serial_server_test.o $(LDFLAGS)
	
serial_server_test.o : serial_server_test.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c serial_server_test.c $(LDFLAGS)
clean :
	rm -f serial_server_test *.o
