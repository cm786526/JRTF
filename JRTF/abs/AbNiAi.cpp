/*
 * based on aiex1.cpp !!!
 *
 *   Single-point on-demand analog input
 *
 * aiex1 reads and scales analog data using software timing and transfers data
 * to the host by reading directly from the FIFO. After configuring the AI
 * subsystem's timing and channel parameters, aiex1 initiates a configurable
 * number of scans and reads, scales and prints the data. Finally, aiex1
 * restores the hardware's previous state.
 *
 * Example Features (! means highlighted, * means default)
 * Device
 *   Operation       : voltage measurement
 * Channel
 * ! Channels        : ai0, ai1, ai2, ai3
 * ! Scaling         : Volts (*) or raw ADC codes
 *   Terminal config : RSE
 * ! Input range     : +/- 10 V (*),  +/- 5 V,     +/- 2 V,    +/- 1 V,
 *                     +/- 500mV,     +/- 200 mV,  +/- 100 mV
 * Timing
 * ! Sample mode     : single-point
 * ! Timing mode     : software-timed
 * ! Clock source    : software strobe
 * Trigger
 * ! Start trigger   : automatic start
 *   Reference trig  : none
 *   Pause trigger   : none
 * Read Buffer
 * ! Data transfer   : programmed IO from FIFO
 *
 * External Connections
 *   ai0:3           : voltages within +/- 10 V (*) or other specified range
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "AbNiAi.h"

AbNiAi::AbNiAi() {
	brdLocation_1 = "12";
	brdLocation_2 = "0";
	CHANNELS_NUMBER = 32;
	memset(NI_6363_ai, 0, sizeof(NI_6363_ai));
}

AbNiAi::~AbNiAi() {
	ni_stop_measurement();
	ni_finalize_measurement();
}

int AbNiAi::init() {

	// Create the board location string
	tChar brdLocation[256];
	sprintf(brdLocation, "PXI%s::%s::INSTR", brdLocation_1.c_str(),
		brdLocation_2.c_str());
	bus = NULL;
	bus = acquireBoard(brdLocation);
	if (bus == NULL) {
		printf("Could not access PCI device. Exiting.\n");
		exit(0);
	}

	ni_config_parameters();
	ni_Initialize();
	ni_ai_subsystem();
	ni_start_measurement();
	//	ni_read_data();
	//	ni_stop_measurement();
	//	ni_finalize_measurement();

	/*for (unsigned int i = 0; i<CHANNELS_NUMBER; i++) {
		std::stringstream ss;
		ss << "ai" << i;
		sharedata_bind(ss.str(), &scaledData[i], sizeof(float));
	}
	sharedata_bind("NI_6363_ai", &NI_6363_ai, sizeof(NI_6363_ai));*/
	return 0;
}

void AbNiAi::dowork() {

	ni_read_data();

	for (unsigned int i = 0; i < CHANNELS_NUMBER; i++) {
		NI_6363_ai[i] = scaledData[i];
	}
	//cout << "***set=***" << scaledData[0] << endl;
}

int AbNiAi::set_data(std::string p1, std::string p2) {
	if (p1 == "brdLocation_1") {
		brdLocation_1 = p2;
	}
	if (p1 == "brdLocation_2") {
		brdLocation_2 = p2;
	}

	if (p1 == "CHANNELS_NUMBER") {
		// setting CHANNELS_NUMBER must before dowork()!!!
		std::stringstream ss;
		ss << p2;
		ss >> CHANNELS_NUMBER;
		std::cout << "ni6363_ai set CHANNELS_NUMBER " << CHANNELS_NUMBER << std::endl;
	}

	if (p1 == "s") {
		std::stringstream ss;
		for (unsigned int i = 0; i<CHANNELS_NUMBER; i++) {
			ss << " ai" << i << "=" << NI_6363_ai[i] << " ";
			if (i % 8 == 7)
				ss << std::endl;
		}
		std::cout << ss.str() << std::endl;
	}

	return 0;
}

// get share data for other ab
ShareData* AbNiAi::get_data(string name) {
	stringstream ss(name);
	int number;
	if (name == "all")
	{
		return new ShareData(&NI_6363_ai, TYPE_FLOAT_ARRAY, sizeof(NI_6363_ai));
	}
	else if (ss>>number && 0<=number && number<=32)
	{
		return new ShareData(&NI_6363_ai[number], TYPE_FLOAT, sizeof(float));
	}
	else
	{
		return new ShareData(TYPE_NONE);
	}
}

void AbNiAi::ni_config_parameters()
{
	/*********************************************************************\
	|
	|   Example parameters
	|
	\*********************************************************************/

	//
	// Feature Parameters (modify these to exercise the example)
	//

	// Channel parameters
	numberOfChannels = CHANNELS_NUMBER;                          // Channels: ai0:3
	printVolts = kTrue;
	range = nNISTC3::kInput_10V;  // Range: +/- 10 Volts

	// Buffer parameters
	sampsPerChan = 1;

	//
	// Fixed or calculated parameters (do not modify these)
	//

	// Channel parameters
	gain = 0;
	chanConfig = std::vector<nNISTC3::aiHelper::tChannelConfiguration>(numberOfChannels, nNISTC3::aiHelper::tChannelConfiguration());
	maxChannel = numberOfChannels;

	// Timing parameters
//	convertPeriod = 400; // 100 MHz / 400 = 250 kHz (refer to device specs for minimum period)
	convertPeriod = 100; // zgz
	convertDelay = 2; // Wait N TB3 ticks after the sample clock before converting (N must be >= 2)
//	nNISTC3::inTimerParams timingConfig;

	// Buffer parameters
	n = 0;  // Number of samples counter
	m = 0;  // Number of channels counter
	samplesAvailable = 0; // Number of samples in the AI data FIFO
	samplesRead = 0; // Number of samples read from the AI data FIFO
	streamFifoSize = 0;

	sampleSizeInBytes = sizeof(i16);
	readSizeInBytes = numberOfChannels * sampleSizeInBytes;

	rawData = std::vector<i16>(numberOfChannels, 0);
	scaledData = std::vector<f32>(numberOfChannels, 0);

	// Behavior parameters
	rlpTimeout = 5; // Wait 5 seconds for a register operation before breaking
//	clock_t rlpStart;
//	f64 rlpElapsedTime;

	// Bookkeeping
//	nMDBG::tStatus2 status;
	aiErrored = kFalse; // Did the AI subsystem have an error?
	scanOverrun = nInTimer::kNO_ERROR;
	adcOverrun = nInTimer::kNO_ERROR;
	fifoOverflow = nInTimer::kNO_ERROR;
	bar0;
	bar0 = bus->createAddressSpace(kPCI_BAR1);

}

void AbNiAi::ni_Initialize()
{
	/*********************************************************************\
	|
	|   Initialize the measurement
	|
	\*********************************************************************/

	//
	// Open, detect, and initialize the X Series device
	//
	device = new tXSeries(bar0, &status);

	deviceInfo = const_cast<nNISTC3::tDeviceInfo *>(nNISTC3::getDeviceInfo(*device,status));

	if (status.isFatal())
	{
	  printf("Error: Cannot identify device (%d).\n", status.statusCode);
	  return;
	}

	if (deviceInfo->isSimultaneous) nNISTC3::initializeSimultaneousXSeries(*device, status);

	//
	// Create subsystem helpers
	//

	aiHelper = new nNISTC3::aiHelper(*device, deviceInfo->isSimultaneous, status);
	eepromHelper = new nNISTC3::eepromHelper(*device, deviceInfo->isSimultaneous, deviceInfo->numberOfADCs, deviceInfo->numberOfDACs, status);
	streamHelper = new nNISTC3::streamHelper(device->AIStreamCircuit, device->CHInCh, status);

	//
	// Validate the Feature Parameters
	//

	// Ensure that the number of channels match the number requested
	if (numberOfChannels > deviceInfo->numberOfAIChannels)
	{
	  if (deviceInfo->isSimultaneous)
	  {
		 printf("Error: Number of channels requested (%u) is greater than number on the device (%u).\n",
			numberOfChannels, deviceInfo->numberOfAIChannels);
		 status.setCode(kStatusBadParameter);
		 return;
	  }
	  else
	  {
		 maxChannel = deviceInfo->numberOfAIChannels;
	  }
	}

	// Ensure that the range is supported by this board
	gain = deviceInfo->getAI_Gain(range, status);
	if (status.isFatal())
	{
	  printf("Error: Unsupported range.\n");
	  status.setCode(kStatusBadParameter);
	  return;
	}

	// Ensure that the FIFO can hold a complete measurement
	streamFifoSize = streamHelper->getFifoSize();
	if (readSizeInBytes > streamFifoSize)
	{
	  printf("Error: Number of samples (%u) is greater than the AI FIFO size (%u).\n", numberOfChannels, streamFifoSize/sampleSizeInBytes);
	  status.setCode(kStatusBadParameter);
	  return;
	}


}

void AbNiAi::ni_ai_subsystem()
{
	/*********************************************************************\
	|
	|   Program the AI subsystem
	|
	\*********************************************************************/

	//
	// Reset the AI subsystem
	//

	aiHelper->reset(status);

	//
	// Program AI timing
	//

	// Enter timing configuration mode
	device->AI.AI_Timer.Reset_Register.writeConfiguration_Start(kTrue, &status);

	// Disable external gating of the sample clock
	aiHelper->programExternalGate(
	nAI::kGate_Disabled,                  // No external pause signal
	nAI::kActive_High_Or_Rising_Edge,     // Don't care
	status);

	// Auto-trigger the START1 signal (start trigger)
	aiHelper->programStart1(
	nAI::kStart1_Low,                     // Drive trigger line low
	nAI::kActive_Low_Or_Falling_Edge,     // Make line active on low...
	kFalse,                               //   ...level (not falling edge)
	status);

	// Program the START signal (sample clock) to start on a software strobe
	aiHelper->programStart(
	nAI::kStartCnv_Low,                   // Drive the clock line low
	nAI::kActive_High_Or_Rising_Edge,     // Make the line active on rising...
	kTrue,                                //   ...edge (not high level)
	status);

	if (deviceInfo->isSimultaneous)
	{
	// Program the convert to be the same as START
	aiHelper->programConvert(
	nAI::kStartCnv_Low,
	nAI::kActive_High_Or_Rising_Edge,
	status);
	}
	else
	{
	// Program the convert clock to start on the sample clock
	aiHelper->programConvert(
	nAI::kStartCnv_InternalTiming,        // Drive the clock line from internal sample clock
	nAI::kActive_Low_Or_Falling_Edge,     // Convert on falling edge
	status);
	}

	// Program the sample and convert clock timing specifications
	if (!deviceInfo->isSimultaneous)
	{
	timingConfig.setUseSI2Counter(kTrue, status); // Use SI2 for internal convert clocking
	timingConfig.setConvertPeriod(convertPeriod, status);
	timingConfig.setConvertDelay(convertDelay, status);
	}

	// Push the timing specification to the device
	aiHelper->getInTimerHelper(status).programTiming(timingConfig, status);

	// Program the FIFO width, this method also clears the FIFO
	aiHelper->programFIFOWidth(nAI::kTwoByteFifo, status);

	//
	// Program AI channels
	//

	// Clear configuration FIFO
	aiHelper->getInTimerHelper(status).clearConfigurationMemory(status);

	for (u16 i=0; i<numberOfChannels; ++i)
	{
	// Set channel parameters
	chanConfig[i].isLastChannel = (i == numberOfChannels-1) ? kTrue : kFalse;  // Last channel?
	chanConfig[i].enableDither = nAI::kEnabled;   // Dithering helps increase ADC accuracy
	chanConfig[i].gain = gain;                    // Set the gain (used by the hardware)
	chanConfig[i].channelType = nAI::kRSE;        // Single-ended: aiN vs aiGnd
	//chanConfig[i].bank = nAI::kBank0;             // AI channels 0..15 are on bank0
	// ZGZ, 0:15 on bank0, 16:31 on bank1
	if(i<16){
		chanConfig[i].bank = nAI::kBank0;
	}else{
		chanConfig[i].bank = nAI::kBank1;
	}

	chanConfig[i].channel = i%maxChannel;         // aiN where N = i%maxChannel
	chanConfig[i].range = range;                  // Set the range (used by the scaler)

	// Push the channel configuration to the device
	aiHelper->programChannel(chanConfig[i], status);
	}

	// Advance the configuration FIFO
	aiHelper->getInTimerHelper(status).primeConfigFifo(status);

	// Leave timing configuration mode
	device->AI.AI_Timer.Reset_Register.writeConfiguration_End(kTrue, &status);

}

void AbNiAi::ni_start_measurement()
{
	/*********************************************************************\
	|
	|   Start the voltage measurement
	|
	\*********************************************************************/

	//
	// Arm the AI subsystem
	//

//	printf("Starting %u-sample on-demand analog measurement.\n", sampsPerChan);
	aiHelper->getInTimerHelper(status).armTiming(timingConfig, status);

	// The START1 signal (start trigger) auto-triggers
}

void AbNiAi::ni_read_data()
{
	/*********************************************************************\
	|
	|   Read and print data
	|
	\*********************************************************************/

//	nNISTC3::nAIDataHelper::printHeader(1, numberOfChannels, printVolts ? "Voltage" : "ADC code");//this line print title

	// Perform an on-demand read of each channel and scale the data
	for (n=0; n<sampsPerChan; ++n)
	{
	  // Begin a scan
	  if (deviceInfo->isSimultaneous)
	  {
		 aiHelper->getInTimerHelper(status).strobeConvert(status);
	  }
	  else
	  {
		 aiHelper->getInTimerHelper(status).strobeStart(status);
	  }

	  // Wait for the scan to complete
	  rlpElapsedTime = 0;
	  rlpStart = clock();
	  while (device->AI.AI_Timer.Status_1_Register.readScan_In_Progress_St(&status))
	  {
		 // Spin on the Scan In Progress bit
		 if (rlpElapsedTime > rlpTimeout)
		 {
			printf("\n");
			printf("Error: AI scan did not complete within timeout.");
			status.setCode(kStatusRLPTimeout);
			break;
		 }
		 rlpElapsedTime = static_cast<f64>(clock() - rlpStart) / CLOCKS_PER_SEC;
	  }

	  // Check for AI subsystem errors
	  device->AI.AI_Timer.Status_1_Register.refresh(&status);
	  scanOverrun = device->AI.AI_Timer.Status_1_Register.getScanOverrun_St(&status);
	  adcOverrun = device->AI.AI_Timer.Status_1_Register.getOverrun_St(&status);
	  if (deviceInfo->isSimultaneous)
	  {
		 fifoOverflow = static_cast<nInTimer::tInTimer_Error_t>(device->SimultaneousControl.InterruptStatus.readAiFifoOverflowInterruptCondition(&status));
	  }
	  else
	  {
		 fifoOverflow = device->AI.AI_Timer.Status_1_Register.getOverflow_St(&status);
	  }

	  // Note: these errors are unlikely to occur in this example because the
	  // data is read between each sample clock pulse. However, if the hardware
	  // were programmed another way, they may happen.
	  if (scanOverrun || adcOverrun || fifoOverflow)
	  {
		 aiErrored = kTrue;
		 break;
	  }

	  // Make sure there is data in the FIFO before reading from it
	  rlpElapsedTime = 0;
	  rlpStart = clock();
	  while (rlpElapsedTime < rlpTimeout)
	  {
		 samplesAvailable = device->AI.AI_Data_FIFO_Status_Register.readRegister(&status);

		 if (samplesAvailable >= numberOfChannels)
		 {
			// Read from the 16-bit FIFO data register since it was configured as such
			for (m=0; m<numberOfChannels; ++m)
			{
			   rawData[m] = device->AI.AI_FIFO_Data_Register16.readRegister();
			}

			// Print the data
			if (printVolts)
			{
			   nNISTC3::nAIDataHelper::scaleData(rawData, numberOfChannels,
												 scaledData, numberOfChannels,
												 chanConfig, *eepromHelper, *deviceInfo);
//			   nNISTC3::nAIDataHelper::printData(scaledData, numberOfChannels, numberOfChannels);//this line print ai values
			}
			else
			{
			   nNISTC3::nAIDataHelper::printData(rawData, numberOfChannels, numberOfChannels);
			}
			samplesRead += numberOfChannels;
			break;
		 }
		 else
		 {
			rlpElapsedTime = static_cast<f64>(clock() - rlpStart) / CLOCKS_PER_SEC;
		 }
	  }

	  if (rlpElapsedTime > rlpTimeout)
	  {
		 printf("\n");
		 printf("Error: AI FIFO expected %u samples, only %u available.", numberOfChannels, samplesAvailable);
		 status.setCode(kStatusRLPTimeout);
		 break;
	  }
	}
//	printf("\n");//this line print end

}

void AbNiAi::ni_stop_measurement()
{

	/*********************************************************************\
	|
	|   Stop the voltage measurement
	|
	\*********************************************************************/

	// The AI subsystem has already been stopped by hardware

	device->AI.AI_Timer.Command_Register.writeDisarm(kTrue, &status);

	// Wait for the timing engine to disarm
	rlpElapsedTime = 0;
	rlpStart = clock();
	while (device->AI.AI_Timer.Status_1_Register.readSC_Armed_St(&status) == nInTimer::kArmed)
	{
	  // Spin on the SC Armed bit
	  if (rlpElapsedTime > rlpTimeout)
	  {
		 printf("\n");
		 printf("Error: AI timing engine did not disarm within timeout.\n");
		 status.setCode(kStatusRLPTimeout);
		 return;
	  }
	  rlpElapsedTime = static_cast<f64>(clock() - rlpStart) / CLOCKS_PER_SEC;
	}

}

void AbNiAi::ni_finalize_measurement()
{
	/*********************************************************************\
	|
	|   Finalize the measurement
	|
	\*********************************************************************/

	//
	// Print run-time summary
	//

	if (scanOverrun)
	{
	  printf("Error: AI sample clock overrun.\n");
	  status.setCode(kStatusRuntimeError);
	}
	if (adcOverrun)
	{
	  printf("Error: AI ADC overrun.\n");
	  status.setCode(kStatusRuntimeError);
	}
	if (fifoOverflow)
	{
	  printf("Error: AI FIFO overflow.\n");
	  status.setCode(kStatusRuntimeError);
	}
	if (!aiErrored)
	{
	  printf("Finished on-demand analog measurement.\n");
	  printf("Read %u samples on %u channels (%u total samples).\n",
			 sampsPerChan,
			 numberOfChannels,
			 samplesRead);
	}else{
//		exit(0);//add by zgz
	}

	//
	// Restore the state of the device
	//

	// Nothing else to do: the helpers' destructors safely unwind device state.

}
