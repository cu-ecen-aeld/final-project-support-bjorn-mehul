CROSS_COMPILE=

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt
endif

all: capture
default: capture

capture: capture.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o capture capture.o $(LDFLAGS)

clean :
	rm -f *.o capture	
	
