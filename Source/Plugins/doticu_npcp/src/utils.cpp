/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameForms.h"

#include "utils.h"
#include "string2.h"
#include "form.h"
#include "object_ref.h"
#include "quest.h"

namespace doticu_npcp { namespace Utils {

    void Print(const char *str) {
        Console_Print(str);
    }

    void CRC32_By_Size(UInt32& result, void* value, UInt32 size)
    {
        static auto crc32_by_size = reinterpret_cast
            <void (*)(UInt32&, void*, UInt32)>
            (RelocationManager::s_baseAddr + Offsets::CRC32::BY_SIZE);
        crc32_by_size(result, value, size);
    }

    void CRC32_By_32(UInt32& result, UInt32 value)
    {
        static auto crc32_by_32 = reinterpret_cast
            <void (*)(UInt32&, UInt32)>
            (RelocationManager::s_baseAddr + Offsets::CRC32::BY_32);
        crc32_by_32(result, value);
    }

    void CRC32_By_64(UInt32& result, UInt64 value)
    {
        static auto crc32_by_64 = reinterpret_cast
            <void (*)(UInt32&, UInt64)>
            (RelocationManager::s_baseAddr + Offsets::CRC32::BY_64);
        crc32_by_64(result, value);
    }

}}

namespace doticu_npcp { namespace Utils { namespace Exports {

    void Print(StaticFunctionTag *, BSFixedString str) {
        Console_Print(str.data);
    }

    using Int_Vector_t = Papyrus::Int_Vector_t;

    Int_Vector_t New_Int_Array(Selfless_t*, Int_t size = 0, Int_t fill = 0)
    {
        Int_Vector_t vec;

        vec.reserve(size);
        for (Int_t idx = 0; idx < size; idx += 1) {
            vec.push_back(fill);
        }

        return vec;
    }

    bool Register(VMClassRegistry *registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("New_Int_Array", 2, Int_Vector_t, New_Int_Array, Int_t, Int_t);

        #undef ADD_GLOBAL

        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, BSFixedString>(
                "Print",
                "doticu_npcp",
                Exports::Print,
                registry)
        );

        return true;
    }

}}}
