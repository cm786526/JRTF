// Copyright 2011 National Instruments
// License: NATIONAL INSTRUMENTS SOFTWARE LICENSE AGREEMENT
//   Refer to "MHDDK License Agreement.pdf" in the root of this distribution.

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#ifndef ___tStreamCircuitRegMap_ipp___
#define ___tStreamCircuitRegMap_ipp___

#ifndef ___tStreamCircuitRegMap_h___
#include "tStreamCircuitRegMap.h"
#endif

#ifndef ___nNIMXRegistermap_tStatus2Ptr_ipp___
#define ___nNIMXRegistermap_tStatus2Ptr_ipp___

typedef nMDBG::tStatus2 nNIMXRegisterMap120_tStatus2;


namespace nNIMXRegisterMap120 {
namespace {

typedef nNIMXRegisterMap120_tStatus2 tStatus2;

inline void setStatus(tStatus2* s, tStatus newStatus)
{
   if (s) s->setCode(newStatus);
}

inline tStatus* toPALStatusPtr(tStatus2* s)
{
   return s ? s->operator tStatus*() : ((tStatus*)NULL);
}

inline tBoolean statusIsFatal(tStatus2* s)
{
   return s && s->isFatal();
}

} // unnamed namespace
} // namespace nNIMXRegisterMap120

#endif // ___nNIMXRegistermap_tStatus2Ptr_ipp___


inline void tStreamCircuitRegMap::tReg32IODirect32::write(
   tBusSpaceReference addrSpace,
   u32 offset,
   u32 value,
   nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   addrSpace.write32(offset, value);
}

inline u32 tStreamCircuitRegMap::tReg32IODirect32::read(
   tBusSpaceReference addrSpace,
   u32 offset,
   nMDBG::tStatus2* s)
{
   u32 value = (u32)~0;
   if (s && s->isFatal()) return value;
   value = addrSpace.read32(offset);
   return value;
}

inline tBusSpaceReference tStreamCircuitRegMap::getBusSpaceReference(void) const
{
   return _addrSpace;
}

inline void tStreamCircuitRegMap::setAddressOffset(u32 value, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   _addressOffset = value;
}
inline u32 tStreamCircuitRegMap::getAddressOffset(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return 0UL;
   return _addressOffset;
}
inline tBoolean tStreamCircuitRegMap::isDirty(tId id, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return kFalse;
   u32 regId = id&0x01FFFFFF;
   if (regId > kMaxRegisterId) {
      nNIMXRegisterMap120::setStatus(s, kStatusBadSelector);
      return kFalse;
   }

   return _dirtyVector[regId];
}

inline void tStreamCircuitRegMap::markDirty(tId id, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   u32 regId = id&0x01FFFFFF;

   if (regId > kMaxRegisterId) {
      nNIMXRegisterMap120::setStatus(s, kStatusBadSelector);
      return;
   }

   _dirtyVector[regId] = 1;
}

inline void tStreamCircuitRegMap::markClean(tId id, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   u32 regId = id&0x01FFFFFF;

   if (regId > kMaxRegisterId) {
      nNIMXRegisterMap120::setStatus(s, kStatusBadSelector);
      return;
   }

   _dirtyVector[regId] = 0;
}

inline void tStreamCircuitRegMap::markDirty(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   unsigned int i;
   for (i = 0; i < sizeof(_dirtyVector)/sizeof(_dirtyVector[0]); i++) {
      _dirtyVector[i] = 1;
   }
}

inline void tStreamCircuitRegMap::markClean(nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   for (unsigned int i = 0; i < sizeof(_dirtyVector)/sizeof(_dirtyVector[0]); i++) {
      _dirtyVector[i] = 0;
   }
}

inline tStreamCircuitRegMap::tStreamControlStatusReg::tStreamControlStatusReg()
{
}

inline tStreamCircuitRegMap::tStreamControlStatusReg::tRegisterMap* tStreamCircuitRegMap::tStreamControlStatusReg::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), fieldValue, s);
}

inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readRegister(nMDBG::tStatus2* s)
{
   u32 fieldValue;
   fieldValue = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
   return fieldValue;
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeCISTCR_Enable(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x0) & ~0xfffffffe,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readCISTCR_Enable(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffffffe) >> 0x0);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeCISTCR_Disable(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x1) & ~0xfffffffd,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readCISTCR_Disable(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffffffd) >> 0x1);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeCISTCR_Clear(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x2) & ~0xfffffffb,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readCISTCR_Clear(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffffffb) >> 0x2);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeCISATCR_AccessIgnored(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x3) & ~0xfffffff7,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readCISATCR_AccessIgnored(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffffff7) >> 0x3);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeDataTransferEnable(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x8) & ~0xfffffeff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readDataTransferEnable(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffffeff) >> 0x8);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeStreamCircuitReset(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x9) & ~0xfffffdff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readStreamCircuitReset(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffffdff) >> 0x9);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeStreamCircuitResetComplete(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0xa) & ~0xfffffbff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readStreamCircuitResetComplete(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffffbff) >> 0xa);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeStreamCircuitResetNotify(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0xb) & ~0xfffff7ff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readStreamCircuitResetNotify(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffff7ff) >> 0xb);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeDoneFlagSet(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0xd) & ~0xffffdfff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readDoneFlagSet(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xffffdfff) >> 0xd);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeInvalidPacketFlag(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0xe) & ~0xffffbfff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readInvalidPacketFlag(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xffffbfff) >> 0xe);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeInvalidPacketClear(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0xf) & ~0xffff7fff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readInvalidPacketClear(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xffff7fff) >> 0xf);
}

inline void tStreamCircuitRegMap::tStreamControlStatusReg::writeFifoEmpty(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x12) & ~0xfffbffff,s);
}
inline u32 tStreamCircuitRegMap::tStreamControlStatusReg::readFifoEmpty(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0xfffbffff) >> 0x12);
}

inline tStreamCircuitRegMap::tStreamAdditiveTransferCountReg::tStreamAdditiveTransferCountReg()
{
}

inline tStreamCircuitRegMap::tStreamAdditiveTransferCountReg::tRegisterMap* tStreamCircuitRegMap::tStreamAdditiveTransferCountReg::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tStreamAdditiveTransferCountReg::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline void tStreamCircuitRegMap::tStreamAdditiveTransferCountReg::writeRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return;
   tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), fieldValue, s);
}

inline void tStreamCircuitRegMap::tStreamAdditiveTransferCountReg::writeStreamAdditiveTransferCount(u32 fieldValue, nMDBG::tStatus2* s)
{
   writeRegister((u32(fieldValue) << 0x0) & ~0x0,s);
}
inline tStreamCircuitRegMap::tStreamTransferCountReg::tStreamTransferCountReg()
{
}

inline tStreamCircuitRegMap::tStreamTransferCountReg::tRegisterMap* tStreamCircuitRegMap::tStreamTransferCountReg::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tStreamTransferCountReg::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline u32 tStreamCircuitRegMap::tStreamTransferCountReg::readRegister(nMDBG::tStatus2* s)
{
   u32 fieldValue;
   fieldValue = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
   return fieldValue;
}

inline u32 tStreamCircuitRegMap::tStreamTransferCountReg::readStreamTransferCount(nMDBG::tStatus2* s)
{
   u32 value = readRegister(s);
   return u32((value & ~0x0) >> 0x0);
}

inline tStreamCircuitRegMap::tStreamFifoSizeReg::tStreamFifoSizeReg()
{
   _softCopy = u32(0x0);
}

inline tStreamCircuitRegMap::tStreamFifoSizeReg::tRegisterMap* tStreamCircuitRegMap::tStreamFifoSizeReg::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tStreamFifoSizeReg::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tStreamCircuitRegMap::tStreamFifoSizeReg& tStreamCircuitRegMap::tStreamFifoSizeReg::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   _softCopy = fieldValue;
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamFifoSizeReg::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tStreamCircuitRegMap::tStreamFifoSizeReg::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tStreamCircuitRegMap::tStreamFifoSizeReg::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tStreamCircuitRegMap::tStreamFifoSizeReg& tStreamCircuitRegMap::tStreamFifoSizeReg::setStreamFifoSize(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0x0) | ((u32(fieldValue) << 0x0) & ~0x0);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamFifoSizeReg::getStreamFifoSize(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0x0) >> 0x0);
}

inline u32 tStreamCircuitRegMap::tStreamFifoSizeReg::readStreamFifoSize(nMDBG::tStatus2* s)
{
   refresh(s);
   return getStreamFifoSize(s);
}

inline tStreamCircuitRegMap::tStreamTransferLimitReg::tStreamTransferLimitReg()
{
   _softCopy = u32(0x0);
}

inline tStreamCircuitRegMap::tStreamTransferLimitReg::tRegisterMap* tStreamCircuitRegMap::tStreamTransferLimitReg::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tBoolean tStreamCircuitRegMap::tStreamTransferLimitReg::isDirty(nMDBG::tStatus2* s)
{
   return _regMap->isDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::markDirty(nMDBG::tStatus2* s)
{
   _regMap->markDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::markClean(nMDBG::tStatus2* s)
{
   _regMap->markClean((tStreamCircuitRegMap::tId)kId, s);
}

inline tStreamCircuitRegMap::tStreamTransferLimitReg& tStreamCircuitRegMap::tStreamTransferLimitReg::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   if (_softCopy != fieldValue) {
      _softCopy = fieldValue;
      markDirty(s);
   }
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamTransferLimitReg::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::flush(nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   if (force || isDirty(s)) {
      tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), _softCopy, s);
      _softCopy &= u32(0xffffffff);
      _softCopy |= u32(0x0);
      markClean(s);
   }
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::writeRegister(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   force = force || (_softCopy != fieldValue);
   _softCopy = fieldValue;
   flush(s, force);
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tStreamCircuitRegMap::tStreamTransferLimitReg::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tStreamCircuitRegMap::tStreamTransferLimitReg& tStreamCircuitRegMap::tStreamTransferLimitReg::setStreamMinPayloadSize(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xffff0000) | ((u32(fieldValue) << 0x0) & ~0xffff0000);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamTransferLimitReg::getStreamMinPayloadSize(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xffff0000) >> 0x0);
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::writeStreamMinPayloadSize(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setStreamMinPayloadSize(fieldValue, s);
   flush(s, force);
}
inline u32 tStreamCircuitRegMap::tStreamTransferLimitReg::readStreamMinPayloadSize(nMDBG::tStatus2* s)
{
   refresh(s);
   return getStreamMinPayloadSize(s);
}

inline tStreamCircuitRegMap::tStreamTransferLimitReg& tStreamCircuitRegMap::tStreamTransferLimitReg::setStreamMaxPayloadSize(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xffff) | ((u32(fieldValue) << 0x10) & ~0xffff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamTransferLimitReg::getStreamMaxPayloadSize(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xffff) >> 0x10);
}

inline void tStreamCircuitRegMap::tStreamTransferLimitReg::writeStreamMaxPayloadSize(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setStreamMaxPayloadSize(fieldValue, s);
   flush(s, force);
}
inline u32 tStreamCircuitRegMap::tStreamTransferLimitReg::readStreamMaxPayloadSize(nMDBG::tStatus2* s)
{
   refresh(s);
   return getStreamMaxPayloadSize(s);
}

inline tStreamCircuitRegMap::tStreamEvictionReg::tStreamEvictionReg()
{
   _softCopy = u32(0x0);
}

inline tStreamCircuitRegMap::tStreamEvictionReg::tRegisterMap* tStreamCircuitRegMap::tStreamEvictionReg::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tBoolean tStreamCircuitRegMap::tStreamEvictionReg::isDirty(nMDBG::tStatus2* s)
{
   return _regMap->isDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::markDirty(nMDBG::tStatus2* s)
{
   _regMap->markDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::markClean(nMDBG::tStatus2* s)
{
   _regMap->markClean((tStreamCircuitRegMap::tId)kId, s);
}

inline tStreamCircuitRegMap::tStreamEvictionReg& tStreamCircuitRegMap::tStreamEvictionReg::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   if (_softCopy != fieldValue) {
      _softCopy = fieldValue;
      markDirty(s);
   }
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamEvictionReg::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::flush(nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   if (force || isDirty(s)) {
      tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), _softCopy, s);
      _softCopy &= u32(0xffffffff);
      _softCopy |= u32(0x0);
      markClean(s);
   }
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::writeRegister(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   force = force || (_softCopy != fieldValue);
   _softCopy = fieldValue;
   flush(s, force);
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tStreamCircuitRegMap::tStreamEvictionReg::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tStreamCircuitRegMap::tStreamEvictionReg& tStreamCircuitRegMap::tStreamEvictionReg::setEvictionTime(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xfffffc00) | ((u32(fieldValue) << 0x0) & ~0xfffffc00);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamEvictionReg::getEvictionTime(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xfffffc00) >> 0x0);
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::writeEvictionTime(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setEvictionTime(fieldValue, s);
   flush(s, force);
}
inline u32 tStreamCircuitRegMap::tStreamEvictionReg::readEvictionTime(nMDBG::tStatus2* s)
{
   refresh(s);
   return getEvictionTime(s);
}

inline tStreamCircuitRegMap::tStreamEvictionReg& tStreamCircuitRegMap::tStreamEvictionReg::setDisableEviction(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0x7fffffff) | ((u32(fieldValue) << 0x1f) & ~0x7fffffff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamEvictionReg::getDisableEviction(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0x7fffffff) >> 0x1f);
}

inline void tStreamCircuitRegMap::tStreamEvictionReg::writeDisableEviction(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setDisableEviction(fieldValue, s);
   flush(s, force);
}
inline u32 tStreamCircuitRegMap::tStreamEvictionReg::readDisableEviction(nMDBG::tStatus2* s)
{
   refresh(s);
   return getDisableEviction(s);
}

inline tStreamCircuitRegMap::tStreamTransactionLimitReg::tStreamTransactionLimitReg()
{
   _softCopy = u32(0x0);
}

inline tStreamCircuitRegMap::tStreamTransactionLimitReg::tRegisterMap* tStreamCircuitRegMap::tStreamTransactionLimitReg::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tBoolean tStreamCircuitRegMap::tStreamTransactionLimitReg::isDirty(nMDBG::tStatus2* s)
{
   return _regMap->isDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::markDirty(nMDBG::tStatus2* s)
{
   _regMap->markDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::markClean(nMDBG::tStatus2* s)
{
   _regMap->markClean((tStreamCircuitRegMap::tId)kId, s);
}

inline tStreamCircuitRegMap::tStreamTransactionLimitReg& tStreamCircuitRegMap::tStreamTransactionLimitReg::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   if (_softCopy != fieldValue) {
      _softCopy = fieldValue;
      markDirty(s);
   }
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamTransactionLimitReg::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::flush(nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   if (force || isDirty(s)) {
      tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), _softCopy, s);
      _softCopy &= u32(0xffffffff);
      _softCopy |= u32(0x0);
      markClean(s);
   }
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::writeRegister(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   force = force || (_softCopy != fieldValue);
   _softCopy = fieldValue;
   flush(s, force);
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tStreamCircuitRegMap::tStreamTransactionLimitReg::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tStreamCircuitRegMap::tStreamTransactionLimitReg& tStreamCircuitRegMap::tStreamTransactionLimitReg::setTransactionLimit(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xffffff00) | ((u32(fieldValue) << 0x0) & ~0xffffff00);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamTransactionLimitReg::getTransactionLimit(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xffffff00) >> 0x0);
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::writeTransactionLimit(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setTransactionLimit(fieldValue, s);
   flush(s, force);
}
inline u32 tStreamCircuitRegMap::tStreamTransactionLimitReg::readTransactionLimit(nMDBG::tStatus2* s)
{
   refresh(s);
   return getTransactionLimit(s);
}

inline tStreamCircuitRegMap::tStreamTransactionLimitReg& tStreamCircuitRegMap::tStreamTransactionLimitReg::setMaxTransactionLimit(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xffff00ff) | ((u32(fieldValue) << 0x8) & ~0xffff00ff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tStreamTransactionLimitReg::getMaxTransactionLimit(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xffff00ff) >> 0x8);
}

inline void tStreamCircuitRegMap::tStreamTransactionLimitReg::writeMaxTransactionLimit(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setMaxTransactionLimit(fieldValue, s);
   flush(s, force);
}
inline u32 tStreamCircuitRegMap::tStreamTransactionLimitReg::readMaxTransactionLimit(nMDBG::tStatus2* s)
{
   refresh(s);
   return getMaxTransactionLimit(s);
}

inline tStreamCircuitRegMap::tDMAChannel::tDMAChannel(u32 offset, u32 id)
 : kOffset(offset),
   kId(id)
{
   _softCopy = u32(0x0);
}

inline tStreamCircuitRegMap::tDMAChannel::tDMAChannel()
 : kOffset((u32)~0),
   kId((u32)~0)
{
   _softCopy = u32(0x0);
}

inline void tStreamCircuitRegMap::tDMAChannel::initialize(u32 offset, u32 id)
{
   u32* mutableOffset = const_cast<u32*>(&this->kOffset);
   u32* mutableId     = const_cast<u32*>(&this->kId);
   *mutableOffset = offset;
   *mutableId = id;
}

inline tStreamCircuitRegMap::tDMAChannel::tRegisterMap* tStreamCircuitRegMap::tDMAChannel::registerMap(void)
{
   return _regMap;
}

inline void tStreamCircuitRegMap::tDMAChannel::setRegisterMap(tRegisterMap* pRegMap)
{
   _regMap = pRegMap;
}

inline tBoolean tStreamCircuitRegMap::tDMAChannel::isDirty(nMDBG::tStatus2* s)
{
   return _regMap->isDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tDMAChannel::markDirty(nMDBG::tStatus2* s)
{
   _regMap->markDirty((tStreamCircuitRegMap::tId)kId, s);
}

inline void tStreamCircuitRegMap::tDMAChannel::markClean(nMDBG::tStatus2* s)
{
   _regMap->markClean((tStreamCircuitRegMap::tId)kId, s);
}

inline tStreamCircuitRegMap::tDMAChannel& tStreamCircuitRegMap::tDMAChannel::setRegister(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   if (_softCopy != fieldValue) {
      _softCopy = fieldValue;
      markDirty(s);
   }
   return *this;
}

inline u32 tStreamCircuitRegMap::tDMAChannel::getRegister(nMDBG::tStatus2*) const
{
   return _softCopy;
}

inline void tStreamCircuitRegMap::tDMAChannel::flush(nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   if (force || isDirty(s)) {
      tIOStrategy::write(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), _softCopy, s);
      _softCopy &= u32(0xffffffff);
      _softCopy |= u32(0x0);
      markClean(s);
   }
}

inline void tStreamCircuitRegMap::tDMAChannel::writeRegister(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   if (s && s->isFatal()) return;
   force = force || (_softCopy != fieldValue);
   _softCopy = fieldValue;
   flush(s, force);
}

inline void tStreamCircuitRegMap::tDMAChannel::refresh(nMDBG::tStatus2* s)
{
   _softCopy = tIOStrategy::read(_regMap->getBusSpaceReference(), kOffset + _regMap->getAddressOffset(s), s);
}

inline u32 tStreamCircuitRegMap::tDMAChannel::readRegister(nMDBG::tStatus2* s)
{
   refresh(s);
   return _softCopy;
}

inline tStreamCircuitRegMap::tDMAChannel& tStreamCircuitRegMap::tDMAChannel::setDMAChannelNumber(u32 fieldValue, nMDBG::tStatus2* s)
{
   if (s && s->isFatal()) return *this;
   u32 newValue;   newValue = (_softCopy & 0xffc00fff) | ((u32(fieldValue) << 0xc) & ~0xffc00fff);
   setRegister(newValue, s);
   return *this;
}

inline u32 tStreamCircuitRegMap::tDMAChannel::getDMAChannelNumber(nMDBG::tStatus2*) const
{
   return u32((_softCopy & ~0xffc00fff) >> 0xc);
}

inline void tStreamCircuitRegMap::tDMAChannel::writeDMAChannelNumber(u32 fieldValue, nMDBG::tStatus2* s, tBoolean force)
{
   setDMAChannelNumber(fieldValue, s);
   flush(s, force);
}
inline u32 tStreamCircuitRegMap::tDMAChannel::readDMAChannelNumber(nMDBG::tStatus2* s)
{
   refresh(s);
   return getDMAChannelNumber(s);
}

#endif


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is autogenerated!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

