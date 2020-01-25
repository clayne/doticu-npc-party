;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_mcm_member extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
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
doticu_npcp_data    p_DATA  =  none

string property p_STR_PLEASE_WAIT hidden
    string function Get()
        return " Please wait, sorting... "
    endFunction
endProperty

; Private Variables
bool                p_is_created                = false
int                 p_code_view                 =     0
doticu_npcp_member  p_ref_member                =  none

int                 p_option_rename             =    -1
int                 p_option_back               =    -1
int                 p_option_prev               =    -1
int                 p_option_next               =    -1

int                 p_option_summon             =    -1
int                 p_option_pack               =    -1
int                 p_option_outfit             =    -1
int                 p_option_settle             =    -1
int                 p_option_resettle           =    -1
int                 p_option_unsettle           =    -1
int                 p_option_enthrall           =    -1
int                 p_option_immobilize         =    -1
int                 p_option_mobilize           =    -1
int                 p_option_paralyze           =    -1
int                 p_option_unparalyze         =    -1
int                 p_option_follow             =    -1
int                 p_option_unfollow           =    -1
int                 p_option_sneak              =    -1
int                 p_option_unsneak            =    -1
int                 p_option_style              =    -1
int                 p_option_vitalize           =    -1
int                 p_option_relevel            =    -1
int                 p_option_resurrect          =    -1
int                 p_option_clone              =    -1
int                 p_option_unclone            =    -1
int                 p_option_unmember           =    -1

int                 p_option_health             =    -1
int                 p_option_magicka            =    -1
int                 p_option_stamina            =    -1
int                 p_option_skill_one_handed   =    -1
int                 p_option_skill_two_handed   =    -1
int                 p_option_skill_block        =    -1
int                 p_option_skill_heavy_armor  =    -1
int                 p_option_skill_light_armor  =    -1
int                 p_option_skill_smithing     =    -1
int                 p_option_skill_destruction  =    -1
int                 p_option_skill_restoration  =    -1
int                 p_option_skill_conjuration  =    -1
int                 p_option_skill_alteration   =    -1
int                 p_option_skill_illusion     =    -1
int                 p_option_skill_enchanting   =    -1
int                 p_option_skill_marksman     =    -1
int                 p_option_skill_sneak        =    -1
int                 p_option_skill_alchemy      =    -1
int                 p_option_skill_lockpicking  =    -1
int                 p_option_skill_pickpocket   =    -1
int                 p_option_skill_speechcraft  =    -1

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_code_view = 0
    p_ref_member = none
endFunction

function f_Destroy()
    p_ref_member = none
    p_code_view = 0
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

function f_Build_Page(int code_view, doticu_npcp_member ref_member)
    p_code_view = code_view
    p_ref_member = ref_member
    if !p_ref_member || !p_ref_member.Exists()
        if p_code_view == CODES.VIEW_MEMBER
            MCM.MCM_MEMBERS.f_View_Members()
            MCM.MCM_MEMBERS.f_Build_Page()
        elseIf p_code_view == CODES.VIEW_FOLLOWER
            MCM.MCM_FOLLOWERS.f_View_Followers()
            MCM.MCM_FOLLOWERS.f_Build_Page()
        endIf
        return
    endIf

    string str_member_name = p_ref_member.Get_Name()
    Actor ref_actor = p_ref_member.Get_Actor()

    MCM.SetCursorPosition(0)
    MCM.SetCursorFillMode(MCM.LEFT_TO_RIGHT)

    if p_code_view == CODES.VIEW_MEMBER
        MCM.SetTitleText("Member: " + str_member_name)
    elseIf p_code_view == CODES.VIEW_FOLLOWER
        MCM.SetTitleText("Follower: " + str_member_name)
    endIf

    p_option_rename = MCM.AddInputOption(str_member_name + " ", " Rename ")
    p_option_back = MCM.AddTextOption("                            Go Back", "")

    if p_code_view == CODES.VIEW_MEMBER
        if MEMBERS.Get_Count() > 1
            p_option_prev = MCM.AddTextOption("                      Previous Member", "")
            p_option_next = MCM.AddTextOption("                        Next Member", "")
        else
            p_option_prev = MCM.AddTextOption("                      Previous Member", "", MCM.OPTION_FLAG_DISABLED)
            p_option_next = MCM.AddTextOption("                        Next Member", "", MCM.OPTION_FLAG_DISABLED)
        endIf
    elseIf p_code_view == CODES.VIEW_FOLLOWER
        if FOLLOWERS.Get_Count() > 1
            p_option_prev = MCM.AddTextOption("                      Previous Follower", "")
            p_option_next = MCM.AddTextOption("                        Next Follower", "")
        else
            p_option_prev = MCM.AddTextOption("                      Previous Follower", "", MCM.OPTION_FLAG_DISABLED)
            p_option_next = MCM.AddTextOption("                        Next Follower", "", MCM.OPTION_FLAG_DISABLED)
        endIf
    endIf

    MCM.SetCursorPosition(4)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)

    MCM.AddHeaderOption("Commands: ")

    p_option_summon = MCM.AddTextOption(CONSTS.STR_MCM_SUMMON, "")

    p_option_pack = MCM.AddTextOption(CONSTS.STR_MCM_PACK, "")

    p_option_outfit = MCM.AddMenuOption(CONSTS.STR_MCM_OUTFIT, "")

    if p_ref_member.Is_Settler()
        p_option_settle = MCM.AddTextOption(CONSTS.STR_MCM_SETTLE, "", MCM.OPTION_FLAG_DISABLED)
        p_option_resettle = MCM.AddTextOption(CONSTS.STR_MCM_RESETTLE, "", MCM.OPTION_FLAG_NONE)
        p_option_unsettle = MCM.AddTextOption(CONSTS.STR_MCM_UNSETTLE, "", MCM.OPTION_FLAG_NONE)
    else
        p_option_settle = MCM.AddTextOption(CONSTS.STR_MCM_SETTLE, "", MCM.OPTION_FLAG_NONE)
        p_option_resettle = MCM.AddTextOption(CONSTS.STR_MCM_RESETTLE, "", MCM.OPTION_FLAG_DISABLED)
        p_option_unsettle = MCM.AddTextOption(CONSTS.STR_MCM_UNSETTLE, "", MCM.OPTION_FLAG_DISABLED)
    endif

    if p_ref_member.Is_Immobile()
        p_option_immobilize = MCM.AddTextOption(CONSTS.STR_MCM_IMMOBILIZE, "", MCM.OPTION_FLAG_DISABLED)
        p_option_mobilize = MCM.AddTextOption(CONSTS.STR_MCM_MOBILIZE, "", MCM.OPTION_FLAG_NONE)
    else
        p_option_immobilize = MCM.AddTextOption(CONSTS.STR_MCM_IMMOBILIZE, "", MCM.OPTION_FLAG_NONE)
        p_option_mobilize = MCM.AddTextOption(CONSTS.STR_MCM_MOBILIZE, "", MCM.OPTION_FLAG_DISABLED)
    endif

    if p_ref_member.Is_Paralyzed()
        p_option_paralyze = MCM.AddTextOption(CONSTS.STR_MCM_PARALYZE, "", MCM.OPTION_FLAG_DISABLED)
        p_option_unparalyze = MCM.AddTextOption(CONSTS.STR_MCM_UNPARALYZE, "", MCM.OPTION_FLAG_NONE)
    else
        p_option_paralyze = MCM.AddTextOption(CONSTS.STR_MCM_PARALYZE, "", MCM.OPTION_FLAG_NONE)
        p_option_unparalyze = MCM.AddTextOption(CONSTS.STR_MCM_UNPARALYZE, "", MCM.OPTION_FLAG_DISABLED)
    endif

    if p_ref_member.Is_Follower()
        p_option_follow = MCM.AddTextOption(CONSTS.STR_MCM_FOLLOW, "", MCM.OPTION_FLAG_DISABLED)
        p_option_unfollow = MCM.AddTextOption(CONSTS.STR_MCM_UNFOLLOW, "", MCM.OPTION_FLAG_NONE)

        if p_ref_member.Is_Sneak()
            p_option_sneak = MCM.AddTextOption(CONSTS.STR_MCM_SNEAK, "", MCM.OPTION_FLAG_DISABLED)
            p_option_unsneak = MCM.AddTextOption(CONSTS.STR_MCM_UNSNEAK, "", MCM.OPTION_FLAG_NONE)
        else
            p_option_sneak = MCM.AddTextOption(CONSTS.STR_MCM_SNEAK, "", MCM.OPTION_FLAG_NONE)
            p_option_unsneak = MCM.AddTextOption(CONSTS.STR_MCM_UNSNEAK, "", MCM.OPTION_FLAG_DISABLED)
        endIf

        p_option_relevel = MCM.AddTextOption(CONSTS.STR_MCM_RELEVEL, "", MCM.OPTION_FLAG_NONE)
    else
        p_option_follow = MCM.AddTextOption(CONSTS.STR_MCM_FOLLOW, "", MCM.OPTION_FLAG_NONE)
        p_option_unfollow = MCM.AddTextOption(CONSTS.STR_MCM_UNFOLLOW, "", MCM.OPTION_FLAG_DISABLED)
    endif

    if p_ref_member.Is_Dead()
        p_option_resurrect = MCM.AddTextOption(CONSTS.STR_MCM_RESURRECT, "", MCM.OPTION_FLAG_NONE)
    else
        p_option_resurrect = MCM.AddTextOption(CONSTS.STR_MCM_RESURRECT, "", MCM.OPTION_FLAG_DISABLED)
    endIf

    p_option_clone = MCM.AddTextOption(CONSTS.STR_MCM_CLONE, "")

    if p_ref_member.Is_Clone()
        p_option_unclone = MCM.AddTextOption(CONSTS.STR_MCM_UNCLONE, "")
    else
        p_option_unclone = MCM.AddTextOption(CONSTS.STR_MCM_UNCLONE, "", MCM.OPTION_FLAG_DISABLED)
    endIf

    if !MEMBERS.Should_Unclone_Member(p_ref_member)
        p_option_unmember = MCM.AddTextOption(CONSTS.STR_MCM_UNMEMBER, "")
    else
        p_option_unmember = MCM.AddTextOption(CONSTS.STR_MCM_UNMEMBER, "", MCM.OPTION_FLAG_DISABLED)
    endIf

    MCM.SetCursorPosition(5)
    MCM.SetCursorFillMode(MCM.TOP_TO_BOTTOM)
    
    MCM.AddHeaderOption("Statistics: ")

    p_option_health = MCM.AddTextOption(CONSTS.STR_MCM_HEALTH, ref_actor.GetActorValue(CONSTS.STR_HEALTH) as int)
    p_option_magicka = MCM.AddTextOption(CONSTS.STR_MCM_MAGICKA, ref_actor.GetActorValue(CONSTS.STR_MAGICKA) as int)
    p_option_stamina = MCM.AddTextOption(CONSTS.STR_MCM_STAMINA, ref_actor.GetActorValue(CONSTS.STR_STAMINA) as int)

    p_option_skill_one_handed = MCM.AddTextOption(CONSTS.STR_MCM_ONE_HANDED, ref_actor.GetActorValue(CONSTS.STR_ONE_HANDED) as int)
    p_option_skill_two_handed = MCM.AddTextOption(CONSTS.STR_MCM_TWO_HANDED, ref_actor.GetActorValue(CONSTS.STR_TWO_HANDED) as int)
    p_option_skill_block = MCM.AddTextOption(CONSTS.STR_MCM_BLOCK, ref_actor.GetActorValue(CONSTS.STR_BLOCK) as int)
    p_option_skill_heavy_armor = MCM.AddTextOption(CONSTS.STR_MCM_HEAVY_ARMOR, ref_actor.GetActorValue(CONSTS.STR_HEAVY_ARMOR) as int)
    p_option_skill_light_armor = MCM.AddTextOption(CONSTS.STR_MCM_LIGHT_ARMOR, ref_actor.GetActorValue(CONSTS.STR_LIGHT_ARMOR) as int)
    p_option_skill_smithing = MCM.AddTextOption(CONSTS.STR_MCM_SMITHING, ref_actor.GetActorValue(CONSTS.STR_SMITHING) as int)

    p_option_skill_destruction = MCM.AddTextOption(CONSTS.STR_MCM_DESTRUCTION, ref_actor.GetActorValue(CONSTS.STR_DESTRUCTION) as int)
    p_option_skill_restoration = MCM.AddTextOption(CONSTS.STR_MCM_RESTORATION, ref_actor.GetActorValue(CONSTS.STR_RESTORATION) as int)
    p_option_skill_conjuration = MCM.AddTextOption(CONSTS.STR_MCM_CONJURATION, ref_actor.GetActorValue(CONSTS.STR_CONJURATION) as int)
    p_option_skill_alteration = MCM.AddTextOption(CONSTS.STR_MCM_ALTERATION, ref_actor.GetActorValue(CONSTS.STR_ALTERATION) as int)
    p_option_skill_illusion = MCM.AddTextOption(CONSTS.STR_MCM_ILLUSION, ref_actor.GetActorValue(CONSTS.STR_ILLUSION) as int)
    p_option_skill_enchanting = MCM.AddTextOption(CONSTS.STR_MCM_ENCHANTING, ref_actor.GetActorValue(CONSTS.STR_ENCHANTING) as int)

    p_option_skill_marksman = MCM.AddTextOption(CONSTS.STR_MCM_MARKSMAN, ref_actor.GetActorValue(CONSTS.STR_MARKSMAN) as int)
    p_option_skill_sneak = MCM.AddTextOption(CONSTS.STR_MCM_SNEAK, ref_actor.GetActorValue(CONSTS.STR_SNEAK) as int)
    p_option_skill_alchemy = MCM.AddTextOption(CONSTS.STR_MCM_ALCHEMY, ref_actor.GetActorValue(CONSTS.STR_ALCHEMY) as int)
    p_option_skill_lockpicking = MCM.AddTextOption(CONSTS.STR_MCM_LOCKPICKING, ref_actor.GetActorValue(CONSTS.STR_LOCKPICKING) as int)
    p_option_skill_pickpocket = MCM.AddTextOption(CONSTS.STR_MCM_PICKPOCKET, ref_actor.GetActorValue(CONSTS.STR_PICKPOCKET) as int)
    p_option_skill_speechcraft = MCM.AddTextOption(CONSTS.STR_MCM_SPEECHCRAFT, ref_actor.GetActorValue(CONSTS.STR_SPEECHCRAFT) as int)
endFunction

function f_On_Option_Select(int id_option)
    Actor ref_actor = p_ref_member.Get_Actor()

    if false

    elseIf id_option == p_option_back
        p_Go_Back()
    elseIf id_option == p_option_prev
        if p_code_view == CODES.VIEW_MEMBER
            if MEMBERS.Will_Sort()
                MCM.SetTitleText(p_STR_PLEASE_WAIT)
            endIf
            MCM.MCM_MEMBERS.f_View_Member(MEMBERS.Get_Prev_Member(p_ref_member))
            MCM.ForcePageReset()
        elseIf p_code_view == CODES.VIEW_FOLLOWER
            if FOLLOWERS.Will_Sort()
                MCM.SetTitleText(p_STR_PLEASE_WAIT)
            endIf
            MCM.MCM_FOLLOWERS.f_View_Follower(FOLLOWERS.Get_Prev_Follower(p_ref_member.Get_Follower()))
            MCM.ForcePageReset()
        endIf
    elseIf id_option == p_option_next
        if p_code_view == CODES.VIEW_MEMBER
            if MEMBERS.Will_Sort()
                MCM.SetTitleText(p_STR_PLEASE_WAIT)
            endIf
            MCM.MCM_MEMBERS.f_View_Member(MEMBERS.Get_Next_Member(p_ref_member))
            MCM.ForcePageReset()
        elseIf p_code_view == CODES.VIEW_FOLLOWER
            if FOLLOWERS.Will_Sort()
                MCM.SetTitleText(p_STR_PLEASE_WAIT)
            endIf
            MCM.MCM_FOLLOWERS.f_View_Follower(FOLLOWERS.Get_Next_Follower(p_ref_member.Get_Follower()))
            MCM.ForcePageReset()
        endIf

    elseIf id_option == p_option_summon
        MCM.SetOptionFlags(p_option_summon, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Summon_Sync(ref_actor)
        MCM.SetOptionFlags(p_option_summon, MCM.OPTION_FLAG_NONE, false)
    elseIf id_option == p_option_pack
        MCM.SetOptionFlags(p_option_pack, MCM.OPTION_FLAG_DISABLED, false)
        FUNCS.Close_Menus()
        COMMANDS.Pack_Sync(ref_actor, false)

    elseIf id_option == p_option_settle
        COMMANDS.Settle_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_settle, MCM.OPTION_FLAG_DISABLED, true)
        MCM.SetOptionFlags(p_option_resettle, MCM.OPTION_FLAG_NONE, true)
        MCM.SetOptionFlags(p_option_unsettle, MCM.OPTION_FLAG_NONE, false)
    elseIf id_option == p_option_resettle
        MCM.SetOptionFlags(p_option_resettle, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Resettle_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_settle, MCM.OPTION_FLAG_DISABLED, true)
        MCM.SetOptionFlags(p_option_resettle, MCM.OPTION_FLAG_NONE, true)
        MCM.SetOptionFlags(p_option_unsettle, MCM.OPTION_FLAG_NONE, false)
    elseIf id_option == p_option_unsettle
        COMMANDS.Unsettle_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_settle, MCM.OPTION_FLAG_NONE, true)
        MCM.SetOptionFlags(p_option_resettle, MCM.OPTION_FLAG_DISABLED, true)
        MCM.SetOptionFlags(p_option_unsettle, MCM.OPTION_FLAG_DISABLED, false)

    elseIf id_option == p_option_immobilize
        COMMANDS.Immobilize_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_immobilize, MCM.OPTION_FLAG_DISABLED, true)
        MCM.SetOptionFlags(p_option_mobilize, MCM.OPTION_FLAG_NONE, false)
    elseIf id_option == p_option_mobilize
        COMMANDS.Mobilize_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_immobilize, MCM.OPTION_FLAG_NONE, true)
        MCM.SetOptionFlags(p_option_mobilize, MCM.OPTION_FLAG_DISABLED, false)

    elseIf id_option == p_option_paralyze
        COMMANDS.Paralyze_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_paralyze, MCM.OPTION_FLAG_DISABLED, true)
        MCM.SetOptionFlags(p_option_unparalyze, MCM.OPTION_FLAG_NONE, false)
    elseIf id_option == p_option_unparalyze
        COMMANDS.Unparalyze_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_paralyze, MCM.OPTION_FLAG_NONE, true)
        MCM.SetOptionFlags(p_option_unparalyze, MCM.OPTION_FLAG_DISABLED, false)

    elseIf id_option == p_option_follow
        COMMANDS.Follow_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_follow, MCM.OPTION_FLAG_DISABLED, true)
        MCM.SetOptionFlags(p_option_unfollow, MCM.OPTION_FLAG_NONE, false)
    elseIf id_option == p_option_unfollow
        MCM.SetOptionFlags(p_option_unfollow, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Unfollow_Sync(ref_actor, false)
        if p_code_view == CODES.VIEW_MEMBER
            MCM.SetOptionFlags(p_option_follow, MCM.OPTION_FLAG_NONE, true)
        elseIf p_code_view == CODES.VIEW_FOLLOWER
            p_Go_Back()
        endIf
    elseIf id_option == p_option_sneak
        COMMANDS.Sneak_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_sneak, MCM.OPTION_FLAG_DISABLED, true)
        MCM.SetOptionFlags(p_option_unsneak, MCM.OPTION_FLAG_NONE, false)
    elseIf id_option == p_option_unsneak
        COMMANDS.Unsneak_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_sneak, MCM.OPTION_FLAG_NONE, true)
        MCM.SetOptionFlags(p_option_unsneak, MCM.OPTION_FLAG_DISABLED, false)

    elseIf id_option == p_option_relevel
        MCM.SetOptionFlags(p_option_relevel, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Relevel_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_relevel, MCM.OPTION_FLAG_NONE, false)
        p_Update_Stats(ref_actor)
    
    elseIf id_option == p_option_resurrect
        MCM.SetOptionFlags(p_option_resurrect, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Resurrect_Sync(ref_actor, false)
        MCM.SetOptionFlags(p_option_resurrect, MCM.OPTION_FLAG_NONE, false)
        MCM.SetTextOptionValue(p_option_health, ref_actor.GetActorValue(CONSTS.STR_HEALTH) as int, true)
        MCM.SetTextOptionValue(p_option_magicka, ref_actor.GetActorValue(CONSTS.STR_MAGICKA) as int, true)
        MCM.SetTextOptionValue(p_option_stamina, ref_actor.GetActorValue(CONSTS.STR_STAMINA) as int, false)
    elseIf id_option == p_option_clone
        MCM.SetOptionFlags(p_option_clone, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Clone_Async(ref_actor)
        MCM.SetOptionFlags(p_option_clone, MCM.OPTION_FLAG_NONE, false)
        
    elseIf id_option == p_option_unclone
        MCM.SetOptionFlags(p_option_unclone, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Unclone_Sync(ref_actor)
        p_Go_Back()
    elseIf id_option == p_option_unmember
        MCM.SetOptionFlags(p_option_unmember, MCM.OPTION_FLAG_DISABLED, false)
        COMMANDS.Unmember_Sync(ref_actor)
        p_Go_Back()
    endIf
endFunction

function f_On_Option_Menu_Open(int id_option)
    if id_option == p_option_outfit
        if ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
            string[] arr_options = Utility.CreateStringArray(6, "")

            arr_options[0] = CONSTS.STR_MCM_CURRENT
            arr_options[1] = CONSTS.STR_MCM_MEMBER
            arr_options[2] = CONSTS.STR_MCM_SETTLER
            arr_options[3] = CONSTS.STR_MCM_THRALL
            arr_options[4] = CONSTS.STR_MCM_FOLLOWER
            arr_options[5] = CONSTS.STR_MCM_IMMOBILE

            MCM.SetMenuDialogOptions(arr_options)
        else
            string[] arr_options = Utility.CreateStringArray(5, "")

            arr_options[0] = CONSTS.STR_MCM_CURRENT
            arr_options[1] = CONSTS.STR_MCM_MEMBER
            arr_options[2] = CONSTS.STR_MCM_SETTLER
            arr_options[3] = CONSTS.STR_MCM_FOLLOWER
            arr_options[4] = CONSTS.STR_MCM_IMMOBILE

            MCM.SetMenuDialogOptions(arr_options)
        endIf
    endIf
endFunction

function f_On_Option_Menu_Accept(int id_option, int idx_option)
    Actor ref_actor = p_ref_member.Get_Actor()

    if id_option == p_option_outfit
        if ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
            if idx_option == 0
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Current_Sync(ref_actor, false)
            elseIf idx_option == 1
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Member_Sync(ref_actor, false)
            elseIf idx_option == 2
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Settler_Sync(ref_actor, false)
            elseIf idx_option == 3
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Thrall_Sync(ref_actor, false)
            elseIf idx_option == 4
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Follower_Sync(ref_actor, false)
            elseIf idx_option == 5
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Immobile_Sync(ref_actor, false)
            endIf
        else
            if idx_option == 0
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Current_Sync(ref_actor, false)
            elseIf idx_option == 1
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Member_Sync(ref_actor, false)
            elseIf idx_option == 2
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Settler_Sync(ref_actor, false)
            elseIf idx_option == 3
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Follower_Sync(ref_actor, false)
            elseIf idx_option == 4
                FUNCS.Close_Menus()
                COMMANDS.Outfit_Immobile_Sync(ref_actor, false)
            endIf
        endIf
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
    if false

    elseIf id_option == p_option_rename
        MCM.SetInfoText("Rename this member.")
    elseIf id_option == p_option_back
        MCM.SetInfoText("Go back to Members")
    elseIf id_option == p_option_prev
        MCM.SetInfoText("Go to the Previous Member")
    elseIf id_option == p_option_next
        MCM.SetInfoText("Go to the Next Member")

    elseIf id_option == p_option_pack
        MCM.SetInfoText("Pack items in this member's inventory.")
    elseIf id_option == p_option_outfit
        MCM.SetInfoText("Choose what this npc will wear in one of their outfits.")

    elseIf id_option == p_option_settle
        MCM.SetInfoText("Settle " + p_ref_member.Get_Name())
    elseIf id_option == p_option_resettle
        MCM.SetInfoText("Resettle " + p_ref_member.Get_Name())
    elseIf id_option == p_option_unsettle
        MCM.SetInfoText("Unsettle " + p_ref_member.Get_Name())

    elseIf id_option == p_option_immobilize
        MCM.SetInfoText("Immobilize " + p_ref_member.Get_Name())
    elseIf id_option == p_option_mobilize
        MCM.SetInfoText("Mobilize " + p_ref_member.Get_Name())

    elseIf id_option == p_option_paralyze
        MCM.SetInfoText("Paralyze " + p_ref_member.Get_Name())
    elseIf id_option == p_option_unparalyze
        MCM.SetInfoText("Unparalyze " + p_ref_member.Get_Name())

    elseIf id_option == p_option_follow
        MCM.SetInfoText("Have " + p_ref_member.Get_Name() + " follow you.")
    elseIf id_option == p_option_unfollow
        MCM.SetInfoText("Have " + p_ref_member.Get_Name() + " stop following you.")
    
    elseIf id_option == p_option_sneak
        MCM.SetInfoText("Have " + p_ref_member.Get_Name() + " sneak.")
    elseIf id_option == p_option_sneak
        MCM.SetInfoText("Have " + p_ref_member.Get_Name() + " stop sneaking.")

    elseIf id_option == p_option_clone
        MCM.SetInfoText("Clone this member.")
    elseIf id_option == p_option_unclone
        MCM.SetInfoText("Unclone and unmember this member.")
    elseIf id_option == p_option_unmember
        MCM.SetInfoText("Unmember this member.")

    endIf
endFunction

function f_On_Option_Slider_Open(int id_option)
endFunction

function f_On_Option_Slider_Accept(int id_option, float float_value)
endFunction

function f_On_Option_Keymap_Change(int id_option, int code_key, string str_conflict_control, string str_conflict_mod)
endFunction

function f_On_Option_Default(int id_option)
endFunction

; Private Methods
function p_Go_Back()
    if p_code_view == CODES.VIEW_MEMBER
        if MEMBERS.Will_Sort()
            MCM.SetTitleText(p_STR_PLEASE_WAIT)
        endIf
        MCM.MCM_MEMBERS.f_View_Members()
        MCM.ForcePageReset()
    elseIf p_code_view == CODES.VIEW_FOLLOWER
        if FOLLOWERS.Will_Sort()
            MCM.SetTitleText(p_STR_PLEASE_WAIT)
        endIf
        MCM.MCM_FOLLOWERS.f_View_Followers()
        MCM.ForcePageReset()
    endIf
endFunction

function p_Update_Stats(Actor ref_actor)
    MCM.SetTextOptionValue(p_option_health,             ref_actor.GetActorValue(CONSTS.STR_HEALTH)      as int,  true)
    MCM.SetTextOptionValue(p_option_magicka,            ref_actor.GetActorValue(CONSTS.STR_MAGICKA)     as int,  true)
    MCM.SetTextOptionValue(p_option_stamina,            ref_actor.GetActorValue(CONSTS.STR_STAMINA)     as int,  true)

    MCM.SetTextOptionValue(p_option_skill_one_handed,   ref_actor.GetActorValue(CONSTS.STR_ONE_HANDED)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_two_handed,   ref_actor.GetActorValue(CONSTS.STR_TWO_HANDED)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_block,        ref_actor.GetActorValue(CONSTS.STR_BLOCK)       as int,  true)
    MCM.SetTextOptionValue(p_option_skill_heavy_armor,  ref_actor.GetActorValue(CONSTS.STR_HEAVY_ARMOR) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_light_armor,  ref_actor.GetActorValue(CONSTS.STR_LIGHT_ARMOR) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_smithing,     ref_actor.GetActorValue(CONSTS.STR_SMITHING)    as int,  true)

    MCM.SetTextOptionValue(p_option_skill_destruction,  ref_actor.GetActorValue(CONSTS.STR_DESTRUCTION) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_restoration,  ref_actor.GetActorValue(CONSTS.STR_RESTORATION) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_conjuration,  ref_actor.GetActorValue(CONSTS.STR_CONJURATION) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_alteration,   ref_actor.GetActorValue(CONSTS.STR_ALTERATION)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_illusion,     ref_actor.GetActorValue(CONSTS.STR_ILLUSION)    as int,  true)
    MCM.SetTextOptionValue(p_option_skill_enchanting,   ref_actor.GetActorValue(CONSTS.STR_ENCHANTING)  as int,  true)

    MCM.SetTextOptionValue(p_option_skill_marksman,     ref_actor.GetActorValue(CONSTS.STR_MARKSMAN)    as int,  true)
    MCM.SetTextOptionValue(p_option_skill_sneak,        ref_actor.GetActorValue(CONSTS.STR_SNEAK)       as int,  true)
    MCM.SetTextOptionValue(p_option_skill_alchemy,      ref_actor.GetActorValue(CONSTS.STR_ALCHEMY)     as int,  true)
    MCM.SetTextOptionValue(p_option_skill_lockpicking,  ref_actor.GetActorValue(CONSTS.STR_LOCKPICKING) as int,  true)
    MCM.SetTextOptionValue(p_option_skill_pickpocket,   ref_actor.GetActorValue(CONSTS.STR_PICKPOCKET)  as int,  true)
    MCM.SetTextOptionValue(p_option_skill_speechcraft,  ref_actor.GetActorValue(CONSTS.STR_SPEECHCRAFT) as int, false)
endFunction