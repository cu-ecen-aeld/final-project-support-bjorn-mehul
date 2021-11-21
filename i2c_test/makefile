CROSS_COMPILE=

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

all: i2c_test
default: i2c_test

i2c_test : i2c_test.o
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -o i2c_test i2c_test.o $(LDFLAGS)

i2c_test.o : i2c_test.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c i2c_test.c $(LDFLAGS)

clean :
	rm -f *.o i2c_test
