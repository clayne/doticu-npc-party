/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Packages {

    void Execute_Package(Package_t* package, Actor_t* actor);

    void Execute_Menu_Exit();

    void Log_Package(Package_t* package);
    void Log_Packages();
    void Log_Template_Packages();

}}}

namespace doticu_npcp { namespace Papyrus { namespace Packages { namespace Exports {

    Bool_t Register(VMClassRegistry *registry);

}}}}
