# 预防C语言bug：

## 1、编译选项：

- -Wall：启用一组常用的易于修改的问题警告
  - -Waddress：检查是否存在可疑的内存地址使用
  - -Wforamt：检查标准库函数使用格式是否正确
  - -Wunused-function：对定义但未使用的静态函数告警
  - -Wswitch：switch处理枚举类型，判断分支是否包含所有枚举值；
  - -Wunused-variable：对声明但未使用的变量告警；
  - -Wunused-but-set-variable：对声明且被赋值但未使用的变量告警；
  - -Warray-bounds=1：检查数组越界，需要启用-ftree-vrp
- -Wextra：开启-Wall之外的一些检查
  - -Wunused-parameter：对未使用的函数参数告警
  - -Wmissing-field-initializers：结构体未初始化完全时告警
  - -Wcast-function-type：函数被强转为不兼容的函数指针时告警
  - -Wempty-body：有空的if/else/do-while语句时告警
  - -Wsign-compare：比较有符号数和无符号数时告警
- -Werror：将被视为告警的问题提升为错误
- -Woctal-literal：使用0开头的8进制常量时，会触发warning；可使用以下代码禁用警告：
```c
#pragma GCC diagnostic ignored "-Woctal-literal"
```

## 2、静态分析工具：

- Clang-Tidy：
- MISRA-C：