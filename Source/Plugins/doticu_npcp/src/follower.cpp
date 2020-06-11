/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include <cmath>

#include "skse64/GameRTTI.h"

#include "actor_base2.h"
#include "actor2.h"
#include "cell.h"
#include "follower.h"
#include "member.h"
#include "object_ref.h"
#include "papyrus.h"
#include "utils.h"

namespace doticu_npcp { namespace Follower {

    Actor *Get_Actor(Follower_t *follower) {
        if (!follower) {
            return nullptr;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_ref_actor").As_Actor();
    }

    BGSBaseAlias *Get_Member(Follower_t *follower) {
        if (!follower) {
            return nullptr;
        }

        Papyrus::Handle hnd(kFormType_Alias, follower);
        return Papyrus::Value(&hnd, "p_ref_member").As_Alias();
    }

    Actor *Get_Horse(Follower_t *follower) {
        if (!follower) {
            return nullptr;
        }

        Papyrus::Handle handle(kFormType_Alias, follower);
        return Papyrus::Value(&handle, "p_ref_horse").As_Actor();
    }

    bool Is_Created(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_created").As_Bool();
    }

    bool Is_Alive(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        return Actor2::Is_Alive(Get_Actor(follower));
    }

    bool Is_Dead(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        return Actor2::Is_Dead(Get_Actor(follower));
    }

    bool Is_Mobile(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Mobile(member);
    }

    bool Is_Immobile(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Immobile(member);
    }

    bool Is_Settler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Settler(member);
    }

    bool Isnt_Settler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Settler(member);
    }

    bool Is_Paralyzed(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Paralyzed(member);
    }

    bool Isnt_Paralyzed(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Paralyzed(member);
    }

    bool Is_Mannequin(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Mannequin(member);
    }

    bool Isnt_Mannequin(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Mannequin(member);
    }

    bool Is_Sneak(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_sneak").As_Bool();
    }

    bool Isnt_Sneak(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return !Papyrus::Value(&hnd_alias, "p_is_sneak").As_Bool();
    }

    bool Is_Saddler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_saddler").As_Bool();
    }

    bool Isnt_Saddler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return !Papyrus::Value(&hnd_alias, "p_is_saddler").As_Bool();
    }

    bool Is_Retreater(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_retreater").As_Bool();
    }

    bool Isnt_Retreater(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return !Papyrus::Value(&hnd_alias, "p_is_retreater").As_Bool();
    }

    bool Exists(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        return Is_Created(follower) && Get_Actor(follower);
    }

    bool Is_Near_Player(Follower_t *follower) {
        if (follower) {

            Actor *follower_actor = Get_Actor(follower);
            if (follower_actor) {

                return Object_Ref::Is_Near_Player(follower_actor);
            }
        }
    }

    bool Isnt_Near_Player(Follower_t *follower) {
        if (follower) {

            Actor *follower_actor = Get_Actor(follower);
            if (follower_actor) {

                return !Object_Ref::Is_Near_Player(follower_actor);
            }
        }
    }

    void Summon(Follower_t *follower, float distance, float angle_degree) {
        Actor *follower_actor = Get_Actor(follower);
        if (follower_actor) {

            Actor *player_actor = *g_thePlayer;
            if (player_actor) {

                TESObjectCELL *player_cell = player_actor->parentCell;
                if (player_cell && Cell::Is_Interior(player_cell) || Isnt_Saddler(follower)) {

                    Actor2::Move_To_Orbit(follower_actor, player_actor, distance, angle_degree);
                } else {

                    Actor *follower_horse = Get_Horse(follower);
                    if (follower_horse) {

                        float saddler_distance = distance * 4;
                        Actor2::Move_To_Orbit(follower_horse, player_actor, saddler_distance, angle_degree);
                        Actor2::Move_To_Orbit(follower_actor, player_actor, saddler_distance, angle_degree - 10);
                    }
                }
            }
        }
    }

    void Summon_Behind(Follower_t *follower, float distance) {
        if (!follower) {
            return;
        }

        Actor *follower_actor = Get_Actor(follower);
        if (!follower_actor) {
            return;
        }

        Actor *player_actor = *g_thePlayer;
        if (!player_actor) {
            return;
        }

        Actor2::Move_To_Orbit(follower_actor, player_actor, distance, 180);
    }

    void Catch_Up(Follower_t *follower) {
        if (Exists(follower) && Is_Mobile(follower) && Isnt_Paralyzed(follower) && Isnt_Mannequin(follower)) {

            TESObjectCELL *player_cell = (*g_thePlayer)->parentCell;
            if (player_cell && Cell::Is_Interior(player_cell) || Isnt_Saddler(follower)) {

                if (Isnt_Near_Player(follower)) {

                    Summon_Behind(follower);
                }
            }
        }
    }

    void Level(Follower_t *follower) {
        enum {
            IS_WARRIOR = -381,
            IS_MAGE = -382,
            IS_ARCHER = -383
        };

        if (!follower) {
            return;
        }

        if (!Is_Created(follower)) {
            return;
        }

        Actor *follower_actor = Get_Actor(follower);
        if (!follower_actor) {
            return;
        }

        TESNPC *follower_base = DYNAMIC_CAST(follower_actor->baseForm, TESForm, TESNPC);
        if (!follower_base) {
            return;
        }

        Actor *player_actor = *g_thePlayer;
        if (!player_actor) {
            return;
        }

        const UInt16 player_level = CALL_MEMBER_FN(player_actor, GetLevel)();
        const SInt32 follower_style = Member::Get_Style(Get_Member(follower));
        const float player_modifier = 0.67f - (log((float)player_level) * 0.067f);
        const float player_level_modded = player_level * player_modifier;
        const float max_attribute = 1000.0f;
        const float min_attribute = 100.0f;
        const float max_skill = 100.0f;
        const float min_skill = 0.0f;

        #define GET_BASE_VALUE(NAME)                                            \
        (                                                                       \
            Actor_Base2::Get_Base_Actor_Value(follower_base, NAME) +            \
            Actor2::Get_Base_Actor_Value(player_actor, NAME) * player_modifier  \
        )

        float health = GET_BASE_VALUE("Health");
        float magicka = GET_BASE_VALUE("Magicka");
        float stamina = GET_BASE_VALUE("Stamina");

        float one_handed = GET_BASE_VALUE("OneHanded");
        float two_handed = GET_BASE_VALUE("TwoHanded");
        float block = GET_BASE_VALUE("Block");
        float heavy_armor = GET_BASE_VALUE("HeavyArmor");
        float light_armor = GET_BASE_VALUE("LightArmor");
        float smithing = GET_BASE_VALUE("Smithing");

        float destruction = GET_BASE_VALUE("Destruction");
        float restoration = GET_BASE_VALUE("Restoration");
        float conjuration = GET_BASE_VALUE("Conjuration");
        float alteration = GET_BASE_VALUE("Alteration");
        float illusion = GET_BASE_VALUE("Illusion");
        float enchanting = GET_BASE_VALUE("Enchanting");

        float marksman = GET_BASE_VALUE("Marksman");
        float sneak = GET_BASE_VALUE("Sneak");
        float alchemy = GET_BASE_VALUE("Alchemy");
        float lockpicking = GET_BASE_VALUE("Lockpicking");
        float pickpocket = GET_BASE_VALUE("Pickpocket");
        float speechcraft = GET_BASE_VALUE("Speechcraft");

        #undef GET_BASE_VALUE

        #define MOD_STRENGTH(OP, OPERAND)   \
        M                                   \
            one_handed  OP= (OPERAND);      \
            two_handed  OP= (OPERAND);      \
            block       OP= (OPERAND);      \
            heavy_armor OP= (OPERAND);      \
            light_armor OP= (OPERAND);      \
            smithing    OP= (OPERAND);      \
        W

        #define MOD_INTELLIGENCE(OP, OPERAND)   \
        M                                       \
            destruction OP= (OPERAND);          \
            restoration OP= (OPERAND);          \
            conjuration OP= (OPERAND);          \
            alteration  OP= (OPERAND);          \
            illusion    OP= (OPERAND);          \
            enchanting  OP= (OPERAND);          \
        W

        #define MOD_DEXTERITY(OP, OPERAND)  \
        M                                   \
            marksman    OP= (OPERAND);      \
            sneak       OP= (OPERAND);      \
            alchemy     OP= (OPERAND);      \
            lockpicking OP= (OPERAND);      \
            pickpocket  OP= (OPERAND);      \
            speechcraft OP= (OPERAND);      \
        W

        if (follower_style == IS_WARRIOR) {
            health += player_level * 4; // find a better equation
            MOD_STRENGTH(+, player_level_modded);
            MOD_INTELLIGENCE(-, player_level_modded);
            MOD_DEXTERITY(-, player_level_modded);
        } else if (follower_style == IS_MAGE) {
            magicka += player_level * 4; // find a better equation
            MOD_STRENGTH(-, player_level_modded);
            MOD_INTELLIGENCE(+, player_level_modded);
            MOD_DEXTERITY(-, player_level_modded);
        } else if (follower_style == IS_ARCHER) {
            stamina += player_level * 4; // find a better equation
            MOD_STRENGTH(-, player_level_modded);
            MOD_INTELLIGENCE(-, player_level_modded);
            MOD_DEXTERITY(+, player_level_modded);
        }

        #undef MOD_STRENGTH
        #undef MOD_INTELLIGENCE
        #undef MOD_DEXTERITY

        #define SET_ATTRIBUTE(NAME, VALUE)                  \
        (                                                   \
            Actor2::Set_Actor_Value(follower_actor, NAME,   \
                (VALUE) > max_attribute ? max_attribute :   \
                (VALUE) < min_attribute ? min_attribute :   \
                (VALUE)                                     \
            )                                               \
        )

        #define SET_SKILL(NAME, VALUE)                      \
        (                                                   \
            Actor2::Set_Actor_Value(follower_actor, NAME,   \
                (VALUE) > max_skill ? max_skill :           \
                (VALUE) < min_skill ? min_skill :           \
                (VALUE)                                     \
            )                                               \
        )

        SET_ATTRIBUTE("Health", health);
        SET_ATTRIBUTE("Magicka", magicka);
        SET_ATTRIBUTE("Stamina", stamina);

        SET_SKILL("OneHanded", one_handed);
        SET_SKILL("TwoHanded", two_handed);
        SET_SKILL("Block", block);
        SET_SKILL("HeavyArmor", heavy_armor);
        SET_SKILL("LightArmor", light_armor);
        SET_SKILL("Smithing", smithing);

        SET_SKILL("Destruction", destruction);
        SET_SKILL("Restoration", restoration);
        SET_SKILL("Conjuration", conjuration);
        SET_SKILL("Alteration", alteration);
        SET_SKILL("Illusion", illusion);
        SET_SKILL("Enchanting", enchanting);

        SET_SKILL("Marksman", marksman);
        SET_SKILL("Sneak", sneak);
        SET_SKILL("Alchemy", alchemy);
        SET_SKILL("Lockpicking", lockpicking);
        SET_SKILL("Pickpocket", pickpocket);
        SET_SKILL("Speechcraft", speechcraft);

        #undef SET_ATTRIBUTE
        #undef SET_SKILL
    }

    void Unlevel(Follower_t *follower) {
        if (!follower) {
            return;
        }

        if (!Is_Created(follower)) {
            return;
        }

        Actor *follower_actor = Get_Actor(follower);
        if (!follower_actor) {
            return;
        }

        TESNPC *follower_base = DYNAMIC_CAST(follower_actor->baseForm, TESForm, TESNPC);
        if (!follower_base) {
            return;
        }

        #define RESET_VALUE(NAME)                                       \
        (                                                               \
            Actor2::Set_Actor_Value(follower_actor, NAME,               \
                Actor_Base2::Get_Base_Actor_Value(follower_base, NAME)  \
            )                                                           \
        )

        RESET_VALUE("Health");
        RESET_VALUE("Magicka");
        RESET_VALUE("Stamina");

        RESET_VALUE("OneHanded");
        RESET_VALUE("TwoHanded");
        RESET_VALUE("Block");
        RESET_VALUE("HeavyArmor");
        RESET_VALUE("LightArmor");
        RESET_VALUE("Smithing");

        RESET_VALUE("Destruction");
        RESET_VALUE("Restoration");
        RESET_VALUE("Conjuration");
        RESET_VALUE("Alteration");
        RESET_VALUE("Illusion");
        RESET_VALUE("Enchanting");

        RESET_VALUE("Marksman");
        RESET_VALUE("Sneak");
        RESET_VALUE("Alchemy");
        RESET_VALUE("Lockpicking");
        RESET_VALUE("Pickpocket");
        RESET_VALUE("Speechcraft");

        #undef RESET_VALUE
    }

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction0 <Follower_t, void>(
                "p_Level",
                "doticu_npcp_follower",
                Follower::Level,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <Follower_t, void>(
                "p_Unlevel",
                "doticu_npcp_follower",
                Follower::Unlevel,
                registry)
        );

        return true;
    }

}}}
