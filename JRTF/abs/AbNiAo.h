#pragma once
#include "AB.h"
#include <stdio.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <sstream>
// OS Interface
#include "osiBus.h"
// Chip Objects
#include "tXSeries.h"
// Chip Object Helpers
#include "dataHelper.h"
#include "devices.h"
#include "eepromHelper.h"
#include "outTimer/aoHelper.h"
#include "simultaneousInit.h"

class AbNiAo :public AB
{
public:
	AbNiAo();

	~AbNiAo();

	int init();

	void output_data();

	void dowork();

	int set_data(std::string p1, std::string p2);

private:
	std::string brdLocation_1;
	std::string brdLocation_2;
	u32 CHANNELS_NUMBER;
	float NI_6363_ao[4];


	/*********************************************************************\
	|
	|   Example parameters
	|
	\*********************************************************************/

	//
	// Feature Parameters (modify these to exercise the example)
	//

	// Channel parameters
	u32 numberOfChannels;                           // Channels: ao0:1
	tBoolean printVolts;
	nNISTC3::tOutputRange range; // Range: +/- 10 Volts
	tBoolean resetToZero;

	// Buffer parameters
	u32 sampsPerChan;

	//
	// Fixed or calculated parameters (do not modify these)
	//

	// Channel parameters
	u8 gain;
	std::vector<nNISTC3::aoHelper::tChannelConfiguration> chanConfig;

	u32 totalNumberOfSamples;

	std::vector<f32> voltData;
	std::vector<i16> scaledData;

	// Behavior parameters
	f64 elapsedTime; // How long has the generation been running?
	clock_t start;

	// Bookkeeping
	nMDBG::tStatus2 status;
	tBoolean aoErrored; // Did the AO subsystem have an error?
	nOutTimer::tOutTimer_Error_t dacOverrun;
	tAddressSpace bar0;
	iBus *bus;

	tXSeries *device;
	const nNISTC3::tDeviceInfo* deviceInfo;
	nNISTC3::aoHelper *aoHelper;
	nNISTC3::eepromHelper *eepromHelper;
};