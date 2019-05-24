/*
 * tCHInChSGL.h
 *
 * Define the CHInCh Scatter-Gather List interface.
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___tCHInChSGL_h___
#define ___tCHInChSGL_h___

#include "tLinkInformation.h"

// Forward declarations
class iBus;

namespace nNISTC3
{
// Forward declarations
class tCHInChSGLChunkyLink;

   class tCHInChSGL {
   public:
      // tLinkLocation
      // Store information about the location of a particular link within a
      // chunky link. 'chunkyLink' is the chunky link that contains our link
      // of interest, and byteOffset is the raw byte offset within the
      // chunkyLink where our link of interest starts.
      struct tLinkLocation
      {
         tLinkLocation( tCHInChSGLChunkyLink* inChunkyLink = NULL,
                        u32                   inByteOffset = 0 ) :
            chunkyLink(inChunkyLink),
            byteOffset(inByteOffset)
         {
            // Nothing else to initialize.
         }

         tCHInChSGLChunkyLink* chunkyLink;
         u32                   byteOffset;
      };

      // Constructor/Destructor
      tCHInChSGL();
      ~tCHInChSGL();

      // Initialize the SGL.
      // This is primarily provided to allow a tCHInChSGL object to be a
      // data member of another class that manages the device. Once the
      // maxLinkSize has been read from the device, the containingclass
      // can call initialize to set up the SGL without having to allocate
      // the SGL from the dynamic memory store. This function should only
      // be called once. Use the reset() function to clear out the SGL for
      // re-use in another transfer.
      //   bus:         iBus object representing the device
      //   maxLinkSize: the size, in bytes, of the largest chunky link that
      //                the hardware can accept.
      //   status
      void initialize( iBus* const      bus,
                       u32              maxLinkSize,
                       nMDBG::tStatus2& status );

      // Add a block of physically contiguous memory to be used in a data transfer.
      //   physicalAddress: the starting address of the data transfer
      //   size:            the size the data transfer
      //   status
      //   newLink:         if true, create a new link for this transfer
      //   returns a tLinkLocation object describing where in the link this transfer was added
      tLinkLocation addTransfer( u64              physicalAddress,
                                 u32              size,
                                 nMDBG::tStatus2& status,
                                 tBoolean         newLink = kFalse );

      // Configure the SGL such that the last link in the list points to the
      // first, thus making the transfer a ring buffer.
      void setWrapAround();

      // Configure the SGL such that the second chunky link points to the
      // first chunky link, thus making the transfer a ring. Furthermore, set
      // the 'reuse', which causes the CHInCh to only fetch the chunky links
      // once and reuse them. Note: this is only valid with ChunkLink lists of
      // length two (as required by the CHInCh hardware implementation).
      void setReuseLink();

      // Configure the SGL such that the last link terminates the transfer
      void setStopOnLastLink();

      // Reset the SGL to its initial state
      void reset(nMDBG::tStatus2& status);

      // Get the values for the Link Address and Link Size Registers that
      // should be programmed on the CHInCh.
      u64 getCHLAR() const;
      u32 getCHLSR() const;

      tBoolean isInitialized() const;

      operator tLinkInformation() const;

   private:
      // Usage guidelines
      tCHInChSGL(const tCHInChSGL&);
      tCHInChSGL& operator=(const tCHInChSGL&);

   private:
      // Allocate a new tCHInCHSGLChunkyLink to use in this SGL
      tCHInChSGLChunkyLink* allocateChunkyLink(nMDBG::tStatus2& status);

      // Clear out the SGL for re-initialization
      void clear(void);

      iBus*                 _bus;
      u32                   _maxLinkSize;
      tBoolean              _initialized;
      tCHInChSGLChunkyLink* _head;
      tCHInChSGLChunkyLink* _tail;

   }; // tCHInChSGL
} // nNISTC3

#endif // ___tCHInChSGL_h___
