/*
 * Create: 2025-03-31 10:39:31
 */

#define DEBUG_RW_ARRAY_SIZE 34
typedef struct {
	u8 val_u8;
	s8 val_s8;
	u16 val_u16;
	s16 val_s16;
	u32 val_u32;
	s32 val_s32;
	float val_float;
	u8 arr_u8[DEBUG_RW_ARRAY_SIZE];
	s8 arr_s8[DEBUG_RW_ARRAY_SIZE];
	u16 arr_u16[DEBUG_RW_ARRAY_SIZE];
	s16 arr_s16[DEBUG_RW_ARRAY_SIZE];
	u32 arr_u32[DEBUG_RW_ARRAY_SIZE];
	s32 arr_s32[DEBUG_RW_ARRAY_SIZE];
	float arr_float[DEBUG_RW_ARRAY_SIZE];
} debug_rw_t __attribute__((aligned(32)));

#define DEBUG_LOG_BUF_SIZE 512
static char g_buf[DEBUG_LOG_BUF_SIZE] = {0};
static int print_debug_rw(void)
{
	int i, len, sum_len;
	debug_rw_t *drw = debug_rw_lookup();
	char *buf = g_buf;

	if (drw == NULL) {
		log_err("get debug_rw failed\n");
		return -1;
	}
	log_info("u8: %hhu, s8: %hhd, u16: %hu, s16: %hd, u32: %u, s32: %d, "
		 "float: %f\n", drw->val_u8, drw->val_s8, drw->val_u16,
		 drw->val_s16, drw->val_u32, drw->val_s32, drw->val_float);

#define PRINT_DRW_ARRAY(_member, _fmt) \
{ \
	memset(buf, 0, DEBUG_LOG_BUF_SIZE); \
	sum_len = 0; \
	for (i = 0; i < 16; i++) { \
		len = snprintf(buf + sum_len, DEBUG_LOG_BUF_SIZE - sum_len - 1, \
			       _fmt, drw->_member[i]); \
		if (len > 0) { \
			sum_len += len; \
		} \
	} \
	log_info(#_member"[ 0-15]: [%s]\n", buf); \
	; \
	memset(buf, 0, DEBUG_LOG_BUF_SIZE); \
	sum_len = 0; \
	for (i = 16; i < 32; i++) { \
		len = snprintf(buf + sum_len, DEBUG_LOG_BUF_SIZE - sum_len - 1, \
			       _fmt, drw->_member[i]); \
		if (len > 0) { \
			sum_len += len; \
		} \
	} \
	log_info(#_member"[16-31]: [%s]\n", buf); \
	; \
	memset(buf, 0, DEBUG_RW_ARRAY_SIZE); \
	sum_len = 0; \
	for (i = 32; i < DEBUG_RW_ARRAY_SIZE; i++) { \
		len = snprintf(buf + sum_len, DEBUG_LOG_BUF_SIZE - sum_len - 1, \
			       _fmt, drw->_member[i]); \
		if (len > 0) { \
			sum_len += len; \
		} \
	} \
	log_info(#_member"[32-%d]: [%s]\n", DEBUG_RW_ARRAY_SIZE - 1, buf); \
}
	PRINT_DRW_ARRAY(arr_u8, "%hhu ")
	PRINT_DRW_ARRAY(arr_s8, "%hhd ")
	PRINT_DRW_ARRAY(arr_u16, "%hu ")
	PRINT_DRW_ARRAY(arr_s16, "%hd ")
	PRINT_DRW_ARRAY(arr_u32, "%u ")
	PRINT_DRW_ARRAY(arr_s32, "%d ")
	PRINT_DRW_ARRAY(arr_float, "%f ")

	return 0;
}
