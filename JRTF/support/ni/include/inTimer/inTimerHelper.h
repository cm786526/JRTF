/*
 * inTimerHelper.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef  ___inTimer_inTimerHelper_h___
#define  ___inTimer_inTimerHelper_h___

#include "inTimerParams.h"
#include "tInTimer.h"
#include "tSimultaneousControl.h"

namespace nNISTC3
{
   class inTimerHelper
   {
   public:
      inline inTimerHelper( tInTimer&                     inTimer,
                            nInTimer::tInTimer_Polarity_t convertPolarity,
                            tSimultaneousControl*         simultaneousControl,
                            nMDBG::tStatus2&              status );
      inline ~inTimerHelper();

      inline tInTimer& getInTimer(nMDBG::tStatus2& status);

      //------------------------------------------------------------------------
      // tInTimerConfigurationBlock - Automatically starts an InTimer configuration
      // sequence during construction and ends it during destruction.
      //------------------------------------------------------------------------
      class tInTimerConfigurationBlock
      {
      public:
         inline tInTimerConfigurationBlock(tInTimer& inTimer, nMDBG::tStatus2& status);
         inline ~tInTimerConfigurationBlock();

      private:
         tInTimer& _inTimer;
         tBoolean  _configStarted;

         // Usage guidelines
         tInTimerConfigurationBlock(const tInTimerConfigurationBlock&);
         tInTimerConfigurationBlock& operator=(const tInTimerConfigurationBlock&);
      };

      inline void primeConfigFifo(nMDBG::tStatus2& status);
      inline void clearConfigurationMemory(nMDBG::tStatus2& status);
      void clearFIFO(nMDBG::tStatus2& status);

      void programTiming(const inTimerParams& timing, nMDBG::tStatus2& status);
      inline void programFIFO(nInTimer::tInTimer_FIFO_Mode_t FIFOMode, nMDBG::tStatus2& status);
      inline void programFIFOThreshold(nInTimer::tInTimer_FIFO_Mode_t threshold, nMDBG::tStatus2& status);
      inline void programExternalGate(const inTimerParams& timing, nMDBG::tStatus2& status);

      void armTiming(const inTimerParams& timing, nMDBG::tStatus2& status);
      inline void changeRateWhileRunning(u32 newSICount, nMDBG::tStatus2 &status);
      inline void disarmTiming(nMDBG::tStatus2& status);

      inline void strobeStart1(nMDBG::tStatus2& status);
      inline void strobeStart(nMDBG::tStatus2& status);
      inline void strobeConvert(nMDBG::tStatus2& status);

      inline nInTimer::tInTimer_FIFO_Mode_t getTransferAssertThreshold(nMDBG::tStatus2& status) const;

   private:
      // Reset should only be called from the context of an AI or DI reset.
      friend class aiHelper;
      friend class diHelper;
      // NOTE: This should be called from within a config block!
      void reset(nMDBG::tStatus2& status);

      tInTimer&                     _inTimer;
      nInTimer::tInTimer_Polarity_t _convertPolarity;
      tSimultaneousControl*         _simultaneousControl;

      // Usage guidelines
      inTimerHelper(const inTimerHelper&);
      inTimerHelper& operator=(const inTimerHelper&);
   };

   inline inTimerHelper::inTimerHelper( tInTimer&                     inTimer,
                                        nInTimer::tInTimer_Polarity_t convertPolarity,
                                        tSimultaneousControl*         simultaneousControl,
                                        nMDBG::tStatus2&              status ) :
      _inTimer(inTimer),
      _convertPolarity(convertPolarity),
      _simultaneousControl(simultaneousControl)
   {
      nNIOSINT100_mUnused(status);
   }

   inline inTimerHelper::~inTimerHelper()
   {}

   inline tInTimer& inTimerHelper::getInTimer(nMDBG::tStatus2& status)
   {
      nNIOSINT100_mUnused(status);
      return _inTimer;
   }

   inline inTimerHelper::tInTimerConfigurationBlock::tInTimerConfigurationBlock( tInTimer&        inTimer,
                                                                                 nMDBG::tStatus2& status ) :
        _inTimer(inTimer),
        _configStarted(kFalse)
   {
      if (status.isFatal()) return;

      _inTimer.Reset_Register.writeConfiguration_Start(1, &status);
      _configStarted = status.isNotFatal();
   }

   inline inTimerHelper::tInTimerConfigurationBlock::~tInTimerConfigurationBlock()
   {
      if (_configStarted) _inTimer.Reset_Register.writeConfiguration_End(1);
   }

   inline void inTimerHelper::primeConfigFifo(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      if (!_simultaneousControl) _inTimer.Command_Register.writeLOCALMUX_CLK_Pulse(1, &status);
   }

   inline void inTimerHelper::clearConfigurationMemory(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      if (_simultaneousControl)
      {
         _simultaneousControl->AIClearChannelOrder.writeAiClearConfig(1, &status);
      }
      else
      {
         _inTimer.Reset_Register.writeConfiguration_Memory_Clear(1, &status);
      }
   }

   inline void inTimerHelper::programFIFO( nInTimer::tInTimer_FIFO_Mode_t FIFOMode,
                                           nMDBG::tStatus2&               status )
   {
      if (status.isFatal()) return;

      _inTimer.Mode_2_Register.writeFIFO_Mode(FIFOMode, &status);
   }

   inline void inTimerHelper::programFIFOThreshold(nInTimer::tInTimer_FIFO_Mode_t threshold, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _inTimer.Mode_2_Register.writeFIFO_Mode(threshold, &status);
   }

   inline void inTimerHelper::programExternalGate(const inTimerParams& timing, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _inTimer.Mode_2_Register.writeExternal_Gate_Mode(timing.getExternalGateMode(status), &status);
   }

   inline void inTimerHelper::changeRateWhileRunning(u32 newSICount, nMDBG::tStatus2 &status)
   {
      if (status.isFatal()) return;

      // Load the new value into load B. Load_A has the sample delay, which can't be overwritten
      // in case the user is retriggering.
      _inTimer.SI_Load_B_Register.writeSI_Load_B(newSICount - 1, &status);
   }

   inline void inTimerHelper::disarmTiming(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _inTimer.Command_Register.writeDisarm(1, &status);
   }

   inline void inTimerHelper::strobeStart1(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _inTimer.Command_Register.writeSTART1_Pulse(1, &status);
   }

   inline void inTimerHelper::strobeStart(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _inTimer.Command_Register.writeSTART_Pulse(1, &status);
   }

   inline void inTimerHelper::strobeConvert(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _inTimer.Command_Register.writeCONVERT_Pulse(1, &status);
   }

   inline nInTimer::tInTimer_FIFO_Mode_t inTimerHelper::getTransferAssertThreshold(nMDBG::tStatus2& status) const
   {
      // Return the soft copy.
      return _inTimer.Mode_2_Register.getFIFO_Mode(&status);
   }
} // nNISTC3

#endif // ___inTimer_inTimerHelper_h___
