/*
 * aoHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef  ___outTimer_aoHelper_h___
#define  ___outTimer_aoHelper_h___

#include "../devices.h"
#include "outTimerHelper.h"
#include "tAO.h"

#include <vector>

namespace nNISTC3
{
   class aoHelper
   {

   public:
      inline aoHelper(tAO& aoPtr, tOutTimer& outTimer, nMDBG::tStatus2& status);
      inline ~aoHelper(void);

      inline tAO& getAO(nMDBG::tStatus2& status);
      inline outTimerHelper& getOutTimerHelper(nMDBG::tStatus2& status);

      void reset(nMDBG::tStatus2& status);

      void programExternalGate( nAO::tAO_External_Gate_Select_t source,
                                nAO::tAO_Polarity_t             sourcePolarity,
                                tBoolean                        enable,
                                nMDBG::tStatus2&                status );

      void programStart1( nAO::tAO_START1_Select_t source,
                          nAO::tAO_Polarity_t      sourcePolarity,
                          tBoolean                 start1Edge,
                          nMDBG::tStatus2&         status );

      struct tChannelConfiguration
      {
         u32 channel;
         u8 gain;
         nAO::tAO_Update_Mode_t updateMode;
         tOutputRange range;
      };

      void programChannels( const std::vector<tChannelConfiguration>& channels,
                            nMDBG::tStatus2&                            status );

      void programConfigBank( const tChannelConfiguration& channelConfig,
                              nMDBG::tStatus2&             status );

      void programUpdate( nAO::tAO_UPDATE_Source_Select_t source,
                          nAO::tAO_Polarity_t             sourcePolarity,
                          nMDBG::tStatus2&                status );

      void setZeroVolts( const std::vector<i16>& zeroVolts,
                         tBoolean                resetToZero,
                         nMDBG::tStatus2&        status );

   private:
      tAO&                    _ao;
      outTimerHelper          _outTimerHelper;
      std::vector<i16>        _zeroVolts;
      tBoolean                _resetToZero;
      const nMDBG::tStatus2&  _exampleStatus;

      // Usage guidelines
      aoHelper(const aoHelper&);
      aoHelper& operator=(const aoHelper&);
   };

   aoHelper::aoHelper(tAO& aoPtr, tOutTimer& outTimer, nMDBG::tStatus2& status) :
      _ao(aoPtr),
      _outTimerHelper(outTimer, status),
      _exampleStatus(status)
   {
   }

   aoHelper::~aoHelper(void)
   {
      nMDBG::tStatus2 status;

      // Disarm the OutTimer if it is armed
      if (_outTimerHelper.getOutTimer(status).Status_1_Register.readUC_Armed_St(&status))
      {
         _outTimerHelper.disarmTiming(status);
      }

      reset(status);

      if (_resetToZero || _exampleStatus.isFatal())
      {
         for (u32 m=0; m<_zeroVolts.size(); ++m)
         {
            _ao.AO_Direct_Data[m].writeRegister(_zeroVolts[m], &status);
         }
      }
   }

   inline tAO& aoHelper::getAO(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _ao;
   }

   inline outTimerHelper& aoHelper::getOutTimerHelper(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _outTimerHelper;
   }
} // nNISTC3

#endif // ___outTimer_aoHelper_h___
