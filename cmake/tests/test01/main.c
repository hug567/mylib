#include <stdio.h>

int main(void)
{
#ifdef DEFINE_A
	printf("DEFINE_A is defined\n");
#endif
#ifdef DEFINE_B
	printf("DEFINE_B is defined\n");
#endif
	return 0;
}
