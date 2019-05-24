
/////////include of NI//////////////
#include <stdio.h>
#include <time.h>
#include <vector>
// OS Interface
#include "osiBus.h"
// Chip Objects
#include "tXSeries.h"
// Chip Object Helpers
#include "dataHelper.h"
#include "devices.h"
#include "eepromHelper.h"
#include "inTimer/aiHelper.h"
#include "simultaneousInit.h"
#include "streamHelper.h"
////////////////////////////////
#include <fstream>
#include <sstream>
#include "AB.h"

class AbNiAi:public AB
{
public:
	AbNiAi();
	~AbNiAi();
	int init();
	void dowork();
	int set_data(std::string p1, std::string p2);
	ShareData* get_data(std::string name);
private:

    std::string brdLocation_1;
	std::string brdLocation_2;
	u32 CHANNELS_NUMBER;
	float NI_6363_ai[32];


//////////Variables of NI///////////////////////
	void ni_config_parameters();
	void ni_Initialize();
	void ni_ai_subsystem();
	void ni_start_measurement();
	void ni_read_data();
	void ni_stop_measurement();
	void ni_finalize_measurement();

	// Channel parameters
	u32 numberOfChannels;                          // Channels: ai0:3
	tBoolean printVolts;
	nNISTC3::tInputRange range;  // Range: +/- 10 Volts

	// Buffer parameters
	u32 sampsPerChan;

	//
	// Fixed or calculated parameters (do not modify these)
	//

	// Channel parameters
	u16 gain;
	std::vector<nNISTC3::aiHelper::tChannelConfiguration> chanConfig;
	u32 maxChannel;

	// Timing parameters
	u32 convertPeriod; // 100 MHz / 400 = 250 kHz (refer to device specs for minimum period)
	u32 convertDelay; // Wait N TB3 ticks after the sample clock before converting (N must be >= 2)
	nNISTC3::inTimerParams timingConfig;

	// Buffer parameters
	u32 n;  // Number of samples counter
	u32 m;  // Number of channels counter
	u32 samplesAvailable; // Number of samples in the AI data FIFO
	u32 samplesRead; // Number of samples read from the AI data FIFO
	u32 streamFifoSize;

	u32 sampleSizeInBytes;
	u32 readSizeInBytes;

	std::vector<i16> rawData;
	std::vector<f32> scaledData;

	// Behavior parameters
	f64 rlpTimeout; // Wait 5 seconds for a register operation before breaking
	clock_t rlpStart;
	f64 rlpElapsedTime;

	// Bookkeeping
	nMDBG::tStatus2 status;
	tBoolean aiErrored; // Did the AI subsystem have an error?
	nInTimer::tInTimer_Error_t scanOverrun;
	nInTimer::tInTimer_Error_t adcOverrun;
	nInTimer::tInTimer_Error_t fifoOverflow;
//	tAddressSpace *bar0;
	iBus* bus;
	tAddressSpace bar0;

	//
	// Create subsystem helpers
	//
	nNISTC3::aiHelper *aiHelper;
	nNISTC3::eepromHelper *eepromHelper;
	nNISTC3::streamHelper *streamHelper;

	tXSeries *device;
	nNISTC3::tDeviceInfo *deviceInfo;
///////////////////////////////////////////////////////

};





