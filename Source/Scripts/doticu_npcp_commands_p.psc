Scriptname doticu_npcp_commands_p extends Quest

; Modules
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
    endFunction
endProperty
doticu_npcp_commands_p_notes property NOTES hidden
    doticu_npcp_commands_p_notes function Get()
        return (self as Quest) as doticu_npcp_commands_p_notes
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA              =  none

; Private Variables
bool                p_is_created        = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    NOTES.f_Create(DATA)

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false

    NOTES.f_Destroy()
endFunction

function f_Register()
    NOTES.f_Register()
endFunction

; Public Methods
function Member(Actor ref_actor)
    if MEMBERS.Should_Clone_Actor(ref_actor)
        Clone(ref_actor)
        return
    endIf

    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    NOTES.Member(MEMBERS.Create_Member(ref_actor), str_name)
endFunction

function Unmember(Actor ref_actor)
    if MEMBERS.Should_Unclone_Member(MEMBERS.Get_Member(ref_actor))
        Unclone(ref_actor)
        return
    endIf

    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    NOTES.Unmember(MEMBERS.Destroy_Member(ref_actor), str_name)
endFunction

function Clone(Actor ref_actor)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if ACTORS.Is_Generic(ref_actor)
        LOGS.Create_Note("Please wait, cloning may take a while.", false)
    endIf

    NOTES.Clone(MEMBERS.Create_Member(ref_actor, true), str_name)
endFunction

function Unclone(Actor ref_actor)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    NOTES.Unclone(MEMBERS.Destroy_Member(ref_actor, true), str_name)
endFunction

function Pack(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Pack(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Pack(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Pack(ref_member.Pack(), str_name)
endFunction

function Outfit(Actor ref_actor, int code_outfit, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if code_outfit != CODES.IS_MEMBER &&\
        code_outfit != CODES.IS_SETTLER &&\
        code_outfit != CODES.IS_THRALL &&\
        code_outfit != CODES.IS_FOLLOWER &&\
        code_outfit != CODES.IS_IMMOBILE
        code_outfit = CODES.IS_MEMBER; eventually VARS.default_outfit
    endIf
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Outfit(code_return, str_name, code_outfit)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Outfit(CODES.HASNT_MEMBER, str_name, code_outfit)
        return
    endIf

    if code_outfit == CODES.IS_MEMBER
        NOTES.Outfit(ref_member.Outfit_Member(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_SETTLER
        NOTES.Outfit(ref_member.Outfit_Settler(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_THRALL
        NOTES.Outfit(ref_member.Outfit_Thrall(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_FOLLOWER
        NOTES.Outfit(ref_member.Outfit_Follower(), str_name, code_outfit)
    elseIf code_outfit == CODES.IS_IMMOBILE
        NOTES.Outfit(ref_member.Outfit_Immobile(), str_name, code_outfit)
    endIf
endFunction

function Outfit_Member(Actor ref_actor, bool auto_create)
    Outfit(ref_actor, CODES.IS_MEMBER, auto_create)
endFunction

function Outfit_Settler(Actor ref_actor, bool auto_create)
    Outfit(ref_actor, CODES.IS_SETTLER, auto_create)
endFunction

function Outfit_Thrall(Actor ref_actor, bool auto_create)
    Outfit(ref_actor, CODES.IS_THRALL, auto_create)
endFunction

function Outfit_Follower(Actor ref_actor, bool auto_create)
    Outfit(ref_actor, CODES.IS_FOLLOWER, auto_create)
endFunction

function Outfit_Immobile(Actor ref_actor, bool auto_create)
    Outfit(ref_actor, CODES.IS_IMMOBILE, auto_create)
endFunction

function Unoutfit(Actor ref_actor, bool auto_create)
    ; can create a toggle between these two
endFunction

function Resurrect(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        NOTES.Resurrect(MEMBERS.Create_Member(ref_actor), str_name)
        return
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Resurrect(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Resurrect(ref_member.Resurrect(), str_name)
endFunction

function Settle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Settle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Settle(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Settle(ref_member.Settle(), str_name)
endFunction

function Unsettle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Unsettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unsettle(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Unsettle(ref_member.Unsettle(), str_name)
endFunction

function Resettle(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Resettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Resettle(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Settler()
        code_return = ref_member.Settle()
        if code_return < 0
            NOTES.Resettle(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_settler ref_settler = ref_member.Get_Settler()
    if !ref_settler
        NOTES.Resettle(CODES.HASNT_SETTLER, str_name)
        return
    endIf

    NOTES.Resettle(ref_settler.Resettle(), str_name)
endFunction

function Enthrall(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Enthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Enthrall(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Enthrall(ref_member.Enthrall(), str_name)
endFunction

function Unthrall(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Unthrall(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unthrall(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Unthrall(ref_member.Unthrall(), str_name)
endFunction

function Immobilize(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Immobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Immobilize(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Immobilize(ref_member.Immobilize(), str_name)
endFunction

function Mobilize(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Mobilize(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Mobilize(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Mobilize(ref_member.Mobilize(), str_name)
endFunction

function Paralyze(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Paralyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Paralyze(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Immobile()
        code_return = ref_member.Immobilize()
        if code_return < 0
            NOTES.Paralyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_immobile ref_immobile = ref_member.Get_Immobile()
    if !ref_immobile
        NOTES.Paralyze(CODES.ISNT_IMMOBILE, str_name)
        return
    endIf
    
    NOTES.Paralyze(ref_immobile.Paralyze(), str_name)
endFunction

function Unparalyze(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Unparalyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unparalyze(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Immobile()
        code_return = ref_member.Immobilize()
        if code_return < 0
            NOTES.Unparalyze(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_immobile ref_immobile = ref_member.Get_Immobile()
    if !ref_immobile
        NOTES.Unparalyze(CODES.ISNT_IMMOBILE, str_name)
        return
    endIf

    NOTES.Unparalyze(ref_immobile.Unparalyze(), str_name)
endFunction

function Style(Actor ref_actor, int code_style, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if code_style != CODES.IS_DEFAULT &&\
        code_style != CODES.IS_WARRIOR &&\
        code_style != CODES.IS_MAGE &&\
        code_style != CODES.IS_ARCHER
        code_style = VARS.auto_style; eventually VARS.default_style
    endIf

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Style(code_return, str_name, code_style)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Style(CODES.HASNT_MEMBER, str_name, code_style)
        return
    endIf

    if code_style == CODES.IS_DEFAULT
        NOTES.Style(ref_member.Style_Default(), str_name, code_style)
    elseIf code_style == CODES.IS_WARRIOR
        NOTES.Style(ref_member.Style_Warrior(), str_name, code_style)
    elseIf code_style == CODES.IS_MAGE
        NOTES.Style(ref_member.Style_Mage(), str_name, code_style)
    elseIf code_style == CODES.IS_ARCHER
        NOTES.Style(ref_member.Style_Archer(), str_name, code_style)
    endIf
endFunction

function Style_Default(Actor ref_actor, bool auto_create)
    Style(ref_actor, CODES.IS_DEFAULT, auto_create)
endFunction

function Style_Warrior(Actor ref_actor, bool auto_create)
    Style(ref_actor, CODES.IS_WARRIOR, auto_create)
endFunction

function Style_Mage(Actor ref_actor, bool auto_create)
    Style(ref_actor, CODES.IS_MAGE, auto_create)
endFunction

function Style_Archer(Actor ref_actor, bool auto_create)
    Style(ref_actor, CODES.IS_ARCHER, auto_create)
endFunction

function Vitalize(Actor ref_actor, int code_vitality, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)
    
    if code_vitality != CODES.IS_MORTAL &&\
        code_vitality != CODES.IS_PROTECTED &&\
        code_vitality != CODES.IS_ESSENTIAL &&\
        code_vitality != CODES.IS_INVULNERABLE
        code_vitality = VARS.auto_vitality; eventually VARS.default_vitality
    endIf
    
    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Vitalize(code_return, str_name, code_vitality)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Vitalize(CODES.HASNT_MEMBER, str_name, code_vitality)
        return
    endIf

    if code_vitality == CODES.IS_MORTAL
        NOTES.Vitalize(ref_member.Vitalize_Mortal(), str_name, code_vitality)
    elseIf code_vitality == CODES.IS_PROTECTED
        NOTES.Vitalize(ref_member.Vitalize_Protected(), str_name, code_vitality)
    elseIf code_vitality == CODES.IS_ESSENTIAL
        NOTES.Vitalize(ref_member.Vitalize_Essential(), str_name, code_vitality)
    elseIf code_vitality == CODES.IS_INVULNERABLE
        NOTES.Vitalize(ref_member.Vitalize_Invulnerable(), str_name, code_vitality)
    endIf
endFunction

function Vitalize_Mortal(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, CODES.IS_MORTAL, auto_create)
endFunction

function Vitalize_Protected(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, CODES.IS_PROTECTED, auto_create)
endFunction

function Vitalize_Essential(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, CODES.IS_ESSENTIAL, auto_create)
endFunction

function Vitalize_Invulnerable(Actor ref_actor, bool auto_create)
    Vitalize(ref_actor, CODES.IS_INVULNERABLE, auto_create)
endFunction

function Follow(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Follow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Follow(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Follow(ref_member.Follow(), str_name)
endFunction

function Unfollow(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Unfollow(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unfollow(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    NOTES.Unfollow(ref_member.Unfollow(), str_name)
endFunction

function Sneak(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Sneak(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return < 0
            NOTES.Sneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        NOTES.Sneak(CODES.HASNT_FOLLOWER, str_name)
        return
    endIf

    NOTES.Sneak(ref_follower.Sneak(), str_name)
endFunction

function Unsneak(Actor ref_actor, bool auto_create)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    if auto_create && !MEMBERS.Has_Member(ref_actor)
        code_return = MEMBERS.Create_Member(ref_actor)
        if code_return < 0
            NOTES.Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Unsneak(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    if auto_create && !ref_member.Is_Follower()
        code_return = ref_member.Follow()
        if code_return < 0
            NOTES.Unsneak(code_return, str_name)
            return
        endIf
    endIf

    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if !ref_follower
        NOTES.Unsneak(CODES.HASNT_FOLLOWER, str_name)
        return
    endIf

    NOTES.Unsneak(ref_follower.Unsneak(), str_name)
endFunction

function Summon(Actor ref_actor)
    int code_return
    string str_name = ACTORS.Get_Name(ref_actor)

    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        NOTES.Summon(CODES.HASNT_MEMBER, str_name)
        return
    endIf

    ref_member.Summon()

    NOTES.Summon(CODES.SUCCESS, str_name)
endFunction

function Toggle_Member(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member
        Unmember(ref_actor)
    else
        Member(ref_actor)
    endIf
endFunction

function Toggle_Settler(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Settler()
        Unsettle(ref_actor, true)
    else
        Settle(ref_actor, true)
    endIf
endFunction

function Toggle_Thrall(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Thrall()
        Unthrall(ref_actor, true)
    else
        Enthrall(ref_actor, true)
    endIf
endFunction

function Toggle_Immobile(Actor ref_actor)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if ref_member && ref_member.Is_Immobile()
        Mobilize(ref_actor, true)
    else
        Immobilize(ref_actor, true)
    endIf
endFunction

function Toggle_Paralyzed(Actor ref_actor)
    doticu_npcp_immobile ref_immobile = MEMBERS.Get_Immobile(ref_actor)
    if ref_immobile && ref_immobile.Is_Paralyzed()
        Unparalyze(ref_actor, true)
    else
        Paralyze(ref_actor, true)
    endIf
endFunction

function Toggle_Follower(Actor ref_actor)
    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower
        Unfollow(ref_actor, true)
    else
        Follow(ref_actor, true)
    endIf
endFunction

function Toggle_Sneak(Actor ref_actor)
    doticu_npcp_follower ref_follower = FOLLOWERS.Get_Follower(ref_actor)
    if ref_follower && ref_follower.Is_Sneak()
        Unsneak(ref_actor, true)
    else
        Sneak(ref_actor, true)
    endIf
endFunction

function Cycle_Style(Actor ref_actor, bool auto_create)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        Style(ref_actor, VARS.auto_style, auto_create)
    elseIf ref_member.Is_Styled_Default()
        Style(ref_actor, CODES.IS_WARRIOR, auto_create)
    elseIf ref_member.Is_Styled_Warrior()
        Style(ref_actor, CODES.IS_MAGE, auto_create)
    elseIf ref_member.Is_Styled_Mage()
        Style(ref_actor, CODES.IS_ARCHER, auto_create)
    elseIf ref_member.Is_Styled_Archer()
        Style(ref_actor, CODES.IS_DEFAULT, auto_create)
    endIf
endFunction

function Cycle_Vitality(Actor ref_actor, bool auto_create)
    doticu_npcp_member ref_member = MEMBERS.Get_Member(ref_actor)
    if !ref_member
        Vitalize(ref_actor, VARS.auto_vitality, auto_create)
    elseIf ref_member.Is_Vitalized_Mortal()
        Vitalize(ref_actor, CODES.IS_PROTECTED, auto_create)
    elseIf ref_member.Is_Vitalized_Protected()
        Vitalize(ref_actor, CODES.IS_ESSENTIAL, auto_create)
    elseIf ref_member.Is_Vitalized_Essential()
        Vitalize(ref_actor, CODES.IS_INVULNERABLE, auto_create)
    elseIf ref_member.Is_Vitalized_Invulnerable()
        Vitalize(ref_actor, CODES.IS_MORTAL, auto_create)
    endIf
endFunction

function Followers_Summon_All()
    NOTES.Followers_Summon_All(FOLLOWERS.Summon_All())
endFunction

function Followers_Summon_Mobile()
    NOTES.Followers_Summon_Mobile(FOLLOWERS.Summon_Mobile())
endFunction

function Followers_Summon_Immobile()
    NOTES.Followers_Summon_Immobile(FOLLOWERS.Summon_Immobile())
endFunction

function Followers_Summon_Mobile_Behind()
    NOTES.Followers_Summon_Mobile_Behind(FOLLOWERS.Summon_Mobile_Behind())
endFunction

function Followers_Settle()
    NOTES.Followers_Settle(FOLLOWERS.Settle())
endFunction

function Followers_Unsettle()
    NOTES.Followers_Unsettle(FOLLOWERS.Unsettle())
endFunction

function Followers_Immobilize()
    NOTES.Followers_Immobilize(FOLLOWERS.Immobilize())
endFunction

function Followers_Mobilize()
    NOTES.Followers_Mobilize(FOLLOWERS.Mobilize())
endFunction

function Followers_Sneak()
    NOTES.Followers_Sneak(FOLLOWERS.Sneak())
endFunction

function Followers_Unsneak()
    NOTES.Followers_Unsneak(FOLLOWERS.Unsneak())
endFunction

function Followers_Resurrect()
    NOTES.Followers_Resurrect(FOLLOWERS.Resurrect())
endFunction

function Followers_Unfollow()
    NOTES.Followers_Unfollow(FOLLOWERS.Unfollow())
endFunction

function Followers_Unmember()
    NOTES.Followers_Unmember(FOLLOWERS.Unmember())
endFunction

function Toggle_Followers_Settle()
    if FOLLOWERS.Get_Count_Settler() > 0
        Followers_Unsettle()
    else
        Followers_Settle()
    endIf
endFunction

function Toggle_Followers_Immobilize()
    if FOLLOWERS.Get_Count_Immobile() > 0
        Followers_Mobilize()
    else
        Followers_Immobilize()
    endIf
endFunction

function Toggle_Followers_Sneak()
    if FOLLOWERS.Get_Count_Sneak() > 0
        Followers_Unsneak()
    else
        Followers_Sneak()
    endIf
endFunction
