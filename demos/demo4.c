//###########################################################################
//
// FILE:    demo4.c
//
// TITLE:   CPU定时器0控制LED闪烁实验
//
// ASSUMPTIONS:
//
//          This program requires the DSP281x V1.00 header files.
//          As supplied, this project is configured for "boot to H0" operation.
//
//          Other then boot mode configuration, no other hardware configuration
//          is required.
//
// 描述:
//
//          本例配置CPU定时器0每隔500ms定时进入中断
//          LED点亮1个时间周期，熄灭5个时间周期
//
//          观察变量:
//                 CpuTimer0.InterruptCount和LED
//
//###########################################################################
//
//###########################################################################


#include "demo4.h"
#include <stdio.h>
int counter = 0;
Uint16 light_status = 0x0;
int *counter_p = &counter;
void demo4(void)
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP281x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP281x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// 本例需要使用GPIO，所以这里需要对其进行初始化
   Gpio_select4();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
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

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &cpu_timer0_isr;


   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP281x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   InitCpuTimers();   // For this example, only initialize the Cpu Timers

// Configure CPU-Timer 0 to interrupt every second:
// 100MHz CPU Freq, 1 second Period (in uSeconds)
   ConfigCpuTimer(&CpuTimer0, 150, 500000);

//   ConfigCpuTimer(&CpuTimer0, 150, 500000);
   StartCpuTimer0();


// Step 5. User specific code, enable interrupts:


// Enable CPU INT1 which is connected to CPU-Timer 0:
   IER |= M_INT1;

// Enable TINT0 in the PIE: Group 1 interrupt 7
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
   PieCtrlRegs.PIEIER2.bit.INTx7 = 1;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

// Step 6. IDLE loop. Just sit and loop forever (optional):
   for(;;){};

}


__interrupt void cpu_timer0_isr(void)
{

    GpioDataRegs.GPACLEAR.all = 0x00FF;
    counter++;
    if(counter == 5){
        counter = 0;
        GpioDataRegs.GPASET.all = 0x00FF;
    }
    printf("timer0:%d\n", counter);
   CpuTimer0.InterruptCount++;

   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


void Gpio_select4(void)
{

    Uint16 var1;
    Uint16 var2;
    Uint16 var3;

    var1= 0x0000;       // 设置GPIO为I/O口
    var2= 0xFFFF;       // 设置GPIO为输出口
    var3= 0x0000;       // 设置输入限定的值

    EALLOW;

    GpioMuxRegs.GPAMUX.all=var1;
    GpioMuxRegs.GPBMUX.all=var1;
    GpioMuxRegs.GPDMUX.all=var1;
    GpioMuxRegs.GPFMUX.all=var1;
    GpioMuxRegs.GPEMUX.all=var1;
    GpioMuxRegs.GPGMUX.all=var1;

    GpioMuxRegs.GPADIR.all=var2;
    GpioMuxRegs.GPBDIR.all=var2;        // 选择所有的GPIO为输出口
    GpioMuxRegs.GPDDIR.all=var2;
    GpioMuxRegs.GPEDIR.all=var2;
    GpioMuxRegs.GPFDIR.all=var2;
    GpioMuxRegs.GPGDIR.all=var2;

    GpioMuxRegs.GPAQUAL.all=var3;       // 设置GPIO输入限定值
    GpioMuxRegs.GPBQUAL.all=var3;
    GpioMuxRegs.GPDQUAL.all=var3;
    GpioMuxRegs.GPEQUAL.all=var3;

    GpioDataRegs.GPADAT.all = 0x0000;

    EDIS;

}
//===========================================================================
// No more.
//===========================================================================
