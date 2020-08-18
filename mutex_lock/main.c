#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int gCount = 0;

void * thread_count(void *arg)
{
	unsigned int i = 0;
	unsigned temp = 0;

	while (i < 500) {
		temp = gCount;
		i++;
		printf("thread id %lu, count: %u\n", pthread_self(), gCount);
		gCount = temp + 1;
	}
}

int main(int argc, const char * argv)
{
	pthread_t tid, tid2;

	pthread_create(&tid, NULL, thread_count, NULL);
	pthread_create(&tid2, NULL, thread_count, NULL);

	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);

	printf("result is %d \n", gCount);
}

