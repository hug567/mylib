/*
 *
 *
 * 2024-10-15
 */
#include <stdio.h>

typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

union u_params {
	u8 p_u8;
	s8 p_s8;
	u16 p_u16;
	s16 p_s16;
	u32 p_u32;
	s32 p_s32;
	float p_float;
};

int main(int argc, char *argc[])
{
	union u_params param = {0};
	return 0;
}
