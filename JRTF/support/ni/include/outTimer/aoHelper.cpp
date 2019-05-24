/*
 * aoHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "aoHelper.h"

namespace nNISTC3
{
   void aoHelper::reset(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      outTimerHelper::tOutTimerConfigurationBlock configBlock(_outTimerHelper.getOutTimer(status), status);

      _ao.AO_Trigger_Select_Register.setRegister(0, &status);
      for (u32 i = 0; i < tAO::kAO_Config_BankArraySize; ++i)
      {
         _ao.AO_Config_Bank[i].setRegister(0x80, &status);
      }

      _outTimerHelper.reset(status);
   }

   void aoHelper::programExternalGate( nAO::tAO_External_Gate_Select_t source,
                                       nAO::tAO_Polarity_t             sourcePolarity,
                                       tBoolean                        enable,
                                       nMDBG::tStatus2&                status )
   {
      if (status.isFatal()) return;

      _ao.AO_Trigger_Select_Register.setAO_External_Gate_Select(source, &status);
      _ao.AO_Trigger_Select_Register.setAO_External_Gate_Polarity(sourcePolarity, &status);
      _ao.AO_Trigger_Select_Register.setAO_External_Gate_Enable(enable ? 1 : 0, &status);
      _ao.AO_Trigger_Select_Register.flush(&status);
   }

   void aoHelper::programStart1( nAO::tAO_START1_Select_t source,
                                 nAO::tAO_Polarity_t      sourcePolarity,
                                 tBoolean                 start1Edge,
                                 nMDBG::tStatus2&         status )
   {
      if (status.isFatal()) return;

      _ao.AO_Trigger_Select_Register.setAO_START1_Select(source, &status);
      _ao.AO_Trigger_Select_Register.setAO_START1_Polarity(sourcePolarity, &status);
      _ao.AO_Trigger_Select_Register.setAO_START1_Edge(start1Edge, &status);
      _ao.AO_Trigger_Select_Register.flush(&status);
   }

   void aoHelper::programChannels( const std::vector< tChannelConfiguration >& channelConfig,
                                   nMDBG::tStatus2&                            status )
   {
      if (status.isFatal()) return;

      _ao.AO_Config_Control_Register.writeAO_Waveform_Order_Clear(1, &status);

      for (u32 i = 0; i < channelConfig.size(); ++i)
      {
         u32 channelNumber = channelConfig[i].channel;
         _ao.AO_Order_Config_Data_Register.writeAO_Waveform_Bitfield_Order(
            channelNumber & 0xF,
            &status);
      }
   }

   void aoHelper::programConfigBank( const tChannelConfiguration& channelConfig,
                                     nMDBG::tStatus2&             status )
   {
      if (status.isFatal()) return;

      _ao.AO_Config_Bank[channelConfig.channel].setAO_Offset(0, &status);
      _ao.AO_Config_Bank[channelConfig.channel].setAO_Reference(channelConfig.gain, &status);
      _ao.AO_Config_Bank[channelConfig.channel].setAO_Update_Mode(channelConfig.updateMode, &status);
      _ao.AO_Config_Bank[channelConfig.channel].setAO_Bipolar(nAO::kBipolar, &status);
      _ao.AO_Config_Bank[channelConfig.channel].flush(&status);
   }

   void aoHelper::programUpdate( nAO::tAO_UPDATE_Source_Select_t source,
                                 nAO::tAO_Polarity_t             sourcePolarity,
                                 nMDBG::tStatus2&                status )
   {
      if (status.isFatal()) return;

      _ao.AO_Trigger_Select_Register.setAO_UPDATE_Source_Select(source, &status);
      _ao.AO_Trigger_Select_Register.setAO_UPDATE_Source_Polarity(sourcePolarity, &status);
      _ao.AO_Trigger_Select_Register.flush(&status);
   }

   void aoHelper::setZeroVolts( const std::vector<i16>& zeroVolts,
                                tBoolean                resetToZero,
                                nMDBG::tStatus2&        status )
   {
      if (status.isFatal()) return;

      _resetToZero = resetToZero;
      _zeroVolts.assign(zeroVolts.size(), 0);

      for (u32 i=0; i < _zeroVolts.size(); ++i)
      {
         _zeroVolts[i] = zeroVolts[i];
      }
   }
}
