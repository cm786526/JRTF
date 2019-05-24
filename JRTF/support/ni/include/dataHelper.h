/*
 * dataHelper.h
 *
 * Scale and print device data.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dataHelper_h___
#define ___dataHelper_h___

#include <vector>

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// Chip Object Helpers
#include "devices.h"
#include "eepromHelper.h"
#include "inTimer/aiHelper.h"
#include "outTimer/aoHelper.h"

namespace nNISTC3
{
   namespace nAIDataHelper
   {
      // Scale data
      //   rawData:          vector that contains raw sample data
      //   rawDataLength:    number of elements in rawData
      //   scaledData:       vector that will contain scaled sample data
      //   scaledDataLength: number of elements in scaledData
      //   channelConfig:    vector of elements containing the channel configuration for each channel
      //   eepromHelper:     EEPROM accessor for scaling coefficients
      //   deviceInfo:       tDeviceInfo struct
      void scaleData( const std::vector<i16>&     rawData,
                      u32                         rawDataLength,
                      std::vector<f32>&           scaledData,
                      u32                         scaledDataLength,
                      const std::vector<nNISTC3::aiHelper::tChannelConfiguration>& channelConfig,
                      nNISTC3::eepromHelper&      eepromHelper,
                      const nNISTC3::tDeviceInfo& deviceInfo );

      // Interleave data
      //   sampsPerChannel:  number of samples for each channel in the data* arrays
      //   numberOfChannels: number of channels in each the data* arrays
      //   jointData:        vector that will contain the the interleaved data, must hold 2*sampsPerChannel*numberOfChannels elements
      //   data1:            vector that contains sample data, must hold sampsPerChannel*numberOfChannels elements
      //   data2:            vector that contains sample data, must hold sampsPerChannel*numberOfChannels elements
      template<typename T>
      void interleaveData( u32                   sampsPerChannel,
                           u32                   numberOfChannels,
                           std::vector<T>&       jointData,
                           const std::vector<T>& data1,
                           const std::vector<T>& data2 );

      // Print header
      //   numDevices:  number of devices in the measurement
      //   numChannels: number of channels for each device in the measurement
      //   label:       12-char or less title
      void printHeader( u32         numDevices,
                        u32         numChannels,
                        const char* label );

      // Print data
      //   data:             vector that contains data to print
      //   dataLength:       number of elements in data
      //   numberOfChannels: the number of channels interleaved in data
      template<typename T>
      void printData( const std::vector<T>& data,
                      u32                   dataLength,
                      u32                   numberOfChannels );

   } // nAIDataHelper

   namespace nAODataHelper
   {
      typedef enum
      {
         kSineWave = 0,
         kSquareWave,
         kRamp
      } tSignalType;

      // Generate a signal
      //   signalType:       the type of signal to generate
      //   minValue:         the minimum value the signal should have
      //   maxValue:         the maximum value the signal should have
      //   signalData:       vector that will contain the generated signal data
      //   signalDataLength: the number of elements in signalData
      void generateSignal( tSignalType       signalType,
                           f32               minValue,
                           f32               maxValue,
                           std::vector<f32>& signalData,
                           u32               signalDataLength );

      // Scale data
      //   voltData:         vector that contains Voltage data
      //   voltDataLength:   number of elements in voltData
      //   scaledData:       vector that will contain the scaled data
      //   scaledDataLength: number of elements in scaledData
      //   channelConfig:    vector of elements containing the channel configuration for each channel
      //   eepromHelper:     EEPROM accessor for scaling coefficients
      void scaleData( const std::vector<f32>& voltData,
                      u32                     voltDataLength,
                      std::vector<i16>&       scaledData,
                      u32                     scaledDataLength,
                      const std::vector<nNISTC3::aoHelper::tChannelConfiguration>& channelConfig,
                      nNISTC3::eepromHelper&  eepromHelper );

      // Interleave data
      //   sampsPerChannel:  number of samples for each channel in the data* arrays
      //   numberOfChannels: number of channels in each the data* arrays
      //   jointData:        vector that will contain the the interleaved data, must hold 2*sampsPerChannel*numberOfChannels elements
      //   data1:            vector that contains sample data, must hold sampsPerChannel*numberOfChannels elements
      //   data2:            vector that contains sample data, must hold sampsPerChannel*numberOfChannels elements
      template<typename T>
      void interleaveData( u32                   sampsPerChannel,
                           u32                   numberOfChannels,
                           std::vector<T>&       jointData,
                           const std::vector<T>& data1,
                           const std::vector<T>& data2 );

      // Print header
      //   numDevices:  number of devices in the measurement
      //   numChannels: number of channels for each device in the measurement
      //   label:       12-char or less title
      void printHeader( u32         numDevices,
                        u32         numChannels,
                        const char* label );

      // Print data
      //   data:             vector that contains data to print
      //   dataLength:       number of elements in data
      //   numberOfChannels: the number of channels interleaved in data
      template<typename T>
      void printData( const std::vector<T>& data,
                      u32                   dataLength,
                      u32                   numberOfChannels );

   } // nAODataHelper

   namespace nDIODataHelper
   {
      typedef union
      {
         u32 value;
         u8  byte[4];
      } tFourByteInt_t;

      // Print header
      //   port:        the port on the device
      void printHeader(u32 port);

      // Print data
      //   data:       vector byte-buffer that contains data to print
      //   dataLength: number of bytes (not samples) in the vector
      //   sampleSize: the size of a sample in bytes
      void printData( const std::vector<u8> data,
                      u32                   dataLength,
                      u32                   sampleSize );

   } // nDIOHelper

   namespace nGPCTDataHelper
   {
      // Frequency scaling information
      typedef struct
      {
         tBoolean isAveraged;     // Is the measurement averaged in hardware?
         f32 timebaseRate;        // The rate of the counter's source
      } tFrequencyScaler_t;

      // Encoder scaling information
      typedef struct
      {
         tBoolean isAngular;      // kTrue means angular, kFalse means linear
         u32 pulsesPerRevolution; // Applies only to angular encoders
         u32 distancePerPulse;    // Applies only to linear encoders
      } tEncoderScaler_t;

      // Digital waveform scaling information
      typedef struct
      {
         f32 timebaseRate;        // The rate of the counter's source
      } tDigWaveformScaler_t;

      // Pulse train scaling information
      typedef struct
      {
         f32 timebaseRate;        // The rate of the counter's source
      } tPulseTrainScaler_t;

      // Scale frequency data
      //   rawData:          vector that contains raw sample data
      //   rawDataLength:    number of elements in rawData
      //   scaledData:       vector that will contain scaled sample data
      //   scaledDataLength: number of elements in scaledData
      //   scaler:           frequency measurement parameters for scaling
      void scaleData( const std::vector<u32>&   rawData,
                      u32                       rawDataLength,
                      std::vector<f32>&         scaledData,
                      u32                       scaledDataLength,
                      const tFrequencyScaler_t& scaler );

      // Scale encoder data
      //   rawData:          array that contains raw sample data
      //   rawDataLength:    number of elements in rawData
      //   scaledData:       array that will contain scaled sample data
      //   scaledDataLength: number of elements in scaledData
      //   scaler:           encoder measurement parameters for scaling
      void scaleData( const std::vector<u32>& rawData,
                      u32                     rawDataLength,
                      std::vector<f32>&       scaledData,
                      u32                     scaledDataLength,
                      const tEncoderScaler_t& scaler );

      // Scale digital waveforms
      //   rawData:          array that contains digital waveform counts
      //   rawDataLength:    number of elements in rawData
      //   scaledData:       array that will contain the scaled data
      //   scaledDataLength: number of elements in scaledData
      //   scaler:           pulse train parameters for scaling
      void scaleData( const std::vector<u32>&     rawData,
                      u32                         rawDataLength,
                      std::vector<f32>&           scaledData,
                      u32                         scaledDataLength,
                      const tDigWaveformScaler_t& scaler );

      // Scale pulse train timing information
      //   timeData:         array that contains pulse train pulse timing
      //   timeDataLength:   number of elements in timeData
      //   scaledData:       array that will contain the scaled data
      //   scaledDataLength: number of elements in scaledData
      //   scaler:           pulse train parameters for scaling
      void scaleData( const std::vector<f32>&    timeData,
                      u32                        timeDataLength,
                      std::vector<u32>&          scaledData,
                      u32                        scaledDataLength,
                      const tPulseTrainScaler_t& scaler );

      // Print header
      //
      void printHeader( const char* label,
                        const char* units );


      // Print data
      //   data:             vector that contains data to print
      //   dataLength:       number of elements in data
      //   numberOfChannels: the number of channels interleaved in data
      template<typename T>
      void printData( const std::vector<T>& data,
                      u32                   dataLength,
                      u32                   numberOfChannels );

   } // nGPCTDataHelper
} // nNISTC3

#ifndef ___dataHelper_ipp___
#include "dataHelper.ipp"
#endif

#endif // ___dataHelper_h___
