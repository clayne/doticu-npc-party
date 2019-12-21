Scriptname doticu_npcp_perks extends Quest hidden

; Private Constants
doticu_npcp_data            p_DATA      = none
doticu_npcp_consts          p_CONSTS    = none
doticu_npcp_perk_kiss       p_KISS      = none
doticu_npcp_perk_kill       p_KILL      = none
doticu_npcp_perk_resurrect  p_RESURRECT = none

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_KISS = DATA.CONSTS.PERK_KISS_THRALL as doticu_npcp_perk_kiss
    p_KILL = DATA.CONSTS.PERK_KILL_ESSENTIAL as doticu_npcp_perk_kill
    p_RESURRECT = DATA.CONSTS.PERK_RESURRECT_MEMBER as doticu_npcp_perk_resurrect

    p_KISS.f_Initialize(DATA)
    p_KILL.f_Initialize(DATA)
    p_RESURRECT.f_Initialize(DATA)

    Add_Perk(p_CONSTS.PERK_KISS_THRALL)
    Add_Perk(p_CONSTS.PERK_KILL_ESSENTIAL)
    Add_Perk(p_CONSTS.PERK_RESURRECT_MEMBER)
endFunction

function f_Register()
    p_KISS.f_Register()
    p_KILL.f_Register()
    p_RESURRECT.f_Register()
endFunction

; Public Functions
function Add_Perk(Perk perk_to_add)
    p_CONSTS.ACTOR_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    p_CONSTS.ACTOR_PLAYER.RemovePerk(perk_to_remove)
endFunction
