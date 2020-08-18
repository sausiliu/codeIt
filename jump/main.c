#include <stdio.h>
#include <setjmp.h>

//#define PTR_MANGLE 0
//#define PTR_DEMANGLE 0
#ifdef PTR_MANGLE
#undef PTR_MANGLE
#endif

jmp_buf env;

double divide(double a, double b)
{
	const double delta = 0.000000000001;

	if (!((-delta < b)&&( b < delta))) {
		return a/b;
	} else {
		longjmp(env, 1);
		return 0;
	}

}

int main(int argc, char *argv[])
{
	double result = 0;
	int a = 0;
	int b = 0;

	int ret = setjmp(env);

	a++;
	if (!ret) {
		result = divide(111, 0);
		printf("result is %f \n", result);
	} else {
		printf("the arg is invalid \n");
	}

	return 0;
}
