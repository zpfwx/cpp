#include  "msg_common.h"

int create_msg_queue(char *path){
	key_t key = ftok(path,'q');
	if(key<0){
		printf("create key fail, errno:%d\n", errno);
		return -1;
	}
	
	int msgid = msgget(key,IPC_CREAT); 
	if( msgid < 0){
	   printf("msgget  error, errno:%d\n",errno);
	   return -1;
	}
	return msgid;
}
int delete_msg_queue(int msgid){
	int reval=msgctl(msgid,IPC_RMID,NULL);//删除消息队列
	if(reval==-1)
	{
	    printf("unlink msg queue error\n");
	    return -1;
	}
	return reval;
}

int send_msg(int msgid, int type , char *msg){
  struct  msg_buf msg_send_buf;
  msg_send_buf.type = type;
  memcpy(msg_send_buf.text, msg, strlen(msg));
  int ret = msgsnd(msgid,&msg_send_buf, strlen(msg)+1,0);
  if(-1==ret){
     printf("send msg error ,errno:%d\n",errno);
     return -1;
  }
  return ret;
}

int recv_msg(int msgid, int type, char *msg){
	struct msg_buf msg_recv_buf;
  int len = msgrcv(msgid,&msg_recv_buf, sizeof(msg_recv_buf),0,0);
  if(-1==len){
    printf("recv msg error, errno:%d\n",errno);
    return -1;
  }
  strcpy(msg, msg_recv_buf.text);
  return  len;
}

int get_msg_queue_info(int msgid,struct msqid_ds msg_info){
	int reval=msgctl(msgid,IPC_STAT,&msg_info);
	if(reval==-1)
	{
	  printf("get_msg_queue_info error\n");
	  return -1;
	}
	
	printf("\n");
	printf("current number of bytes on queue is %d\n",msg_info.msg_cbytes);
	printf("number of messages in queue is %d\n",msg_info.msg_qnum);
	printf("max number of bytes on queue is %d\n",msg_info.msg_qbytes);
	printf("pid of last msgsnd is %d\n",msg_info.msg_lspid);
	printf("pid of last msgrcv is %d\n",msg_info.msg_lrpid);
	printf("last msgsnd time is %s", ctime(&(msg_info.msg_stime)));
	printf("last msgrcv time is %s", ctime(&(msg_info.msg_rtime)));
	printf("last change time is %s", ctime(&(msg_info.msg_ctime)));
	printf("msg uid is %d\n",msg_info.msg_perm.uid);
	printf("msg gid is %d\n",msg_info.msg_perm.gid);
}