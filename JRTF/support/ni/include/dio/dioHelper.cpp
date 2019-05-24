/*
 * dioHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "dioHelper.h"

namespace nNISTC3
{
   dioHelper::dioHelper( tDI&             diRef,
                         tDO&             doRef,
                         nMDBG::tStatus2& status ) :
      _outMask(0),
      _inMask(0xFFFFFFFF >> (32 - kNumLines)),
      _outSoftCopy(0),
      _di(diRef),
      _do(doRef),
      _cdoMask(0),
      _cdiMask(0),
      _tristate(kTrue),
      _exampleStatus(status)
   {
      if (status.isFatal()) return;
   }

   dioHelper::~dioHelper()
   {
      if (_tristate || _exampleStatus.isFatal())
      {
         nMDBG::tStatus2 status;
         reset(NULL, 0, status);
      }
   }

   void dioHelper::setTristate(tBoolean tristateOnExit, nMDBG::tStatus2 &status)
   {
      if (status.isFatal()) return;

      _tristate = tristateOnExit;
   }

   static const tDigitalPowerupState sDefaultPowerupStates[] = {
      {kTrue, 0xFFFFFFFF, 0x00000000}
   };

   void dioHelper::reset( const tDigitalPowerupState* powerupStates,
                          u32                         numPowerupStates,
                          nMDBG::tStatus2&            status )
   {
      if (status.isFatal()) return;

      if (numPowerupStates == 0)
      {
         powerupStates = sDefaultPowerupStates;
         numPowerupStates = sizeof(sDefaultPowerupStates)/sizeof(sDefaultPowerupStates[0]);
      }

      _outSoftCopy = ((_di.Static_Digital_Input_Register.readRegister(&status) & powerupStates->highImp) |
                      (powerupStates->outputValue & ~(powerupStates->highImp)));

      _cdoMask = 0;
      _cdiMask = 0;
      _outMask = ~(powerupStates->highImp);
      _inMask  = powerupStates->highImp;

      // Force hardware to a known state
      _do.Static_Digital_Output_Register.writeDO_StaticValue(_outSoftCopy, &status, kTrue);
      _do.DO_Mask_Enable_Register.writeRegister(_cdoMask, &status, kTrue);
      _do.DIO_Direction_Register.writeRegister(_outMask, &status, kTrue);

      _di.DI_Mask_Enable_Register.writeRegister(_cdiMask, &status, kTrue);
   }

   u32 dioHelper::writePresentValue( const tDigDataType lineMask,
                                     const tDigDataType newValue,
                                     nMDBG::tStatus2&   status )
   {
      if (status.isFatal()) return 0;

      // Invert the line mask, AND it with the soft copy, OR it with the new
      // value to be written (in other words, zero the bits for the lines of
      // interest and OR them with the new value for those lines).
      _outSoftCopy = ((_outSoftCopy & (~lineMask)) | (lineMask & newValue));
      _writeValue(_outSoftCopy, status);

      if (status.isFatal()) return 0;
      else return 1;
   }

   u32 dioHelper::readPresentValue( const tDigDataType lineMask,
                                    tDigDataType&      value,
                                    nMDBG::tStatus2&   status ) const
   {
      value = 0;

      if (status.isFatal()) return 0;

      value = (_readValue(status) & lineMask);

      if (status.isFatal()) return 0;
      else return 1;
   }

   tDigDataType dioHelper::_readValue(nMDBG::tStatus2 &status) const
   {
      return _di.Static_Digital_Input_Register.readRegister(&status);
   }

   void dioHelper::_writeValue(const tDigDataType newValue, nMDBG::tStatus2 &status)
   {
      _do.Static_Digital_Output_Register.writeDO_StaticValue(newValue, &status);
   }

   void dioHelper::configureLines( const tDigDataType      lineMask,
                                   const tDigConfiguration configuration,
                                   nMDBG::tStatus2&        status )
   {
      if (status.isFatal()) return;

      // Check to see if the lines need to be configured.
      // If the soft copies match the requested configuration and the registers
      // are not dirty, no action required.
      if (!(_do.DIO_Direction_Register.isDirty(&status) ||
            _do.DO_Mask_Enable_Register.isDirty(&status) ||
            _di.DI_Mask_Enable_Register.isDirty(&status)) &&
          (((kInput == configuration)  && (lineMask == (lineMask & _inMask))) ||
           // If it is output we need to check that it is not in the _cdoMask
           ((kOutput == configuration) && (lineMask == (lineMask & _outMask)) && !(lineMask & _cdoMask)) ||
           ((kCorrInput == configuration) && (lineMask == (lineMask & _cdiMask))) ||
           ((kCorrOutput == configuration) && (lineMask == _cdoMask)))) return;

      tDigDataType cdoPreserveMask=0;

      // Set and clear the bits in the appropriate masks.
      // The in/out mask should be compliments of each other.
      // Since CDI/CDO can only have one task, they will only have one configure call and it is therefore
      // legal to assign the mask directly.
      // The in/out mask serve to denote direction and must be updated for correlated tasks as well as static.
      switch (configuration)
      {
      case kInput:
      {
         _inMask |= lineMask;
         _outMask &= ~(lineMask);
         _cdiMask &= ~(lineMask);
         _cdoMask &= ~(lineMask);
      }
      break;

      case kCorrInput:
      {
         _inMask |= lineMask;
         _outMask &= ~(lineMask);
         _cdiMask = lineMask;
         _cdoMask &= ~(lineMask);
      }
      break;

      case kOutput:
      {
         _inMask &= ~(lineMask);
         _outMask |= lineMask;
         _cdiMask &= ~(lineMask);
         _cdoMask &= ~(lineMask);
      }
      break;

      case kCorrOutput:
      {
         // Task A does CDO on 1-16, task B does CDO on 10-20 keep values on 1-9 when swiching from A to B
         cdoPreserveMask = (_cdoMask^lineMask) &(~lineMask);
         _inMask &= ~(lineMask);
         _outMask |= lineMask | cdoPreserveMask;
         _cdiMask &= ~(lineMask);
         _cdoMask = lineMask;
      }
      break;

      default:
      {
         return;
      }
      }

      if (cdoPreserveMask)
      {
         tDigDataType temp;
         temp = _readValue (status);
         _writeValue(temp,status);
      }
      _configureLines(configuration, lineMask, status);

      return;
   }

   void dioHelper::_configureLines( tDigConfiguration configuration,
                                    tDigDataType      lineMask,
                                    nMDBG::tStatus2&  status )
   {
      nNIOSINT100_mUnused(lineMask);
      // For the STC3, 1=output and 0=input so always use the _outMask to set the value in
      // the configuration register.

      // If tristating lines, then write the direction register prior to updating the
      // correlated digital masks to avoid glitching to the static digital value.
      if (configuration == kInput || configuration == kCorrInput)
      {
         _do.DIO_Direction_Register.setRegister(_outMask, &status);
         _do.DIO_Direction_Register.flush(&status);
      }

      // It is essential to always write changes to the _cdoMask since they will route back to static
      // digital when necessary.
      _do.DO_Mask_Enable_Register.setRegister(_cdoMask, &status);
      _do.DO_Mask_Enable_Register.flush(&status);
      _di.DI_Mask_Enable_Register.setRegister(_cdiMask, &status);
      _di.DI_Mask_Enable_Register.flush(&status);

      // If driving lines, then write the direction register after updating the correlated
      // digital masks to avoid glitching to the static digital value.
      if (configuration == kOutput || configuration == kCorrOutput)
      {
         _do.DIO_Direction_Register.setRegister(_outMask, &status);
         _do.DIO_Direction_Register.flush(&status);
      }
   }
} // nNISTC3
