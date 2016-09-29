#ifndef FUN_H
#define FUN_H
#include"include/fun.h"
#endif 

#define FIFO_SERVER "./myfifo"

int fifo_open(int fd){
        if((mkfifo(FIFO_SERVER,O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))
                printf("cannot create fifoserver\n");
                 //设置非阻塞标志
	if((fd=open(FIFO_SERVER,O_WRONLY|O_NONBLOCK,0))==-1)
                if(errno==ENXIO)
                        printf("open error; no reading process\n");
	//fd=open(FIFO_SERVER,O_WRONLY,0);//设置阻塞标志
	return fd;
}

int fifo_write(int fd,const char *w_buf){
	int buf_len=strlen(w_buf);
	//memset(w_buf,0,buf_len);
	//char w_buf[4096*2];
	int real_num;
	real_num=write(fd,w_buf,buf_len);
	if(real_num==-1){
		if(errno==EAGAIN)
			printf("write to fifo error; try later\n");
	}else 
		printf("real write num is %d\n",real_num);
	return 0;
}

int fifo_close(int fd){
	close(fd);
	return 0;
}
