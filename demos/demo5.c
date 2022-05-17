//###########################################################################
//
// FILE:    demo5.c
//
// TITLE:   ��ˮ���밴��ʵ��
//
// ˵��
//
//          ���������ڻ��������������������Լ��̳��򣬵�����SW1ʱ������ƴ�������������������SW4ʱ������ƴ�������������������SW7ʱ�������ֹͣ��
//          ��ߣ�ʵ�־�����̹��ܡ�������SW1-SW8ʱ����Ӧ�����LED�Ƶ�����������SW9ʱ�����е�Ϩ��

//
// ����:
//
//          ͨ��LED���Թ۲�GPIO�����ƽ�ı仯
//
//###########################################################################
// �ͷ�����:
//###########################################################################
//#define DEMO5   1   //����ʵ��  �����
//#define DEMO5_1 0   //���ʵ��  �������

#include "demo2.h"
#include "demo5.h"
#include <stdio.h>
/***************ȫ�ֱ�������****************/
static Uint32 temp5;
static Uint32 direction;
static int stop = 0;
static int light_map[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

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

   GpioDataRegs.GPADAT.all    =0x0000;//GPIOA0-A7�����0��ʹLED1����
   GpioDataRegs.GPBDAT.all   =0xFFFF;
   GpioDataRegs.GPBDAT.all   &=0xFFFE;//GPIOB0�����0�������ø�
   direction=0;
   for(;;)
   {
       temp5=0x0001;
#if DEMO5
    if(direction%2!=0)//������ˮ�Ƶķ���
        temp5=0x0001;
    else
        temp5=0x0080;
#endif

#if DEMO5
    while(temp5!=0x0100&&temp5!=0x0000)//��������GPIOA0-A7��
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
            if(direction%2!=0)//������ˮ�Ƶķ���
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

static void delay_loop()
{
    Uint32      i;
    Uint32      j;
    for(i=0;i<4;i++)
    for (j = 0; j < 10000; j++) {}
}

/*------------------------------------------*/
/*��ʽ������void                         */
/*����ֵ:void                              */
/*��������:ɨ���ֵ                         */
/*------------------------------------------*/
static void Scan_Key5(void)
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


static void Gpio_select5(void)
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
    GpioMuxRegs.GPBDIR.all=0xFFC7;          // GPIO��B��ȫ������Ϊ�������GPIOB5����Ϊ����
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

