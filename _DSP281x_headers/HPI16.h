/////////////////hpi.h////////////////////////////////
unsigned char List16(void);
unsigned char OpenFile16(char *pBuffer);
unsigned char ReadFile16(unsigned long readLength,unsigned char *pBuffer);
unsigned char SetFilePointer16(unsigned long pointer);

unsigned char CreateFile16(char *str,unsigned char attr);
unsigned char WriteFile16(unsigned long writeLength,unsigned char *pBuffer);
unsigned char RemoveFile16(char *str);
unsigned long GetCapacity16(void);

unsigned char CreateDir16(char *str);
unsigned char DownDir16(char *pBuffer);
unsigned char UpDir16(void);
unsigned char UpRootDir16(void);

