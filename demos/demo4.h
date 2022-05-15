#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

// 主函数下调用的函数，需要在主函数前申明，否则会出错
interrupt void cpu_timer0_isr(void);
void Gpio_select4(void);
void demo4(void);
