; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_mcm extends SKI_ConfigBase

; Modules
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return doticu_npcp.Vars()
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return doticu_npcp.Members()
    endFunction
endProperty
doticu_npcp_keys property KEYS hidden
    doticu_npcp_keys function Get()
        return doticu_npcp.Control().KEYS
    endFunction
endProperty
doticu_npcp_mcm_followers property MCM_FOLLOWERS
    doticu_npcp_mcm_followers function Get()
        return (self as Quest) as doticu_npcp_mcm_followers
    endFunction
endProperty
doticu_npcp_mcm_members property MCM_MEMBERS
    doticu_npcp_mcm_members function Get()
        return (self as Quest) as doticu_npcp_mcm_members
    endFunction
endProperty
doticu_npcp_mcm_member property MCM_MEMBER
    doticu_npcp_mcm_member function Get()
        return (self as Quest) as doticu_npcp_mcm_member
    endFunction
endProperty
doticu_npcp_mcm_filter property MCM_FILTER
    doticu_npcp_mcm_filter function Get()
        return (self as Quest) as doticu_npcp_mcm_filter
    endFunction
endProperty
doticu_npcp_mcm_mannequins property MCM_MANNEQUINS
    doticu_npcp_mcm_mannequins function Get()
        return (self as Quest) as doticu_npcp_mcm_mannequins
    endFunction
endProperty
doticu_npcp_mcm_chests property MCM_CHESTS
    doticu_npcp_mcm_chests function Get()
        return (self as Quest) as doticu_npcp_mcm_chests
    endFunction
endProperty
doticu_npcp_mcm_settings property MCM_SETTINGS
    doticu_npcp_mcm_settings function Get()
        return (self as Quest) as doticu_npcp_mcm_settings
    endFunction
endProperty
doticu_npcp_mcm_hotkeys property MCM_HOTKEYS
    doticu_npcp_mcm_hotkeys function Get()
        return (self as Quest) as doticu_npcp_mcm_hotkeys
    endFunction
endProperty
doticu_npcp_mcm_log property MCM_LOG
    doticu_npcp_mcm_log function Get()
        return (self as Quest) as doticu_npcp_mcm_log
    endFunction
endProperty

; Public Constants
string property PAGE_FOLLOWERS      = " Followers "     autoReadOnly hidden
string property PAGE_MEMBERS        = " Members "       autoReadOnly hidden
string property PAGE_MANNEQUINS     = " Mannequins "    autoReadOnly hidden
string property PAGE_CHESTS         = " Chests "        autoReadOnly hidden
string property PAGE_FILTER         = " Filter "        autoReadOnly hidden
string property PAGE_SETTINGS       = " Settings "      autoReadOnly hidden
string property PAGE_HOTKEYS        = " Hotkeys "       autoReadOnly hidden
string property PAGE_LOG            = " Log "           autoReadOnly hidden

; Private Variables
bool                p_is_custom_page    = false
string              p_str_def_page      =    ""
string              p_str_curr_page     =    ""

; Native Methods
function Reset_Page() native

; Friend Methods
function f_Create()
    p_is_custom_page = false
    p_str_def_page = PAGE_SETTINGS; or a help page? or global stats page?
    p_str_curr_page = p_str_def_page
endFunction

function f_Change_Page(string str_page)
    p_str_curr_page = str_page
    p_is_custom_page = true
    Reset_Page()
endFunction

string function f_Get_Current_Page()
    return p_str_curr_page
endFunction

; Events
event OnConfigInit()
    ModName = " NPC Party"
endEvent

event OnConfigOpen()
    Pages = Utility.CreateStringArray(8, "")
    Pages[0] = PAGE_FOLLOWERS
    Pages[1] = PAGE_MEMBERS
    Pages[2] = PAGE_MANNEQUINS
    Pages[3] = PAGE_FILTER
    Pages[4] = PAGE_CHESTS
    Pages[5] = PAGE_SETTINGS
    Pages[6] = PAGE_HOTKEYS
    Pages[7] = PAGE_LOG
endEvent

event OnPageReset(string str_page)
    if str_page == ""
        ; open the last viewed page rather than a blank one
        str_page = p_str_curr_page
    endIf

    if p_is_custom_page
        ; override for programmatic page changes
        str_page = p_str_curr_page
        p_is_custom_page = false
    endIf

    if str_page == PAGE_FOLLOWERS
        p_str_curr_page = str_page
        MCM_FOLLOWERS.View_Followers()
        MCM_FOLLOWERS.On_Build_Page()
    elseIf str_page == PAGE_MEMBERS
        p_str_curr_page = str_page
        MCM_MEMBERS.View_Members()
        MCM_MEMBERS.On_Build_Page()
    elseIf str_page == PAGE_FILTER
        p_str_curr_page = str_page
        MCM_FILTER.On_Build_Page()
    elseIf str_page == PAGE_MANNEQUINS
        p_str_curr_page = str_page
        MCM_MANNEQUINS.View_Mannequins()
        MCM_MANNEQUINS.On_Build_Page()
    elseIf str_page == PAGE_CHESTS
        p_str_curr_page = str_page
        MCM_CHESTS.f_Build_Page()
    elseIf str_page == PAGE_SETTINGS
        p_str_curr_page = str_page
        MCM_SETTINGS.On_Build_Page()
    elseIf str_page == PAGE_HOTKEYS
        p_str_curr_page = str_page
        MCM_HOTKEYS.f_Build_Page()
    elseIf str_page == PAGE_LOG
        p_str_curr_page = str_page
        MCM_LOG.f_Build_Page()
    else
        p_str_curr_page = p_str_def_page
        Reset_Page()
    endIf
endEvent

event OnOptionSelect(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Select(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Select(id_option)
    endIf
endEvent

event OnOptionMenuOpen(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Menu_Open(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Menu_Open(id_option)
    endIf
endEvent

event OnOptionMenuAccept(int id_option, int idx_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endEvent

event OnOptionSliderOpen(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Slider_Open(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Slider_Open(id_option)
    endIf
endEvent

event OnOptionSliderAccept(int id_option, float float_value)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Slider_Accept(id_option, float_value)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Slider_Accept(id_option, float_value)
    endIf
endEvent

event OnOptionInputAccept(int id_option, string str_input)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endEvent

event OnOptionKeymapChange(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Keymap_Change(id_option, code_key, str_conflict_control, str_conflict_mod)
    endIf
endEvent

event OnOptionDefault(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Default(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Default(id_option)
    endIf
endEvent

event OnOptionHighlight(int id_option)
    if p_str_curr_page == PAGE_FOLLOWERS
        MCM_FOLLOWERS.On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_MEMBERS
        MCM_MEMBERS.On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_FILTER
        MCM_FILTER.On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_MANNEQUINS
        MCM_MANNEQUINS.On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_CHESTS
        MCM_CHESTS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_SETTINGS
        MCM_SETTINGS.On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_HOTKEYS
        MCM_HOTKEYS.f_On_Option_Highlight(id_option)
    elseIf p_str_curr_page == PAGE_LOG
        MCM_LOG.f_On_Option_Highlight(id_option)
    endIf
endEvent
