/*
 * inTimerHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include <stdio.h>
#include <time.h>

#include "inTimerHelper.h"

namespace nNISTC3
{
   void inTimerHelper::reset(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _inTimer.Reset_Register.writeReset(1, &status);

      // Setting the above reset bit has the side effect of modifying the
      // following registers. Therefore set the soft copy as well. Note that
      // AI/DI registers may be touched as well. See their respective helpers!

      _inTimer.Mode_1_Register.writeExportedConvertPolarity(_convertPolarity, &status);

      _inTimer.Mode_2_Register.setRegister(0, &status);
      _inTimer.SI_Load_A_Register.setRegister(0, &status);
      _inTimer.SI_Load_B_Register.setRegister(0, &status);
      _inTimer.SC_Load_A_Register.setRegister(0, &status);
      _inTimer.SC_Load_B_Register.setRegister(0, &status);
      _inTimer.SI2_Load_A_Register.setRegister(0, &status);
      _inTimer.SI2_Load_B_Register.setRegister(0, &status);
      _inTimer.DIV_Load_A_Register.setRegister(0, &status);

      // Disable Interrupts, strobe all acknowledges. Clear the FIFO.
      _inTimer.Interrupt2_Register.writeRegister(0xFFFFFFFF, &status);
      clearFIFO(status);
   }

   void inTimerHelper::clearFIFO(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      if (_simultaneousControl)
      {
         if (_simultaneousControl->AcquisitionCtrl.readExtendedChannelsPresent(&status))
         {
            if (!_simultaneousControl->DcmCtrlStat.readExtDcmIsLocked(&status))
            {
               if (!_simultaneousControl->DcmCtrlStat.readExtDcmResetStatus(&status))
               {
                  _simultaneousControl->DcmCtrlStat.writeSetExtDcmReset(kTrue, &status);
               }

               _simultaneousControl->DcmCtrlStat.writeClrExtDcmReset(kTrue, &status);

               // Timeout after 5 seconds
               f64 runTime = 5;
               f64 elapsedTime;
               clock_t start = clock();
               while (!_simultaneousControl->DcmCtrlStat.readExtDcmIsLocked(&status) && status.isNotFatal())
               {
                  elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
                  if (elapsedTime > runTime)
                  {
                     printf("Error: SMIO extended channels did not initialize.\n");
                     break;
                  }
               }
            }
         }

         if (!_simultaneousControl->DcmCtrlStat.readStc3DcmIsLocked(&status))
         {
            if (!_simultaneousControl->DcmCtrlStat.readStc3DcmResetStatus(&status))
            {
               _simultaneousControl->DcmCtrlStat.writeSetStc3DcmReset(kTrue, &status);
            }

            _simultaneousControl->DcmCtrlStat.writeClrStc3DcmReset(kTrue, &status);

            // Timeout after 5 seconds
            f64 runTime = 5;
            f64 elapsedTime;
            clock_t start = clock();
            while (!_simultaneousControl->DcmCtrlStat.readStc3DcmIsLocked(&status) && status.isNotFatal())
            {
               elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
               if (elapsedTime > runTime)
               {
                  printf("Error: SMIO channels did not initialize.\n");
                  break;
               }
            }
         }
      }

      _inTimer.Reset_Register.writeFIFO_Clear(1, &status);
   }

   void inTimerHelper::programTiming(const inTimerParams& timing, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      // Program the External Mux
      _inTimer.Mode_2_Register.setEXTMUX_CLK_Polarity(timing.getExtMuxPolarity(status), &status);
      _inTimer.Mode_1_Register.setExternal_MUX_Present(timing.getExtMuxMode(status), &status);
      if (timing.getExtMuxMode(status) == nInTimer::kDIV_TC_Converts)
      {
         // Program pulse width and div count
         if (timing.getDivNumber(status) > 1)
         {
            // Write so that load is meaningful
            _inTimer.DIV_Load_A_Register.writeDIV_Load_A(timing.getDivNumber(status) - 1, &status);
            _inTimer.Command_Register.writeDIV_Load(1, &status);
         }
      }

      _inTimer.Mode_1_Register.setStart_Stop_Gate_Enable(timing.getStartStopGateEnable(status), &status);

      // Program Sample Counts, etc
      _inTimer.Mode_1_Register.setTrigger_Once(!timing.getRetriggerRecord(status), &status);
      if (timing.getAcqLevelTimingMode(status) == kInTimerPreTrigger)
      {
         _inTimer.Mode_1_Register.setContinuous(0, &status);
         _inTimer.Mode_1_Register.setPre_Trigger(nInTimer::kPretrigger, &status);
         _inTimer.Mode_1_Register.setSC_Initial_Load_Source(nInTimer::kLoad_B, &status);
         _inTimer.Mode_1_Register.setSC_Reload_Mode(nInTimer::kSC_Reload_Switch, &status);

         _inTimer.SC_Load_B_Register.writeSC_Load_B(timing.getStartTriggerHoldoffCount(status) - 1, &status);
      }
      else
      {
         _inTimer.Mode_1_Register.setContinuous(
            timing.getAcqLevelTimingMode(status) == kInTimerContinuous ? 1 : 0,
            &status);
         _inTimer.Mode_1_Register.setPre_Trigger(nInTimer::kPosttrigger, &status);
         _inTimer.Mode_1_Register.setSC_Initial_Load_Source(nInTimer::kLoad_A, &status);
         _inTimer.Mode_1_Register.setSC_Reload_Mode(nInTimer::kSC_Reload_No_Change, &status);
      }
      _inTimer.Mode_1_Register.flush(&status);

      _inTimer.SC_Load_A_Register.writeSC_Load_A(timing.getNumberOfSamples(status) - 1, &status);
      _inTimer.Command_Register.writeSC_Load(1, &status);

      _inTimer.Mode_2_Register.setStart1_Export_Mode(timing.getStart1ExportMode(status), &status);
      _inTimer.Mode_2_Register.setStart2_Export_Mode(timing.getStart2ExportMode(status), &status);
      _inTimer.Mode_2_Register.setStart_Trigger_Length(timing.getStartTriggerLength(status), &status);
      _inTimer.Mode_2_Register.setSyncMode(timing.getSyncMode(status), &status);
      _inTimer.Mode_2_Register.setHaltOnError(1, &status);
      _inTimer.Mode_2_Register.flush(&status);

      if (timing.getUseSICounter(status))
      {
         // Program the SI route and loading behavior
         _inTimer.Mode_1_Register.setSI_Source_Select(timing.getSITimebaseSource(status), &status);
         _inTimer.Mode_1_Register.setSI_Source_Polarity(timing.getSITimebasePolarity(status), &status);
         _inTimer.Mode_1_Register.setSI_Initial_Load_Source(nInTimer::kLoad_A, &status);
         if (timing.getAcqLevelTimingMode(status) == kInTimerContinuous)
         {
            _inTimer.Mode_1_Register.setSI_Reload_Mode(nInTimer::kSI_Reload_No_Change, &status);
         }
         else
         {
            _inTimer.Mode_1_Register.setSI_Reload_Mode(nInTimer::kSI_Reload_Alt_First_Period_Every_SCTC, &status);
         }
         _inTimer.Mode_1_Register.flush(&status);

         // Load the actual values for SI
         _inTimer.SI_Load_A_Register.writeSI_Load_A(timing.getSampleDelay(status) - 1, &status);
         _inTimer.Command_Register.writeSI_Load(1, &status);
         _inTimer.SI_Load_B_Register.writeSI_Load_B(timing.getSamplePeriod(status) - 1, &status);
         _inTimer.Mode_1_Register.writeSI_Initial_Load_Source(nInTimer::kLoad_B, &status);
      }

      if (timing.getUseSI2Counter(status))
      {
         _inTimer.Mode_1_Register.setSI2_Initial_Load_Source(nInTimer::kLoad_A, &status);
         _inTimer.Mode_1_Register.setSI2_Reload_Mode(nInTimer::kSI2_Reload_Alt_First_Period_Every_STOP, &status);
         _inTimer.Mode_1_Register.flush(&status);

         _inTimer.Mode_2_Register.writeSI2_Source_Select(timing.getSI2TimebaseSource(status), &status);

         // Load the convert to sample clock delay
         _inTimer.SI2_Load_A_Register.writeSI2_Load_A(timing.getConvertDelay(status) - 1, &status);
         _inTimer.Command_Register.writeSI2_Load(1, &status);

         // Load the convert period
         _inTimer.SI2_Load_B_Register.writeSI2_Load_B(timing.getConvertPeriod(status) - 1, &status);
         _inTimer.Mode_1_Register.writeSI2_Initial_Load_Source(nInTimer::kLoad_B, &status);
      }
   }

   void inTimerHelper::armTiming(const inTimerParams& timing, nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      // Arm bits must be set at the same time since this is a strobe register
      u32 commandValue = 0;

      // Determine what to arm
      commandValue |= (1 << nInTimer::nCommand_Register::nSC_Arm::kOffset);
      if (timing.getUseSICounter(status))
      {
         commandValue |= (1 << nInTimer::nCommand_Register::nSI_Arm::kOffset);
      }
      if (timing.getUseSI2Counter(status))
      {
         commandValue |= (1 << nInTimer::nCommand_Register::nSI2_Arm::kOffset);
      }
      commandValue |= (1 << nInTimer::nCommand_Register::nDIV_Arm::kOffset);

      _inTimer.Command_Register.writeRegister(commandValue, &status);

      // Poll the armed state, timeout after 5 seconds
      f64 runTime = 5;
      f64 elapsedTime;
      clock_t start = clock();
      while (!_inTimer.Status_1_Register.readSC_Armed_St(&status) && status.isNotFatal())
      {
         elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
         if (elapsedTime > runTime)
         {
            printf("Error: Timing engine did not arm.\n");
            status.setCode(kStatusRLPTimeout);
            break;
         }
      }
   }
} // nNISTC3
