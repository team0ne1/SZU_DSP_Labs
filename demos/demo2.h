#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include <stdio.h>
/****************�˿ں궨��*****************/


/****************��������*******************/
void demo2(void);
void Init_Keys_Gpio(void); //gpio�˿������ӳ���
static void delay_c2(int);
static void Scan_Key(void);
static void LED_Stop(void);
void print_bin(int number);
struct Key_Pos Scan_Key_Horizon_Vertical(void);


#ifndef _DEMO2_H_         //ifndef ����if no define ����д

#define _DEMO2_H_
struct Key_Pos {
    int x;
    int y;
    int val;
};
#endif


