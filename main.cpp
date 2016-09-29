#include<iostream>
#include<fstream>

extern"C"{
#include "library/include/fun.h"
#include "library/include/config.h"
}

#define buf_size 20
#define PORT "/dev/ttyS0"
using namespace std;

int main(){
	char rec_buf[buf_size];	//缓冲区定义
	int fd_serial=0,fd_pipe=0;//文件描述符定义
	int num_rec;
	
	char szFileName[]="./conf/serial.conf";/*配置文件名*/
	char szSectionName[]="config";/*节名*/  
	char szKeyName[100];/*键名*/    
	char szKeyValue[100];/*键值*/   
	int iRetCode = 0;  
	int iPort = -1;  
	char szHostIp[30];  
	
	int bit_speed;//波特率
	int data_bits;//串口传输数据位数
	int stop_bits;//停止位
	char parity;//奇偶校验
	
	GetConfigIntValue(szFileName,szSectionName,"bit_speed",&bit_speed); 
	GetConfigIntValue(szFileName,szSectionName,"data_bits",&data_bits);
	GetConfigIntValue(szFileName,szSectionName,"stop_bits",&stop_bits);
	GetConfigStringValue(szFileName,szSectionName,"parity",&parity);
	cout<<"bit_speed:"<<bit_speed<<endl;
	cout<<"date_bits:"<<data_bits<<endl;
	cout<<"stop_bits:"<<stop_bits<<endl;
	cout<<"parity:"<<parity<<endl;

	//开启串口,返回文件描述符
	fd_serial=serial_open(fd_serial,PORT);
	
	//打开（创建）命名管道，返回文件描述符
	fd_pipe=fifo_open(fd_pipe);
	
	//初始化串口
	if(serial_init(fd_serial,bit_speed,0,data_bits,stop_bits,parity)==FALSE){
		cout<<"serial init error!"<<endl;
		exit(0);
	} else cout<<"serial init success!"<<endl;
	
	//清空缓冲区为
	memset(rec_buf,0,strlen(rec_buf));
	cout << "status：read from serial_port!" << endl;
	char buffer[buf_size];	
	//循环读取串口，写入管道
	while((num_rec = serial_recv(fd_serial, rec_buf,buf_size))>0){
		if(rec_buf[0] == 'q')	break;
		
		rec_buf[num_rec]='\0';
		
		cout<<rec_buf<<endl;
		protocol(rec_buf);
		if(unprotocol(rec_buf,buffer)!=0){
			continue;
		}
		cout<<buffer<<endl;
		fifo_write(fd_pipe,buffer);
	}
	//cout<<"num_rec:"<<num_rec<<endl;	
	fifo_write(fd_pipe,"quit");
	//关闭串口
	close(fd_serial);
	//关闭命名管道
	close(fd_serial);	
	
	cout << "status：completely!" << endl;
	return TRUE;
}
