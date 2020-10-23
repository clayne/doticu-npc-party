/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameExtraData.h"
#include "skse64/GameForms.h"
#include "skse64/GameFormComponents.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PluginAPI.h"

#include "offsets.h"

namespace doticu_npcp {

    typedef uint8_t         u8;
    typedef uint16_t        u16;
    typedef uint32_t        u32;
    typedef uint64_t        u64;
    typedef int8_t          s8;
    typedef int16_t         s16;
    typedef int32_t         s32;
    typedef int64_t         s64;
    typedef int64_t         idx_t;

}

namespace doticu_npcp {

    typedef SInt32          Int_t;
    typedef BSFixedString   String_t;
    typedef float           Float_t;
    typedef bool            Bool_t;

    template <typename Key_t, typename Value_t>
    class Hash_Map_t {
    public:
        class Tuple_t {
        public:
            Key_t key;
            Value_t value;
        };

        class Entry_t {
        public:
            Tuple_t tuple;
            Entry_t* chain; // if nullptr, key is not in the table
        };

        UInt64 pad_00; // 00
        UInt32 pad_08; // 08
        UInt32 capacity; // 0C
        UInt32 free_count; // 10
        UInt32 free_idx; // 14
        Entry_t* end_of_chain; // 18
        UInt64 pad_20; // 20
        Entry_t* entries; // 28

        Bool_t Has_Key(Key_t key)
        {
            if (entries) {
                UInt32 idx = Utils::CRC32(key) & (capacity - 1);
                Entry_t* entry = entries + idx;
                if (entry && entry->chain != nullptr) {
                    for (; entry != end_of_chain; entry = entry->chain) {
                        if (entry->tuple.key == key) {
                            return true;
                        }
                    }
                    return false;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    };

    typedef UInt32          Form_Type_t;
    typedef UInt32          Reference_Handle_t;

    typedef TESForm         Form_t;
    typedef TESWorldSpace   Worldspace_t;
    typedef TESObjectCELL   Cell_t;
    typedef TESObjectREFR   Reference_t;
    typedef TESObjectMISC   Misc_t;
    typedef TESObjectSTAT   Static_t;
    typedef TESObjectWEAP   Weapon_t;
    typedef TESObjectARMO   Armor_t;
    typedef TESObjectCONT   Container_t;
    typedef BGSPerk         Perk_t;
    typedef TESEffectShader Effect_Shader_t;
    typedef TESLevCharacter Leveled_Actor_t;
    typedef TESLevItem      Leveled_Item_t;
    typedef BGSLocation     Location_t;
    typedef TESFaction      Faction_t;
    typedef BGSOutfit       Outfit_t;
    typedef BGSKeyword      Keyword_t;
    typedef EffectSetting   Magic_Effect_t;
    typedef ActiveEffect    Active_Magic_Effect_t;
    typedef SpellItem       Spell_t;
    typedef TESFurniture    Furniture_t;

    typedef Actor           Actor_t;
    typedef TESNPC          Actor_Base_t;
    typedef Character       Character_t;
    typedef PlayerCharacter Player_Character_t;

    typedef Projectile      Projectile_t;
    typedef BGSProjectile   Projectile_Base_t;

    typedef BGSListForm     Formlist_t;

    typedef TESQuest            Quest_t;

    typedef BGSDialogueBranch   Branch_t;

    class Topic_Info_t;
    class Topic_t : public Form_t {
    public:
        enum {
            kTypeID = kFormType_Topic
        };

        virtual ~Topic_t();

        TESFullName full_name; // 20

        UInt8 flags; // 30
        UInt8 type; // 31
        UInt16 subtype; // 32
        UInt32 priority_and_journal_index; // 34
        Branch_t* branch; // 38
        Quest_t* quest; // 40
        Topic_Info_t** topic_infos; // 48
        UInt32 topic_info_count; // 50
        String_t editor_id; // 58
    };
    STATIC_ASSERT(sizeof(Topic_t) == 0x60);

    class Topic_Info_t : public Form_t {
    public:
        enum {
            kTypeID = kFormType_TopicInfo
        };

        virtual ~Topic_Info_t();

        Topic_t* topic; // 20
        Topic_Info_t* shared; // 28 (I think)
        Condition* conditions; // 30
        UInt16 index; // 38 (to array on topic)
        Bool_t said_once; // 3A
        UInt8 favor_level; // 3B
        UInt16 flags; // 3C
        UInt16 hours_to_reset; // 3E
        UInt32 mod_info_offset; // 40
        UInt32 pad_44; // 44

        Bool_t Is_In_Quest(Quest_t* quest)
        {
            if (topic) {
                if (topic->quest) {
                    return topic->quest == quest;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        Bool_t Is_In_Branch(Branch_t* branch)
        {
            if (topic) {
                if (topic->branch) {
                    return topic->branch == branch;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        Bool_t Is_In_Topic(Topic_t* topic)
        {
            if (this->topic) {
                return this->topic == topic;
            } else {
                return false;
            }
        }

        Branch_t* Branch()
        {
            if (topic) {
                return topic->branch;
            } else {
                return nullptr;
            }
        }
    };
    STATIC_ASSERT(sizeof(Topic_Info_t) == 0x48);

    typedef TESContainer            BContainer_t;
    typedef TESContainer::Entry**   BEntries_t;
    typedef TESContainer::Entry     BEntry_t;

    typedef ExtendDataList          XLists_t;
    typedef BaseExtraList           XList_t;
    typedef BSExtraData             XData_t;
    typedef ExtraAliasInstanceArray XAliases_t;

    template <typename ...Arguments>
    struct Callback_t {
        virtual ~Callback_t() = default;
        virtual void operator()(Arguments...) = 0;
    };

    template <typename Type, size_t count_>
    struct Static_Array_t {
        size_t count = count_;
        Type data[count_];

        Static_Array_t() {}
    };

    using Int_Callback_t = Callback_t<Int_t>;

    class Reference_t2 {
    public:
    };

    // a lot of credit for deciphering these classes goes to Ryan-rsm-McKenzie of CommonLibSSE as well as the SKSE team
    class Actor_Base_Data_t : public BaseFormComponent {
    public:
        enum Flags : UInt32 {
            IS_FEMALE = 0,
            IS_ESSENTIAL = 1,
            FACE_PRESET = 2,
            RESPAWNS = 3,
            AUTO_STATS = 4,
            IS_UNIQUE = 5,
            // ...
            IS_PROTECTED = 11,
            // ...
            IS_GHOST = 29,
            // ...
        };

        UInt32 flags; // 08

        Bool_t Is_Unique();
        Bool_t Is_Ghost();
        Bool_t Is_Protected();
        Bool_t Is_Essential();

        void Protect();
        void Unprotect();
        void Essentialize();
        void Unessentialize();
    };

    enum class Actor_Value_t : UInt32 {
        AGGRESSION = 0,
        CONFIDENCE,
        ENERGY,
        MORALITY,
        MOOD,
        ASSISTANCE,
        ONE_HANDED,
        TWO_HANDED,
        MARKSMAN,
        BLOCK,
        SMITHING,
        HEAVY_ARMOR,
        LIGHT_ARMOR,
        PICKPOCKET,
        LOCKPICKING,
        SNEAK,
        ALCHEMY,
        SPEECHCRAFT,
        ALTERATION,
        CONJURATION,
        DESTRUCTION,
        ILLUSION,
        RESTORATION,
        ENCHANTING,
        HEALTH,
        MAGICKA,
        STAMINA,
        HEAL_RATE,
        MAGICKA_RATE,
        STAMINA_RATE,
        SPEED_MULT,
        INVENTORY_WEIGHT,
        CARRY_WEIGHT,
        CRITICAL_CHANCE,
        MELEE_DAMAGE,
        UNARMED_DAMAGE,
        MASS,
        VOICE_POINTS,
        VOICE_RATE,
        DAMAGE_RESIST,
        POISON_RESIST,
        RESIST_FIRE,
        RESIST_SHOCK,
        RESIST_FROST,
        RESIST_MAGIC,
        RESIST_DISEASE,
        UNKNOWN_46,
        UNKNOWN_47,
        UNKNOWN_48,
        UNKNOWN_49,
        UNKNOWN_50,
        UNKNOWN_51,
        UNKNOWN_52,
        PARALYSIS,
        INVISIBILITY,
        NIGHT_EYE,
        DETECT_LIFE_RANGE,
        WATER_BREATHING,
        WATER_WALKING,
        UNKNOWN_59,
        FAME,
        INFAMY,
        JUMPING_BONUS,
        WARD_POWER,
        RIGHT_ITEM_CHARGE,
        ARMOR_PERKS,
        SHIELD_PERKS,
        WARD_DEFLECTION,
        VARIABLE_01,
        VARIABLE_02,
        VARIABLE_03,
        VARIABLE_04,
        VARIABLE_05,
        VARIABLE_06,
        VARIABLE_07,
        VARIABLE_08,
        VARIABLE_09,
        VARIABLE_10,
        // ...
        WAITING_FOR_PLAYER = 95,
        // ...
        INVALID = 164
    };

    enum class Actor_Modifier_t : UInt32 {
        PERMANENT = 0,
        TEMPORARY = 1,
        DAMAGE = 2,
        INVALID = 3
    };

    class Actor_Value_Owner_t {
    public:
        virtual ~Actor_Value_Owner_t(); // 00
        virtual float Get_Actor_Value(Actor_Value_t value_type); // 01
        virtual float Get_Permanent_Actor_Value(Actor_Value_t value_type); // 02
        virtual float Get_Base_Actor_Value(Actor_Value_t value_type); // 03 (doesn't get the base actor, but its own base)
        virtual void Set_Base_Actor_Value(Actor_Value_t value_type, float value); // 04 (doesn't set the base actor, but its own base)
        virtual void Mod_Actor_Value(Actor_Value_t value_type, float value); // 05
        virtual void Restore_Actor_Value(Actor_Modifier_t modifier_type, Actor_Value_t value_type, float value); // 06
        virtual void Set_Actor_Value(Actor_Value_t value_type, float value); // 07
        virtual void Is_Player_Owner(); // 08
        //void* _vtbl; // 00
    };
    STATIC_ASSERT(sizeof(Actor_Value_Owner_t) == 0x08);

    class Actor_State_t : public IMovementState {
    public:
        virtual ~Actor_State_t();

        class State_t {
        public:
            Bool_t moving_back : 1;
            Bool_t moving_forward : 1;
            Bool_t moving_right : 1;
            Bool_t moving_left : 1;
            Bool_t unk_0_4 : 1;
            Bool_t unk_0_5 : 1;
            Bool_t walking : 1;
            Bool_t running : 1;

            Bool_t sprinting : 1;
            Bool_t sneaking : 1;
            Bool_t swimming : 1;

            Bool_t wip_2;
            Bool_t wip_3;
            Bool_t wip_4;
            Bool_t wip_5;
            Bool_t wip_6;
            Bool_t wip_7;
        };

        void Stop_Movement();

        State_t state;
    };
    STATIC_ASSERT(sizeof(Actor_State_t) == 0x10);

    class Actor_Equipper_t {
    public:
        static Actor_Equipper_t* Self();
    public:
        void Equip_Item(Actor_t* actor,
                        Form_t* form,
                        XList_t* xlist,
                        UInt32 count,
                        BGSEquipSlot* slot,
                        Bool_t do_queue,
                        Bool_t do_force,
                        Bool_t do_sounds,
                        Bool_t do_apply);
        Bool_t Unequip_Item(Actor_t* actor,
                            Form_t* form,
                            XList_t* xlist,
                            UInt32 count,
                            BGSEquipSlot* slot,
                            Bool_t do_queue,
                            Bool_t do_force,
                            Bool_t do_sounds,
                            Bool_t do_apply,
                            BGSEquipSlot* slot_to_replace);

        BGSEquipSlot* Right_Hand_Slot();
        BGSEquipSlot* Left_Hand_Slot();
        BGSEquipSlot* Either_Hand_Slot();
    };

    class Actor_t2 {
    public:
        enum Form_Flags : UInt32 {
            HASNT_HAVOK_COLLISION = 4, // checkout 29 on Character type
            IGNORES_FRIENDLY_HITS = 20,
            IS_INITIALLY_DISABLED = 27,
        };

        enum Flags_1 : UInt32 {
            PROCESS_AI              = 1,
            IS_DEAD                 = 11,
            RESET_AI                = 17,
            IS_PLAYER_TEAMMATE      = 26,
            IS_PARALYZED            = 31,
        };

        enum Flags_2 : UInt32 {
            IS_A_MOUNT              = 1,
            IS_MOUNT_OBSTRUCTED     = 2,
            IS_MOUNTING_ON_OFF      = 3,
            DOES_FAVORS             = 7,
            UPDATE_ANIMATION_GRAPH  = 8,
            CAN_SPEAK               = 13,
            FORCE_ANIMATION_UPDATE  = 17,
            IS_ESSENTIAL            = 18,
            IS_PROTECTED            = 19,
            HIDDEN_FROM_STEALTH_EYE = 26,
            IS_IMMOBILE             = 27,
            FORCE_ANIMATION_UPDATES = 29,
            IS_UNDERWATER           = 31,
        };

        enum Update_3D_Flags : UInt8 {
            MODEL_3D                = 0,
            SKIN_3D                 = 1,
            HEAD_3D                 = 2,
            FACE_3D                 = 3,
            SCALE_3D                = 4,
            SKELETON_3D             = 5,
            UNKNOWN_6               = 6,
            UNKNOWN_7               = 7,
        };
    };

    class Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_Alias
        };

        enum Flags : UInt32 {
            // ...
            IS_ESSENTIAL = 1 << 6,
            // ...
            IS_PROTECTED = 1 << 10,
            // ...
        };

        enum Fill_Types : UInt16 {
            CONDITION_FILL = 0,
            FORCED_FILL = 1
            // ...
        };

        virtual ~Alias_Base_t(); // 00
        virtual bool Load(TESFile* file); // 01
        virtual void Item(TESForm* form); // 02
        virtual String_t Type(); // 03

        // void* _vtbl; // 00
        String_t name; // 08
        Quest_t* quest; // 10
        UInt32 id; // 18
        UInt32 flags; // 1C
        UInt16 fill_type; // 20
        UInt16 pad_22; // 22
        UInt32 pad_24; // 24

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

    class Alias_Reference_t : public Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_ReferenceAlias,
        };

        struct Forced_Fill {
            Reference_Handle_t ref_handle; // this never seems to be there...
        };
        STATIC_ASSERT(sizeof(Forced_Fill) == 0x4);

        union Fill_u {
            UInt64 padding[3];
            Forced_Fill forced;
        };
        STATIC_ASSERT(sizeof(Fill_u) == 0x18);

        virtual ~Alias_Reference_t(); // 00
        virtual bool Load(TESFile* file) override; // 01
        virtual void Item(TESForm* form) override; // 02
        virtual String_t Type() override; // 03

        Fill_u fill; // 28
        void* conditions; // 40

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Reference_t) == 0x48);

    class Faction_Rank_t {
    public:
        Faction_t* faction;
        SInt8 rank;
        UInt8 pad[7];
    };
    STATIC_ASSERT(sizeof(Faction_Rank_t) == 0x10);

    class Quest_t2 : public BGSStoryManagerTreeForm {
    public:
        class Hash_Map_t {
        public:
            class Tuple_t {
            public:
                UInt16 key;
                UInt16 value; // unused in this hashmap!
            };

            class Entry_t {
            public:
                Tuple_t tuple;
                Entry_t* chain; // if nullptr, key is not in the table
            };

            UInt64 pad_00; // 00
            UInt32 pad_08; // 08
            UInt32 capacity; // 0C
            UInt32 free_count; // 10
            UInt32 free_idx; // 14
            Entry_t* end_of_chain; // 18
            UInt64 pad_20; // 20
            Entry_t* entries; // 28

            Bool_t Has_Key(UInt16 key);
        };
    };

    class Process_Lists_t {
    public:
        static Process_Lists_t* Self();
    public:
        void Stop_Combat_Alarm(Actor_t* actor, Bool_t dont_end_alarm = false);
    };

    class Global_t : public Form_t {
    public:
        enum {
            kTypeID = kFormType_Global,
        };

        enum Type : char {
            FLOAT = 'f',
            SHORT = 's',
            LONG = 'l',
        };
    public:
        virtual ~Global_t();

        BSString editor_id; // 20
        char type; // 30
        UInt8 pad_31; // 31
        UInt16 pad_32; // 32
        Float_t value; // 34 (static cast to other types)
    };
    STATIC_ASSERT(sizeof(Global_t) == 0x38);

    class Relationship_t : public Form_t {
    public:

        // interesting. maybe we can just enforce the relationship rank
        // and not save it. that way we don't have to back it up so seriously
        enum class Change_e : UInt32 {
            RELATIONSHIP = 1 << 1,
        };

        // are these accurate? Papyrus returns different values for GetRelationshipRank
        enum class Rank_e : UInt8 {
            LOVER = 0,
            ALLY = 1,
            CONFIDANT = 2,
            FRIEND = 3,
            ACQUAINTANCE = 4,
            RIVAL = 5,
            FOE = 6,
            ENEMY = 7,
            ARCHNEMESIS = 8,
        };

        virtual ~Relationship_t(); // 00

        Actor_Base_t* base_actor_1; // 20
        Actor_Base_t* base_actor_2; // 28
        BGSAssociationType* association; // 30
        Rank_e rank; // 38
        UInt8 unk_39; // 39
        UInt8 unk_3A; // 3A
        UInt8 flag_3B; // 3B
        UInt32 pad_3C; // 3C

        static const char* Rank_To_String(Rank_e rank);
        static Int_t To_Papyrus_Rank(Rank_e rank);
        static Rank_e From_Papyrus_Rank(Int_t rank);
    };
    STATIC_ASSERT(sizeof(Relationship_t) == 0x40);

    class Relationships_t {
    public:
        static Relationships_t* Self();

    public:
        Relationship_t::Rank_e Relationship_Rank(Form_t* form_1, Form_t* form_2);
        void Relationship_Rank(Form_t* form_1, Form_t* form_2, Relationship_t::Rank_e rank);
    };

    class Magic_Target_t {
    public:
        virtual ~Magic_Target_t(); // 00

        Bool_t Has_Magic_Effect(Magic_Effect_t* magic_effect);

        // bool HasMagicEffect(EffectSetting* a_effect);
    };

    class Menu_Manager_t {
    public:
        UInt8 unk[0x110];
        UnkArray menu_stack; // 0x110
    };
    STATIC_ASSERT(sizeof(Menu_Manager_t) == 0x110 + 0x18);

    class Dialogue_Response_t {
    public:
        enum class Emotion_e : UInt32 {
            NEUTRAL = 0,
            ANGER = 1,
            DISGUST = 2,
            FEAR = 3,
            SAD = 4,
            HAPPY = 5,
            SURPRISE = 6,
            PUZZLED = 7,
        };

        BSString text; // 00
        Emotion_e emotion; // 10
        UInt32 emotion_value; // 14
        BSFixedString voice_text; // 18
        TESIdleForm* speaker_idle; // 20
        TESIdleForm* listener_idle; // 28
        BGSSoundDescriptorForm* voice_sound; // 30
        Bool_t allow_emotion; // 38
        Bool_t has_sound_lip; // 39
        UInt16 pad_3A; // 3A
        UInt32 pad_3C; // 3C
    };
    STATIC_ASSERT(sizeof(Dialogue_Response_t) == 0x40);

    class Dialogue_Info_t {
    public:
        Dialogue_Info_t(Quest_t* quest, Topic_t* topic, Topic_Info_t* topic_info, Actor_t* speaker);

        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        tList<Dialogue_Response_t> responses; // 08
        void* current_response; // 18 (node in tList?)
        Topic_Info_t* topic_info; // 20
        Topic_t* topic; // 28
        Quest_t* quest; // 30
        Actor_t* speaker; // 38
        void* extra_response; // 40 (ExtraSayToTopicInfo)
    };

}

namespace doticu_npcp {

    typedef tArray<Faction_Rank_t>  BFaction_Ranks_t;
    typedef Faction_Rank_t          BFaction_Rank_t;
    typedef ExtraFactionChanges     XFactions_t;
    typedef tArray<Faction_Rank_t>  XFaction_Ranks_t;
    typedef Faction_Rank_t          XFaction_Rank_t;

    class ExtraCanTalkToPlayer : public BSExtraData {
    public:
        virtual ~ExtraCanTalkToPlayer();

        Bool_t can_talk; // 10
        UInt8 pad_11; // 11
        UInt16 pad_12; // 12
        UInt32 pad_14; // 14
    };

    class ExtraFlags : public BSExtraData {
    public:
        enum : UInt32 {
            BLOCKS_ACTIVATION = 0,
            BLOCKS_PLAYER_ACTIVATION = 1,
            // ...
        };

        virtual ~ExtraFlags();

        UInt32 flags; // 10
        UInt32 pad; // 14
    };

    class ExtraGhost : public BSExtraData {
    public:
        virtual ~ExtraGhost();

        Bool_t is_ghost; // 10
        UInt8 pad_11; // 11
        UInt16 pad_12; // 12
        UInt32 pad_14; // 14
    };

    class ExtraTextDisplay : public BSExtraData {
    public:
        virtual ~ExtraTextDisplay();

        enum {
            DEFAULT = -1,
            CUSTOM = -2,
        };

        String_t name; // 10
        BGSMessage* message; // 18
        Quest_t* owner; // 20
        SInt32 flag; // 28
        Float_t extra_health; // 2C
        UInt16 custom_length; // 30
        UInt16 pad_32; // 32
        UInt32 pad_34; // 34

        void Force_Rename(String_t new_name);
    };
    STATIC_ASSERT(sizeof(ExtraTextDisplay) == 0x38);

    class ExtraOutfitItem : public BSExtraData {
    public:
        virtual ~ExtraOutfitItem();

        UInt32 outfit_form_id; // 10
        UInt32 pad_0C; // 14
    };
    STATIC_ASSERT(sizeof(ExtraOutfitItem) == 0x18);

    enum class Soul_Level_e : UInt8 {
        NONE = 0,
        PETTY = 1,
        LESSER = 2,
        COMMON = 3,
        GREATER = 4,
        GRAND = 5,
    };

    class Extra_Soul_t : public BSExtraData {
    public:
        virtual ~Extra_Soul_t();

        Soul_Level_e soul_level; // 10
        UInt8 pad_11; // 11
        UInt16 pad_12; // 12
        UInt32 pad_14; // 14

        String_t Soul_Level_String()
        {
            switch (soul_level) {
                case (Soul_Level_e::PETTY): return "PETTY";
                case (Soul_Level_e::LESSER): return "LESSER";
                case (Soul_Level_e::COMMON): return "COMMON";
                case (Soul_Level_e::GREATER): return "GREATER";
                case (Soul_Level_e::GRAND): return "GRAND";
                default: return "NONE";
            };
        }
    };
    STATIC_ASSERT(sizeof(Extra_Soul_t) == 0x18);

    class Extra_Followers_t : public BSExtraData {
    public:
        class Follower_Info_t {
        public:
            Reference_Handle_t actor_handle; // 0
            Float_t follow_distance; // 4
        };
        STATIC_ASSERT(sizeof(Follower_Info_t) == 0x08);

        virtual ~Extra_Followers_t();

        tArray<Follower_Info_t> follower_infos; // 10
    };
    STATIC_ASSERT(sizeof(Extra_Followers_t) == 0x28);

    /* Packages */

    class Package_Value_t {
    public:
        virtual ~Package_Value_t();

        enum class Type_e {
            NONE,
            BOOL,
            INT,
            FLOAT,
            LOCATION,
            SINGLE_REFERENCE,
            TOPIC,
        };

        Type_e Type();
    };
    STATIC_ASSERT(sizeof(Package_Value_t) == 0x08);

    class Package_Bool_Value_t : public Package_Value_t {
    public:
        virtual ~Package_Bool_Value_t();

        UInt32 value; // 08
        UInt32 pad_0C; // 0C
    };
    STATIC_ASSERT(sizeof(Package_Bool_Value_t) == 0x10);

    class Package_Int_Value_t : public Package_Value_t {
    public:
        virtual ~Package_Int_Value_t();

        UInt64 pad_08; // 08
        Int_t value; // 10
        UInt32 pad_14; // 14
        void* unk_18; // 18
        UInt64 unk_20; // 20
        UInt64 unk_28; // 28
    };
    STATIC_ASSERT(sizeof(Package_Int_Value_t) == 0x30); // maybe 0x18

    class Package_Float_Value_t : public Package_Value_t {
    public:
        virtual ~Package_Float_Value_t();

        UInt64 pad_08; // 08
        Float_t value; // 10
        UInt32 pad_14; // 14
        void* unk_18; // 18
        UInt64 unk_20; // 20
        UInt64 unk_28; // 28
    };
    STATIC_ASSERT(sizeof(Package_Float_Value_t) == 0x30); // maybe 0x18

    class Package_Location_t;
    class Package_Location_Value_t : public Package_Value_t {
    public:
        virtual ~Package_Location_Value_t();

        UInt64 pad_08; // 08
        Package_Location_t* location; // 10
        void* unk_18; // 18
    };
    STATIC_ASSERT(sizeof(Package_Location_Value_t) == 0x20);

    class Package_Target_t;
    class Package_Single_Reference_Value_t : public Package_Value_t {
    public:
        virtual ~Package_Single_Reference_Value_t();

        UInt64 pad_08; // 08
        Package_Target_t* target; // 10
        void* unk_18; // 18
    };
    STATIC_ASSERT(sizeof(Package_Single_Reference_Value_t) == 0x20);

    class Package_t;
    class Package_Data_t {
    public:
        virtual ~Package_Data_t();

        Package_Value_t** values;
        void* data_10; // 10 Variable Size, probably an array or hashmap (** ptr to ptrs) repeats more among like packages
        UInt16 value_count; // 18
        UInt8 marker; // 1A XNAM
        UInt8 uint_1B; // 1B
        Bool_t bool_1C; // 1C
        UInt8 pad_1D; // 1D
        UInt16 pad_1E; // 1E
        void* shared_20; // 20 (connected with template. procedures or inputs)
        void* shared_28; // 28 (connected with template. procedures or inputs)
        Package_t* package_template; // 30
        UInt16 version; // 38
        UInt16 uint_3A; // 3A
        Bool_t bool_3C; // 3C
        UInt8 pad_3D; // 3D
        UInt16 pad_3E; // 3E
    };
    STATIC_ASSERT(sizeof(Package_Data_t) == 0x40);

    class Package_Location_t {
    public:
        virtual ~Package_Location_t();

        enum class Type_e : UInt8 {
            NEAR_REFERENCE = 0, // handle
            NEAR_SELF = 12, // nullptr
        };

        union Location_u {
            Reference_Handle_t handle;
            Form_t* form;
        };
        STATIC_ASSERT(sizeof(Location_u) == 0x08);

        Type_e type; // 08
        UInt8 pad_09; // 09
        UInt16 pad_0A; // 0A
        UInt32 radius; // 0C
        Location_u location; // 10
    };
    STATIC_ASSERT(sizeof(Package_Location_t) == 0x18);

    class Package_Target_t {
    public:
        enum class Type_e : UInt8 {
            SPECIFIC = 0, // Reference_handle_t
            FORM_ID = 1, // form_id. need to verify this isn't 5 instead.
            FORM_TYPE = 2, // form_type
            LINKED = 3, // Form_t*
            ALIAS_ID = 4, // alias_id
            UNKNOWN = 5, // unknown, interrupt flag?
            SELF = 6, // nullptr
        };

        union Target_u {
            Reference_Handle_t specific;
            UInt32 form_id;
            UInt32 form_type;
            Form_t* linked;
            UInt32 alias_id;
        };
        STATIC_ASSERT(sizeof(Target_u) == 0x08);

        Type_e type; // 00
        UInt8 pad_01; // 01
        UInt16 pad_02; // 02
        Target_u target; // 08
        Int_t count_or_distance; // 10
        UInt32 pad_14; // 14
    };
    STATIC_ASSERT(sizeof(Package_Target_t) == 0x18);

    class Package_Schedule_t {
    public:
        enum class Day_e : SInt8 {
            ANY = -1,
            SUNDAY = 0,
            MONDAY = 1,
            TUESDAY = 2,
            WEDNESDAY = 3,
            THURSDAY = 4,
            FRIDAY = 5,
            SATURDAY = 6,
            WEEKDAYS = 7,
            WEEKENDS = 8,
            MONDAY_WEDNESDAY_FRIDAY = 9,
            TUESDAY_THURSDAY = 10,
        };

        SInt8 month; // 00
        Day_e day; // 01
        SInt8 date; // 02
        SInt8 hour; // 03
        SInt8 minute; // 04
        SInt8 pad_05; // 05
        SInt8 pad_06; // 06
        SInt8 pad_07; // 07
        SInt32 duration_in_minutes; // 08
    };
    STATIC_ASSERT(sizeof(Package_Schedule_t) == 0x0C);

    class Package_t : public Form_t {
    public:
        enum {
            kTypeID = kFormType_Package,
        };

        enum class Type_e : UInt8 {
            FIND = 0,
            FOLLOWER,
            ESCORT,
            EAT,
            SLEEP,
            WANDER,
            TRAVEL,
            ACCOMPANY,
            USE_ITEM_AT,
            AMBUSH,
            FLEE_NOT_COMBAT,
            CAST_MAGIC,
            SANDBOX,
            PATROL,
            GUARD,
            DIALOGUE,
            USE_WEAPON,
            FIND_2,
            PACKAGE,
            PACKAGE_TEMPLATE,
            ACTIVATE,
            ALARM,
            FLEE,
            TRESPASS,
            SPECTATOR,
            REACT_TO_DEAD,
            GET_UP_FROM_CHAIR_OR_BED,
            DO_NOTHING,
            IN_GAME_DIALOGUE,
            SURFACE,
            SEARCH_FOR_ATTACKER,
            AVOID_PLAYER,
            REACT_TO_DESTROYED_OBJECT,
            REACT_TO_GRENADE_OR_MINE,
            STEAL_WARNING,
            PICK_POCKET_WARNING,
            MOVEMENT_BLOCKED,
            VAMPIRE_FEED,
            CANNIBAL
        };

        enum class General_Flag_e : UInt32 {
            OFFERS_SERVICES                 = 1 << 0,
            MUST_COMPLETE                   = 1 << 2,
            MAINTAIN_SPEED_AT_GOAL          = 1 << 3,
            UNLOCKS_DOORS_AT_PACKAGE_START  = 1 << 6,
            UNLOCKS_DOORS_AT_PACKAGE_END    = 1 << 7,
            CONTINUE_IF_PC_NEAR             = 1 << 9,
            ONLY_ONCE_PER_DAY               = 1 << 10,
            ALLOW_PREFERRED_SPEED           = 1 << 13,
            ALWAYS_SNEAK                    = 1 << 17,
            ALLOW_SWIMMING                  = 1 << 18,
            IGNORE_COMBAT                   = 1 << 20,
            HIDE_WEAPONS                    = 1 << 21,
            KEEP_WEAPONS_DRAWN              = 1 << 23,
            SKIP_COMBAT_ALERT               = 1 << 27,
            WEAR_SLEEP_OUTFIT               = 1 << 29,
        };

        enum class Interrupt_Flag_e : UInt16 {
            ALLOW_HELLOS_TO_PLAYER      = 1 << 0,
            ALLOW_HELLOS_TO_NPCS        = 1 << 1,
            OBSERVE_COMBAT_BEHAVIOR     = 1 << 2,
            INSPECT_CORPSE_BEHAVIOR     = 1 << 3,
            REACT_TO_PLAYER_ACTIONS     = 1 << 4,
            COMMENT_ON_FRIENDLY_FIRE    = 1 << 5,
            ALLOW_AGGRO_RADIUS_BEHAVIOR = 1 << 6,
            ALLOW_IDLE_CHATTER          = 1 << 7,
            ALLOW_WORLD_INTERACTIONS    = 1 << 9,
        };

        enum class Preferred_Speed_e : UInt8 {
            WALK        = 0,
            JOG         = 1,
            RUN         = 2,
            FAST_WALK   = 3,
        };

        virtual ~Package_t();

        virtual Bool_t Is_Actor_At_Location(Actor_t* actor, Bool_t arg_2, Float_t arg_3, Bool_t arg_4);
        virtual Bool_t Is_Actor_At_Location_2(Actor_t* actor_1, Actor_t* actor_2, Bool_t arg_3, Float_t arg_4, Bool_t arg_5);
        virtual Bool_t Is_Actor_At_Target(Actor_t* actor, SInt32 arg_2);
        virtual Bool_t Is_Target_At_Location(Actor_t* actor, SInt32 arg_2);
        virtual Bool_t Is_Package_Owner(Actor_t* actor);

        UInt32 flags; // 20
        Type_e type; // 24
        UInt8 interrupt_override; // 25
        Preferred_Speed_e preferred_speed; // 26
        UInt8 pad_27; // 27
        UInt16 interrupt_flags; // 28
        UInt16 other_flags; // 2A
        UInt32 pad_2C; // 2C
        Package_Data_t* data; // 30
        Package_Location_t* location; // 38
        Package_Target_t* target; // 40
        void* idles; // 48
        Package_Schedule_t schedule; // 50
        UInt32 pad_5C; // 5C
        void* conditions; // 60
        TESCombatStyle* combat_style; // 68
        Quest_t* quest; // 70
        UInt8 on_begin_event[0x20]; // 78
        UInt8 on_end_event[0x20]; // 98
        UInt8 on_change_event[0x20]; // B8
        UInt32 procedure_type; // D8
        UInt32 ref_count; // DC
    };
    STATIC_ASSERT(sizeof(Package_t) == 0xE0);

}

namespace doticu_npcp {

    typedef TESQuest                Consts_t;

    typedef StaticFunctionTag       Selfless_t;

}

namespace doticu_npcp { namespace Papyrus {

    typedef VMClassRegistry         Registry_t;
    typedef IObjectHandlePolicy     Policy_t;
    typedef UInt32                  Stack_ID_t;
    typedef VMScriptInstance        Script_t;
    typedef UInt64                  Type_e;
    typedef UInt32                  Type_ID_t;

    template <typename T> using Vector_t = VMResultArray<T>;
    typedef Vector_t<Int_t> Int_Vector_t;

    template <typename Type>
    struct Range_t {
        Type begin;
        Type end;
    };

}}
