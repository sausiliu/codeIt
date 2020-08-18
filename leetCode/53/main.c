#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int right = 3;
	int left = 4;

	int mid = left + (right - left)>>1;

	printf("mid: %d \n", mid);

	return 0;
}
