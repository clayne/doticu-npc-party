/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once
#undef TEXT

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    enum Flags : Int_t {
        NONE = 0,
        DISABLE = 1 << 0,
        HIDE = 1 << 1,
        UNMAP = 1 << 2,
    };

    enum class Cursor_Fill_Mode_e : Int_t {
        LEFT_TO_RIGHT = 1,
        TOP_TO_BOTTOM = 2,
    };

    enum class State_e : Int_t {
        DEFAULT = 0,
        RESET = 1,
        SLIDER = 2,
        MENU = 3,
        COLOR = 4,
    };

    enum class Option_Type_e : Int_t {
        EMPTY = 0,
        HEADER = 1,
        TEXT = 2,
        TOGGLE = 3,
        SLIDER = 4,
        MENU = 5,
        COLOR = 6,
        KEYMAP = 7,
        INPUT = 8,
    };

    class SKI_Config_Base_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

        static constexpr const char* JOURNAL_MENU = "Journal Menu";
        static constexpr const char* ROOT_MENU = "_root.ConfigPanelFader.configPanel";

    public:
        Object_t* Object();
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_Page_Name_Variable();
        Variable_t* Current_Page_Number_Variable();
        Variable_t* Current_State_Variable();
        Variable_t* Cursor_Position_Variable();
        Variable_t* Cursor_Fill_Mode_Variable();
        Variable_t* Flags_Variable();
        Variable_t* Labels_Variable();
        Variable_t* String_Values_Variable();
        Variable_t* Number_Values_Variable();
        Variable_t* States_Variable();
        Variable_t* Info_Text_Variable();
        Variable_t* Slider_Parameters_Variable(); // Array_t* of Float_t
        Variable_t* Menu_Parameters_Variable(); // Array_t* of Int_t

        String_t Current_Page_Name();
        Int_t Current_Page_Number();
        State_e Current_State();
        Int_t Cursor_Position();
        Cursor_Fill_Mode_e Cursor_Fill_Mode();
        Array_t* Flags();
        Array_t* Labels();
        Array_t* String_Values();
        Array_t* Number_Values();
        Array_t* States();

        void Cursor_Position(Int_t cursor_position);
        void Cursor_Fill_Mode(Cursor_Fill_Mode_e cursor_fill_mode);

        Int_t Pack_Flags(Int_t flags, Option_Type_e option_type);
        Int_t Pack_Option_ID(Int_t page_number, Int_t cursor_position);

        void Reset(); // ClearOptionBuffers

        void Title_Text(String_t title);

        String_t Info_Text();
        void Info_Text(String_t info);

        Int_t Add_Option(Option_Type_e option_type, String_t label, String_t string, Float_t number, Int_t flags);
        Int_t Add_Empty_Option();
        Int_t Add_Header_Option(String_t label, Int_t flags = 0);
        Int_t Add_Text_Option(String_t label, String_t value, Int_t flags = 0);
        Int_t Add_Toggle_Option(String_t label, Bool_t is_toggled, Int_t flags = 0);
        Int_t Add_Slider_Option(String_t label, Float_t value, String_t format = "{0}", Int_t flags = 0);
        Int_t Add_Menu_Option(String_t label, String_t value, Int_t flags = 0);
        Int_t Add_Color_Option(String_t label, Int_t color, Int_t flags = 0);
        Int_t Add_Keymap_Option(String_t label, Int_t key_code, Int_t flags = 0);
        Int_t Add_Input_Option(String_t label, String_t value, Int_t flags = 0);

        void Number_Option_Value(Int_t index, Float_t value, Bool_t do_render);
        void String_Option_Value(Int_t index, String_t value, Bool_t do_render);
        void Both_Option_Values(Int_t index, String_t string_value, Float_t number_value, Bool_t do_render);

        void Slider_Dialog_Current_Value(Float_t value);
        void Slider_Dialog_Default_Value(Float_t value);
        void Slider_Dialog_Range_Values(Float_t min, Float_t max);
        void Slider_Dialog_Interval_Value(Float_t value);
        void Menu_Dialog_Values(Vector_t<String_t> values);
        void Menu_Dialog_Default(Int_t index);

        void Text_Option_Value(Int_t option, String_t text, Bool_t do_render = true);
        void Toggle_Option_Value(Int_t option, Bool_t value, Bool_t do_render = true);
        void Slider_Option_Value(Int_t option, Float_t value, String_t format = "{0}", Bool_t do_render = true);
        void Menu_Option_Value(Int_t option, String_t value, Bool_t do_render = true);
        void Input_Option_Value(Int_t option, String_t value, Bool_t do_render = true);
        void Keymap_Option_Value(Int_t option, Int_t key_code, Bool_t do_render = true);

        void Option_Flags(Int_t option, Int_t flags, Bool_t do_render = true);

        void Show_Message(String_t message,
                          Bool_t allow_cancel = true,
                          String_t accept = "$Accept",
                          String_t cancel = "$Cancel",
                          Virtual_Callback_i** callback = nullptr);
        void Reset_Page();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

    class Main_t : public SKI_Config_Base_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Main_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        void Close_Menus(Virtual_Callback_i** callback = nullptr);
        void Enable(Int_t option, Bool_t do_render = true, Bool_t with_unmap = false);
        void Disable(Int_t option, Bool_t do_render = true);
        void Show(Int_t option, Bool_t do_render = true, Bool_t with_unmap = false);
        void Hide(Int_t option, Bool_t do_render = true);
        void Flicker(Int_t option);
        String_t Concat(const char* a, const char* b);
        String_t Concat(const char* a, const char* b, const char* c);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
