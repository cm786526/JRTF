#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <osiBus.h>
#include <cstring>
#include <bitset>

#include <tXSeries.h>
#include <devices.h>
#include <dio/dioHelper.h>
#include <dio/pfiDioHelper.h>
#include <simultaneousInit.h>

#include "AB.h"

class AbNiDo :public AB
{
public:
	AbNiDo();

	~AbNiDo();

	int init();

	void dowork();

	int set_data(std::string p1, std::string p2);

private:

	std::string brdLocation_1;
	std::string brdLocation_2;

	// Channel parameters
	u32 lineMaskPort0;
	u8 lineMaskPort1;
	u8 lineMaskPort2;
	tBoolean tristateOnExit;

	// Buffer parameters
	u32 outputDataPort0; // Value to write to port0
	u32 outputDataPort1; // Value to write to port1
	u32 outputDataPort2; // Value to write to port2

						 //
						 // Fixed or calculated parameters (do not modify these)
						 //

						 // Channel parameters
	u32 port0Length;
	u32 port1Length;
	u32 lineMaskPFI;

	// Buffer parameters
	u32 outputDataPFI;
	u32 inputDataPort0; // Value of lines on port0
	u32 inputDataPFI; // Value of lines on port1:2 (PFI0..15)

					  // Bookkeeping
	nMDBG::tStatus2 status;
	tAddressSpace bar0;

	iBus *bus;

	tXSeries *device;
	const nNISTC3::tDeviceInfo* deviceInfo;
	nNISTC3::dioHelper *dioHelper;
	nNISTC3::pfiDioHelper *pfiDioHelper;

};