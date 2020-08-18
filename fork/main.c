#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define POST_STACK_POINTER() \
	do { \
		register unsigned long int sp; \
		__asm__ __volatile__("mov %0, sp" : "=r"(sp)); \
		printf("the sp is %08x \n", sp); \
	} while(0)

void breakpoint_test(int flag)
{

	if (flag) {

		int var  = 1;
		while (var) {
		}
		printf(" [[[break point from Child ]]]\n");
	} else {
		printf(" [[[break point from Parent ]]]\n");
	}

}

int main(int argc, char *argv[])
{

	char buf[20];
	char * str = "123456";
	int a = 10;
	pid_t pid;

	printf("Password: \n");
	gets(buf, stdin);
	a++;

	if (strcmp(buf, str))
		a = 0;

	pid = fork();

	if (!pid) {
		printf("\n ---------------------- \n");
		printf("Child :  I am the child \n");
		breakpoint_test(1);
		POST_STACK_POINTER();
		buf[1] = 'A';
	} else {
		printf("\n ++++++++++++++++++++++  \n");
		printf("Parent:  the child's pid is %d \n", pid);
		breakpoint_test(0);
		POST_STACK_POINTER();
	}

	printf("a is %d n \n", a);
	printf("buf is %s n \n", buf);
	printf("\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   \n");
	return 0;
}
