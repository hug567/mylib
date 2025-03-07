# C语言常见bug：

## 1、字符串溢出：



## 2、异常路径资源未释放：



## 3、使用free后的内存：



## 4、if/while中判断等于写成赋值：

```c
/* 等于判断写成赋值，可以将常量写在左边，编译时就可发现 */
while (battery_temp = CRITICAL_TEMP) {
    emergency_shutdown();
}
```

## 5、逻辑与写成按位与运算：

```c
if (limit_switch_A & limit_switch_B) {
    ...
}
/* 实际逻辑是判断limit_switch_A和limit_switch_B同时为真 */
if (limit_switch_A && limit_switch_B) {
    ...
}
```

## 6、8进制数当10进制：

```c
/* 0开头的数是8进制数，0123 == 83 */
int throttle = 0123;
```

## 7、函数参数为整形，传入字符串：

```c
void set_config(int temp);
/* 字符串参数生成整形：0x48494748 */
set_config('HIGH');
```

