/*
 * streamHelper.h
 *
 * Programs the Stream Circuit for DMA transfers.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___streamHelper_h___
#define ___streamHelper_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// Chip objects
#include "tCHInCh.h"
#include "tStreamCircuitRegMap.h"

// DMA Channel enumeration
#include "CHInCh/dmaProperties.h"

namespace nNISTC3
{
   class streamHelper
   {
   public:
      // Constructor
      //   streamCircuit: the device subsystem's Stream Circuit chip object
      //   CHInCH:        the device's CHInCh chip object
      //   status
      streamHelper( tStreamCircuitRegMap& streamCircuit,
                    tCHInCh&              CHInCh,
                    nMDBG::tStatus2&      status );

      // Configure the Stream Circuit for a transfer
      //   useCISTCR:  should the Stream Circuit use the transfer count register
      //               to throttle DMA transfers?
      //   dmaChannel: the DMA channel associated with the Stream Circuit
      //   status
      void configureForInput( tBoolean                   useCISTCR,
                              nNISTC3::tDMAChannelNumber dmaChannel,
                              nMDBG::tStatus2&           status );
      void configureForOutput( tBoolean                   useCISTCR,
                               nNISTC3::tDMAChannelNumber dmaChannel,
                               nMDBG::tStatus2&           status );

      // Enable the Stream Circuit
      void enable(nMDBG::tStatus2& status);

      // Modify the transfer allowance for the Stream Circuit
      //   sizeDelta:  the number of bytes to allow (if positive) or revoke
      //               from (if negative) the Stream Circuit. This applies
      //               only when the CISTCR is enabled.
      //   status
      void modifyTransferSize(i32 sizeDelta, nMDBG::tStatus2& status);

      // Query the Stream Circuit FIFO size
      u32 getFifoSize();

      // Query if the Stream Circuit FIFO is empty
      tBoolean fifoIsEmpty(nMDBG::tStatus2& status);

      // Disable the Stream Circuit
      void disable(nMDBG::tStatus2& status);

      // Reset the Stream Circuit
      void reset(nMDBG::tStatus2& status);

      ~streamHelper();

   private:
      // Usage guidelines
      streamHelper(const streamHelper&);
      streamHelper& operator=(const streamHelper&);

   private:
      void _configure( tBoolean                   isInput,
                       tBoolean                   useCISTCR,
                       nNISTC3::tDMAChannelNumber dmaChannel,
                       nMDBG::tStatus2&           status );

      tStreamCircuitRegMap& _streamCircuit;
      tCHInCh&              _CHInCh;
      u32                   _streamFifoSize;
      u32                   _transactionLimit;
      u16                   _payloadSize;
      tBoolean              _isEnabled;
      tBoolean              _isConfigured;
      tBoolean              _usingCISTCR;
   };
} // nNISTC3

#endif // ___streamHelper_h___
