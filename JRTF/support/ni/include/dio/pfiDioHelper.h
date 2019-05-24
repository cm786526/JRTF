/*
 * pfiDioHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dio_pfiDioHelper_h___
#define ___dio_pfiDioHelper_h___

#include "dioHelper.h"
#include "tTriggers.h"

namespace nNISTC3
{
    class pfiDioHelper
    {
    public:
       pfiDioHelper(tTriggers& triggers, nMDBG::tStatus2 &status);
       ~pfiDioHelper();

       void setTristate(tBoolean tristateOnExit, nMDBG::tStatus2 &status);

       void reset( const tDigitalPowerupState* powerupStates,
                   u32                         numPowerupStates,
                   nMDBG::tStatus2&            status);

       // Returns the current value being sensed on the lines specified in the lineMask
       u32 readPresentValue( const tDigDataType lineMask,
                             tDigDataType&      value,
                             nMDBG::tStatus2&   status ) const;

       // Drives the value in newValue onto the lines specified by the lineMask
       u32 writePresentValue( const tDigDataType lineMask,
                              const tDigDataType newValue,
                              nMDBG::tStatus2&   status );

       // Configures the lines specified in the lineMask for the desired direction
       void configureLines( const tDigDataType      lineMask,
                            const tDigConfiguration configuration,
                            nMDBG::tStatus2&        status );

    private:
       enum
       {
          kNumLines = 16
       };

       tDigDataType _outSoftCopy;
       tTriggers&   _triggers;
       tBoolean     _tristate;
       const nMDBG::tStatus2& _exampleStatus;

       tDigDataType _readValue(nMDBG::tStatus2 &status) const;
       void _writeValue( const tDigDataType newValue,
                         const tDigDataType lineMask,
                         nMDBG::tStatus2&   status );
       void _configureLines( tDigConfiguration configuration,
                             tDigDataType      lineMask,
                             nMDBG::tStatus2&  status );
       void _writePFIOutputSelect( tDigDataType     lineMask,
                                   nMDBG::tStatus2& status,
                                   tBoolean         force = kFalse );

       // Usage guidelines
       pfiDioHelper& operator=(const pfiDioHelper &rhs);
       pfiDioHelper(const pfiDioHelper &rhs);

    };
}; // nNISTC3

#endif //___dio_pfiDioHelper_h___
