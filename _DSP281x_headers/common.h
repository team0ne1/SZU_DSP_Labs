void delay(unsigned int k);
/////////////////////////////////

#define NULL		0
#define TRUE   		1
#define FALSE  		0

#define BUFFER_LENGTH	2048 //8192
#define MAX_READ_LENGTH 2048//16384
#define MAX_WRITE_LENGTH 2048//2048

typedef unsigned char       INT8;
typedef unsigned short      INT16;
typedef unsigned long       INT32;


typedef union __FLAGS
{
	struct _FLAGS
	{
		unsigned char   SLAVE_IS_ATTACHED	;
		unsigned char   SLAVE_REMOVED		;
		unsigned char  	SLAVE_FOUND			;	// Slave USB device found
		unsigned char  	SLAVE_ENUMERATED	;	// slave USB device enumeration done
		unsigned char   SLAVE_ONLINE		;
		unsigned char 	TIMEOUT_ERR			;	// timeout error during data endpoint transfer
		unsigned char	DATA_STOP			;	// device unplugged during data transfer
		unsigned char 	bData1				;
		unsigned char 	bUartInDone			;		
		unsigned char 	bMassDevice			;
		
	} bits;
	
} FLAGS;



