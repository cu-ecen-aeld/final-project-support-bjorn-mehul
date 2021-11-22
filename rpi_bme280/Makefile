CROSS_COMPILE=

ifeq ($(CC),)
	CC=$(CROSS_COMPILE)gcc
endif

ifeq ($(CFLAGS),)
	CFLAGS= -g -Wall -Werror
endif

ifeq ($(LDFLAGS),)
	LDFLAGS= 
endif

all: bme_sensor
default: bme_sensor
 
bme280_sensor: linux_userspace.o bme280.o
  $(CROSS_COMPILE)$(CC) $(CFLAGS) -o bme_sensor linux_userspace.o bme280.o $(LDFLAGS)

clean :
	rm -f bme_sensor *.o
