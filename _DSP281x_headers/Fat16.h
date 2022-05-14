unsigned long 	FirstSectorofCluster16(unsigned int n);
unsigned int 	ThisFatSecNum16(unsigned int clusterNum);
unsigned int 	ThisFatEntOffset16(unsigned int clusterNum);
unsigned int 	GetNextClusterNum16(unsigned int clusterNum);
unsigned int 	GetClusterNumFromSectorNum(unsigned long sectorNum);

unsigned char 	GoToPointer16(unsigned long pointer);
unsigned int 	GetFreeCusterNum16(void);
unsigned int 	CreateClusterLink16(unsigned int currentCluster);
unsigned char 	DeleteClusterLink16(unsigned int clusterNum);

