/*
 * 解析THISS猫openamip协议中name=value类型的值
 * 2024-08-07
 */
#include <stdio.h>
#include <string.h>

#define DEFINE_GET_VAL_FROM_STR(_type, _fmt) \
static int __attribute__((unused)) \
get_##_type##_from_str(const char *str, const char *name, _type *val) \
{ \
	int ret; \
	_type tmp; \
	char *pos = NULL; \
	size_t str_len, name_len; \
	if (str == NULL || name == NULL || val == NULL) { \
		return -1; \
	} \
	str_len = strlen(str); \
	name_len = strlen(name); \
	if (str_len < name_len + 2) { \
		return -1; \
	} \
	pos = strstr(str, name); \
	if (pos == NULL) { \
		return -1; \
	} \
	pos = pos + name_len + 1; \
	ret = sscanf(pos, _fmt, &tmp); \
	if (ret < 1) { \
		return -1; \
	} \
	*val = tmp; \
	return 0; \
}
DEFINE_GET_VAL_FROM_STR(int, "%d")
DEFINE_GET_VAL_FROM_STR(float, "%f")

/* test: **********************************************************************/
static void parse_int_member(const char *message, const char *member)
{
	int ret;
	int val;

	ret = get_int_from_str(message, member, &val);
	if (ret < 0) {
		printf("get int [%s] from [%s] failed\n", member, message);
		return;
	}
	printf("int %s: %d\n", member, val);
}

static void parse_float_member(const char *message, const char *member)
{
	int ret;
	float val_f = 0.0f;

	ret = get_float_from_str(message, member, &val_f);
	if (ret < 0) {
		printf("get float [%s] from [%s] failed\n", member, message);
		return;
	}
	printf("float %s: %f\n", member, val_f);
}

static void parse_H_cmd(void)
{
	char *message = "H 1981.000 0.950 rol=1.0\r\n";

	printf("[%s]: ------------------------\n", __FUNCTION__);
	parse_float_member(message, "rol");
}

static void parse_C_cmd(void)
{
	//char *message = "C -50.00 -50.00 0.000 0 0.00 dvb=0 lat=0.00000 long=0.00000 modemUTC=0.000 plfUTC=0.000 plfEN=0.00 plfD=0.000 plfCRC=0 plfOP=0.00 plfM=0.00";
	char *message = "C -50.00 -50.00 0.000 0 0.00 dvb=1 lat=2.00000 long=3.00000 modemUTC=4.567 plfUTC=5.007 plfEN=6.70 plfD=7.312 plfCRC=8 plfOP=9.45 plfM=10.5";

	printf("[%s]: ------------------------\n", __FUNCTION__);
	parse_int_member(message, "dvb");
	parse_float_member(message, "lat");
	parse_float_member(message, "long");
	parse_float_member(message, "modemUTC");
	parse_float_member(message, "plfUTC");
	parse_float_member(message, "plfEN");
	parse_float_member(message, "plfD");
	parse_int_member(message, "plfCRC");
	parse_float_member(message, "plfOP");
	parse_float_member(message, "plfM");
}

int main()
{
	parse_H_cmd();
	parse_C_cmd();

	return 0;
}
