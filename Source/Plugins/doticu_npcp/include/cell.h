/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Cell {

    using namespace Papyrus;

    bool Is_Interior(TESObjectCELL *cell);
    bool Is_Exterior(TESObjectCELL *cell);
    Bool_t Has_Same_Worldspace(Cell_t* cell, Cell_t* other);

    Vector_t<Reference_t*> References(Cell_t* cell, Form_t* of_base);

}}
