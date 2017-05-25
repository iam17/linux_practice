/*************************************************************************
	> File Name: wait.c
	> Author: 
	> Mail: 
	> Created Time: Sat 20 May 2017 08:07:13 PM PDT
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
    int status;
    pid_t pc,pr;
    pc=fork();
    if(pc<0)
        printf("error ocurred!\n");
    else if(0==pc)
        {
            printf("this is child process whit pid of %d\n",getpid());
            exit(3);
        }
    else
    {
        pr=wait(&status);
        if(status|0xff)
        {
            printf("the child process %d exit normally. \n",pr);
            printf("the return code is %d.\n",WEXITSTATUS(status));  
        }
        else
       {
           printf("the child process %d exit abnormally. \n",pr);
       }
    }
    return 0;
}
