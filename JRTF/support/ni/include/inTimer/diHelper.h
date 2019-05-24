/*
 * diHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef  ___inTimer_diHelper_h___
#define  ___inTimer_diHelper_h___

#include "inTimerHelper.h"
#include "tDI.h"
#include "tInTimer.h"

namespace nNISTC3
{
   class diHelper
   {

   public:
      inline diHelper(tDI& diPtr, tInTimer& inTimer, nMDBG::tStatus2& status);
      inline ~diHelper();

      inline tDI& getDI(nMDBG::tStatus2& status);
      inline inTimerHelper& getInTimerHelper(nMDBG::tStatus2& status);

      void reset(nMDBG::tStatus2& status);

      void programExternalGate( nDI::tDI_External_Gate_Select_t source,
                                nDI::tDI_Polarity_t             sourcePolarity,
                                nMDBG::tStatus2&                status );

      void programStart1( nDI::tDI_START1_Select_t source,
                          nDI::tDI_Polarity_t      sourcePolarity,
                          tBoolean                 start1Edge,
                          nMDBG::tStatus2&         status );

      void programStart2( nDI::tDI_START2_Select_t source,
                          nDI::tDI_Polarity_t      sourcePolarity,
                          tBoolean                 start2Edge,
                          nMDBG::tStatus2&         status );

      void programConvert( nDI::tDI_StartConvertSelMux_t convertSource,
                           nDI::tDI_Polarity_t           convertPolarity,
                           nMDBG::tStatus2&              status );

      void programChangeDetection( u32              diRisingEdgeMask,
                                   u32              diFallingEdgeMask,
                                   u16              pfiRisingEdgeMask,
                                   u16              pfiFallingEdgeMask,
                                   nMDBG::tStatus2& status);

   private:
      tDI&          _di;
      inTimerHelper _inTimerHelper;

      // Usage guidelines
      diHelper(const diHelper&);
      diHelper& operator=(const diHelper&);
   };

   inline diHelper::diHelper(tDI& di, tInTimer& inTimer, nMDBG::tStatus2& status) :
      _di(di),
      _inTimerHelper(inTimer, nInTimer::kActive_High, NULL /* simultaneousControl is for AI only */, status)
   {
   }

   inline diHelper::~diHelper(void)
   {
      nMDBG::tStatus2 status;

      // Disarm the inTimer if it is armed
      if (_inTimerHelper.getInTimer(status).Status_1_Register.readSC_Armed_St(&status))
      {
         _inTimerHelper.disarmTiming(status);
      }

      reset(status);
   }

   inline tDI& diHelper::getDI(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _di;
   }

   inline inTimerHelper& diHelper::getInTimerHelper(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _inTimerHelper;
   }
} // nNISTC3

#endif // ___inTimer_diHelper_h___
