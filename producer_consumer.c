#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>

int buff[5];
sem_t empty,full;
pthread_mutex_t m;
void * producer(void * arg)
{
	int item=10,i=0;
	printf("\nProducer Thread Created\n");	
	sleep(2);
	while(1)
	{
	  	sem_wait(&empty);
	  	pthread_mutex_lock(&m);
	  	sleep(1);
	  	buff[i++]=item;
	  	printf("%d item inserted at %d position\n",item,i);
		sleep(1);
	  	if(i==5)
	  		i=0;
	  	pthread_mutex_unlock(&m);
	  	sem_post(&full);
	}  	
	printf("Producer Terminated\n");

}

void * consumer(void * arg)
{	
	int key,i=0;
	printf("\nCosumer Thread Created\n");
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&m);
		sleep(2);
		key=buff[i++];
		printf("%d item from postion %d\n",key,i);
		if(i==5)
			i=0;
		pthread_mutex_unlock(&m);
		sem_post(&empty);
	}
	printf("Consumer Terminated\n");
}

int main()
{
	pthread_t pid,cid;
	sem_init(&empty,0,5);
	sem_init(&full,0,0);
	pthread_create(&pid,NULL,producer,NULL);
	pthread_create(&cid,NULL,consumer,NULL);
	pthread_mutex_init(&m,NULL);
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);
	printf("Main thread terminated\n");
	

}

