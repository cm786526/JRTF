/*
 * tLinkInformation.h
 *
 * Define a struct for decoupling SGL generation from programming the DMA
 * controller.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tLinkInformation_h___
#define ___tLinkInformation_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

namespace nNISTC3
{
   struct tLinkInformation
   {
      u64 chlar;  // Channel Link Address Register
      u32 chlsr;  // Channel Link Size Register

      tLinkInformation() :
         chlar(0),
         chlsr(0)
      {
         // Nothing else to initialize
      }

      tLinkInformation(u64 chlar_, u32 chlsr_) :
         chlar(chlar_),
         chlsr(chlsr_)
      {
         // Nothing else to initialize
      }

   }; // tLinkInformation
} // nNISTC3

#endif // ___tLinkInformation_h___
