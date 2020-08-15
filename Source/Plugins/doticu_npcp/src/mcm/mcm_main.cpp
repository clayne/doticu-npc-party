/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "utils.h"

#include "mcm/mcm_main.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace MCM {

    String_t SKI_Config_Base_t::Class_Name()
    {
        static const String_t class_name = String_t("SKI_ConfigBase");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* SKI_Config_Base_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Object_t* SKI_Config_Base_t::Object()
    {
        Object_t* object = Object_t::Fetch(this, Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* SKI_Config_Base_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* SKI_Config_Base_t::Current_Page_Name_Variable() { DEFINE_VARIABLE("_currentPage"); }
    Variable_t* SKI_Config_Base_t::Current_Page_Number_Variable() { DEFINE_VARIABLE("_currentPageNum"); }
    Variable_t* SKI_Config_Base_t::Current_State_Variable() { DEFINE_VARIABLE("_state"); }
    Variable_t* SKI_Config_Base_t::Cursor_Position_Variable() { DEFINE_VARIABLE("_cursorPosition"); }
    Variable_t* SKI_Config_Base_t::Cursor_Fill_Mode_Variable() { DEFINE_VARIABLE("_cursorFillMode"); }
    Variable_t* SKI_Config_Base_t::Flags_Variable() { DEFINE_VARIABLE("_optionFlagsBuf"); }
    Variable_t* SKI_Config_Base_t::Labels_Variable() { DEFINE_VARIABLE("_textBuf"); }
    Variable_t* SKI_Config_Base_t::String_Values_Variable() { DEFINE_VARIABLE("_strValueBuf"); }
    Variable_t* SKI_Config_Base_t::Number_Values_Variable() { DEFINE_VARIABLE("_numValueBuf"); }
    Variable_t* SKI_Config_Base_t::States_Variable() { DEFINE_VARIABLE("_stateOptionMap"); }

    String_t SKI_Config_Base_t::Current_Page_Name()
    {
        return Current_Page_Name_Variable()->String();
    }

    Int_t SKI_Config_Base_t::Current_Page_Number()
    {
        return Current_Page_Number_Variable()->Int();
    }

    State_e SKI_Config_Base_t::Current_State()
    {
        return static_cast<State_e>(Current_State_Variable()->Int());
    }

    Int_t SKI_Config_Base_t::Cursor_Position()
    {
        return Cursor_Position_Variable()->Int();
    }

    Cursor_Fill_Mode_e SKI_Config_Base_t::Cursor_Fill_Mode()
    {
        return static_cast<Cursor_Fill_Mode_e>(Cursor_Fill_Mode_Variable()->Int());
    }

    Array_t* SKI_Config_Base_t::Flags()
    {
        return Flags_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::Labels()
    {
        return Labels_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::String_Values()
    {
        return String_Values_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::Number_Values()
    {
        return Number_Values_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::States()
    {
        return States_Variable()->Array();
    }

    void SKI_Config_Base_t::Cursor_Position(Int_t cursor_position)
    {
        NPCP_ASSERT(cursor_position < 128 && cursor_position >= -1);

        Cursor_Position_Variable()->Int(cursor_position);
    }

    void SKI_Config_Base_t::Cursor_Fill_Mode(Cursor_Fill_Mode_e cursor_fill_mode)
    {
        NPCP_ASSERT(cursor_fill_mode == Cursor_Fill_Mode_e::LEFT_TO_RIGHT ||
                    cursor_fill_mode == Cursor_Fill_Mode_e::TOP_TO_BOTTOM);

        Cursor_Fill_Mode_Variable()->Int(static_cast<Int_t>(cursor_fill_mode));
    }

    Int_t SKI_Config_Base_t::Pack_Flags(Int_t flags, Option_Type_e option_type)
    {
        return (flags * 0x100) + static_cast<Int_t>(option_type);
    }

    Int_t SKI_Config_Base_t::Pack_Option_ID(Int_t page_number, Int_t cursor_position)
    {
        return (page_number * 0x100) + cursor_position;
    }

    void SKI_Config_Base_t::Reset()
    {
        Array_t* flags = Flags();
        Array_t* labels = Labels();
        Array_t* strings = String_Values();
        Array_t* numbers = Number_Values();
        Array_t* states = States();

        for (size_t idx = 0, count = 128; idx < count; idx += 1) {
            flags->Point(idx)->Int(0);
            labels->Point(idx)->String("");
            strings->Point(idx)->String("");
            numbers->Point(idx)->Float(0.0f);
            states->Point(idx)->String("");
        }

        Cursor_Position(0);
        Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);
    }

    Int_t SKI_Config_Base_t::Add_Option(Option_Type_e option_type, String_t label, String_t string, Float_t number, Int_t flags)
    {
        NPCP_ASSERT(label);
        NPCP_ASSERT(string);
        NPCP_ASSERT(Current_State() == State_e::RESET);

        Int_t position = Cursor_Position();
        if (position != -1) {
            Flags()->Point(position)->Int(Pack_Flags(flags, option_type));
            Labels()->Point(position)->String(label);
            String_Values()->Point(position)->String(string);
            Number_Values()->Point(position)->Float(number);

            Int_t new_position = position + static_cast<Int_t>(Cursor_Fill_Mode());
            if (new_position >= 128) {
                Cursor_Position(-1);
            } else {
                Cursor_Position(new_position);
            }

            return Pack_Option_ID(Current_Page_Number(), position);
        } else {
            return -1;
        }
    }

    Int_t SKI_Config_Base_t::Add_Empty_Option()
    {
        return Add_Option(Option_Type_e::EMPTY, "", "", 0.0f, 0);
    }

    Int_t SKI_Config_Base_t::Add_Header_Option(String_t label, Int_t flags)
    {
        return Add_Option(Option_Type_e::HEADER, label, "", 0.0f, flags);
    }

    Int_t SKI_Config_Base_t::Add_Text_Option(String_t label, String_t value, Int_t flags)
    {
        return Add_Option(Option_Type_e::TEXT, label, value, 0.0f, flags);
    }

    Int_t SKI_Config_Base_t::Add_Toggle_Option(String_t label, Bool_t is_toggled, Int_t flags)
    {
        return Add_Option(Option_Type_e::TOGGLE, label, "", static_cast<Float_t>(is_toggled), flags);
    }

    Int_t SKI_Config_Base_t::Add_Slider_Option(String_t label, Float_t value, String_t format, Int_t flags)
    {
        return Add_Option(Option_Type_e::SLIDER, label, format, value, flags);
    }

    Int_t SKI_Config_Base_t::Add_Menu_Option(String_t label, String_t value, Int_t flags)
    {
        return Add_Option(Option_Type_e::MENU, label, value, 0.0f, flags);
    }

    Int_t SKI_Config_Base_t::Add_Color_Option(String_t label, Int_t color, Int_t flags)
    {
        return Add_Option(Option_Type_e::COLOR, label, "", static_cast<Float_t>(color), flags);
    }

    Int_t SKI_Config_Base_t::Add_Keymap_Option(String_t label, Int_t key_code, Int_t flags)
    {
        return Add_Option(Option_Type_e::KEYMAP, label, "", static_cast<Float_t>(key_code), flags);
    }

    void SKI_Config_Base_t::Register_Me(Registry_t* registry)
    {
        auto Reset = [](SKI_Config_Base_t* self)->void FORWARD_VOID(SKI_Config_Base_t::Reset());

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), MCM::SKI_Config_Base_t,      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("ClearOptionBuffers", 0, void, Reset);

        #undef ADD_METHOD
    }

}}

namespace doticu_npcp { namespace MCM {

    String_t Main_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Main_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Main_t* Main_t::Self()
    {
        return static_cast<Main_t*>(Consts::Control_Quest());
    }

    Object_t* Main_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Main_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    void Main_t::Set_Text_Option(Variable_t* option_in, String_t value, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);
        NPCP_ASSERT(value);

        struct Arguments : public Virtual_Arguments_t {
        public:
            Int_t option;
            String_t value;
            Bool_t dont_render;
            Arguments(Int_t option, String_t value, Bool_t dont_render) :
                option(option), value(value), dont_render(dont_render)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(3);
                arguments->At(0)->Int(option);
                arguments->At(1)->String(value);
                arguments->At(2)->Bool(dont_render);

                return true;
            }
        } arguments(option_in->Int(), value, !do_render);

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "SetTextOptionValue", &arguments);
    }

    void Main_t::Set_Option_Flags(Variable_t* option_in, Int_t flags, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);

        struct Arguments : public Virtual_Arguments_t {
        public:
            Int_t option;
            Int_t flags;
            Bool_t dont_render;
            Arguments(Int_t option, Int_t flags, Bool_t dont_render) :
                option(option), flags(flags), dont_render(dont_render)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(3);
                arguments->At(0)->Int(option);
                arguments->At(1)->Int(flags);
                arguments->At(2)->Bool(dont_render);

                return true;
            }
        } arguments(option_in->Int(), flags, !do_render);

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "SetOptionFlags", &arguments);
    }

    void Main_t::Enable_Option(Variable_t* option_in, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);
        Set_Option_Flags(option_in, MCM::NONE, do_render);
    }

    void Main_t::Disable_Option(Variable_t* option_in, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);
        Set_Option_Flags(option_in, MCM::DISABLE, do_render);
    }

    void Main_t::Register_Me(Registry_t* registry)
    {
        return;
    }

}}
