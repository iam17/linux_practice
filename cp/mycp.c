/*************************************************************************
	> File Name: mycp.c
	> Author: 
	> Mail: 
	> Created Time: Sun 18 Jun 2017 04:55:37 AM PDT
 ************************************************************************/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
typedef struct _node{
    int data;
    struct _node* next;
}node_t,*node_p,**node_pp;
node_p head=NULL;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
static node_p  alloc_node(int data)
{
    node_p tmp=(node_p)malloc(sizeof(node_t));
    if(tmp==NULL)
    {
        perror("malloc");
        exit(1);
    }
    tmp->data=data;
    tmp->next=NULL;
    return tmp;
}
static void delete_node(node_p n)
{
    if(n!=NULL)
        free(n);
}
static int isEmpty(node_p h)
{
    return h->next==NULL;
}
void initList(node_pp h)
{
    *h=alloc_node(0);
}
void pushFront(node_p h,int data)
{
    node_p tmp=alloc_node(data);
    tmp->next=h->next;
    h->next=tmp;
}
void popFront(node_p h,int* out)
{
    if(!isEmpty(h))
    {
        node_p p=h->next;
        h->next=p->next;
        *out =  p->data;
        delete_node(p);
    }
}
void destoryList(node_p h)
{
    int out=0;
    while(!isEmpty(h))
    {
        popFront(h,&out);
    }
    delete_node(h);

}
void showList(node_p h)
{
    node_p start=h->next;
    while(start)
    {
        printf("%d ",start->data);
        start=start->next;
    }
    printf("\n");
}
void *product(void *arg)//生产
{
    while(1)
    {
        int data=rand()%1234;
        pthread_mutex_lock(&lock);
        pushFront(head,data);
        pthread_mutex_unlock(&lock);  
        pthread_cond_signal(&cond);
        printf("product done: %d",data);
        sleep(1);
    }
}
void *consume(void *arg)//消费
{
    int c=-1;
    while(1)
    {
        pthread_mutex_lock(&lock);
        while(isEmpty(head))
        {
            printf("consume begin waiting...\n");
            pthread_cond_wait(&cond,&lock);
        }
        popFront(head,&c);
        printf("consumer done: %d\n",c);
        pthread_mutex_unlock(&lock);
    }
}
int main()
{
    initList(&head);
    pthread_t p,c;
    pthread_create(&p,NULL,product,NULL);
    pthread_create(&c,NULL,consume,NULL);

    pthread_join(p,NULL);
    pthread_join(c,NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    destoryList(head);
    return 0;
}
