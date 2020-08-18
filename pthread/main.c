#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>

#define STACK_SIZE (1024 * 1024) 

static thread_id;

static size_t getPageSize()
{
	/*Hard-coding page size to 4096 bytes*/
	return 4096;
}

struct thread_info {
	pthread_t threadID;
	pthread_attr_t threadAttr;

	int flags;
	void *(*startupFunc) (void *arg);
	void *startupArg;

	size_t stacksize;
	size_t guardSize;
	void * stackaddr;
	char nativeThreadName[20];
};

typedef struct thread_info thread_info_t;

static thread_info_t * thread_info_new()
{
	thread_info_t *tinfo = malloc(sizeof(thread_info_t));
	tinfo->flags = 0;
	tinfo->threadID = 0;
	tinfo->startupFunc = NULL;
	tinfo->startupArg = NULL;
	tinfo->stacksize = STACK_SIZE;
	tinfo->guardSize = getPageSize();
}

void * func(void *arg)
{
	int a = 0;
	int val = *(int *)arg;
	for(int i = 0; i < 10; i++) {
		printf("Tread id: %d   [i:%d]\n", val, i);
		a += val;
	}

	printf("Bye bye!!\n ");

	return NULL;
}

void * func_copy(void *arg)
{
	int a = 0;
	int val = *(int *)arg;
	for(int i = 0; i < 10; i++) {
		printf("Tread id: %d   [i:%d]\n", val, i);
		a += val;
	}

	printf("Bye bye!!\n ");
	return NULL;
}

static void wrap_pthread_attr_init(thread_info_t *tinfo, const pthread_attr_t *tattr)
{
	pthread_attr_init(&tinfo->threadAttr);

	if(tattr) {
		//Overwrite default thread stack and guard size with tattr.
		pthread_attr_getstacksize(tattr, &tinfo->stacksize);
		pthread_attr_getguardsize(tattr, &tinfo->guardSize);

		size_t pageSize = getPageSize();
		tinfo->stacksize = (tinfo->stacksize + pageSize - 1) % pageSize;
		tinfo->guardSize = (tinfo->guardSize + pageSize - 1) % pageSize;

		int detachState = 0;
		pthread_attr_getdetachstate(tattr, &detachState);
		pthread_attr_setdetachstate(&tinfo->threadAttr, detachState);
	}

	//init thread stack
	
	tinfo->stackaddr = mmap(NULL, 
							tinfo->stacksize + tinfo->guardSize,
							PROT_READ | PROT_WRITE,
							MAP_PRIVATE | MAP_ANONYMOUS,
							/* fd */ -1,
							0);

	mprotect(tinfo->stackaddr, tinfo->guardSize, PROT_NONE);
	pthread_attr_setstack(&tinfo->threadAttr, 
						  (char *)tinfo->stackaddr + tinfo->guardSize,
						  tinfo->stacksize);
}

int wrap_pthread_create(pthread_t *thread,
						const pthread_attr_t *attr,
						void *(*start_routine) (void *),
						void *arg)
{
	thread_info_t *tinfo;
	tinfo = thread_info_new();
	//wrap_pthread_attr_init(tinfo, attr);

	tinfo->threadID = ++thread_id;
	
	tinfo->startupFunc = start_routine;
	tinfo->startupArg = arg;

	pthread_create(thread, &tinfo->threadAttr, tinfo->startupFunc, &tinfo->threadID);

}


int main(int argc, char *argv[])
{
	int ret;

	pthread_t thread_1, thread_2;

	wrap_pthread_create(&thread_1, NULL, func, NULL);
	wrap_pthread_create(&thread_2, NULL, func_copy, NULL);

	for(int i = 0; i < 10; i++) {
		printf("This main process [i = %d]\n", i);
	}

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	return 0;
}
