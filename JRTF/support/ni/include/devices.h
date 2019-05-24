/*
 * devices.h
 *
 * Given an X Series device, find the information we care about for it.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___devices_h___
#define ___devices_h___

// OS Interface (for basic datatype names)
#include "eepromHelper.h"
#include "osiTypes.h"

// Forward declarations
class tXSeries;

namespace nNISTC3
{
   typedef enum
   {
      kInput_10V = 0,   // Range = +/-10V
      kInput_5V,        // Range = +/-5V
      kInput_2V,        // Range = +/-2V
      kInput_1V,        // Range = +/-1V
      kInput_500mV,     // Range = +/-500mV
      kInput_200mV,     // Range = +/-200mV
      kInput_100mV,     // Range = +/-100mV
   } tInputRange;

   typedef enum
   {
      kOutput_10V = 0,  // Range = +/-10V
      kOutput_5V,       // Range = +/-5V
      kOutput_APFI0,    // Range = +/-APFI0 External Reference Voltage
      kOutput_APFI1,    // Range = +/-APFI1 External Reference Voltage
   } tOutputRange;

   struct aiRangeGain
   {
      tInputRange range;
      u16 gain;
   };

   struct aoRangeGain
   {
      tOutputRange range;
      u8 gain;
   };

   struct tDeviceInfo
   {
      u16 getAI_Gain(tInputRange range, nMDBG::tStatus2& status) const;
      u8 getAO_Gain(tOutputRange range, nMDBG::tStatus2& status) const;

      u32 productID;
      const char* deviceName;
      tBoolean isSimultaneous;
      tBoolean isPCIe;
      u32 numberOfADCs;
      u32 numberOfAIChannels;
      const aiRangeGain ** aiRangeGainMap;
      u32 numberOfDACs;
      const aoRangeGain ** aoRangeGainMap;
      u32 port0Length;
   };

   const tDeviceInfo* getDeviceInfo(tXSeries& xseries, nMDBG::tStatus2& status);
}

#endif // ___devices_h___
