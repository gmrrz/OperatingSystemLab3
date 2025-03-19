#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
//int counter = 0;

sem_t mutex, empty, full;


void *producer(void *param){
	int item_produced = 1;
	while (1){
		sem_wait(&empty);
		sem_wait(&mutex);
		//while (counter == BUFFER_SIZE);
		buffer[in] = item_produced;
		printf("Produced: %d\n", item_produced);
		item_produced++;
		in = (in + 1)%BUFFER_SIZE;
		//counter++;

		sem_post(&mutex);
		sem_post(&full);

		printf("producer produced an item, counter is: %d\n", counter);
		sleep(1);
	}
}


void *consumer(void * param){
	while (1){
		//while(counter == 0);
		sem_wait(&full);
		sem_wait(&mutex);
		int item = buffer[out];
		printf("Consumed: %d\n", item);
		out = (out+1)%BUFFER_SIZE;
		sem_post(&mutex);
		sem_post(&empty);
		//counter--;
		sleep(2);
	}
}

int main(){

	pthread_t thread1, thread2;

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);

	pthread_create(&thread1, NULL, producer, NULL);
	pthread_create(&thread2, NULL, consumer, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;

}


