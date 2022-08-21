# 共享内存：

## 1、用户态接口：

```c
#include <sys/shm.h>

/*
 * 功能：创建或查找共享内存
 *   key: 键值，unsigned int类型，是共享内存在系统中的编号，不同共享内存编号不同
 *   size：共享内存大小
 *   shm_flg：共享内存访问权限
 *     IPC_CREAT：创建或查找共享内存
 *     IPC_CREAT | IPC_EXCL：创建共享内存，已存在则报错
 * 返回值：成功返回共享内存标识符，失败返回-1
 */
int shmget(key_t ket, size_t size, int shm_flg);

/*
 * 功能：映射共享内存到当前进程地址空间
 *   shm_id：共享内存标识符
 *   shm_addr：
 *     NULL：由系统选择映射的虚址
 *   shm_addr & shm_flg：
 *     shm_addr != NULL, shm_flg & SHM_RND != 0：va = shm_addr - ((uintptr_t)shm_addr % SHMLBA)
 *     shm_addr != NULL, shm_flg & SHM_RND == 0：va = shm_addr
 *   shm_flg：
 *     shm_flg & SHM_RDONLY != 0：可读
 *     shm_flg & SHM_RDONLY == 0：可读可写
 * 返回值：成功返回映射后的虚址，失败返回(void *)-1
 */
void *shmat(int shm_id, const void *shm_addr, int shm_flg);

/*
 * 功能：解除共享内存映射
 *   shm_addr：共享内存映射的虚址
 * 返回值：成功返回0，失败返回-1
 */
int shmdt(const void *shm_addr);

/*
 * 功能：共享内存控制
 *   shm_id：共享内存标识符
 *   cmd：
 *     IPC_STAT：获取共享内存管理信息并存入buf
 *     IPC_SET：使用buf中的信息设置共享内存
 *     IPC_RMID：删除共享内存
 *   buf：共享内存管理结构
 * 返回值：成功返回0，失败返回-1
 */
int shmctl(int shm_id, int cmd, struct shmid_ds *buf);

```

