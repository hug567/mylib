// 常用接口/结构所在头文件

#include <stdio.h>
    FILE
    printf()
    snprintf()
    fopen()
    fclose()
    fread()
    fwrite()

#include <stdlib.h>
    atoi()
    atol()
    atoll()
    atof()
    malloc()
    free()
    exit()
    system()

#include <string.h>
    size_t
    NULL
    strlen()
    strcmp()
    strncmp()
    strcpy()
    strncpy()
    strerror()
    strstr()
    memset()
    memcpy()

#include <stdbool.h>
    true/false

#include <fcntl.h>
    open()

#include <unistd.h>
    close()
    read()
    write()
    sleep()
    usleep()
    access()
    unlink()
    fork()
    pipe()

#include <time.h>
    struct tm
    time()
    localtime()
    localtime_r()

#include <signal.h>
    struct sigaction
    signal()
    sigaction()

#include <pthread.h>
    pthread_create()
    pthread_join()

#include <sys/ioctl.h>
    ioctl()

#include <sys/socket.h>
    socket()
    bind()
    listen()
    accept()
    sendto()
    setsockopt()

#include <sys/un.h>
    struct sockaddr_un

#include <netinet/in.h>
    #define IPPROTO_TCP
    struct sockaddr_in

#include <netinet/tcp.h>
    struct tcp_info

#include <arpa/inet.h>
    inet_addr()
    htons()

#include <sys/wait.h>
    wait()
    waitpid()

#include <sys/stat.h>
    stat()
    fstat()

#include <sys/file.h>
    flock()

#include <sys/time.h>
    struct timeval
