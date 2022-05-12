//###########################################################################
//
// FILE:    Example_281xGpioToggle.c
//
// TITLE:   流水灯与按键实验
//
// 说明
//
//          基础：基于基础程序给出程序，设计线性键盘程序，当按下SW1时，跑马灯从右向左流动；当按下SW4时，跑马灯从左向右流动；当按下SW7时，跑马灯停止。
//          提高：实现矩阵键盘功能。当按下SW1-SW8时，对应号码的LED灯点亮，当按下SW9时，所有灯熄灭。

//
// 描述:
//
//          通过LED可以观察GPIO输出电平的变化
//
//###########################################################################
// 释放日期: 2015.01.02
//###########################################################################
#define DEMO5   1
#define DEMO5_1 0

#include "demo2.h"
#include "demo5.h"
#include <stdio.h>
/***************全局变量定义****************/
Uint32 temp5;
Uint32 direction;
int stop = 0;
int light_map[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

void demo5(void)
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP281x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP281x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// For this example use the following configuration:
   Gpio_select5();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP281x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP281x_DefaultIsr.c.
// This function is found in DSP281x_PieVect.c.
   InitPieVectTable();


// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP281x_InitPeripherals.c
// InitPeripherals(); // Not required for this example

// Step 5. User specific code:

   GpioDataRegs.GPADAT.all    =0x0000;//GPIOA0-A7输出清0，使LED1灯灭
   GpioDataRegs.GPBDAT.all   =0xFFFF;
   GpioDataRegs.GPBDAT.all   &=0xFFFE;//GPIOB0输出清0，其他置高
   direction=0;
   for(;;)
   {
       temp5=0x0001;
#if DEMO5
    if(direction%2!=0)//控制流水灯的方向
        temp5=0x0001;
    else
        temp5=0x0080;
#endif

#if DEMO5
    while(temp5!=0x0100&&temp5!=0x0000)//轮流点亮GPIOA0-A7；
#elif DEMO5_1
    while(1)
#endif
    {
        printf("temp5:%u; stop:%d; direction:%u\n", temp5, stop, direction);
        Scan_Key5();
//        delay_loop();

//        GpioDataRegs.GPASET.all |=temp5;
#if DEMO5
        GpioDataRegs.GPASET.all |=temp5;
        delay_loop();
        GpioDataRegs.GPACLEAR.all |=temp5;
#endif

#if DEMO5
        if(!stop){
            if(direction%2!=0)//控制流水灯的方向
                temp5<<=1;
            else
                temp5>>=1;
        }
#elif DEMO5_1
        if(stop){
            GpioDataRegs.GPACLEAR.all = 0x0FF;
            continue;
        }
        GpioDataRegs.GPACLEAR.all = 0x0FF;
        GpioDataRegs.GPASET.all = temp5;
        delay_loop();

#endif



    }
  }

}

void delay_loop()
{
    Uint32      i;
    Uint32      j;
    for(i=0;i<4;i++)
    for (j = 0; j < 10000; j++) {}
}

/*------------------------------------------*/
/*形式参数：void                         */
/*返回值:void                              */
/*函数描述:扫描键值                         */
/*------------------------------------------*/
void Scan_Key5(void)
{
    struct Key_Pos pos;


    pos = Scan_Key_Horizon_Vertical();

#if DEMO5
    if(pos.val == 1){
        stop = 0;
        direction = 1;
    }
    else if(pos.val == 4){
        stop = 0;
        direction = 0;
    }
    else if(pos.val == 7){
        stop = 1;
    }
    printf("keyval: %d\n", pos.val);

#elif DEMO5_1

    printf("keyval: %d\n", pos.val);
    if(pos.val != 0){
        stop = 0;
        temp5 = light_map[pos.val-1];
    }
    if(pos.val == 9){
        stop = 1;
    }

#endif
}


void Gpio_select5(void)
{

    Uint16 var1;
    Uint16 var2;
    Uint16 var3;

    var1= 0x0000;       // sets GPIO Muxs as I/Os
    var2= 0xFFFF;       // sets GPIO DIR as outputs
    var3= 0x0000;       // sets the Input qualifier values

    EALLOW;

    GpioMuxRegs.GPAMUX.all=var1;
    GpioMuxRegs.GPBMUX.all=var1;
    GpioMuxRegs.GPDMUX.all=var1;
    GpioMuxRegs.GPFMUX.all=var1;
    GpioMuxRegs.GPEMUX.all=var1;
    GpioMuxRegs.GPGMUX.all=var1;

    GpioMuxRegs.GPADIR.all=var2;        // GPIO PORTs  as output
    GpioMuxRegs.GPBDIR.all=0xFFC7;          // GPIO的B组全部定义为输出，除GPIOB5定义为输入
    GpioMuxRegs.GPDDIR.all=var2;
    GpioMuxRegs.GPEDIR.all=var2;
    GpioMuxRegs.GPFDIR.all=var2;
    GpioMuxRegs.GPGDIR.all=var2;

    GpioMuxRegs.GPAQUAL.all=var3;       // Set GPIO input qualifier values
    GpioMuxRegs.GPBQUAL.all=var3;
    GpioMuxRegs.GPDQUAL.all=var3;
    GpioMuxRegs.GPEQUAL.all=var3;

    EDIS;

}
//===========================================================================
// No more.
//===========================================================================

