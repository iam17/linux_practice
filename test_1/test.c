/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Tue 09 May 2017 01:56:02 PM PDT
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>
#include <signal.h>
#include <pwd.h>
#include <sys/utsname.h>
#include<malloc.h>

#define normal          0       //一般命令
#define out_redirect_1  1       //输出重定向('>'新建)
#define out_redirect_2  2       //输出重定向('>>'追加)
#define in_redirect     3       //输入重定向
#define have_pipe       4       //管道命令

int main()
{

    while(1)
    {       
        printf("[tiancong@hostname ~]$");
        fflush(stdout);
        char buff[1024];
        ssize_t s=read(0,buff,sizeof(buff)-1);
        if(s>0)
        {
            buff[s-1]=0;
        }
        char* start=buff;
        char* _argv[32];
        int i=1;
        _argv[0]=start;
        int option=normal;
        int fd;
        int flag=0;
        while(*start)
        {
            if(*start==' ')
            {
                *start='\0';
                start++;
                while(*start==' ')
                {
                    start++;
                }
               _argv[i++]=start;
            }
            else if(*start=='>')
            {
               *start++='\0';
                int count=1;
               while(*start=='>')
                   {
                    count++;   
                    start++;
                }
                if(count==1)
                    _argv[i++]=">";
                else if(count==2)
                _argv[i++]=">>";
                else
                   {
                       printf("input is error!\n");
                       break;
                   }
                _argv[i++]=start;
            }
            else{
                start++;
            }
        }
        buff[s-1]='\0';
        _argv[i]=NULL;
        pid_t id=fork();
        if(id==0)
        {
            //调用普通指令    
            int option=normal;
            int fd;
            int flag=0;
            char* file;
            for (i=0; _argv[i] != NULL; i++)
            {
                if (strcmp(_argv[i],">") == 0)      
                {
                    file=_argv[i+1];
                    option= out_redirect_1;  
                    _argv[i+1]=NULL;
                    if (_argv[i+1] == NULL) {
                        flag++;
               }
            }
                if (strcmp(_argv[i],">>") == 0) {
                   flag++;
                   option = out_redirect_2;
                   file=_argv[i+1];
                 if (_argv[i+1] == NULL) {
                        flag++;
               }
           }

                if (strcmp(_argv[i],"<") == 0) {
                   flag++;
                   option = in_redirect;
                   file=_argv[i+1];
                    _argv[i+i]=NULL;
                   if (i == 0) {
                       flag++;
               }
           }
                if(strcmp(_argv[i],"|") == 0)
                {
                   flag++;
                    _argv[i+1]=NULL;
                   option = have_pipe;
                   file=_argv[i+1];
                   if (_argv[i+1] == NULL) {
                       flag++;
                  }
                   if (i == 0) {
                       flag++;
               }
            }
       }
            switch(option)
            {
            case 0:
               { 
                   execvp(_argv[0],_argv);    
                   exit(1);
               }
                break;
            case 1:
                {
                    fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
                               
                                dup2(fd,1);
                                execvp(_argv[0],_argv);
                                close(fd);
                                exit(0);
                    ;
                }
                break;
            case 2:
                {
                   fd = open(file,O_APPEND|O_WRONLY,0644);
                                dup2(fd,1);
                                execvp(_argv[0],_argv);
                                close(fd);
                                exit(0);

                }
                break;
            case 3:
                {
                    fd = open(file,O_RDONLY);
                                dup2(fd,1);
                                execvp(_argv[0],_argv);
                                close(fd);
                                exit(0);

                }
                break;  
            default:
                break;       
            }
        }
        else{
            pid_t ret=waitpid(id,NULL,0);
            if(ret>0)
            {
               // printf("father wait success!:%d",ret);
            }
            else{
               // printf("father wait false!");
            }
        }
    }
    return 0;
}
