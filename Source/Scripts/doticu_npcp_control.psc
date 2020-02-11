;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_control extends Quest

; Modules
doticu_npcp_commands property COMMANDS
    doticu_npcp_commands function Get()
        return (self as Quest) as doticu_npcp_commands
    endFunction
endProperty
doticu_npcp_keys property KEYS
    doticu_npcp_keys function Get()
        return (self as Quest) as doticu_npcp_keys
    endFunction
endProperty
doticu_npcp_mcm property MCM
    doticu_npcp_mcm function Get()
        return (self as Quest) as doticu_npcp_mcm
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_is_created = true

    COMMANDS.f_Create(DATA)
    KEYS.f_Create(DATA)
    MCM.f_Create(DATA)
endFunction

function f_Destroy()
    MCM.f_Destroy()
    KEYS.f_Destroy()
    COMMANDS.f_Destroy()
    
    p_is_created = false
endFunction

function f_Register()
    COMMANDS.f_Register()
    KEYS.f_Register()
    MCM.f_Register()
endFunction

function f_Unregister()
endFunction

function f_Start_Updating()
    COMMANDS.GotoState("f_STATE_UPDATING")
endFunction

function f_Stop_Updating()
    COMMANDS.GotoState("")
endFunction
