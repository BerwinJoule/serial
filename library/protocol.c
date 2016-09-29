#ifndef FUN_H
#define FUN_H
#include"include/fun.h"
#endif
void byte_shift(int shift_num,char *raw_message);
void protocol(char *raw_message){
	char info_type;
	char num;
	//if((raw_message[0]>='0') &&(raw_message[0] <= '9')){
		num=(char)strlen(raw_message);
		byte_shift(2,raw_message);
		raw_message[0]='a';
		raw_message[1]=num;
		//raw_message[2]=num;
	//}else if((raw_message[0]>='a')&&(raw_message[0]<='z')){
	//	num=(char)strlen(raw_message);
	//	byte_shift(3,raw_message);
	//	raw_message[0]='a';
        //      raw_message[1]='c';
        //      raw_message[2]=num;
	//}
	
}

int unprotocol(char *raw_message,char *new_message){
	char i=0;
	if(raw_message[0]=='a'){
		char num=raw_message[1];
		for(i=0;i<=num;i++){
			new_message[i]=raw_message[i+2];
		}
		return 0;
	}else return -1;
	
}

void byte_shift(int shift_num,char *raw_message){
	int i;int num=strlen(raw_message);
	for(i=0;i<shift_num;i++){	
		//printf("%d",num);
		char *pnum;pnum=raw_message+num+shift_num;
		for(;pnum!=raw_message;pnum--){
			*pnum=*(pnum-1);
		}
		num++;	
	}

}
