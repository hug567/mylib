#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define FILE_NAME "/proc/test_proc/proc_wfile"

static int proc_ioctl(void)
{
    int fd, ret;

    fd = open(FILE_NAME, O_RDWR);
    if (fd < 0) {
        printf("open %s failed\n", FILE_NAME);
        return -1;
    }

    ret = ioctl(fd, 0xF0001, 0);
    if (ret < 0) {
        printf("ioctl failed\n", FILE_NAME);
        close(fd);
        return ret;
    }

    ret = ioctl(fd, 0xF0002, 0);
    if (ret < 0) {
        printf("ioctl failed\n", FILE_NAME);
        close(fd);
        return ret;
    }

    ret = ioctl(fd, 0xF0003, 0);
    if (ret < 0) {
        printf("ioctl failed\n", FILE_NAME);
        close(fd);
        return ret;
    }

    close(fd);

    return 0;
}

int main(void)
{
    int ret;

    ret = proc_ioctl();
    if (ret < 0) {
        return ret;
    }

    return 0;
}
