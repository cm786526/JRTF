#pragma once

#include <stdio.h>
#include <string.h>
#include "rfm2g_api.h"
#include "AB.h"

#define DEVICE_PREFIX   "/dev/rfm2g"
#if (defined(RFM2G_LINUX))

#ifdef CONFIG_DEVFS_FS
#define DEVICE_PREFIX   "/dev/rfm2g/"
#else
#define DEVICE_PREFIX   "/dev/rfm2g"
#endif

#define PROCFILE         "/proc/rfm2g"
#endif

//#define BUFFER_SIZE     1024

class Rfm:public AB{
public:
	Rfm();

	int init(RFM2G_INT32 my_numDevice);

	~Rfm();

	int Peek8(RFM2G_UINT32 Offset, RFM2G_UINT8  *Value);

	int Peek16(RFM2G_UINT32 Offset, RFM2G_UINT16  *Value);

	int Peek32(RFM2G_UINT32 Offset, RFM2G_UINT32  *Value);

	/* Implemented only on 64 bit Operating Systems */
	//	int Peek64(RFM2G_UINT32 Offset, RFM2G_UINT64  *Value);

	int Poke8(RFM2G_UINT32 Offset, RFM2G_UINT8 Value);

	int Poke16(RFM2G_UINT32 Offset, RFM2G_UINT16  Value);

	int Poke32(RFM2G_UINT32 Offset, RFM2G_UINT32  Value);

	/* Implemented only on 64 bit Operating Systems */
	//	int Poke64(RFM2G_UINT32 Offset, RFM2G_UINT64  Value);

	int read(RFM2G_UINT32 Offset, void *Buffer, RFM2G_UINT32 Length);

	int write(RFM2G_UINT32 Offset, void *Buffer, RFM2G_UINT32 Length);

	int send(RFM2G_NODE ToNode, RFM2GEVENTTYPE EventType, RFM2G_UINT32 ExtendedData);

	void receive();

	int wait(RFM2GEVENTTYPE event_num, int timeout);

	int SetLed(RFM2G_BOOL Led);
private:
	//std::string name;
	//pthread_t  Tid;

	RFM2G_STATUS   result;                 /* Return codes from RFM2g API calls */
	RFM2GHANDLE    Handle;
	RFM2G_INT32    numDevice;
	RFM2G_CHAR     device[40];             /* Name of PCI RFM2G device to use   */
	RFM2G_NODE     NodeId;
	RFM2G_NODE     otherNodeId;            /* Node ID of the other RFM board    */
	RFM2GEVENTINFO EventInfo;              /* Info about received interrupts    */

										   //    RFM2G_UINT32   outbuffer[BUFFER_SIZE]; /* Data written to another node      */
										   //    RFM2G_UINT32   inbuffer[BUFFER_SIZE];  /* Data read from another node       */

};

