# 深圳大学 机电学院 2022年春 DSP课程实验



## 程序与实验对照

demo1:(3) LED和跑马灯 按键停止与继续跑马灯

demo2:(5) 矩阵键盘

demo3:(1) 串口与SPI实验 数码管

demo4:(2) 中断管理和CPU计数 

demo5:(3) LED和跑马灯换向 和 矩阵键盘选择灯亮 两个实验

demo6:(4) 看门狗

demo7:(6) 作弊秒表

demo8:(7) 模拟信号AD采集, 0-3V电压表; 使用扫描法

demo9:(7) 模拟信号AD采集, 0-3V电压表; 使用中断



## 运行

main.c文件中
修改 `#define RUN_DEMO  DEMOx` 的 `x` 为数字

demo5较特殊：

修改 `demo5.h` 文件中的条件编译参数为

```c
#define DEMO5   1   //基础实验  跑马灯换向和暂停               
#define DEMO5_1 0   //...   
```

或者

~~~c
#define DEMO5   0   //...       
#define DEMO5_1 1   //提高实验  矩阵键盘点亮特定的灯sw9熄灭所有灯     
~~~

实现不同实验代码的编译



**Note:** 
不足：本工程文件为GB2312编码，如果出现中文乱码请在编辑器中切换编码



## 环境

Code Composer Studio 
 Version: 11.2.0.00007 

OS: Windows 10, v.10.0, x86_64 / win32
GB2312

## 实验列表

1. 串口与SPI实验 
2. 中断管理和CPU计数
3. LED和跑马灯
4. 看门狗
5. 矩阵键盘
6. 作弊秒表
7. 模拟信号AD采集 
8. EV实验 （未完成）
9. PWM控制电机 （未完成）