Scriptname doticu_npcp_greeter extends ReferenceAlias

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
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variable
bool                p_is_created    = false
Actor               p_ref_actor     =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA, Actor ref_actor)
    p_DATA = DATA

    p_is_created = true
    p_ref_actor = ref_actor

    ForceRefTo(p_ref_actor)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_GREETER)
    ACTORS.Pacify(p_ref_actor)

    UnregisterForCrosshairRef()
    RegisterForCrosshairRef()
endFunction

function f_Destroy()
    UnregisterForCrosshairRef()

    ACTORS.Pacify(p_ref_actor)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_GREETER)
    Clear()
    p_ref_actor.EvaluatePackage()

    p_ref_actor = none
    p_is_created = false
endFunction

function f_Register()
endFunction

; Public Methods
bool function Exists()
    return p_is_created
endFunction

; Events
event OnCrosshairRefChange(ObjectReference ref_target)
    if ref_target == p_ref_actor
        f_Destroy()
    endIf
endEvent
