#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

#ifndef _DEMO5_H_                   //ifndef 就是if no define 的缩写

#define _DEMO5_H_
/****************函数声明*******************/
static void Gpio_select5(void); //gpio端口配置子程序
static void delay_loop(void);
static void Scan_Key5(void);
void demo5(void);
#endif

/****************端口宏定义*****************/
#define S1 GpioDataRegs.GPBDAT.bit.GPIOB5
#define S4 GpioDataRegs.GPBDAT.bit.GPIOB4
#define S7 GpioDataRegs.GPBDAT.bit.GPIOB3

/****************条件编译*******************/
                                                                         //(1)和(2)选择一组取消注释
#define DEMO5   1   //基础实验  跑马灯换向和暂停                        <-----(1)
#define DEMO5_1 0   //提高实验  矩阵键盘点亮特定的灯sw9熄灭所有灯        <-----(1)
//#define DEMO5   0   //基础实验  跑马灯换向和暂停                        <-----(2)
//#define DEMO5_1 1   //提高实验  矩阵键盘点亮特定的灯sw9熄灭所有灯        <-----(2)


