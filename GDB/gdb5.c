//This program calculates and prints out the factorials of 5 and 17


#include <stdio.h>
#include <stdlib.h>

int factorial(int n);

int main(void) {
	
	int n = 5;
	int f = factorial(n);
	printf("The factorial of %d is %d.\n", n, f);
	n = 17;
	f = factorial(n);
	printf("The factorial of %d is %d.\n", n, f);

	return 0;
		
}
//A factorial is calculated by n! = n * (n - 1) * (n - 2) * ... * 1
//E.g. 5! = 5 * 4 * 3 * 2 * 1 = 120
int factorial(int n) {
	int f = 1;
	int i = 1;
	while (i <= n) {
		f = f * i;
		i++;
	}
	return f;	
}
