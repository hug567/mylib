#define mt_log(fmt, ...) printf("[mytest][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_succ(fmt, ...) printf("[mytest][success][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define mt_fail(fmt, ...) printf("[mytest][fail][%s@%d]: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define RUN_TEST(__test__) \
	do { \
		printf("--------------- %s ---------------\n", #__test__); \
		ret = __test__(); \
		if (ret < 0) { \
			mt_fail("%s failed\n", #__test__); \
		}\
	} while (0)
