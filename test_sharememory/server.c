/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Tue 13 Jun 2017 06:50:10 AM PDT
 ************************************************************************/
#include"shm.h"
int main()
{
    int shmid=creat_shm();
    if(shmid==-1)
    {
        printf("creat_shm is faild!\n");
        return -1;
    }
    sleep(5);
    char *addr=at_shm(shmid);
    while(1)
    {
        sleep(1);
        printf("%s\n",addr);
    }
    sleep(5);
    dt_shm(addr);
    destory_shm(shmid);
    return 0;
}

