// Copyright 2011 National Instruments
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

#ifndef ___dataHelper_ipp___
#define ___dataHelper_ipp___

#ifndef ___dataHelper_h___
#include "dataHelper.h"
#endif

namespace nNISTC3
{
   inline void printElement(i16 element)
   {
      printf("   0x%04hX    ", element);
   }

   inline void printElement(u32 element)
   {
      printf(" 0x%08X  ", element);
   }

   inline void printElement(f32 element)
   {
      printf(" %10.4f  ", element);
   }

   template<typename T>
   void printData( const std::vector<T>& data,
                   u32                   dataLength,
                   u32                   numberOfChannels,
                   const char*           label )
   {
      static u32 n = 0;  // Number of samples counter
      u32 m = 0;         // Number of channels counter

      for (u32 i=0; i<dataLength ; ++i)
      {
         if (m%numberOfChannels == 0)
         {
            printf("\n");
            printf("  %6s %6d: ", label, n+1);
            m = 0;
            ++n;
         }
         ++m;

         printElement(data[i]);
      }
   }

   namespace nAIDataHelper
   {
      template<typename T>
      void interleaveData( u32                   sampsPerChannel,
                           u32                   numberOfChannels,
                           std::vector<T>&       jointData,
                           const std::vector<T>& data1,
                           const std::vector<T>& data2 )
      {
         jointData.clear();
         jointData.reserve(2*sampsPerChannel); // Must hold both data1 and data2

         // Prepare interleaved data from one device with N channels to be
         // printed with interleaved data from another device with N channels.
         //   Example: interleave data1 and data2 with numberOfChannels == 2
         //     1.0 1.1 1.2 1.3 ...
         //     2.0 2.1 2.2 2.3 ...
         //   to make
         //     1.0 1.1 2.0 2.1 1.2 1.3 2.2 2.3 ...
         for (u32 i=0; i<sampsPerChannel; i+=numberOfChannels)
         {
            for (u32 k=0; k<numberOfChannels; ++k)
            {
               jointData.push_back(data1[i+k]);
            }

            for (u32 k=0; k<numberOfChannels; ++k)
            {
               jointData.push_back(data2[i+k]);
            }
         }
      }

      template<typename T>
      void printData( const std::vector<T>& data,
                      u32                   dataLength,
                      u32                   numberOfChannels )
      {
         nNISTC3::printData(data, dataLength, numberOfChannels, "Scan");
      }
   } // nAIDataHelper

   namespace nAODataHelper
   {
      template<typename T>
      void interleaveData( u32                   sampsPerChannel,
                           u32                   numberOfChannels,
                           std::vector<T>&       jointData,
                           const std::vector<T>& data1,
                           const std::vector<T>& data2 )
      {
         jointData.clear();
         jointData.reserve(numberOfChannels*sampsPerChannel);

         // Prepare data to be generated from separate, single waveforms. When
         // there are more than 2 output channels, repeat the data in the
         // higher channels.
         //   Example: interleave data1 and data2 with numberOfChannels == 3
         //     1.0 1.1 1.2 1.3 ...
         //     2.0 2.1 2.2 2.3 ...
         //   to make
         //     1.0 2.0 1.0 1.1 2.1 1.1 1.2 2.2 1.2 1.3 2.3 1.3 ...
         if ( (data1.size() < sampsPerChannel) || (data2.size() < sampsPerChannel) )
         {
            printf("Warning: Not interleaving because data vectors do not have the minimum number of elements.\n");
            return;
         }

         for (u32 i=0; i<sampsPerChannel; ++i)
         {
            for (u32 j=0; j<numberOfChannels; ++j)
            {
               if(j%2 == 0)
               {
                  jointData.push_back(data1[i]);
               }
               else
               {
                  jointData.push_back(data2[i]);
               }
            }
         }
      }

      template<typename T>
      void printData( const std::vector<T>& data,
                      u32                   dataLength,
                      u32                   numberOfChannels )
      {
         nNISTC3::printData(data, dataLength, numberOfChannels, "Update");
      }
   } // nAODataHelper

   namespace nGPCTDataHelper
   {
      template<typename T>
      void printData( const std::vector<T>& data,
                      u32                   dataLength,
                      u32                   numberOfChannels )
      {
         nNISTC3::printData(data, dataLength, numberOfChannels, "Sample");
      }
   } // nGPCTDataHelper
} // nNISTC3

#endif // ___dataHelper_ipp___
