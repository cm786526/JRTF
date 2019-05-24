/*
 * counterResetHelper.h
 *
 * Helper for reseting counters.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___counterResetHelper_h___
#define ___counterResetHelper_h___

#include "osiBus.h"

// Forward declarations
class tCounter;

namespace nNISTC3
{
   class counterResetHelper
   {
   public:
      // Constructor
      // counter:             the counter object
      // preserveOutputState: counter output continues to output after reset
      // status
      counterResetHelper( tCounter&        counter,
                          tBoolean         preserveOutputState,
                          nMDBG::tStatus2& status );

      ~counterResetHelper();

      // Reset the counter
      // initialReset: initial reset call in an example
      // status
      void reset( tBoolean         initialReset,
                  nMDBG::tStatus2& status );

   private:
      // Usage guidelines
      counterResetHelper(const counterResetHelper&);
      counterResetHelper& operator=(const counterResetHelper&);

      tCounter&               _counter;
      tBoolean                _preserveOutputState;
      const nMDBG::tStatus2&  _exampleStatus;
   };
}

#endif // ___counterResetHelper_h___
