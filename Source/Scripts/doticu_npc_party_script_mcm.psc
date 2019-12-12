Scriptname doticu_npc_party_script_mcm extends SKI_ConfigBase

; Private Constants
doticu_npc_party_script_mcm_followers   p_MCM_FOLLOWERS = none
doticu_npc_party_script_mcm_members     p_MCM_MEMBERS   = none
doticu_npc_party_script_mcm_filter      p_MCM_FILTER    = none
doticu_npc_party_script_mcm_settings    p_MCM_SETTINGS  = none
string                                  p_STR_FOLLOWERS = "   Followers"
string                                  p_STR_MEMBERS   = "   Members"
string                                  p_STR_FILTER    = "   Filter"
string                                  p_STR_SETTINGS  = "   Settings"

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_MCM_FOLLOWERS = (self as Quest) as doticu_npc_party_script_mcm_followers
    p_MCM_MEMBERS = (self as Quest) as doticu_npc_party_script_mcm_members
    p_MCM_FILTER = (self as Quest) as doticu_npc_party_script_mcm_filter
    p_MCM_SETTINGS = (self as Quest) as doticu_npc_party_script_mcm_settings

    p_MCM_FOLLOWERS.f_Initialize(DATA)
    p_MCM_MEMBERS.f_Initialize(DATA)
    p_MCM_FILTER.f_Initialize(DATA)
    p_MCM_SETTINGS.f_Initialize(DATA)
endFunction

; Events
event OnConfigOpen()
    Pages = Utility.CreateStringArray(4, "")
    Pages[0] = p_STR_FOLLOWERS
    Pages[1] = p_STR_MEMBERS
    Pages[2] = p_STR_FILTER
    Pages[3] = p_STR_SETTINGS
endEvent

event OnPageReset(string str_page)
    if str_page == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_Build_Page()
    elseIf str_page == p_STR_MEMBERS
        p_MCM_MEMBERS.f_Build_Page()
    elseIf str_page == p_STR_FILTER
        p_MCM_FILTER.f_Build_Page()
    elseIf str_page == p_STR_SETTINGS
        p_MCM_SETTINGS.f_Build_Page()
    endIf
endEvent

event OnOptionSelect(int id_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Select(id_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Select(id_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Select(id_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Select(id_option)
    endIf
endEvent

event OnOptionMenuOpen(int id_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Menu_Open(id_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Menu_Open(id_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Menu_Open(id_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Menu_Open(id_option)
    endIf
endEvent

event OnOptionMenuAccept(int id_option, int idx_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Menu_Accept(id_option, idx_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Menu_Accept(id_option, idx_option)
    endIf
endEvent

event OnOptionInputAccept(int id_option, string str_input)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Input_Accept(id_option, str_input)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Input_Accept(id_option, str_input)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Input_Accept(id_option, str_input)
    endIf
endEvent

event OnOptionHighlight(int id_option)
    if CurrentPage == p_STR_FOLLOWERS
        p_MCM_FOLLOWERS.f_On_Option_Highlight(id_option)
    elseIf CurrentPage == p_STR_MEMBERS
        p_MCM_MEMBERS.f_On_Option_Highlight(id_option)
    elseIf CurrentPage == p_STR_FILTER
        p_MCM_FILTER.f_On_Option_Highlight(id_option)
    elseIf CurrentPage == p_STR_SETTINGS
        p_MCM_SETTINGS.f_On_Option_Highlight(id_option)
    endIf
endEvent
