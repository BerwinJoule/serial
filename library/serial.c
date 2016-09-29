#ifndef FUN_H
#define FUN_H
#include"include/fun.h"
#endif

/** 
 * open_port 
 * @param  fd 文件描述符
 * @param  port 想要打开的串口设备
 * @return  返回-1为打开失败 
 */  
int serial_open(int fd,const char* port){
  
	fd = open(port, O_RDWR|O_NOCTTY|O_NDELAY);   
	if (FALSE == fd)  
	{   
		perror("Can't Open Serial Port");   
		return FALSE;   
	}
	//恢复串口为阻塞状态
	if(fcntl(fd, F_SETFL, 0)<0){   
		printf("fcntl failed!\n");
		return FALSE;
	}
	else	printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));   
	/*测试是否为终端设备*/   
	if(isatty(STDIN_FILENO)==0)	printf("standard input is not a terminal device\n");   
     	else	printf("isatty success!\n");   
     	
	printf("open fd=%d\n",fd);   
     	return fd;   
}

int serial_set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)
{ 
    
    	int   i;
	struct termios options; 

	if(tcgetattr( fd,&options)  !=  0){  
	    perror("SetupSerial 1");     
	    return(FALSE);  
    	} 

	switch( speed )   
        {   
                case 2400:   
                cfsetispeed(&options, B2400);   
                cfsetospeed(&options, B2400);   
                break;   
                case 4800:   
                cfsetispeed(&options, B4800);   
                cfsetospeed(&options, B4800);   
                break;   
                case 9600:   
                cfsetispeed(&options, B9600);   
                cfsetospeed(&options, B9600);   
                break;   
                case 115200:   
                cfsetispeed(&options, B115200);   
                cfsetospeed(&options, B115200);   
                break;   
                case 460800:   
                cfsetispeed(&options, B460800);   
                cfsetospeed(&options, B460800);   
                break;   
                default:   
                cfsetispeed(&options, B9600);   
                cfsetospeed(&options, B9600);   
                break;   
         }   

	options.c_cflag |= CLOCAL;
	options.c_cflag |= CREAD;
	switch(flow_ctrl){
		case 0 :
			options.c_cflag &= ~CRTSCTS;
			break;	
    		case 1 :
    			options.c_cflag |= CRTSCTS;
    			break;
    		case 2 :
    			options.c_cflag |= IXON | IXOFF | IXANY;
    			break;
	}
    
	options.c_cflag &= ~CSIZE; 
	switch (databits){   
		case 5 :
    			options.c_cflag |= CS5;
    			break;
    		case 6	:
    			options.c_cflag |= CS6;
    			break;
    		case 7	:     
        		options.c_cflag |= CS7; 
        		break;
    		case 8:     
        		options.c_cflag |= CS8;
        		break;   
       		default:    
        		fprintf(stderr,"Unsupported data size\n"); 
        		return (FALSE);
	}
	switch (parity) {   
		case 'n':
    		case 'N': 
        		options.c_cflag &= ~PARENB;  
        		options.c_iflag &= ~INPCK;     
        		break;  
    		case 'o':   
    		case 'O':    
        		options.c_cflag |= (PARODD | PARENB);  
        		options.c_iflag |= INPCK;              
        		break;  
    		case 'e':  
    		case 'E':   
        		options.c_cflag |= PARENB;        
        		options.c_cflag &= ~PARODD;        
        		options.c_iflag |= INPCK;       
        		break;
    		case 's': 
    		case 'S': 
        		options.c_cflag &= ~PARENB;
        		options.c_cflag &= ~CSTOPB;
        		break;  
        	default:   
        		fprintf(stderr,"Unsupported parity\n");    
        		return (FALSE); 
	}  
	switch (stopbits){   
		case 1:    
			options.c_cflag &= ~CSTOPB;  
        		break;  
    		case 2:    
        		options.c_cflag |= CSTOPB;  
       			break;
    		default:    
         		fprintf(stderr,"Unsupported stop bits\n");  
         		return (FALSE); 
	} 
    
    	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~ (ICANON | ECHO | ECHOE | ISIG); 
	
	options.c_cc[VTIME] = 1;    
	options.c_cc[VMIN] = 1; 
	
	tcflush(fd,TCIFLUSH);
	
	if(tcsetattr(fd,TCSANOW,&options) != 0){ 
		perror("com set error!\n");   
    		return (FALSE);  
	} 
	return (TRUE);  
}

int serial_init(int fd, int speed,int flow_ctrlint ,int databits,int stopbits,char parity)
{
	if (FALSE == serial_set(fd,speed,flow_ctrlint,databits,stopbits,parity)) {    		
		return FALSE;
    	} else {
   		return  TRUE;
   	}
}

int serial_recv(int fd, char *rec_buf,int data_len)
{
    	int len,fs_sel;
    	fd_set fs_read;
   
    	struct timeval time;
   
    	FD_ZERO(&fs_read);
    	FD_SET(fd,&fs_read);
   
    	time.tv_sec = 60;
    	time.tv_usec = 0;
   
    	//使用select实现串口的多路通信
    	fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);
    	if(fs_sel)
       	{
		len = read(fd,rec_buf,data_len);
             	return len;
       	}
    	else
       	{
		return FALSE;
       	}     
}
/*
int serial_recv(int fd, char *rec_buf,int data_len){
	int len;
	len = read(fd,rec_buf,data_len);
	return len;
}
*/
