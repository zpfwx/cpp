#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>


 struct msgbuf {
             long mtype;       /* message type, must be > 0 */
             char mtext[256];    /* message data */
         };

int main(){
	
	key_t key =ftok("/home/zhaopengfei/ipc/msgqueue",'q');
	if(key<0){
		printf("create key fail\n");
		return -1;
		}
	
	int fd = msgget(key,IPC_CREAT);
	if(fd<0){
	   printf("msgget  error\n");
	   return -1;
	}
	struct msgbuf msg_recv_buf;

  
  int recvlen = msgrcv(fd,&msg_recv_buf, sizeof(msg_recv_buf),0,IPC_NOWAIT);
  if(-1==recvlen){
    printf("recv msg error, errno:%d\n",errno);
    return -1;
  }
  printf("recv msg:%s\n",msg_recv_buf.mtext);


}