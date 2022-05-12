// TI File $Revision: /main/2 $
// Checkin $Date: April 29, 2005   11:08:24 $
//###########################################################################
//
// FILE:   DSP281x_Spi.c
//
// TITLE:  DSP281x SPI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP281x C/C++ Header Files V1.20 $
// $Release Date: July 27, 2009 $
//###########################################################################

#include "DSP281x_Device.h"     // DSP281x Headerfile Include File
#include "DSP281x_Examples.h"   // DSP281x Examples Include File

//---------------------------------------------------------------------------
// InitSPI: 
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitSpi(void)
{
   // Initialize SPI-A:

   //tbd...
 
}
//////////////////////////////////////////////////////////////
void InitSpi1(void)
{
	

	
	
	// Initialize SPI-A:
	EALLOW;
	GpioMuxRegs.GPFMUX.all = 0x3fff;
	EDIS;

	SpiaRegs.SPICCR.all = 0x4f;//0x0f;///进入初始状态，数据在上升沿输出，自测禁止，16位数据模式
	
	SpiaRegs.SPICTL.all =0x06; //0x0e;   //主动模式，禁止中断
	
	SpiaRegs.SPIBRR = 0x3B;//波特率 = LSPCLK/（SPIBRR+1）= 30/60 = 0.5M
	
	SpiaRegs.SPICCR.all = 0xcf;//0x8f; //退出初始状态
	

//	PieCtrl.PIEIER6.bit.INTx1 = 1;
//	PieCtrl.PIEIER6.bit.INTx2 = 1;
	//tbd...
	//tbd...
	
}
void InitSpi2(void)
{
	// Initialize SPI-A:
	EALLOW;
	GpioMuxRegs.GPFMUX.all = 0x000F;//1--funtion device  0--IO
	EDIS;

	SpiaRegs.SPICCR.all = 0x07;///进入初始状态，数据在上升沿输出，自测禁止，8位数据模式
//	SpiaRegs.SPICCR.all = 0x47;///	
	SpiaRegs.SPICTL.all = 0x0E;   //主动模式，禁止中断
//	SpiaRegs.SPICTL.all = 0x06;   //主动模式，禁止中断	
	SpiaRegs.SPIBRR = 0x1D;//波特率 = LSPCLK/（SPIBRR+1）= 30/30 = 1M
	
	SpiaRegs.SPICCR.all = 0x87; //退出初始状态
	

//	PieCtrl.PIEIER6.bit.INTx1 = 1;
//	PieCtrl.PIEIER6.bit.INTx2 = 1;
	//tbd...
	//tbd...
	
}
////////////////////////////////////////////////////////////////////////////////////////
unsigned int Spi_TxReady(void)
{
	unsigned int i;
	if(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1)
	{
		i = 0;
	}
	else
	{
		i = 1;
	}
	return(i);
}

unsigned int Spi_RxReady(void)
{
	unsigned int i;
	if(SpiaRegs.SPISTS.bit.INT_FLAG == 1)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	return(i);	
}

interrupt void SPIRXINTA_ISR(void);   // SPI
interrupt void SPITXINTA_ISR(void);   // SPI
//===========================================================================
// No more.
//===========================================================================
