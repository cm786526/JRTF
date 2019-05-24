/*
 * diHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "diHelper.h"

namespace nNISTC3
{
   void diHelper::reset(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      inTimerHelper::tInTimerConfigurationBlock configBlock(_inTimerHelper.getInTimer(status), status);
      if (status.isFatal()) return;

      // Set DataWidth to 32 bits
      _di.DI_Mode_Register.writeDI_DataWidth(nDI::kDI_FourBytes, &status);

      _inTimerHelper.reset(status);
   }

   void diHelper::programExternalGate( nDI::tDI_External_Gate_Select_t source,
                                       nDI::tDI_Polarity_t             sourcePolarity,
                                       nMDBG::tStatus2&                status )
   {
      if (status.isFatal()) return;

      _di.DI_Trigger_Select_Register.setDI_External_Gate_Select(source, &status);
      _di.DI_Trigger_Select_Register.setDI_External_Gate_Polarity(sourcePolarity, &status);
      _di.DI_Trigger_Select_Register.flush(&status);
   }

   void diHelper::programStart1( nDI::tDI_START1_Select_t source,
                                 nDI::tDI_Polarity_t      sourcePolarity,
                                 tBoolean                 start1Edge,
                                 nMDBG::tStatus2&         status )
   {
      if (status.isFatal()) return;

      _di.DI_Trigger_Select_Register.setDI_START1_Select(source, &status);
      _di.DI_Trigger_Select_Register.setDI_START1_Polarity(sourcePolarity, &status);
      _di.DI_Trigger_Select_Register.setDI_START1_Edge(start1Edge, &status);
      _di.DI_Trigger_Select_Register.flush(&status);
   }

   void diHelper::programStart2( nDI::tDI_START2_Select_t source,
                                 nDI::tDI_Polarity_t      sourcePolarity,
                                 tBoolean                 start2Edge,
                                 nMDBG::tStatus2&         status )
   {
      if (status.isFatal()) return;

      _di.DI_Trigger_Select_Register.setDI_START2_Select(source, &status);
      _di.DI_Trigger_Select_Register.setDI_START2_Polarity(sourcePolarity, &status);
      _di.DI_Trigger_Select_Register.setDI_START2_Edge(start2Edge, &status);
      _di.DI_Trigger_Select_Register.flush(&status);
   }

   void diHelper::programConvert( nDI::tDI_StartConvertSelMux_t convertSource,
                                  nDI::tDI_Polarity_t           convertPolarity,
                                  nMDBG::tStatus2&              status )
   {
      if (status.isFatal()) return;

      _di.DI_Trigger_Select_Register.setDI_CONVERT_Source_Select(convertSource, &status);
      _di.DI_Trigger_Select_Register.setDI_CONVERT_Source_Polarity(convertPolarity, &status);
      _di.DI_Trigger_Select_Register.flush(&status);
   }

   void diHelper::programChangeDetection( u32              diRisingEdgeMask,
                                          u32              diFallingEdgeMask,
                                          u16              pfiRisingEdgeMask,
                                          u16              pfiFallingEdgeMask,
                                          nMDBG::tStatus2& status )
   {
      if (status.isFatal()) return;

      _di.DI_ChangeIrqRE_Register.writeRegister(diRisingEdgeMask, &status);
      _di.DI_ChangeIrqFE_Register.writeRegister(diFallingEdgeMask, &status);

      _di.PFI_ChangeIrq_Register.setPFI_ChangeIrqRE(pfiRisingEdgeMask, &status);
      _di.PFI_ChangeIrq_Register.setPFI_ChangeIrqFE(pfiFallingEdgeMask, &status);
      _di.PFI_ChangeIrq_Register.flush(&status);
   }
} // nNISTC3
