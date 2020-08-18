#include <stdio.h>
#include <string.h>
#include <time.h>

int get_passwd() 
{
	char * pass_word = "123456";
	char buf[20];
	printf("Passwd[%p]: \n", buf);
	gets(buf, stdin);

	if (strcmp(buf, pass_word))
		return -1;

	return 0;
}

void display_content()
{
	time_t now;
	struct tm *timenow;

	time(&now);
	timenow = localtime(&now);
	printf("Local time is %s \n", asctime(timenow));
}

int main(int argc, char *argv[])
{
	int a = 1;
	if ( 0 == get_passwd())
		display_content();

	a += 1;

	printf("a = %d \n", a);
	return 0;
}
