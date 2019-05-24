/*
 * tCHInChSGLChunkyLink.h
 *
 * Define the CHInCh chunky link interface.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tCHInChSGLChunkyLink_h___
#define ___tCHInChSGLChunkyLink_h___

// OS Interface (for basic datatype names)
#include "osiTypes.h"

// OS iBus (for tDMAMemory)
#include "osiBus.h"

namespace nNISTC3
{
   class tCHInChSGLChunkyLink {
   public:
      // Constructor
      //   bus:          iBus object representing the device
      //   previousLink: the previous link in the SGL (if any)
      //   maxSize:      the maximum size in bytes that the link can occupy in memory
      //   status
      tCHInChSGLChunkyLink( iBus* const           bus,
                            tCHInChSGLChunkyLink* previousLink,
                            u32                   maxSize,
                            nMDBG::tStatus2&      status );

      // Destructor
      ~tCHInChSGLChunkyLink();

      // Add a link to this chunky link
      //   physicalAddress: physical address of the physically contiguous chunk of memory
      //   size:            the size of the physically contiguous chunk of memory
      //   status
      void addDataTransferLink( u64              physicalAddress,
                                u32              size,
                                nMDBG::tStatus2& status );

      // Point to the next link. If next is NULL, then there is no next link
      // and thus this link is the last link.
      void setNext(tCHInChSGLChunkyLink *next);

      // Set the reuse bit on this chunky link. This should only be called on
      // the last chunky link in the list. Furthermore, the list is limited by
      // the CHInCH's hardware to two chunky links.
      void setReuseLink();

      // Returns true if the reuse bit on this chunky link is set.
      tBoolean getReuseLink() const;

      // Get the pointer to the next link after this link.
      tCHInChSGLChunkyLink* getNext() const;

      // Get the pointer to the previous link before this link.
      tCHInChSGLChunkyLink* getPrevious() const;

      // Get the size (in bytes) of this chunky link. Note that this is the
      // number of bytes that contain active chunky link data -- NOT the number
      // of bytes allocated to the chunky link.
      u32 getSize() const;

      // Get the physical address of this chunky link.
      u64 getPhysicalAddress() const;

      // Get the linear address of this chunky link.
      void* getVirtualAddress() const;

      // Returns true if the chunky link is empty (i.e. has no transfer links)
      tBoolean isEmpty() const;

   private:
      // These structs represent the physical layout of the chunky link in
      // memory. Their layout is specified by the CHInCh hardware implementation
      // and must not be modified by compiler packing.
   #if kMicrosoft || kGNU
      #pragma pack( push, 1 )
   #else
      #error Unsupported compiler!
   #endif

      struct tHeaderData
      {
         u32 nextLinkSize;
         u32 unused : 30;
         u32 reuseLink : 1;
         u32 isLastLink : 1;
         u64 nextLink;
         enum
         {
            NotLastLink = 0,
            LastLink    = 1
         };
         enum
         {
            doNotReuseLink = 0,
            doReuseLink    = 1
         };
      };

      struct tTransferLinkData
      {
         u32 transferSize;
         u32 unused : 31;
         u32 linkIdent : 1;
         u64 physAddr;
      };

      enum LinkIdent
      {
         TransferLink   = 0,
      };

   #if kMicrosoft || kGNU
      #pragma pack( pop )
   #else
      #error Unsupported compiler!
   #endif

   private:
      // Usage guidelines
      tCHInChSGLChunkyLink(const tCHInChSGLChunkyLink&);
      tCHInChSGLChunkyLink& operator=(const tCHInChSGLChunkyLink&);

   private:
      // Get the pointer to the header of this chunky link.
      tHeaderData* getHeader() const;

      // Get the number of bytes in the chunky link that are available to have
      // new data written to.
      u32 getNumberOfBytesAvailable() const;

      // Update the previous link with information about this link (if there is
      // a previous link).
      void updatePrevious();

      iBus* const           _bus;
      const u32             _maxSize;         // Maximum size for an SGL node
      tDMAMemory*           _linkMemory;      // The memory allocated for this SGL node
      u32                   _linkMemorySize;  // The size of the memory allocated for this SGL node
      u32                   _bytesUsed;       // The number of bytes in the SGL node with meaningful information (header and page descriptors)
      tCHInChSGLChunkyLink* _previousLink;
      tCHInChSGLChunkyLink* _nextLink;
   }; // tCHInChSGLChunkyLink

   inline tCHInChSGLChunkyLink::tHeaderData* tCHInChSGLChunkyLink::getHeader() const
   {
      return reinterpret_cast<tHeaderData*>(getVirtualAddress());
   }

   inline u32 tCHInChSGLChunkyLink::getSize() const
   {
      return _bytesUsed;
   }

   inline u32 tCHInChSGLChunkyLink::getNumberOfBytesAvailable() const
   {
      return _linkMemorySize - _bytesUsed;
   }

   inline u64 tCHInChSGLChunkyLink::getPhysicalAddress() const
   {
      return _linkMemory->getPhysicalAddress();
   }

   inline void* tCHInChSGLChunkyLink::getVirtualAddress() const
   {
      return _linkMemory->getAddress();
   }

   inline tBoolean tCHInChSGLChunkyLink::isEmpty() const
   {
      return _bytesUsed == sizeof(tHeaderData);
   }

   inline tCHInChSGLChunkyLink* tCHInChSGLChunkyLink::getNext() const
   {
      return _nextLink;
   }

   inline tCHInChSGLChunkyLink* tCHInChSGLChunkyLink::getPrevious() const
   {
      return _previousLink;
   }
} // nNISTC3

#endif // ___tCHInChSGLChunkyLink_h___
