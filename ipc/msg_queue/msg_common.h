#ifndef _MSG_COMMON_H
#define _MSG_COMMON_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define MSG_LEN 256
struct msg_buf{
	 int type;
	 char text[MSG_LEN];
	};

int create_msg_queue(char *path);
int delete_msg_queue(int flag);

int send_msg(int msgid, int type , char *msg);
int recv_msg(int msgid, int type, char *msg);

int get_msg_queue_info(int msgid,struct msqid_ds msg_info);


#endif