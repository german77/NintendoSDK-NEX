#include "Platform/Core/StringStream.h"

#include <cstring>
#include <stdio.h>

namespace nn::nex {
StringStream::StringStream() : mBegin(&mBuffer[0]), mEnd(&mBuffer[0]) {
    mBuffer[0] = '\0';
    mIsDecimalFormat = false;
    mIsBaseRequired = true;
    _122 = true;
}

StringStream::~StringStream() {
    FreeBuffer();
}

void StringStream::FreeBuffer() {
    FreeBuffer(mBegin);
}

u64 StringStream::GetLength() const {
    return mEnd - mBegin;
}

void StringStream::Clear() {
    FreeBuffer();
    mBegin = &mBuffer[0];
    mCapacity = 0x100;
    mEnd = &mBuffer[0];
    mBuffer[0] = '\0';
}

void StringStream::FreeBuffer(char* buffer) {
    if (mBuffer == buffer)
        return;
    RootObject::operator delete[](buffer - 0x4);  // Include size bytes
}

void StringStream::ResizeBuffer(u64 size) {
    u64 prevLength = GetLength();
    char* prevBegin = mBegin;

    char* txt = (char*)RootObject::operator new[](size + 0x4);  // Account for size bytes

    *(u32*)txt = size;
    mBegin = txt + 4;
    mCapacity = size;
    memcpy(mBegin, prevBegin, prevLength + 1);
    mEnd = mBegin + prevLength;

    FreeBuffer(prevBegin);
}

__attribute__((noinline)) void StringStream::TestFreeRoom(u64 size) {
    if (GetLength() + size <= mCapacity)
        return;

    u64 newCapacity = mCapacity;
    while (newCapacity < GetLength() + size)
        newCapacity += newCapacity / 2;

    ResizeBuffer(newCapacity);
}

void StringStream::StreamNumber(u8 value) {
    TestFreeRoom(0x20);

    const char* format = "%x";
    if (!mIsDecimalFormat) {
        format = "%u";
    } else {
        if (mIsBaseRequired)
            AddBaseIfRequired();

        if (mIsByteFormat)
            format = "%02x";
    }

    mEnd += snprintf(mEnd, 0x20, format, value);
}

__attribute__((noinline)) void strcat(char* dst, const char* src) {
    std::strcat(dst, src);
}

void StringStream::AddBaseIfRequired() {
    if (mIsBaseRequired) {
        const char* base = "0x";
        strcat(mEnd, base);
        mEnd = mEnd + 2;
    }
}

void StringStream::StreamNumber(u32 value) {
    TestFreeRoom(0x20);

    const char* format = "%x";
    if (!mIsDecimalFormat) {
        format = "%u";
    } else {
        if (mIsBaseRequired)
            AddBaseIfRequired();

        if (mIsByteFormat)
            format = "%02x";
    }

    mEnd += snprintf(mEnd, 0x20, format, value);
}

void StringStream::StreamNumber(s32 value) {
    TestFreeRoom(0x20);

    const char* format = "%x";
    if (!mIsDecimalFormat) {
        format = "%u";
    } else {
        if (mIsBaseRequired)
            AddBaseIfRequired();

        if (mIsByteFormat)
            format = "%02x";
    }

    mEnd += snprintf(mEnd, 0x20, format, value);
}

StringStream& StringStream::operator<<(const char* str) {
    if (str == nullptr)
        str = "(null)";

    u64 length = strlen(str);
    TestFreeRoom(length + 1);
    strcpy(mEnd, str);
    mEnd += length;
    return *this;
}

StringStream& StringStream::operator<<(const StringStream& stream) {
    return operator<<(stream.Begin());
}

StringStream& StringStream::operator<<(bool value) {}

StringStream& StringStream::operator<<(f64 value) {
    TestFreeRoom(0x20);
    mEnd += snprintf(mEnd, 0x20, "%f", value);
    return *this;
}

StringStream& StringStream::operator<<(f32 value) {
    TestFreeRoom(0x20);
    mEnd += snprintf(mEnd, 0x20, "%f", value);
    return *this;
}

StringStream& StringStream::operator<<(const void* buffer) {}

StringStream& StringStream::operator<<(u64 value) {}

StringStream& StringStream::operator<<(s64 value) {}

StringStream& StringStream::BytesDump(const u8* src, u64 size) {
    mIsByteFormat = true;
    mIsDecimalFormat = false;
    mIsBaseRequired = true;
    for (u64 i = 0; i < size; i++, src++)
        StreamNumber(*src);
    return *this;
}

StringStream& StringStream::BytesAsciiDump(const u8* src, u64 size) {
    for (u64 i = 0; i < size; i++, src++) {
        TestFreeRoom(0x20);

        u64 bytes;
        if (*src - 32u < 95u)  // Is an ASCII printable
            bytes = snprintf(mEnd, 0x20, "%c", *src);
        else
            bytes = snprintf(mEnd, 0x20, ".");

        mEnd += bytes;
    }
    return *this;
}

}  // namespace nn::nex
