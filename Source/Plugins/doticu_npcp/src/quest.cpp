/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"

#include "consts.h"
#include "object_ref.h"
#include "papyrus.h"
#include "papyrus.inl"
#include "quest.h"
#include "types.h"
#include "utils.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest) {
        if (!quest) {
            return "";
        }

        TESFullName *full_name = DYNAMIC_CAST(quest, TESQuest, TESFullName);
        if (!full_name || !full_name->name || !full_name->name.data) {
            return "";
        }

        return full_name->name.data;
    }

    bool Is_Alias_Filled(Quest_t* quest, UInt16 alias_id)
    {
        if (quest) {
            Quest_t2::Hash_Map_t* hash_map = (Quest_t2::Hash_Map_t*)((u8*)quest + 0x070);
            if (hash_map) {
                return hash_map->Has_Key(alias_id);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Actor_t* Alias_Actor(Quest_t* quest, UInt16 alias_id)
    {
        if (quest) {
            tArray<Reference_Handle_t>* promoted = (tArray<Reference_Handle_t>*)((u8*)quest + 0x250);
            if (promoted) {
                for (size_t idx = 0, count = promoted->count; idx < count; idx += 1) {
                    Reference_Handle_t handle = promoted->entries[idx];
                    Reference_t* reference = Object_Ref::From_Handle(handle);
                    if (reference) {
                        XAliases_t* xaliases = static_cast<XAliases_t*>
                            (reference->extraData.GetByType(kExtraData_AliasInstanceArray));
                        if (xaliases) {
                            for (size_t idx = 0, count = xaliases->aliases.count; idx < count; idx += 1) {
                                XAliases_t::AliasInfo* info = xaliases->aliases.entries[idx];
                                if (info && info->quest == quest && info->alias && info->alias->aliasId == alias_id) {
                                    return static_cast<Actor_t*>(reference);
                                }
                            }
                        }
                    }
                }
            }
        }

        return nullptr;
    }

    void Clear_Alias(Quest_t* quest, UInt16 alias_id)
    {
        using namespace Papyrus;

        NPCP_ASSERT(quest);
        NPCP_ASSERT(alias_id < quest->aliases.count);

        Alias_Reference_t* alias = reinterpret_cast<Alias_Reference_t*>
            (quest->aliases.entries[alias_id]);
        Virtual_Machine_t::Self()->Send_Event(alias, "Clear");

        // to do this manually would at minimum require that we clear the relevant data
        // on quest, which is from a hashmap and an array (at least) and we clear data
        // on the actor, like promoted ref and xaliases. but I'm not sure what else
        // there might be I don't know about. I still haven't found the actual function
        // in the executable. maybe it's nearby Alias_Reference_t instead of Quest_t,
        // like ForceToRef is.
    }

    void Log_Aliases(Quest_t* quest)
    {
        _MESSAGE("Start Log Aliases: %s {", Get_Name(quest));

        _MESSAGE("Hashmap");
        Quest_t2::Hash_Map_t* hash_map = (Quest_t2::Hash_Map_t*)((u8*)quest + 0x070);
        for (size_t idx = 0, count = hash_map->capacity; idx < count; idx += 1) {
            Quest_t2::Hash_Map_t::Entry_t* entry = hash_map->entries + idx;
            if (entry->chain != nullptr) {
                _MESSAGE("    idx: %zu, key: %u, value: %u", idx, entry->tuple.key, entry->tuple.value);
            }
        }

        _MESSAGE("Promoted");
        tArray<Reference_Handle_t>* arr = (tArray<Reference_Handle_t>*)((u8*)quest + 0x250);
        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            Reference_Handle_t handle = arr->entries[idx];
            if (handle) {
                Reference_t* reference = Object_Ref::From_Handle(handle);
                if (reference) {
                    XAliases_t* xaliases = static_cast<XAliases_t*>
                        (reference->extraData.GetByType(kExtraData_AliasInstanceArray));
                    if (xaliases) {
                        for (size_t idx1 = 0, count = xaliases->aliases.count; idx1 < count; idx1 += 1) {
                            if (xaliases->aliases.entries[idx1]->quest == quest) {
                                UInt16 alias_id = xaliases->aliases.entries[idx1]->alias->aliasId;
                                _MESSAGE("    idx: %zu, handle: %u, ref: %p, id: %u",
                                         idx, handle, reference, alias_id);
                            }
                        }
                    }
                }
            }
        }

        _MESSAGE("}");
    }

    Bool_t Start(Quest_t* quest)
    {
        static auto start = reinterpret_cast
            <Bool_t(*)(Quest_t*, Bool_t&, Bool_t)>
            (RelocationManager::s_baseAddr + Offsets::Quest::START);
        Bool_t b; // what is this for? a latent indicator?
        return start(quest, b, true);
    }

    /*void Start(Quest_t* quest)
    {
        Papyrus::Virtual_Machine_t::Self()->Call_Method(quest, "Quest", "Start", nullptr, nullptr);
    }*/

    void Log_Dialogue(Quest_t* quest)
    {
        if (quest) {
            auto log_topic = [](Quest_t* quest, Topic_t* topic, std::string indent = "")
            {
                if (topic) {
                    _MESSAGE((indent + "topic: %8.8X %s").c_str(), topic->formID, topic->Editor_ID());
                    Topic_Info_t** topic_infos = reinterpret_cast<Topic_Info_t**>(topic->unk2C);
                    for (size_t idx = 0, count = topic->unk50; idx < count; idx += 1) {
                        Topic_Info_t* topic_info = topic_infos[idx];
                        if (topic_info) {
                            _MESSAGE((indent + "    topic_info: %8.8X %s").c_str(), topic_info->formID, topic_info->Editor_ID());
                            Dialogue_Info_t dialogue_info(quest, topic, topic_info, nullptr);
                            for (auto it = dialogue_info.responses.Begin(); !it.End(); ++it) {
                                Dialogue_Response_t* response = it.Get();
                                if (response) {
                                    _MESSAGE((indent + "        %s").c_str(), response->text.Get());
                                }
                            }
                        }
                    }
                }
            };

            _MESSAGE("quest: %8.8X %s", quest->formID, quest->Editor_ID());
            for (size_t idx = 0, count = 2; idx < count; idx += 1) {
                using Branch_Map_t = Hash_Map_t<Branch_t*, tArray<Topic_t*>*>;
                Branch_Map_t& branch_tab = reinterpret_cast<Branch_Map_t&>(quest->unk118[idx]);
                for (size_t idx = 0, count = branch_tab.capacity; idx < count; idx += 1) {
                    Branch_Map_t::Entry_t* entry = branch_tab.entries + idx;
                    if (entry && entry->chain != nullptr) {
                        Branch_t* branch = entry->tuple.key;
                        tArray<Topic_t*>* topics = entry->tuple.value;
                        if (branch && topics) {
                            _MESSAGE("    branch: %8.8X %s", branch->formID, branch->Editor_ID());
                            for (size_t idx = 0, count = topics->count; idx < count; idx += 1) {
                                Topic_t* topic = *(topics->entries + idx);
                                log_topic(quest, topic, "        ");
                            }
                        }
                    }
                }
            }
            for (size_t idx = 0, count = 6; idx < count; idx += 1) {
                tArray<Topic_t*>& tab = reinterpret_cast<tArray<Topic_t*>&>(quest->unk178[idx]);
                if (tab.count > 0) {
                    if (idx == 0) {
                        _MESSAGE("    branch: SCENE");
                    } else if (idx == 1) {
                        _MESSAGE("    branch: COMBAT");
                    } else if (idx == 2) {
                        _MESSAGE("    branch: FAVORS");
                    } else if (idx == 3) {
                        _MESSAGE("    branch: DETECTION");
                    } else if (idx == 4) {
                        _MESSAGE("    branch: SERVICE");
                    } else if (idx == 5) {
                        _MESSAGE("    branch: MISC");
                    }
                    for (size_t idx = 0, count = tab.count; idx < count; idx += 1) {
                        log_topic(quest, tab[idx], "        ");
                    }
                }
            }
        }
    }

    void Log_Start_Enabled_Dialogue()
    {
        DataHandler* data_handler = DataHandler::GetSingleton();
        if (data_handler) {
            for (size_t idx = 0, count = data_handler->quests.count; idx < count; idx += 1) {
                Quest_t* quest = *(data_handler->quests.entries + idx);
                if (quest && quest->unk0D8.flags & (1 << 4)) {
                    Log_Dialogue(quest);
                }
            }
        }
    }

}}

namespace doticu_npcp { namespace Quest { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        return true;
    }

}}}
