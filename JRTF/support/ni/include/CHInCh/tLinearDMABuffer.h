/*
 * tLinearDMABuffer.h
 *
 * Provide an interface for controlling a contiguous DMA buffer.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tLinearDMABuffer_h___
#define ___tLinearDMABuffer_h___

// Parent class
#include "tDMABuffer.h"

// OS Interface for iBus and tDMAMemory
#include "osiBus.h"

namespace nNISTC3
{
   class tLinearDMABuffer : public tDMABuffer
   {
   public:
      explicit tLinearDMABuffer(iBus *bus);
      virtual ~tLinearDMABuffer ();

      // OS-specific methods for allocating the DMA buffer
      virtual void allocate(u32 size, nMDBG::tStatus2& status);
      virtual void free();

      // Copy data to/from the DMA buffer
      virtual void  read(u32 requestedBytes, void *buffer);
      virtual void write(u32 requestedBytes, void *buffer);

      // Retrieve information describing the DMA buffer's location/size
      virtual u64 getStartAddress() const; // Physical address of the DMA buffer/SGL link
      virtual u32 getSize() const;         // Length of the DMA buffer
      virtual u32 getLinkSize() const;     // Length of the first DMA SGL link

      // Operate on the DMA buffer
      virtual void initialize(tDMATopology topo, u32 maxLinkSize, nMDBG::tStatus2& status);

   private:
      // Usage guidelines
      tLinearDMABuffer(const tLinearDMABuffer&);
      tLinearDMABuffer& operator=(const tLinearDMABuffer&);

   private:
      iBus*       _bus;
      tDMAMemory* _memory;
      u32         _size;

   }; // tLinearDMABuffer
} // nNISTC3

#endif // ___tLinearDMABuffer_h___
