/*
 * pfiRtsiResetHelper.h
 *
 * Reset for PFI and RTSI lines results in all pins set to input.
 * The reset can be called explicitly or by letting the helper go out of scope (destructor).
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___pfiRtsiResetHelper_h___
#define ___pfiRtsiResetHelper_h___

#include "osiBus.h"

// Forward declarations
class tTriggers;

namespace nNISTC3
{
   class pfiRtsiResetHelper
   {
   public:
      // Constructor
      // triggers:            the trigger object
      // preserveOutputState: PFI and RTSI lines should not be changed to input during reset
      // status
      pfiRtsiResetHelper( tTriggers&       triggers,
                          tBoolean         preserveOutputState,
                          nMDBG::tStatus2& status );

      ~pfiRtsiResetHelper();

      // Changes the direction of all PFI and RTSI lines to input
      // status
      void reset(nMDBG::tStatus2& status);

   private:
      // Usage guidelines
      pfiRtsiResetHelper(const pfiRtsiResetHelper&);
      pfiRtsiResetHelper& operator=(const pfiRtsiResetHelper&);

      tTriggers&              _triggers;
      tBoolean                _preserveOutputState;
      const nMDBG::tStatus2&  _exampleStatus;
   };
}

#endif // ___pfiRtsiResetHelper_h___
