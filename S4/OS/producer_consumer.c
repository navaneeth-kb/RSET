#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

#define BUFFER_SIZE 3
#define NUM_CONSUMERS 2
#define NUM_PRODUCERS 2

int buffer[BUFFER_SIZE];
int in=0,out=0;
sem_t mutex,empty,full;

void *producer(void *arg)
{
    int item;
    item=rand();
    sem_wait(&empty);
    sem_wait(&mutex);
    buffer[in]=item;
    printf("produced:%d\n",item);
    in=(in+1)%BUFFER_SIZE;
    sem_post(&mutex);
    sem_post(&full);
    sleep(1);
}

void *consumer(void *arg)
{
    int item;
    sem_wait(&full);
    sem_wait(&mutex);
    item=buffer[out];
    printf("consumed:%d\n",item);
    out=(out+1)%BUFFER_SIZE;
    sem_post(&mutex);
    sem_post(&empty);
    sleep(1);
}

void main()
{
    int n;
    printf("enter the number of items to consume and produce:");
    scanf("%d",&n);
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    sem_init(&mutex,0,1);
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    for(int i=0;i<n;i++)
    {
        pthread_create(&producer_threads[0],NULL,producer,NULL);
        pthread_create(&consumer_threads[0],NULL,consumer,NULL);
    }
    for(int i=0;i<NUM_PRODUCERS;i++)
    {
        pthread_join(producer_threads[0],NULL);
        pthread_join(consumer_threads[0],NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}
