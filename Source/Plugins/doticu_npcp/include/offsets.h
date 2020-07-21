/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64_common/Relocation.h"

// credit goes to meh321 of 'Address Library for SKSE Plugins' for the offsets
// and also Ryan-rsm-McKenzie of CommonLibSSE for the ids

// this is for version 1.5.97.0 only. use the ids in comments for other versions
namespace doticu_npcp { namespace Offsets {

    namespace Actor {

        constexpr uintptr_t EVALUATE_PACKAGE            = 0x005DB310; // 36407
        constexpr uintptr_t UPDATE_3D_MODEL             = 0x00650DF0; // 38404

    }

    namespace Container_Changes {

        constexpr uintptr_t CTOR                        = 0x001D9200; // 15812
        constexpr uintptr_t DTOR                        = 0x001D92F0; // 15813

    }

    namespace CRC32 {

        constexpr uintptr_t BY_SIZE                     = 0x00C06490; // 66962
        constexpr uintptr_t BY_32                       = 0x00C064F0; // 66963
        constexpr uintptr_t BY_64                       = 0x00C06570; // 66964

    }

    namespace Extra {

        constexpr uintptr_t CAN_TALK_TO_PLAYER_V_TABLE  = 0x0152C740; // 229596
        constexpr uintptr_t CONTAINER_CHANGES_V_TABLE   = 0x0152F260; // 229886
        constexpr uintptr_t FACTION_CHANGES_V_TABLE     = 0x0152C800; // 229602
        constexpr uintptr_t FLAGS_V_TABLE               = 0x0152CBC0; // 229632
        constexpr uintptr_t GHOST_V_TABLE               = 0x0152F2A0; // 229888
        constexpr uintptr_t TEXT_DISPLAY_V_TABLE        = 0x0152CAE0; // 229625

    }

    namespace Quest {

        //constexpr uintptr_t CLEAR_ALL_ALIASES         = 0x003745D0; // 24520
        //constexpr uintptr_t RESET_ALIAS_HASHMAP       = 0x00374880; // 24521
        constexpr uintptr_t FORCE_REFERENCE_TO          = 0x00375050; // 24523

    }

    namespace Reference {

        constexpr uintptr_t LOOKUP_REFERENCE_BY_HANDLE1 = 0x001328A0; // 12203
        constexpr uintptr_t LOOKUP_REFERENCE_BY_HANDLE2 = 0x001329D0; // 12204
        constexpr uintptr_t PLACE_AT_ME                 = 0x009951F0; // 55672
        constexpr uintptr_t PLAY_ANIMATION              = 0x00189E30; // 14189

    }

}}
