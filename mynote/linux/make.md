## 1、常见变量：

### 1.1、系统变量：

```C
$@        //目标文件
$<        //第一个依赖文件
$^        //所有依赖文件
```

### 1.2、make参数：

```c
-C dir, --directory=dir						//执行前先进入 dir 目录
```

### 1.3、赋值符号：

```c
=         //使用时赋值，直到定义变量被使用时，等号右边的内容才会被展开
:=        //立即赋值，在定义变量处，等号右边立即被被展开
?=        //条件赋值，只有当变量没有被定义过时，才进行赋值，适合处理环境变量
+=        //追加赋值
```

### 1.4、FORCE：

```c
FORCE    //伪目标，一般无依赖和可执行命令
  //如果一个规则没有命令或者依赖，且其目标不是一个存在的文件名，执行此规则时，目标总会被认为是最新的；
  //也就是说，这个规则一旦被执行，make 就认为它所表示的目标已经被更新过；
  //当将这样的目标作为一个规则的依赖时，该规则定义的命令总会被执行。
```

### 1.5、PHONY：

```c
伪目标：Makefile中目标默认是文件，PHONY指定的目标为伪目标，.PHONY定义的目标总是会执行

1、对于普通目标，若执行目录中有与目标同名的文件，make将拒绝执行该目标；
2、.PHONY包含的目标，若执行目录中有与目标同名的文件，该目标仍会被执行；
```

### 1.6、make环境变量

```c
SHELL           //当前使用shell
CURDIR          //当前make文件所在路径
MAKEFLAGS       //make参数
MAKECMDGOALS    //make命令行指定的目标
```

## 2、常用函数

```c
TEXT            //可使用空格、TAB、回车、换行分割
%               //通配符，匹配任意字符串

filter          //$(filter PATTERN…,TEXT) 过滤掉字串“TEXT”中所有不符合“PATTERN”的单词
filter-out      //$(filter-out PATTERN…,TEXT) 过滤掉字串“TEXT”中所有符合“PATTERN”的单词
findstring      //$(findstring FIND,IN) 如果在“IN”之中存在“FIND”，返回“FIND”，否则返回空
subst           //$(subst FROM,TO,TEXT) 将字串“TEXT”中的“FROM”替换为“TO”
patsubst        //$(patsubst PATTERN,REPLACEMENT,TEXT) 将“TEXT”中符合“PATTERN”的替换为“REPLACEMENT”
words           //$(word N,TEXT) 返回字串“TEXT”中第“N”个单词
firstword       //$(firstword TEXT) 返回字字串“TEXT”中的第一个单词
origin          //$(origin <variable>) 获取变量来源，有："undefined", "enviroment", "default", "file", "command line", "override", "automatic"
dir             //$(dir TEXT) 取目录，返回TEXT中最后一个/之前的部分，包括/，TEXT中无/时返回./
notdir          //$(dir TEXT) 取文件，返回TEXT中最后一个/之后的部分，不包括/，最后一个字符为/时返回空格
basename        //$(basename TEXT) 取文件名前缀，返回TEXT最后一个.之前的部分，不包括.
suffix          //$(suffix TEXT) 取后缀，返回TEXT最后一个.之后的部分，包括.
strip           //$(strip TEXT) 去除TEXT头尾空字符，并将中间多个空字符合并为一个空字符
call            //$(call VARIABLE,PARAM1,PARAM2,...) 调用自定义函数
shell           //$(shell cmd) 执行shell命令
if              //$(if CONDITION,THEN-PART[,ELSE-PART]) CONDITION非空执行THEN，否则执行ELSE
foreach         //$(foreach <var>,<list>,<text>) 把参数<list>中的项逐一取出放到参数<var>所指定的变量中，然后再执行<text>所包含的表达式
wildcard        //$(wildcard PATTERN...) 扩展通配符，被展开为已经存在的、使用空格分开的、匹配此模式的所有文件列表
```

