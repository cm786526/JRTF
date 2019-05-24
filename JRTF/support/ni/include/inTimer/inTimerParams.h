/*
 * inTimerParams.h
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___inTimer_inTimerParams_h___
#define ___inTimer_inTimerParams_h___

#include "tInTimer.h"

namespace nNISTC3
{
   typedef enum
   {
      kInTimerPostTrigger,
      kInTimerPreTrigger,
      kInTimerContinuous
   } tInTimerAcqLevelTimingMode;

   typedef enum
   {
      kInTimerInvalidLevel,
      kInTimerConvertLevel,
      kInTimerSampleLevel,
      kInTimerRecordLevel
   } tInTimerTimingLevel;

   class inTimerParams
   {
   public:
      inTimerParams();
      ~inTimerParams();

      inline void setConvertDelay(u32 convertDelay, nMDBG::tStatus2& status);
      inline u32 getConvertDelay(nMDBG::tStatus2& status) const;

      inline void setConvertPeriod(u32 convertPeriod, nMDBG::tStatus2& status);
      inline u32 getConvertPeriod(nMDBG::tStatus2& status) const;

      inline void setDivNumber(u16 divNumber, nMDBG::tStatus2& status);
      inline u16 getDivNumber(nMDBG::tStatus2& status) const;

      inline void setExternalGateMode(nInTimer::tInTimer_External_Gate_Mode_t externalGateMode, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_External_Gate_Mode_t getExternalGateMode(nMDBG::tStatus2& status) const;

      inline void setExtMuxClkPulseWidth(nInTimer::tInTimer_EXTMUX_CLK_Pulse_Width_t extMuxClkPulseWidth, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_EXTMUX_CLK_Pulse_Width_t getExtClkPulseWidth(nMDBG::tStatus2& status) const;

      inline void setExtMuxMode(nInTimer::tInTimer_External_MUX_Present_t extMuxPresent, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_External_MUX_Present_t getExtMuxMode(nMDBG::tStatus2& status) const;

      inline void setExtMuxPolarity(nInTimer::tInTimer_Polarity_t extMuxOutputSelect, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_Polarity_t getExtMuxPolarity(nMDBG::tStatus2& status) const;

      inline void setUseSICounter(tBoolean useSICounter, nMDBG::tStatus2& status);
      inline tBoolean getUseSICounter(nMDBG::tStatus2& status) const;

      inline void setUseSI2Counter(tBoolean useSI2Counter, nMDBG::tStatus2& status);
      inline tBoolean getUseSI2Counter(nMDBG::tStatus2& status) const;

      inline void setNumberOfSamples(u32 numberOfSamples, nMDBG::tStatus2& status);
      inline u32 getNumberOfSamples(nMDBG::tStatus2& status) const;

      inline void setRetriggerRecord(tBoolean retriggerRecord, nMDBG::tStatus2& status);
      inline tBoolean getRetriggerRecord(nMDBG::tStatus2& status) const;

      inline void setSampleDelay(u32 sampleDelay, nMDBG::tStatus2& status);
      inline u32 getSampleDelay(nMDBG::tStatus2& status) const;

      inline void setSamplePeriod(u32 samplePeriod, nMDBG::tStatus2& status);
      inline u32 getSamplePeriod(nMDBG::tStatus2& status) const;

      inline void setSITimebaseSource(nInTimer::tInTimer_SI_Source_Select_t siSource, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_SI_Source_Select_t getSITimebaseSource(nMDBG::tStatus2& status) const;

      inline void setSITimebasePolarity(nInTimer::tInTimer_SI_Source_Polarity_t siPolarity, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_SI_Source_Polarity_t getSITimebasePolarity(nMDBG::tStatus2& status) const;

      inline void setSI2TimebaseSource(nInTimer::tInTimer_SI2_Source_Select_t si2Source, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_SI2_Source_Select_t getSI2TimebaseSource(nMDBG::tStatus2& status) const;

      inline void setStartTriggerHoldoffCount(u32 startTriggerHoldoff, nMDBG::tStatus2& status);
      inline u32 getStartTriggerHoldoffCount(nMDBG::tStatus2& status) const;

      inline void setSyncMode(nInTimer::tInTimer_SyncMode_t syncMode, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_SyncMode_t getSyncMode(nMDBG::tStatus2& status) const;

      inline void setStart1ExportMode(nInTimer::tInTimer_Start1_Export_Mode_t exportMode, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_Start1_Export_Mode_t getStart1ExportMode(nMDBG::tStatus2& status) const;

      inline void setStart2ExportMode(nInTimer::tInTimer_Start2_Export_Mode_t exportMode, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_Start2_Export_Mode_t getStart2ExportMode(nMDBG::tStatus2& status) const;

      inline void setStartTriggerLength(nInTimer::tInTimer_Start_Trigger_Length_t triggerLength, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_Start_Trigger_Length_t getStartTriggerLength(nMDBG::tStatus2& status) const;

      inline void setStartStopGateEnable(nInTimer::tInTimer_Disabled_Enabled_t startStopGate, nMDBG::tStatus2& status);
      inline nInTimer::tInTimer_Disabled_Enabled_t getStartStopGateEnable(nMDBG::tStatus2& status) const;

      inline void setAcqLevelTimingMode(tInTimerAcqLevelTimingMode mode, nMDBG::tStatus2& status);
      inline tInTimerAcqLevelTimingMode getAcqLevelTimingMode(nMDBG::tStatus2& status) const;

   private:
      u32                                         _convertDelay;
      u32                                         _convertPeriod;
      u16                                         _divNumber;
      nInTimer::tInTimer_External_Gate_Mode_t     _externalGateMode;
      nInTimer::tInTimer_EXTMUX_CLK_Pulse_Width_t _extMuxClkPulseWidth;
      nInTimer::tInTimer_External_MUX_Present_t   _extMuxPresent;
      nInTimer::tInTimer_Polarity_t               _extMuxPolarity;
      tBoolean                                    _useSICounter;
      tBoolean                                    _useSI2Counter;
      u32                                         _numberOfSamples;
      tBoolean                                    _retriggerRecord;
      u32                                         _sampleDelay;
      u32                                         _samplePeriod;
      nInTimer::tInTimer_SI_Source_Select_t       _siSource;
      nInTimer::tInTimer_SI_Source_Polarity_t     _siPolarity;
      nInTimer::tInTimer_SI2_Source_Select_t      _si2Source;
      u32                                         _startTriggerHoldoffCount;
      nInTimer::tInTimer_SyncMode_t               _syncMode;
      nInTimer::tInTimer_Start1_Export_Mode_t     _start1ExportMode;
      nInTimer::tInTimer_Start2_Export_Mode_t     _start2ExportMode;
      nInTimer::tInTimer_Start_Trigger_Length_t   _startTriggerLength;
      nInTimer::tInTimer_Disabled_Enabled_t       _inTimerStartStopGateEnable;
      tInTimerAcqLevelTimingMode                  _timingMode;
   };
} // nNISTC3

#include "inTimerParams.ipp"

#endif // ___inTimer_inTimerParams_h___
