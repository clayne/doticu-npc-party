Scriptname doticu_npc_party_script_settler extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
doticu_npc_party_script_member      MEMBER      = none
int                                 ID_ALIAS    =   -1
ObjectReference                     REF_MARKER  = none

; Private Variables
bool    is_created      = false
Actor   ref_actor       =  none

; Private Methods
function p_Token()
    ACTOR2.Token(ref_actor, CONSTS.TOKEN_SETTLER)
endFunction

function p_Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_SETTLER)
endFunction

function p_Settle()
    REF_MARKER.MoveTo(ref_actor)
endFunction

function p_Unsettle()
    REF_MARKER.MoveToMyEditorLocation()
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int idx_alias)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    MEMBER = (self as ReferenceAlias) as doticu_npc_party_script_member
    ID_ALIAS = idx_alias
    REF_MARKER = DATA.CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(idx_alias) as ObjectReference
endFunction

int function f_Enforce()
    if !Exists()
        return CODES.NO_SETTLER
    endIf

    p_Token()
    ; p_Settle() is not f_Enforce()'d

    return CODES.SUCCESS
endFunction

; Public Methods
int function Create()
    int code_return

    if Exists()
        return CODES.EXISTS
    endIf
    ref_actor = GetActorReference()
    if !ref_actor
        return CODES.NO_ACTOR
    endIf
    if !MEMBER.Exists()
        return CODES.NO_MEMBER
    endIf
    is_created = true

    ;/code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf/;

    p_Settle()

    return CODES.SUCCESS
endFunction

int function Destroy()
    if !Exists()
        return CODES.NO_SETTLER
    endIf

    p_Unsettle()
    p_Untoken()

    ref_actor = none
    is_created = false

    return CODES.SUCCESS
endFunction

bool function Exists()
    return is_created
endFunction

int function Resettle()
    int code_return

    if !Exists()
        return CODES.NO_SETTLER
    endIf

    p_Settle()

    code_return = MEMBER.f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction
