#include"AbNiDo.h"

AbNiDo::~AbNiDo()
{
	delete device;
	delete dioHelper;
	delete pfiDioHelper;
	//	releaseBoard(bus);
}

AbNiDo::AbNiDo() {
	brdLocation_1 = "0";
	brdLocation_2 = "0";

}


void AbNiDo::dowork() {

	// test getdata
	if (get_run_count() == 0) {
		
	}

	//get data from ABproc
	/*safe_get_data_from_other("do", &outputDataPort0, sizeof(outputDataPort0));
	safe_get_data_from_other("do_2", &outputDataPFI, sizeof(outputDataPFI));*/


	/*********************************************************************\
	|
	|   Write data
	|
	\*********************************************************************/

	//	printf("Writing 0x%0X to port0.\n", outputDataPort0 & lineMaskPort0);
	dioHelper->writePresentValue(lineMaskPort0, outputDataPort0, status);

	//	printf("Writing 0x%0X to port1.\n", outputDataPort1 & lineMaskPort1);
	//	printf("Writing 0x%0X to port2.\n", outputDataPort2 & lineMaskPort2);
	pfiDioHelper->writePresentValue(lineMaskPFI, outputDataPFI, status);

}

int AbNiDo::set_data(std::string p1, std::string p2) {

	if (p1 == "brdLocation_1") {
		brdLocation_1 = p2;
	}
	if (p1 == "brdLocation_2") {
		brdLocation_2 = p2;
	}

	if (p1 == "lineMaskPort0") {
		std::stringstream ss(p2);
		std::string value = "";
		std::string base = "";
		ss >> value >> base;
		if (base == "binary") {
			// base 2 ---> 10
			lineMaskPort0 = strtoul(p2.c_str(), NULL, 2);
		}
		else {
			// base 8 10 16 ---> 10
			lineMaskPort0 = strtoul(p2.c_str(), NULL, 0);
		}
		std::bitset<32> b = lineMaskPort0;
		std::cout << "Set lineMaskPort0 = " << b << std::endl;
	}

	if (p1 == "lineMaskPFI") {
		std::stringstream ss(p2);
		std::string value = "";
		std::string base = "";
		ss >> value >> base;
		if (base == "binary") {
			// base 2 ---> 10
			lineMaskPFI = strtoul(p2.c_str(), NULL, 2);
		}
		else {
			// base 8 10 16 ---> 10
			lineMaskPFI = strtoul(p2.c_str(), NULL, 0);
		}
		std::bitset<32> b = lineMaskPFI;
		std::cout << "Set lineMaskPFI = " << b << std::endl;
	}


	// show di data
	if (p1 == "s") {
		std::bitset<32> bbb = outputDataPort0;
		std::bitset<32> bbb2 = outputDataPFI;

		std::cout << " channel(*10) " << "33222222222211111111110000000000" << std::endl
			<< " channel(*01) " << "10987654321098765432109876543210" << std::endl
			<< COLOR_WARN
			<< "  dio value = " << bbb
			<< COLOR_DEF
			<< std::endl;
		std::cout << " channel(*10)     " << "33222222222211111111110000000000" << std::endl
			<< " channel(*01)     " << "10987654321098765432109876543210" << std::endl
			<< COLOR_WARN
			<< "  dio_pfi value = " << bbb2
			<< COLOR_DEF
			<< std::endl;
	}

	// update port0
	if (p1 == "u") {
		std::stringstream ss(p2);
		int channel = 0;
		int value = 0;

		if (ss >> channel >> value) {
			std::bitset<32> bbb = outputDataPort0;
			bbb[channel] = value;
			outputDataPort0 = bbb.to_ulong();
			dioHelper->writePresentValue(lineMaskPort0, outputDataPort0, status);
		}
	}

	return 0;
}


int AbNiDo::init()
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

	// Channel parameters
	//	lineMaskPort0 = 0xFFFF0000; // Use low 16 bits as di, high 16 bits as do
	u8 lineMaskPort1 = 0xFF; // Use all the lines on port1
	u8 lineMaskPort2 = 0xFF; // Use all the lines on port2
	tristateOnExit = kTrue;

	// Buffer parameters
	outputDataPort0 = 0x0; // Value to write to port0
	outputDataPort1 = 0x0; // Value to write to port1
	outputDataPort2 = 0x0; // Value to write to port2

						   //
						   // Fixed or calculated parameters (do not modify these)
						   //

						   // Channel parameters
	port0Length = 0;
	port1Length = 8;
	//	lineMaskPFI = (lineMaskPort2 << port1Length) | lineMaskPort1;
	//	lineMaskPFI = 0xFF00; // Use low 8 bits as di, high 8 bits as do

	// Buffer parameters
	outputDataPFI = (outputDataPort2 << port1Length) | outputDataPort1;
	inputDataPort0 = 0x0; // Value of lines on port0
	inputDataPFI = 0x0; // Value of lines on port1:2 (PFI0..15)

						// Bookkeeping
	status;
	bar0;
	bar0 = bus->createAddressSpace(kPCI_BAR1);
	//bar0 = bus->createAddressSpace(kPCI_BAR0);



	/*********************************************************************\
	|
	|   Initialize the operation
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

	// Determine the size of Port 0
	port0Length = deviceInfo->port0Length;

	if (port0Length == 32)
	{
		// Port 0 has 32 lines for hardware-timed DIO
		lineMaskPort0 &= static_cast<u32>(nDI::nDI_FIFO_Data_Register::nCDI_FIFO_Data::kMask);
	}
	else
	{
		// Port 0 has 8 lines for hardware-timed DIO
		lineMaskPort0 &= static_cast<u32>(nDI::nDI_FIFO_Data_Register8::nCDI_FIFO_Data8::kMask);
	}

	//
	// Create subsystem helpers
	//

	dioHelper = new nNISTC3::dioHelper(device->DI, device->DO, status);
	dioHelper->setTristate(tristateOnExit, status);
	pfiDioHelper = new nNISTC3::pfiDioHelper(device->Triggers, status);
	pfiDioHelper->setTristate(tristateOnExit, status);

	//
	// Validate the Feature Parameters
	//

	// Nothing else to validate

	/*********************************************************************\
	|
	|   Program peripheral subsystems
	|
	\*********************************************************************/

	// No peripheral subsystems used in this example

	/*********************************************************************\
	|
	|   Program the digital subsystem
	|
	\*********************************************************************/

	//
	// Reset the digital subsystem (port 0)
	//

	dioHelper->reset(NULL, 0, status);

	//
	// Program lines for output
	//

	dioHelper->configureLines(lineMaskPort0, nNISTC3::kOutput, status);

	/*********************************************************************\
	|
	|   Program the PFI subsystem
	|
	\*********************************************************************/

	//
	// Reset the PFI subsystem (ports 1 and 2)
	//

	pfiDioHelper->reset(NULL, 0, status);

	//
	// Program lines for output
	//
	pfiDioHelper->configureLines(lineMaskPFI, nNISTC3::kOutput, status);
	return 0;
}