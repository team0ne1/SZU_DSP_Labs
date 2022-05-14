#define LED       *(int *)0xc0000
#define SW        *(int *)0xc1000
#define SPI_OE    *(int *)0xc2000
#define DA_CTL    *(int *)0xc0003
#define DA_DATA_L *(int *)0xc0006
#define DA_DATA_H *(int *)0xc0007
#define DA_LATCH  *(int *)0xc6000
#define DA_CHN1   0x0
#define DA_CHN2   0x40 
#define DA_CHN3   0x80
#define DA_CHN4   0xc0
// E2ROM Instruction
#define WREN      6
#define WRDI      4
#define RDSR      5
#define WRSR      1
#define READ      3
#define WRITE     2    
#define WPEN      0x80
#define BL1       0x8   
#define BL0       0x4
#define WEL       0x2
#define WIP       0x1     
