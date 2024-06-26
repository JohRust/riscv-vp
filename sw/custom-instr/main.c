#include <stdio.h>

/**
 * This program demonstrates the usage of inline assembly in C.
 */
int main() {
	int a = 5;
	int b = 10;
	int result;

	asm ("add %0, %1, %2\n\t"
		: "=r" (result)
		: "r" (a), "r" (b)
		);
	printf("Result: %i\n", result);
}
