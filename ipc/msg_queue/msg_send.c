#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>


 struct msgbuf {
             long mtype;       /* message type, must be > 0 */
             char mtext[1];    /* message data */
         };

int main(){
	

	key_t key =ftok("/home/zhaopengfei/ipc/msgqueue",'q');
	if(key<0){
		printf("create key fail\n");
		return -1;
		}
	int msgid = msgget(key,IPC_CREAT);
	if(msgid<0){
	   printf("msgget  error\n");
	   	return -1;
	}
	struct msgbuf msg_send_buf;
  msg_send_buf.mtype =1;
  char text[]="this is test";
  memcpy(  msg_send_buf.mtext,text,strlen(text)+1);
  
  int sendlen = msgsnd(msgid,&msg_send_buf, strlen(text)+1,IPC_NOWAIT);
  if(-1==sendlen){
    printf("send msg error ,errno:%d\n",errno);
    	return -1;
  }
/*
int reval=msgctl(msgid,IPC_RMID,NULL);//删除消息队列
if(reval==-1)
{
    printf("unlink msg queue error\n");
    return -1;
}*/
}
	