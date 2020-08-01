/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Consts {

    using namespace Papyrus;

    constexpr size_t MAX_MEMBERS = 1024;
    constexpr size_t MAX_FOLLOWERS = 16;

    String_t Class_Name();
    Class_Info_t* Class_Info();
    Consts_t* Self();
    Object_t* Object();
    Variable_t* Variable(String_t variable_name);

    // Skyrim.esm
    Actor_t* Player_Actor();

    Faction_t* No_Bard_Singer_Autostart_Faction();
    Faction_t* Current_Follower_Faction();
    Faction_t* Player_Follower_Faction();
    Faction_t* Potential_Follower_Faction();
    Faction_t* WI_No_Body_Cleanup_Faction();

    Global_t* Player_Follower_Count_Global();

    Keyword_t* Fire_Damage_Magic_Keyword();
    Keyword_t* Frost_Damage_Magic_Keyword();
    Keyword_t* Shock_Damage_Magic_Keyword();
    Keyword_t* Vampire_Drain_Magic_Keyword();

    Quest_t* Follower_Dialogue_Quest();

    Static_t* X_Marker_Static();

    // Dawnguard.esm
    Faction_t* DLC1_Thrall_Faction();
    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction();
    
    // doticu_npc_party.esp
    Armor_t* Blank_Armor();

    Faction_t* Member_Faction();
    Faction_t* Horse_Faction();

    Formlist_t* Settler_Markers_Formlist();

    Misc_t* Member_Token();
    Misc_t* Generic_Token();
    Misc_t* Clone_Token();
    Misc_t* Greeter_Token();
    Misc_t* Movee_Token();
    Misc_t* Immobile_Token();
    Misc_t* Settler_Token();
    Misc_t* Thrall_Token();
    Misc_t* Paralyzed_Token();
    Misc_t* Mannequin_Token();
    Misc_t* Display_Token();
    Misc_t* Reanimated_Token();
    Misc_t* Banished_Token();
    Misc_t* Default_Style_Token();
    Misc_t* Warrior_Style_Token();
    Misc_t* Mage_Style_Token();
    Misc_t* Archer_Style_Token();
    Misc_t* Coward_Style_Token();
    Misc_t* Mortal_Vitality_Token();
    Misc_t* Protected_Vitality_Token();
    Misc_t* Essential_Vitality_Token();
    Misc_t* Invulnerable_Vitality_Token();
    Misc_t* Follower_Token();
    Misc_t* Sneak_Follower_Token();
    Misc_t* Saddler_Token();
    Misc_t* Retreater_Token();
    Misc_t* Form_Vector();

    Outfit_t* Empty_Outfit();

    Quest_t* Static_Data_Quest();
    Quest_t* Dynamic_Data_Quest();
    Quest_t* Funcs_Quest();
    Quest_t* Members_Quest();
    Quest_t* Followers_Quest();
    Quest_t* Control_Quest();

    Reference_t* Input_Category();
    Reference_t* Swords_Category();
    Reference_t* Greatswords_Category();
    Reference_t* Waraxes_Category();
    Reference_t* Battleaxes_Category();
    Reference_t* Maces_Category();
    Reference_t* Warhammers_Category();
    Reference_t* Daggers_Category();
    Reference_t* Staves_Category();
    Reference_t* Bows_Category();
    Reference_t* Ammo_Category();
    Reference_t* Weapons_Category();
    Reference_t* Light_Armor_Category();
    Reference_t* Heavy_Armor_Category();
    Reference_t* Shields_Category();
    Reference_t* Jewelry_Category();
    Reference_t* Clothes_Category();
    Reference_t* Potions_Category();
    Reference_t* Poisons_Category();
    Reference_t* Ingredients_Category();
    Reference_t* Food_Category();
    Reference_t* Soulgems_Category();
    Reference_t* Scrolls_Category();
    Reference_t* Metals_Category();
    Reference_t* Leather_Category();
    Reference_t* Gems_Category();
    Reference_t* Clutter_Category();
    Reference_t* Keys_Category();
    Reference_t* Misc_Category();
    Reference_t* Spell_Tomes_Category();
    Reference_t* Recipes_Category();
    Reference_t* A_Books_Category();
    Reference_t* B_Books_Category();
    Reference_t* C_Books_Category();
    Reference_t* D_Books_Category();
    Reference_t* E_Books_Category();
    Reference_t* F_Books_Category();
    Reference_t* G_Books_Category();
    Reference_t* H_Books_Category();
    Reference_t* I_Books_Category();
    Reference_t* J_Books_Category();
    Reference_t* K_Books_Category();
    Reference_t* L_Books_Category();
    Reference_t* M_Books_Category();
    Reference_t* N_Books_Category();
    Reference_t* O_Books_Category();
    Reference_t* P_Books_Category();
    Reference_t* Q_Books_Category();
    Reference_t* R_Books_Category();
    Reference_t* S_Books_Category();
    Reference_t* T_Books_Category();
    Reference_t* U_Books_Category();
    Reference_t* V_Books_Category();
    Reference_t* W_Books_Category();
    Reference_t* X_Books_Category();
    Reference_t* Y_Books_Category();
    Reference_t* Z_Books_Category();
    Reference_t* Books_Category();
    Reference_t* Storage_Marker();

    Weapon_t* Blank_Weapon();

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Registry_t* registry);

}}}
