/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"
#include "types.h"

namespace doticu_npcp {

    const IDebugLog g_log;
    const SKSEInterface* g_skse;
    const SKSEPapyrusInterface* g_papyrus;
    const SKSEMessagingInterface* g_messaging;
    PluginHandle g_plugin_handle;

}

namespace doticu_npcp { namespace Modules {

    using namespace Papyrus;

    class Main_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Main_t* Self();
        static Object_t* Object();
    public:
        Variable_t* Variable(String_t variable_name);

        Bool_t Is_Version_Less_Than(Int_t major,
                                    Int_t minor,
                                    Int_t patch,
                                    Int_t min_major,
                                    Int_t min_minor,
                                    Int_t min_patch);
        Bool_t Is_NPCP_Version_Less_Than(Int_t min_major,
                                         Int_t min_minor,
                                         Int_t min_patch);

        void Load_Mod();
        Bool_t Try_Update();
    public:
        static void Register_Me(Registry_t* registry);
    };

}}
