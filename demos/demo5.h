#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

#ifndef _DEMO5_H_                   //ifndef ����if no define ����д

#define _DEMO5_H_
/****************��������*******************/
static void Gpio_select5(void); //gpio�˿������ӳ���
static void delay_loop(void);
static void Scan_Key5(void);
void demo5(void);
#endif

/****************�˿ں궨��*****************/
#define S1 GpioDataRegs.GPBDAT.bit.GPIOB5
#define S4 GpioDataRegs.GPBDAT.bit.GPIOB4
#define S7 GpioDataRegs.GPBDAT.bit.GPIOB3

/****************��������*******************/
                                                                         //(1)��(2)ѡ��һ��ȡ��ע��
#define DEMO5   1   //����ʵ��  ����ƻ������ͣ                        <-----(1)
#define DEMO5_1 0   //���ʵ��  ������̵����ض��ĵ�sw9Ϩ�����е�        <-----(1)
//#define DEMO5   0   //����ʵ��  ����ƻ������ͣ                        <-----(2)
//#define DEMO5_1 1   //���ʵ��  ������̵����ض��ĵ�sw9Ϩ�����е�        <-----(2)


