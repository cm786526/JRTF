/*
 * inTimerParams.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "inTimerParams.h"

namespace nNISTC3
{
   inTimerParams::inTimerParams() :
      _convertDelay(0),
      _convertPeriod(0),
      _divNumber(1),
      _externalGateMode(nInTimer::kFree_Run),
      _extMuxClkPulseWidth(nInTimer::kExtMuxPulseLong),
      _extMuxPresent(nInTimer::kEvery_Convert),
      _extMuxPolarity(nInTimer::kActive_Low),
      _useSICounter(kFalse),
      _useSI2Counter(kFalse),
      _numberOfSamples(0),
      _retriggerRecord(kFalse),
      _sampleDelay(0),
      _samplePeriod(0),
      _siSource(nInTimer::kSI_Src_TB3),
      _siPolarity(nInTimer::kRising_Edge),
      _si2Source(nInTimer::kSI2_Src_Is_SI_Src),
      _startTriggerHoldoffCount(0),
      _syncMode(nInTimer::kSyncDefault),
      _start1ExportMode(nInTimer::kExportSynchronizedStart1),
      _start2ExportMode(nInTimer::kExportMaskedStart2),
      _startTriggerLength(nInTimer::kExportSynchronizedStart),
      _inTimerStartStopGateEnable(nInTimer::kDisabled),
      _timingMode(kInTimerContinuous)
   {}

   inTimerParams::~inTimerParams(void)
   {}
}
