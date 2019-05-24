/*
 * eepromHelper.h
 *
 * Reads information from the EEPROM of the device and provides scaling methods.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___eepromHelper_h___
#define ___eepromHelper_h___

#include <time.h>

#include "osiBus.h"

// Forward declarations
class tXSeries;

namespace nNISTC3
{
   static const u32 kNumAIScalingCoefficients = 4;
   struct tAIScalingCoefficients
   {
      f32 c[kNumAIScalingCoefficients];
   };
   inline f32 scale(i16 value, tAIScalingCoefficients& coefficients)
   {
      f32 result = 0;
      for (i32 j=kNumAIScalingCoefficients-1; j>=0; --j)
      {
         result *= value;
         result += coefficients.c[j];
      }
      return result;
   }

   static const u32 kNumAOScalingCoefficients = 2;
   struct tAOScalingCoefficients
   {
      f32 c[kNumAOScalingCoefficients];
   };
   inline i16 scale(f32 value, tAOScalingCoefficients& coefficients)
   {
      return static_cast<i16>(value * coefficients.c[1] + coefficients.c[0]);
   }

   class eepromHelper
   {
   public:
      eepromHelper( tXSeries&        xseries,
                    tBoolean         isSimultaneous,
                    u32              numberOfADCs,
                    u32              numberOfDACs,
                    nMDBG::tStatus2& status );
      ~eepromHelper();

      u32 getSerialNumber() { return _serialNumber; }
      u32 getGeographicalAddress() { return _geographicalAddress; }
      u32 getSTC3_Revision() { return _stc3Revision; }
      time_t getExtCalTime() { return _extCalTime; }
      f32 getExtCalTemp() { return _extCalTemp; }
      f32 getExtCalVoltRef() { return _extCalVoltRef; }
      time_t getSelfCalTime() { return _selfCalTime; }
      f32 getSelfCalTemp() { return _selfCalTemp; }
      f32 getSelfCalVoltRef() { return _selfCalVoltRef; }
      static const u32 kNumAIIntervals = 7;
      static const u32 kNumAOIntervals = 4;
      void getAIScalingCoefficients(u32 ADCNumber, u32 intervalNumber, tAIScalingCoefficients& coefficients, nMDBG::tStatus2& status);
      void getAOScalingCoefficients(u32 DACNumber, u32 intervalNumber, tAOScalingCoefficients& coefficients, nMDBG::tStatus2& status);

   private:
      static const u32 kCapabilitiesListFlagPtrOffset = 0x0C;
      static const u32 kCapabilitiesListAPtrOffset    = 0x10;
      static const u32 kCapabilitiesListBPtrOffset    = 0x14;

      static const u32 kGeographicalAddressingNodeID  = 0x4741;
      static const u32 kGAPointerOffset               = 0x4;
      static const u32 kGAInfoOffset                  = 0x8;
      static const u32 kGAShiftMask                   = 0x001F0000;
      static const u32 kGAShiftShift                  = 0x00000010;
      static const u32 kGAReadWidthMask               = 0x00000700;
      static const u32 kGAReadWidthShift              = 0x00000008;
      static const u32 kGAReadWidth8Bit               = 0x1;
      static const u32 kGAReadWidth16Bit              = 0x2;
      static const u32 kGAReadWidth32Bit              = 0x4;
      static const u32 kGASpaceMask                   = 0x0000000F;
      static const u32 kGALocalSpace                  = 0x1;
      static const u32 kGAMask                        = 0x1F;

      static const u32 kASIC_RevisionID               = 0x0002;

      static const u32 kSerialNumberNodeID            = 0x0004;
      static const u32 kSerialNumberOffset            = 0x4;

      static const u32 kDeviceSpecificNodeID          = 0x0001;
      static const u32 kDSNSizeOffset                 = 0x4;
      static const u32 kDSNBodyFormatOffset           = 0x8;
      static const u32 kDSNBodyFormat16BitValueID     = 0x1;
      static const u32 kDSNBodyFormat32BitValueID     = 0x2;
      static const u32 kDSNBodyFormat16BitIDValue     = 0x3;
      static const u32 kDSNBodyFormat32BitIDValue     = 0x4;
      static const u32 kDSNBodyOffset                 = 0xC;
      static const u32 kExtCalAPtrID                  = 0x40;
      static const u32 kExtCalBPtrID                  = 0x41;
      static const u32 kSelfCalAPtrID                 = 0x42;
      static const u32 kSelfCalBPtrID                 = 0x43;
      static const u32 kCalDataOffset                 = 0x2;
      // The following are relative to kCalDataOffset
      static const u32 kCalTimeLowerOffset            = 0x0;
      static const u32 kCalTimeUpperOffset            = 0x4;
      // The time stored in the EEPROM is relative to 1904. time_t is relative to 1970.
      static const u32 kCalTimeBias                   = 0x7c25b080;
      static const u32 kCalTemperatureOffset          = 0x8;
      static const u32 kCalVoltageRefOffset           = 0xC;
      static const u32 kCalCoefficientsOffset         = 0x10;

      static const u32 kNumModeCoefficients = 4;
      // This might not be strictly aligned, manually calculate.
      static const u32 kModeSizeInBytes = sizeof(u8) + 4*sizeof(f32);
      struct tMode
      {
          u8 order;
          f32 coefficients[kNumModeCoefficients];
      };

      static const u32 kIntervalSizeInBytes = 2*sizeof(f32);
      struct tInterval
      {
          f32 gain;
          f32 offset;
          tBoolean valid;
      };

      static const u32 kNumAIModes = 4;
      struct tAICalibration
      {
         tMode modes[kNumAIModes];
         tInterval intervals[kNumAIIntervals];
      };
      struct tAOCalibration
      {
         tMode mode;
         tInterval intervals[kNumAOIntervals];
      };

      void _traverseCapabilitiesList(u32 nodeAddress, nMDBG::tStatus2& status);
      void _parseGeographicalAddressingNode(u32 nodeAddress, nMDBG::tStatus2& status);
      void _parseSerialNumberNode(u32 nodeAddress, nMDBG::tStatus2& status);
      void _parseDeviceSpecificNode(u32 nodeAddress, nMDBG::tStatus2& status);
      void _readMode(u32 address, tMode& mode);
      void _readInterval(u32 address, tInterval& interval);
      u32 _getOffsetForPages(u32 aOffset, u32 bOffset, nMDBG::tStatus2& status);

      void _shiftWindow(u32 address);
      u8   _readU8(u32 address);
      u16  _readU16(u32 address);
      u32  _readU32(u32 address);
      f32  _readF32(u32 address);

      // Static information
      tBusSpaceReference _eeprom;
      tXSeries&          _xseries;
      const tBoolean     _isSimultaneous;
      u32                _baseAddress;
      const u32          _numberOfADCs;
      const u32          _numberOfDACs;

      u32 _serialNumber;
      u32 _geographicalAddress;
      u32 _stc3Revision;

      // Cal info
      time_t          _extCalTime;
      f32             _extCalTemp;
      f32             _extCalVoltRef;
      time_t          _selfCalTime;
      f32             _selfCalTemp;
      f32             _selfCalVoltRef;
      tAICalibration* _aiCalInfo;
      tAOCalibration* _aoCalInfo;

      // Usage guidelines
      eepromHelper(const eepromHelper&);
      eepromHelper& operator=(const eepromHelper&);
   };
}

#endif // ___eepromHelper_h___
