/*************************************************************************
	> File Name: sem.c
	> Author: 
	> Mail: 
	> Created Time: Mon 12 Jun 2017 01:00:25 AM PDT
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <string.h>
#include <errno.h>

#define KEY_PATH "."
#define PROJECT_ID 88

/*union  semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};*/
/*struct sembuf{
    unsigned short sem_num;
    short sem_op;
    short sem_flg;
};*/
static int comm_sem(int flag,int nsem)
{
    key_t semkey=ftok(KEY_PATH,PROJECT_ID);
    if(semkey<0)
    {
        printf("ftok is faild\n");
    }
    return semget(semkey,nsem,flag);
}
int create_sem(int _semset_num)
{
    return comm_sem(IPC_CREAT|0666,_semset_num);
}
int init_sem(int _sem_id,int _which)
{
    union semun{
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    };
    union semun sem_un;
    sem_un.val=1;
    return semctl(_sem_id,_which,SETVAL,sem_un);
}
int get_sem()
{
    return comm_sem(IPC_CREAT,0);
}
static int op_sem(int sem_id,int which,int op)
{
    struct sembuf sem_buf;
    memset(&sem_buf,0,sizeof(sem_buf));
    sem_buf.sem_num=which;
    sem_buf.sem_op=op;
    sem_buf.sem_flg=0;
    return semop(sem_id,&sem_buf,1);
}
int sem_p(int sem_id,int which)
{
   return  op_sem(sem_id,which,-1);   
}
int sem_v(int sem_id,int which)
{
    return op_sem(sem_id,which,1);
}
int destory_sem(int _sem_id)
{
   return semctl(_sem_id,0,IPC_RMID);
}
int main()
{
    int sem_id=create_sem(1); 
    printf("semid:%d",sem_id);
    init_sem(sem_id,0);
    pid_t id=fork();
    if(id==0)
    {
        //child
        while(1)
        {
            sem_p(sem_id,0);
            usleep(10000);
            printf("A");
            fflush(stdout);
            sem_v(sem_id,0);
        }
    }
    else if(id>0)//father
    {
        while(1)
        {
            sem_p(sem_id,0);
            usleep(10000);
            printf("B");
            fflush(stdout);
            sem_v(sem_id,0);
        }
        wait(NULL);
    }
    else
    {
        printf("fork is faild\n");
    }
    
    destory_sem(sem_id);
    return 0;
}
