/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "utils.h"

#include "mcm/mcm_member.h"

#include "papyrus.inl"
#include "party.inl"

namespace doticu_npcp { namespace MCM {

    String_t Member_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_member");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Member_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Member_t* Member_t::Self()
    {
        return static_cast<Member_t*>(Consts::Control_Quest());
    }

    Object_t* Member_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Member_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Member_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Member_t::Party_Member_Variable() { DEFINE_VARIABLE("p_ref_member"); }

    Variable_t* Member_t::Unmember_Option_Variable() { DEFINE_VARIABLE("p_option_unmember"); }
    Variable_t* Member_t::Clone_Option_Variable() { DEFINE_VARIABLE("p_option_clone"); }
    Variable_t* Member_t::Unclone_Option_Variable() { DEFINE_VARIABLE("p_option_unclone"); }
    Variable_t* Member_t::Mobilize_Option_Variable() { DEFINE_VARIABLE("p_option_mobilize"); }
    Variable_t* Member_t::Immobilize_Option_Variable() { DEFINE_VARIABLE("p_option_immobilize"); }
    Variable_t* Member_t::Settle_Option_Variable() { DEFINE_VARIABLE("p_option_settle"); }
    Variable_t* Member_t::Resettle_Option_Variable() { DEFINE_VARIABLE("p_option_resettle"); }
    Variable_t* Member_t::Unsettle_Option_Variable() { DEFINE_VARIABLE("p_option_unsettle"); }
    Variable_t* Member_t::Enthrall_Option_Variable() { DEFINE_VARIABLE("p_option_enthrall"); }
    Variable_t* Member_t::Unthrall_Option_Variable() { DEFINE_VARIABLE("p_option_unthrall"); }
    Variable_t* Member_t::Paralyze_Option_Variable() { DEFINE_VARIABLE("p_option_paralyze"); }
    Variable_t* Member_t::Unparalyze_Option_Variable() { DEFINE_VARIABLE("p_option_unparalyze"); }
    Variable_t* Member_t::Stylize_Option_Variable() { DEFINE_VARIABLE("p_option_style"); }
    Variable_t* Member_t::Vitalize_Option_Variable() { DEFINE_VARIABLE("p_option_vitalize"); }
    Variable_t* Member_t::Outfit2_Option_Variable() { DEFINE_VARIABLE("p_option_outfit"); }
    Variable_t* Member_t::Pack_Option_Variable() { DEFINE_VARIABLE("p_option_pack"); }
    Variable_t* Member_t::Stash_Option_Variable() { DEFINE_VARIABLE("p_option_stash"); }
    Variable_t* Member_t::Summon_Option_Variable() { DEFINE_VARIABLE("p_option_summon"); }
    Variable_t* Member_t::Goto_Option_Variable() { DEFINE_VARIABLE("p_option_goto"); }
    Variable_t* Member_t::Rating_Option_Variable() { DEFINE_VARIABLE("p_option_rating"); }
    Variable_t* Member_t::Resurrect_Option_Variable() { DEFINE_VARIABLE("p_option_resurrect"); }
    Variable_t* Member_t::Rename_Option_Variable() { DEFINE_VARIABLE("p_option_rename"); }
    Variable_t* Member_t::Follow_Option_Variable() { DEFINE_VARIABLE("p_option_follow"); }
    Variable_t* Member_t::Unfollow_Option_Variable() { DEFINE_VARIABLE("p_option_unfollow"); }
    Variable_t* Member_t::Sneak_Option_Variable() { DEFINE_VARIABLE("p_option_sneak"); }
    Variable_t* Member_t::Unsneak_Option_Variable() { DEFINE_VARIABLE("p_option_unsneak"); }

    Variable_t* Member_t::Health_Attribute_Option_Variable() { DEFINE_VARIABLE("p_option_health"); }
    Variable_t* Member_t::Magicka_Attribute_Option_Variable() { DEFINE_VARIABLE("p_option_magicka"); }
    Variable_t* Member_t::Stamina_Attribute_Option_Variable() { DEFINE_VARIABLE("p_option_stamina"); }

    Variable_t* Member_t::One_Handed_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_one_handed"); }
    Variable_t* Member_t::Two_Handed_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_two_handed"); }
    Variable_t* Member_t::Block_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_block"); }
    Variable_t* Member_t::Heavy_Armor_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_heavy_armor"); }
    Variable_t* Member_t::Light_Armor_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_light_armor"); }
    Variable_t* Member_t::Smithing_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_smithing"); }

    Variable_t* Member_t::Destruction_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_destruction"); }
    Variable_t* Member_t::Restoration_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_restoration"); }
    Variable_t* Member_t::Conjuration_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_conjuration"); }
    Variable_t* Member_t::Alteration_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_alteration"); }
    Variable_t* Member_t::Illusion_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_illusion"); }
    Variable_t* Member_t::Enchanting_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_enchanting"); }

    Variable_t* Member_t::Marksman_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_marksman"); }
    Variable_t* Member_t::Sneak_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_sneak"); }
    Variable_t* Member_t::Alchemy_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_alchemy"); }
    Variable_t* Member_t::Lockpicking_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_lockpicking"); }
    Variable_t* Member_t::Pickpocket_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_pickpocket"); }
    Variable_t* Member_t::Speechcraft_Skill_Option_Variable() { DEFINE_VARIABLE("p_option_skill_speechcraft"); }

    Variable_t* Member_t::Race_Option_Variable() { DEFINE_VARIABLE("p_option_race"); }

    Party::Member_t* Member_t::Party_Member()
    {
        return static_cast<Party::Member_t*>(Party_Member_Variable()->Alias());
    }

    void Member_t::Build_Commands()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);

        mcm_main->Cursor_Position(4);
        mcm_main->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);

        mcm_main->Add_Header_Option("Commands: ");

        Summon_Option_Variable()->Int(mcm_main->Add_Text_Option(" Summon ", ""));
        Goto_Option_Variable()->Int(mcm_main->Add_Text_Option(" Goto ", ""));
        Pack_Option_Variable()->Int(mcm_main->Add_Text_Option(" Pack ", ""));
        Stash_Option_Variable()->Int(mcm_main->Add_Text_Option(" Stash ", ""));
        Outfit2_Option_Variable()->Int(mcm_main->Add_Menu_Option(" Outfit ", ""));

        if (party_member->Is_Mobile()) {
            Mobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Mobilize ", "", MCM::DISABLE));
            Immobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Immobilize ", ""));
        } else {
            Mobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Mobilize ", ""));
            Immobilize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Immobilize ", "", MCM::DISABLE));
        }

        if (party_member->Is_Settler()) {
            Settle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Settle ", "", MCM::DISABLE));
            Resettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resettle ", ""));
            Unsettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsettle ", ""));
        } else {
            Settle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Settle ", ""));
            Resettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resettle ", "", MCM::DISABLE));
            Unsettle_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsettle ", "", MCM::DISABLE));
        }

        if (party_member->Is_Paralyzed()) {
            Paralyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Paralyze ", "", MCM::DISABLE));
            Unparalyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unparalyze ", ""));
        } else {
            Paralyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Paralyze ", ""));
            Unparalyze_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unparalyze ", "", MCM::DISABLE));
        }

        if (party_member->Is_Follower()) {
            Follow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Follow ", "", MCM::DISABLE));
            Unfollow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unfollow ", ""));
            if (party_member->Is_Sneak()) {
                Sneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Sneak ", "", MCM::DISABLE));
                Unsneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsneak ", ""));
            } else {
                Sneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Sneak ", ""));
                Unsneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsneak ", "", MCM::DISABLE));
            }
        } else {
            Follow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Follow ", ""));
            Unfollow_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unfollow ", "", MCM::DISABLE));

            Sneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Sneak ", "", MCM::DISABLE));
            Unsneak_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unsneak ", "", MCM::DISABLE));
        }

        Rating_Option_Variable()->Int(mcm_main->Add_Text_Option(" Rating ", party_member->Rating_Stars()));

        Int_t style = party_member->Style();
        if (style == CODES::STYLE::DEFAULT) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Default "));
        } else if (style == CODES::STYLE::WARRIOR) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Warrior "));
        } else if (style == CODES::STYLE::MAGE) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Mage "));
        } else if (style == CODES::STYLE::ARCHER) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Archer "));
        } else if (style == CODES::STYLE::COWARD) {
            Stylize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Style ", " Coward "));
        } else {
            NPCP_ASSERT(false);
        }

        Int_t vitality = party_member->Vitality();
        if (vitality == CODES::VITALITY::MORTAL) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Mortal "));
        } else if (vitality == CODES::VITALITY::PROTECTED) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Protected "));
        } else if (vitality == CODES::VITALITY::ESSENTIAL) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Essential "));
        } else if (vitality == CODES::VITALITY::INVULNERABLE) {
            Vitalize_Option_Variable()->Int(mcm_main->Add_Text_Option(" Vitality ", " Invulnerable "));
        } else {
            NPCP_ASSERT(false);
        }

        if (party_member->Is_Alive()) {
            Resurrect_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resurrect ", "", MCM::DISABLE));
        } else {
            Resurrect_Option_Variable()->Int(mcm_main->Add_Text_Option(" Resurrect ", ""));
        }

        Clone_Option_Variable()->Int(mcm_main->Add_Text_Option(" Clone ", ""));
        if (party_member->Is_Clone()) {
            Unclone_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unclone ", ""));
        } else {
            Unclone_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unclone ", "", MCM::DISABLE));
        }

        if (party_member->Should_Unclone()) {
            Unmember_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unmember ", "", MCM::DISABLE));
        } else {
            Unmember_Option_Variable()->Int(mcm_main->Add_Text_Option(" Unmember ", ""));
        }
    }

    void Member_t::Update_Commands()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);

        mcm_main->Enable_Option(Summon_Option_Variable(), false);
        mcm_main->Enable_Option(Goto_Option_Variable(), false);
        mcm_main->Enable_Option(Pack_Option_Variable(), false);
        mcm_main->Enable_Option(Stash_Option_Variable(), false);
        mcm_main->Enable_Option(Outfit2_Option_Variable(), false);

        if (party_member->Is_Mobile()) {
            mcm_main->Disable_Option(Mobilize_Option_Variable(), false);
            mcm_main->Enable_Option(Immobilize_Option_Variable(), false);
        } else {
            mcm_main->Enable_Option(Mobilize_Option_Variable(), false);
            mcm_main->Disable_Option(Immobilize_Option_Variable(), false);
        }

        if (party_member->Is_Settler()) {
            mcm_main->Disable_Option(Settle_Option_Variable(), false);
            mcm_main->Enable_Option(Resettle_Option_Variable(), false);
            mcm_main->Enable_Option(Unsettle_Option_Variable(), false);
        } else {
            mcm_main->Enable_Option(Settle_Option_Variable(), false);
            mcm_main->Disable_Option(Resettle_Option_Variable(), false);
            mcm_main->Disable_Option(Unsettle_Option_Variable(), false);
        }

        if (party_member->Is_Paralyzed()) {
            mcm_main->Disable_Option(Paralyze_Option_Variable(), false);
            mcm_main->Enable_Option(Unparalyze_Option_Variable(), false);
        } else {
            mcm_main->Enable_Option(Paralyze_Option_Variable(), false);
            mcm_main->Disable_Option(Unparalyze_Option_Variable(), false);
        }

        if (party_member->Is_Follower()) {
            mcm_main->Disable_Option(Follow_Option_Variable(), false);
            mcm_main->Enable_Option(Unfollow_Option_Variable(), false);
            if (party_member->Is_Sneak()) {
                mcm_main->Disable_Option(Sneak_Option_Variable(), false);
                mcm_main->Enable_Option(Unsneak_Option_Variable(), false);
            } else {
                mcm_main->Enable_Option(Sneak_Option_Variable(), false);
                mcm_main->Disable_Option(Unsneak_Option_Variable(), false);
            }
        } else {
            mcm_main->Enable_Option(Follow_Option_Variable(), false);
            mcm_main->Disable_Option(Unfollow_Option_Variable(), false);

            mcm_main->Disable_Option(Sneak_Option_Variable(), false);
            mcm_main->Disable_Option(Unsneak_Option_Variable(), false);
        }

        mcm_main->Set_Text_Option(Rating_Option_Variable(), party_member->Rating_Stars(), false);

        Int_t style = party_member->Style();
        if (style == CODES::STYLE::DEFAULT) {
            mcm_main->Set_Text_Option(Stylize_Option_Variable(), " Default ", false);
        } else if (style == CODES::STYLE::WARRIOR) {
            mcm_main->Set_Text_Option(Stylize_Option_Variable(), " Warrior ", false);
        } else if (style == CODES::STYLE::MAGE) {
            mcm_main->Set_Text_Option(Stylize_Option_Variable(), " Mage ", false);
        } else if (style == CODES::STYLE::ARCHER) {
            mcm_main->Set_Text_Option(Stylize_Option_Variable(), " Archer ", false);
        } else if (style == CODES::STYLE::COWARD) {
            mcm_main->Set_Text_Option(Stylize_Option_Variable(), " Coward ", false);
        } else {
            NPCP_ASSERT(false);
        }

        Int_t vitality = party_member->Vitality();
        if (vitality == CODES::VITALITY::MORTAL) {
            mcm_main->Set_Text_Option(Vitalize_Option_Variable(), " Mortal ", false);
        } else if (vitality == CODES::VITALITY::PROTECTED) {
            mcm_main->Set_Text_Option(Vitalize_Option_Variable(), " Protected ", false);
        } else if (vitality == CODES::VITALITY::ESSENTIAL) {
            mcm_main->Set_Text_Option(Vitalize_Option_Variable(), " Essential ", false);
        } else if (vitality == CODES::VITALITY::INVULNERABLE) {
            mcm_main->Set_Text_Option(Vitalize_Option_Variable(), " Invulnerable ", false);
        } else {
            NPCP_ASSERT(false);
        }

        if (party_member->Is_Alive()) {
            mcm_main->Disable_Option(Resurrect_Option_Variable(), false);
        } else {
            mcm_main->Enable_Option(Resurrect_Option_Variable(), false);
        }

        mcm_main->Enable_Option(Clone_Option_Variable(), false);
        if (party_member->Is_Clone()) {
            mcm_main->Enable_Option(Unclone_Option_Variable(), false);
        } else {
            mcm_main->Disable_Option(Unclone_Option_Variable(), false);
        }

        if (party_member->Should_Unclone()) {
            mcm_main->Disable_Option(Unmember_Option_Variable(), false);
        } else {
            mcm_main->Enable_Option(Unmember_Option_Variable(), false);
        }

        mcm_main->Enable_Option(Rename_Option_Variable(), true);
    }

    void Member_t::Build_Statistics()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);
        Actor_t* actor = party_member->Actor();
        NPCP_ASSERT(actor);
        Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
        NPCP_ASSERT(values);

        mcm_main->Cursor_Position(5);
        mcm_main->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);

        mcm_main->Add_Header_Option("Statistics: ");

        auto build_stat = [&](Variable_t* variable, String_t text, Actor_Value_t actor_value) -> void
        {
            Int_t value = static_cast<Int_t>(values->Get_Actor_Value(actor_value));
            variable->Int(mcm_main->Add_Text_Option(text, std::to_string(value).c_str()));
        };

        build_stat(Health_Attribute_Option_Variable(), " Health ", Actor_Value_t::HEALTH);
        build_stat(Magicka_Attribute_Option_Variable(), " Magicka ", Actor_Value_t::MAGICKA);
        build_stat(Stamina_Attribute_Option_Variable(), " Stamina ", Actor_Value_t::STAMINA);

        build_stat(One_Handed_Skill_Option_Variable(), " One Handed ", Actor_Value_t::ONE_HANDED);
        build_stat(Two_Handed_Skill_Option_Variable(), " Two Handed ", Actor_Value_t::TWO_HANDED);
        build_stat(Block_Skill_Option_Variable(), " Block ", Actor_Value_t::BLOCK);
        build_stat(Heavy_Armor_Skill_Option_Variable(), " Heavy Armor ", Actor_Value_t::HEAVY_ARMOR);
        build_stat(Light_Armor_Skill_Option_Variable(), " Light Armor ", Actor_Value_t::LIGHT_ARMOR);
        build_stat(Smithing_Skill_Option_Variable(), " Smithing ", Actor_Value_t::SMITHING);

        build_stat(Destruction_Skill_Option_Variable(), " Destruction ", Actor_Value_t::DESTRUCTION);
        build_stat(Restoration_Skill_Option_Variable(), " Restoration ", Actor_Value_t::RESTORATION);
        build_stat(Conjuration_Skill_Option_Variable(), " Conjuration ", Actor_Value_t::CONJURATION);
        build_stat(Alteration_Skill_Option_Variable(), " Alteration ", Actor_Value_t::ALTERATION);
        build_stat(Illusion_Skill_Option_Variable(), " Illusion ", Actor_Value_t::ILLUSION);
        build_stat(Enchanting_Skill_Option_Variable(), " Enchanting ", Actor_Value_t::ENCHANTING);

        build_stat(Marksman_Skill_Option_Variable(), " Marksman ", Actor_Value_t::MARKSMAN);
        build_stat(Sneak_Skill_Option_Variable(), " Sneak ", Actor_Value_t::SNEAK);
        build_stat(Alchemy_Skill_Option_Variable(), " Alchemy ", Actor_Value_t::ALCHEMY);
        build_stat(Lockpicking_Skill_Option_Variable(), " Lockpicking ", Actor_Value_t::LOCKPICKING);
        build_stat(Pickpocket_Skill_Option_Variable(), " Pickpocket ", Actor_Value_t::PICKPOCKET);
        build_stat(Speechcraft_Skill_Option_Variable(), " Speechcraft ", Actor_Value_t::SPEECHCRAFT);

        Race_Option_Variable()->Int(mcm_main->Add_Text_Option(" Race ", party_member->Race()));
    }

    void Member_t::Update_Statistics()
    {
        MCM::Main_t* mcm_main = Main();
        NPCP_ASSERT(mcm_main);

        Party::Member_t* party_member = Party_Member();
        NPCP_ASSERT(party_member);
        Actor_t* actor = party_member->Actor();
        NPCP_ASSERT(actor);
        Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
        NPCP_ASSERT(values);

        auto update_stat = [&](Variable_t* variable, Actor_Value_t actor_value, Bool_t do_render) -> void
        {
            Int_t value = static_cast<Int_t>(values->Get_Actor_Value(actor_value));
            mcm_main->Set_Text_Option(variable, std::to_string(value).c_str(), do_render);
        };

        update_stat(Health_Attribute_Option_Variable(), Actor_Value_t::HEALTH, false);
        update_stat(Magicka_Attribute_Option_Variable(), Actor_Value_t::MAGICKA, false);
        update_stat(Stamina_Attribute_Option_Variable(), Actor_Value_t::STAMINA, false);

        update_stat(One_Handed_Skill_Option_Variable(), Actor_Value_t::ONE_HANDED, false);
        update_stat(Two_Handed_Skill_Option_Variable(), Actor_Value_t::TWO_HANDED, false);
        update_stat(Block_Skill_Option_Variable(), Actor_Value_t::BLOCK, false);
        update_stat(Heavy_Armor_Skill_Option_Variable(), Actor_Value_t::HEAVY_ARMOR, false);
        update_stat(Light_Armor_Skill_Option_Variable(), Actor_Value_t::LIGHT_ARMOR, false);
        update_stat(Smithing_Skill_Option_Variable(), Actor_Value_t::SMITHING, false);

        update_stat(Destruction_Skill_Option_Variable(), Actor_Value_t::DESTRUCTION, false);
        update_stat(Restoration_Skill_Option_Variable(), Actor_Value_t::RESTORATION, false);
        update_stat(Conjuration_Skill_Option_Variable(), Actor_Value_t::CONJURATION, false);
        update_stat(Alteration_Skill_Option_Variable(), Actor_Value_t::ALTERATION, false);
        update_stat(Illusion_Skill_Option_Variable(), Actor_Value_t::ILLUSION, false);
        update_stat(Enchanting_Skill_Option_Variable(), Actor_Value_t::ENCHANTING, false);

        update_stat(Marksman_Skill_Option_Variable(), Actor_Value_t::MARKSMAN, false);
        update_stat(Sneak_Skill_Option_Variable(), Actor_Value_t::SNEAK, false);
        update_stat(Alchemy_Skill_Option_Variable(), Actor_Value_t::ALCHEMY, false);
        update_stat(Lockpicking_Skill_Option_Variable(), Actor_Value_t::LOCKPICKING, false);
        update_stat(Pickpocket_Skill_Option_Variable(), Actor_Value_t::PICKPOCKET, false);
        update_stat(Speechcraft_Skill_Option_Variable(), Actor_Value_t::SPEECHCRAFT, false);

        mcm_main->Set_Text_Option(Race_Option_Variable(), party_member->Race(), true);
    }

    void Member_t::Register_Me(Registry_t* registry)
    {
        auto Build_Commands = [](Member_t* self)->void FORWARD_VOID(Member_t::Build_Commands());
        auto Update_Commands = [](Member_t* self)->void FORWARD_VOID(Member_t::Update_Commands());
        auto Build_Statistics = [](Member_t* self)->void FORWARD_VOID(Member_t::Build_Statistics());
        auto Update_Statistics = [](Member_t* self)->void FORWARD_VOID(Member_t::Update_Statistics());

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), MCM::Member_t,               \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("p_Build_Commands", 0, void, Build_Commands);
        ADD_METHOD("p_Update_Commands", 0, void, Update_Commands);
        ADD_METHOD("p_Build_Statistics", 0, void, Build_Statistics);
        ADD_METHOD("p_Update_Statistics", 0, void, Update_Statistics);

        #undef ADD_METHOD
    }

}}
