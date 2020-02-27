/*#include <stdio.h>

extern void hello_print_c(void);

void hello_print_c(void)
{
	printf("this is a c fuanction\n");
}
*/

extern int add(int a, int b);
int add(int a, int b)
{
	return a + b;
}
