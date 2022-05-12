//###########################################################################
//
// FILE:    demo2.c
//
// TITLE:   矩阵键盘实验
//
// 说明
//
//          读取IO输入，得到按下的按键
//          采用轮询的方式，扫描按键输入。
//
//          需要注意的是，默认IO输入为高电位，即默认 B5 B4 B3 = 111;
//          扫描IO输出是低电平，检测IO输入应该检测低电平
//          列扫描：B2 B1 B0 轮流输出: 011 -> 101 -> 110
//          检测按键按下,检测低电位：
//          读取B5 B4 B3寄存器的值.
//          B5 B4 B3 = 011 -> 第一行按下
//          B5 B4 B3 = 101 -> 第二行按下
//          B5 B4 B3 = 110 -> 第三行按下
//
// 描述:
//
//
//
//###########################################################################
//
//###########################################################################


#include "demo2.h"


/***************全局变量定义****************/
Uint16 B_input;
Uint16 B_output;


int key_press[3][3];



void demo2(void)
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
   Init_Keys_Gpio();

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

   //GpioDataRegs.GPADAT.all   =0x0000;//GPIOA0-A7输出清0，使LED1灯灭
   GpioDataRegs.GPBDAT.all   =0x0;
   //GpioDataRegs.GPBDAT.all   &=0xFFFE;//GPIOB0输出清0，其他置高
//   init_key_press();
   B_input = 0x0;

   while(1){
       struct Key_Pos keyPress = Scan_Key_Horizon_Vertical();
       printf("key value:%d\n", keyPress.val);
//       Scan_Key_Horizon(1);
//       Scan_Key_Horizon(2);
   }

}

/*------------------------------------------*/
/*形式参数: void                         */
/*返回值:void                              */
/*函数描述: 初始化按键值                         */
/*------------------------------------------*/

void init_key_press(void){
    int m, n;
    for(m=0;m<3;m++){
        for(n=0;n<3;n++){
            key_press[m][n] = 0;
        }
    }
    //printf("%d %d", m, n);
}

/*------------------------------------------*/
/*形式参数: int                         */
/*返回值:void                              */
/*函数描述: 延时函数                         */
/*------------------------------------------*/

void delay_c2(int t)
{
    Uint32      i;
    Uint32      j;
    for(i=0;i<4;i++)
    for (j = 0; j < t; j++);
}


/*------------------------------------------*/
/*形式参数：void                         */
/*返回值:void                              */
/*函数描述:扫描键值                         */
/*------------------------------------------*/
int Scan_Key_Horizon(int y)
{
    int n = 0;
    B_input = 0x04;
    B_output = (0x20 >> y);
    while((B_input & 0x07) ){ //0x07:0000 0111b


        GpioDataRegs.GPBDAT.all &= ~0x07;                         //write the regs
        GpioDataRegs.GPBDAT.all |= (~B_input & 0x3F);                      //write the regs
//        GpioDataRegs.GPBCLEAR.all = B_input;
//        GpioDataRegs.GPBDAT.all = GpioDataRegs.GPBDAT.all & 0xFFF8;

        delay_c2(100);
        //print_bin(GpioDataRegs.GPBDAT.all);                     //read the regs
        if((GpioDataRegs.GPBDAT.all & B_output)==0){
//            printf("btn press");
//            printf("Horizon: y=%d; x=%d; data: %u\n", (y+1), (n+1), GpioDataRegs.GPBDAT.all);
            return n+1;
        }
        B_input = (B_input >> 1);
        n++;
        delay_c2(100);
    }
    return -1;
}


void print_bin(int number){
    int bit = sizeof(int)*8;
    int i;
    for(i = bit - 1;i >= 0;i--){
        int bin = (number & (1 << i)) >> i;
        printf("%d", bin);
    }
    printf("\n");
}

struct Key_Pos Scan_Key_Horizon_Vertical(void){
    struct Key_Pos pos1;
    int i;
    pos1.y = 0;
    pos1.val = 0;
    for(i=0; i<3; i++){
        pos1.x = Scan_Key_Horizon(i);
        if(pos1.x != -1){
            pos1.y = i ;
            pos1.val = pos1.x + pos1.y * 3;
        }
    }
    return pos1;
}

void Init_Keys_Gpio(void)
{

    EALLOW;

    //////////////////////////////以下3个IO口设置为输出，作为列扫描////////////////////////////

    //初始化行1的GPIOB2

    GpioDataRegs.GPBSET.bit.GPIOB2= 1;                                      // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM9_GPIOB2 = 0;                                     // GPIO48 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB2 = 1;                                      // GPIO48 = output

    //初始化行2的GPIOB1

    GpioDataRegs.GPBSET.bit.GPIOB1 = 1;                                     // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM8_GPIOB1= 0;                                      // GPIO49 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB1 = 1;                                      // GPIO49 = output

    //初始化行3的GPIOB0

    GpioDataRegs.GPBSET.bit.GPIOB0 = 1;                                     // Load output latch
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
    //ResetAllKY();
}
//===========================================================================
// End
//===========================================================================

