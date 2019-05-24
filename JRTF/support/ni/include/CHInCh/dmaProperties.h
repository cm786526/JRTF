/*
 * dmaProperties.h
 *
 * Describe attributes for DMA channel and buffer objects
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___dmaProperties_h___
#define ___dmaProperties_h___

namespace nNISTC3
{
   // DMA Channel Topography
   // The CHInCh only supports two modes (normal and link-chain, see
   // tCHInChDMAChannelController.h), but to demonstrate the different
   // link-chain uses, a few hard-coded implementations are defined below.
   typedef enum
   {
      kNormal = 0,    // Single-use contiguous transfer
      kRing,          // Multi-use contiguous transfer (not supported by the CHInCh)
      kLinkChain,     // Single-use scatter-gather transfer (4 links)
      kLinkChainRing, // Multi-use scatter-gather transfer (4 links)
      kReuseLinkRing, // Multi-use scatter-gather transfer (optimized with 2-link reuse)
      kNone,          // No DMA
   } tDMATopology;

   // DMA Channel Number
   // The CHInCh provides a DMA channel for each subsystem.
   typedef enum
   {
      kAI_DMAChannel = 0,
      kCounter0DmaChannel,
      kCounter1DmaChannel,
      kCounter2DmaChannel,
      kCounter3DmaChannel,
      kDI_DMAChannel,
      kAO_DMAChannel,
      kDO_DMAChannel
   } tDMAChannelNumber;

   // SGL Lengths
   // Most of these are arbitrary and do not depend on the CHInCh hardware implementation
   typedef enum
   {
      kNumLinkChainNodes     = 4,
      kNumLinkChainRingNodes = 4,
      kNumReuseLinkRingNodes = 2  // This value cannot be changed, see tCHInChSGL.h setResuseLink()
   } tNumSGLNodes;

   // Number of page descriptors in each kind of SGL node
   // The CHInCh hardware implementation specifies the maximum size for an SGL in
   // the COREDR register (see tCHInChDMAChannelController.h). Each SGL node has a
   // 16-byte header, and each page descriptor consumes 16 bytes as well. These
   // values are well below the maximum supported and can be increased.
   typedef enum
   {
      kNumPagesInLinkChainNode     = 4,
      kNumPagesInLinkChainRingNode = 4,
      kNumPagesInReuseLinkRingNode = 4
   } tNumPagesInSGLNode;

   // DMA Channel states
   typedef enum
   {
      kUnknown = 0,
      kIdle,
      kConfigured,
      kStarted,
      kStopped
   } tDMAState;

   // DMA Channel Direction
   typedef enum
   {
      kIn  = 0,       // From device to host memory
      kOut = 1        // From host memory to device
   } tDMADirection;
} // nNISTC3

#endif // ___dmaProperties_h___
