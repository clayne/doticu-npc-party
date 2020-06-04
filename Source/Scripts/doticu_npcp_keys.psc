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

; Private Methods
bool function Is_Modifier_Pressed(int code_modifier)
    return code_modifier < 0 || Input.IsKeyPressed(code_modifier)
endFunction

; Public Methods
bool function Is_Active(int code_key)
    return code_key > -1
endFunction

function Update_Keys()
    UnregisterForAllKeys()

    ; General
    if VARS.key_g_modifier > -1
        RegisterForKey(VARS.key_g_modifier)
    endIf
    if VARS.key_g_dialogue_menu > -1
        RegisterForKey(VARS.key_g_dialogue_menu)
    endIf

    ; All Followers
    if VARS.key_fs_modifier > -1
        RegisterForKey(VARS.key_fs_modifier)
    endIf
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

    ; All Members
    if VARS.key_ms_modifier > -1
        RegisterForKey(VARS.key_ms_modifier)
    endIf
    if VARS.key_ms_display_toggle > -1
        RegisterForKey(VARS.key_ms_display_toggle)
    endIf
    if VARS.key_ms_display_next > -1
        RegisterForKey(VARS.key_ms_display_next)
    endIf
    if VARS.key_ms_display_previous > -1
        RegisterForKey(VARS.key_ms_display_previous)
    endIf

    ; One Member/Follower
    if VARS.key_m_modifier > -1
        RegisterForKey(VARS.key_m_modifier)
    endIf
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

    ; One NPC
    if VARS.key_n_modifier > -1
        RegisterForKey(VARS.key_n_modifier)
    endIf
    if VARS.key_move_toggle > -1
        RegisterForKey(VARS.key_move_toggle)
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
endFunction

string function Get_Control(int code_key)
    if false

    ; General
    elseIf code_key == VARS.key_g_modifier
        return CONSTS.STR_KEY_G_MODIFIER
    elseIf code_key == VARS.key_g_dialogue_menu
        return CONSTS.STR_KEY_G_DIALOGUE_MENU

    ; All Followers
    elseIf code_key == VARS.key_fs_modifier
        return CONSTS.STR_KEY_FS_MODIFIER
    elseIf code_key == VARS.key_fs_summon_all
        return CONSTS.STR_KEY_FS_SUMMON_ALL
    elseIf code_key == VARS.key_fs_summon_mobile
        return CONSTS.STR_KEY_FS_SUMMON_MOBILE
    elseIf code_key == VARS.key_fs_summon_immobile
        return CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
    elseIf code_key == VARS.key_fs_settle
        return CONSTS.STR_KEY_FS_SETTLE
    elseIf code_key == VARS.key_fs_unsettle
        return CONSTS.STR_KEY_FS_UNSETTLE
    elseIf code_key == VARS.key_fs_immobilize
        return CONSTS.STR_KEY_FS_IMMOBILIZE
    elseIf code_key == VARS.key_fs_mobilize
        return CONSTS.STR_KEY_FS_MOBILIZE
    elseIf code_key == VARS.key_fs_sneak
        return CONSTS.STR_KEY_FS_SNEAK
    elseIf code_key == VARS.key_fs_unsneak
        return CONSTS.STR_KEY_FS_UNSNEAK
    elseIf code_key == VARS.key_fs_resurrect
        return CONSTS.STR_KEY_FS_RESURRECT

    ; All Members
    elseIf code_key == VARS.key_ms_modifier
        return CONSTS.STR_KEY_MS_MODIFIER
    elseIf code_key == VARS.key_ms_display_toggle
        return CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
    elseIf code_key == VARS.key_ms_display_next
        return CONSTS.STR_KEY_MS_DISPLAY_NEXT
    elseIf code_key == VARS.key_ms_display_previous
        return CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS

    ; One Member/Follower
    elseIf code_key == VARS.key_m_modifier
        return CONSTS.STR_KEY_M_MODIFIER
    elseIf code_key == VARS.key_m_toggle_member
        return CONSTS.STR_KEY_M_TOGGLE_MEMBER
    elseIf code_key == VARS.key_m_toggle_clone
        return CONSTS.STR_KEY_M_TOGGLE_CLONE
    elseIf code_key == VARS.key_m_toggle_settler
        return CONSTS.STR_KEY_M_TOGGLE_SETTLER
    elseIf code_key == VARS.key_m_toggle_thrall
        return CONSTS.STR_KEY_M_TOGGLE_THRALL
    elseIf code_key == VARS.key_m_toggle_immobile
        return CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
    elseIf code_key == VARS.key_m_toggle_paralyzed
        return CONSTS.STR_KEY_M_TOGGLE_PARALYZED
    elseIf code_key == VARS.key_m_toggle_follower
        return CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
    elseIf code_key == VARS.key_m_toggle_sneak
        return CONSTS.STR_KEY_M_TOGGLE_SNEAK

    ; One NPC
    elseIf code_key == VARS.key_n_modifier
        return CONSTS.STR_KEY_N_MODIFIER
    elseIf code_key == VARS.key_move_toggle
        return CONSTS.STR_KEY_MOVE_TOGGLE
    elseIf code_key == VARS.key_move_farther
        return CONSTS.STR_KEY_MOVE_FARTHER
    elseIf code_key == VARS.key_move_nearer
        return CONSTS.STR_KEY_MOVE_NEARER
    elseIf code_key == VARS.key_move_rotate_right
        return CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
    elseIf code_key == VARS.key_move_rotate_left
        return CONSTS.STR_KEY_MOVE_ROTATE_LEFT
    elseIf code_key == VARS.key_n_has_base
        return CONSTS.STR_KEY_N_HAS_BASE
    elseIf code_key == VARS.key_n_count_base
        return CONSTS.STR_KEY_N_COUNT_BASE
    elseIf code_key == VARS.key_n_has_head
        return CONSTS.STR_KEY_N_HAS_HEAD
    elseIf code_key == VARS.key_n_count_heads
        return CONSTS.STR_KEY_N_COUNT_HEADS
    
    else
        return ""

    endIf
endFunction

int function Get_Key(string str_control)
    if false

    ; General
    elseIf str_control == CONSTS.STR_KEY_G_MODIFIER
        return VARS.key_g_modifier
    elseIf str_control == CONSTS.STR_KEY_G_DIALOGUE_MENU
        return VARS.key_g_dialogue_menu

    ; All Followers
    elseIf str_control == CONSTS.STR_KEY_FS_MODIFIER
        return VARS.key_fs_modifier
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_ALL
        return VARS.key_fs_summon_all
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_MOBILE
        return VARS.key_fs_summon_mobile
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
        return VARS.key_fs_summon_immobile
    elseIf str_control == CONSTS.STR_KEY_FS_SETTLE
        return VARS.key_fs_settle
    elseIf str_control == CONSTS.STR_KEY_FS_UNSETTLE
        return VARS.key_fs_unsettle
    elseIf str_control == CONSTS.STR_KEY_FS_IMMOBILIZE
        return VARS.key_fs_immobilize
    elseIf str_control == CONSTS.STR_KEY_FS_MOBILIZE
        return VARS.key_fs_mobilize
    elseIf str_control == CONSTS.STR_KEY_FS_SNEAK
        return VARS.key_fs_sneak
    elseIf str_control == CONSTS.STR_KEY_FS_UNSNEAK
        return VARS.key_fs_unsneak
    elseIf str_control == CONSTS.STR_KEY_FS_RESURRECT
        return VARS.key_fs_resurrect

    ; All Members
    elseIf str_control == CONSTS.STR_KEY_MS_MODIFIER
        return VARS.key_ms_modifier
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
        return VARS.key_ms_display_toggle
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_NEXT
        return VARS.key_ms_display_next
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS
        return VARS.key_ms_display_previous

    ; One Member/Follower
    elseIf str_control == CONSTS.STR_KEY_M_MODIFIER
        return VARS.key_m_modifier
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_MEMBER
        return VARS.key_m_toggle_member
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_CLONE
        return VARS.key_m_toggle_clone
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SETTLER
        return VARS.key_m_toggle_settler
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_THRALL
        return VARS.key_m_toggle_thrall
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
        return VARS.key_m_toggle_immobile
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_PARALYZED
        return VARS.key_m_toggle_paralyzed
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
        return VARS.key_m_toggle_follower
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SNEAK
        return VARS.key_m_toggle_sneak

    ; One NPC
    elseIf str_control == CONSTS.STR_KEY_N_MODIFIER
        return VARS.key_n_modifier
    elseIf str_control == CONSTS.STR_KEY_MOVE_TOGGLE
        return VARS.key_move_toggle
    elseIf str_control == CONSTS.STR_KEY_MOVE_FARTHER
        return VARS.key_move_farther
    elseIf str_control == CONSTS.STR_KEY_MOVE_NEARER
        return VARS.key_move_nearer
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
        return VARS.key_move_rotate_right
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_LEFT
        return VARS.key_move_rotate_left
    elseIf str_control == CONSTS.STR_KEY_N_HAS_BASE
        return VARS.key_n_has_base
    elseIf str_control == CONSTS.STR_KEY_N_COUNT_BASE
        return VARS.key_n_count_base
    elseIf str_control == CONSTS.STR_KEY_N_HAS_HEAD
        return VARS.key_n_has_head
    elseIf str_control == CONSTS.STR_KEY_N_COUNT_HEADS
        return VARS.key_n_count_heads
        
    else
        return -1
    
    endIf
endFunction

int function Get_Key_Default(string str_control)
    if false

    ; General
    elseIf str_control == CONSTS.STR_KEY_G_MODIFIER
        return CONSTS.KEY_DEF_G_MODIFIER
    elseIf str_control == CONSTS.STR_KEY_G_DIALOGUE_MENU
        return CONSTS.KEY_DEF_G_DIALOGUE_MENU

    ; All Followers
    elseIf str_control == CONSTS.STR_KEY_FS_MODIFIER
        return CONSTS.KEY_DEF_FS_MODIFIER
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_ALL
        return CONSTS.KEY_DEF_FS_SUMMON_ALL
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_MOBILE
        return CONSTS.KEY_DEF_FS_SUMMON_MOBILE
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
        return CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE
    elseIf str_control == CONSTS.STR_KEY_FS_SETTLE
        return CONSTS.KEY_DEF_FS_SETTLE
    elseIf str_control == CONSTS.STR_KEY_FS_UNSETTLE
        return CONSTS.KEY_DEF_FS_UNSETTLE
    elseIf str_control == CONSTS.STR_KEY_FS_IMMOBILIZE
        return CONSTS.KEY_DEF_FS_IMMOBILIZE
    elseIf str_control == CONSTS.STR_KEY_FS_MOBILIZE
        return CONSTS.KEY_DEF_FS_MOBILIZE
    elseIf str_control == CONSTS.STR_KEY_FS_SNEAK
        return CONSTS.KEY_DEF_FS_SNEAK
    elseIf str_control == CONSTS.STR_KEY_FS_UNSNEAK
        return CONSTS.KEY_DEF_FS_UNSNEAK
    elseIf str_control == CONSTS.STR_KEY_FS_RESURRECT
        return CONSTS.KEY_DEF_FS_RESURRECT
    
    ; All Members
    elseIf str_control == CONSTS.STR_KEY_MS_MODIFIER
        return CONSTS.KEY_DEF_MS_MODIFIER
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
        return CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS
        return CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_NEXT
        return CONSTS.KEY_DEF_MS_DISPLAY_NEXT
    
    ; One Member/Follower
    elseIf str_control == CONSTS.STR_KEY_M_MODIFIER
        return CONSTS.KEY_DEF_M_MODIFIER
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_MEMBER
        return CONSTS.KEY_DEF_M_TOGGLE_MEMBER
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_CLONE
        return CONSTS.KEY_DEF_M_TOGGLE_CLONE
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SETTLER
        return CONSTS.KEY_DEF_M_TOGGLE_SETTLER
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_THRALL
        return CONSTS.KEY_DEF_M_TOGGLE_THRALL
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
        return CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_PARALYZED
        return CONSTS.KEY_DEF_M_TOGGLE_PARALYZED
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
        return CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SNEAK
        return CONSTS.KEY_DEF_M_TOGGLE_SNEAK

    ; One NPC
    elseIf str_control == CONSTS.STR_KEY_N_MODIFIER
        return CONSTS.KEY_DEF_N_MODIFIER
    elseIf str_control == CONSTS.STR_KEY_MOVE_TOGGLE
        return CONSTS.KEY_DEF_MOVE_TOGGLE
    elseIf str_control == CONSTS.STR_KEY_MOVE_FARTHER
        return CONSTS.KEY_DEF_MOVE_FARTHER
    elseIf str_control == CONSTS.STR_KEY_MOVE_NEARER
        return CONSTS.KEY_DEF_MOVE_NEARER
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
        return CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_LEFT
        return CONSTS.KEY_DEF_MOVE_ROTATE_LEFT
    elseIf str_control == CONSTS.STR_KEY_N_HAS_BASE
        return CONSTS.KEY_DEF_N_HAS_BASE
    elseIf str_control == CONSTS.STR_KEY_N_COUNT_BASE
        return CONSTS.KEY_DEF_N_COUNT_BASE
    elseIf str_control == CONSTS.STR_KEY_N_HAS_HEAD
        return CONSTS.KEY_DEF_N_HAS_HEAD
    elseIf str_control == CONSTS.STR_KEY_N_COUNT_HEADS
        return CONSTS.KEY_DEF_N_COUNT_HEADS

    else
        return -1
        
    endIf
endFunction

; Events
event OnKeyDown(int code_key)
    if !FUNCS.Can_Use_Keys()
        return
    endIf
    
    Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor

    ; add Followers sub menu to dialogue_menu, e.g. "Summon All"

    if false

    ; General
    elseIf code_key == VARS.key_g_dialogue_menu && Is_Modifier_Pressed(VARS.key_g_modifier)
        FUNCS.ACTORS.Create_Menu()

    ; All Followers
    elseIf code_key == VARS.key_fs_summon_all && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Summon_All()
    elseIf code_key == VARS.key_fs_summon_mobile && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Summon_Mobile()
    elseIf code_key == VARS.key_fs_summon_immobile && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Summon_Immobile()
    elseIf code_key == VARS.key_fs_settle && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Settle()
    elseIf code_key == VARS.key_fs_unsettle && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Unsettle()
    elseIf code_key == VARS.key_fs_immobilize && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Immobilize()
    elseIf code_key == VARS.key_fs_mobilize && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Mobilize()
    elseIf code_key == VARS.key_fs_sneak && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Sneak()
    elseIf code_key == VARS.key_fs_unsneak && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Unsneak()
    elseIf code_key == VARS.key_fs_resurrect && Is_Modifier_Pressed(VARS.key_fs_modifier)
        COMMANDS.Followers_Resurrect()

    ; All Members
    elseIf code_key == VARS.key_ms_display_toggle && Is_Modifier_Pressed(VARS.key_ms_modifier)
        COMMANDS.Toggle_Members_Display(ref_actor)
    elseIf code_key == VARS.key_ms_display_next && Is_Modifier_Pressed(VARS.key_ms_modifier)
        COMMANDS.Members_Display_Next()
    elseIf code_key == VARS.key_ms_display_previous && Is_Modifier_Pressed(VARS.key_ms_modifier)
        COMMANDS.Members_Display_Previous()
    
    ; One Member/Follower
    elseIf code_key == VARS.key_m_toggle_member && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Member_Sync(ref_actor)
    elseIf code_key == VARS.key_m_toggle_clone && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Clone_Sync(ref_actor)
    elseIf code_key == VARS.key_m_toggle_settler && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Settler_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_thrall && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Thrall_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_immobile && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Immobile_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_paralyzed && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Paralyzed_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_follower && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Follower_Sync(ref_actor)
    elseIf code_key == VARS.key_m_toggle_sneak && Is_Modifier_Pressed(VARS.key_m_modifier)
        COMMANDS.Toggle_Sneak_Async(ref_actor)

    ; One NPC
    elseIf code_key == VARS.key_move_toggle && Is_Modifier_Pressed(VARS.key_n_modifier)
        COMMANDS.Move_Sync(ref_actor)
    elseIf code_key == VARS.key_n_has_base && Is_Modifier_Pressed(VARS.key_n_modifier)
        ; this should prob. be a func in commands
        if ref_actor == none
            p_DATA.MODS.FUNCS.LOGS.Create_Note("That is not an NPC.", false)
        elseIf p_DATA.MODS.MEMBERS.Has_Base(ref_actor)
            p_DATA.MODS.FUNCS.LOGS.Create_Note("Yes, you have this base.", false)
        else
            p_DATA.MODS.FUNCS.LOGS.Create_Note("No, you don't have this base.", false)
        endIf
    elseIf code_key == VARS.key_n_count_base && Is_Modifier_Pressed(VARS.key_n_modifier)
        ; put in Commands also
        if ref_actor == none
            p_DATA.MODS.FUNCS.LOGS.Create_Note("That is not an NPC.", false)
        else
            int num_members = p_DATA.MODS.MEMBERS.Get_Base_Count(ref_actor)
            p_DATA.MODS.FUNCS.LOGS.Create_Note("You have " + num_members + " of this base.", false)
        endIf
    elseif code_key == VARS.key_n_has_head && Is_Modifier_Pressed(VARS.key_n_modifier)
        if ref_actor == none
            p_DATA.MODS.FUNCS.LOGS.Create_Note("That is not an NPC.", false)
        elseIf p_DATA.MODS.MEMBERS.Has_Head(ref_actor)
            p_DATA.MODS.FUNCS.LOGS.Create_Note("Yes, you have this head and face.", false)
        else
            p_DATA.MODS.FUNCS.LOGS.Create_Note("No, you don't have this head and face.", false)
        endIf
    elseIf code_key == VARS.key_n_count_heads && Is_Modifier_Pressed(VARS.key_n_modifier)
        if ref_actor == none
            p_DATA.MODS.FUNCS.LOGS.Create_Note("That is not an NPC.", false)
        else
            int num_heads = p_DATA.MODS.MEMBERS.Get_Head_Count(ref_actor)
            p_DATA.MODS.FUNCS.LOGS.Create_Note("You have " + num_heads + " with this head and face.", false)
        endIf

    endIf
endEvent
