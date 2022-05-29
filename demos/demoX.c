//###########################################################################
//
// FILE:   demoX.c
//
// TITLE:  ֱ������Ӽ���������תʵ��
//
//
// ����:
//
//          ֱ�����ת�ٷ�6����������1~6�ֱ����6����λ��ת�ٴӵ͵��ߣ���
//          ����7����ת��
//          ����9ֹͣ�����ð���ʵ��ֱ��������ơ�
//
//
#include "demoX.h"
// ʹ��ǰ���������ļ��е���غ���
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
/***************ȫ�ֱ�������****************/
Uint16 temp=0;  //�ߵ�ƽʱ��
Uint16 Direction=0;//ת�ٷ���
Uint16 PWM_list[] = {3000, 4000, 5000, 6000, 7000, 8000}; //ת��PWM

void demo10(void)
{

// ���� 1. ��ʼ��ϵͳ����:
// ����PLL, WatchDog, ʹ������ʱ��
// ��������������Դ�DSP281x_SysCtrl.c�ļ����ҵ�.
   InitSysCtrl();

// ���� 2. ��ʼ��ͨ�����������·������GPIO:
// ���������DSP281x_Gpio.cԴ�ļ��б�������
// InitGpio();  // ����ֱ�������ò���

// ��������ʼ��GPA/GPB��·���ÿ��ƼĴ���
   Init_Keys_Gpio();
   Init_PWM_Port();
   Init_Port();


// ���� 3. ��������ж�,��ʼ���ж�������:
// ��ֹCPUȫ���ж�
   DINT;

// ��ʼ��PIE���ƼĴ��������ǵ�Ĭ��״̬.
// ���Ĭ��״̬���ǽ�ֹPIE�жϼ��������PIE�жϱ�־
// �����������DSP281x_PieCtrl.cԴ�ļ���
   InitPieCtrl();

// ��ֹCPU�жϺ��������CPU�жϱ�־
   IER = 0x0000;
   IFR = 0x0000;

//��ʼ��PIE�ж���������ʹ��ָ���жϷ����ӳ���ISR��
// ��Щ�жϷ����ӳ��򱻷�����DSP281x_DefaultIsr.cԴ�ļ���
// �������������DSP281x_PieVect.cԴ�ļ�����.
   InitPieVectTable();

   // �����е��ж�����ӳ�䵽���ļ��е��жϷ����ӳ�����
   EALLOW;  //����Ĵ�������
   PieVectTable.T1PINT = &epwm1_isr;
   EDIS;   // ��ӼĴ�������

// ���� 4.��ʼ��Ƭ������:
   init_eva();
// ʹ�ܱ���ʹ����Ҫ���ж�
   //PieCtrlRegs.PIECRTL.bit.ENPIE = 1;   // ʹ��PIEģ��
   PieCtrlRegs.PIEIER2.bit.INTx4=1;     // PIE �� 2, INT4��T1PINT
   IER = M_INT2;    // ʹ�� CPU INT2
   EINT;
   ERTM;

// ���� 5. �û��ض��Ĵ����������ж�

   EvaRegs.CMPR1 = 0;

 // ����6��ѭ���������ȴ��жϣ�
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

// EVA ����T1PWM, T2PWM, PWM1-PWM6
// ��ʼ����ʱ��
   // ��ʼ��EVA��ʱ��1
   EvaRegs.T1PR = 0x1D4B;       // ����Ƶ��ȡ10k����f=TCK/(T1PR+1),�õ���ʱ��1����ֵ=7499=0x1D4B
   EvaRegs.T1CMPR = 0x0000;     // ��ʱ��1�ȽϼĴ�����ֵ
   EvaRegs.T1CNT = 0x0000;      // ��ʱ��1�����Ĵ�����ֵ
   // ����ģʽΪ��������
   // ��ʱ��ʹ��
   // ��ʱ�Ƚ�ʹ��
   EvaRegs.T1CON.all = 0x1042;  //����������ģʽ��T1CLK=HSPCLK=75MHZ,ʹ�ܶ�ʱ����ʹ�ܶ�ʱ�Ƚϲ���




  // ��ʼ��PWM1-PWM6��صıȽϼĴ���1��ֵ
  EvaRegs.CMPR1 = 0x0000;


  // �Ƚ϶������ƣ��������Ƚ�ƥ����������Ӧ��ƽ
  // �������1�������� CMPR1ƥ�� - ����͵�ƽ
  // �������2�������� CMPR1ƥ�� - ǿ������͵�ƽ

  EvaRegs.ACTRA.all = 0x0001;
  EvaRegs.DBTCONA.all = 0x0000; // ��ֹ����
  EvaRegs.COMCONA.all = 0xA600;//ʹ�ܱȽϲ�������T1CNT = 0�� T1CNT = T1PR����ƥ�������ƥ�䣩���¼��رȽϼĴ�����ֵ��
                               //��T1CNT = 0�� T1CNT = T1PR����ƥ�������ƥ�䣩���¼��ض����Ĵ�����ֵ��
                               //PWM1/2/3/4/5/6���Ƚ��߼����
   // ��������жϱ�־λ
   EvaRegs.EVAIFRA.bit.T1PINT=1;

   // ʹ�������жϣ�
   EvaRegs.EVAIMRA.bit.T1PINT=1;

}

interrupt void epwm1_isr(void)
{
    struct Key_Pos keyPress = Scan_Key_Horizon_Vertical();
//    printf("key value:%d\n", keyPress.val);
    printf("speed: temp_value=%d\n", temp);
    int key_val = keyPress.val;
    if(key_val>0)//ɨ���Ƿ񰴼�����
    {
     while(keyPress.val != 0){
         keyPress = Scan_Key_Horizon_Vertical();
     };
     Key_handle(key_val);
     // ����CMPA��CMPB�ȽϼĴ�����ֵ
     Motor_Drive();
    }

     PieCtrlRegs.PIEACK.all|=0x002;       // PIEӦ��λ��1�������´��ж�
     // ��������жϱ�־λ
     EvaRegs.EVAIFRA.bit.T1PINT=1;

}


/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void                              */
/*��������:��ʼ��������ƶ˿�               */
/*------------------------------------------*/
void Init_PWM_Port(void){
    EALLOW;
    // ����GPIOΪPWM����
    GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0 = 1; // EVA PWM 1��
    GpioMuxRegs.GPAMUX.bit.PWM2_GPIOA1 = 1; // EVA PWM 2��
    EDIS;
}

void Init_Port(void)
{
    //////////////////////////////����3��IO������Ϊ�������Ϊ��ɨ��////////////////////////////

    //��ʼ����1��GPIOB2
    EALLOW;
    GpioDataRegs.GPBCLEAR.bit.GPIOB2= 1;                                    // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM9_GPIOB2 = 0;                                     // GPIO48 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB2 = 1;                                      // GPIO48 = output

    //��ʼ����2��GPIOB1

    GpioDataRegs.GPBCLEAR.bit.GPIOB1 = 1;                                       // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM8_GPIOB1= 0;                                      // GPIO49 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB1 = 1;                                      // GPIO49 = output

    //��ʼ����3��GPIOB0

    GpioDataRegs.GPBCLEAR.bit.GPIOB0 = 1;                                       // Load output latch
    GpioMuxRegs.GPBMUX.bit.PWM7_GPIOB0 = 0;                                     // GPIO50 = GPIO
    GpioMuxRegs.GPBDIR.bit.GPIOB0 = 1;                                      // GPIO50 = output


    //////////////////////////////����3��IO������Ϊ���룬��Ϊ��ɨ��////////////////////////////



    //��ʼ����1��GPIOB5

    GpioMuxRegs.GPBMUX.bit.PWM12_GPIOB5 = 0;                                    // ����Ϊһ��IO��
    GpioMuxRegs.GPBDIR.bit.GPIOB5  = 0;                                     // IO�ڷ���Ϊ����

    //��ʼ����2��GPIOB4

    GpioMuxRegs.GPBMUX.bit.PWM11_GPIOB4 = 0;                                    // ����Ϊһ��IO��
    GpioMuxRegs.GPBDIR.bit.GPIOB4  = 0;                                     // IO�ڷ���Ϊ����

    //��ʼ����3��GPIOB3

    GpioMuxRegs.GPBMUX.bit.PWM10_GPIOB3 = 0;                                    // ����Ϊһ��IO��
    GpioMuxRegs.GPBDIR.bit.GPIOB3   = 0;                                    // IO�ڷ���Ϊ����

    EDIS;
}

/*------------------------------------------*/
/*��ʽ������void                         */
/*����ֵ:void                              */
/*��������:�����������                       */
/*------------------------------------------*/
void Motor_Drive(void)
{
    EvaRegs.CMPR1 = temp;//�ı�����
}

void Motor_changeDir(void){
    ////��֤����PWM1��EPWM2�໥�л�ͬʱ���0��ƽ��
//    EPwm1Regs.CMPA.half.CMPA = 0;//�ı�����
//    EPwm1Regs.CMPB = 0;//�ı�����
    printf("Direction:%d", Direction);
    if(Direction==0)
    {
// ���ö����޶�������Ĭ��Ϊת������Ϊ��ת����ʱֻ��PWM2���ռ�ձȣ�
        EvaRegs.ACTRA.all = 0x0004;
        Direction=1;
    }
    else
    {
     // ���ö����޶�������Ĭ��Ϊת������Ϊ��ת����ʱֻ��PWM1���ռ�ձȣ�
        EvaRegs.ACTRA.all = 0x0001;
        Direction=0;
    }
    temp=0;
}


//===========================================================================
// No more.
//===========================================================================

