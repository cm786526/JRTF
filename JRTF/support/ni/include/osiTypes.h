/*
 * osiTypes.h
 *   Defines the constants and macros needed for ChipObjects and the iBus
 *
 * Copyright 2011 National Instruments
 * License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
 *   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.
 *
 */

#ifndef ___osiTypes_h___
#define ___osiTypes_h___
#define kLittleEndian 1
#define kGNU 1
// Note: these different typedef's may be different
// depending on you system. On a 32 bit processor with a 32 bit
// OS, these will probably not need to be modified.
typedef signed char     i8;
typedef unsigned char   u8;
typedef short           i16;
typedef unsigned short  u16;
typedef signed int      i32;
typedef unsigned int    u32;
typedef float           f32;
typedef double          f64;
typedef char            tText;
typedef char            tChar;
typedef i32             tStatus;
typedef u32             tBoolean;
enum { kFalse = 0, kTrue = 1};

//
// Set to match the target endianness of the target platform
//
inline u32 SwitchEndianU32(u32 x)
{
   volatile u32 rval;
   u8  *tmpPtr;
   rval = x;
   tmpPtr = (u8 *)(&rval);
   tmpPtr[0] ^= tmpPtr[3];
   tmpPtr[3] ^= tmpPtr[0];
   tmpPtr[0] ^= tmpPtr[3];
   tmpPtr[1] ^= tmpPtr[2];
   tmpPtr[2] ^= tmpPtr[1];
   tmpPtr[1] ^= tmpPtr[2];
   return rval;
}

inline u16 SwitchEndianU16(u16 x)
{
   volatile u16 rval;
   u8  *tmpPtr;

   rval = x;
   tmpPtr = (u8 *)(&rval);

   tmpPtr[0] ^= tmpPtr[1];
   tmpPtr[1] ^= tmpPtr[0];
   tmpPtr[0] ^= tmpPtr[1];

   return rval;
}

//
// kLittleEndian=1 or kBigEndian=1 is defined in the
// OS specific makefile or project
//
#if kLittleEndian

   #define ReadLittleEndianU32(x) (x)
   #define ReadLittleEndianU16(x) (x)

   #define ReadBigEndianU32(x) (SwitchEndianU32(x))
   #define ReadBigEndianU16(x) (SwitchEndianU16(x))

#elif kBigEndian

   #define ReadLittleEndianU32(x) (SwitchEndianU32(x))
   #define ReadLittleEndianU16(x) (SwitchEndianU16(x))

   #define ReadBigEndianU32(x) (x)
   #define ReadBigEndianU16(x) (x)

#else

   //
   // In your build project define
   //    kLittleEndian=1
   // or
   //    kBigEndian=1
   // to specify your platform's endianness
   //

   #error target endianness not specified
#endif

#if kMicrosoft

   typedef unsigned __int64      u64;
   typedef __int64               i64;

   #define nOSINT100_mI64bitLiteral(x) (x)
   #define nOSINT100_mU64bitLiteral(x) (x)

   #define nOSINT100_kCCall      __cdecl
   #define nOSINT100_kStdCall    __stdcall

#elif kApple || kGNU

   typedef unsigned long long    u64;
   typedef long long             i64;

   #define nOSINT100_mI64bitLiteral(x) (x##LL)
   #define nOSINT100_mU64bitLiteral(x) (x##ULL)

   #define nOSINT100_kCCall
   #define nOSINT100_kStdCall

#else

   //
   // In your build project define
   //    kMicrosoft=1
   // or
   //    kApple=1 or kGNU=1
   // to specify your platform type
   //

    #error platform not specified; see osiTypes.h
#endif

#ifndef ___nimdbg_tStatus2_h___
#define ___nimdbg_tStatus2_h___
inline tBoolean statusIsFatal(tStatus status)      {return (status < 0);}
inline tBoolean statusIsNonfatal(tStatus status)   {return (status >= 0);}
inline tStatus statusForceFatal(tStatus status)    {return ((status<=0)?status:-status);}
inline tStatus statusForceNonfatal(tStatus status) {return ((status>=0)?status:-status);}
inline tStatus statusSetStatus(tStatus currentStatus, tStatus newStatus)
{
   if (currentStatus < 0)
      return currentStatus;
   else if (currentStatus == 0)
      return newStatus;
   else if (newStatus < 0)
      return newStatus;
   else return currentStatus;
}

#define  kStatusOffset                    -50000
#define  kStatusSuccess                   0
#define  kStatusBadParameter              (-15  + kStatusOffset)
#define  kStatusBadWindowType             (-16  + kStatusOffset)
#define  kStatusBadWriteMode              (-17  + kStatusOffset)
#define  kStatusBadReadMode               (-18  + kStatusOffset)
#define  kStatusBadDataSize               (-19  + kStatusOffset)
#define  kStatusBadSelector               (-20  + kStatusOffset)
#define  kStatusBadCHInCh                 (-21  + kStatusOffset)
#define  kStatusBadInterval               (-22  + kStatusOffset)
#define  kStatusUnknownDevice             (-23  + kStatusOffset)
#define  kStatusWrongState                (-24  + kStatusOffset)
#define  kStatusRLPTimeout                (-25  + kStatusOffset)
#define  kStatusUnknownCHInCh             (-26  + kStatusOffset)
#define  kStatusUnknownSTC3               (-27  + kStatusOffset)
#define  kStatusRuntimeError              (-28  + kStatusOffset)

namespace nMDBG{
   class tStatus2
   {
   public:
      tStatus2() : statusCode(kStatusSuccess) {};
      i32 statusCode;
      i32 isFatal() const {return statusIsFatal(statusCode);};
      i32 isNotFatal() const {return !isFatal();};
      void setCode(int code){ statusCode = statusSetStatus(statusCode, code);}
      operator i32*() {return &statusCode;};

      operator i32&() {return statusCode;};

   };
};
#endif

#define  nNIOSINT100_mUnused(x)           nNIOSINT100_mUnused_func((const void *)&x)
inline void nNIOSINT100_mUnused_func(const void *) {}

#ifndef NULL
 #define  NULL 0
#endif

#endif // ___osiTypes_h___
