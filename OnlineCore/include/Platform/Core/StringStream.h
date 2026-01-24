#pragma once

#include "Platform/Core/RootObject.h"

namespace nn::nex {

class StringStream : public RootObject {
public:
    StringStream();
    virtual ~StringStream();

    void FreeBuffer();
    u64 GetLength() const;
    void Clear();
    void FreeBuffer(char*);
    void ResizeBuffer(u64);
    void TestFreeRoom(u64);
    void StreamNumber(u8);
    void AddBaseIfRequired();
    void StreamNumber(u32);
    void StreamNumber(s32);
    StringStream& operator<<(const char*);
    StringStream& operator<<(const StringStream&);
    StringStream& operator<<(bool);
    StringStream& operator<<(f64);
    StringStream& operator<<(f32);
    StringStream& operator<<(const void*);
    StringStream& operator<<(u64);
    StringStream& operator<<(s64);
    StringStream& BytesDump(const u8*, u64);
    StringStream& BytesAsciiDump(const u8*, u64);

    char* Begin() const { return mBegin; }

    char* End() const { return mEnd; }

private:
    char* mBegin;
    u64 mCapacity = 0x100;
    char* mEnd;
    char mBuffer[0x100];
    bool mIsDecimalFormat;
    bool mIsBaseRequired;
    bool _122;
    bool mIsByteFormat;
};
}  // namespace nn::nex
