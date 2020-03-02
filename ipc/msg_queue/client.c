#include "msg_common.h"

int client(){
 int msgid =	create_msg_queue("./msgqueue");
 char input_buf[256]={0};
 while(1){
 	  printf("input msg:");
 	  scanf("%s", input_buf);
 	  printf("send msg:%s\n",input_buf);
 	  
 	  int ret = send_msg(msgid,1, input_buf);
 	  if(ret<0){
 	    printf("send msg error\n");
 	    continue;	
 	  }
 	  ret = recv_msg(msgid,1,input_buf);
 	  if(ret<0){
 	     printf("recv msg error\n");
 	    continue;	
 	  }
 	  
 	  printf("recv msg:%s\n", input_buf);
 	  if(strcmp("e",input_buf)==0){
 	    break;
 	  }
 	}

}

int main(){
	  client();
	}