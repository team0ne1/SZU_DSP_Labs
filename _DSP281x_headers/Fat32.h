//////////////////////////////////////////////////////////////////////
unsigned long FirstSectorofCluster32(unsigned long clusterNum);
unsigned long ThisFatSecNum32(unsigned long clusterNum);
unsigned long ThisFatEntOffset32(unsigned long clusterNum);
unsigned long GetNextClusterNum32(unsigned long clusterNum);
unsigned char GoToPointer32(unsigned long pointer);
unsigned char DeleteClusterLink32(unsigned long clusterNum);
unsigned long GetFreeCusterNum32(void);
unsigned long CreateClusterLink32(unsigned long currentCluster);
