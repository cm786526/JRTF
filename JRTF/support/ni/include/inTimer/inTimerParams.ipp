/*
 * inTimerParams.ipp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___inTimerParams_ipp___
#define ___inTimerParams_ipp___

namespace nNISTC3
{
   inline void inTimerParams::setConvertDelay(u32 convertDelay, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _convertDelay = convertDelay;
   }

   inline u32 inTimerParams::getConvertDelay(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _convertDelay;
   }

   inline void inTimerParams::setConvertPeriod(u32 convertPeriod, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _convertPeriod = convertPeriod;
   }

   inline u32 inTimerParams::getConvertPeriod(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _convertPeriod;
   }

   inline void inTimerParams::setDivNumber(u16 divNumber, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _divNumber = divNumber;
   }

   inline u16 inTimerParams::getDivNumber(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _divNumber;
   }

   inline void inTimerParams::setExternalGateMode(nInTimer::tInTimer_External_Gate_Mode_t externalGateMode, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _externalGateMode = externalGateMode;
   }

   inline nInTimer::tInTimer_External_Gate_Mode_t inTimerParams::getExternalGateMode(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _externalGateMode;
   }

   inline void inTimerParams::setExtMuxClkPulseWidth(nInTimer::tInTimer_EXTMUX_CLK_Pulse_Width_t extMuxClkPulseWidth, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _extMuxClkPulseWidth = extMuxClkPulseWidth;
   }

   inline nInTimer::tInTimer_EXTMUX_CLK_Pulse_Width_t inTimerParams::getExtClkPulseWidth(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _extMuxClkPulseWidth;
   }

   inline void inTimerParams::setExtMuxMode(nInTimer::tInTimer_External_MUX_Present_t extMuxPresent, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _extMuxPresent = extMuxPresent;
   }

   inline nInTimer::tInTimer_External_MUX_Present_t inTimerParams::getExtMuxMode(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _extMuxPresent;
   }

   inline void inTimerParams::setExtMuxPolarity(nInTimer::tInTimer_Polarity_t extMuxPolarity, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _extMuxPolarity = extMuxPolarity;
   }

   inline nInTimer::tInTimer_Polarity_t inTimerParams::getExtMuxPolarity(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _extMuxPolarity;
   }

   inline void inTimerParams::setUseSICounter(tBoolean useSICounter, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _useSICounter = useSICounter;
   }

   inline tBoolean inTimerParams::getUseSICounter(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _useSICounter;
   }

   inline void inTimerParams::setUseSI2Counter(tBoolean useSI2Counter, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _useSI2Counter = useSI2Counter;
   }

   inline tBoolean inTimerParams::getUseSI2Counter(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _useSI2Counter;
   }

   inline void inTimerParams::setNumberOfSamples(u32 numberOfSamples, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _numberOfSamples = numberOfSamples;
   }

   inline u32 inTimerParams::getNumberOfSamples(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _numberOfSamples;
   }

   inline void inTimerParams::setRetriggerRecord(tBoolean retriggerRecord, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _retriggerRecord = retriggerRecord;
   }

   inline tBoolean inTimerParams::getRetriggerRecord(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _retriggerRecord;
   }

   inline void inTimerParams::setSampleDelay(u32 sampleDelay, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _sampleDelay = sampleDelay;
   }

   inline u32 inTimerParams::getSampleDelay(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _sampleDelay;
   }

   inline void inTimerParams::setSamplePeriod(u32 samplePeriod, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _samplePeriod = samplePeriod;
   }

   inline u32 inTimerParams::getSamplePeriod(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _samplePeriod;
   }

   inline void inTimerParams::setSITimebaseSource(nInTimer::tInTimer_SI_Source_Select_t siSource, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _siSource = siSource;
   }

   inline nInTimer::tInTimer_SI_Source_Select_t inTimerParams::getSITimebaseSource(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _siSource;
   }

   inline void inTimerParams::setSITimebasePolarity(nInTimer::tInTimer_SI_Source_Polarity_t siPolarity, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _siPolarity = siPolarity;
   }

   inline nInTimer::tInTimer_SI_Source_Polarity_t inTimerParams::getSITimebasePolarity(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _siPolarity;
   }

   inline void inTimerParams::setSI2TimebaseSource(nInTimer::tInTimer_SI2_Source_Select_t si2Source, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _si2Source = si2Source;
   }

   inline nInTimer::tInTimer_SI2_Source_Select_t inTimerParams::getSI2TimebaseSource(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _si2Source;
   }

   inline void inTimerParams::setStartTriggerHoldoffCount(u32 startTriggerHoldoff, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _startTriggerHoldoffCount = startTriggerHoldoff;
   }

   inline u32 inTimerParams::getStartTriggerHoldoffCount(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _startTriggerHoldoffCount;
   }

   inline void inTimerParams::setSyncMode(nInTimer::tInTimer_SyncMode_t syncMode, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _syncMode = syncMode;
   }

   inline nInTimer::tInTimer_SyncMode_t inTimerParams::getSyncMode(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _syncMode;
   }

   inline void inTimerParams::setStart1ExportMode(nInTimer::tInTimer_Start1_Export_Mode_t exportMode, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _start1ExportMode = exportMode;
   }

   inline nInTimer::tInTimer_Start1_Export_Mode_t inTimerParams::getStart1ExportMode(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _start1ExportMode;
   }

   inline void inTimerParams::setStart2ExportMode(nInTimer::tInTimer_Start2_Export_Mode_t exportMode, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _start2ExportMode = exportMode;
   }

   inline nInTimer::tInTimer_Start2_Export_Mode_t inTimerParams::getStart2ExportMode(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _start2ExportMode;
   }

   inline void inTimerParams::setStartTriggerLength(nInTimer::tInTimer_Start_Trigger_Length_t triggerLength, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _startTriggerLength = triggerLength;
   }

   inline nInTimer::tInTimer_Start_Trigger_Length_t inTimerParams::getStartTriggerLength(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _startTriggerLength;
   }

   inline void inTimerParams::setStartStopGateEnable(nInTimer::tInTimer_Disabled_Enabled_t startStopGate, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _inTimerStartStopGateEnable = startStopGate;
   }

   inline nInTimer::tInTimer_Disabled_Enabled_t inTimerParams::getStartStopGateEnable(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _inTimerStartStopGateEnable;
   }

   inline void inTimerParams::setAcqLevelTimingMode(tInTimerAcqLevelTimingMode mode, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;
      _timingMode = mode;
   }

   inline tInTimerAcqLevelTimingMode inTimerParams::getAcqLevelTimingMode(nMDBG::tStatus2& status) const
   {
      nNIOSINT100_mUnused(status);
      return _timingMode;
   }
} // nNISTC3

#endif // ___inTimerParams_ipp___
