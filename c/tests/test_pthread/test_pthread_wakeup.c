/*
 * 测试：阻塞与唤醒线程
 * 2023-09-09
 */
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#define log_info(fmt, ...) \
	printf("[INFO][%s:%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

int g_flag = 0;
int g_count = 0;
pthread_cond_t g_cond;
pthread_mutex_t g_mutex;

//子线程
void *thread_func(void *data)
{
	int internal_s = *((int *)data);

	while (true) {
		pthread_mutex_lock(&g_mutex);
		if (g_flag == 1) {
			log_info("thread will sleep\n");
			pthread_cond_wait(&g_cond, &g_mutex);
		}
		pthread_mutex_unlock(&g_mutex);
		log_info("thread run times: %d\n", g_count);
		sleep(internal_s);
		g_count++;
	}

	return NULL;
}

//主进程
int main(void)
{
	int ret;
	int internal_s = 3;
	pthread_t thread;

	pthread_mutex_init(&g_mutex, NULL);
	pthread_cond_init(&g_cond, NULL);

	ret = pthread_create(&thread, NULL, thread_func, &internal_s);
	if (ret < 0) {
		log_info("pthread create failed\n");
		return -1;
	}
	log_info("main will sleep 9s\n");
	sleep(9);
	log_info("main finish sleep\n");

	log_info("main will put thread to sleep\n");
	//休眠线程
	pthread_mutex_lock(&g_mutex);
	g_flag = 1;
	pthread_mutex_unlock(&g_mutex);
	sleep(9);
	log_info("main finish sleep\n");

	log_info("main will wake up thread\n");
	//唤醒线程
	pthread_mutex_lock(&g_mutex);
	g_flag = 0;
	pthread_cond_signal(&g_cond);
	pthread_mutex_unlock(&g_mutex);
	sleep(9);
	log_info("main finish sleep, will exit\n");

	return 0;
}
