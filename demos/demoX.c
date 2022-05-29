//###########################################################################
//
// FILE:   demoX.c
//
// TITLE:  直流电机加减速与正反转实验
//
//
// 描述:
//
//          直流电机转速分6个档，按键1~6分别代表6个档位（转速从低到高），
//          按键7正反转，
//          按键9停止，利用按键实现直流电机控制。
//
//
#include "demoX.h"
// 使用前，声明本文件中的相关函数
void init_eva(void);
void init_evb(void);
interrupt void epwm1_isr(void);

void Scan_Key(void);
void Manage_Up(void);
void Manage_Down(void);
void Motor_Drive(void);
void Init_Port(void);
void Init_PWM_Port(void);
void Motor_changeDir(void);
/***************全局变量定义****************/
Uint16 temp=0;  //高电平时间
Uint16 Direction=0;//转速方向
Uint16 PWM_list[] = {3000, 4000, 5000, 6000, 7000, 8000}; //转速PWM

void demo10(void)
{

// 步骤 1. 初始化系统控制:
// 设置PLL, WatchDog, 使能外设时钟
// 下面这个函数可以从DSP281x_SysCtrl.c文件中找到.
   InitSysCtrl();

// 步骤 2. 初始化通用输入输出多路复用器GPIO:
// 这个函数在DSP281x_Gpio.c源文件中被定义了
// InitGpio();  // 本例直接跳过该步骤

// 本例仅初始化GPA/GPB多路复用控制寄存器
   Init_Keys_Gpio();
   Init_PWM_Port();
   Init_Port();


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
   EALLOW;  //解除寄存器保护
   PieVectTable.T1PINT = &epwm1_isr;
   EDIS;   // 添加寄存器保护

// 步骤 4.初始化片内外设:
   init_eva();
// 使能本例使用需要的中断
   //PieCtrlRegs.PIECRTL.bit.ENPIE = 1;   // 使能PIE模块
   PieCtrlRegs.PIEIER2.bit.INTx4=1;     // PIE 组 2, INT4；T1PINT
   IER = M_INT2;    // 使能 CPU INT2
   EINT;
   ERTM;

// 步骤 5. 用户特定的代码来允许中断

   EvaRegs.CMPR1 = 0;

 // 步骤6：循环函数，等待中断；
    while(1){};


}

void Key_handle(keyValue){
    if(keyValue>6){
        if(keyValue == 7) Motor_changeDir();
        if(keyValue == 9) temp = 0;
    }
    else if(keyValue>0){
        temp = PWM_list[keyValue-1];
    }
}

void init_eva()
{

// EVA 配置T1PWM, T2PWM, PWM1-PWM6
// 初始化定时器
   // 初始化EVA定时器1
   EvaRegs.T1PR = 0x1D4B;       // 开关频率取10k，由f=TCK/(T1PR+1),得到定时器1周期值=7499=0x1D4B
   EvaRegs.T1CMPR = 0x0000;     // 定时器1比较寄存器的值
   EvaRegs.T1CNT = 0x0000;      // 定时器1计数寄存器的值
   // 计数模式为增减计数
   // 定时器使能
   // 定时比较使能
   EvaRegs.T1CON.all = 0x1042;  //连续增计数模式，T1CLK=HSPCLK=75MHZ,使能定时器，使能定时比较操作




  // 初始化PWM1-PWM6相关的比较寄存器1的值
  EvaRegs.CMPR1 = 0x0000;


  // 比较动作控制，当发生比较匹配后动作输出相应电平
  // 输出引脚1，当发生 CMPR1匹配 - 输出低电平
  // 输出引脚2，当发生 CMPR1匹配 - 强制输出低电平

  EvaRegs.ACTRA.all = 0x0001;
  EvaRegs.DBTCONA.all = 0x0000; // 禁止死区
  EvaRegs.COMCONA.all = 0xA600;//使能比较操作；当T1CNT = 0或 T1CNT = T1PR（零匹配或周期匹配）重新加载比较寄存器的值；
                               //当T1CNT = 0或 T1CNT = T1PR（零匹配或周期匹配）重新加载动作寄存器的值；
                               //PWM1/2/3/4/5/6按比较逻辑输出
   // 清除周期中断标志位
   EvaRegs.EVAIFRA.bit.T1PINT=1;

   // 使能周期中断；
   EvaRegs.EVAIMRA.bit.T1PINT=1;

}

interrupt void epwm1_isr(void)
{
    struct Key_Pos keyPress = Scan_Key_Horizon_Vertical();
//    printf("key value:%d\n", keyPress.val);
    printf("speed: temp_value=%d\n", temp);
    int key_val = keyPress.val;
    if(key_val>0)//扫描是否按键按下
    {
     while(keyPress.val != 0){
         keyPress = Scan_Key_Horizon_Vertical();
     };
     Key_handle(key_val);
     // 更新CMPA和CMPB比较寄存器的值
     Motor_Drive();
    }

     PieCtrlRegs.PIEACK.all|=0x002;       // PIE应答位置1，允许下次中断
     // 清除周期中断标志位
     EvaRegs.EVAIFRA.bit.T1PINT=1;

}


/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void                              */
/*函数描述:初始化电机控制端口               */
/*------------------------------------------*/
void Init_PWM_Port(void){
    EALLOW;
    // 配置GPIO为PWM引脚
    GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0 = 1; // EVA PWM 1脚
    GpioMuxRegs.GPAMUX.bit.PWM2_GPIOA1 = 1; // EVA PWM 2脚
    EDIS;
}

void Init_Port(void)
{
    //////////////////////////////以下3个IO口设置为输出，作为列扫描////////////////////////////

    //初始化行1的GPIOB2
    EALLOW;
    GpioDataRegs.GPBCLEAR.bit.GPIOB2= 1;                                    // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM9_GPIOB2 = 0;                                     // GPIO48 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB2 = 1;                                      // GPIO48 = output

    //初始化行2的GPIOB1

    GpioDataRegs.GPBCLEAR.bit.GPIOB1 = 1;                                       // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM8_GPIOB1= 0;                                      // GPIO49 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB1 = 1;                                      // GPIO49 = output

    //初始化行3的GPIOB0

    GpioDataRegs.GPBCLEAR.bit.GPIOB0 = 1;                                       // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM7_GPIOB0 = 0;                                     // GPIO50 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB0 = 1;                                      // GPIO50 = output


    //////////////////////////////以下3个IO口设置为输入，作为行扫描////////////////////////////



    //初始化列1的GPIOB5

    GpioMuxRegs.GPBMUX.bit.PWM12_GPIOB5 = 0;                                    // 设置为一般IO口
    GpioMuxRegs.GPBDIR.bit.GPIOB5  = 0;                                     // IO口方向为输入

    //初始化列2的GPIOB4

    GpioMuxRegs.GPBMUX.bit.PWM11_GPIOB4 = 0;                                    // 设置为一般IO口
    GpioMuxRegs.GPBDIR.bit.GPIOB4  = 0;                                     // IO口方向为输入

    //初始化列3的GPIOB3

    GpioMuxRegs.GPBMUX.bit.PWM10_GPIOB3 = 0;                                    // 设置为一般IO口
    GpioMuxRegs.GPBDIR.bit.GPIOB3   = 0;                                    // IO口方向为输入

    EDIS;
}

/*------------------------------------------*/
/*形式参数：void                         */
/*返回值:void                              */
/*函数描述:电机驱动程序                       */
/*------------------------------------------*/
void Motor_Drive(void)
{
    EvaRegs.CMPR1 = temp;//改变脉宽
}

void Motor_changeDir(void){
    ////保证下面PWM1和EPWM2相互切换同时输出0电平；
//    EPwm1Regs.CMPA.half.CMPA = 0;//改变脉宽
//    EPwm1Regs.CMPB = 0;//改变脉宽
    printf("Direction:%d", Direction);
    if(Direction==0)
    {
// 设置动作限定；首先默认为转动方向为反转，这时只有PWM2输出占空比；
        EvaRegs.ACTRA.all = 0x0004;
        Direction=1;
    }
    else
    {
     // 设置动作限定；首先默认为转动方向为正转，这时只有PWM1输出占空比；
        EvaRegs.ACTRA.all = 0x0001;
        Direction=0;
    }
    temp=0;
}


//===========================================================================
// No more.
//===========================================================================

