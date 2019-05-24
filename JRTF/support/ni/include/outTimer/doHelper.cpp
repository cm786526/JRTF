/*
 * doHelper.cpp
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#include "doHelper.h"

namespace nNISTC3
{
   void doHelper::reset(nMDBG::tStatus2& status)
   {
      if (status.isFatal()) return;

      outTimerHelper::tOutTimerConfigurationBlock configBlock(_outTimerHelper.getOutTimer(status), status);

      _outTimerHelper.reset(status);
   }

   void doHelper::programExternalGate( nDO::tDO_External_Gate_Select_t source,
                                       nDO::tDO_Polarity_t             sourcePolarity,
                                       tBoolean                        enable,
                                       nMDBG::tStatus2&                status )
   {
      if (status.isFatal()) return;

      _do.DO_Trigger_Select_Register.setDO_External_Gate_Select(source, &status);
      _do.DO_Trigger_Select_Register.setDO_External_Gate_Polarity(sourcePolarity, &status);
      _do.DO_Trigger_Select_Register.setDO_External_Gate_Enable(enable ? 1 : 0, &status);
      _do.DO_Trigger_Select_Register.flush(&status);
   }

   void doHelper::programStart1( nDO::tDO_START1_Select_t source,
                                 nDO::tDO_Polarity_t      sourcePolarity,
                                 tBoolean                 start1Edge,
                                 nMDBG::tStatus2&         status )
   {
      if (status.isFatal()) return;

      _do.DO_Trigger_Select_Register.setDO_START1_Select(source, &status);
      _do.DO_Trigger_Select_Register.setDO_START1_Polarity(sourcePolarity, &status);
      _do.DO_Trigger_Select_Register.setDO_START1_Edge(start1Edge, &status);
      _do.DO_Trigger_Select_Register.flush(&status);
   }

   void doHelper::programUpdate( nDO::tDO_UPDATE_Source_Select_t source,
                                 nDO::tDO_Polarity_t             sourcePolarity,
                                 nMDBG::tStatus2&                status )
   {
      if (status.isFatal()) return;

      _do.DO_Trigger_Select_Register.setDO_UPDATE_Source_Select(source, &status);
      _do.DO_Trigger_Select_Register.setDO_UPDATE_Source_Polarity(sourcePolarity, &status);
      _do.DO_Trigger_Select_Register.flush(&status);
   }
} // nNISTC3
