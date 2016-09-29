#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<stdlib.h>
#include<stdio.h> 
#include<sys/types.h>  
#include<sys/stat.h>
#include<errno.h>      
#include<string.h>

#define FALSE -1
#define TRUE 0
//#define PORT "/dev/ttyS0"

int serial_open(int fd,const char *port);	//串口打开函数

int serial_init(int fd, int speed,int flow_ctrlint ,int databits,int stopbits,char parity);

int serial_recv(int fd, char *rec_buf,int data_len);

int fifo_open(int fd);

int fifo_write(int fd,const char* w_buf);

int fifo_close(int fd);

void protocol(char *raw_message);

int unprotocol(char *raw_message,char *new_message);

