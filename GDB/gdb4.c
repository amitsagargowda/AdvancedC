#include <stdio.h>
struct test{
	int a;
	int b;
	int c;
};
int func1(void)
{
	struct test test1;
	int a;
	a=16;
	test1.a=1;
	test1.b=2;
	test1.c=3;
	return a;
}
int func2(void)
{
	int a;
	a=17;
	return a;
}
int main()
{
	int a;
	a=20+func1();
	printf("The value=%d\n",a);
	a=20+func2();
	printf("The value=%d\n",a);
	return 0;
}
