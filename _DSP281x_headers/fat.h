unsigned  char  List(void);
unsigned  char	OpenFile(char *str);
unsigned  char  ReadFile(unsigned long readLength, unsigned char *pBuffer);
unsigned  char 	SetFilePointer(unsigned long pointer);
unsigned  char  CreateFile(char *str,unsigned char attr);
unsigned  char  WriteFile(unsigned long writeLength,unsigned char *pBuffer);
unsigned  char  RemoveFile(char *str);
unsigned long 	GetCapacity();
unsigned  char  DetectDisk();
unsigned  char  CreateDir(char *str);
unsigned  char  DownDir(char *str);
unsigned  char  UpDir();
unsigned  char  UpRootDir();


