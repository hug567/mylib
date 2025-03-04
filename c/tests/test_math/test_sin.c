/*
 * 生成正弦变化的数据
 * 2025-03-01
 */
#include <stdio.h>
#include <math.h>

#define MAX_COUNT 1000

int main(void)
{
	int i;
	float x, y;

	for (i = 0; i < MAX_COUNT; i++) {
		x = i * M_PI / 500.0f;
		y = 15 * sin(x);
		printf("x: %f, y: %f\n", x, y);
	}

	return 0;
}
