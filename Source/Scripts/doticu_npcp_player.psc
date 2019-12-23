Scriptname doticu_npcp_player extends ReferenceAlias

; Private Constants
doticu_npcp_data        p_DATA          = none
doticu_npcp_consts      p_CONSTS        = none
doticu_npcp_codes       p_CODES         = none
doticu_npcp_vars        p_VARS          = none
doticu_npcp_funcs       p_FUNCS         = none
doticu_npcp_actors      p_ACTORS        = none
doticu_npcp_followers   p_FOLLOWERS     = none
doticu_npcp_main        p_MAIN          = none

doticu_npcp_async_alias p_ASYNC         = none
Actor                   p_REF_PLAYER    = none

; Private Variables
bool p_is_in_combat = false

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_FUNCS = DATA.MODS.FUNCS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_MAIN = DATA.MODS.MAIN

    p_ASYNC = (self as ReferenceAlias) as doticu_npcp_async_alias
    p_REF_PLAYER = DATA.CONSTS.ACTOR_PLAYER

    p_ASYNC.f_Initialize(DATA)
endFunction

function f_Register()
    p_ASYNC.f_Register()
endFunction

function f_Begin_Combat()
    if !p_is_in_combat
        p_is_in_combat = true
        p_ASYNC.Enqueue("f_Try_End_Combat()", 5.0)
    endIf
endFunction

function f_End_Combat()
    if p_is_in_combat
        p_is_in_combat = false
        p_ASYNC.Flush()
        if p_VARS.auto_resurrect
            p_FOLLOWERS.Resurrect()
        endIf
    endIf
endFunction

function f_Try_End_Combat()
    if p_REF_PLAYER.IsInCombat()
        p_ASYNC.Enqueue("f_Try_End_Combat()", 5.0)
    else
        f_End_Combat()
    endIf
endFunction

; Private Methods
bool function p_Send_NPCP_Load_Game()
    int handle = ModEvent.Create("doticu_npcp_load_game")

    if !handle
        return false
    endIf

    ; push any args here

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    p_REF_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    p_REF_PLAYER.RemovePerk(perk_to_remove)
endFunction

; Events
event OnUpdate()
    string str_message = p_ASYNC.Dequeue()

    if str_message == "f_Try_End_Combat()"
        f_Try_End_Combat()
    endIf
endEvent

event OnPlayerLoadGame()
    Utility.Wait(0.5)
    p_DATA.MODS.RESETS.Reset()
    Utility.Wait(0.5)

    p_MAIN.f_Register()
    
    p_MAIN.f_Version()

    while !p_Send_NPCP_Load_Game()
        Utility.Wait(0.25)
    endWhile
endEvent

event OnActorAction(int code_action, Actor ref_activator, Form form_source, int slot)
endEvent
