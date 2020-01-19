Scriptname doticu_npcp_keys extends Quest

; Modules
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

; Public Methods
function Update_Keys()
    UnregisterForAllKeys()

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
    if VARS.key_fs_immobilize > -1
        RegisterForKey(VARS.key_fs_immobilize)
    endIf
    if VARS.key_fs_mobilize > -1
        RegisterForKey(VARS.key_fs_mobilize)
    endIf
    if VARS.key_fs_sneak > -1
        RegisterForKey(VARS.key_fs_sneak)
    endIf
    if VARS.key_fs_unsneak > -1
        RegisterForKey(VARS.key_fs_unsneak)
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

    ; Members Display
    if VARS.key_ms_toggle_display > -1
        RegisterForKey(VARS.key_ms_toggle_display)
    endIf
    if VARS.key_ms_display_next > -1
        RegisterForKey(VARS.key_ms_display_next)
    endIf
    if VARS.key_ms_display_previous > -1
        RegisterForKey(VARS.key_ms_display_previous)
    endIf

    ; Actors Move
    if VARS.key_move_toggle
        RegisterForKey(VARS.key_move_toggle)
    endIf
    ACTORS.MOVEE.Update_Keys()

    ; Member/Follower
    if VARS.key_resurrect > -1
        RegisterForKey(VARS.key_resurrect)
    endIf
    if VARS.key_pack > -1
        RegisterForKey(VARS.key_pack)
    endIf
    if VARS.key_outfit > -1
        RegisterForKey(VARS.key_outfit)
    endIf

    ; Member/Follower Toggles
    if VARS.key_m_toggle_member > -1
        RegisterForKey(VARS.key_m_toggle_member)
    endIf
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
    if VARS.key_m_toggle_sneak > -1
        RegisterForKey(VARS.key_m_toggle_sneak)
    endIf

    ; Member/Follower Cycles
    if VARS.key_cycle_style > -1
        RegisterForKey(VARS.key_cycle_style)
    endIf
    if VARS.key_cycle_vitality > -1
        RegisterForKey(VARS.key_cycle_vitality)
    endIf
    if VARS.key_cycle_outfit > -1
        RegisterForKey(VARS.key_cycle_outfit)
    endIf
endFunction

; Events
event OnKeyDown(int code_key)
    if !FUNCS.Can_Use_Keys()
        return
    endIf
    
    Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor

    ; can add a 'Yell' command to topics, so that all funcs can be used in dialogue, e.g. "Summon All"

    if false

    ; Followers
    elseIf code_key == VARS.key_fs_summon_all
        COMMANDS.Followers_Summon_All()
    elseIf code_key == VARS.key_fs_summon_mobile
        COMMANDS.Followers_Summon_Mobile()
    elseIf code_key == VARS.key_fs_summon_immobile
        COMMANDS.Followers_Summon_Immobile()
    elseIf code_key == VARS.key_fs_settle
        COMMANDS.Followers_Settle()
    elseIf code_key == VARS.key_fs_unsettle
        COMMANDS.Followers_Unsettle()
    elseIf code_key == VARS.key_fs_immobilize
        COMMANDS.Followers_Immobilize()
    elseIf code_key == VARS.key_fs_mobilize
        COMMANDS.Followers_Mobilize()
    elseIf code_key == VARS.key_fs_sneak
        COMMANDS.Followers_Sneak()
    elseIf code_key == VARS.key_fs_unsneak
        COMMANDS.Followers_Unsneak()
    elseIf code_key == VARS.key_fs_resurrect
        COMMANDS.Followers_Resurrect()

    ; Members Display
    elseIf code_key == VARS.key_ms_toggle_display
        COMMANDS.Toggle_Members_Display(ref_actor)
    elseIf code_key == VARS.key_ms_display_next
        COMMANDS.Members_Display_Next()
    elseIf code_key == VARS.key_ms_display_previous
        COMMANDS.Members_Display_Previous()

    ; Actors Move
    elseIf code_key == VARS.key_move_toggle
        COMMANDS.Move_Sync(ref_actor)

    ; Member/Follower
    elseIf code_key == VARS.key_resurrect
        COMMANDS.Resurrect_Async(ref_actor, true)
    elseIf code_key == VARS.key_pack
        COMMANDS.Pack_Sync(ref_actor, true)
    elseIf code_key == VARS.key_outfit
        COMMANDS.Outfit_Current_Sync(ref_actor, true)
    
    ; Member/Follower Toggles
    elseIf code_key == VARS.key_m_toggle_member
        COMMANDS.Toggle_Member_Sync(ref_actor)
    elseIf code_key == VARS.key_m_toggle_clone
        COMMANDS.Toggle_Clone_Sync(ref_actor)
    elseIf code_key == VARS.key_m_toggle_settler
        COMMANDS.Toggle_Settler_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_thrall
        COMMANDS.Toggle_Thrall_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_immobile
        COMMANDS.Toggle_Immobile_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_paralyzed
        COMMANDS.Toggle_Paralyzed_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_follower
        COMMANDS.Toggle_Follower_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_sneak
        COMMANDS.Toggle_Sneak_Async(ref_actor)
    
    ; Member/Follower Cycles
    elseIf code_key == VARS.key_cycle_style
        COMMANDS.Cycle_Style(ref_actor, false)
    endIf
endEvent
