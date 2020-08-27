/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "game.h"
#include "utils.h"

#include "papyrus.inl"

/*
    We us macros in this module, because we want the
    assert to show us which variable is actually nullptr,
    instead of it being ambiguous through a template.
*/

namespace doticu_npcp { namespace Consts {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_consts");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    #define FORM(MOD_, TYPE_, MOD_ID_)              \
    {                                               \
        static TYPE_* value = static_cast<TYPE_*>   \
            (Game::MOD_(MOD_ID_));                  \
        NPCP_ASSERT(value);                         \
        return value;                               \
    }

    enum Skyrim_Forms {
        // Skyrim Actors
        ACTOR_PLAYER                        = 0x000014,

        // Skyrim Armors
        ARMOR_BELTED_TUNIC                  = 0x01BE1A,

        // Skyrim Effect Shaders
        EFFECT_SHADER_REANIMATE             = 0x075272,

        // Skyrim Factions
        FACTION_BARD_SINGER_NO_AUTOSTART    = 0x0163FA,
        FACTION_CURRENT_FOLLOWER            = 0x05C84E,
        FACTION_PLAYER_FOLLOWER             = 0x084D1B,
        FACTION_POTENTIAL_FOLLOWER          = 0x05C84D,
        FACTION_WI_NO_BODY_CLEANUP          = 0x09653A,

        // Skyrim Globals
        GLOBAL_PLAYER_FOLLOWER_COUNT        = 0x0BCC98,

        // Skyrim Keywords
        KEYWORD_MAGIC_DAMAGE_FIRE           = 0x01CEAD,
        KEYWORD_MAGIC_DAMAGE_FROST          = 0x01CEAE,
        KEYWORD_MAGIC_DAMAGE_SHOCK          = 0x01CEAF,
        KEYWORD_MAGIC_VAMPIRE_DRAIN         = 0x101BDE,
        KEYWORD_VAMPIRE                     = 0x0A82BB,

        // Skyrim Miscs
        MISC_GOLD                           = 0x00000F,

        // Skyrim Perks
        PERK_VAMPIRE_FEED                   = 0x0CF02C,

        // Skyrim Quests
        QUEST_BARD_SONGS                    = 0x074A55,
        QUEST_DIALOGUE_FOLLOWER             = 0x0750BA,
        QUEST_PLAYER_VAMPIRE                = 0x0EAFD5,

        // Skyrim Reference Markers
        REFERENCE_MARKER_GO_BACK_SAFE       = 0x01BDF3,

        // Skyrim Statics
        STATIC_MARKER_X                     = 0x00003B,
    };

    #define SKYRIM_FORM(TYPE_, MOD_ID_) FORM(Skyrim_Form, TYPE_, MOD_ID_);

    // Skyrim Actors
    Actor_t* Player_Actor() { SKYRIM_FORM(Actor_t, ACTOR_PLAYER); }

    // Skyrim Armors
    Armor_t* Belted_Tunic_Armor() { SKYRIM_FORM(Armor_t, ARMOR_BELTED_TUNIC); }

    // Skyrim Effect Shaders
    Effect_Shader_t* Reanimate_Effect_Shader() { SKYRIM_FORM(Effect_Shader_t, EFFECT_SHADER_REANIMATE); }

    // Skyrim Factions
    Faction_t* No_Bard_Singer_Autostart_Faction() { SKYRIM_FORM(Faction_t, FACTION_BARD_SINGER_NO_AUTOSTART); }
    Faction_t* Current_Follower_Faction() { SKYRIM_FORM(Faction_t, FACTION_CURRENT_FOLLOWER); }
    Faction_t* Player_Follower_Faction() { SKYRIM_FORM(Faction_t, FACTION_PLAYER_FOLLOWER); }
    Faction_t* Potential_Follower_Faction() { SKYRIM_FORM(Faction_t, FACTION_POTENTIAL_FOLLOWER); }
    Faction_t* WI_No_Body_Cleanup_Faction() { SKYRIM_FORM(Faction_t, FACTION_WI_NO_BODY_CLEANUP); }

    // Skyrim Globals
    Global_t* Player_Follower_Count_Global() { SKYRIM_FORM(Global_t, GLOBAL_PLAYER_FOLLOWER_COUNT); }

    // Skyrim Keywords
    Keyword_t* Fire_Damage_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_FIRE); }
    Keyword_t* Frost_Damage_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_FROST); }
    Keyword_t* Shock_Damage_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_DAMAGE_SHOCK); }
    Keyword_t* Vampire_Drain_Magic_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_MAGIC_VAMPIRE_DRAIN); }
    Keyword_t* Vampire_Keyword() { SKYRIM_FORM(Keyword_t, KEYWORD_VAMPIRE); }

    // Skyrim Miscs
    Misc_t* Gold() { SKYRIM_FORM(Misc_t, MISC_GOLD); }

    // Skyrim Perks
    Perk_t* Vampire_Feed_Perk() { SKYRIM_FORM(Perk_t, PERK_VAMPIRE_FEED); }

    // Skyrim Quests
    Quest_t* Bard_Songs_Quest() { SKYRIM_FORM(Quest_t, QUEST_BARD_SONGS); }
    Quest_t* Follower_Dialogue_Quest() { SKYRIM_FORM(Quest_t, QUEST_DIALOGUE_FOLLOWER); }
    Quest_t* Player_Vampire_Quest() { SKYRIM_FORM(Quest_t, QUEST_PLAYER_VAMPIRE); }

    // Skyrim Reference Markers
    Reference_t* Safe_Go_Back_Marker() { SKYRIM_FORM(Reference_t, REFERENCE_MARKER_GO_BACK_SAFE); }

    // Skyrim Statics
    Static_t* X_Marker_Static() { SKYRIM_FORM(Static_t, STATIC_MARKER_X); }

    #undef SKYRIM_FORM

    enum Dawnguard_Forms {
        // Dawnguard Factions
        FACTION_DLC1_THRALL                 = 0x0162F7,
        FACTION_DLC1_VAMPIRE_FEED_NO_CRIME  = 0x014CBD,
    };

    #define DAWNGUARD_FORM(TYPE_, MOD_ID_) FORM(Dawnguard_Form, TYPE_, MOD_ID_);

    // Dawnguard Factions
    Faction_t* DLC1_Thrall_Faction() { DAWNGUARD_FORM(Faction_t, FACTION_DLC1_THRALL); }
    Faction_t* DLC1_Vampire_Feed_No_Crime_Faction() { DAWNGUARD_FORM(Faction_t, FACTION_DLC1_VAMPIRE_FEED_NO_CRIME); }

    #undef DAWNGUARD_FORM

    enum NPCP_Forms {
        // NPCP Actor Base
        ACTOR_BASE_MENU                     = 0x317447,

        // NPCP Armors
        ARMOR_BLANK                         = 0x1EF2A5,

        // NPCP Cells
        CELL_STORAGE                        = 0x114F9C,

        // NPCP Containers
        CONTAINER_EMPTY                     = 0x0A5561,
        CONTAINER_OUTFIT2                   = 0x0B9A63,
        CONTAINER_OUTFIT2_IMMOBILE          = 0x1663CE,
        CONTAINER_OUTFIT2_SETTLER           = 0x1663CD,
        CONTAINER_OUTFIT2_THRALL            = 0x1663CC,
        CONTAINER_OUTFIT2_FOLLOWER          = 0x1663C7,

        // NPCP Factions
        FACTION_HORSE                       = 0x354111,
        FACTION_MEMBER                      = 0x091154,

        // NPCP Formlists
        FORMLIST_GLOBALS_IS_SADDLER_SITTING = 0x395E54,
        FORMLIST_MARKERS_EXPO_CELL          = 0x2928AF,
        FORMLIST_MARKERS_SETTLER            = 0x00B46E,

        // NPCP Globals
        GLOBAL_IS_INSTALLED                 = 0x189ADD,
        GLOBAL_ALLOW_DIALOGUE_FOR_ALL       = 0x3B4463,
        GLOBAL_FORCE_CLONE_UNIQUES          = 0x05244D,
        GLOBAL_FORCE_CLONE_GENERICS         = 0x05244E,
        GLOBAL_FORCE_UNCLONE_UNIQUES        = 0x05244F,
        GLOBAL_FORCE_UNCLONE_GENERICS       = 0x052450,
        GLOBAL_PERCENT_NO_BODY              = 0x193CEA,
        GLOBAL_PERCENT_NO_FEET              = 0x193CE7,
        GLOBAL_PERCENT_NO_HANDS             = 0x193CE8,
        GLOBAL_PERCENT_NO_HEAD              = 0x193CE6,

        // NPCP Leveled Actor
        LEVELED_ACTOR_HORSE                 = 0x354127,

        // NPCP Location
        LOCATION_EXPO                       = 0x27E48E,

        // NPCP Magic Effects
        MAGIC_EFFECT_REANIMATE              = 0x3AF361,
        MAGIC_EFFECT_RETREAT                = 0x2DF8FA,

        // NPCP Misc Tokens
        MISC_TOKEN_BANISHED                 = 0x003DFD,
        MISC_TOKEN_CLONE                    = 0x003DFC,
        MISC_TOKEN_DISPLAY                  = 0x13D7AC,
        MISC_TOKEN_FOLLOWER                 = 0x000D84,
        MISC_TOKEN_FOLLOWER_SNEAK           = 0x000D85,
        MISC_TOKEN_GENERIC                  = 0x003DFE,
        MISC_TOKEN_GREETER                  = 0x057384,
        MISC_TOKEN_IMMOBILE                 = 0x000D77,
        MISC_TOKEN_MANNEQUIN                = 0x264F42,
        MISC_TOKEN_MEMBER                   = 0x000D75,
        MISC_TOKEN_MOVEE                    = 0x1612B3,
        MISC_TOKEN_PARALYZED                = 0x12E4A7,
        MISC_TOKEN_REANIMATED               = 0x1E4E9D,
        MISC_TOKEN_RETREATER                = 0x2F3D00,
        MISC_TOKEN_SADDLER                  = 0x34F000,
        MISC_TOKEN_SETTLER                  = 0x000D73,
        MISC_TOKEN_STYLE_ARCHER             = 0x0A045E,
        MISC_TOKEN_STYLE_COWARD             = 0x2D56F3,
        MISC_TOKEN_STYLE_DEFAULT            = 0x0A045D,
        MISC_TOKEN_STYLE_MAGE               = 0x0A045F,
        MISC_TOKEN_STYLE_WARRIOR            = 0x0A0460,
        MISC_TOKEN_THRALL                   = 0x011E90,
        MISC_TOKEN_VITALITY_ESSENTIAL       = 0x0A0459,
        MISC_TOKEN_VITALITY_INVULNERABLE    = 0x0A045C,
        MISC_TOKEN_VITALITY_MORTAL          = 0x0A045B,
        MISC_TOKEN_VITALITY_PROTECTED       = 0x0A045A,

        // NPCP Misc
        MISC_VECTOR_FORM                    = 0x15C1B2,

        // NPCP Outfits
        OUTFIT_EMPTY                        = 0x0C3C64,

        // NPCP PERKS
        PERK_KISS_THRALL                    = 0x07CD48,
        PERK_REANIMATE                      = 0x1DFD9C,
        PERK_RESURRECT                      = 0x0D2F7C,
        PERK_UNPARALYZE                     = 0x16B4D1,

        // NPCP Quests
        QUEST_MAIN                          = 0x005385,
        QUEST_VARS                          = 0x003DFF,
        QUEST_FUNCS                         = 0x005384,
        QUEST_MEMBERS                       = 0x00184C,
        QUEST_FOLLOWERS                     = 0x000D83,
        QUEST_CONTROL                       = 0x000D7F,
        QUEST_DIALOGUE_THRALL               = 0x212D57,
        QUEST_DIALOGUE_REANIMATED           = 0x2089A9,

        // NPCP Reference Categories
        REFERENCE_CATEGORY_INPUT            = 0x395E55,
        REFERENCE_CATEGORY_SWORDS           = 0x30D20A,
        REFERENCE_CATEGORY_GREATSWORDS      = 0x30D20B,
        REFERENCE_CATEGORY_WARAXES          = 0x30D20C,
        REFERENCE_CATEGORY_BATTLEAXES       = 0x30D20D,
        REFERENCE_CATEGORY_MACES            = 0x30D20E,
        REFERENCE_CATEGORY_WARHAMMERS       = 0x30D20F,
        REFERENCE_CATEGORY_DAGGERS          = 0x30D210,
        REFERENCE_CATEGORY_STAVES           = 0x30D212,
        REFERENCE_CATEGORY_BOWS             = 0x30D211,
        REFERENCE_CATEGORY_AMMO             = 0x30D23D,
        REFERENCE_CATEGORY_WEAPONS          = 0x30D213,
        REFERENCE_CATEGORY_LIGHT_ARMOR      = 0x30D214,
        REFERENCE_CATEGORY_HEAVY_ARMOR      = 0x30D215,
        REFERENCE_CATEGORY_SHIELDS          = 0x30D216,
        REFERENCE_CATEGORY_JEWELRY          = 0x30D217,
        REFERENCE_CATEGORY_CLOTHES          = 0x30D218,
        REFERENCE_CATEGORY_POTIONS          = 0x30D219,
        REFERENCE_CATEGORY_POISONS          = 0x30D21A,
        REFERENCE_CATEGORY_INGREDIENTS      = 0x30D23E,
        REFERENCE_CATEGORY_FOOD             = 0x30D21B,
        REFERENCE_CATEGORY_SOULGEMS         = 0x30D240,
        REFERENCE_CATEGORY_SCROLLS          = 0x30D23F,
        REFERENCE_CATEGORY_METALS           = 0x30D239,
        REFERENCE_CATEGORY_LEATHER          = 0x30D23A,
        REFERENCE_CATEGORY_GEMS             = 0x30D23B,
        REFERENCE_CATEGORY_CLUTTER          = 0x30D23C,
        REFERENCE_CATEGORY_KEYS             = 0x30D241,
        REFERENCE_CATEGORY_MISC             = 0x30D242,
        REFERENCE_CATEGORY_SPELL_TOMES      = 0x30D21C,
        REFERENCE_CATEGORY_RECIPES          = 0x30D21D,
        REFERENCE_CATEGORY_BOOKS_A          = 0x30D21E,
        REFERENCE_CATEGORY_BOOKS_B          = 0x30D21F,
        REFERENCE_CATEGORY_BOOKS_C          = 0x30D220,
        REFERENCE_CATEGORY_BOOKS_D          = 0x30D221,
        REFERENCE_CATEGORY_BOOKS_E          = 0x30D222,
        REFERENCE_CATEGORY_BOOKS_F          = 0x30D223,
        REFERENCE_CATEGORY_BOOKS_G          = 0x30D224,
        REFERENCE_CATEGORY_BOOKS_H          = 0x30D225,
        REFERENCE_CATEGORY_BOOKS_I          = 0x30D226,
        REFERENCE_CATEGORY_BOOKS_J          = 0x30D227,
        REFERENCE_CATEGORY_BOOKS_K          = 0x30D228,
        REFERENCE_CATEGORY_BOOKS_L          = 0x30D229,
        REFERENCE_CATEGORY_BOOKS_M          = 0x30D22A,
        REFERENCE_CATEGORY_BOOKS_N          = 0x30D22B,
        REFERENCE_CATEGORY_BOOKS_O          = 0x30D22C,
        REFERENCE_CATEGORY_BOOKS_P          = 0x30D22D,
        REFERENCE_CATEGORY_BOOKS_Q          = 0x30D22E,
        REFERENCE_CATEGORY_BOOKS_R          = 0x30D22F,
        REFERENCE_CATEGORY_BOOKS_S          = 0x30D230,
        REFERENCE_CATEGORY_BOOKS_T          = 0x30D231,
        REFERENCE_CATEGORY_BOOKS_U          = 0x30D232,
        REFERENCE_CATEGORY_BOOKS_V          = 0x30D233,
        REFERENCE_CATEGORY_BOOKS_W          = 0x30D234,
        REFERENCE_CATEGORY_BOOKS_X          = 0x30D235,
        REFERENCE_CATEGORY_BOOKS_Y          = 0x30D236,
        REFERENCE_CATEGORY_BOOKS_Z          = 0x30D237,
        REFERENCE_CATEGORY_BOOKS            = 0x30D238,

        // NPCP Reference Markers
        REFERENCE_MARKER_CELL               = 0x15C1AE,
        REFERENCE_MARKER_EXPO_ANTECHAMBER   = 0x2979B0,
        REFERENCE_MARKER_STORAGE            = 0x114F9D,

        // NPCP Spells
        SPELL_ABILITY_CELL                  = 0x15C1B0,
        SPELL_ABILITY_REANIMATE             = 0x3AF362,
        SPELL_ABILITY_RETREAT               = 0x2F3CFF,

        // NPCP Weapons
        WEAPON_BLANK                        = 0x0C8D65,
    };

    #define NPCP_FORM(TYPE_, MOD_ID_) FORM(NPCP_Form, TYPE_, MOD_ID_);

    // NPCP Actor Base
    Actor_Base_t* Menu_Actor_Base() { NPCP_FORM(Actor_Base_t, ACTOR_BASE_MENU); }

    // NPCP Armors
    Armor_t* Blank_Armor() { NPCP_FORM(Armor_t, ARMOR_BLANK); }

    // NPCP Cells
    Cell_t* Storage_Cell() { NPCP_FORM(Cell_t, CELL_STORAGE); }

    // NPCP Containers
    Container_t* Empty_Container() { NPCP_FORM(Container_t, CONTAINER_EMPTY); }
    Container_t* Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2); }
    Container_t* Immobile_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_IMMOBILE); }
    Container_t* Settler_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_SETTLER); }
    Container_t* Thrall_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_THRALL); }
    Container_t* Follower_Outfit2_Container() { NPCP_FORM(Container_t, CONTAINER_OUTFIT2_FOLLOWER); }

    // NPCP Factions
    Faction_t* Member_Faction() { NPCP_FORM(Faction_t, FACTION_MEMBER); }
    Faction_t* Horse_Faction() { NPCP_FORM(Faction_t, FACTION_HORSE); }

    // NPCP Formlists
    Formlist_t* Is_Saddler_Sitting_Globals_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_GLOBALS_IS_SADDLER_SITTING); }
    Formlist_t* Expo_Cell_Markers_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_MARKERS_EXPO_CELL); }
    Formlist_t* Settler_Markers_Formlist() { NPCP_FORM(Formlist_t, FORMLIST_MARKERS_SETTLER); }

    // NPCP Globals
    Global_t* Is_Installed_Global() { NPCP_FORM(Global_t, GLOBAL_IS_INSTALLED); }
    Global_t* Allow_Dialogue_For_All_Global() { NPCP_FORM(Global_t, GLOBAL_ALLOW_DIALOGUE_FOR_ALL); }
    Global_t* Force_Clone_Uniques_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_CLONE_UNIQUES); }
    Global_t* Force_Clone_Generics_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_CLONE_GENERICS); }
    Global_t* Force_Unclone_Uniques_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_UNCLONE_UNIQUES); }
    Global_t* Force_Unclone_Generics_Global() { NPCP_FORM(Global_t, GLOBAL_FORCE_UNCLONE_GENERICS); }
    Global_t* No_Body_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_BODY); }
    Global_t* No_Feet_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_FEET); }
    Global_t* No_Hands_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_HANDS); }
    Global_t* No_Head_Percent_Global() { NPCP_FORM(Global_t, GLOBAL_PERCENT_NO_HEAD); }

    // NPCP Ints
    Int_t NPCP_Major() { return 0; } // set manually upon each release
    Int_t NPCP_Minor() { return 9; } // set manually upon each release
    Int_t NPCP_Patch() { return 5; } // set manually upon each release

    // NPCP Leveled Actor
    Leveled_Actor_t* Horse_Leveled_Actor() { NPCP_FORM(Leveled_Actor_t, LEVELED_ACTOR_HORSE); }

    // NPCP Location
    Location_t* Expo_Location() { NPCP_FORM(Location_t, LOCATION_EXPO); }

    // NPCP Magic Effects
    Magic_Effect_t* Reanimate_Magic_Effect() { NPCP_FORM(Magic_Effect_t, MAGIC_EFFECT_REANIMATE); }
    Magic_Effect_t* Retreat_Magic_Effect() { NPCP_FORM(Magic_Effect_t, MAGIC_EFFECT_RETREAT); }

    // NPCP Misc Tokens
    Misc_t* Member_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_MEMBER); }
    Misc_t* Generic_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_GENERIC); }
    Misc_t* Clone_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_CLONE); }
    Misc_t* Greeter_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_GREETER); }
    Misc_t* Movee_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_MOVEE); }
    Misc_t* Immobile_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_IMMOBILE); }
    Misc_t* Settler_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SETTLER); }
    Misc_t* Thrall_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_THRALL); }
    Misc_t* Paralyzed_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_PARALYZED); }
    Misc_t* Mannequin_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_MANNEQUIN); }
    Misc_t* Display_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_DISPLAY); }
    Misc_t* Reanimated_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_REANIMATED); }
    Misc_t* Banished_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_BANISHED); }
    Misc_t* Default_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_DEFAULT); }
    Misc_t* Warrior_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_WARRIOR); }
    Misc_t* Mage_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_MAGE); }
    Misc_t* Archer_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_ARCHER); }
    Misc_t* Coward_Style_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_STYLE_COWARD); }
    Misc_t* Mortal_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_MORTAL); }
    Misc_t* Protected_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_PROTECTED); }
    Misc_t* Essential_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_ESSENTIAL); }
    Misc_t* Invulnerable_Vitality_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_VITALITY_INVULNERABLE); }
    Misc_t* Follower_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER); }
    Misc_t* Sneak_Follower_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_FOLLOWER_SNEAK); }
    Misc_t* Saddler_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_SADDLER); }
    Misc_t* Retreater_Token() { NPCP_FORM(Misc_t, MISC_TOKEN_RETREATER); }

    // NPCP Misc
    Misc_t* Form_Vector() { NPCP_FORM(Misc_t, MISC_VECTOR_FORM); }

    // NPCP Outfits
    Outfit_t* Empty_Outfit() { NPCP_FORM(Outfit_t, OUTFIT_EMPTY); }

    // NPCP Perks
    Perk_t* Kiss_Thrall_Perk() { NPCP_FORM(Perk_t, PERK_KISS_THRALL); }
    Perk_t* Reanimate_Perk() { NPCP_FORM(Perk_t, PERK_REANIMATE); }
    Perk_t* Resurrect_Perk() { NPCP_FORM(Perk_t, PERK_RESURRECT); }
    Perk_t* Unparalyze_Perk() { NPCP_FORM(Perk_t, PERK_UNPARALYZE); }

    // NPCP Quests
    Quest_t* Main_Quest() { NPCP_FORM(Quest_t, QUEST_MAIN); }
    Quest_t* Vars_Quest() { NPCP_FORM(Quest_t, QUEST_VARS); }
    Quest_t* Funcs_Quest() { NPCP_FORM(Quest_t, QUEST_FUNCS); }
    Quest_t* Members_Quest() { NPCP_FORM(Quest_t, QUEST_MEMBERS); }
    Quest_t* Followers_Quest() { NPCP_FORM(Quest_t, QUEST_FOLLOWERS); }
    Quest_t* Control_Quest() { NPCP_FORM(Quest_t, QUEST_CONTROL); }
    Quest_t* Thrall_Dialogue_Quest() { NPCP_FORM(Quest_t, QUEST_DIALOGUE_THRALL); }
    Quest_t* Reanimated_Dialogue_Quest() { NPCP_FORM(Quest_t, QUEST_DIALOGUE_REANIMATED); }

    // NPCP Reference Categories
    Reference_t* Input_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_INPUT); }
    Reference_t* Swords_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SWORDS); }
    Reference_t* Greatswords_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_GREATSWORDS); }
    Reference_t* Waraxes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WARAXES); }
    Reference_t* Battleaxes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BATTLEAXES); }
    Reference_t* Maces_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_MACES); }
    Reference_t* Warhammers_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WARHAMMERS); }
    Reference_t* Daggers_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_DAGGERS); }
    Reference_t* Staves_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_STAVES); }
    Reference_t* Bows_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOWS); }
    Reference_t* Ammo_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_AMMO); }
    Reference_t* Weapons_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_WEAPONS); }
    Reference_t* Light_Armor_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_LIGHT_ARMOR); }
    Reference_t* Heavy_Armor_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_HEAVY_ARMOR); }
    Reference_t* Shields_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SHIELDS); }
    Reference_t* Jewelry_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_JEWELRY); }
    Reference_t* Clothes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CLOTHES); }
    Reference_t* Potions_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_POTIONS); }
    Reference_t* Poisons_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_POISONS); }
    Reference_t* Ingredients_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_INGREDIENTS); }
    Reference_t* Food_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_FOOD); }
    Reference_t* Soulgems_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SOULGEMS); }
    Reference_t* Scrolls_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SCROLLS); }
    Reference_t* Metals_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_METALS); }
    Reference_t* Leather_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_LEATHER); }
    Reference_t* Gems_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_GEMS); }
    Reference_t* Clutter_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_CLUTTER); }
    Reference_t* Keys_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_KEYS); }
    Reference_t* Misc_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_MISC); }
    Reference_t* Spell_Tomes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_SPELL_TOMES); }
    Reference_t* Recipes_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_RECIPES); }
    Reference_t* A_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_A); }
    Reference_t* B_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_B); }
    Reference_t* C_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_C); }
    Reference_t* D_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_D); }
    Reference_t* E_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_E); }
    Reference_t* F_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_F); }
    Reference_t* G_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_G); }
    Reference_t* H_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_H); }
    Reference_t* I_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_I); }
    Reference_t* J_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_J); }
    Reference_t* K_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_K); }
    Reference_t* L_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_L); }
    Reference_t* M_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_M); }
    Reference_t* N_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_N); }
    Reference_t* O_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_O); }
    Reference_t* P_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_P); }
    Reference_t* Q_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Q); }
    Reference_t* R_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_R); }
    Reference_t* S_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_S); }
    Reference_t* T_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_T); }
    Reference_t* U_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_U); }
    Reference_t* V_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_V); }
    Reference_t* W_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_W); }
    Reference_t* X_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_X); }
    Reference_t* Y_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Y); }
    Reference_t* Z_Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS_Z); }
    Reference_t* Books_Category() { NPCP_FORM(Reference_t, REFERENCE_CATEGORY_BOOKS); }

    // NPCP Reference Markers
    Reference_t* Cell_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_CELL); }
    Reference_t* Expo_Antechamber_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_EXPO_ANTECHAMBER); }
    Reference_t* Storage_Marker() { NPCP_FORM(Reference_t, REFERENCE_MARKER_STORAGE); }

    // NPCP Spells
    Spell_t* Cell_Ability_Spell() { NPCP_FORM(Spell_t, SPELL_ABILITY_CELL); }
    Spell_t* Reanimate_Ability_Spell() { NPCP_FORM(Spell_t, SPELL_ABILITY_REANIMATE); }
    Spell_t* Retreat_Ability_Spell() { NPCP_FORM(Spell_t, SPELL_ABILITY_RETREAT); }

    // NPCP Weapons
    Weapon_t* Blank_Weapon() { NPCP_FORM(Weapon_t, WEAPON_BLANK); }

    #undef NPCP_FORM

    #undef FORM

}}

namespace doticu_npcp { namespace Consts { namespace Exports {

    bool Register(Papyrus::Registry_t* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            auto lambda = [](Selfless_t*) -> RETURN_                    \
            {                                                           \
                return Consts::METHOD_();                               \
            };                                                          \
            ADD_CLASS_METHOD("doticu_npcp_consts", Selfless_t,          \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, lambda, __VA_ARGS__);             \
        W

        // Skyrim Actors
        ADD_GLOBAL("Player_Actor", 0, Actor_t*, Player_Actor);

        // Skyrim Keywords
        ADD_GLOBAL("Vampire_Keyword", 0, Keyword_t*, Vampire_Keyword);

        // Skyrim Perks
        ADD_GLOBAL("Vampire_Feed_Perk", 0, Perk_t*, Vampire_Feed_Perk);

        // Skyrim Quests
        ADD_GLOBAL("Bard_Songs_Quest", 0, Quest_t*, Bard_Songs_Quest);
        ADD_GLOBAL("Player_Vampire_Quest", 0, Quest_t*, Player_Vampire_Quest);

        // Skyrim Statics
        ADD_GLOBAL("X_Marker_Static", 0, Static_t*, X_Marker_Static);

        // Dawnguard Factions
        ADD_GLOBAL("DLC1_Thrall_Faction", 0, Faction_t*, DLC1_Thrall_Faction);

        // NPCP Actor Base
        ADD_GLOBAL("Menu_Actor_Base", 0, Actor_Base_t*, Menu_Actor_Base);

        // NPCP Formlists
        ADD_GLOBAL("Is_Saddler_Sitting_Globals_Formlist", 0, Formlist_t*, Is_Saddler_Sitting_Globals_Formlist);
        ADD_GLOBAL("Expo_Cell_Markers_Formlist", 0, Formlist_t*, Expo_Cell_Markers_Formlist);

        // NPCP Globals
        ADD_GLOBAL("Is_Installed_Global", 0, Global_t*, Is_Installed_Global);
        ADD_GLOBAL("Allow_Dialogue_For_All_Global", 0, Global_t*, Allow_Dialogue_For_All_Global);
        ADD_GLOBAL("Force_Clone_Uniques_Global", 0, Global_t*, Force_Clone_Uniques_Global);
        ADD_GLOBAL("Force_Clone_Generics_Global", 0, Global_t*, Force_Clone_Generics_Global);
        ADD_GLOBAL("Force_Unclone_Uniques_Global", 0, Global_t*, Force_Unclone_Uniques_Global);
        ADD_GLOBAL("Force_Unclone_Generics_Global", 0, Global_t*, Force_Unclone_Generics_Global);
        ADD_GLOBAL("No_Body_Percent_Global", 0, Global_t*, No_Body_Percent_Global);
        ADD_GLOBAL("No_Feet_Percent_Global", 0, Global_t*, No_Feet_Percent_Global);
        ADD_GLOBAL("No_Hands_Percent_Global", 0, Global_t*, No_Hands_Percent_Global);
        ADD_GLOBAL("No_Head_Percent_Global", 0, Global_t*, No_Head_Percent_Global);

        // NPCP Ints
        ADD_GLOBAL("NPCP_Major", 0, Int_t, NPCP_Major);
        ADD_GLOBAL("NPCP_Minor", 0, Int_t, NPCP_Minor);
        ADD_GLOBAL("NPCP_Patch", 0, Int_t, NPCP_Patch);

        // NPCP Location
        ADD_GLOBAL("Expo_Location", 0, Location_t*, Expo_Location);

        // NPCP Misc Tokens
        ADD_GLOBAL("Greeter_Token", 0, Misc_t*, Greeter_Token);
        ADD_GLOBAL("Movee_Token", 0, Misc_t*, Movee_Token);

        // NPCP Perks
        ADD_GLOBAL("Kiss_Thrall_Perk", 0, Perk_t*, Kiss_Thrall_Perk);
        ADD_GLOBAL("Reanimate_Perk", 0, Perk_t*, Reanimate_Perk);
        ADD_GLOBAL("Resurrect_Perk", 0, Perk_t*, Resurrect_Perk);
        ADD_GLOBAL("Unparalyze_Perk", 0, Perk_t*, Unparalyze_Perk);

        // NPCP Quests
        ADD_GLOBAL("Main_Quest", 0, Quest_t*, Main_Quest);
        ADD_GLOBAL("Vars_Quest", 0, Quest_t*, Vars_Quest);
        ADD_GLOBAL("Funcs_Quest", 0, Quest_t*, Funcs_Quest);
        ADD_GLOBAL("Members_Quest", 0, Quest_t*, Members_Quest);
        ADD_GLOBAL("Followers_Quest", 0, Quest_t*, Followers_Quest);
        ADD_GLOBAL("Control_Quest", 0, Quest_t*, Control_Quest);
        ADD_GLOBAL("Thrall_Dialogue_Quest", 0, Quest_t*, Thrall_Dialogue_Quest);
        ADD_GLOBAL("Reanimated_Dialogue_Quest", 0, Quest_t*, Reanimated_Dialogue_Quest);

        // NPCP Reference Categories
        ADD_GLOBAL("Input_Category", 0, Reference_t*, Input_Category);
        ADD_GLOBAL("Swords_Category", 0, Reference_t*, Swords_Category);
        ADD_GLOBAL("Greatswords_Category", 0, Reference_t*, Greatswords_Category);
        ADD_GLOBAL("Waraxes_Category", 0, Reference_t*, Waraxes_Category);
        ADD_GLOBAL("Battleaxes_Category", 0, Reference_t*, Battleaxes_Category);
        ADD_GLOBAL("Maces_Category", 0, Reference_t*, Maces_Category);
        ADD_GLOBAL("Warhammers_Category", 0, Reference_t*, Warhammers_Category);
        ADD_GLOBAL("Daggers_Category", 0, Reference_t*, Daggers_Category);
        ADD_GLOBAL("Staves_Category", 0, Reference_t*, Staves_Category);
        ADD_GLOBAL("Bows_Category", 0, Reference_t*, Bows_Category);
        ADD_GLOBAL("Ammo_Category", 0, Reference_t*, Ammo_Category);
        ADD_GLOBAL("Weapons_Category", 0, Reference_t*, Weapons_Category);
        ADD_GLOBAL("Light_Armor_Category", 0, Reference_t*, Light_Armor_Category);
        ADD_GLOBAL("Heavy_Armor_Category", 0, Reference_t*, Heavy_Armor_Category);
        ADD_GLOBAL("Shields_Category", 0, Reference_t*, Shields_Category);
        ADD_GLOBAL("Jewelry_Category", 0, Reference_t*, Jewelry_Category);
        ADD_GLOBAL("Clothes_Category", 0, Reference_t*, Clothes_Category);
        ADD_GLOBAL("Potions_Category", 0, Reference_t*, Potions_Category);
        ADD_GLOBAL("Poisons_Category", 0, Reference_t*, Poisons_Category);
        ADD_GLOBAL("Ingredients_Category", 0, Reference_t*, Ingredients_Category);
        ADD_GLOBAL("Food_Category", 0, Reference_t*, Food_Category);
        ADD_GLOBAL("Soulgems_Category", 0, Reference_t*, Soulgems_Category);
        ADD_GLOBAL("Scrolls_Category", 0, Reference_t*, Scrolls_Category);
        ADD_GLOBAL("Metals_Category", 0, Reference_t*, Metals_Category);
        ADD_GLOBAL("Leather_Category", 0, Reference_t*, Leather_Category);
        ADD_GLOBAL("Gems_Category", 0, Reference_t*, Gems_Category);
        ADD_GLOBAL("Clutter_Category", 0, Reference_t*, Clutter_Category);
        ADD_GLOBAL("Keys_Category", 0, Reference_t*, Keys_Category);
        ADD_GLOBAL("Misc_Category", 0, Reference_t*, Misc_Category);
        ADD_GLOBAL("Spell_Tomes_Category", 0, Reference_t*, Spell_Tomes_Category);
        ADD_GLOBAL("Recipes_Category", 0, Reference_t*, Recipes_Category);
        ADD_GLOBAL("A_Books_Category", 0, Reference_t*, A_Books_Category);
        ADD_GLOBAL("B_Books_Category", 0, Reference_t*, B_Books_Category);
        ADD_GLOBAL("C_Books_Category", 0, Reference_t*, C_Books_Category);
        ADD_GLOBAL("D_Books_Category", 0, Reference_t*, D_Books_Category);
        ADD_GLOBAL("E_Books_Category", 0, Reference_t*, E_Books_Category);
        ADD_GLOBAL("F_Books_Category", 0, Reference_t*, F_Books_Category);
        ADD_GLOBAL("G_Books_Category", 0, Reference_t*, G_Books_Category);
        ADD_GLOBAL("H_Books_Category", 0, Reference_t*, H_Books_Category);
        ADD_GLOBAL("I_Books_Category", 0, Reference_t*, I_Books_Category);
        ADD_GLOBAL("J_Books_Category", 0, Reference_t*, J_Books_Category);
        ADD_GLOBAL("K_Books_Category", 0, Reference_t*, K_Books_Category);
        ADD_GLOBAL("L_Books_Category", 0, Reference_t*, L_Books_Category);
        ADD_GLOBAL("M_Books_Category", 0, Reference_t*, M_Books_Category);
        ADD_GLOBAL("N_Books_Category", 0, Reference_t*, N_Books_Category);
        ADD_GLOBAL("O_Books_Category", 0, Reference_t*, O_Books_Category);
        ADD_GLOBAL("P_Books_Category", 0, Reference_t*, P_Books_Category);
        ADD_GLOBAL("Q_Books_Category", 0, Reference_t*, Q_Books_Category);
        ADD_GLOBAL("R_Books_Category", 0, Reference_t*, R_Books_Category);
        ADD_GLOBAL("S_Books_Category", 0, Reference_t*, S_Books_Category);
        ADD_GLOBAL("T_Books_Category", 0, Reference_t*, T_Books_Category);
        ADD_GLOBAL("U_Books_Category", 0, Reference_t*, U_Books_Category);
        ADD_GLOBAL("V_Books_Category", 0, Reference_t*, V_Books_Category);
        ADD_GLOBAL("W_Books_Category", 0, Reference_t*, W_Books_Category);
        ADD_GLOBAL("X_Books_Category", 0, Reference_t*, X_Books_Category);
        ADD_GLOBAL("Y_Books_Category", 0, Reference_t*, Y_Books_Category);
        ADD_GLOBAL("Z_Books_Category", 0, Reference_t*, Z_Books_Category);
        ADD_GLOBAL("Books_Category", 0, Reference_t*, Books_Category);

        // NPCP Reference Markers
        ADD_GLOBAL("Cell_Marker", 0, Reference_t*, Cell_Marker);
        ADD_GLOBAL("Expo_Antechamber_Marker", 0, Reference_t*, Expo_Antechamber_Marker);

        // NPCP Spells
        ADD_GLOBAL("Cell_Ability_Spell", 0, Spell_t*, Cell_Ability_Spell);

        #undef ADD_GLOBAL

        return true;
    }

}}}
