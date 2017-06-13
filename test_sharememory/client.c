/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Tue 13 Jun 2017 06:16:21 AM PDT
 ************************************************************************/
#include"shm.h"
int main()
{
    int shmid=get_shm();
    if(shmid==-1)
    {
        printf("get_shm is faild!\n");
    }
    char *addr=at_shm(shmid);
    sleep(1);
    int i = 0;
   while(1)
        {
           sleep(1);
            addr[i++] = 'a';
            i %= (__SHM_SIZE__-1);
            addr[i]='\0';
        }

    dt_shm(addr);
    return 0;
}
