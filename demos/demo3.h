#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File
/********************************宏定义数码管位选 IO 接口*******************************************/
#define  SET_BIT4   GpioDataRegs.GPBSET.bit.GPIOB8   = 1        //与外设板 8_LEDS 端子的 IOB8 对应
#define  RST_BIT4   GpioDataRegs.GPBCLEAR.bit.GPIOB8 = 1        //与外设板 8_LEDS 端子的 IOB8 对应
#define  SET_BIT3   GpioDataRegs.GPBSET.bit.GPIOB9   = 1        //与外设板 8_LEDS 端子的 IOB9 对应
#define  RST_BIT3   GpioDataRegs.GPBCLEAR.bit.GPIOB9 = 1        //与外设板 8_LEDS 端子的 IOB9 对应
#define  SET_BIT2   GpioDataRegs.GPBSET.bit.GPIOB10  = 1        //与外设板 8_LEDS 端子的 IOB10 对应
#define  RST_BIT2   GpioDataRegs.GPBCLEAR.bit.GPIOB10 = 1       //与外设板 8_LEDS 端子的 IOB10 对应
#define  SET_BIT1   GpioDataRegs.GPBSET.bit.GPIOB13  = 1        //与外设板 8_LEDS 端子的 IOB13 对应
#define  RST_BIT1   GpioDataRegs.GPBCLEAR.bit.GPIOB13 = 1       //与外设板 8_LEDS 端子的 IOB13 对应
/*****************************************************************************************************/


/*********************************************函数申明************************************************/
//void delay(Uint32 t);
void DisData_Trans(Uint16 data);
void Sellect_Bit(Uint16 i);
void Init_LEDS_Gpio(void);
void spi_xmit(Uint16 a);
void spi_fifo_init(void);
void spi_init(void);
void delay1(unsigned long int t);
void demo3(void);
/*****************************************************************************************************/
