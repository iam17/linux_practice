/*************************************************************************
	> File Name: tcp_server.c
	> Author: 
	> Mail: 
	> Created Time: Wed 21 Jun 2017 02:37:15 AM PDT
 ************************************************************************/
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
int startup( char* local_ip, char *local_port)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        exit(2);
    }
    struct sockaddr_in local;
    local.sin_family=AF_INET;
   // local.sin_port=htons(local_port);
    local.sin_addr.s_addr=inet_addr(local_ip);
    local.sin_port=htons(atoi(local_port));
    if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
    {
        perror("bind");
        exit(3);
    }
    if(listen(sock,5)<0)
    {
        perror("listen");
        exit(4);
    }
    return sock;
}
int main(int argc,char *argv[])
{
    if(argc<3)
    {
        printf("%s [local_ip] [local_port]\n",argv[0]);
        return 0;
    }
    int listen_sock=startup(argv[1],argv[2]);
    while(1)
    {
        struct sockaddr_in client;
        socklen_t len=sizeof(client);
        int new_fd=accept(listen_sock,(struct sockaddr*)&client,&len);
        if(new_fd<0)
        {
            perror("accept");
            continue;
        }
        printf("get a new client, %s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        pid_t id=fork();
        if(id<0)
        {
            perror("fork");
            close(new_fd);
        }
        else if(id==0)//child
        {
            pid_t id2=fork();
            close(listen_sock);
            if(id>0)
            {
                exit(1);
            }
            while(1)
            {
                char buf[1024];
                ssize_t s=read(new_fd,buf,sizeof(buf)-1);
                if(s>0)
                {
                    buf[s]='\0';
                    printf("client[%s:%d]: %s",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
                   /* if(strncmp(buf,"quit",4)==0);
                    {
                        close(new_fd);
                        break;
                    }*/
                    write(new_fd,buf,strlen(buf));
                }
                else
                {
                    printf("read done break...\n");
                    break;
                }
            }
            close(new_fd);
        }
        else//father
        {
                    
        }
}
       /*while(1)
       {
           char buf[1024];
           ssize_t s=read(new_fd,buf,sizeof(buf)-1);
           if(s>0)
           {
               buf[s]='\0';
               printf("client : %s\n",buf);
               write(new_fd,buf,strlen(buf));
           }
           else{
               printf("read done...,break\n");
               break;
           }
       }*/
    return 0;
}
