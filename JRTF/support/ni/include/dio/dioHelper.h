/*
 * dioHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dio_dioHelper_h___
#define ___dio_dioHelper_h___

#include "tDI.h"
#include "tDO.h"

namespace nNISTC3
{
    typedef u32 tDigDataType;

    enum tDigConfiguration
    {
       kInput=0,         // Static input
       kOutput=1,        // Static output
       kNotConfigured=2,
       kCorrInput=6,     // Correlated input
       kCorrOutput=7,    // Correlated output
    };

    struct tDigitalPowerupState
    {
       tBoolean enable;
       u32 highImp;     // Mask
       u32 outputValue; // Value
    };

    class dioHelper
    {
    public:
       dioHelper( tDI&             diRef,
                  tDO&             doRef,
                  nMDBG::tStatus2& status );
       virtual ~dioHelper();

       void setTristate(tBoolean tristateOnExit, nMDBG::tStatus2 &status);

       void reset( const tDigitalPowerupState* powerupStates,
                   u32                         numPowerupStates,
                   nMDBG::tStatus2&            status );

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
          kNumLines = 32
       };

       tDigDataType _readValue(nMDBG::tStatus2 &status) const;
       void _writeValue(const tDigDataType newValue, nMDBG::tStatus2 &status);
       void _configureLines( tDigConfiguration configuration,
                             tDigDataType      lineMask,
                             nMDBG::tStatus2&  status);

       tDigDataType _outMask;
       tDigDataType _inMask;
       tDigDataType _outSoftCopy;

       tDI&         _di;
       tDO&         _do;
       tDigDataType _cdoMask;
       tDigDataType _cdiMask;

       tBoolean     _tristate;
       const nMDBG::tStatus2& _exampleStatus;

       // Usage guidelines
       dioHelper& operator=(const dioHelper &rhs);
       dioHelper(const dioHelper &rhs);
    };

} // nNISTC3

#endif //___dio_dioHelper_h___
