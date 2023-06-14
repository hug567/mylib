## 1、tick：

* 内核使用struct tick_device描述系统中的tick设备；
  * 系统为每个cpu建立一个local tick device；
  * 选择一个作为global tick device，用于更新jiffies、wall time、平均负载等；
  * broadcast device；
* tick可工作在两种模式下：周期性tick模式、one shot模式；
  * tickless；
  * 高精度timer；

## 2、idle：

* tickless idle（dyntick）模式：不向没有任务的CPU发送定时器中断