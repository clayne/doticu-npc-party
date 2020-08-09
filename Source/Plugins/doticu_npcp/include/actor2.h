/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "offsets.h"
#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Actor2 {

    const char *Get_Base_Name(Actor *actor);
    const char *Get_Ref_Name(Actor *actor);
    const char *Get_Name(Actor *actor);

    Outfit_t* Base_Outfit(Actor_t* actor);
    void Base_Outfit(Actor_t* actor, Outfit_t* outfit);
    void Base_Sleep_Outfit(Actor_t* actor, Outfit_t* outfit);
    void Set_Outfit_Basic(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit = false);
    void Set_Outfit(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit = false);

    void Set_Outfit2(Actor_t* actor, Reference_t* vanilla, Reference_t* custom, Reference_t* transfer);
    void Copy_Outfit2_Partition(Actor_t* actor, Reference_t* outfit2_partition);
    void Split_Inventory(Actor_t* actor, Reference_t* worn_out, Reference_t* pack_out);
    void Cache_Worn(Actor_t* actor, Reference_t* cache_out);
    void Cache_BContainer(Actor_t* actor, Reference_t* cache_out);

    bool Has_Same_Head(Actor *actor_a, Actor *actor_b);

    bool Is_Alive(Actor *actor);
    bool Is_Dead(Actor *actor);
    bool Is_Loaded(Actor_t *actor);
    bool Is_Unloaded(Actor_t* actor);
    bool Is_Unique(Actor_t* actor);
    bool Is_Generic(Actor_t* actor);
    bool Is_Aliased_In_Quest(Actor *actor, TESQuest *quest);

    void Move_To_Orbit(Actor* actor, Reference_t* origin, float radius, float degree);

    Actor_Value_Owner_t* Actor_Value_Owner(Actor_t* actor);
    float Get_Actor_Value(Actor *actor, const char *name);
    float Get_Base_Actor_Value(Actor *actor, const char *name);
    float Get_Max_Actor_Value(Actor *actor, const char *name);
    void Set_Actor_Value(Actor *actor, const char *name, float value);
    void Reset_Actor_Value(Actor *actor, const char *name);
    void Log_Actor_Values(Actor *actor);

    Actor_t* Get_Mount(Actor_t* mounter);
    Actor_t* Get_Mounted_Actor(Actor_t* horse);
    bool Is_On_Mount(Actor_t* actor);

    Int_t Sex(Actor_t* actor);
    String_t Sex_String(Actor_t* actor);
    String_t Race(Actor_t* actor);

    void Evaluate_Package(Actor_t* actor, bool unk_01 = false, bool unk_02 = false);
    void Update_3D_Model(Actor_t* actor);
    void Fully_Update_3D_Model(Actor_t* actor);
    void Queue_Ni_Node_Update(Actor_t* actor, bool do_update_weight = false);
    
    XFactions_t* XFactions(Actor_t* actor, bool do_create = false);
    BFaction_Ranks_t* BFaction_Ranks(Actor_t* actor);
    XFaction_Ranks_t* XFaction_Ranks(Actor_t* actor, bool do_create = false);
    
    Bool_t Has_Faction(Actor_t* actor, Faction_t* faction);
    Bool_t Has_Faction_Rank(Actor_t* actor, Faction_t* faction, Int_t rank);
    void Add_Faction(Actor_t* actor, Faction_t* faction, Int_t rank = 0);
    void Remove_Faction(Actor_t* actor, Faction_t* faction);
    void Add_Crime_Faction(Actor_t* actor, Faction_t* crime_faction);
    void Remove_Crime_Faction(Actor_t* actor);
    void Log_Factions(Actor_t* actor);

    void Join_Player_Team(Actor_t* actor, Bool_t allow_favors = true);
    void Leave_Player_Team(Actor_t* actor);
    Bool_t Is_Player_Teammate(Actor_t* actor);
    void Talks_To_Player(Actor_t* actor, Bool_t can_talk);
    Bool_t Can_Talk_To_Player(Actor_t* actor);
    Bool_t Cant_Talk_To_Player(Actor_t* actor);
    Bool_t Race_Can_Talk_To_Player(Actor_t* actor);
    Bool_t Race_Cant_Talk_To_Player(Actor_t* actor);

    Bool_t Is_AI_Enabled(Actor_t* actor);
    void Enable_AI(Actor_t* actor);
    void Disable_AI(Actor_t* actor);
    
    Bool_t Is_Ghost(Actor_t* actor);
    void Ghostify(Actor_t* actor);
    void Unghostify(Actor_t* actor);

    void Enable_Havok_Collision(Actor_t* actor);
    void Disable_Havok_Collision(Actor_t* actor);

    void Stop_Movement(Actor_t* actor);

    Actor_Base_t* Dynamic_Base(Actor_t* actor);
    Actor_Base_t* Real_Base(Actor_t* actor);

    void Pacify(Actor_t* actor);

    Actor_t* Clone(Actor_t* actor, Reference_t* marker = nullptr);
    void Resurrect(Actor_t* actor, Bool_t do_reset_inventory = false);
    Bool_t Try_Resurrect(Actor_t* actor, Bool_t do_reset_inventory = false);

    Bool_t Is_Child(Actor_t* actor);
    Bool_t Isnt_Child(Actor_t* actor);

    void Update_Equipment(Actor_t* actor, Papyrus::Virtual_Callback_i** callback = nullptr);

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
