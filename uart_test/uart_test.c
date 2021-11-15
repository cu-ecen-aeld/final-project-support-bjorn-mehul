#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

int fd1;
int open_port(void)
{
	if ((fd1 = open("/dev/tty01", O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
    {
        perror("open\n");
        return -1;
    }
}

int set_baudrate(void)
{
	struct termios options;
    tcgetattr(fd1, &options);
    if((cfsetispeed(&options, B9600)) == -1)
    {
        perror("Input baud rate\n");
        return -1;
    }
    if((cfsetospeed(&options, B9600)) == -1)
    {
        perror("Output baud rate\n");
        return -1;
    } 

    options.c_cflag |= (CLOCAL | CS8);
    options.c_iflag &= ~(ISTRIP | IXON | INLCR | PARMRK | ICRNL | IGNBRK);
    options.c_oflag = 0;
    options.c_lflag = 0;

    tcsetattr(fd1, TCSAFLUSH, &options);
}
int main(void)
{
    int count;
   
    char tx[20] = "Hello", rx[20];

    printf("Testing uart implementation");
	open_port();
	set_baudrate();
 
 
    printf("Sending: '%s'\n", tx);
    if ((count = write(fd1, &tx, 17)) < 0)
    {
        perror("write\n");
        return -1;
    }

    usleep(100000);

    printf("Receive characters\n");

    if ((count = read(fd1, (void*)rx, 17)) < 0)
    {
        perror("read\n");
        return -1;
    }

    if(count)
    {
        printf("Received-> %s, %d chars", rx, count);
    }

    close(fd1);
    return 0;
}
