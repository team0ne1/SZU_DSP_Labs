//###########################################################################
//
// FILE:    demo1.c
//
// TITLE:   流水灯与按键实验 
//
// 说明
//
//          发光二极管轮流点亮，当按键SW3按下后流水
//          灯停止，再按下按键SW3后流水灯又恢复；
//
// 描述:
//
//          通过LED可以观察GPIO输出电平的变化 
//         
//###########################################################################
//
//###########################################################################


#include "demo1.h"
/***************全局变量定义****************/

Uint32 led_status = 0x0;

void demo1(void)
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
   Gpio_select1();

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

   while(1)
   {
       Uint32 temp=0x0001;

        while(temp!=0x0100)//轮流点亮GPIOA0-A7；
        {
            GpioDataRegs.GPASET.all |=temp;
            Scan_Key();
            delay_c1(10000);
            if(led_status == 0x0){
                GpioDataRegs.GPACLEAR.all |=temp;
                temp<<=1;
            }
        }
    }

} 	

void delay_c1(int t)
{
    Uint32      i;
	Uint32      j;
	for(i=0;i<4;i++)
    for (j = 0; j < t; j++);
}



void LED_Stop(void){
    led_status = ~led_status;
}


/*------------------------------------------*/
/*形式参数：void		            		*/
/*返回值:void				    			*/
/*函数描述:扫描键值             	    	*/
/*------------------------------------------*/
void Scan_Key(void)      
{

    while(S1==0){
      delay_c1(100);
      if(S1==1)
	  {
	      LED_Stop();
	      break;
	  }
	}


}


void Gpio_select1(void)
{

    Uint16 var1;
    Uint16 var2;
    Uint16 var3;

    var1= 0x0000;		// sets GPIO Muxs as I/Os
    var2= 0xFFFF;		// sets GPIO DIR as outputs
    var3= 0x0000;		// sets the Input qualifier values
   
    EALLOW;
	 
	GpioMuxRegs.GPAMUX.all=var1;
    GpioMuxRegs.GPBMUX.all=var1;   
    GpioMuxRegs.GPDMUX.all=var1;
    GpioMuxRegs.GPFMUX.all=var1;		 
    GpioMuxRegs.GPEMUX.all=var1; 
    GpioMuxRegs.GPGMUX.all=var1;
										
    GpioMuxRegs.GPADIR.all=var2;		// GPIO PORTs  as output
    GpioMuxRegs.GPBDIR.all=0xFFDF;   		// GPIO的B组全部定义为输出，除GPIOB5定义为输入
    GpioMuxRegs.GPDDIR.all=var2;
    GpioMuxRegs.GPEDIR.all=var2;		
    GpioMuxRegs.GPFDIR.all=var2; 
    GpioMuxRegs.GPGDIR.all=var2;

    GpioMuxRegs.GPAQUAL.all=var3;  		// Set GPIO input qualifier values
    GpioMuxRegs.GPBQUAL.all=var3;   
    GpioMuxRegs.GPDQUAL.all=var3;
    GpioMuxRegs.GPEQUAL.all=var3;
 
    EDIS;
     
}     
//===========================================================================
// End
//===========================================================================

