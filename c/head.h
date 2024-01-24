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
    access()
    unlink()

#include <signal.h>
    struct sigaction
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

#include <sys/un.h>
    struct sockaddr_un

#include <netinet/in.h>
    struct sockaddr_in

#include <netinet/tcp.h>
    struct tcp_info

#include <netinet/in.h>
    #define IPPROTO_TCP

#include <arpa/inet.h>
    inet_addr()
