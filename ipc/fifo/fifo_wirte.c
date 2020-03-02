#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
   printf("this a fifo write process\n");
   int fd=0;
   //打开管道
   fd = open("fifo",O_WRONLY);
   if(fd<0){
      printf("open fifo error.\n");
      exit(-1);
   }

   char buff[64]={0};
   for(int i=0;i<10 ;i++){
   
   	   int  n=sprintf(buff,"send msg:%i",i);
   	   printf("send msg: %s\n", buff); // 打印
       //打开管道
   	   int len = write(fd,buff,strlen(buff)+1);
   	   if(len<0){
   	     perror("write mkfifo error");
   	      exit(-1);
   	    }
   	
     	sleep(1);
   	}
   	return 0;
}