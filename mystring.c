#include<stdio.h>
#include <pthread.h>
#include<stdlib.h>
#include<semaphore.h>
#include<string.h>

void* pthread_fun_word();//영단어 출력 함수
void* pthread_fun_spcword();//특수기호 출력
void* pthread_fun_null();//띄어쓰기
char* str;
int len_str;

sem_t sem_word,sem_spc,sem_nul;

int main()
{
    pthread_t word,spc,nul;

    str=malloc(sizeof(char)*100);
    fgets(str,100,stdin);
    sem_init(&sem_word,0,2);
    sem_init(&sem_spc,0,0);
    sem_init(&sem_nul,0,0);
    len_str=strlen(str);

    pthread_create(&word,NULL,pthread_fun_word,NULL);
    pthread_create(&spc,NULL,pthread_fun_spcword,NULL);
    pthread_create(&nul,NULL,pthread_fun_null,NULL);
    
    
    
    
    pthread_join(word,NULL);
    pthread_join(spc,NULL);
    pthread_join(nul,NULL);


//    printf("%c\n",str[1]);

}


void* pthread_fun_word(){
    int i;
    
    
    for (i=0;i<len_str;i++){//돌면서
        sem_wait(&sem_word);
        sem_wait(&sem_word);//wait두번 하면서 sem_word가 2여야 돌아가도록
        //printf("th word\n");
        if ((str[i]>='a' && str[i]<='z') || (str[i]>='A' &&str[i]<='Z')){
            printf("%c",str[i]);
            
            sem_post(&sem_spc);//각각 쏴주고
            sem_post(&sem_nul);   
        }
        else{
            sem_post(&sem_spc);//각각 쏴주고
            sem_post(&sem_nul);
        }
    }
}

void* pthread_fun_spcword(){
    int i;
    
    for (i=0;i<len_str;i++){
        sem_wait(&sem_spc);//워드에서 쏴줘야 확인
        //sem_wait(&sem_spc);
        //printf("th spc\n");
        if (!(str[i]>='a' && str[i]<='z') && !(str[i]>='A' && str[i]<='Z') && str[i]!=' '){
            printf("%c",str[i]);
            sem_post(&sem_word);
        }
        else{
            sem_post(&sem_word);//내꺼 쓸거 없으면 워드로 보냄
        }
    }
}

void* pthread_fun_null(){
    int i;
    
    for (i=0;i<len_str;i++){
        sem_wait(&sem_nul);//워드에서 쏴 줘야 확인
        //sem_wait(&sem_nul);
        //printf("th nul\n");
        if (str[i]==' '){
            printf("%c",str[i]);
            sem_post(&sem_word);
        }
        else{
            sem_post(&sem_word);//내꺼 없으면 워드로 보냄            
        }
    }
}