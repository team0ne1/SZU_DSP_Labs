
////////////////////////////////////////////////////////////////////////////////////
// Command Descriptor Block
//      _RBC : Reduced Block Command
//      _SPC : SPC-2 SCSI primary Command - 2
////////////////////////////////////////////////////////////////////////////////////
typedef struct _SYS_INFO_BLOCK{
  unsigned long StartSector;
  unsigned long TotalSector;
  
  INT16 BPB_BytesPerSec;
  INT8 BPB_SecPerClus;
  
  INT8 BPB_NumFATs;
  INT16 BPB_RootEntCnt;
  unsigned long BPB_TotSec16;
 // INT8 BPB_Media;
  INT16 BPB_FATSz16;
  INT16 BPB_SecPerTrk;
  INT16 BPB_NumHeads;
  unsigned long BPB_HiddSec;
  unsigned long BPB_TotSec32;
  //INT8 BS_DrvNum;
 // INT8 BS_BootSig;
  //INT8 BS_VolID[4];
  //INT8 BS_VolLab[11];
  //INT8 BS_FilSysType[8];
   ///////////////////////////////
  unsigned long FatStartSector;
  unsigned long RootStartSector;
  unsigned long FirstDataSector;
/////////////////////FAT32///////////////////////////////
  INT32 BPB_FATSz32;
  unsigned long RootStartCluster;
  unsigned long TotCluster;
  unsigned long LastFreeCluster;
  unsigned char FAT;	
} SYS_INFO_BLOCK;

typedef struct _FILE_INFO{
  unsigned char bFileOpen;
  unsigned long StartCluster;//unsigned int StartCluster;
  unsigned long LengthInByte;
  unsigned long ClusterPointer;//unsigned int ClusterPointer;
  unsigned long SectorPointer;
  unsigned int OffsetofSector;
  unsigned char SectorofCluster;
  unsigned long pointer;
  unsigned long FatSectorPointer;//unsigned int	FatSectorPointer;
} FILE_INFO;

typedef struct _DIR_INFO{
	unsigned char name[8];
	unsigned char extension[3];
	unsigned char attribute;
	unsigned char Reserved[10];
	unsigned int lastUpdateDate;
	unsigned int lastUpdateTime;
	unsigned int startCluster;
	unsigned long length;
} DIR_INFO;


unsigned char InitFileSystem(void);
unsigned char RBC_Read(unsigned long sector,unsigned char len,unsigned char *pBuffer);
unsigned char RBC_Write(unsigned long sector,unsigned char len,unsigned char *pBuffer);
