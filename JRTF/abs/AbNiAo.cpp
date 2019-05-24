#include"AbNiAo.h"

AbNiAo::AbNiAo() {
	brdLocation_1 = "12";
	brdLocation_2 = "0";

	CHANNELS_NUMBER = 4;// must init CHANNELS_NUMBER before init!!!
	memset(NI_6363_ao, 0, sizeof(NI_6363_ao));

}

AbNiAo::~AbNiAo() {
	delete  device;
	delete aoHelper;
	delete eepromHelper;
	//	releaseBoard(bus);
}


void AbNiAo::dowork() {
	// test gedata
	if (get_run_count() == 0) {
			NI_6363_ao[0] = 0.11;
			NI_6363_ao[1] = 0.12;
			NI_6363_ao[2] = 0.13;
			NI_6363_ao[3] = 0.14;
			/*LOG_E(g_logger, "AbNiAo, getdata error, set NI_6363_ao[] = "
				<< NI_6363_ao[0] << " "
				<< NI_6363_ao[1] << " "
				<< NI_6363_ao[2] << " "
				<< NI_6363_ao[3]);*/
	}
	for (unsigned int i = 0; i<CHANNELS_NUMBER; i++) {
		voltData[i] = NI_6363_ao[i];
	}
	output_data();
}

int AbNiAo::set_data(std::string p1, std::string p2) {

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
		std::cout << "ni6363_ao set CHANNELS_NUMBER " << CHANNELS_NUMBER << std::endl;
	}

	if (p1 == "channel") {
		float value = atof(p2.c_str());
		NI_6363_ao[0] = value;  // use channel 0 default, later can customer the channel by modify the code
	}

	if (p1 == "s") {
		std::stringstream ss;
		for (unsigned int i = 0; i<CHANNELS_NUMBER; i++) {
			ss << " ai" << i << "=" << NI_6363_ao[i] << " ";
		}
		std::cout << ss.str() << std::endl;
	}

	return 0;
}


int AbNiAo::init()
{
	// Create the board location string
	tChar brdLocation[256];
	sprintf(brdLocation, "PXI%s::%s::INSTR", brdLocation_1.c_str(), brdLocation_2.c_str());
	bus = NULL;
	bus = acquireBoard(brdLocation);
	if (bus == NULL)
	{
		printf("Could not access PCI device. Exiting.\n");
		exit(0);
	}
	/*********************************************************************\
	|
	|   Example parameters
	|
	\*********************************************************************/

	//
	// Feature Parameters (modify these to exercise the example)
	//

	// Channel parameters
	numberOfChannels = 4;                           // Channels: ao0:1
	numberOfChannels = CHANNELS_NUMBER;// zgz
	printVolts = kTrue;
	range = nNISTC3::kOutput_10V; // Range: +/- 10 Volts
	resetToZero = kTrue;

	// Buffer parameters
	sampsPerChan = 1;

	//
	// Fixed or calculated parameters (do not modify these)
	//

	// Channel parameters
	gain = 0;
	chanConfig = std::vector<nNISTC3::aoHelper::tChannelConfiguration>(numberOfChannels, nNISTC3::aoHelper::tChannelConfiguration());

	totalNumberOfSamples = numberOfChannels * sampsPerChan;

	voltData = std::vector<f32>(numberOfChannels, 0);
	scaledData = std::vector<i16>(totalNumberOfSamples, 0);


	// Bookkeeping
	status;
	aoErrored = kFalse; // Did the AO subsystem have an error?
	dacOverrun = nOutTimer::kNo_error;
	bar0;
	bar0 = bus->createAddressSpace(kPCI_BAR1);
	//bar0 = bus->createAddressSpace(kPCI_BAR0);



	/*********************************************************************\
	|
	|   Initialize the generation
	|
	\*********************************************************************/

	//
	// Open, detect, and initialize the X Series device
	//

	device = new tXSeries(bar0, &status);

	deviceInfo = nNISTC3::getDeviceInfo(*device, status);
	if (status.isFatal())
	{
		printf("Error: Cannot identify device (%d).\n", status.statusCode);
		exit(0);
	}

	if (deviceInfo->isSimultaneous) nNISTC3::initializeSimultaneousXSeries(*device, status);

	//
	// Create subsystem helpers
	//

	aoHelper = new nNISTC3::aoHelper(device->AO, device->AO.AO_Timer, status);
	eepromHelper = new nNISTC3::eepromHelper(*device, deviceInfo->isSimultaneous, deviceInfo->numberOfADCs, deviceInfo->numberOfDACs, status);

	//
	// Validate the Feature Parameters
	//

	// Ensure that the number of DACs match the number of channels requested
	if (numberOfChannels > deviceInfo->numberOfDACs)
	{
		printf("Error: Number of channels requested (%u) is greater than number of DACs on the device (%u).\n",
			numberOfChannels, deviceInfo->numberOfDACs);
		status.setCode(kStatusBadParameter);
		exit(0);
	}

	// Ensure that the range is supported by this board
	gain = deviceInfo->getAO_Gain(range, status);
	if (status.isFatal())
	{
		printf("Error: Unsupported range.\n");
		status.setCode(kStatusBadParameter);
		exit(0);
	}

	/*********************************************************************\
	|
	|   Program peripheral subsystems
	|
	\*********************************************************************/

	// No peripheral subsystems used in this example

	/*********************************************************************\
	|
	|   Program the AO subsystem
	|
	\*********************************************************************/

	//
	// Reset the AO subsystem
	//

	aoHelper->reset(status);

	//
	// Program AO channels
	//

	// Enter timing configuration mode
	device->AO.AO_Timer.Reset_Register.writeConfiguration_Start(kTrue, &status);

	// Set the configuration for each channel
	for (u32 i = 0; i<numberOfChannels; ++i)
	{
		chanConfig[i].channel = i; // aoN where N = i
		chanConfig[i].gain = gain; // Set the gain (used by the hardware)
		chanConfig[i].updateMode = nAO::kImmediate; // Set the update mode
		chanConfig[i].range = range; // Set the range (used by the scaler)

		aoHelper->programConfigBank(
			chanConfig[i],    // Set the channel configuration for this channel
			status);
	}

	// Leave timing configuration mode
	device->AO.AO_Timer.Reset_Register.writeConfiguration_End(kTrue, &status);

	return 0;
}

void AbNiAo::output_data() {

	/*********************************************************************\
	|
	|   Program output data
	|
	\*********************************************************************/

	//
	// Create, scale, and print output voltages
	//

	// Create zero voltage for each ao channel
	std::vector<f32> zeroVolts(numberOfChannels, 0);
	std::vector<i16> scaledZeroVolts(numberOfChannels, 0);
	nNISTC3::nAODataHelper::scaleData(zeroVolts, numberOfChannels,
		scaledZeroVolts, numberOfChannels,
		chanConfig, *eepromHelper);

	// Give aoHelper enough information to set output to 0V in the event of an error
	aoHelper->setZeroVolts(scaledZeroVolts, resetToZero, status);

	// Scale both waveforms
	nNISTC3::nAODataHelper::scaleData(voltData, totalNumberOfSamples,
		scaledData, totalNumberOfSamples,
		chanConfig, *eepromHelper);



	/*********************************************************************\
	|
	|   Write data
	|
	\*********************************************************************/


	// Update the channels individually
	for (unsigned int i = 0; i<numberOfChannels; ++i)
	{
		device->AO.AO_Direct_Data[i].writeRegister(scaledData[i], &status);
	}

	// Check for AO subsystem errors
	device->AO.AO_Timer.Status_1_Register.refresh(&status);
	dacOverrun = device->AO.AO_Timer.Status_1_Register.getOverrun_St(&status);


	/*********************************************************************\
	|
	|   Finalize the generation
	|
	\*********************************************************************/
	// Note: this error is unlikely to occur in this example because the
	// data is written between each update.
	if (dacOverrun)
	{
		printf("Error: DAC overrun.\n");
		status.setCode(kStatusRuntimeError);
	}

}