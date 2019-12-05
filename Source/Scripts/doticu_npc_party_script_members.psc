Scriptname doticu_npc_party_script_members extends Quest

; Private Constants
doticu_npc_party_script_consts  CONSTS  = none
doticu_npc_party_script_codes   CODES   = none
doticu_npc_party_script_vars    VARS    = none
doticu_npc_party_script_mods    MODS    = none
doticu_npc_party_script_aliases ALIASES = none

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ALIASES = (self as Quest) as doticu_npc_party_script_aliases

    ALIASES.f_Initialize(DATA)

    int idx_alias = 0
    int max_aliases = ALIASES.Get_Max()
    ReferenceAlias ref_alias = none
    while idx_alias < max_aliases
        ref_alias = GetNthAlias(idx_alias) as ReferenceAlias
        (ref_alias as doticu_npc_party_script_member).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npc_party_script_settler).f_Initialize(DATA, idx_alias)
        (ref_alias as doticu_npc_party_script_immobile).f_Initialize(DATA, idx_alias)
        idx_alias += 1
    endWhile
endFunction

; Public Methods
int function Create_Member(Actor ref_actor, bool make_clone = false)
    int code_return

    code_return = ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        return code_return
    endIf

    code_return = Get_Member(ref_actor).Create(make_clone)
    if code_return < 0
        ALIASES.Destroy_Alias(ref_actor)
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Destroy_Member(Actor ref_actor)
    int code_return

    if !Has_Member(ref_actor)
        return CODES.NO_MEMBER
    endIf

    code_return = Get_Member(ref_actor).Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = ALIASES.Destroy_Alias(ref_actor)
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

bool function Has_Member(Actor ref_actor)
    return ALIASES.Has_Alias(ref_actor)
endFunction

doticu_npc_party_script_member function Get_Member(Actor ref_actor)
    return ALIASES.Get_Alias(ref_actor) as doticu_npc_party_script_member
endFunction

int function Get_Count()
    return ALIASES.Get_Count()
endFunction
