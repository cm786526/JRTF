/*
 * simultaneousInit.h
 *
 * Initializes simultaneous X Series boards.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___simultaneousInit_h___
#define ___simultaneousInit_h___

// OS Interface
#include "osiBus.h"

// Forward declarations
class tXSeries;

namespace nNISTC3
{
   // Simultaneous AI Configuration Registers
   static const u32  kSimultaneousAIConfiguration0Address   = 0x0002028A;
   static const u16  kSimultaneousAIConfiguration0Value     = 0x0000080C;
   static const u32  kSimultaneousAIConfiguration1Address   = 0x0002000E;
   static const u16  kSimultaneousAIConfiguration1Value     = 0x00000001;

   void initializeSimultaneousXSeries(tXSeries& xseries, nMDBG::tStatus2& status);
}

#endif // ___simultaneousInit_h___
