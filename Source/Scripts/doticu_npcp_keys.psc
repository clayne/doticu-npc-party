;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_keys extends Quest

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
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
    Update_Keys()
endFunction

; Native Methods
int function Default_Value(string key) native
int function Current_Value(string key) native
int[] function Default_Mods(string key) native
int[] function Current_Mods(string key) native
string function Default_Mods_To_String(string key) native
string function Current_Mods_To_String(string key) native
string function Conflicting_Hotkey(string key, int value, int mod_1, int mod_2, int mod_3) native
string function p_Pressed_Hotkey(int value, int pressed_1 = -1, int pressed_2 = -1, int pressed_3 = -1, int pressed_4 = -1) native

; Public Methods
bool function Is_Active(int code_key)
    return code_key > -1
endFunction

string function Pressed_Hotkey(int value)
    int pressed_key_count = Input.GetNumKeysPressed()
    if pressed_key_count >= 4
        return p_Pressed_Hotkey(value,                      \
                                Input.GetNthKeyPressed(0),  \
                                Input.GetNthKeyPressed(1),  \
                                Input.GetNthKeyPressed(2),  \
                                Input.GetNthKeyPressed(3))
    elseIf pressed_key_count == 3
        return p_Pressed_Hotkey(value,                      \
                                Input.GetNthKeyPressed(0),  \
                                Input.GetNthKeyPressed(1),  \
                            Input.GetNthKeyPressed(2))
    elseIf pressed_key_count == 2
        return p_Pressed_Hotkey(value,                      \
                                Input.GetNthKeyPressed(0),  \
                                Input.GetNthKeyPressed(1))
    elseIf pressed_key_count == 1
        return p_Pressed_Hotkey(value,                      \
                                Input.GetNthKeyPressed(0))
    else
        return p_Pressed_Hotkey(value)
    endIf
endFunction

function Update_Keys()
    UnregisterForAllKeys()

    ; General
    if VARS.key_g_dialogue_menu > -1
        RegisterForKey(VARS.key_g_dialogue_menu)
    endIf

    ; NPC
    if VARS.key_n_toggle_member > -1
        RegisterForKey(VARS.key_n_toggle_member)
    endIf
    if VARS.key_n_toggle_move > -1
        RegisterForKey(VARS.key_n_toggle_move)
    endIf
    ACTORS.MOVEE.Update_Keys()
    if VARS.key_n_has_base > -1
        RegisterForKey(VARS.key_n_has_base)
    endIf
    if VARS.key_n_count_base > -1
        RegisterForKey(VARS.key_n_count_base)
    endIf
    if VARS.key_n_has_head > -1
        RegisterForKey(VARS.key_n_has_head)
    endIf
    if VARS.key_n_count_heads > -1
        RegisterForKey(VARS.key_n_count_heads)
    endIf

    ; Member
    if VARS.key_m_toggle_clone > -1
        RegisterForKey(VARS.key_m_toggle_clone)
    endIf
    if VARS.key_m_toggle_settler > -1
        RegisterForKey(VARS.key_m_toggle_settler)
    endIf
    if VARS.key_m_toggle_thrall > -1
        RegisterForKey(VARS.key_m_toggle_thrall)
    endIf
    if VARS.key_m_toggle_immobile > -1
        RegisterForKey(VARS.key_m_toggle_immobile)
    endIf
    if VARS.key_m_toggle_paralyzed > -1
        RegisterForKey(VARS.key_m_toggle_paralyzed)
    endIf
    if VARS.key_m_toggle_follower > -1
        RegisterForKey(VARS.key_m_toggle_follower)
    endIf

    ; Follower
    if VARS.key_f_toggle_sneak > -1
        RegisterForKey(VARS.key_f_toggle_sneak)
    endIf
    if VARS.key_f_toggle_saddler > -1
        RegisterForKey(VARS.key_f_toggle_saddler)
    endIf

    ; Members
    if VARS.key_ms_toggle_display > -1
        RegisterForKey(VARS.key_ms_toggle_display)
    endIf
    if VARS.key_ms_display_previous > -1
        RegisterForKey(VARS.key_ms_display_previous)
    endIf
    if VARS.key_ms_display_next > -1
        RegisterForKey(VARS.key_ms_display_next)
    endIf

    ; Followers
    if VARS.key_fs_summon_all > -1
        RegisterForKey(VARS.key_fs_summon_all)
    endIf
    if VARS.key_fs_summon_mobile > -1
        RegisterForKey(VARS.key_fs_summon_mobile)
    endIf
    if VARS.key_fs_summon_immobile > -1
        RegisterForKey(VARS.key_fs_summon_immobile)
    endIf
    if VARS.key_fs_settle > -1
        RegisterForKey(VARS.key_fs_settle)
    endIf
    if VARS.key_fs_unsettle > -1
        RegisterForKey(VARS.key_fs_unsettle)
    endIf
    if VARS.key_fs_mobilize > -1
        RegisterForKey(VARS.key_fs_mobilize)
    endIf
    if VARS.key_fs_immobilize > -1
        RegisterForKey(VARS.key_fs_immobilize)
    endIf
    if VARS.key_fs_sneak > -1
        RegisterForKey(VARS.key_fs_sneak)
    endIf
    if VARS.key_fs_unsneak > -1
        RegisterForKey(VARS.key_fs_unsneak)
    endIf
    if VARS.key_fs_saddle > -1
        RegisterForKey(VARS.key_fs_saddle)
    endIf
    if VARS.key_fs_unsaddle > -1
        RegisterForKey(VARS.key_fs_unsaddle)
    endIf
    if VARS.key_fs_resurrect > -1
        RegisterForKey(VARS.key_fs_resurrect)
    endIf
    if VARS.key_fs_unfollow > -1
        RegisterForKey(VARS.key_fs_unfollow)
    endIf
    if VARS.key_fs_unmember > -1
        RegisterForKey(VARS.key_fs_unmember)
    endIf
endFunction

; Events
event OnKeyDown(int value)
    if !FUNCS.Can_Use_Keys()
        return
    endIf

    string pressed_hotkey = Pressed_Hotkey(value)
    if !pressed_hotkey

    ; General
    elseIf pressed_hotkey == CONSTS.KEY_G_DIALOGUE_MENU
        FUNCS.ACTORS.Create_Menu()

    ; NPC
    elseIf pressed_hotkey == CONSTS.KEY_N_TOGGLE_MEMBER
        COMMANDS.Toggle_Member_Sync(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_N_TOGGLE_MOVE
        COMMANDS.Move_Sync(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_N_HAS_BASE
        Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor
        if ref_actor == none
            LOGS.Create_Note("That is not an NPC.", false)
        elseIf p_DATA.MODS.MEMBERS.Has_Base(ref_actor)
            LOGS.Create_Note("A member has the base of " + ACTORS.Get_Name(ref_actor) + ".", false)
        else
            LOGS.Create_Note("No member has the base of " + ACTORS.Get_Name(ref_actor) + ".", false)
        endIf
    elseIf pressed_hotkey == CONSTS.KEY_N_COUNT_BASE
        Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor
        if ref_actor == none
            LOGS.Create_Note("That is not an NPC.", false)
        else
            int num_members = p_DATA.MODS.MEMBERS.Get_Base_Count(ref_actor)
            if num_members == 1
                LOGS.Create_Note(num_members + " member has the base of " + ACTORS.Get_Name(ref_actor) + ".", false)
            else
                LOGS.Create_Note(num_members + " members have the base of " + ACTORS.Get_Name(ref_actor) + ".", false)
            endIf
        endIf
    elseif pressed_hotkey == CONSTS.KEY_N_HAS_HEAD
        Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor
        if ref_actor == none
            LOGS.Create_Note("That is not an NPC.", false)
        elseIf p_DATA.MODS.MEMBERS.Has_Head(ref_actor)
            LOGS.Create_Note("A member looks like " + ACTORS.Get_Name(ref_actor) + ".", false)
        else
            LOGS.Create_Note("No member looks like " + ACTORS.Get_Name(ref_actor) + ".", false)
        endIf
    elseIf pressed_hotkey == CONSTS.KEY_N_COUNT_HEADS
        Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor
        if ref_actor == none
            LOGS.Create_Note("That is not an NPC.", false)
        else
            int num_heads = p_DATA.MODS.MEMBERS.Get_Head_Count(ref_actor)
            if num_heads == 1
                LOGS.Create_Note(num_heads + " member looks like " + ACTORS.Get_Name(ref_actor) + ".", false)
            else
                LOGS.Create_Note(num_heads + " members look like " + ACTORS.Get_Name(ref_actor) + ".", false)
            endIf
        endIf

    ; Member
    elseIf pressed_hotkey == CONSTS.KEY_M_TOGGLE_CLONE
        COMMANDS.Toggle_Clone_Sync(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_M_TOGGLE_SETTLER
        COMMANDS.Toggle_Settler_Async(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_M_TOGGLE_THRALL
        COMMANDS.Toggle_Thrall_Async(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_M_TOGGLE_IMMOBILE
        COMMANDS.Toggle_Immobile_Async(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_M_TOGGLE_PARALYZED
        COMMANDS.Toggle_Paralyzed_Async(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_M_TOGGLE_FOLLOWER
        COMMANDS.Toggle_Follower_Sync(Game.GetCurrentCrosshairRef() as Actor)

    ; Follower
    elseIf pressed_hotkey == CONSTS.KEY_F_TOGGLE_SNEAK
        COMMANDS.Toggle_Sneak_Async(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_F_TOGGLE_SADDLER
        COMMANDS.Toggle_Saddler_Async(Game.GetCurrentCrosshairRef() as Actor)

    ; Members
    elseIf pressed_hotkey == CONSTS.KEY_MS_TOGGLE_DISPLAY
        COMMANDS.Toggle_Members_Display(Game.GetCurrentCrosshairRef() as Actor)
    elseIf pressed_hotkey == CONSTS.KEY_MS_DISPLAY_PREVIOUS
        COMMANDS.Members_Display_Previous()
    elseIf pressed_hotkey == CONSTS.KEY_MS_DISPLAY_NEXT
        COMMANDS.Members_Display_Next()

    ; Followers
    elseIf pressed_hotkey == CONSTS.KEY_FS_SUMMON_ALL
        COMMANDS.Followers_Summon_All()
    elseIf pressed_hotkey == CONSTS.KEY_FS_SUMMON_MOBILE
        COMMANDS.Followers_Summon_Mobile()
    elseIf pressed_hotkey == CONSTS.KEY_FS_SUMMON_IMMOBILE
        COMMANDS.Followers_Summon_Immobile()
    elseIf pressed_hotkey == CONSTS.KEY_FS_SETTLE
        COMMANDS.Followers_Settle()
    elseIf pressed_hotkey == CONSTS.KEY_FS_UNSETTLE
        COMMANDS.Followers_Unsettle()
    elseIf pressed_hotkey == CONSTS.KEY_FS_MOBILIZE
        COMMANDS.Followers_Mobilize()
    elseIf pressed_hotkey == CONSTS.KEY_FS_IMMOBILIZE
        COMMANDS.Followers_Immobilize()
    elseIf pressed_hotkey == CONSTS.KEY_FS_SNEAK
        COMMANDS.Followers_Sneak()
    elseIf pressed_hotkey == CONSTS.KEY_FS_UNSNEAK
        COMMANDS.Followers_Unsneak()
    elseIf pressed_hotkey == CONSTS.KEY_FS_SADDLE
        COMMANDS.Followers_Saddle()
    elseIf pressed_hotkey == CONSTS.KEY_FS_UNSADDLE
        COMMANDS.Followers_Unsaddle()
    elseIf pressed_hotkey == CONSTS.KEY_FS_RESURRECT
        COMMANDS.Followers_Resurrect()

    endIf
endEvent
