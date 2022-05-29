#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
#include <stdio.h>

#include "demo2.h"

/****************¶Ë¿Úºê¶¨Òå*****************/
#define Up_Key GpioDataRegs.GPBDAT.bit.GPIOB5
#define Down_Key GpioDataRegs.GPBDAT.bit.GPIOB4
#define Direction_Key GpioDataRegs.GPBDAT.bit.GPIOB3

void demo10(void);
