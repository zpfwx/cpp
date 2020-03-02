#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int agrc, char **argv){
	
	int fds[2]; //fds[0]read
	pid_t pid;
	
	int ret = pipe(fds);
	if( ret < 0 ){
	   printf("create pipe error\n");
	   exit(-1);
	}
	
	printf("main fork id:%d\n",getpid());
  ret = fork();
  if(ret<0)
	{
	   printf("fork error!\n");
	   exit(-1) ; 
	}
	else if(ret > 0) 	//������
	{
	
	  //�رն���
		close(fds[0]);
		printf(" parent fork id:%d\n",getpid());
		//д����
	  char data[]="hello world\n";
		write(fds[1],data, strlen(data)+1);
		
	}
	else //�ӽ���
	{
		//�ر�д
		close(fds[1]); 
		char buff[20]={0};
		//������
		read(fds[0],buff, 20);
		printf("child fork read:%s",buff);
	}
	
	return 0;

}

