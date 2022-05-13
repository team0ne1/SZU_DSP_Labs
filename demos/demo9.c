/********************************************************************
* �ļ�����  demo8
* ����:   ��ѹ������ʵ��

**********************************************************************/
/********************************************************************
// ��������:
//      ������ñ��J9�����1,2���Ŷ̽�
//    ͨ��ADCͨ��A0�ɼ�ģ���ѹֵ��Ȼ��ͨ��SPI����������
//    ͨ���������ʾ��ѹֵ
********************************************************************/
//#include "demo5.h"
//#include "demo7.h"
#include "demo9.h"


/*********************************************��������************************************************/
static void DisData_Trans(Uint16 data);
static void Sellect_Bit(Uint16 i);
static void Init_LEDS_Gpio(void);
static void spi_xmit(Uint16 a);
static void spi_fifo_init(void);
static void spi_init(void);
void showVin(Uint32 Res);
static void showLEDs(int data);
__interrupt void adc_int(void);
//static void delay(Uint32 t);
/*****************************************************************************************************/

/************************************������ر���*********************************************/
static unsigned char msg[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};  //���룺0~9
static unsigned char DisData_Bit[4] = {0};                                         //��Ų�ֺ����λ����
static Uint16 DisData = 1234;                                                      //��ʾ������
static Uint16 Loop = 0;

//static Uint16 counter_int = 0;
//
//static Uint16 LedBuffer[2];
//
//static Uint32 Sum=0;
static volatile  Uint16 RES=0;
static volatile  int isBusy = 0;
//static Uint32 showdata;

// ADC��������
#define ADC_MODCLK 0x3   // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)     = 25MHz
#define ADC_CKPS   0x0F   // ADC ģ��ʱ�� = HSPCLK/1      = 25MHz/(1)     = 25MHz
#define ADC_SHCLK  0x1   // ��������ʱ��                 = 2 ADC ����
#define AVG        1000  // ƽ��������ֵ
#define ZOFFSET    0x00
#define BUF_SIZE   1024  // �����������ߴ�

// ������ʹ�õ�ȫ�ֱ���
static Uint16 SampleTable[BUF_SIZE];
                                                        //ѭ��ɨ�����

/*****************************************************************************************************/

/******************************�����λѡ IO �ӿڳ�ʼ��*******************************************/

static void Init_LEDS_Gpio(void)
{
    EALLOW;


    GpioDataRegs.GPBSET.bit.GPIOB8 = 1;                     // ����ߵ�ƽ
    GpioMuxRegs.GPBMUX.bit.CAP4Q1_GPIOB8 = 0;                   // GPIOB8 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB8 = 1;                      // GPIOB8 = output

    GpioDataRegs.GPBSET.bit.GPIOB9 = 1;                     // ����ߵ�ƽ
    GpioMuxRegs.GPBMUX.bit.CAP5Q2_GPIOB9 = 0;                   // GPIOB9 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB9 = 1;                      // GPIOB9 = output

    GpioDataRegs.GPBSET.bit.GPIOB10 = 1;                    // ����ߵ�ƽ
    GpioMuxRegs.GPBMUX.bit.CAP6QI2_GPIOB10 = 0;                     // GPIOB10 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB10 = 1;                     // GPIOB10 = output

    GpioDataRegs.GPBSET.bit.GPIOB13 = 1;                    // ����ߵ�ƽ
    GpioMuxRegs.GPBMUX.bit.C4TRIP_GPIOB13 = 0;                      // GPIOB13 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB13 = 1;                     // GPIOB13 = output

    EDIS;

    RST_BIT1;//�ر��������ʾ
    RST_BIT2;
    RST_BIT3;
    RST_BIT4;
}
///*****************************************************************************************************/
//
//
///******************************�����λѡ�������ӵ�λ����λɨ�裩***************************************************/
static void Sellect_Bit(Uint16 i)
{
    switch(i)
    {
        case 0:
            RST_BIT4;                                   //�ض�����ܵ���λ
            SET_BIT1;                                   //ѡͨ����ܵ�һλ
            break;

        case 1:
            RST_BIT1;                                   //�ض�����ܵ�һλ
            SET_BIT2;                                   //ѡͨ����ܵڶ�λ
            break;

        case 2:
            RST_BIT2;                                   //�ض�����ܵڶ�λ
            SET_BIT3;                                   //ѡͨ����ܵ���λ
            break;

        case 3:
            RST_BIT3;                                   //�ض�����ܵ���λ
            SET_BIT4;                                   //ѡͨ����ܵ���λ
            break;

        default:
            break;
    }
}
/*****************************************************************************************************/

/************************** ���Ҫ��ʾ����λ�����浽����DisData_Trans����*****************************/
static void DisData_Trans(Uint16 data)
{
    DisData_Bit[3] = data / 1000;                       //ǧλ��
    DisData_Bit[2] = data % 1000 / 100 ;                //��λ��
    DisData_Bit[1] = data % 100 / 10;                   //ʮλ��
    DisData_Bit[0] = data % 10;                         //��λ��
}
/*****************************************************************************************************/



/*********************************************��ʱ����************************************************/
static void delay1(Uint32 t)
{
    Uint32 i = 0;
    for (i = 0; i < t; i++);
}
/*****************************************************************************************************/

/*********************************************Spi��ʼ��************************************************/

static void spi_init()
{
    SpiaRegs.SPICCR.all =0x004F;                            // Reset on, rising edge, 16-bit char bits
                                                            //0x000F��ӦRising Edge��0x004F��ӦFalling Edge
    SpiaRegs.SPICTL.all =0x0006;                            // Enable master mode, normal phase,
                                                            // enable talk, and SPI int disabled.
    SpiaRegs.SPIBRR =0x007F;
    SpiaRegs.SPICCR.all =0x00DF;                            // Relinquish SPI from Reset
    SpiaRegs.SPIPRI.bit.FREE = 1;                           // Set so breakpoints don't disturb xmission
}
///*****************************************************************************************************/
//
///****************************************Spiģ��FIFO����**********************************************/
static void spi_fifo_init()
{
//  ��ʼ�� SPI FIFO �Ĵ���
    SpiaRegs.SPIFFTX.all=0xE040;
    SpiaRegs.SPIFFRX.all=0x204f;
    SpiaRegs.SPIFFCT.all=0x0;
}

/*****************************************************************************************************/

/*********************************************Spi����************************************************/

static void spi_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF=a;
}
/*****************************************************************************************************/
//�ӳٺ���

static void delay_loop8()
{
    long      i;
    for (i = 0; i < 4500; i++) {}
}


void demo9(void)
{
   Uint16 i;

//   Uint32 Vin;


// ���� 1. ��ʼ��ϵͳ����:
// ����PLL, WatchDog, ʹ������ʱ��
// ��������������Դ�DSP281x_SysCtrl.c�ļ����ҵ�.
   InitSysCtrl();

// ���� 2. ��ʼ��ͨ�����������·������GPIO:
// ���������DSP281x_Gpio.cԴ�ļ��б�������
// InitGpio();  // ����ֱ�������ò���
// ��������ӦGPIOΪΪSPI��������

// �����ض���ʱ������
   EALLOW;
   SysCtrlRegs.HISPCP.all = ADC_MODCLK; // HSPCLK = SYSCLKOUT/ADC_MODCLK
   EDIS;



   //��ʼ��SPI
   EALLOW;
   GpioMuxRegs.GPFMUX.all=0x000F;   // ѡ��GPIOΪSPI����
                                    // �˿�F MUX - x000 0000 0000 1111
   EDIS;

   Init_LEDS_Gpio();


// ���� 3. ��������ж�,��ʼ���ж�������:
// ��ֹCPUȫ���ж�
   DINT;

// ��ʼ��PIE���ƼĴ��������ǵ�Ĭ��״̬.
// ���Ĭ��״̬���ǽ�ֹPIE�жϼ��������PIE�жϱ�־
// �����������DSP281x_PieCtrl.cԴ�ļ���
   InitPieCtrl();

// ��ֹCPU�жϣ����CPU�жϱ�־λ
   IER = 0x0000;
   IFR = 0x0000;

//��ʼ��PIE�ж�����������ʹ��ָ���жϷ����ӳ���ISR��
// ��Щ�жϷ����ӳ��򱻷�����DSP281x_DefaultIsr.cԴ�ļ���
// �������������DSP281x_PieVect.cԴ�ļ�����.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
  EALLOW;  // This is needed to write to EALLOW protected registers
  PieVectTable.ADCINT = &adc_int;

// ���� 4.��ʼ��Ƭ������:
   InitAdc();  // For this example, init the ADC

   spi_fifo_init();   // ��ʼ��Spi FIFO
   spi_init();        // ��ʼ�� SPI

   // ������Ҫ����ADC����
   AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;
   AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;  // ADC ģ��ʱ�� = HSPCLK/1      = 25MHz/(1)     = 25MHz
   AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  ����ģʽ
   AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;   //ADCͨ��ѡ��ADCIN0
   AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // ����Ϊ��������

   AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
   AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 1;


// Enable CPU INT1 which is connected to CPU-Timer 0:
  IER |= M_INT1;

// Enable TINT0 in the PIE: Group 1 interrupt 7
  PieCtrlRegs.PIEIER1.bit.INTx6 = 1;
//  PieCtrlRegs.PIEIER2.bit.INTx7 = 1;

// Enable global Interrupts and higher priority real-time debug events:
  EINT;   // Enable Global interrupt INTM
  ERTM;   // Enable Global realtime interrupt DBGM

// Step 5.�û�ָ�����룬ʹ���ж�:

// ��������0
//   for (i=0; i<BUF_SIZE; i++)
//   {
//     SampleTable[i] = 0;
//   }
   //������ܣ�
   spi_xmit(0xFFFF);
     //�ӳ�
      delay_loop8();

   // ��������SEQ1
//   AdcRegs.ADCTRL2.all = 0x2000;
   AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;

//   counter_int = 0;
   // ȡADC���ݲ�д��������ݱ�
   while(1)
   {
       if(!isBusy){
           showVin((AdcRegs.ADCRESULT0>>4));
       }
//       showVin((AdcRegs.ADCRESULT0>>4));
//       showVin((RES>>4));
//     for (i=0; i<AVG; i++)
//     {
//        while (AdcRegs.ADCST.bit.INT_SEQ1== 0) {} // �ȴ��ж�
//        AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
//        SampleTable[i] =((AdcRegs.ADCRESULT0>>4));
//     }
//     for (i=0;i<AVG;i++)
//     {
//      Sum+=SampleTable[i];
//      Sum=Sum/2;
//     }
//     //�����ѹ��ADֵ֮��Ĺ�ϵVin/Sum=3/4096��
//     Vin=Sum*3*10000/4096;      //�������ѹ�Ŵ�100�����Ա��ڵ�2λ��ЧС��������������㣻
//     if(Vin%10>=5)//���һλ����>=5ʱ��Ҫ���룻
//     showdata=Vin/10+1;
//     else
//     showdata=Vin/10;//Ҫ���᣻
//     printf("showdata:%d\n", showdata);
//     if(Vin>1.5){
//         printf("Vin > 1.5\n");
//     }
//       AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;
//       showVin();



   }
}

static void showVin(Uint32 Res){
    printf("showVin:Res:%d\n", Res);

    int Vin;
    int showdata = 0;

//    for (i=0;i<AVG;i++)
//    {
//     Sum+=SampleTable[i];
//     Sum=Sum/2;
//    }
    //�����ѹ��ADֵ֮��Ĺ�ϵVin/Sum=3/4096��

    Vin=Res*3*10000/4096;      //�������ѹ�Ŵ�100�����Ա��ڵ�2λ��ЧС��������������㣻
//    printf("Vin*10:%d\n", Vin);
    if(Vin%10>=5)//���һλ����>=5ʱ��Ҫ���룻
        showdata=Vin/10+1;
    else
        showdata=Vin/10;//Ҫ���᣻

    printf("showdata:%d\n", showdata);
    showLEDs(showdata);

//    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
}

static void showLEDs(int data){
    int i;
    DisData_Trans(data);
    for(i=0;i<2;i++)
    {
       for(Loop=0;Loop<4;Loop++)                               //�ֱ���ʾ��λ
       {
           Sellect_Bit(Loop);                                  //ѡ��Ҫɨ��������λ
           if(Loop==3)
               spi_xmit(msg[DisData_Bit[Loop]]+0x80);
           else
           spi_xmit(msg[DisData_Bit[Loop]]);                   //�������Ҫ��ʾ������
           delay1(1000);                                       //��ʱ������۷�Ӧʱ��
       }
       delay1(1000);
    }
}


__interrupt void adc_int(void){
    printf("adc_int\n");
//    if(counter_int<AVG){

//        AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
//        Uint32 RES;
        RES = AdcRegs.ADCRESULT0;
//        printf("RES>>4:%d\n",RES>>4);
//        showVin((AdcRegs.ADCRESULT0>>4));
        printf("(AdcRegs.ADCRESULT0>>4):%d\n",(AdcRegs.ADCRESULT0>>4));
//        SampleTable[counter_int] =((AdcRegs.ADCRESULT0>>4));

//        printf("SampleTable[counter_int]:%d\n",SampleTable[counter_int]);
//        counter_int++;
//    }else{
//        counter_int = 0;
//    }

//    showVin();
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

}

//===========================================================================
// No more.
//===========================================================================
