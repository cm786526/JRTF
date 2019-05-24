/*
 * doHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef  ___outTimer_doHelper_h___
#define  ___outTimer_doHelper_h___

#include "outTimerHelper.h"
#include "tDO.h"
#include "tOutTimer.h"

namespace nNISTC3
{
   class doHelper
   {

   public:
      inline doHelper(tDO& doPtr, tOutTimer& outTimer, nMDBG::tStatus2& status);
      inline ~doHelper(void);

      inline tDO& getDO(nMDBG::tStatus2& status);
      inline outTimerHelper& getOutTimerHelper(nMDBG::tStatus2& status);

      void reset(nMDBG::tStatus2& status);

      void programExternalGate( nDO::tDO_External_Gate_Select_t source,
                                nDO::tDO_Polarity_t             sourcePolarity,
                                tBoolean                        enable,
                                nMDBG::tStatus2&                status );

      void programStart1( nDO::tDO_START1_Select_t source,
                          nDO::tDO_Polarity_t      sourcePolarity,
                          tBoolean                 start1Edge,
                          nMDBG::tStatus2&         status );

      void programUpdate( nDO::tDO_UPDATE_Source_Select_t source,
                          nDO::tDO_Polarity_t             sourcePolarity,
                          nMDBG::tStatus2&                status );

   private:
      tDO&            _do;
      outTimerHelper  _outTimerHelper;

      // Usage guidelines
      doHelper(const doHelper&);
      doHelper& operator=(const doHelper&);
   };

   doHelper::doHelper(tDO& doPtr, tOutTimer& outTimer, nMDBG::tStatus2& status) :
      _do(doPtr),
      _outTimerHelper(outTimer, status)
   {
   }

   doHelper::~doHelper(void)
   {
      nMDBG::tStatus2 status;

      // Disarm the inTimer if it is armed
      if (_outTimerHelper.getOutTimer(status).Status_1_Register.readUC_Armed_St(&status))
      {
         _outTimerHelper.disarmTiming(status);
      }

      reset(status);
   }

   inline tDO& doHelper::getDO(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _do;
   }

   inline outTimerHelper& doHelper::getOutTimerHelper(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _outTimerHelper;
   }
} // nNISTC3

#endif // ___outTimer_doHelper_h___
