Scriptname doticu_npcp_data extends Quest

; Private Constants
doticu_npcp_consts  p_CONSTS    = none; static
doticu_npcp_codes   p_CODES     = none; static
doticu_npcp_mods    p_MODS      = none; static
doticu_npcp_vars    p_VARS      = none; dynamic

; Public Constants
doticu_npcp_consts property CONSTS
    doticu_npcp_consts function Get()
        return p_CONSTS
    endFunction
    function Set(doticu_npcp_consts val)
        if p_CONSTS == none
            p_CONSTS = val
        endIf
    endFunction
endProperty

doticu_npcp_codes property CODES
    doticu_npcp_codes function Get()
        return p_CODES
    endFunction
    function Set(doticu_npcp_codes val)
        if p_CODES == none
            p_CODES = val
        endIf
    endFunction
endProperty

doticu_npcp_mods property MODS
    doticu_npcp_mods function Get()
        return p_MODS
    endFunction
    function Set(doticu_npcp_mods val)
        if p_MODS == none
            p_MODS = val
        endIf
    endFunction
endProperty

doticu_npcp_vars property VARS
    doticu_npcp_vars function Get()
        return p_VARS
    endFunction
    function Set(doticu_npcp_vars val)
        if p_VARS == none
            p_VARS = val
        endIf
    endFunction
endProperty

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_VARS.f_Link(DATA)
endFunction

function f_Initialize()
    p_VARS.f_Initialize()
endFunction

function f_Register()
    p_VARS.f_Register()
endFunction

; Update Methods
function u_0_1_0()
    p_VARS.u_0_1_0()
endFunction
