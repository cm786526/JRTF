/*
 * pfiDioHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "pfiDioHelper.h"

namespace nNISTC3
{
   // Helper switch function: placed in an unnamed namespace since it should
   // never be accessed outside this file.
   namespace {
      inline tTriggers::tId registerFieldIDForPFILine(u32 pfiLine)
      {
         switch (pfiLine)
         {
         case 0  : return tTriggers::kPFI_OutputSelectRegister_i0Id;
         case 1  : return tTriggers::kPFI_OutputSelectRegister_i1Id;
         case 2  : return tTriggers::kPFI_OutputSelectRegister_i2Id;
         case 3  : return tTriggers::kPFI_OutputSelectRegister_i3Id;
         case 4  : return tTriggers::kPFI_OutputSelectRegister_i4Id;
         case 5  : return tTriggers::kPFI_OutputSelectRegister_i5Id;
         case 6  : return tTriggers::kPFI_OutputSelectRegister_i6Id;
         case 7  : return tTriggers::kPFI_OutputSelectRegister_i7Id;
         case 8  : return tTriggers::kPFI_OutputSelectRegister_i8Id;
         case 9  : return tTriggers::kPFI_OutputSelectRegister_i9Id;
         case 10 : return tTriggers::kPFI_OutputSelectRegister_i10Id;
         case 11 : return tTriggers::kPFI_OutputSelectRegister_i11Id;
         case 12 : return tTriggers::kPFI_OutputSelectRegister_i12Id;
         case 13 : return tTriggers::kPFI_OutputSelectRegister_i13Id;
         case 14 : return tTriggers::kPFI_OutputSelectRegister_i14Id;
         case 15 : return tTriggers::kPFI_OutputSelectRegister_i15Id;
         default :
         {
            return tTriggers::kMaxRegisterId;
         }
         }
      }
   }

   pfiDioHelper::pfiDioHelper( tTriggers&       triggers,
                               nMDBG::tStatus2& status ) :
      _outSoftCopy(0),
      _triggers(triggers),
      _tristate(kTrue),
      _exampleStatus(status)
   {
      if (status.isFatal()) return;
   }

   pfiDioHelper::~pfiDioHelper()
   {
      if (_tristate || _exampleStatus.isFatal())
      {
         nMDBG::tStatus2 status;
         reset(NULL, 0, status);
      }
   }

   void pfiDioHelper::setTristate( tBoolean         tristateOnExit,
                                   nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _tristate = tristateOnExit;
   }

   static const tDigitalPowerupState sDefaultPowerupStates[] = {
      {kTrue, 0x000000FF, 0x00000000},
      {kTrue, 0x000000FF, 0x00000000}
   };

   void pfiDioHelper::reset( const tDigitalPowerupState* powerupStates,
                             u32                         numPowerupStates,
                             nMDBG::tStatus2&            status )
   {
      if (status.isFatal()) return;

      if (numPowerupStates == 0)
      {
         powerupStates = sDefaultPowerupStates;
         numPowerupStates = sizeof(sDefaultPowerupStates)/sizeof(sDefaultPowerupStates[0]);
      }

      u32 inputMask = powerupStates[0].highImp | (powerupStates[1].highImp << 8);

      _outSoftCopy = ((_triggers.PFI_DI_Register.readRegister(&status) & inputMask) |
                      ((powerupStates[0].outputValue |
                        powerupStates[1].outputValue << 8) & ~inputMask)) & 0xFFFF;

      // Force hardware to a known state
      _triggers.PFI_DO_Register.writePFI_DO_Bf(static_cast<u16>(_outSoftCopy), &status);
      _writePFIOutputSelect(~inputMask, status, kTrue);
      _triggers.PFI_Direction_Register.writeRegister(static_cast<u16>(~inputMask), &status);
   }

   u32 pfiDioHelper::readPresentValue( const tDigDataType lineMask,
                                       tDigDataType&      value,
                                       nMDBG::tStatus2&   status ) const
   {
      value = 0;

      if (status.isFatal()) return 0; // Read 0 items

      value = (_readValue(status) & lineMask);

      return 1; // Read 1 item
   }

   u32 pfiDioHelper::writePresentValue( const tDigDataType lineMask,
                                        const tDigDataType newValue,
                                        nMDBG::tStatus2&   status )
   {
      if (status.isFatal()) return 0;

      // Invert the line mask, AND it with the soft copy, OR it with the new
      // value to be written (in other words, zero the bits for the lines of
      // interest and OR them with the new value for those lines).
      _outSoftCopy = ((_outSoftCopy & (~lineMask)) | (lineMask & newValue));
      _writeValue(_outSoftCopy, lineMask, status);

      if (status.isFatal()) return 0;
      else return 1;
   }

   void pfiDioHelper::configureLines( const tDigDataType      lineMask,
                                      const tDigConfiguration configuration,
                                      nMDBG::tStatus2&        status )
   {
      if (status.isFatal()) return;

      _configureLines(configuration, lineMask, status);
   }

   tDigDataType pfiDioHelper::_readValue(nMDBG::tStatus2 &status) const
   {
      return _triggers.PFI_DI_Register.readRegister(&status);
   }

   void pfiDioHelper::_writeValue( const tDigDataType newValue,
                                   const tDigDataType lineMask,
                                   nMDBG::tStatus2&   status )
   {
      nNIOSINT100_mUnused(lineMask);
      _triggers.PFI_DO_Register.writePFI_DO_Bf(static_cast<u16>(newValue), &status);
   }

   void pfiDioHelper::_configureLines( tDigConfiguration configuration,
                                       tDigDataType      lineMask,
                                       nMDBG::tStatus2&  status )
   {
      if (status.isFatal()) return;

      u32 oldDirectionMask = _triggers.PFI_Direction_Register.getRegister(&status);
      u32 newDirectionMask = ~0UL;

      if (configuration == kInput)
      {
         newDirectionMask = oldDirectionMask & ~lineMask;
      }
      else if (configuration == kOutput)
      {
         newDirectionMask = oldDirectionMask | lineMask;

         _writePFIOutputSelect(lineMask, status);
      }
      else
      {
          return;
      }

      // Update the lower 8 PFI lines (port1) and then the upper 8 PFI lines (port2).

      u32 currentDirectionMask = oldDirectionMask;
      if (lineMask & 0x00FF)
      {
         currentDirectionMask = (currentDirectionMask & 0xFF00) | (newDirectionMask & 0x00FF);
         _triggers.PFI_Direction_Register.setRegister(static_cast<u16>(currentDirectionMask), &status);
         _triggers.PFI_Direction_Register.flush(&status);
      }
      if (lineMask & 0xFF00)
      {
         currentDirectionMask = (currentDirectionMask & 0x00FF) | (newDirectionMask & 0xFF00);
         _triggers.PFI_Direction_Register.setRegister(static_cast<u16>(currentDirectionMask), &status);
         _triggers.PFI_Direction_Register.flush(&status);
      }
   }

   void pfiDioHelper::_writePFIOutputSelect( tDigDataType     lineMask,
                                             nMDBG::tStatus2& status,
                                             tBoolean         force )
   {
      if (status.isFatal()) return;

      u32 pfiLineNum = 0;
      u32 currentBitMask = 1;
      for(; pfiLineNum < kNumLines; ++pfiLineNum, currentBitMask <<= 1)
      {
         if (lineMask & currentBitMask)
         {
            _triggers.PFI_OutputSelectRegister_i[pfiLineNum].writePFI_i_Output_Select(nTriggers::kPFI_DO, &status, force);
         }
      }
   }

} // nNISTC3
