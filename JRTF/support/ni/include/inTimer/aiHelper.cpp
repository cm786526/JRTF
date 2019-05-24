/*
 * aiHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "aiHelper.h"

#include <time.h>

namespace nNISTC3
{
   void aiHelper::reset(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      inTimerHelper::tInTimerConfigurationBlock configBlock(_inTimerHelper.getInTimer(status), status);
      if (status.isFatal()) return;

      _ai.AI_Config_FIFO_Data_Register.setRegister(0, &status);

      _ai.AI_Data_Mode_Register.setRegister(0, &status);
      _ai.AI_Trigger_Select_Register.setRegister(0, &status);
      _ai.AI_Trigger_Select_Register2.setRegister(0, &status);

      _inTimerHelper.reset(status);

      if (_simultaneousControl)
      {
         _simultaneousControl->InterruptControl.writeGlobalInterruptDisable(kTrue, &status);
         _simultaneousControl->InterruptControl.writeAiFifoOverflowInterruptDisable(kTrue, &status);
         _simultaneousControl->InterruptControl.writeAiFifoOverflowInterruptAck(kTrue, &status);
         _simultaneousControl->AiFifoCtrlStat.writeResetAiFifo(kTrue, &status);
         _simultaneousControl->AiFifoCtrlStat.writeResetAiFifo(kFalse, &status);
      }
   }

   void aiHelper::programFIFOWidth( nAI::tAI_FifoWidth_t aiFIFOWidth,
                                    nMDBG::tStatus2&     status )
   {
      if (status.isFatal()) return;

      if (_simultaneousControl)
      {
         switch (aiFIFOWidth)
         {
         case nAI::kTwoByteFifo:
            _simultaneousControl->AiFifoCtrlStat.writeSetFifoIn16BitMode(kTrue, &status);
            break;
         case nAI::kFourByteFifo:
            _simultaneousControl->AiFifoCtrlStat.writeClrFifoIn16BitMode(kTrue, &status);
            break;
         }
      }
      _ai.AI_Data_Mode_Register.writeAI_FifoWidth(aiFIFOWidth, &status);

      // Only recognizes the change after a FIFO_Clear.
      _inTimerHelper.clearFIFO(status);
   }

   void aiHelper::programChannel( const tChannelConfiguration& channelConfig,
                                  nMDBG::tStatus2&             status )
   {
      if (status.isFatal()) return;

      if (_simultaneousControl)
      {
         _simultaneousControl->AISetChannelOrder.writeAiChannel(static_cast<u8>(channelConfig.channel), &status);
         _simultaneousControl->AIChanConfigCtrlStat.writeAiGain(static_cast<u8>(channelConfig.gain), &status);

         // Wait 20 milliseconds
         f64 runTime = .02;
         f64 elapsedTime;
         clock_t start = clock();
         do
         {
            elapsedTime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
         }
         while (elapsedTime < runTime);
      }
      else
      {
         _ai.AI_Config_FIFO_Data_Register.setAI_Config_Last_Channel(static_cast<u16>(channelConfig.isLastChannel), &status);
         _ai.AI_Config_FIFO_Data_Register.setAI_Config_Dither(channelConfig.enableDither, &status);
         _ai.AI_Config_FIFO_Data_Register.setAI_Config_Gain(channelConfig.gain, &status);
         _ai.AI_Config_FIFO_Data_Register.setAI_Config_Channel_Type(channelConfig.channelType, &status);
         _ai.AI_Config_FIFO_Data_Register.setAI_Config_Bank(channelConfig.bank, &status);
         _ai.AI_Config_FIFO_Data_Register.setAI_Config_Channel(channelConfig.channel, &status);
         _ai.AI_Config_FIFO_Data_Register.flush(&status);
      }
   }

   void aiHelper::programExternalGate( nAI::tAI_External_Gate_Select_t source,
                                       nAI::tAI_Polarity_t             sourcePolarity,
                                       nMDBG::tStatus2&                status )
   {
      if (status.isFatal()) return;

      _ai.AI_Trigger_Select_Register.setAI_External_Gate_Select(source, &status);
      _ai.AI_Trigger_Select_Register.setAI_External_Gate_Polarity(sourcePolarity, &status);
      _ai.AI_Trigger_Select_Register.flush(&status);
   }

   void aiHelper::programStart1( nAI::tAI_START1_Select_t source,
                                 nAI::tAI_Polarity_t      sourcePolarity,
                                 tBoolean                 start1Edge,
                                 nMDBG::tStatus2&         status )
   {
      if (status.isFatal()) return;

      _ai.AI_Trigger_Select_Register.setAI_START1_Select(source, &status);
      _ai.AI_Trigger_Select_Register.setAI_START1_Polarity(sourcePolarity, &status);
      _ai.AI_Trigger_Select_Register.setAI_START1_Edge(start1Edge, &status);
      _ai.AI_Trigger_Select_Register.flush(&status);
   }

   void aiHelper::programStart2( nAI::tAI_START2_Select_t source,
                                 nAI::tAI_Polarity_t      sourcePolarity,
                                 tBoolean                 start2Edge,
                                 nMDBG::tStatus2&         status )
   {
      if (status.isFatal()) return;

      _ai.AI_Trigger_Select_Register.setAI_START2_Select(source, &status);
      _ai.AI_Trigger_Select_Register.setAI_START2_Polarity(sourcePolarity, &status);
      _ai.AI_Trigger_Select_Register.setAI_START2_Edge(start2Edge, &status);
      _ai.AI_Trigger_Select_Register.flush(&status);
   }

   void aiHelper::programStart( nAI::tAI_StartConvertSelMux_t startSource,
                                nAI::tAI_Polarity_t           startPolarity,
                                tBoolean                      startEdge,
                                nMDBG::tStatus2&              status )
   {
      if (status.isFatal()) return;

      _ai.AI_Trigger_Select_Register2.setAI_START_Select(startSource, &status);
      _ai.AI_Trigger_Select_Register2.setAI_START_Edge(startEdge, &status);
      _ai.AI_Trigger_Select_Register2.setAI_START_Polarity(startPolarity, &status);
      _ai.AI_Trigger_Select_Register2.flush(&status);
   }

   void aiHelper::programConvert( nAI::tAI_StartConvertSelMux_t convertSource,
                                  nAI::tAI_Polarity_t           convertPolarity,
                                  nMDBG::tStatus2&              status )
   {
      if (status.isFatal()) return;

      _ai.AI_Trigger_Select_Register.setAI_CONVERT_Source_Select(convertSource, &status);
      _ai.AI_Trigger_Select_Register.setAI_Convert_Source_Polarity(convertPolarity, &status);
      _ai.AI_Trigger_Select_Register.flush(&status);
   }
} // nNISTC3
