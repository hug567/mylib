/*
 * 常用安全函数打桩头文件
 * memcpy_s
 * memset_s
 * strcpy_s
 * strcat_s
 * strtok_s
 * sprintf_s
 * scanf_s
 * gets_s
 * 2020-09-26
 */

/* stdio.h */
#define gets_s gets
#define scanf_s scanf
#define sprintf_s(buf, len, format, ...) sprintf(buf, format, __VA_ARGS__)

/* string.h */
#define memcpy_s(dst, dstMax, src, count) memcpy(dst, src, count)
#define memset_s(dst, dstSize, ch, count) memset(dst, ch, count)
#define strcat_s(dst, dstMax, src) strcat(dst, src)
#define strcpy_s(dst, dstSize, src) strcpy(dst, src)
#define strtok_s(str, deliem, contex) strtok(str, deliem)
