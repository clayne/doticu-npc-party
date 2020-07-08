/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party.h"

namespace doticu_npcp { namespace Party { namespace Member {

    String_t Class_Name();
    Class_Info_t* Class_Info();

    Variable_t* Variable(Member_t* self, String_t variable_name);

    Actor_t* Actor(Member_t* self);
    Int_t Rating(Member_t* self);
    String_t Race_Name(Member_t* self);

    Bool_t Is_Filled(Member_t* self);
    Bool_t Is_Unfilled(Member_t* self);
    Bool_t Is_Loaded(Member_t* self);
    Bool_t Is_Unloaded(Member_t* self);
    Bool_t Is_Created(Member_t* self);
    Bool_t Is_Destroyed(Member_t* self);

    Bool_t Has_Same_Head(Member_t* self, Actor_t* actor);

    void Log_Variable_Infos(Member_t* self);

}}}

namespace doticu_npcp { namespace Party { namespace Member { namespace Exports {

    Bool_t Register(Registry_t* registry);

}}}}











































#include "papyrus.h"

namespace doticu_npcp { namespace Member {

    using namespace Papyrus;

    Actor* Get_Actor(Member_t* member);
    TESObjectREFR *Get_Pack(Member_t *member);
    SInt32 Get_Style(Member_t *member);
    SInt32 Get_Vitality(Member_t *member);
    SInt32 Get_Outfit2(Member_t *member);
    SInt32 Get_Rating(Member_t *member);

    bool Is_Created(Member_t *member);
    bool Is_Original(Member_t *member);
    bool Is_Clone(Member_t *member);
    bool Is_Follower(Member_t *member);
    bool Is_Mobile(Member_t *member);
    bool Is_Immobile(Member_t *member);
    bool Is_Settler(Member_t *member);
    bool Isnt_Settler(Member_t *member);
    bool Is_Thrall(Member_t *member);
    bool Isnt_Thrall(Member_t *member);
    bool Is_Paralyzed(Member_t *member);
    bool Isnt_Paralyzed(Member_t *member);
    bool Is_Mannequin(Member_t *member);
    bool Isnt_Mannequin(Member_t *member);
    bool Is_Reanimated(Member_t *member);
    bool Isnt_Reanimated(Member_t *member);

    void On_Hit(Member_t *member);

}}

namespace doticu_npcp { namespace Member { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
