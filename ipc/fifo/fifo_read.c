#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main()
{

 printf("this is a fifo read process\n");	
 //创建命名管道
 int ret = mkfifo("fifo", 0666);
 if(ret < 0 && errno != EEXIST ){
     perror("creat mkfifo error\n");
     exit(-1);
 }
 
 //打开命名管道
  int fd = open("fifo",O_RDONLY);
  if(fd < 0){
      printf("open fifo error.\n");
      exit(-1);
  }
  
  int len =0;
  char buff[256]={0};
  //从管道读取数据
  while ((len = read(fd, buff, 256))>0){
     printf("recv msg:%s\n",buff);
  }
  
  close(fd);

}