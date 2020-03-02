#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

int create_sem(key_t key, int value) {
	int semid = semget(key,1, IPC_CREAT|0666);
	if(semid < 0) {
		printf("create sem error, error no:%d\n",errno);
		return -1;
	}
	union semun sem;
	sem.val = value;

	semctl(semid,0,SETVAL,sem);
	return semid;
}
int sem_p(int semid) {
	struct sembuf sops= {
		0,-1,IPC_NOWAIT
	}
	;
	return  semop(semid,&sops,1);
}
int sem_v(int semid) {
	struct sembuf sops= {
		0,1,IPC_NOWAIT
	}
	;
	return  semop(semid,&sops,1);
}
int get_sem_value(int semid) {
	union semun sem;
	return    semctl(semid,0,GETVAL,sem);
}
int del_sem(int semid) {
	//union semun sem;
	union semun sem_union;
	sem_union.val=0;
	return    semctl(semid,0,IPC_RMID,sem_union);
}
int main() {
	key_t key = ftok("/ipc/sem",'a');
	int semid = create_sem(key,0);
	
	pid_t  pid = fork();
	if(pid < 0){
	   printf("creat fork error\n");
	   return -1;
	}else if(pid==0){//子进程
		sem_p(semid);
		printf("child process get sem\n ");
		sleep(1);
		printf("Process child: pid=%d\n", getpid());
		sem_v(semid);
	
	}else{//父进程
			sem_p(semid);
			sleep(4);
			printf("parent  process get sem\n ");
			printf("Process parent: pid=%d\n", getpid());
			printf("hello,world\n");
			sem_v(semid);
	
	}

	int value = get_sem_value(semid);
	printf("sem value:%d\n",value);
	del_sem(semid);
	
	return 0;
}
