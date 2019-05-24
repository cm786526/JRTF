/*
 * tScatterGatherDMABuffer.h
 *
 * Provide an interface for controlling a linked-list DMA buffer.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tScatterGatherDMABuffer_h___
#define ___tScatterGatherDMABuffer_h___

// Parent class
#include "tDMABuffer.h"

// OS Interface for iBus and tDMAMemory
#include "osiBus.h"

// Scatter Gather Link
#include "tCHInChSGL.h"

namespace nNISTC3
{
   class tScatterGatherDMABuffer : public tDMABuffer
   {
   public:
      explicit tScatterGatherDMABuffer(iBus *bus);
      virtual ~tScatterGatherDMABuffer ();

      // OS-specific methods for allocating the DMA buffer
      virtual void allocate(u32 size, nMDBG::tStatus2& status);
      virtual void free();

      // Copy data to/from the DMA buffer
      virtual void  read(u32 requestedBytes, void *buffer);
      virtual void write(u32 requestedBytes, void *buffer);

      // Retrieve information describing the DMA link's location/size
      virtual u64 getStartAddress() const; // Physical address of the DMA buffer/SGL link
      virtual u32 getSize() const;         // Length of the DMA buffer
      virtual u32 getLinkSize() const;     // Length of the first DMA SGL link

      // Operate on the DMA buffer
      virtual void initialize(tDMATopology topo, u32 maxLinkSize, nMDBG::tStatus2& status);

   private:
      // Usage guidelines
      tScatterGatherDMABuffer(const tScatterGatherDMABuffer&);
      tScatterGatherDMABuffer& operator=(const tScatterGatherDMABuffer&);

   private:
      void _buildGenericSGL( u32              maxLinkSize,
                             u32              numPages,
                             u32              pagesPerNode,
                             u32              dmaPageSize,
                             u32              dmaPageRem,
                             nMDBG::tStatus2& status );

      iBus*       _bus;
      tDMAMemory* _memory;       // The DMA memory used to hold the links (not nodes, which are allocated/held by _sgl)
      u32         _size;         // The size of DMA memory allocated by the OS (again, for links, not nodes)
      tCHInChSGL  _sgl;          // SGL interface, which holds tCHInChSGLChunkyLinks (which hold the DMA link memory)

   }; // tScatterGatherDMABuffer
} // nNISTC3

#endif // ___tScatterGatherDMABuffer_h___
