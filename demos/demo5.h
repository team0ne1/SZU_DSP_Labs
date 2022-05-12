#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

#ifndef _DEMO5_H_                   //ifndef 就是if no define 的缩写

#define _DEMO5_H_
/****************函数声明*******************/
void Gpio_select5(void); //gpio端口配置子程序
void delay_loop(void);
void Scan_Key5(void);
void demo5(void);
#endif

/****************端口宏定义*****************/
#define S1 GpioDataRegs.GPBDAT.bit.GPIOB5
#define S4 GpioDataRegs.GPBDAT.bit.GPIOB4
#define S7 GpioDataRegs.GPBDAT.bit.GPIOB3

