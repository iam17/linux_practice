/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 May 2017 04:47:33 AM PDT
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
int main()
{
    if(mkfifo("tmp",0666)==-1)
    {
        printf("myfifo error!");
        exit(1);
    }
    else
    {
        int n=open("tmp",O_WRONLY);
        if(n==-1)
        {
            printf("open error!\n");
            exit(1);
        }
        else
        {
            char *mesg="i am test!";
            write(n,mesg,strlen(mesg)+1);
        }
    }
    return 0;
}
