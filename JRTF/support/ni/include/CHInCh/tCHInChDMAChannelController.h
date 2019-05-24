/*
 * tCHInChDMAChannelController.h
 *
 * Provide a chip-level interface for DMA programming on the CHInCh.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tCHInChDMAChannelController_h___
#define ___tCHInChDMAChannelController_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// OS iBus for tBusSpaceReference member
#include "osiBus.h"

// tDMATopology
#include "dmaProperties.h"

// tDMA_Mode_t
#include "tDMAControllerValues.h"

// Forward declarations
class tXSeries;
class tDMAController;

namespace nNISTC3
{
   class tCHInChDMAChannelController
   {
   public:
      // Constructor: initialize CHInCh for DMA operations
      //   device:        tXSeries object representing the device
      //   channelNumber: DMA channel to use on CHInCh
      //   status
      tCHInChDMAChannelController( tXSeries&         device,
                                   tDMAChannelNumber channelNumber,
                                   nMDBG::tStatus2&  status );

      ~tCHInChDMAChannelController();

      u64 getTransferCount(nMDBG::tStatus2& status) const;

      u32 getMaxLinkSize() const;

      // Configure the DMA Channel controller on the CHInCh
      //   topo:       Layout for the DMA buffer
      //   memAddress: start address for the DMA buffer (or first DMA link)
      //   memSize:    size of the DMA buffer (or first DMA link)
      //   status
      void configure( tDMATopology     topo,
                      u64              memAddress,
                      u32              memSize,
                      nMDBG::tStatus2& status );

      // Start the DMA Channel
      void start(nMDBG::tStatus2& status);

      // Stop the DMA Channel
      void requestStop(nMDBG::tStatus2& status);

      // Get the DMA Channel's status register
      u32 getStatus(nMDBG::tStatus2& status) const;

   private:
      // Usage guidelines
      tCHInChDMAChannelController(void);
      tCHInChDMAChannelController(const tCHInChDMAChannelController& source);
      tCHInChDMAChannelController& operator=(const tCHInChDMAChannelController& source);

   private:
      tXSeries&       _device;
      tDMAController* _controller;
      tDMATopology    _topo;

   }; // tCHInChDMAChannelController
} // nNISTC3

#endif // ___tCHInChDMAChannelController_h___
