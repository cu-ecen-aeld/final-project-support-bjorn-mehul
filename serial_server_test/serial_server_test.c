/* 
 * Fetch sensor data on UART 
 * Sends & Receives via the serial port (/dev/tty0)
 * server code - TCP Server client communication - testing for local server-client
 */
#include <stdio.h>    
#include <string.h>   
#include <unistd.h>  
#include <fcntl.h>    
#include <errno.h>    
#include <termios.h>
#include<dirent.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h> 
#include<sys/time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<time.h>



#define PORTNO 9000

int initport(int fd);
int writeport(int fd, char * buff);
int readport(int fd, char * result);
int getbaud(int fd);
int fd;
char rbuff[40];
char t[10], p[10], rh[10];
int portno;

//Creating thread for Serving Client request 
void * thread_1(void * p) 
{
  struct sockaddr_in v, v1;
  int sfd, len, nsfd, op;
  char s[18] = "Invalid Option..";
  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd < 0) {
    perror("socket");
    return NULL;
  }
   
  v.sin_family = AF_INET;
  v.sin_port = htons(portno);
  v.sin_addr.s_addr = inet_addr("0.0.0.0");
  len = sizeof(v);
  if (bind(sfd, (struct sockaddr * ) & v, len) < 0) {
    perror("bind");
    return NULL;
  }
  
  if (listen(sfd, 5) < 0) {
    perror("listen");
    return NULL;
  }
  
  nsfd = accept(sfd, (struct sockaddr * ) & v1, & len);
   
  while (1) 
  {
    read(nsfd, & op, sizeof(op));
    if (op == 1)
      write(nsfd, t, strlen(t) + 1);
    else if (op == 2)
      write(nsfd, p, strlen(p) + 1);
    else if (op == 3)
      write(nsfd, rh, strlen(rh) + 1);
    else
      write(nsfd, s, strlen(s) + 1);
  }
  return NULL;
}
 
int initport(int fd) 
{
  struct termios options;
  // Get the current options for the port...
  tcgetattr(fd, & options);
  // Set the baud rates to 9600...
  cfsetispeed( & options, B9600);
  cfsetospeed( & options, B9600);
  // Enable the receiver and set local mode...
  options.c_cflag |= (CLOCAL | CREAD);
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  // Set the new options for the port...
  tcsetattr(fd, TCSANOW, & options);
  return 1;
}
////////////////////////////////////////////////////////////////////////////////
int readport(int fd, char * result) {
  int iIn = read(fd, result, 254);
  result[iIn - 1] = 0x00;
  if (iIn < 0) {
    if (errno == EAGAIN) {
      printf("SERIAL EAGAIN ERROR\n");
      return 0;
    } else {
      printf("SERIAL read error %d %s\n", errno, strerror(errno));
      return 0;
    }
  }
  return 1;
}
 
int main(void)
{
  portno = PORTNO;
  pthread_t t1;
  fd = open("/dev/tty1", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1) 
  {
    perror("open_port: Unable to open /dev/tty1 - ");     
    return 1;
  } else {
    fcntl(fd, F_SETFL, 0);
  }
  initport(fd);
  usleep(500000);
  //fcntl(fd, F_SETFL, FNDELAY); // don't block serial read
  fcntl(fd, F_SETFL, 0); // block serial read
   
  pthread_create( & t1, NULL, thread_1, NULL);
   
  while (1)
  {
    if (!readport(fd, rbuff))
	{
      printf("read failed\n");
      close(fd);
      return 1;
    }
    strcpy(t, rbuff);
    t[9] = '\0';
    strcpy(p, rbuff + 10);
    p[9] = '\0';
    strcpy(rh, rbuff + 20);
    rh[9] = '\0';
    printf("Sensor data - \n");
    printf("%s\n", t);
    printf("%s\n", p);
    printf("%s\n", rh);
    sleep(1);
    system("clear");
  }
  close(fd);
  return 0;
} 
