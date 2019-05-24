/*
 * aiHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef  ___inTimer_aiHelper_h___
#define  ___inTimer_aiHelper_h___

#include "../devices.h"
#include "inTimerHelper.h"
#include "tXSeries.h"

namespace nNISTC3
{
   class aiHelper
   {

   public:
      inline aiHelper(tXSeries& device, tBoolean isSimultaneous, nMDBG::tStatus2& status);
      inline ~aiHelper();

      inline tAI& getAI(nMDBG::tStatus2& status);
      inline inTimerHelper& getInTimerHelper(nMDBG::tStatus2& status);

      void reset(nMDBG::tStatus2& status);

      void programFIFOWidth(nAI::tAI_FifoWidth_t aiFIFOWidth, nMDBG::tStatus2& status);

      struct tChannelConfiguration
      {
         u32 isLastChannel;
         nAI::tAI_Disabled_Enabled_t enableDither;
         u16 gain;
         tInputRange range;
         nAI::tAI_Config_Channel_Type_t channelType;
         nAI::tAI_Config_Bank_t bank;
         u16 channel;
      };

      void programChannel( const tChannelConfiguration& channelConfig,
                           nMDBG::tStatus2&             status );

      void programExternalGate( nAI::tAI_External_Gate_Select_t source,
                                nAI::tAI_Polarity_t             sourcePolarity,
                                nMDBG::tStatus2&                status );

      void programStart1( nAI::tAI_START1_Select_t source,
                          nAI::tAI_Polarity_t      sourcePolarity,
                          tBoolean                 start1Edge,
                          nMDBG::tStatus2&         status );

      void programStart2( nAI::tAI_START2_Select_t source,
                          nAI::tAI_Polarity_t      sourcePolarity,
                          tBoolean                 start2Edge,
                          nMDBG::tStatus2&         status );

      void programStart( nAI::tAI_StartConvertSelMux_t startSource,
                         nAI::tAI_Polarity_t           startPolarity,
                         tBoolean                      startEdge,
                         nMDBG::tStatus2&              status );

      void programConvert( nAI::tAI_StartConvertSelMux_t convertSource,
                           nAI::tAI_Polarity_t           convertPolarity,
                           nMDBG::tStatus2&              status );

   private:
      tAI&                  _ai;
      inTimerHelper         _inTimerHelper;
      tSimultaneousControl* _simultaneousControl;

      // Usage guidelines
      aiHelper(const aiHelper&);
      aiHelper& operator=(const aiHelper&);
   };

   inline aiHelper::aiHelper(tXSeries& device, tBoolean isSimultaneous, nMDBG::tStatus2& status) :
      _ai(device.AI),
      _inTimerHelper(device.AI.AI_Timer, nInTimer::kActive_Low, isSimultaneous ? &device.SimultaneousControl : NULL, status),
      _simultaneousControl(isSimultaneous ? &device.SimultaneousControl : NULL)
   {
   }

   inline aiHelper::~aiHelper(void)
   {
      nMDBG::tStatus2 status;

      // Disarm the inTimer if it is armed
      if (_inTimerHelper.getInTimer(status).Status_1_Register.readSC_Armed_St(&status))
      {
         _inTimerHelper.disarmTiming(status);
      }

      reset(status);
   }

   inline tAI& aiHelper::getAI(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _ai;
   }

   inline inTimerHelper& aiHelper::getInTimerHelper(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _inTimerHelper;
   }
} // nNISTC3

#endif // ___inTimer_aiHelper_h___
