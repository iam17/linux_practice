/*************************************************************************
	> File Name: revive.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 May 2017 07:28:57 AM PDT
 ************************************************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
int main()
{
    int fd=open("tmp",O_RDONLY);
    if(fd==-1)
    {
        printf("receive error!\n ");
        exit(1);
    }
    else
    {
        char mesg[100];

       ssize_t s= read(fd,mesg,sizeof(mesg));
       mesg[s-1]='\0';
       printf("%s\n",mesg);
    }
    return 0;
}
