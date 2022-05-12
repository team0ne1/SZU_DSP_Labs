//###########################################################################
//
// FILE:   demo6.c
//
// TITLE:  看门狗中断测试程序.
//
//
// 描述:
//
//
//          首先看门狗被连接到PIE的WAKEINT中断位
//          然后代码被放入一个无限循环
//
//          通过无限循环里注释的一行代码，用户可以选择喂狗
//
//
//          如果使用KickDog函数给看门狗钥匙寄存器喂狗，则不会发生WAKEINT中断
//           如果不使用KickDog喂狗的话，则会发生WAKEINT中断
//
//
//          观察变量:
//                LoopCount 为无限循环发生的次数
//                WakeCount 为WAKEINT中断发生的次数
//
//###########################################################################
// 释放日期: 2015-02-16
//###########################################################################



#include "demo6.h"

// 本例程使用的全局变量
Uint32 WakeCount;
Uint32 LoopCount;

void demo6(void)
{

// 步骤 1. 初始化系统控制:
// 设置PLL, WatchDog, 使能外设时钟
// 下面这个函数可以从DSP281x_SysCtrl.c文件中找到.
   InitSysCtrl();

// 步骤 2. 初始化通用输入输出多路复用器GPIO:
// 这个函数在DSP281x_Gpio.c源文件中被定义了
// InitGpio();  // 本例直接跳过该步骤

// 步骤 3. 清除所有中断,初始化中断向量表:
// 禁止CPU全局中断
   DINT;

// 初始化PIE控制寄存器到他们的默认状态.
// 这个默认状态就是禁止PIE中断及清除所有PIE中断标志
// 这个函数放在DSP281x_PieCtrl.c源文件里
   InitPieCtrl();

// 禁止CPU中断和清除所有CPU中断标志
   IER = 0x0000;
   IFR = 0x0000;

//初始化PIE中断向量表，并使其指向中断服务子程序（ISR）
// 这些中断服务子程序被放在了DSP281x_DefaultIsr.c源文件中
// 这个函数放在了DSP281x_PieVect.c源文件里面.
   InitPieVectTable();

// 本例中的中断重新映射到本文件中的中断服务子程序中
   EALLOW;   //解除寄存器保护
   PieVectTable.WAKEINT = &wakeint_isr;
   EDIS;   // 添加寄存器保护

// 步骤 4.初始化片内外设:
// InitPeripherals(); // 本例未使用

// 步骤 5. 用户特定的代码来允许中断

// 清除计数值
   WakeCount = 0; // 中断计数值
   LoopCount = 0; // 无限循环计数值

// 连接看门狗到PIE中断位WAKEINT
// 对整个SCSR寄存器写如0x002,使能看门狗中断并避免清除WDOVERRIDE位
   EALLOW;
   SysCtrlRegs.SCSR = BIT1;
   EDIS;

// 使能PIE WAKEINT中断：PIE1.8
// 使能CPU INT1（它连到WAKEINT）;
   PieCtrlRegs.PIECRTL.bit.ENPIE = 1;   // Enable the PIE block使能PIE模块
   PieCtrlRegs.PIEIER1.bit.INTx8 = 1;   // 使能PIE组1中断8
   IER |= M_INT1;                       // 使能 CPU INT1
   EINT;                                // 使能全局中断

// 复位看门狗计数值
   KickDog();

// 使能看门狗
   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;
   EDIS;

// 步骤 6. 无限循环，等待中断的产生
   for(;;)
   {
      LoopCount++;


      KickDog(); //默认是KickDog()函数不执行，通过去掉KickDog()函数前的//，则使用KickDog()函数；
   }


}


// 步骤 7. 中断服务子程序

interrupt void wakeint_isr(void)
{
    WakeCount++;

    // 清除组1应答位，以获得下次中断
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//===========================================================================
// No more.
//===========================================================================
