/*************************************************************************
	> File Name: msgsend.c
	> Author: 
	> Mail: 
	> Created Time: Wed 07 Jun 2017 09:18:44 PM PDT
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<unistd.h>
#include<error.h>
#include<string.h>
struct mymesg{
    long mtype;
    char mtext[512];
};
int main()
{
    int msgid=-1;
    msgid=msgget(1234,0666|IPC_CREAT);
    struct mymesg data;
    if(msgid==-1)
    {
        perror("msgget is faild!!!\n");
        exit(1);
    }
    while(1)
    {
        printf("007say:");
        fgets(data.mtext,512,stdin);
        if(msgsnd(msgid,&data,sizeof(data.mtext),0)==-1)
        {
            perror("send is faild\n");
            exit(1);
        }
        if(strncmp(data.mtext,"end",3)==0)
        {
            printf("007 bye");
           break;
        }
        memset(data.mtext,0,sizeof(data.mtext));
        if(msgrcv(msgid,&data,sizeof(data.mtext),0,0)==-1)
                {
                                perror("msgrcv is faild\n");
                                exit(1);
                            }
                printf("008say:%s",data.mtext);
                if(strncmp(data.mtext,"end",3)==0)
                break;
    }
    return 0;
}
