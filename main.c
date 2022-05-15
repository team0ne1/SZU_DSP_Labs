#include <stdio.h>

#include "./demos/demo1.h"
#include "./demos/demo2.h"
#include "./demos/demo3.h"
#include "./demos/demo4.h"
#include "./demos/demo5.h"
#include "./demos/demo6.h"
#include "./demos/demo7.h"
#include "./demos/demo8.h"
#include "./demos/demo9.h"


#define DEMO1 1         //LED和跑马灯 按键停止与继续跑马灯
#define DEMO2 2         //矩阵键盘
#define DEMO3 3         //串口与SPI实验 数码管
#define DEMO4 4         //中断管理和CPU计数
#define DEMO5 5         //LED和跑马灯 矩阵键盘选择功能
#define DEMO6 6         //看门狗案例程序
#define DEMO7 7         //作弊秒表
#define DEMO8 8         //模拟信号AD采集
#define DEMO8 9         //模拟信号AD采集 中断

#define RUN_DEMO  DEMO8 //选择编译的实验代码

/**
 * main.c
 */
int main(void)
{
#if    RUN_DEMO == DEMO1
    demo1();
#elif  RUN_DEMO == DEMO2
    demo2();
#elif  RUN_DEMO == DEMO3
    demo3();
#elif  RUN_DEMO == DEMO4
    demo4();
#elif  RUN_DEMO == DEMO5
    demo5();
#elif  RUN_DEMO == DEMO6
    demo6();
#elif  RUN_DEMO == DEMO7
    demo7();
#elif  RUN_DEMO == DEMO8
    demo8();
#elif  RUN_DEMO == DEMO9
    demo9();
#endif

	return 0;
}
