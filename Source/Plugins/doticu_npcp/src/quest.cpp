/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameRTTI.h"

#include "object_ref.h"
#include "quest.h"
#include "types.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest) {
        if (!quest) {
            return "";
        }

        TESFullName *full_name = DYNAMIC_CAST(quest, TESQuest, TESFullName);
        if (!full_name || !full_name->name || !full_name->name.data) {
            return "";
        }

        return full_name->name.data;
    }

}}

namespace doticu_npcp { namespace Quest { namespace Exports {


    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
