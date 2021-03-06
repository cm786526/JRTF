// Copyright 2011 National Instruments
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tDIValues_h___
#define ___tDIValues_h___

#include "tInTimerValues.h"

namespace nDI {
   using namespace nInTimer;
   typedef enum {
      kDI_OneByte                        = 0,
      kDI_TwoBytes                       = 1,
      kDI_FourBytes                      = 2,
   } tDI_DataWidth_t;

   typedef enum {
      kDI_DataLane0                      = 0,
      kDI_DataLane1                      = 1,
      kDI_DataLane2                      = 2,
      kDI_DataLane3                      = 3,
   } tDI_Data_Lane_t;

   typedef enum {
      kGate_Disabled                     = 0,
      kGate_PFI0                         = 1,
      kGate_PFI1                         = 2,
      kGate_PFI2                         = 3,
      kGate_PFI3                         = 4,
      kGate_PFI4                         = 5,
      kGate_PFI5                         = 6,
      kGate_PFI6                         = 7,
      kGate_PFI7                         = 8,
      kGate_PFI8                         = 9,
      kGate_PFI9                         = 10,
      kGate_RTSI0                        = 11,
      kGate_RTSI1                        = 12,
      kGate_RTSI2                        = 13,
      kGate_RTSI3                        = 14,
      kGate_RTSI4                        = 15,
      kGate_RTSI5                        = 16,
      kGate_RTSI6                        = 17,
      kGate_PXIe_DStarA                  = 18,
      kGate_PXIe_DStarB                  = 19,
      kGate_Star_Trigger                 = 20,
      kGate_PFI10                        = 21,
      kGate_PFI11                        = 22,
      kGate_PFI12                        = 23,
      kGate_PFI13                        = 24,
      kGate_PFI14                        = 25,
      kGate_PFI15                        = 26,
      kGate_RTSI7                        = 27,
      kGate_Analog_Trigger               = 30,
      kGate_Low                          = 31,
      kGate_G0_Out                       = 32,
      kGate_G1_Out                       = 33,
      kGate_G2_Out                       = 34,
      kGate_G3_Out                       = 35,
      kGate_G0_Gate                      = 36,
      kGate_G1_Gate                      = 37,
      kGate_G2_Gate                      = 38,
      kGate_G3_Gate                      = 39,
      kGate_AI_Gate                      = 40,
      kGate_AO_Gate                      = 43,
      kGate_DO_Gate                      = 44,
      kGate_IntTriggerA0                 = 53,
      kGate_IntTriggerA1                 = 54,
      kGate_IntTriggerA2                 = 55,
      kGate_IntTriggerA3                 = 56,
      kGate_IntTriggerA4                 = 57,
      kGate_IntTriggerA5                 = 58,
      kGate_IntTriggerA6                 = 59,
      kGate_IntTriggerA7                 = 60,
   } tDI_External_Gate_Select_t;

   typedef enum {
      k6509Mode                          = 0,
      kCorrelatedMode                    = 1,
   } tDI_FilterMode_t;

   typedef enum {
      kNo_Filter                         = 0,
      kSmall_Filter                      = 1,
      kMedium_Filter                     = 2,
      kLarge_Filter                      = 3,
   } tDI_Filter_Select_t;

   typedef enum {
      kForceZero                         = 0,
      kKeepData                          = 1,
   } tDI_Mask_t;

   typedef enum {
      kActive_High_Or_Rising_Edge        = 0,
      kActive_Low_Or_Falling_Edge        = 1,
   } tDI_Polarity_t;

   typedef enum {
      kStart1_SW_Pulse                   = 0,
      kStart1_PFI0                       = 1,
      kStart1_PFI1                       = 2,
      kStart1_PFI2                       = 3,
      kStart1_PFI3                       = 4,
      kStart1_PFI4                       = 5,
      kStart1_PFI5                       = 6,
      kStart1_PFI6                       = 7,
      kStart1_PFI7                       = 8,
      kStart1_PFI8                       = 9,
      kStart1_PFI9                       = 10,
      kStart1_RTSI0                      = 11,
      kStart1_RTSI1                      = 12,
      kStart1_RTSI2                      = 13,
      kStart1_RTSI3                      = 14,
      kStart1_RTSI4                      = 15,
      kStart1_RTSI5                      = 16,
      kStart1_RTSI6                      = 17,
      kStart1_PXIe_DStarA                = 18,
      kStart1_PXIe_DStarB                = 19,
      kStart1_Star_Trigger               = 20,
      kStart1_PFI10                      = 21,
      kStart1_PFI11                      = 22,
      kStart1_PFI12                      = 23,
      kStart1_PFI13                      = 24,
      kStart1_PFI14                      = 25,
      kStart1_PFI15                      = 26,
      kStart1_RTSI7                      = 27,
      kStart1_DIO_ChgDetect              = 28,
      kStart1_Analog_Trigger             = 30,
      kStart1_Low                        = 31,
      kStart1_G0_Out                     = 36,
      kStart1_G1_Out                     = 37,
      kStart1_G2_Out                     = 38,
      kStart1_G3_Out                     = 39,
      kStart1_AI_Start1                  = 40,
      kStart1_AO_Start1                  = 43,
      kStart1_DO_Start1                  = 44,
      kStart1_IntTriggerA0               = 53,
      kStart1_IntTriggerA1               = 54,
      kStart1_IntTriggerA2               = 55,
      kStart1_IntTriggerA3               = 56,
      kStart1_IntTriggerA4               = 57,
      kStart1_IntTriggerA5               = 58,
      kStart1_IntTriggerA6               = 59,
      kStart1_IntTriggerA7               = 60,
   } tDI_START1_Select_t;

   typedef enum {
      kStart2_SW_Pulse                   = 0,
      kStart2_PFI0                       = 1,
      kStart2_PFI1                       = 2,
      kStart2_PFI2                       = 3,
      kStart2_PFI3                       = 4,
      kStart2_PFI4                       = 5,
      kStart2_PFI5                       = 6,
      kStart2_PFI6                       = 7,
      kStart2_PFI7                       = 8,
      kStart2_PFI8                       = 9,
      kStart2_PFI9                       = 10,
      kStart2_RTSI0                      = 11,
      kStart2_RTSI1                      = 12,
      kStart2_RTSI2                      = 13,
      kStart2_RTSI3                      = 14,
      kStart2_RTSI4                      = 15,
      kStart2_RTSI5                      = 16,
      kStart2_RTSI6                      = 17,
      kStart2_PXIe_DStarA                = 18,
      kStart2_PXIe_DStarB                = 19,
      kStart2_Star_Trigger               = 20,
      kStart2_PFI10                      = 21,
      kStart2_PFI11                      = 22,
      kStart2_PFI12                      = 23,
      kStart2_PFI13                      = 24,
      kStart2_PFI14                      = 25,
      kStart2_PFI15                      = 26,
      kStart2_RTSI7                      = 27,
      kStart2_DIO_ChgDetect              = 28,
      kStart2_Analog_Trigger             = 30,
      kStart2_Low                        = 31,
      kStart2_G0_Out                     = 36,
      kStart2_G1_Out                     = 37,
      kStart2_G2_Out                     = 38,
      kStart2_G3_Out                     = 39,
      kStart2_AI_Start2                  = 40,
      kStart2_AO_Start1                  = 43,
      kStart2_DO_Start1                  = 44,
      kStart2_IntTriggerA0               = 53,
      kStart2_IntTriggerA1               = 54,
      kStart2_IntTriggerA2               = 55,
      kStart2_IntTriggerA3               = 56,
      kStart2_IntTriggerA4               = 57,
      kStart2_IntTriggerA5               = 58,
      kStart2_IntTriggerA6               = 59,
      kStart2_IntTriggerA7               = 60,
   } tDI_START2_Select_t;

   typedef enum {
      kSampleClk_Internal                = 0,
      kSampleClk_PFI0                    = 1,
      kSampleClk_PFI1                    = 2,
      kSampleClk_PFI2                    = 3,
      kSampleClk_PFI3                    = 4,
      kSampleClk_PFI4                    = 5,
      kSampleClk_PFI5                    = 6,
      kSampleClk_PFI6                    = 7,
      kSampleClk_PFI7                    = 8,
      kSampleClk_PFI8                    = 9,
      kSampleClk_PFI9                    = 10,
      kSampleClk_RTSI0                   = 11,
      kSampleClk_RTSI1                   = 12,
      kSampleClk_RTSI2                   = 13,
      kSampleClk_RTSI3                   = 14,
      kSampleClk_RTSI4                   = 15,
      kSampleClk_RTSI5                   = 16,
      kSampleClk_RTSI6                   = 17,
      kSampleClk_DIO_ChgDetect           = 18,
      kSampleClk_G0_Out                  = 19,
      kSampleClk_Star_Trigger            = 20,
      kSampleClk_PFI10                   = 21,
      kSampleClk_PFI11                   = 22,
      kSampleClk_PFI12                   = 23,
      kSampleClk_PFI13                   = 24,
      kSampleClk_PFI14                   = 25,
      kSampleClk_PFI15                   = 26,
      kSampleClk_RTSI7                   = 27,
      kSampleClk_G1_Out                  = 28,
      kSampleClk_AI_Start                = 29,
      kSampleClk_Atrig                   = 30,
      kSampleClk_Low                     = 31,
      kSampleClk_PXIe_DStarA             = 32,
      kSampleClk_PXIe_DStarB             = 33,
      kSampleClk_G2_Out                  = 34,
      kSampleClk_G3_Out                  = 35,
      kSampleClk_G0_SampleClk            = 36,
      kSampleClk_G1_SampleClk            = 37,
      kSampleClk_G2_SampleClk            = 38,
      kSampleClk_G3_SampleClk            = 39,
      kSampleClk_AI_Convert              = 40,
      kSampleClk_AO_Update               = 43,
      kSampleClk_DO_Update               = 44,
      kSampleClk_IntTriggerA0            = 53,
      kSampleClk_IntTriggerA1            = 54,
      kSampleClk_IntTriggerA2            = 55,
      kSampleClk_IntTriggerA3            = 56,
      kSampleClk_IntTriggerA4            = 57,
      kSampleClk_IntTriggerA5            = 58,
      kSampleClk_IntTriggerA6            = 59,
      kSampleClk_IntTriggerA7            = 60,
      kSampleClk_FreqOut                 = 61,
   } tDI_StartConvertSelMux_t;

   namespace nDI_ChangeDetectStatusRegister {
      namespace nDI_ChangeDetectStatus {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nDI_ChangeDetectError {
         enum {
            kMask = 0x2,
            kOffset = 0x1,
         };
      }

   }

   namespace nDI_ChangeIrqRE_Register {
      namespace nDI_ChangeIrqRE {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_ChangeDetectLatchedDI_Register {
      namespace nDI_ChangeDetectLatchedDI {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_ChangeIrqFE_Register {
      namespace nDI_ChangeIrqFE {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_ChangeDetectLatchedPFI_Register {
      namespace nDI_ChangeDetectLatchedPFI {
         enum {
            kMask = 0xffff,
            kOffset = 0,
         };
      }

   }

   namespace nPFI_ChangeIrq_Register {
      namespace nPFI_ChangeIrqRE {
         enum {
            kMask = 0xffff,
            kOffset = 0,
         };
      }

      namespace nPFI_ChangeIrqFE {
         enum {
            kMask = 0xffff0000,
            kOffset = 0x10,
         };
      }

   }

   namespace nDI_ChangeDetectIRQ_Register {
      namespace nChangeDetectIRQ_Acknowledge {
         enum {
            kMask = 0x1,
            kOffset = 0,
         };
      }

      namespace nChangeDetectErrorIRQ_Acknowledge {
         enum {
            kMask = 0x2,
            kOffset = 0x1,
         };
      }

      namespace nChangeDetectIRQ_Disable {
         enum {
            kMask = 0x10,
            kOffset = 0x4,
         };
      }

      namespace nChangeDetectIRQ_Enable {
         enum {
            kMask = 0x20,
            kOffset = 0x5,
         };
      }

      namespace nChangeDetectErrorIRQ_Disable {
         enum {
            kMask = 0x40,
            kOffset = 0x6,
         };
      }

      namespace nChangeDetectErrorIRQ_Enable {
         enum {
            kMask = 0x80,
            kOffset = 0x7,
         };
      }

   }

   namespace nDI_DMA_Select_Register {
      namespace nDI_DoneNotificationEnable {
         enum {
            kMask = 0x80,
            kOffset = 0x7,
         };
      }

   }

   namespace nStatic_Digital_Input_Register {
      namespace nDI_StaticValue {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_FIFO_St_Register {
      namespace nCDI_FIFO_FullCount {
         enum {
            kMask = 0xffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_Mode_Register {
      namespace nDI_DigitalFiltersMode {
         enum {
            kMask = 0x800,
            kOffset = 0xb,
         };
      }

      namespace nDI_Data_Lane {
         enum {
            kMask = 0x3000,
            kOffset = 0xc,
         };
      }

      namespace nDI_DataWidth {
         enum {
            kMask = 0xc000,
            kOffset = 0xe,
         };
      }

   }

   namespace nDI_FIFO_Data_Register {
      namespace nCDI_FIFO_Data {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_FIFO_Data_Register16 {
      namespace nCDI_FIFO_Data16 {
         enum {
            kMask = 0xffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_FIFO_Data_Register8 {
      namespace nCDI_FIFO_Data8 {
         enum {
            kMask = 0xff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_Mask_Enable_Register {
      namespace nCDI_Mask {
         enum {
            kMask = 0xffffffff,
            kOffset = 0,
         };
      }

   }

   namespace nDI_Trigger_Select_Register {
      namespace nDI_START1_Select {
         enum {
            kMask = 0x3f,
            kOffset = 0,
         };
      }

      namespace nDI_START1_Edge {
         enum {
            kMask = 0x40,
            kOffset = 0x6,
         };
      }

      namespace nDI_START1_Polarity {
         enum {
            kMask = 0x80,
            kOffset = 0x7,
         };
      }

      namespace nDI_START2_Select {
         enum {
            kMask = 0x3f00,
            kOffset = 0x8,
         };
      }

      namespace nDI_START2_Edge {
         enum {
            kMask = 0x4000,
            kOffset = 0xe,
         };
      }

      namespace nDI_START2_Polarity {
         enum {
            kMask = 0x8000,
            kOffset = 0xf,
         };
      }

      namespace nDI_External_Gate_Select {
         enum {
            kMask = 0x3f0000,
            kOffset = 0x10,
         };
      }

      namespace nDI_External_Gate_Polarity {
         enum {
            kMask = 0x800000,
            kOffset = 0x17,
         };
      }

      namespace nDI_CONVERT_Source_Select {
         enum {
            kMask = 0x3f000000,
            kOffset = 0x18,
         };
      }

      namespace nDI_CONVERT_Source_Polarity {
         enum {
            kMask = 0x80000000,
            kOffset = 0x1f,
         };
      }

   }

   namespace nDI_FilterRegisterLo {
      namespace nDI0_Filter_Select {
         enum {
            kMask = 0x3,
            kOffset = 0,
         };
      }

      namespace nDI1_Filter_Select {
         enum {
            kMask = 0xc,
            kOffset = 0x2,
         };
      }

      namespace nDI2_Filter_Select {
         enum {
            kMask = 0x30,
            kOffset = 0x4,
         };
      }

      namespace nDI3_Filter_Select {
         enum {
            kMask = 0xc0,
            kOffset = 0x6,
         };
      }

      namespace nDI4_Filter_Select {
         enum {
            kMask = 0x300,
            kOffset = 0x8,
         };
      }

      namespace nDI5_Filter_Select {
         enum {
            kMask = 0xc00,
            kOffset = 0xa,
         };
      }

      namespace nDI6_Filter_Select {
         enum {
            kMask = 0x3000,
            kOffset = 0xc,
         };
      }

      namespace nDI7_Filter_Select {
         enum {
            kMask = 0xc000,
            kOffset = 0xe,
         };
      }

      namespace nDI8_Filter_Select {
         enum {
            kMask = 0x30000,
            kOffset = 0x10,
         };
      }

      namespace nDI9_Filter_Select {
         enum {
            kMask = 0xc0000,
            kOffset = 0x12,
         };
      }

      namespace nDI10_Filter_Select {
         enum {
            kMask = 0x300000,
            kOffset = 0x14,
         };
      }

      namespace nDI11_Filter_Select {
         enum {
            kMask = 0xc00000,
            kOffset = 0x16,
         };
      }

      namespace nDI12_Filter_Select {
         enum {
            kMask = 0x3000000,
            kOffset = 0x18,
         };
      }

      namespace nDI13_Filter_Select {
         enum {
            kMask = 0xc000000,
            kOffset = 0x1a,
         };
      }

      namespace nDI14_Filter_Select {
         enum {
            kMask = 0x30000000,
            kOffset = 0x1c,
         };
      }

      namespace nDI15_Filter_Select {
         enum {
            kMask = 0xc0000000,
            kOffset = 0x1e,
         };
      }

   }

   namespace nDI_FilterRegisterHi {
      namespace nDI16_Filter_Select {
         enum {
            kMask = 0x3,
            kOffset = 0,
         };
      }

      namespace nDI17_Filter_Select {
         enum {
            kMask = 0xc,
            kOffset = 0x2,
         };
      }

      namespace nDI18_Filter_Select {
         enum {
            kMask = 0x30,
            kOffset = 0x4,
         };
      }

      namespace nDI19_Filter_Select {
         enum {
            kMask = 0xc0,
            kOffset = 0x6,
         };
      }

      namespace nDI20_Filter_Select {
         enum {
            kMask = 0x300,
            kOffset = 0x8,
         };
      }

      namespace nDI21_Filter_Select {
         enum {
            kMask = 0xc00,
            kOffset = 0xa,
         };
      }

      namespace nDI22_Filter_Select {
         enum {
            kMask = 0x3000,
            kOffset = 0xc,
         };
      }

      namespace nDI23_Filter_Select {
         enum {
            kMask = 0xc000,
            kOffset = 0xe,
         };
      }

      namespace nDI24_Filter_Select {
         enum {
            kMask = 0x30000,
            kOffset = 0x10,
         };
      }

      namespace nDI25_Filter_Select {
         enum {
            kMask = 0xc0000,
            kOffset = 0x12,
         };
      }

      namespace nDI26_Filter_Select {
         enum {
            kMask = 0x300000,
            kOffset = 0x14,
         };
      }

      namespace nDI27_Filter_Select {
         enum {
            kMask = 0xc00000,
            kOffset = 0x16,
         };
      }

      namespace nDI28_Filter_Select {
         enum {
            kMask = 0x3000000,
            kOffset = 0x18,
         };
      }

      namespace nDI29_Filter_Select {
         enum {
            kMask = 0xc000000,
            kOffset = 0x1a,
         };
      }

      namespace nDI30_Filter_Select {
         enum {
            kMask = 0x30000000,
            kOffset = 0x1c,
         };
      }

      namespace nDI31_Filter_Select {
         enum {
            kMask = 0xc0000000,
            kOffset = 0x1e,
         };
      }

   }

   using namespace nDI_ChangeDetectStatusRegister;
   using namespace nDI_ChangeIrqRE_Register;
   using namespace nDI_ChangeDetectLatchedDI_Register;
   using namespace nDI_ChangeIrqFE_Register;
   using namespace nDI_ChangeDetectLatchedPFI_Register;
   using namespace nPFI_ChangeIrq_Register;
   using namespace nDI_ChangeDetectIRQ_Register;
   using namespace nDI_DMA_Select_Register;
   using namespace nStatic_Digital_Input_Register;
   using namespace nDI_FIFO_St_Register;
   using namespace nDI_Mode_Register;
   using namespace nDI_FIFO_Data_Register;
   using namespace nDI_FIFO_Data_Register16;
   using namespace nDI_FIFO_Data_Register8;
   using namespace nDI_Mask_Enable_Register;
   using namespace nDI_Trigger_Select_Register;
   using namespace nDI_FilterRegisterLo;
   using namespace nDI_FilterRegisterHi;
}

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

