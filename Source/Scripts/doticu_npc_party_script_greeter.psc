Scriptname doticu_npc_party_script_greeter extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts  p_CONSTS    = none
doticu_npc_party_script_codes   p_CODES     = none
doticu_npc_party_script_actor   p_ACTOR2    = none

; Private Variable
bool    is_created  = false
Actor   p_ref_actor =  none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    p_CONSTS = DATA.CONSTS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
endFunction

int function f_Create(Actor ref_actor)
    if Exists()
        return p_CODES.IS_GREETER
    endIf
    if !ref_actor
        return p_CODES.ISNT_ACTOR
    endIf

    is_created = true
    p_ref_actor = ref_actor

    ForceRefTo(p_ref_actor)
    p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_GREETER); maybe not necessary
    p_ACTOR2.Pacify(p_ref_actor)

    UnregisterForCrosshairRef()
    RegisterForCrosshairRef()

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return p_CODES.ISNT_GREETER
    endIf

    UnregisterForCrosshairRef()

    p_ACTOR2.Pacify(p_ref_actor)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_GREETER)
    Clear()
    p_ref_actor.EvaluatePackage()

    p_ref_actor = none
    is_created = false

    return p_CODES.SUCCESS
endFunction

; Public Methods
bool function Exists()
    return is_created
endFunction

; Events
event OnCrosshairRefChange(ObjectReference ref_target)
    if ref_target == p_ref_actor
        f_Destroy()
    endIf
endEvent
