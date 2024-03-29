//zynq7020h

//delay_ms(1000)实际延时约447ms
#define DELAY_MS_LOOP_COUNT 30000
void delay_ms(u32 ms)
{
	volatile int i, j;

	for (i = 0; i < ms; i++) {
		for (j = 0; j < DELAY_MS_LOOP_COUNT; j++);
	}
}
