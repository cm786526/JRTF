/*
 * dmaErrors.h
 *
 * Describe error codes for DMA channel and buffer objects
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dmaErrors_h___
#define ___dmaErrors_h___

#include "osiTypes.h"

namespace nNISTC3
{
   const i32 kDMAErrorOffset   = -80000;
   const i32 kDMAWarningOffset =  80000;

   typedef enum
   {
      kNoDMAError                    =     0,
      kBufferBadMemoryAllocation     = (   0 + kDMAErrorOffset),
      kBufferOverflow                = (  -1 + kDMAErrorOffset),
      kBufferUnderflow               = (  -2 + kDMAErrorOffset),
      kWrongChannelState             = (  -3 + kDMAErrorOffset),
      kInvalidChannel                = (  -4 + kDMAErrorOffset),
      kInvalidInput                  = (  -5 + kDMAErrorOffset),
      kBufferInitializationError     = (  -6 + kDMAErrorOffset),
      kDMAChunkyLinkMemoryFull       = (  -7 + kDMAErrorOffset),
      kBufferBadAlignment            = (  -8 + kDMAErrorOffset),
      kBadDMAChannel                 = (  -9 + kDMAErrorOffset),
      kBadBuffer                     = ( -10 + kDMAErrorOffset),
      kBadCHInCh                     = ( -11 + kDMAErrorOffset)
   } tDMAError;

   typedef enum
   {
      kDataNotAvailable              = (  0 + kDMAWarningOffset),
      kSpaceNotAvailable             = (  1 + kDMAWarningOffset)
   } tDMAWarning;
} // nNISTC3

#endif // ___dmaErrors_h___
