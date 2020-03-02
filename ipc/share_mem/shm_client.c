#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <unistd.h>

int main(){
 key_t key = ftok("shm",'c');
 if(key<0){
  printf("get key error, errno:%d\n",errno);
  return -1;
 }	
 
 int shmid=shmget(key,1024,IPC_CREAT|0604);
 if(shmid<0){
 	 printf("shmget error, errno:%d",errno);
 	 return -1;
 	}
 	
 	char *shms = shmat(shmid,0,0);
 	if(shms==NULL){
 	 printf("shmat error, errno:%d",errno);
 	 return -1;
 	}

 	int index=0;
 	while(1){
 		
 		index++;
 		if(index==1000){
 		 break;
 		}
 		
 		printf("get share memory:%s\n",shms);
 		sleep(2);
 	
 	}
 
}