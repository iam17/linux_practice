/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Sat 20 May 2017 07:41:14 PM PDT
 ************************************************************************/
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
    pid_t pc,pr=0;
    pc=fork();
    if(pc<0)
       { printf("Error fork\n");}
    else if(pc==0)
        {
            sleep(5);
            exit(0);
        }
    else
    {
        while(pr==0)
        {
            pr=waitpid(pc,NULL,WNOHANG);
            if(pr==0)
            {
                printf("The child process has not exited \n");
                sleep(1);
            }
        }
      if(pc==pr)
          printf("Get child exit code:%d\n ",pr);
      else
           printf("Some error occured. \n");  
    }
    exit(0);
}

