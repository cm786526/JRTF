/*
 * outTimerHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include <stdio.h>
#include <time.h>

#include "outTimerHelper.h"

namespace nNISTC3
{
   void outTimerHelper::reset(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      // Reset the OutTimer timing module and update all affected registers.
      // Note that AO/DO registers may be touched as well. See their respective helpers!
      _outTimer.Reset_Register.writeReset(1, &status);

      _outTimer.Mode_1_Register.setRegister(0, &status);
      _outTimer.Mode_2_Register.setRegister(0, &status);
      _outTimer.Output_Control_Register.setExportedUpdatePolarity(nOutTimer::kFalling_Edge, &status);
      _outTimer.UI_Load_A_Register.setRegister(0, &status);
      _outTimer.UI_Load_B_Register.setRegister(0, &status);
      _outTimer.UC_Load_A_Register.setRegister(0, &status);
      _outTimer.UC_Load_B_Register.setRegister(0, &status);
      _outTimer.BC_Load_A_Register.setRegister(0, &status);
      _outTimer.BC_Load_B_Register.setRegister(0, &status);

      // Disable Interrupts, strobe all acknowledges. Clear the FIFO.
      _outTimer.Interrupt2_Register.writeRegister(0xFFFFFFFF, &status);
      _outTimer.Reset_Register.writeFIFO_Clear(1, &status);
   }

   void outTimerHelper::clearFIFO(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _outTimer.Reset_Register.writeFIFO_Clear(1, &status);
   }

   void outTimerHelper::programStart1( nOutTimer::tOutTimerSyncMode_t            syncMode,
                                       nOutTimer::tOutTimer_Start1_Export_Mode_t exportMode,
                                       nMDBG::tStatus2&                          status )
   {
      if (status.isFatal()) return;

      _outTimer.Mode_2_Register.setSyncMode(syncMode, &status);
      _outTimer.Mode_2_Register.setStart1_Export_Mode(exportMode, &status);
      _outTimer.Mode_2_Register.flush(&status);
   }

   void outTimerHelper::programUICounter( nOutTimer::tOutTimer_UI_Source_Select_t source,
                                          nOutTimer::tOutTimer_Polarity_t         sourcePolarity,
                                          nOutTimer::tOutTimer_Continuous_t       continuous,
                                          nMDBG::tStatus2&                        status )
   {
      if (status.isFatal()) return;

      if (continuous == nOutTimer::kContinuousOp)
      {
         _outTimer.Mode_1_Register.setUI_Reload_Mode(nOutTimer::kUI_Reload_No_Change, &status);
      }
      else
      {
         _outTimer.Mode_1_Register.setUI_Reload_Mode(nOutTimer::kUI_Reload_Switch_On_BC_TC_First, &status);
      }
      _outTimer.Mode_1_Register.setUI_Source_Select(source, &status);
      _outTimer.Mode_1_Register.setUI_Source_Polarity(sourcePolarity, &status);
      _outTimer.Mode_1_Register.flush(&status);
   }

   void outTimerHelper::programStopCondition( tBoolean                             triggerOnce,
                                              nOutTimer::tOutTimer_Continuous_t    continuous,
                                              nOutTimer::tOutTimer_Stop_On_Error_t stop_On_BC_TC_Error,
                                              nOutTimer::tOutTimer_Stop_On_Error_t stop_On_BC_TC_Trigger_Error,
                                              nOutTimer::tOutTimer_Stop_On_Error_t stop_On_Overrun_Error,
                                              nMDBG::tStatus2&                     status )
   {
      if (status.isFatal()) return;

      _outTimer.Mode_1_Register.setTrigger_Once(triggerOnce, &status);
      _outTimer.Mode_1_Register.setContinuous(continuous, &status);
      _outTimer.Mode_1_Register.flush(&status);

      _outTimer.Mode_2_Register.setStop_On_BC_TC_Error(stop_On_BC_TC_Error, &status);
      _outTimer.Mode_2_Register.setStop_On_BC_TC_Trigger_Error(stop_On_BC_TC_Trigger_Error, &status);
      _outTimer.Mode_2_Register.setStop_On_Overrun_Error(stop_On_Overrun_Error, &status);
      _outTimer.Mode_2_Register.flush(&status);
   }

   void outTimerHelper::programBufferCount( u32              bufferLoopCount,
                                            nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _outTimer.Mode_1_Register.setBC_Initial_Load_Source(nOutTimer::kReg_A, &status);
      _outTimer.Mode_1_Register.setBC_Reload_Mode(nOutTimer::kBC_Reload_No_Change, &status);
      _outTimer.Mode_1_Register.flush(&status);

      _outTimer.BC_Load_A_Register.writeRegister(bufferLoopCount - 1, &status);
      _outTimer.Command_1_Register.writeBC_Load(1, &status);
   }

   void outTimerHelper::programUpdateCount( u32              updatesPerBufferPrimary,
                                            u32              updatesPerBufferSecondary,
                                            nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _outTimer.UC_Load_A_Register.writeRegister(updatesPerBufferPrimary - 1, &status);
      if (updatesPerBufferSecondary != 0)
      {
         _outTimer.UC_Load_B_Register.writeRegister(updatesPerBufferSecondary - 1, &status);
      }
      else
      {
         _outTimer.UC_Load_B_Register.writeRegister(updatesPerBufferPrimary - 1, &status);
      }
      _outTimer.Mode_1_Register.writeUC_Reload_Mode(nOutTimer::kAlternate_First_Period_Every_BC_TC, &status);
   }

   void outTimerHelper::programFIFO( tBoolean                                FIFOEnable,
                                     nOutTimer::tOutTimer_FIFO_Mode_t        FIFOMode,
                                     nOutTimer::tOutTimer_Disabled_Enabled_t useOnlyOnboardMemory,
                                     nMDBG::tStatus2&                        status )
   {
      if (status.isFatal()) return;

      _outTimer.Mode_1_Register.setFIFO_Mode(FIFOMode, &status);
      _outTimer.Mode_1_Register.setFIFO_Retransmit_Enable(useOnlyOnboardMemory, &status);
      _outTimer.Mode_1_Register.flush(&status);

      _outTimer.Mode_2_Register.setFIFO_Enable(FIFOEnable ? nOutTimer::kEnabled : nOutTimer::kDisabled, &status);
      _outTimer.Mode_2_Register.flush(&status);
   }

   void outTimerHelper::loadUI( u32              start1DelayCount,
                                u32              UI_Updates,
                                nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _outTimer.Mode_1_Register.writeUI_Initial_Load_Source(nOutTimer::kReg_A, &status);
      _outTimer.UI_Load_A_Register.writeRegister(start1DelayCount - 1, &status);
      _outTimer.Command_1_Register.writeUI_Load(1, &status);
      _outTimer.UI_Load_B_Register.writeRegister(UI_Updates - 1, &status);
      _outTimer.Mode_1_Register.writeUI_Initial_Load_Source(nOutTimer::kReg_B, &status);
   }

   void outTimerHelper::loadUC(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      _outTimer.Mode_1_Register.setUC_Initial_Load_Source(nOutTimer::kReg_A, &status);
      _outTimer.Mode_1_Register.flush(&status);
      _outTimer.Command_1_Register.writeUC_Load(1, &status);

      _outTimer.Mode_1_Register.writeUC_Initial_Load_Source(nOutTimer::kReg_B, &status);
   }

   void outTimerHelper::armTiming(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      // Arm bits must be set at the same time, since this is a strobe
      // register, build up the value and write them all at once
      u32 commandValue = 0;

      // Determine what to arm
      if (_armUI)
      {
         commandValue |= (1 << nOutTimer::nCommand_1_Register::nUI_Arm::kOffset);
      }
      if (_armBC)
      {
         commandValue |= (1 << nOutTimer::nCommand_1_Register::nBC_Arm::kOffset);
      }
      if (_armUC)
      {
         commandValue |= (1 << nOutTimer::nCommand_1_Register::nUC_Arm::kOffset);
      }
      _outTimer.Command_1_Register.writeRegister(commandValue, &status);

      // Poll the armed state, timeout after 5 seconds
      f64 runTime = 5;
      f64 elapsedTime;
      clock_t start = clock();
      while (!_outTimer.Status_1_Register.readBC_Armed_St(&status) && status.isNotFatal())
      {
         elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
         if (elapsedTime > runTime)
         {
            printf("Error: Timing engine did not arm.\n");
            status.setCode(kStatusRLPTimeout);
            break;
         }
      };
   }

   outTimerHelper::tOutTimerFIFOStatus outTimerHelper::getOutTimerFIFOStatus(nMDBG::tStatus2& status) const
   {
      if (status.isFatal()) return outTimerHelper::kFIFOEmpty;

      if (_outTimer.Status_1_Register.readFIFO_Empty_St(&status))
         return outTimerHelper::kFIFOEmpty;

      if (_outTimer.Status_1_Register.readFIFO_Full_St(&status))
         return outTimerHelper::kFIFOFull;

      if (_outTimer.Status_1_Register.readFIFO_Half_Full_St(&status))
         return outTimerHelper::kFIFOHalfFull;

      return outTimerHelper::kFIFONotEmpty;
   }
} // nNISTC3
