/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Sat 20 May 2017 09:22:23 PM PDT
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
int main()
{
    pid_t pid;
    int fd[2];
    int ret=pipe(fd);
    if(ret<0)
        printf("pipe error\n");
    pid=fork();
    if(pid<0)
    {
        printf("fork error\n");
    }
    else if(pid>0)
    {
        close(fd[0]);
        int i=0;
        char* mesg=NULL;
        while(i<100)
        {
            mesg="i am child!";
            write(fd[1],mesg,strlen(mesg)+1);
            sleep(1);
          /*  if(i==5)
            {
                close(fd[1]);
                break;
            }*/
            i++;
        }
         close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char mesg[100];
       
        int j=0;
        int n;
        while(j<100)
        { 
            ssize_t s=read(fd[0],mesg,sizeof(mesg));
            mesg[s-1]='\0';
            printf("%s\n",mesg);
            j++;
        }
        close(fd[0]);
    }
    return 0;
}
