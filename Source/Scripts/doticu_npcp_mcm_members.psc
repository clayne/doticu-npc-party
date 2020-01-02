Scriptname doticu_npcp_mcm_members extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
    endFunction
endProperty
doticu_npcp_mcm property MCM hidden
    doticu_npcp_mcm function Get()
        return p_DATA.MODS.CONTROL.MCM
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA                  =  none

int                 p_VIEW_MEMBERS          =     0
int                 p_VIEW_MEMBER           =     1

int                 p_HEADERS_PER_PAGE      =     4
int                 p_MEMBERS_PER_PAGE      =    20

int                 p_COMMANDS_PER_MEMBER   =     4
int                 p_IDX_SUMMON            =     0
int                 p_IDX_FOLLOW            =     1
int                 p_IDX_IMMOBILIZE        =     2
int                 p_IDX_MORE              =     3

; Private Variables
bool                p_is_created            = false

int                 p_curr_view             =     0
int                 p_curr_page             =     0
int                 p_count_pages           =    -1
Alias[]             p_arr_aliases           =  none
doticu_npcp_member  p_ref_member            =  none
int                 p_idx_member            =    -1
int                 p_options_offset        =    -1

int                 p_option_rename         =    -1
int                 p_option_back           =    -1
int                 p_option_prev           =    -1
int                 p_option_next           =    -1

int                 p_option_pack           =    -1
int                 p_option_clone          =    -1
int                 p_option_unclone        =    -1
int                 p_option_unmember       =    -1

int                 p_option_health         =    -1
int                 p_option_magicka        =    -1
int                 p_option_stamina        =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Build_Page()
endFunction

function f_On_Option_Select(int id_option)
endFunction

function f_On_Option_Menu_Open(int id_option)
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
endFunction

function f_On_Option_Input_Accept(int id_option, string str_input)
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Highlight(int id_option)
endFunction

; Private Methods
int function p_Get_Idx_Entity(int id_option)
endFunction

int function p_Get_Idx_Command(int id_option, int idx_entity)
endFunction

; Private States
auto state p_STATE_MEMBERS
    function f_Build_Page()
        if p_curr_view == p_VIEW_MEMBER
            GotoState("p_STATE_MEMBER")
            f_Build_Page()
            return
        endIf

        MCM.SetCursorPosition(0)
        MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

        int count_members = MEMBERS.Get_Count()
        int max_members = MEMBERS.Get_Max()
        string str_count_members
        string str_count_pages
        if count_members == 0
            str_count_members = "Members: 0/" + max_members
            str_count_pages = "Page: 1/1"
            MCM.SetTitleText(str_count_members + ", " + str_count_pages)
            ; should add a no members option(s)
            return
        endIf

        p_count_pages = Math.Ceiling(count_members / (p_MEMBERS_PER_PAGE as float))
        str_count_members = "Members: " + count_members + "/" + max_members
        str_count_pages = "Page: " + (p_curr_page + 1) + "/" + p_count_pages
        MCM.SetTitleText(str_count_members + ", " + str_count_pages)

        if count_members > p_MEMBERS_PER_PAGE
            p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "")
            p_option_next = MCM.AddTextOption("                       Go to Next Page", "")
        else
            p_option_prev = MCM.AddTextOption("                     Go to Previous Page", "", MCM.OPTION_FLAG_DISABLED)
            p_option_next = MCM.AddTextOption("                       Go to Next Page", "", MCM.OPTION_FLAG_DISABLED)
        endIf
        p_options_offset = p_option_prev

        MCM.AddHeaderOption("")
        MCM.AddHeaderOption("")

        int idx_from = p_MEMBERS_PER_PAGE * p_curr_page
        int idx_to_ex = idx_from + p_MEMBERS_PER_PAGE
        int idx = 0
        p_arr_aliases = MEMBERS.Get_Aliases_Sorted(idx_from, idx_to_ex)
        while idx < p_arr_aliases.length
            doticu_npcp_member ref_member = p_arr_aliases[idx] as doticu_npcp_member
            MCM.AddMenuOption(ref_member.Get_Name(), "...")
            idx += 1
        endWhile
    endFunction

    int function p_Get_Idx_Entity(int id_option)
        return id_option - p_options_offset - p_HEADERS_PER_PAGE
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_prev
            if p_curr_page == 0
                p_curr_page = p_count_pages - 1
            else
                p_curr_page -= 1
            endIf
        elseIf id_option == p_option_next
            if p_curr_page == p_count_pages - 1
                p_curr_page = 0
            else
                p_curr_page += 1
            endIf
        endIf

        MCM.ForcePageReset()
    endFunction

    function f_On_Option_Menu_Open(int id_option)
        int idx_entity = p_Get_Idx_Entity(id_option)
        doticu_npcp_member ref_member = p_arr_aliases[idx_entity] as doticu_npcp_member
        string[] arr_options = Utility.CreateStringArray(p_COMMANDS_PER_MEMBER, "")

        arr_options[p_IDX_SUMMON] = " Summon "
        if ref_member.Is_Follower()
            arr_options[p_IDX_FOLLOW] = " Unfollow "
        else
            arr_options[p_IDX_FOLLOW] = " Follow "
        endIf
        if ref_member.Is_Immobile()
            arr_options[p_IDX_IMMOBILIZE] = " Mobilize "
        else
            arr_options[p_IDX_IMMOBILIZE] = " Immobilize "
        endIf
        arr_options[p_IDX_MORE] = " More... "

        MCM.SetMenuDialogOptions(arr_options)
    endFunction

    function f_On_Option_Menu_Accept(int id_option, int idx_option)
        int idx_entity = p_Get_Idx_Entity(id_option)
        doticu_npcp_member ref_member = p_arr_aliases[idx_entity] as doticu_npcp_member

        if idx_option == p_IDX_SUMMON
            ref_member.Summon()
        elseIf idx_option == p_IDX_FOLLOW
            if ref_member.Is_Follower()
                ref_member.Unfollow()
            else
                ref_member.Follow()
            endIf
        elseIf idx_option == p_IDX_IMMOBILIZE
            if ref_member.Is_Immobile()
                ref_member.Mobilize()
            else
                ref_member.Immobilize()
            endIf
        elseIf idx_option == p_IDX_MORE
            p_ref_member = ref_member
            p_idx_member = idx_entity
            p_curr_view = p_VIEW_MEMBER
            MCM.ForcePageReset()
        endIf
    endFunction
    
    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_prev
            MCM.SetInfoText("Go to the Previous Page")
        elseIf id_option == p_option_next
            MCM.SetInfoText("Go to the Next Page")
        else
            int idx_entity = p_Get_Idx_Entity(id_option)
            doticu_npcp_member ref_member = p_arr_aliases[idx_entity] as doticu_npcp_member
            string str_name = ref_member.Get_Name()
            MCM.SetInfoText("Opens the member menu for " + str_name)
            ; this should show more about the member, like race, gender, style, and stats!!!
            ; whether is dead, healthly, etc.
        endIf
    endFunction
endState

state p_STATE_MEMBER
    function f_Build_Page()
        if !p_ref_member || !p_ref_member.Exists()
            p_curr_view = p_VIEW_MEMBERS
        endIf
        if p_curr_view == p_VIEW_MEMBERS
            GotoState("p_STATE_MEMBERS")
            f_Build_Page()
            return
        endIf

        string str_member_name = p_ref_member.Get_Name()

        MCM.SetCursorPosition(0)
        MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

        MCM.SetTitleText("Member: " + str_member_name)

        p_option_rename = MCM.AddInputOption(str_member_name + " ", " Rename ")
        p_option_back = MCM.AddTextOption("                            Go Back", "")
        if MEMBERS.Get_Count() > 1
            p_option_prev = MCM.AddTextOption("                      Previous Member", "")
            p_option_next = MCM.AddTextOption("                        Next Member", "")
        else
            p_option_prev = MCM.AddTextOption("                      Previous Member", "", MCM.OPTION_FLAG_DISABLED)
            p_option_next = MCM.AddTextOption("                        Next Member", "", MCM.OPTION_FLAG_DISABLED)
        endIf

        MCM.SetCursorPosition(4)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

        MCM.AddHeaderOption("Commands: ")
        p_option_pack = MCM.AddTextOption(" Pack ", "")
        p_option_clone  = MCM.AddTextOption(" Clone ", "")
        if p_ref_member.Is_Clone()
            p_option_unclone  = MCM.AddTextOption(" Unclone ", "")
        else
            p_option_unclone  = MCM.AddTextOption(" Unclone ", "", MCM.OPTION_FLAG_DISABLED)
        endIf
        if !MEMBERS.Should_Unclone_Member(p_ref_member)
            p_option_unmember = MCM.AddTextOption(" Unmember ", "")
        else
            p_option_unmember = MCM.AddTextOption(" Unmember ", "", MCM.OPTION_FLAG_DISABLED)
        endIf

        MCM.SetCursorPosition(5)
        MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

        Actor ref_actor = p_ref_member.Get_Actor()
        MCM.AddHeaderOption("Statistics: ")
        p_option_health = MCM.AddTextOption(" Health: ", ref_actor.GetActorValue(CONSTS.STR_HEALTH) as int)
        p_option_magicka = MCM.AddTextOption(" Magicka: ", ref_actor.GetActorValue(CONSTS.STR_MAGICKA) as int)
        p_option_stamina = MCM.AddTextOption(" Stamina: ", ref_actor.GetActorValue(CONSTS.STR_STAMINA) as int)
    endFunction

    function f_On_Option_Select(int id_option)
        if id_option == p_option_back
            p_ref_member = none
            p_idx_member = -1
            p_curr_view = p_VIEW_MEMBERS
            MCM.ForcePageReset()
        elseIf id_option == p_option_prev
            if p_idx_member == 0
                p_idx_member = p_arr_aliases.length - 1
            else
                p_idx_member -= 1
            endIf
            p_ref_member = p_arr_aliases[p_idx_member] as doticu_npcp_member
            MCM.ForcePageReset()
        elseIf id_option == p_option_next
            if p_idx_member == p_arr_aliases.length - 1
                p_idx_member = 0
            else
                p_idx_member += 1
            endIf
            p_ref_member = p_arr_aliases[p_idx_member] as doticu_npcp_member
            MCM.ForcePageReset()
        elseIf id_option == p_option_pack
            FUNCS.Close_Menus()
            p_ref_member.Pack()
        elseIf id_option == p_option_clone
            p_ref_member.Clone()
        elseIf id_option == p_option_unclone
            p_ref_member.Unclone()
            p_ref_member = none
            p_idx_member = -1
            p_curr_view = p_VIEW_MEMBERS
            MCM.ForcePageReset()
        elseIf id_option == p_option_unmember
            p_ref_member.Unmember()
            p_ref_member = none
            p_idx_member = -1
            p_curr_view = p_VIEW_MEMBERS
            MCM.ForcePageReset()
        endIf
    endFunction

    function f_On_Option_Input_Accept(int id_option, string str_input)
        if id_option == p_option_rename
            if str_input != ""
                p_ref_member.Set_Name(str_input)
                MCM.ForcePageReset()
            endIf
        endIf
    endFunction

    function f_On_Option_Highlight(int id_option)
        if id_option == p_option_back
            MCM.SetInfoText("Go back to Members")
        elseIf id_option == p_option_prev
            MCM.SetInfoText("Go to the Previous Member")
        elseIf id_option == p_option_next
            MCM.SetInfoText("Go to the Next Member")
        elseIf id_option == p_option_pack
            MCM.SetInfoText("Pack items in this member's inventory.")
        elseIf id_option == p_option_rename
            MCM.SetInfoText("Rename this member.")
        elseIf id_option == p_option_clone
            MCM.SetInfoText("Clone this member.")
        elseIf id_option == p_option_unclone
            MCM.SetInfoText("Unclone and unmember this member.")
        elseIf id_option == p_option_unmember
            MCM.SetInfoText("Unmember this member.")
        endIf
    endFunction
endState
