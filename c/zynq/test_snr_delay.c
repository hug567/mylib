/*
 * 测试猫输出snr延迟代码参考
 *    1、在自动或手动模式下，让天线对准卫星，接收最大
 *    2、按正弦变化修改AngleDes，让天线缓慢左右摆动
 *    3、通过debug_info_t记录天线的AngleDes和snr值，AngleDes的正弦0值点，和snr
 *       最大值点之间的差值，就是猫输出snr的延迟
 * 2025-03-03
 */


/*
 * 2025-03-03：
 * 以下代码在安装天际易达猫的S450B中做过实测，代码放在point_sate_auto()中，待
 * 天线自动找星后，延时20s，之后让天线左右摆动，AngleDes按正弦曲线变化
 */
/***** hx-debug ***************************************************************/
static u32 g_hx_count = 0; /* hx-debug */
static u32 g_hx_index = 0; /* hx-debug */
static int g_hx_flag = 0; /* hx-debug */
static float g_hx_init_angle_des = 0; /* hx-debug */
/***** hx-debug ***************************************************************/

/***** hx-debug ***************************************************************/
	float new_des;
	float max_count = 20000; /* 一个周期的数据点数，点数越大，正弦扫描的越慢 */
	if (g_hx_count < 2000) {
		g_hx_count++;
	} else {
		if (g_hx_flag == 0) {
			g_hx_flag = 1;
			g_hx_init_angle_des = angle_ptr->AngleDes;
		}

		if (g_hx_index >= max_count) {
			g_hx_index = 0;
		}
		new_des = g_hx_init_angle_des + 30.0f * sin(g_hx_index * 2.0f * M_PI / max_count);
		angle_ptr->AngleDes = new_des;
		Xil_DCacheFlushRange((INTPTR)angle_ptr, sizeof(AntennaAngle));
#ifdef CONFIG_MOTOR_TYPE_LK
		set_pos_goal(angle_ptr->AngleDes);
#endif
/***** hx-debug ***************************************************************/

		g_hx_index++;
		return;
	}
