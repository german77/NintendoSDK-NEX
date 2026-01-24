#include "Platform/Core/String.h"
#include "Platform/Core/MemoryManager.h"

#include <cstring>

namespace nn::nex {

template <typename T>
void* SpecialNewArray(u32 a1, T* ptr, u32 a3) {
    void* mem = MemoryManager::Allocate(sizeof(ptr));
    return (void*)((int*)(mem) + 1);
}

template <typename T, T>
void StrCopy(T* str, const T* copyStr, u64 unk) {
    if (str) {
    }
}

String::String(String::NoAllocTag) {
    m_String = nullptr;
}

String::String(const char* str) {
    if (str)
        strlen(str);
    else
        str = nullptr;
}

// void String::Truncate(u64) const;
u64 String::GetLength() const {
    if (!m_String)
        return 0;

    return strlen(m_String);
}

// void String::Reserve(u64);
// void String::SetBufferPtr(char*);
// void String::SetStringToPreReservedBuffer(const char*);
// void String::GetWideCharLength() const;
void String::CopyString(char*, u64) const {}

// void String::CreateCopy(wchar_t**) const;
// void String::ReleaseCopy(wchar_t*);
// void String::CopyString(wchar_t*, u64) const;
// void String::CreateCopy(char16_t**) const;
// void String::ReleaseCopy(char16_t*);
// void String::CopyString(char16_t*, u64) const;
// void String::ToUpper();
// void String::ToLower();
// void String::FindSubstringCase(const char*, s32) const;
// void String::FindSubstringNoCase(const char*) const;
// void String::ByteArrayToBase64(const unsigned char*, u64, char*, u64);
// void String::Base64ToByteArray(const char*, u64, u8*, u64);
// void String::Base64ToByteArray(const String&, u8*, u64);
// void ContainsCase(const String&) const;
// void String::ToUInt64() const;

bool String::ContainsNoCase(const String& str) const {
    return FindSubstringNoCase(str.cstr()) != -1;
}

void String::SetDefaultStringEncoding(u32 encoding) {
    s_uiDefaultStringEncoding = encoding;
}

void String::Trace(u64) {}

}  // namespace nn::nex
