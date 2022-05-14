/////////////////hpi32.h////////////////////////////////
#define MaxLFNum 20

typedef struct ShowFileName_D{
  unsigned char LongName[256];	//long file name,end by 00 00
  unsigned char item[32];		//short file name & dir
} ShowFileName_Def;

unsigned char List32(void);
unsigned char OpenFile32(char *str);


unsigned char ReadFile32(unsigned long readLength,unsigned char *pBuffer);
unsigned char SetFilePointer32(unsigned long pointer);
unsigned char CreateFile32(char *str,unsigned char attr);
unsigned char WriteFile32(unsigned long writeLength,unsigned char *pBuffer);
unsigned char RemoveFile32(char *str);
unsigned long GetCapacity32(void);

unsigned char CreateDir32(char *str);
unsigned char DownDir32(char *pBuffer);
unsigned char UpDir32(void);
unsigned char UpRootDir32(void);
unsigned char ListDirve(void);

//====================no more==================================
