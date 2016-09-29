# serial
基于串口（可配置）的通信，从主机接收数据，写入有名管道

serial	//主文件夹
   |——library//函数库源代码文件夹
   |           
   |——conf	//配置文件夹
   |           |——serial.conf
   |——main.cpp	//主程序源码
   |——makefile	//make文件
   |——myfifo	//通信管道
   |——out//编译输出文件夹
                |——serial//二进制可执行文件        

library    //函数库文件夹
    |——include  //头文件文件夹
    |              |——fun.h	//主要功能头文件
    |              |——config.c	//配置功能头文件
    |——serial.c	//串口通信函数
    |——pipe.c	//管道通信函数
    |——config.c	//配置文件读取函数
    |——protocol.c	//协议配置函数
    |——makefile	//make文件
