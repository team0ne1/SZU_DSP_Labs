#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include <stdio.h>
/****************端口宏定义*****************/


/****************函数声明*******************/
void demo2(void);
void Init_Keys_Gpio(void); //gpio端口配置子程序
void delay_c2(int);
void Scan_Key(void);
void LED_Stop(void);
void init_key_press(void);
struct Key_Pos Scan_Key_Horizon_Vertical(void);


#ifndef _DEMO2_H_         //ifndef 就是if no define 的缩写

#define _DEMO2_H_
struct Key_Pos {
    int x;
    int y;
    int val;
};
#endif


