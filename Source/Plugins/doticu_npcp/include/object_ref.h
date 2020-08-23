/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Object_Ref {

    using namespace Papyrus;

    String_t Class_Name();
    Class_Info_t* Class_Info();

    BContainer_t *Get_BContainer(TESObjectREFR *obj);
    XContainer_t *Get_XContainer(TESObjectREFR *obj, bool do_create = false);

    BEntry_t *Get_BEntry(TESObjectREFR *obj, TESForm *form);
    XEntry_t *Get_XEntry(TESObjectREFR *obj, TESForm *form, bool do_create = false);
    void Add_XEntry(TESObjectREFR *obj, XEntry_t *xentry_add);
    void Remove_XEntry(TESObjectREFR *obj, XEntry_t *xentry);
    void Remove_All_XEntries(Reference_t* ref);
    bool Has_XEntry(TESObjectREFR *obj, TESForm *form);
    void Move_Entry(TESObjectREFR *from, TESObjectREFR *to, TESForm *form);

    SInt32 Get_BEntry_Count(TESObjectREFR *obj, TESForm *form);
    SInt32 Get_XEntry_Count(TESObjectREFR *obj, TESForm *form);
    SInt32 Get_Entry_Count(TESObjectREFR *obj, TESForm *form);

    const char *Get_Base_Name(TESObjectREFR *ref_object);
    const char *Get_Ref_Name(TESObjectREFR *ref_object);
    const char *Get_Name(TESObjectREFR *ref_object);

    bool Is_Off_Limits(TESObjectREFR *ref_object);
    bool Is_Quest_Item(TESObjectREFR *ref_object);
    bool Is_Worn(TESObjectREFR *obj, TESForm *form);

    void Remove_If(Reference_t* from,
                   Reference_t* to = nullptr, // if nullptr, will delete items
                   Bool_t(*should_remove_xform)(Form_t*) = nullptr, // if nullptr, will remove all
                   Bool_t(*should_remove_xlist)(XList_t*, Form_t*) = nullptr, // if nullptr, will remove non-quest items
                   Bool_t(*should_remove_bform)(Form_t*) = nullptr); // if nullptr, is the same as should_remove_xform
    void Remove_Wearables(Reference_t* obj, Reference_t* other = nullptr, Bool_t remove_quest_items = false);
    void Remove_Unwearables(Reference_t* obj, Reference_t* other = nullptr, Bool_t remove_quest_items = false);
    void Remove_Non_Outfit_Worn(Reference_t* obj, Reference_t* other = nullptr, Bool_t remove_quest_items = false);
    void Remove_All_Items(Reference_t* from, Reference_t* to = nullptr, Bool_t remove_quest_items = false, Bool_t remove_unplayable_items = true);
    
    void Categorize(TESObjectREFR *ref_object);
    void Log_XContainer(TESObjectREFR *obj);
    void Log_XList(TESObjectREFR *ref_object);

    void Move_To_Orbit(TESObjectREFR *obj, TESObjectREFR *target, float radius, float angle_degree);
    void Move_To_Orbit_And_Callback(Reference_t* ref,
                                    Reference_t* origin,
                                    Float_t radius,
                                    Float_t degree,
                                    Virtual_Callback_i** callback = nullptr);
    void Move_To(Reference_t* ref,
                 Reference_t* target,
                 Float_t x_offset,
                 Float_t y_offset,
                 Float_t z_offset,
                 Bool_t do_match_rotation = true,
                 Virtual_Callback_i** callback = nullptr);
    void Set_Angle(Reference_t* ref,
                   Float_t x_degree,
                   Float_t y_degree,
                   Float_t z_degree,
                   Virtual_Callback_i** callback = nullptr);

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

    void Init_Container_If_Needed(Reference_t* ref);
    void Open_Container(Reference_t* ref, Papyrus::Virtual_Callback_i** callback = nullptr);

    void Activate(Reference_t* ref,
                  Reference_t* activator,
                  Bool_t do_default_processing_only = false,
                  Papyrus::Virtual_Callback_i** callback = nullptr);

    Reference_t* Place_At_Me(Reference_t* me,
                             Form_t* to_place,
                             Int_t count = 1,
                             Bool_t force_persist = true,
                             Bool_t initially_disabled = false);

    void Add_Item(Reference_t* ref, Form_t* form, Int_t count, Bool_t do_silently = true);

    Reference_t* From_Handle(Reference_Handle_t handle);

    Reference_t* Create_Marker_At(Reference_t* ref);
    Reference_t* Create_Container();

    void Delete_Safe(Reference_t* ref);
    void Delete_Unsafe(Reference_t* ref); // for some unknown reason, can sometimes cause a crash. but the above does not work with user types
    void Queue_Delete(Reference_t* ref);

    void Enable(Reference_t* ref, Bool_t do_fade_in = false, Virtual_Callback_i** callback = nullptr);
    void Disable(Reference_t* ref, Bool_t do_fade_out = false, Virtual_Callback_i** callback = nullptr);

    bool Is_In_Interior_Cell(Reference_t* ref);
    bool Is_In_Exterior_Cell(Reference_t* ref);

    UInt32 Ref_Count(Reference_t* ref);

    void Add_Item_And_Callback(Reference_t* ref,
                               Form_t* form,
                               Int_t count = 1,
                               Bool_t do_sounds = false,
                               Papyrus::Virtual_Callback_i** callback = nullptr);
    void Remove_Item_And_Callback(Reference_t* ref,
                                  Form_t* form,
                                  Int_t count = 1,
                                  Bool_t do_sounds = false,
                                  Reference_t* destination = nullptr,
                                  Papyrus::Virtual_Callback_i** callback = nullptr);

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
