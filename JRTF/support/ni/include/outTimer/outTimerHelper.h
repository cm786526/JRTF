/*
 * outTimerHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef  ___outTimer_outTimerHelper_h___
#define  ___outTimer_outTimerHelper_h___

#include "tOutTimer.h"

namespace nNISTC3
{
   class outTimerHelper
   {

   public:
      inline outTimerHelper(tOutTimer& outTimer, nMDBG::tStatus2& status);
      inline ~outTimerHelper(void);

      inline tOutTimer& getOutTimer(nMDBG::tStatus2& status);

      //------------------------------------------------------------------------
      // tOutTimerConfigurationBlock - Automatically starts an OutTimer configuration
      // sequence during construction and ends it during destruction.
      //------------------------------------------------------------------------
      class tOutTimerConfigurationBlock
      {
      public:
         inline tOutTimerConfigurationBlock(tOutTimer& outTimer, nMDBG::tStatus2& status);
         inline ~tOutTimerConfigurationBlock();

      private:
         tOutTimer&         _outTimer;
         tBoolean           _configStarted;

         // Usage guidelines
         tOutTimerConfigurationBlock(const tOutTimerConfigurationBlock&);
         tOutTimerConfigurationBlock& operator=(const tOutTimerConfigurationBlock&);
      };

      // NOTE: This should be called from within a config block!
      void clearFIFO(nMDBG::tStatus2& status);

      void programStart1( nOutTimer::tOutTimerSyncMode_t            syncMode,
                          nOutTimer::tOutTimer_Start1_Export_Mode_t exportMode,
                          nMDBG::tStatus2&                          status );

      void programUICounter( nOutTimer::tOutTimer_UI_Source_Select_t source,
                             nOutTimer::tOutTimer_Polarity_t         sourcePolarity,
                             nOutTimer::tOutTimer_Continuous_t       continuous,
                             nMDBG::tStatus2&                        status );

      void programStopCondition( tBoolean                             triggerOnce,
                                 nOutTimer::tOutTimer_Continuous_t    continuous,
                                 nOutTimer::tOutTimer_Stop_On_Error_t stop_On_BC_TC_Error,
                                 nOutTimer::tOutTimer_Stop_On_Error_t stop_On_BC_TC_Trigger_Error,
                                 nOutTimer::tOutTimer_Stop_On_Error_t stop_On_Overrun_Error,
                                 nMDBG::tStatus2&                     status );

      void programBufferCount( u32              bufferLoopCount,
                               nMDBG::tStatus2& status );
      
      void programUpdateCount( u32              updatesPerBufferPrimary,
                               u32              updatesPerBufferSecondary,
                               nMDBG::tStatus2& status );
      
      void programFIFO( tBoolean                                FIFOEnable,
                        nOutTimer::tOutTimer_FIFO_Mode_t        FIFOMode,
                        nOutTimer::tOutTimer_Disabled_Enabled_t useOnlyOnboardMemory,
                        nMDBG::tStatus2&                        status );
      
      inline void programBCGate( nOutTimer::tOutTimer_Disabled_Enabled_t enable,
                                 nMDBG::tStatus2&                        status );
      
      inline void programSoftwareGate( nOutTimer::tOutTimer_Software_Gate_t gate,
                                       nMDBG::tStatus2&                     status );
      
      inline void programNumberOfChannels(u16 numberOfChannels, nMDBG::tStatus2& status);

      void loadUI(u32 start1DelayCount, u32 UI_Updates, nMDBG::tStatus2& status);
      void loadUC(nMDBG::tStatus2& status);
      inline void loadBC(nMDBG::tStatus2& status);

      inline void setArmUI(tBoolean arm, nMDBG::tStatus2& status);
      inline void setArmBC(tBoolean arm, nMDBG::tStatus2& status);
      inline void setArmUC(tBoolean arm, nMDBG::tStatus2& status);

      void armTiming(nMDBG::tStatus2& status);
      inline void changeRateWhileRunning(u32 newUICount, nMDBG::tStatus2 &status);
      inline void disarmTiming(nMDBG::tStatus2& status);

      inline void notAnUpdate(nMDBG::tStatus2& status);
      inline void acknowledgeUpdate(tBoolean acknowledgeUpdate, nMDBG::tStatus2& status);
      inline tBoolean readUpdate(nMDBG::tStatus2& status) const;

      enum tOutTimerFIFOStatus
      {
         kFIFONotEmpty  = 0,
         kFIFOEmpty     = 1,
         kFIFOHalfFull  = 2,
         kFIFOFull      = 3,
      };
      tOutTimerFIFOStatus getOutTimerFIFOStatus(nMDBG::tStatus2& status) const;

   private:
      // Reset should only be called from the context of an AO or DO reset.
      friend class aoHelper;
      friend class doHelper;
      // NOTE: This should be called from within a config block!
      void reset(nMDBG::tStatus2& status);

      tOutTimer&  _outTimer;
      tBoolean    _armBC;
      tBoolean    _armUC;
      tBoolean    _armUI;

      // Usage guidelines
      outTimerHelper(const outTimerHelper&);
      outTimerHelper& operator=(const outTimerHelper&);
   };

   inline outTimerHelper::outTimerHelper(tOutTimer& outTimer, nMDBG::tStatus2& status) :
      _outTimer(outTimer),
      _armBC(kFalse),
      _armUC(kFalse),
      _armUI(kFalse)
   {
      nNIOSINT100_mUnused(status);
   }

   inline outTimerHelper::~outTimerHelper(void)
   {
   }

   inline tOutTimer& outTimerHelper::getOutTimer(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _outTimer;
   }

   inline outTimerHelper::tOutTimerConfigurationBlock::tOutTimerConfigurationBlock( tOutTimer&       outTimer,
                                                                                    nMDBG::tStatus2& status ) :
      _outTimer(outTimer),
      _configStarted(kFalse)
   {
      if (status.isFatal()) return;

      _outTimer.Reset_Register.writeConfiguration_Start(1, &status);
      _configStarted = status.isNotFatal();
   }

   inline outTimerHelper::tOutTimerConfigurationBlock::~tOutTimerConfigurationBlock(void)
   {
      if (_configStarted) _outTimer.Reset_Register.writeConfiguration_End(1);
   }

   inline void outTimerHelper::programBCGate( nOutTimer::tOutTimer_Disabled_Enabled_t enable,
                                              nMDBG::tStatus2&                        status )
   {
      if (status.isFatal()) return;

      _outTimer.Mode_2_Register.writeBC_Gate_Enable(enable, &status);
   }

   inline void outTimerHelper::programSoftwareGate( nOutTimer::tOutTimer_Software_Gate_t gate,
                                                    nMDBG::tStatus2&                     status )
   {
      if (status.isFatal()) return;

      _outTimer.Mode_2_Register.writeSoftware_Gate(gate, &status);
   }

   inline void outTimerHelper::programNumberOfChannels( u16              numberOfChannels,
                                                        nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _outTimer.Output_Control_Register.writeNumber_Of_Channels(numberOfChannels - 1, &status);
   }

   inline void outTimerHelper::loadBC(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _outTimer.Command_1_Register.writeBC_Load(1, &status);
   }

   inline void outTimerHelper::setArmUI(tBoolean arm, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _armUI = arm;
   }

   inline void outTimerHelper::setArmBC(tBoolean arm, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _armBC = arm;
   }

   inline void outTimerHelper::setArmUC(tBoolean arm, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _armUC = arm;
   }

   inline void outTimerHelper::changeRateWhileRunning(u32 newUICount, nMDBG::tStatus2 &status)
   {
      if (status.isFatal()) return;

      // Load the new value into load_B. Load_A has the sample delay, which can't be overwritten
      // in case the user is retriggering.
      _outTimer.UI_Load_B_Register.writeUI_Load_B(newUICount - 1, &status);
   }

   inline void outTimerHelper::disarmTiming(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _outTimer.Command_1_Register.writeDisarm(1, &status);

      _armUC = kFalse;
      _armBC = kFalse;
      _armUI = kFalse;
   }

   inline void outTimerHelper::notAnUpdate(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _outTimer.Mode_2_Register.writeNot_An_UPDATE(1, &status);
      _outTimer.Mode_2_Register.writeNot_An_UPDATE(0, &status);
   }

   inline void outTimerHelper::acknowledgeUpdate( tBoolean         acknowledgeUpdate,
                                                  nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _outTimer.Interrupt1_Register.writeUPDATE_Interrupt_Ack(acknowledgeUpdate, &status);
   }

   inline tBoolean outTimerHelper::readUpdate(nMDBG::tStatus2& status) const
   {
      if(status.isFatal()) return kFalse;

      return _outTimer.Status_1_Register.readUPDATE_St(&status);
   }
} // nNISTC3

#endif // ___outTimer_outTimerHelper_h___
