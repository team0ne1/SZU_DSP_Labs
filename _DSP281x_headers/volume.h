/*
 *  Copyright 2000 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *  U.S. Patent Nos. 5,283,900  5,392,448
 */
/* "@(#) DSP/BIOS 4.00 03-16-00 (barracuda-e06)" */
/*
 *  ======== volume.h ========
 *
 */

#ifndef __VOLUME_H
#define __VOLUME_H

#ifndef TRUE
#define TRUE 1
#endif

#define BUFSIZE 0x64

#define FRAMESPERBUFFER 10

#define MINGAIN 1
#define MAXGAIN 10

#define MINCONTROL 0
#define MAXCONTROL 19

#define BASELOAD 1

#endif /* __VOLUME_H */
