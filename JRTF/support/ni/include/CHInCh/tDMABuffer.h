/*
 * tDMABuffer.h
 *
 * Provide a generic interface for DMA buffer control.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tDMABuffer_h___
#define ___tDMABuffer_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// The DMA Channel topology (tDMATopology) tells the buffer how to partition itself
#include "dmaProperties.h"

namespace nNISTC3
{
   class tDMABuffer
   {
   public:
      tDMABuffer();
      virtual ~tDMABuffer();

      // Get/set methods for buffer index
      inline u64  getLocation() const;
      inline void setLocation(u64 location);

      // OS-specific methods for allocating the DMA buffer
      virtual void allocate(u32 size, nMDBG::tStatus2& status) = 0;
      virtual void free() = 0;

      // Copy data to/from the DMA buffer
      virtual void  read(u32 requestedBytes, void *buffer) = 0;
      virtual void write(u32 requestedBytes, void *buffer) = 0;

      // Retrieve information describing the DMA buffer's location/size
      virtual u64 getStartAddress() const = 0; // Physical address of the DMA buffer/SGL link
      virtual u32 getSize() const = 0;         // Length of the DMA buffer
      virtual u32 getLinkSize() const = 0;     // Length of the first DMA SGL link

      // Operate on the DMA buffer
      virtual void initialize(tDMATopology topo, u32 maxLinkSize, nMDBG::tStatus2& status) = 0;

   private:
      u64 _index;
   }; // tDMABuffer

   inline u64 tDMABuffer::getLocation() const
   {
      return _index;
   }

   inline void tDMABuffer::setLocation (u64 location)
   {
      _index = location;
   }
} // nNISTC3

#endif // ___tDMABuffer_h___
