/*
 * tCHInChDMAChannel.h
 *
 * Provide a user-level interface for DMA Channel control
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tCHInChDMAChannel_h___
#define ___tCHInChDMAChannel_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// For tDMABuffer member, tDMATopology
#include "tDMABuffer.h"

// For tCHInChDMAChannelController member
#include "tCHInChDMAChannelController.h"

namespace nNISTC3
{
   class tCHInChDMAChannel
   {
   public:
      // Constructor: place channel into kIdle state
      //   device:        tXSeries object representing the device
      //   channelNumber: DMA channel to use on CHInCh
      //   status
      tCHInChDMAChannel( tXSeries&         device,
                         tDMAChannelNumber channelNumber,
                         nMDBG::tStatus2&  status );

      // Destructor
      ~tCHInChDMAChannel();

      // Configure the DMA channel: place channel into kConfigured state
      //   bus:       iBus object representing the device
      //   topo:      layout for the DMA buffer
      //   direction: DMA transfer direction
      //   size:      of DMA buffer in bytes
      //   status
      void configure( iBus* const      bus,
                      tDMATopology     topo,
                      tDMADirection    direction,
                      u32              size,
                      nMDBG::tStatus2& status );

      // Start the DMA channel: place channel into kStarted state
      void start(nMDBG::tStatus2& status);

      // Stop the DMA channel: place channel into kStopped state
      void stop(nMDBG::tStatus2& status);

      // Read data from the DMA Channel: channel must be in kStarted state
      //   requestedBytes:  requested number of bytes to be read
      //   buffer:          buffer from which to copy the data
      //   bytesLeft:       data left in the DMA buffer
      //   allowOverwrite:  can the channel overwrite unread data?
      //   dataOverwritten: has the channel overwritten unread data?
      //   status
      void read( u32       requestedBytes,
                 u8*       buffer,
                 u32*      bytesLeft,
                 tBoolean  allowOverwrite,
                 tBoolean* dataOverwritten,
                 nMDBG::tStatus2& status );

      // Write data to the DMA Channel: channel must be kConfigured or kStarted
      //   requestedBytes:    requested number of bytes to be written
      //   buffer:            buffer into which to copy the data
      //   bytesLeft:         space left in the DMA buffer
      //   allowRegeneration: can the channel regenerate old data?
      //   dataRegenerated:   has the channel regenerated old data?
      //   status
      void write( u32       requestedBytes,
                  u8*       buffer,
                  u32*      bytesLeft,
                  tBoolean  allowRegeneration,
                  tBoolean* dataRegenerated,
                  nMDBG::tStatus2& status );

      // Reset the DMA channel: place channel into kIdle state
      void reset(nMDBG::tStatus2& status);

      // Get the status of the DMA channel controller
      u32 getControllerStatus(nMDBG::tStatus2& status) const;

   private:
      // Usage guidelines
      tCHInChDMAChannel(const tCHInChDMAChannel& rhs);
      tCHInChDMAChannel& operator=(const tCHInChDMAChannel& rhs);

   private:
      void _config(nMDBG::tStatus2& status);
      u32 _getBytesInBuffer(nMDBG::tStatus2& status);

      u64                         _readIdx;
      u64                         _writeIdx;
      u64                         _lastwriteIdx;  // Last "good" _writdeIdx snapshot

      tDMADirection               _direction;
      tDMATopology                _topo;
      u32                         _size;          // Size of DMA buffer used for data (excludes SGL nodes, if present)

      tDMAState                   _state;
      tDMABuffer*                 _buffer;        // Accesses the host buffer
      tCHInChDMAChannelController _controller;    // Accesses the CHInCh

   }; // tCHInChDMAChannel
} // nNISTC3

#endif // ___tCHInChDMAChannel_h___
