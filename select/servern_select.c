/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Jun 2017 12:45:42 AM PDT
 ************************************************************************/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>
#define __SIZE__ 64
int gfds[__SIZE__];
void usage()
{
    printf("./server [local_ip] [local_port]\n");
}
int startup(const char *ip,int port)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        exit(2);
    }
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    server.sin_addr.s_addr=inet_addr(ip);
    const int on=1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
    if(bind(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        perror("bind");
        exit(3);
    }
    return sock;
}
int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        usage();
        exit(1);
    }
    int listen_sock=startup(argv[1],atoi(argv[2]));
    if(listen(listen_sock,5)<0)
    {
        perror("listen");
        exit(4);
    }
    int i=1;
    for(;i<__SIZE__;i++)
    {
        gfds[i]=-1;              
    }
    gfds[0]=listen_sock;
    while(1)
    {
        int max_fd=-1;
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(listen_sock,&rfds);
        int k=0;
        for(;k<__SIZE__;k++)
        {
            if(gfds[k]>0)
            {
                if(gfds[k]>max_fd)
                    max_fd=gfds[k];
                FD_SET(gfds[k],&rfds);
            }
        }//for
        struct timeval timeout={5,0};
        switch(select(max_fd+1,&rfds,0,0,&timeout))
        {
            case -1:
            {
                perror("select");
                break;
            }
            case 0:
            {
                printf("timeout...\n");
                continue;
            } 
            default:
            {
                int j=0;
                for(;j<__SIZE__;j++)
                {
                    if(gfds[j]==-1)
                        continue;
                    else if(FD_ISSET(gfds[j],&rfds)) 
                    {
                        if(j==0)
                        {
                        struct sockaddr_in client;
                        socklen_t len=sizeof(client);
                        int new_fd=accept(listen_sock,(struct sockaddr*)&client,&len);
                        pid_t id=fork();
                        if(id==0)
                        {
                            close(new_fd);
                            exit(0);
                        } 
                        printf("get a new client,%s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                        if(new_fd<0)
                        {
                            perror("accept");
                            continue;
                        }
                        int m=1;   
                        for(;m<__SIZE__;m++)
                        {
                            if(gfds[m]==-1)
                                break;
                        }
                        if(m==__SIZE__)
                        {
                            close(new_fd);
                            printf("no\n");
                        }
                        else
                        {
                            gfds[m]=new_fd;
                        }
                        }
                        if(j!=0)
                        {//other fd ready
                            char buf[1024];
                            ssize_t s=read(gfds[j],buf,sizeof(buf)-1);
                            if(s>0)
                            {
                                buf[s]='\0';
                                printf("client[%d]: %s",j,buf);
                                if(strncmp(buf,"quit",4)==0)
                                {
                                    printf("quit\n");
                                    break;
                                }
                                write(gfds[j],buf,strlen(buf));
                            }
                            else if(s==0)
                            {
                                printf("client[%d] is quit!!!\n",j);
                                close(gfds[j]);
                                gfds[j]=-1;
                                break;
                            }
                            else
                                perror("read");
                        }
                     }
                    else
                        ;
                }
            }
            break;
        }
    }//while
    close(listen_sock);
    return 0;
}
