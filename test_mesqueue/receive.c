/*************************************************************************
	> File Name: receive.c
	> Author: 
	> Mail: 
	> Created Time: Wed 07 Jun 2017 07:09:50 PM PDT
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>
struct mymesg{
        long mtype;
        char mtext[512];
};
int main()
{
    int msgid=-1;
    struct mymesg data;
    memset(data.mtext,0,sizeof(data.mtext));
    msgid=msgget(1234,IPC_EXCL|IPC_CREAT|0666);
    if(msgid==-1)
    {
        perror("msgget is error!!\n");
        exit(1);
    }
    while(1)
    {
        if(msgrcv(msgid,&data,sizeof(data.mtext),0,0)==-1)
        {
            perror("msgrcv is faild\n");
            exit(1);
        }
        printf("007:%s",data.mtext);
        printf("008:");
        memset(data.mtext,0,sizeof(data.mtext));
                fgets(data.mtext,512,stdin);
                if(msgsnd(msgid,&data,sizeof(data.mtext),0)==-1)
                {
                                perror("send is faild\n");
                                exit(1);
                            }
                if(strncmp(data.mtext,"end",3)==0)
        {
            printf("007 bye!\n");
                break;
        }
    }
    if(msgctl(msgid,IPC_RMID,0)==-1)
    {
        perror("msgctl is faild\n");
        exit(1);
    }
    return 0;
}
