#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char *a;

	a = NULL;

	a = calloc(2, sizeof(char));
	printf("a = %p\n", a);

	char *b = a;

	free(a);
	printf("a = %p\n", a);
	printf("b = %p\n", b);
	return(0);
}