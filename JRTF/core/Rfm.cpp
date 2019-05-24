#include"Rfm.h"

Rfm::Rfm() {
	numDevice = 0;
	Handle = 0;
	NodeId = 0;
	otherNodeId = 0;
	result = RFM2G_MAX_ERROR_CODE;
	//init(0);
}

int Rfm::init(RFM2G_INT32 my_numDevice) {
	numDevice = my_numDevice;
	Handle = 0;
	NodeId = 0;
	otherNodeId = 0;
	sprintf(device, "%s%d", DEVICE_PREFIX, numDevice);

	/* Open the Reflective Memory device */
	result = RFM2gOpen(device, &Handle);
	if (result != RFM2G_SUCCESS)
	{
		printf("ERROR: RFM2gOpen() failed. \n");
		printf("Error: %s.\n\n", RFM2gErrorMsg(result));
		return -1;
	}

	/* Tell the user the NodeId of this device */
	result = RFM2gNodeID(Handle, &NodeId);
	if (result != RFM2G_SUCCESS)
	{
		printf("Could not get the Node ID.\n");
		printf("Error: %s.\n\n", RFM2gErrorMsg(result));
		return -1;
	}

	printf("RFM device=%s%d NodeID=0x%02x\n", DEVICE_PREFIX, numDevice, NodeId);
	return 0;
}

Rfm::~Rfm() {
	/* Close the Reflective Memory device */
	RFM2gClose(&Handle);
}

int Rfm::Peek8(RFM2G_UINT32 Offset, RFM2G_UINT8  *Value) {
	result = RFM2gPeek8(Handle, Offset, Value);
	if (result == RFM2G_SUCCESS) {
		return 0;
	}
	else {
		return -1;
	}
}

int Rfm::Peek16(RFM2G_UINT32 Offset, RFM2G_UINT16  *Value) {
	result = RFM2gPeek16(Handle, Offset, Value);
	if (result == RFM2G_SUCCESS) {
		return 0;
	}
	else {
		return -1;
	}
}

int Rfm::Peek32(RFM2G_UINT32 Offset, RFM2G_UINT32  *Value) {
	result = RFM2gPeek32(Handle, Offset, Value);
	if (result == RFM2G_SUCCESS) {
		return 0;
	}
	else {
		return -1;
	}
}

/* Implemented only on 64 bit Operating Systems */
//	int Rfm::Peek64(RFM2G_UINT32 Offset, RFM2G_UINT64  *Value){
//		result = RFM2gPeek64(Handle, Offset, Value);
//        if(result == RFM2G_SUCCESS){
//        	return 0;
//        }
//        else{
//            return -1;
//        }
//	}

int Rfm::Poke8(RFM2G_UINT32 Offset, RFM2G_UINT8 Value) {
	result = RFM2gPoke8(Handle, Offset, Value);
	if (result == RFM2G_SUCCESS) {
		return 0;
	}
	else {
		return -1;
	}
}

int Rfm::Poke16(RFM2G_UINT32 Offset, RFM2G_UINT16  Value) {
	result = RFM2gPoke16(Handle, Offset, Value);
	if (result == RFM2G_SUCCESS) {
		return 0;
	}
	else {
		return -1;
	}
}

int Rfm::Poke32(RFM2G_UINT32 Offset, RFM2G_UINT32  Value) {
	result = RFM2gPoke32(Handle, Offset, Value);
	if (result == RFM2G_SUCCESS) {
		return 0;
	}
	else {
		return -1;
	}
}

/* Implemented only on 64 bit Operating Systems */
//	int Rfm::Poke64(RFM2G_UINT32 Offset, RFM2G_UINT64  Value){
//		result = RFM2gPoke64(Handle, Offset, Value);
//        if(result == RFM2G_SUCCESS){
//        	return 0;
//        }
//        else{
//            return -1;
//        }
//	}

int Rfm::read(RFM2G_UINT32 Offset, void *Buffer, RFM2G_UINT32 Length) {
	/* Now read data from the other board from OFFSET_1 */
	result = RFM2gRead(Handle, Offset, Buffer, Length);
	if (result == RFM2G_SUCCESS)
	{
		//printf( "\nData was read from Reflective Memory.\n" );
	}
	else
	{
		printf("\nERROR: Could not read data from Reflective Memory.\n");
		RFM2gClose(&Handle);
		return(-1);
	}

	return 0;
}

int Rfm::write(RFM2G_UINT32 Offset, void *Buffer, RFM2G_UINT32 Length) {

	/* Write outbuffer into Reflective Memory starting at OFFSET_1 */
	result = RFM2gWrite(Handle, Offset, Buffer, Length);
	if (result == RFM2G_SUCCESS)
	{
		//printf( "The data was written to Reflective Memory.  " );
	}
	else
	{
		printf("ERROR: Could not write data to Reflective Memory.\n");
		RFM2gClose(&Handle);
		return(-1);
	}

	return 0;
}

int Rfm::send(RFM2G_NODE ToNode, RFM2GEVENTTYPE EventType, RFM2G_UINT32 ExtendedData) {
	/* Send an interrupt to the other Reflective Memory board */
	result = RFM2gSendEvent(Handle, ToNode, EventType, ExtendedData);
	if (result == RFM2G_SUCCESS)
	{
		//            printf( "An interrupt was sent to Node %d.\n", otherNodeId );
	}
	else
	{
		printf("Error: %s\n", RFM2gErrorMsg(result));
		RFM2gClose(&Handle);
		return(-1);
	}

	return 0;
}

void Rfm::receive() {
	// to do
}

int Rfm::wait(RFM2GEVENTTYPE event_num, int timeout) {
	EventInfo.Event = event_num;  /* We'll wait on this interrupt */
	EventInfo.Timeout = timeout;       /* We'll wait this many milliseconds */
	result = RFM2gEnableEvent(Handle, RFM2GEVENT_INTR1);
	if (result != RFM2G_SUCCESS)
	{
		printf("Error: %s\n", RFM2gErrorMsg(result));
		RFM2gClose(&Handle);
		return(result);
	}

	/* Wait on an interrupt from the other Reflective Memory board */
	//        printf( "\nWaiting %d seconds to receive an interrupt from the other Node ...  ", timeout/1000 );
	fflush(stdout);

	result = RFM2gWaitForEvent(Handle, &EventInfo);
	if (result == RFM2G_SUCCESS)
	{
		//            printf( "\nReceived the interrupt from Node %d.\n", EventInfo.NodeId );
	}
	else
	{
		printf("Error: %s\n", RFM2gErrorMsg(result));
		RFM2gClose(&Handle);
		return(-1);
	}

	/* Got the interrupt, see who sent it */
	otherNodeId = EventInfo.NodeId;
	RFM2G_UINT32 extendedInfo = EventInfo.ExtendedInfo;

	return 0;
}

int Rfm::SetLed(RFM2G_BOOL Led) {
	RFM2gSetLed(Handle, Led);
	return 0;
}