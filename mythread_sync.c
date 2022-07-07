#include<stdio.h>
#include <pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#define THREAD_NUM 25000
int value = 0;
void *add();
void *sub();

sem_t ter;


int main()
{
    pthread_t tid[THREAD_NUM];
    int i;
    //add함수 부분
    sem_init(&ter,0,1);
    
    for(i=0;i<THREAD_NUM;i++)
        if(pthread_create(&tid[i],  NULL, add, NULL)){
            printf("error pthread_create\n");
            exit(0);
            }
    
    
    for(i=0;i<THREAD_NUM;i++)        
        if (pthread_join(tid[i], NULL))
            printf("error pthread_join\n");
    
    //sub함수 부분
    for(i=0;i<THREAD_NUM;i++)
        if(pthread_create(&tid[i],  NULL, sub,  NULL))
            printf("error pthread_create\n");
    
    
    for(i=0;i<THREAD_NUM;i++)        
        if (pthread_join(tid[i], NULL))
            printf("error pthread_join\n");
    exit(0);
}

void *add(){
    sem_wait(&ter);   
    value++;
    
    printf("%d\n",value);
    sem_post(&ter);
    pthread_exit((void*)NULL);
}

void *sub(){
    sem_wait(&ter);
    value--;
    printf("%d\n",value);
    sem_post(&ter);
    pthread_exit((void*)NULL);
}