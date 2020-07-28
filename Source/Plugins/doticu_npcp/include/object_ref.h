/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Object_Ref {

    BContainer_t *Get_BContainer(TESObjectREFR *obj);
    XContainer_t *Get_XContainer(TESObjectREFR *obj, bool do_create = false);

    BEntry_t *Get_BEntry(TESObjectREFR *obj, TESForm *form);
    XEntry_t *Get_XEntry(TESObjectREFR *obj, TESForm *form, bool do_create = false);
    void Add_XEntry(TESObjectREFR *obj, XEntry_t *xentry_add);
    void Remove_XEntry(TESObjectREFR *obj, XEntry_t *xentry);
    bool Has_XEntry(TESObjectREFR *obj, TESForm *form);

    void Move_Entry(TESObjectREFR *from, TESObjectREFR *to, TESForm *form);
    void Move_XList(TESObjectREFR *from, TESObjectREFR *to, TESForm *form, XList_t *xlist);

    SInt32 Get_BEntry_Count(TESObjectREFR *obj, TESForm *form);
    SInt32 Get_XEntry_Count(TESObjectREFR *obj, TESForm *form);
    SInt32 Get_Entry_Count(TESObjectREFR *obj, TESForm *form);

    const char *Get_Base_Name(TESObjectREFR *ref_object);
    const char *Get_Ref_Name(TESObjectREFR *ref_object);
    const char *Get_Name(TESObjectREFR *ref_object);

    bool Is_Off_Limits(TESObjectREFR *ref_object);
    bool Is_Quest_Item(TESObjectREFR *ref_object);
    bool Is_Worn(TESObjectREFR *obj, TESForm *form);

    void Remove_Unwearable(TESObjectREFR *obj, TESObjectREFR *other);
    void Categorize(TESObjectREFR *ref_object);
    void Log_XContainer(TESObjectREFR *obj);
    void Log_XList(TESObjectREFR *ref_object);

    void Move_To_Orbit(TESObjectREFR *obj, TESObjectREFR *target, float radius, float angle_degree);

    float Get_Distance(TESObjectREFR *obj, TESObjectREFR *target);
    bool Is_Near_Player(TESObjectREFR *obj, float max_radius = 4096);

    bool Has_Token(Reference_t* ref, Form_t* token, Int_t count = 1);
    void Token(Reference_t* ref, Form_t* token, Int_t count = 1);
    void Untoken(Reference_t* ref, Form_t* token);

    void Block_Activation(Reference_t* ref);
    void Unblock_Activation(Reference_t* ref);
    void Block_Player_Activation(Reference_t* ref);
    void Unblock_Player_Activation(Reference_t* ref);
    void Block_All_Activation(Reference_t* ref);
    void Unblock_All_Activation(Reference_t* ref);

    void Play_Animation(Reference_t* ref, void* nicontroller, void* nisequence_from, void* nisequence_to);

    void Rename(Reference_t* ref, String_t new_name);

    void Init_Container(Reference_t* ref);

    Reference_t* Place_At_Me(Reference_t* me,
                             Form_t* to_place,
                             Int_t count,
                             Bool_t force_persist = true,
                             Bool_t initially_disabled = false);

    Reference_t* From_Handle(Reference_Handle_t handle);

    Reference_t* Create_Marker_At(Reference_t* ref);

    void Delete(Reference_t* ref);
    void Undelete(Reference_t* ref);

    bool Is_In_Interior_Cell(Reference_t* ref);
    bool Is_In_Exterior_Cell(Reference_t* ref);

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
