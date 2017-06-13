/*************************************************************************
	> File Name: shm.h
	> Author: 
	> Mail: 
	> Created Time: Tue 13 Jun 2017 05:46:14 AM PDT
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#define __PATH__ "."
#define __PROJECT__ 8888
#define __SHM_SIZE__ 4*1024 //4k对齐
//创建共享存储区
int common_shm(int flag)
{
   int key=ftok(__PATH__,__PROJECT__);
    if(key==-1)
    {
        printf("ftok is faild!\n");
        return -1;
    }
    return shmget(key,__SHM_SIZE__,flag);
}
int creat_shm()
{
    return common_shm(IPC_CREAT|0666);
}
int get_shm()
{
    return common_shm(0);
}
//连接已有的共享内存
void *at_shm(int shmid)
{
    return (char*)shmat(shmid,NULL,0);   
}
//进程与共享内存分离
int dt_shm(const void *addr)
{
    return shmdt(addr);
}
//删除共享内存
int destory_shm(int shmid)
{
    return shmctl(shmid,IPC_RMID,NULL);
}
