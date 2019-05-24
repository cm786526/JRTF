/*
 * pllHelper.h
 *
 * Programs the PLL for X Series devices.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___pllHelper_h___
#define ___pllHelper_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// Chip objects
#include "tXSeries.h"

namespace nNISTC3
{
   enum referenceFrequency_t
   {
      kReference10MHz =    10,
      kReference20MHz =    20,
      kReference100MHz =   100,
   };

   typedef struct
   {
      // PLL multiplier and divisor variables
      referenceFrequency_t frequency;
      u16 pllDivisor;
      u16 pllMultiplier;
      u16 pllOutputDivider;
   } PLL_Parameters_t;

   class pllHelper
   {
   public:
      // Constructor
      //   xseries: the device chip object
      //   isPCIe:  is the device a PCIe-based device?
      //   status
      pllHelper( tXSeries&        xseries,
                 tBoolean         isPCIe,
                 nMDBG::tStatus2& status );

      ~pllHelper();

      // Phase-lock loop to an external clock to use as the master timebase.
      //   pllParameters:     PLL multiplier/divisor settings
      //   desiredPll_Source: the PFI/RTSI source for the external clock
      //   status
      void enablePLL( const PLL_Parameters_t&                 pllParameters,
                      nTriggers::tTrig_PLL_In_Source_Select_t desiredPLL_Source,
                      nMDBG::tStatus2&                        status );

      // Disable the phase-lock loop to an external clock, restores the
      // on-board timebase as the master timebase.
      void disablePLL (nMDBG::tStatus2& status);

   private:
      // Usage guidelines
      pllHelper(const pllHelper&);
      pllHelper& operator=(const pllHelper&);

   private:
      tXSeries&                               _xseries;
      nTriggers::tTrig_PLL_In_Source_Select_t _backupPLL_Source;
      tBoolean                                _isPCIe;
      tBoolean                                _pllIsEnabled;
   };
}

#endif // #ifndef ___pllHelper_h___
