#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int ret;
    float a, b, c;

    ret = sscanf(" 123 456 789 #dfafadf", "%f %f %f", &a, &b, &c);
    if (ret < 0) {
        printf("sscanf failed, ret: %d, errno: %d(%s)\n", ret, errno, strerror(errno));
        return ret;
    }
    printf("ret: %d, a: %f, b: %f, c: %f\n", ret, a, b, c);

    return 0;
}
