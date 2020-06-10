## 1、命名：
---
* **局部变量**：小驼峰
  ```c
  char ch;
  int strLen;
  ````
* **函数名、结构名**：大驼峰
  ```c
  int Add(int x, int y);
  struct Student {
      char *name,
      int class,
      int age,
  };
  ````
## 2、语句
---
- **if语句：**
  ```c
  if (conditidon) {
      DoSomeThing(a, b, c, d);
  } else {
      DoOtherThing(e, f, g, h);
  }
  ````
- **while语句：**
  ```c
  while (conditidon) {
      DoSomeThing(a, b, c, d);
  }

  do {
      DoSomeThing(a, b, c, d);
  } while (condition);
  ````