/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Player {

    bool Is_Party_In_Combat(Player_t *player);
    bool Is_In_Interior_Cell();
    bool Is_In_Exterior_Cell();

}}

namespace doticu_npcp { namespace Player { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
