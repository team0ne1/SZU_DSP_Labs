#include "assert.h"
#include "demo7.h"

static unsigned int msg[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};  //段码：0~9
static unsigned int DisData_Bit[4] = {0};                                         //存放拆分后的四位数字
static unsigned int time_T;
static Uint16 time_show = 0;
static unsigned int time_counter = 0;
static Uint16 counter_is_stop = 0;
//static Uint16 keys = 0;

static __interrupt void cpu_timer0_isr(void);
static void DisData_Trans(Uint16 data);
static void show_time(Uint16 second);
static void clear_time(void);
static int Scan_Keys(void);



void demo7(void)
{

// step 1. 初始化系统控制:
// 设置PLL, WatchDog, 使能外设时钟
// 下面这个函数可以从DSP281x_SysCtrl.c文件中找到.
   InitSysCtrl();

// step 2. 初始化通用输入输出多路复用器GPIO:
// 这个函数在DSP281x_Gpio.c源文件中被定义了


   //初始化SPI
   EALLOW;
   GpioMuxRegs.GPFMUX.all=0x000F;   // 选择GPIO为SPI引脚
                                    // 端口F MUX - x000 0000 0000 1111

// 初始化Gpio

   Init_LEDS_Gpio(); //数码管
   Init_Keys_Gpio(); //按键

// step 3. 清除所有中断,初始化中断向量表:
// 禁止CPU全局中断
   DINT;

// 初始化PIE控制寄存器到他们的默认状态.
// 这个默认状态就是禁止PIE中断及清除所有PIE中断标志
// 这个函数放在DSP281x_PieCtrl.c源文件里
   InitPieCtrl();

// 禁止CPU中断，清除CPU中断标志位
   IER = 0x0000;
   IFR = 0x0000;

//初始化PIE中断向量表，并使其指向中断服务子程序（ISR）
// 这些中断服务子程序被放在了DSP281x_DefaultIsr.c源文件中
// 这个函数放在了DSP281x_PieVect.c源文件里面.
   InitPieVectTable();

// step 4.初始化片内外设:
   spi_fifo_init();   // 初始化Spi FIFO
   spi_init();        // 初始化 SPI



// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
  EALLOW;  // This is needed to write to EALLOW protected registers
  PieVectTable.TINT0 = &cpu_timer0_isr;


  EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 5. Initialize all the Device Peripherals:
// This function is found in DSP281x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
  InitCpuTimers();   // For this example, only initialize the Cpu Timers

// Configure CPU-Timer 0 to interrupt every second:
// 100MHz CPU Freq, 1 second Period (in uSeconds)
  ConfigCpuTimer(&CpuTimer0, 150, 200000);

//   ConfigCpuTimer(&CpuTimer0, 150, 500000);
  StartCpuTimer0();
// Step 6. User specific code, enable interrupts:

// Enable CPU INT1 which is connected to CPU-Timer 0:
  IER |= M_INT1;

// Enable TINT0 in the PIE: Group 1 interrupt 7
  PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
  PieCtrlRegs.PIEIER2.bit.INTx7 = 1;

// Enable global Interrupts and higher priority real-time debug events:
  EINT;   // Enable Global interrupt INTM
  ERTM;   // Enable Global realtime interrupt DBGM

  time_T = 5; //default: 5 -> 5*200ms=1s

// Step 6. IDLE loop. Just sit and loop forever (optional):
  while(1){
      show_time(time_show);
      int key = 0;
      if(Scan_Keys() != 0){
          delay1(25000);
          if(Scan_Keys() != 0){
              key = Scan_Keys();
          }
      }

      if(key == 4 && time_T<15){ //sw3
          time_T++;
          printf("time_T:%d\n", time_T);
          continue;
      }
      if(key == 2){ //sw6
          counter_is_stop = ~counter_is_stop;
          printf("stop/continue\n");
          continue;
      }
      if(key == 1 && time_T>1){ //sw9
          time_T--;
          printf("time_T:%d\n", time_T);
          continue;
      }
      if(key == 6){ //sw3+sw6
          clear_time();
          continue;
      }
  }
}



static void DisData_Trans(Uint16 data)
{
    DisData_Bit[3] = data / 1000;                       //千位数
    DisData_Bit[2] = data % 1000 / 100 ;                //百位数
    DisData_Bit[1] = data % 100 / 10;                   //十位数
    DisData_Bit[0] = data % 10;                         //个位数
}


static void show_time(Uint16 second)
{
//    assert(second >= 0);
    if(second > 1000) second = 1000;
    DisData_Trans(second);
    printf("time:");
    int Loop;
    for(Loop = 0;Loop < 4;Loop++){
        Sellect_Bit(Loop%4);                                  //选择要扫描的数码管位
        spi_xmit(msg[DisData_Bit[Loop%4]]);                   //串行输出要显示的数字
        if(Loop < 4) printf("%d", DisData_Bit[3-Loop%4]);
        delay1(1500);
    }
    printf("s\n");

}

static void clear_time(void){
    time_show = 0;
    time_counter = 0;
    printf("clear\n");
}


static int Scan_Keys(void){
    GpioDataRegs.GPBCLEAR.all =  0x1;  //  |= 0000 0000 0000 0001
    int key_press = (~(GpioDataRegs.GPBDAT.all >> 3) & 0x07);

//    printf("keys:%d\n",key_press);
    return key_press;
}

void print_bin1(unsigned int number){
    int bit = sizeof(unsigned int)*8;
    int i;
    for(i = bit - 1;i >= 0;i--){
        int bin = (number & (1 << i)) >> i;
        printf("%d", bin);
    }
    printf("\n");
}


static __interrupt void cpu_timer0_isr(void)
{
    if(counter_is_stop == 0){
        time_counter++;
        //    GpioDataRegs.GPACLEAR.all = 0x00FF;
        if(time_counter % time_T == 0) {
            time_show++;
        }
    }

//    printf("time_counter:%d\n", time_counter);
//   CpuTimer0.InterruptCount++;

   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}






