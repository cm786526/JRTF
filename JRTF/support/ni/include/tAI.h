// Copyright 2011 National Instruments
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tAI_h___
#define ___tAI_h___

// includes
#include "osiTypes.h"
#include "osiBus.h"
#include "tInTimer.h"
#include "tAIValues.h"


#ifndef ___tAIValues_h___
#include "tAIValues.h"
#endif

#ifndef nNIMXRegisterMap120_mBuildFieldId

// Algorithm:
//    Move lowermost 5 bits (4 through 0) of field id to uppermost 5 bits (31
//          through 27)
//    Move bit 5 of field id to bit 26
//    Move bit 6 of field id to bit 25
//    OR in the register id (which is allowed the remaining bits)
//
// Why not move the lowermost 7 bits directly to the uppermost 7 bits? Because
// we originally moved only the lowermost 5, and for backwards compatibility,
// we can't change where those 5 bits end up.
//
// For future expansion purposes, the bits beyond the first 5 are put in reverse
// order in the resulting combined id.
#define nNIMXRegisterMap120_mBuildFieldId(fieldId, regId) \
   ( \
     ((fieldId) << 27) | \
     ((((fieldId) >> 5) & 0x1) << 26) | \
     ((((fieldId) >> 6) & 0x1) << 25) | \
     (regId) \
   )

#endif

#ifndef nNIMXRegisterMap120_mExtractFieldId

// Algorithm: (basically the reverse of mBuildFieldId)
//    Move uppermost 5 bits (31 through 27) to lowermost 5 bits (4 through 0)
//    Move 26th bit to bit 5 (right-shifting by (26 - 5) is like right-shifting
//          by 26 then left-shifting by 5, but it's more efficient)
//    Move 25th bit to bit 6
#define nNIMXRegisterMap120_mExtractFieldId(id) \
   (unsigned int) \
   ( \
     (((id) >> 27) & 0x1F) | \
     (((id) & (0x1 << 26)) >> (26 - 5)) | \
     (((id) & (0x1 << 25)) >> (25 - 6)) \
   )

#endif

class tAI
{
public:
   tInTimer AI_Timer;

   //---------------------------------------------------------------------------
   // IO Strategies
   //---------------------------------------------------------------------------
   class tReg16IODirect32
   {
   public:
      inline void write(
         tBusSpaceReference addrSpace,
         u32 offset,
         u16 value,
         nMDBG::tStatus2* statusChain = NULL);

      inline u16 read(
         tBusSpaceReference addrSpace,
         u32 offset,
         nMDBG::tStatus2* statusChain = NULL);
   };

   class tReg32IODirect32
   {
   public:
      inline void write(
         tBusSpaceReference addrSpace,
         u32 offset,
         u32 value,
         nMDBG::tStatus2* statusChain = NULL);

      inline u32 read(
         tBusSpaceReference addrSpace,
         u32 offset,
         nMDBG::tStatus2* statusChain = NULL);
   };

   //---------------------------------------------------------------------------
   // AI_Config_FIFO_Status_Register
   //---------------------------------------------------------------------------
   class tAI_Config_FIFO_Status_Register : public tReg32IODirect32
   {
   public:
      typedef tReg32IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x0,
         kId     = 0
      };
      tAI_Config_FIFO_Status_Register();


      typedef enum {
         kRegisterId                          = 0,
         kAI_Config_FIFO_StatusId          = 1,
         kMaxFieldId                          = 1
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Register Accessors (Compile-time selectable)
      inline tAI_Config_FIFO_Status_Register& setRegister(u32 value, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getRegister(nMDBG::tStatus2* statusChain = NULL) const;

      inline void refresh(nMDBG::tStatus2* statusChain = NULL);

      inline u32 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline tAI_Config_FIFO_Status_Register& setAI_Config_FIFO_Status(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getAI_Config_FIFO_Status(nMDBG::tStatus2* statusChain = NULL) const;

      inline u32 readAI_Config_FIFO_Status(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      u32 _softCopy;

      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_Config_FIFO_Status_Register(const tAI_Config_FIFO_Status_Register&);
      tAI_Config_FIFO_Status_Register& operator=(const tAI_Config_FIFO_Status_Register&);

   };

   //---------------------------------------------------------------------------
   // AI_Data_FIFO_Status_Register
   //---------------------------------------------------------------------------
   class tAI_Data_FIFO_Status_Register : public tReg32IODirect32
   {
   public:
      typedef tReg32IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x4,
         kId     = 1
      };
      tAI_Data_FIFO_Status_Register();


      typedef enum {
         kRegisterId                          = 0,
         kAI_Data_FIFO_StatusId            = 1,
         kMaxFieldId                          = 1
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Register Accessors (Compile-time selectable)
      inline tAI_Data_FIFO_Status_Register& setRegister(u32 value, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getRegister(nMDBG::tStatus2* statusChain = NULL) const;

      inline void refresh(nMDBG::tStatus2* statusChain = NULL);

      inline u32 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline tAI_Data_FIFO_Status_Register& setAI_Data_FIFO_Status(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getAI_Data_FIFO_Status(nMDBG::tStatus2* statusChain = NULL) const;

      inline u32 readAI_Data_FIFO_Status(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      u32 _softCopy;

      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_Data_FIFO_Status_Register(const tAI_Data_FIFO_Status_Register&);
      tAI_Data_FIFO_Status_Register& operator=(const tAI_Data_FIFO_Status_Register&);

   };

   //---------------------------------------------------------------------------
   // AI_FIFO_Data_Register
   //---------------------------------------------------------------------------
   class tAI_FIFO_Data_Register : public tReg32IODirect32
   {
   public:
      typedef tReg32IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x8,
         kId     = 2
      };
      tAI_FIFO_Data_Register();


      typedef enum {
         kRegisterId                          = 0,
         kAI_FIFO_DataId                   = 1,
         kMaxFieldId                          = 1
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Register Accessors (Compile-time selectable)

      inline u32 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline u32 readAI_FIFO_Data(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_FIFO_Data_Register(const tAI_FIFO_Data_Register&);
      tAI_FIFO_Data_Register& operator=(const tAI_FIFO_Data_Register&);

   };

   //---------------------------------------------------------------------------
   // AI_FIFO_Data_Register16
   //---------------------------------------------------------------------------
   class tAI_FIFO_Data_Register16 : public tReg16IODirect32
   {
   public:
      typedef tReg16IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x8,
         kId     = 3
      };
      tAI_FIFO_Data_Register16();


      typedef enum {
         kRegisterId                          = 0,
         kAI_FIFO_Data16Id                 = 1,
         kMaxFieldId                          = 1
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Register Accessors (Compile-time selectable)

      inline u16 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline u16 readAI_FIFO_Data16(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_FIFO_Data_Register16(const tAI_FIFO_Data_Register16&);
      tAI_FIFO_Data_Register16& operator=(const tAI_FIFO_Data_Register16&);

   };

   //---------------------------------------------------------------------------
   // AI_Config_FIFO_Data_Register
   //---------------------------------------------------------------------------
   class tAI_Config_FIFO_Data_Register : public tReg16IODirect32
   {
   public:
      typedef tReg16IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x1e,
         kId     = 4
      };
      tAI_Config_FIFO_Data_Register();


      typedef enum {
         kRegisterId                          = 0,
         kAI_Config_ChannelId              = 1,
         kAI_Config_BankId                 = 2,
         kAI_Config_Channel_TypeId         = 3,
         kAI_Config_GainId                 = 4,
         kAI_Config_DitherId               = 6,
         kAI_Config_Last_ChannelId         = 7,
         kMaxFieldId                          = 7
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Dirty Tracking
      inline tBoolean isDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markClean(nMDBG::tStatus2* statusChain = NULL);

      // Register Accessors (Compile-time selectable)
      inline tAI_Config_FIFO_Data_Register& setRegister(u16 value, nMDBG::tStatus2* statusChain = NULL);
      inline u16 getRegister(nMDBG::tStatus2* statusChain = NULL) const;

      inline void flush(nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline void writeRegister(u16 value, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline u16 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline tAI_Config_FIFO_Data_Register& setAI_Config_Channel(u16 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u16 getAI_Config_Channel(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_Config_Channel(u16 fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline u16 readAI_Config_Channel(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Config_FIFO_Data_Register& setAI_Config_Bank(nAI::tAI_Config_Bank_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Config_Bank_t getAI_Config_Bank(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_Config_Bank(nAI::tAI_Config_Bank_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline nAI::tAI_Config_Bank_t readAI_Config_Bank(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Config_FIFO_Data_Register& setAI_Config_Channel_Type(nAI::tAI_Config_Channel_Type_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Config_Channel_Type_t getAI_Config_Channel_Type(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_Config_Channel_Type(nAI::tAI_Config_Channel_Type_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline nAI::tAI_Config_Channel_Type_t readAI_Config_Channel_Type(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Config_FIFO_Data_Register& setAI_Config_Gain(u16 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u16 getAI_Config_Gain(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_Config_Gain(u16 fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline u16 readAI_Config_Gain(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Config_FIFO_Data_Register& setAI_Config_Dither(nAI::tAI_Disabled_Enabled_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Disabled_Enabled_t getAI_Config_Dither(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_Config_Dither(nAI::tAI_Disabled_Enabled_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline nAI::tAI_Disabled_Enabled_t readAI_Config_Dither(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Config_FIFO_Data_Register& setAI_Config_Last_Channel(u16 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u16 getAI_Config_Last_Channel(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_Config_Last_Channel(u16 fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kTrue);

      inline u16 readAI_Config_Last_Channel(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      u16 _softCopy;

      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_Config_FIFO_Data_Register(const tAI_Config_FIFO_Data_Register&);
      tAI_Config_FIFO_Data_Register& operator=(const tAI_Config_FIFO_Data_Register&);

   };

   //---------------------------------------------------------------------------
   // AI_Data_Mode_Register
   //---------------------------------------------------------------------------
   class tAI_Data_Mode_Register : public tReg32IODirect32
   {
   public:
      typedef tReg32IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x28,
         kId     = 5
      };
      tAI_Data_Mode_Register();


      typedef enum {
         kRegisterId                          = 0,
         kAI_DoneNotificationEnableId      = 3,
         kAI_FifoWidthId                   = 4,
         kMaxFieldId                          = 4
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Dirty Tracking
      inline tBoolean isDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markClean(nMDBG::tStatus2* statusChain = NULL);

      // Register Accessors (Compile-time selectable)
      inline tAI_Data_Mode_Register& setRegister(u32 value, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getRegister(nMDBG::tStatus2* statusChain = NULL) const;

      inline void flush(nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline void writeRegister(u32 value, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline u32 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline tAI_Data_Mode_Register& setAI_DoneNotificationEnable(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getAI_DoneNotificationEnable(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_DoneNotificationEnable(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline u32 readAI_DoneNotificationEnable(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Data_Mode_Register& setAI_FifoWidth(nAI::tAI_FifoWidth_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_FifoWidth_t getAI_FifoWidth(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_FifoWidth(nAI::tAI_FifoWidth_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_FifoWidth_t readAI_FifoWidth(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      u32 _softCopy;

      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_Data_Mode_Register(const tAI_Data_Mode_Register&);
      tAI_Data_Mode_Register& operator=(const tAI_Data_Mode_Register&);

   };

   //---------------------------------------------------------------------------
   // AI_Trigger_Select_Register
   //---------------------------------------------------------------------------
   class tAI_Trigger_Select_Register : public tReg32IODirect32
   {
   public:
      typedef tReg32IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x2c,
         kId     = 6
      };
      tAI_Trigger_Select_Register();


      typedef enum {
         kRegisterId                          = 0,
         kAI_START1_SelectId               = 1,
         kAI_START1_EdgeId                 = 2,
         kAI_START1_PolarityId             = 3,
         kAI_START2_SelectId               = 4,
         kAI_START2_EdgeId                 = 5,
         kAI_START2_PolarityId             = 6,
         kAI_External_Gate_SelectId        = 7,
         kAI_External_Gate_PolarityId      = 9,
         kAI_CONVERT_Source_SelectId       = 10,
         kAI_Convert_Source_PolarityId     = 12,
         kMaxFieldId                          = 12
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Dirty Tracking
      inline tBoolean isDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markClean(nMDBG::tStatus2* statusChain = NULL);

      // Register Accessors (Compile-time selectable)
      inline tAI_Trigger_Select_Register& setRegister(u32 value, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getRegister(nMDBG::tStatus2* statusChain = NULL) const;

      inline void flush(nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline void writeRegister(u32 value, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline u32 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline tAI_Trigger_Select_Register& setAI_START1_Select(nAI::tAI_START1_Select_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_START1_Select_t getAI_START1_Select(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START1_Select(nAI::tAI_START1_Select_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_START1_Select_t readAI_START1_Select(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_START1_Edge(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getAI_START1_Edge(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START1_Edge(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline u32 readAI_START1_Edge(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_START1_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Polarity_t getAI_START1_Polarity(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START1_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_Polarity_t readAI_START1_Polarity(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_START2_Select(nAI::tAI_START2_Select_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_START2_Select_t getAI_START2_Select(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START2_Select(nAI::tAI_START2_Select_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_START2_Select_t readAI_START2_Select(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_START2_Edge(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getAI_START2_Edge(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START2_Edge(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline u32 readAI_START2_Edge(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_START2_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Polarity_t getAI_START2_Polarity(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START2_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_Polarity_t readAI_START2_Polarity(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_External_Gate_Select(nAI::tAI_External_Gate_Select_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_External_Gate_Select_t getAI_External_Gate_Select(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_External_Gate_Select(nAI::tAI_External_Gate_Select_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_External_Gate_Select_t readAI_External_Gate_Select(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_External_Gate_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Polarity_t getAI_External_Gate_Polarity(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_External_Gate_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_Polarity_t readAI_External_Gate_Polarity(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_CONVERT_Source_Select(nAI::tAI_StartConvertSelMux_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_StartConvertSelMux_t getAI_CONVERT_Source_Select(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_CONVERT_Source_Select(nAI::tAI_StartConvertSelMux_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_StartConvertSelMux_t readAI_CONVERT_Source_Select(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register& setAI_Convert_Source_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Polarity_t getAI_Convert_Source_Polarity(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_Convert_Source_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_Polarity_t readAI_Convert_Source_Polarity(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      u32 _softCopy;

      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_Trigger_Select_Register(const tAI_Trigger_Select_Register&);
      tAI_Trigger_Select_Register& operator=(const tAI_Trigger_Select_Register&);

   };

   //---------------------------------------------------------------------------
   // AI_Trigger_Select_Register2
   //---------------------------------------------------------------------------
   class tAI_Trigger_Select_Register2 : public tReg32IODirect32
   {
   public:
      typedef tReg32IODirect32 tIOStrategy;
      typedef tAI tRegisterMap;

      enum {
         kOffset = 0x30,
         kId     = 7
      };
      tAI_Trigger_Select_Register2();


      typedef enum {
         kRegisterId                          = 0,
         kAI_START_SelectId                = 2,
         kAI_START_EdgeId                  = 3,
         kAI_START_PolarityId              = 4,
         kMaxFieldId                          = 4
      } tId;

      inline tRegisterMap* registerMap(void);
      inline void setRegisterMap(tRegisterMap* pRegMap);


      // Dirty Tracking
      inline tBoolean isDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markDirty(nMDBG::tStatus2* statusChain = NULL);
      inline void markClean(nMDBG::tStatus2* statusChain = NULL);

      // Register Accessors (Compile-time selectable)
      inline tAI_Trigger_Select_Register2& setRegister(u32 value, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getRegister(nMDBG::tStatus2* statusChain = NULL) const;

      inline void flush(nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline void writeRegister(u32 value, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline u32 readRegister(nMDBG::tStatus2* statusChain = NULL);

      // Field Accessors (Compile-time selectable)
      inline tAI_Trigger_Select_Register2& setAI_START_Select(nAI::tAI_StartConvertSelMux_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_StartConvertSelMux_t getAI_START_Select(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START_Select(nAI::tAI_StartConvertSelMux_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_StartConvertSelMux_t readAI_START_Select(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register2& setAI_START_Edge(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline u32 getAI_START_Edge(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START_Edge(u32 fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline u32 readAI_START_Edge(nMDBG::tStatus2* statusChain = NULL);

      inline tAI_Trigger_Select_Register2& setAI_START_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL);
      inline nAI::tAI_Polarity_t getAI_START_Polarity(nMDBG::tStatus2* statusChain = NULL) const;

      inline void writeAI_START_Polarity(nAI::tAI_Polarity_t fieldValue, nMDBG::tStatus2* statusChain = NULL, tBoolean force = kFalse);

      inline nAI::tAI_Polarity_t readAI_START_Polarity(nMDBG::tStatus2* statusChain = NULL);

      // Run-time selectable Register/Field Accessors
   private:
      u32 _softCopy;

      tRegisterMap* _regMap;

      // Usage guidelines
      tAI_Trigger_Select_Register2(const tAI_Trigger_Select_Register2&);
      tAI_Trigger_Select_Register2& operator=(const tAI_Trigger_Select_Register2&);

   };

   //---------------------------------------------------------------------------
   // AI_Config_FIFO_Status_Register
   //---------------------------------------------------------------------------
   tAI_Config_FIFO_Status_Register AI_Config_FIFO_Status_Register;

   //---------------------------------------------------------------------------
   // AI_Data_FIFO_Status_Register
   //---------------------------------------------------------------------------
   tAI_Data_FIFO_Status_Register AI_Data_FIFO_Status_Register;

   //---------------------------------------------------------------------------
   // AI_FIFO_Data_Register
   //---------------------------------------------------------------------------
   tAI_FIFO_Data_Register AI_FIFO_Data_Register;

   //---------------------------------------------------------------------------
   // AI_FIFO_Data_Register16
   //---------------------------------------------------------------------------
   tAI_FIFO_Data_Register16 AI_FIFO_Data_Register16;

   //---------------------------------------------------------------------------
   // AI_Config_FIFO_Data_Register
   //---------------------------------------------------------------------------
   tAI_Config_FIFO_Data_Register AI_Config_FIFO_Data_Register;

   //---------------------------------------------------------------------------
   // AI_Data_Mode_Register
   //---------------------------------------------------------------------------
   tAI_Data_Mode_Register AI_Data_Mode_Register;

   //---------------------------------------------------------------------------
   // AI_Trigger_Select_Register
   //---------------------------------------------------------------------------
   tAI_Trigger_Select_Register AI_Trigger_Select_Register;

   //---------------------------------------------------------------------------
   // AI_Trigger_Select_Register2
   //---------------------------------------------------------------------------
   tAI_Trigger_Select_Register2 AI_Trigger_Select_Register2;

   //---------------------------------------------------------------------------
   // Register Groups
   //---------------------------------------------------------------------------

   //----------------------------------------
   // Register/Field Ids
   //----------------------------------------
   typedef enum {
      kAI_Config_FIFO_Status_RegisterId   = 0,
      kAI_Config_FIFO_StatusId          = nNIMXRegisterMap120_mBuildFieldId(tAI_Config_FIFO_Status_Register::kAI_Config_FIFO_StatusId, kAI_Config_FIFO_Status_RegisterId),

      kAI_Data_FIFO_Status_RegisterId   = 1,
      kAI_Data_FIFO_StatusId            = nNIMXRegisterMap120_mBuildFieldId(tAI_Data_FIFO_Status_Register::kAI_Data_FIFO_StatusId, kAI_Data_FIFO_Status_RegisterId),

      kAI_FIFO_Data_RegisterId          = 2,
      kAI_FIFO_DataId                   = nNIMXRegisterMap120_mBuildFieldId(tAI_FIFO_Data_Register::kAI_FIFO_DataId, kAI_FIFO_Data_RegisterId),

      kAI_FIFO_Data_Register16Id        = 3,
      kAI_FIFO_Data16Id                 = nNIMXRegisterMap120_mBuildFieldId(tAI_FIFO_Data_Register16::kAI_FIFO_Data16Id, kAI_FIFO_Data_Register16Id),

      kAI_Config_FIFO_Data_RegisterId   = 4,
      kAI_Config_ChannelId              = nNIMXRegisterMap120_mBuildFieldId(tAI_Config_FIFO_Data_Register::kAI_Config_ChannelId, kAI_Config_FIFO_Data_RegisterId),
      kAI_Config_BankId                 = nNIMXRegisterMap120_mBuildFieldId(tAI_Config_FIFO_Data_Register::kAI_Config_BankId, kAI_Config_FIFO_Data_RegisterId),
      kAI_Config_Channel_TypeId         = nNIMXRegisterMap120_mBuildFieldId(tAI_Config_FIFO_Data_Register::kAI_Config_Channel_TypeId, kAI_Config_FIFO_Data_RegisterId),
      kAI_Config_GainId                 = nNIMXRegisterMap120_mBuildFieldId(tAI_Config_FIFO_Data_Register::kAI_Config_GainId, kAI_Config_FIFO_Data_RegisterId),
      kAI_Config_DitherId               = nNIMXRegisterMap120_mBuildFieldId(tAI_Config_FIFO_Data_Register::kAI_Config_DitherId, kAI_Config_FIFO_Data_RegisterId),
      kAI_Config_Last_ChannelId         = nNIMXRegisterMap120_mBuildFieldId(tAI_Config_FIFO_Data_Register::kAI_Config_Last_ChannelId, kAI_Config_FIFO_Data_RegisterId),

      kAI_Data_Mode_RegisterId          = 5,
      kAI_DoneNotificationEnableId      = nNIMXRegisterMap120_mBuildFieldId(tAI_Data_Mode_Register::kAI_DoneNotificationEnableId, kAI_Data_Mode_RegisterId),
      kAI_FifoWidthId                   = nNIMXRegisterMap120_mBuildFieldId(tAI_Data_Mode_Register::kAI_FifoWidthId, kAI_Data_Mode_RegisterId),

      kAI_Trigger_Select_RegisterId     = 6,
      kAI_START1_SelectId               = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_START1_SelectId, kAI_Trigger_Select_RegisterId),
      kAI_START1_EdgeId                 = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_START1_EdgeId, kAI_Trigger_Select_RegisterId),
      kAI_START1_PolarityId             = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_START1_PolarityId, kAI_Trigger_Select_RegisterId),
      kAI_START2_SelectId               = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_START2_SelectId, kAI_Trigger_Select_RegisterId),
      kAI_START2_EdgeId                 = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_START2_EdgeId, kAI_Trigger_Select_RegisterId),
      kAI_START2_PolarityId             = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_START2_PolarityId, kAI_Trigger_Select_RegisterId),
      kAI_External_Gate_SelectId        = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_External_Gate_SelectId, kAI_Trigger_Select_RegisterId),
      kAI_External_Gate_PolarityId      = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_External_Gate_PolarityId, kAI_Trigger_Select_RegisterId),
      kAI_CONVERT_Source_SelectId       = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_CONVERT_Source_SelectId, kAI_Trigger_Select_RegisterId),
      kAI_Convert_Source_PolarityId     = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register::kAI_Convert_Source_PolarityId, kAI_Trigger_Select_RegisterId),

      kAI_Trigger_Select_Register2Id    = 7,
      kAI_START_SelectId                = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register2::kAI_START_SelectId, kAI_Trigger_Select_Register2Id),
      kAI_START_EdgeId                  = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register2::kAI_START_EdgeId, kAI_Trigger_Select_Register2Id),
      kAI_START_PolarityId              = nNIMXRegisterMap120_mBuildFieldId(tAI_Trigger_Select_Register2::kAI_START_PolarityId, kAI_Trigger_Select_Register2Id),


      kMaxRegisterId = 7

   } tId;

   tAI(tBusSpaceReference addrSpace, nMDBG::tStatus2* statusChain = NULL);
   tAI();
   void initialize(tBusSpaceReference addrSpace, u32 addressOffset, nMDBG::tStatus2* statusChain = NULL);
   void reset(nMDBG::tStatus2* statusChain = NULL);
   virtual ~tAI();

   inline tBusSpaceReference getBusSpaceReference(void) const;

   inline void setAddressOffset(u32 value, nMDBG::tStatus2* statusChain = NULL);
   inline u32  getAddressOffset(nMDBG::tStatus2* statusChain = NULL);
   inline tBoolean isDirty(tId id, nMDBG::tStatus2* statusChain = NULL);
   inline void markDirty(tId id, nMDBG::tStatus2* statusChain = NULL);
   inline void markClean(tId id, nMDBG::tStatus2* statusChain = NULL);

   inline void markDirty(nMDBG::tStatus2* statusChain = NULL);
   inline void markClean(nMDBG::tStatus2* statusChain = NULL);

private:
   void _initialize(nMDBG::tStatus2* statusChain = NULL);
   tBusSpaceReference _addrSpace;
   u32 _addressOffset;
   u8 _dirtyVector[8];

};

#ifndef ___tAI_ipp___
#ifndef ___tAI_h_no_inline___
#include "tAI.ipp"
#endif

#endif

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

