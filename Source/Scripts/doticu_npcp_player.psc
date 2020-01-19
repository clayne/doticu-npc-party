Scriptname doticu_npcp_player extends ReferenceAlias

; Modules
doticu_npcp_main property MAIN hidden
    doticu_npcp_main function Get()
        return p_DATA.MODS.MAIN
    endFunction
endProperty
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
doticu_npcp_queues property QUEUES hidden
    doticu_npcp_queues function Get()
        return p_DATA.MODS.FUNCS.QUEUES
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
    endFunction
endProperty

; Public Constants
Actor property ACTOR_PLAYER hidden
    Actor function Get()
        return p_DATA.CONSTS.ACTOR_PLAYER
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false
bool                p_is_in_combat  = false
doticu_npcp_queue   p_queue_player  =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_is_in_combat = false
    p_queue_player = QUEUES.Create("player", 32, 5.0)
endFunction

function f_Destroy()
    QUEUES.Destroy(p_queue_player)
    p_is_in_combat = false
    p_is_created = false
endFunction

function f_Register()
    p_queue_player.Register_Alias(self, "On_Queue_Player")
    RegisterForModEvent("doticu_npcp_init_mod", "On_Init_Mod")
    RegisterForModEvent("doticu_npcp_cell_change", "On_Cell_Change")
endFunction

function f_Unregister()
endFunction

function f_Begin_Combat()
    ; there is no way for PLAYER to know when they are
    ; in combat! so we have followers tell PLAYER to begin
    if p_is_in_combat == false
        p_is_in_combat = true

        p_queue_player.Enqueue("Try_End_Combat", 5.0)

        ; here we can put functions at the beginning of battle

    endIf
endFunction

; Private Methods
function p_Try_End_Combat()
    ; because all followers may actually die in battle,
    ; and their combat state will not indicate whether
    ; the player is actually in battle, we have a looping
    ; queue set instead
    if ACTOR_PLAYER.IsInCombat() || FOLLOWERS.Are_In_Combat()
        p_queue_player.Enqueue("Try_End_Combat", 5.0)
    else
        p_End_Combat()
    endIf
endFunction

function p_End_Combat()
    ; the whole point of this is so that we can have behavior
    ; after a battle ends, e.g. resurrecting followers automatically
    if p_is_in_combat == true
        p_is_in_combat = false

        p_queue_player.Flush()

        ; here we can put functions at the end of battle
        if VARS.auto_resurrect
            FOLLOWERS.Resurrect()
        endIf

    endIf
endFunction

function p_Update_Outfits(Cell cell_curr)
    int idx_actors = cell_curr.GetNumRefs(43)
    while idx_actors > 0
        idx_actors -= 1
        Actor ref_actor = cell_curr.GetNthRef(idx_actors, 43) as Actor
        if ref_actor && ref_actor != ACTOR_PLAYER && !ref_actor.IsPlayerTeammate() && ref_actor.GetWornForm(0x00000004) == none
            ref_actor.SetPlayerTeammate(true, true)
            ref_actor.AddItem(CONSTS.WEAPON_BLANK, 1, true)
            ref_actor.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)
            ref_actor.SetPlayerTeammate(false, false)
        endIf
    endWhile
endFunction

; Public Methods
function Add_Perk(Perk perk_to_add)
    ACTOR_PLAYER.AddPerk(perk_to_add)
endFunction

function Remove_Perk(Perk perk_to_remove)
    ACTOR_PLAYER.RemovePerk(perk_to_remove)
endFunction

; Update Methods
function u_0_6_0()
    p_queue_player = QUEUES.Create("player", 32, 5.0)
    p_queue_player.Register_Alias(self, "On_Queue_Player")
    p_is_in_combat = false
endFunction

; Events
event On_Init_Mod()
    ACTOR_PLAYER.AddSpell(CONSTS.ABILITY_CELL, false)
endEvent

event OnPlayerLoadGame()
    ;p_Update_Outfits(ACTOR_PLAYER.GetParentCell()); maybe put this behind a bool
    MAIN.f_Load_Mod()
endEvent

event On_Cell_Change(Form cell_new, Form cell_old)
    ;p_Update_Outfits(cell_new); maybe put this behind a bool
    Debug.Trace("FOLLOWERS exists: " + (FOLLOWERS != none))
    FOLLOWERS.Catch_Up()
endEvent

event On_Queue_Player(string str_message)
    if p_queue_player.Should_Cancel()
        
    elseIf str_message == "Try_End_Combat"
        p_Try_End_Combat()

    endIf

    p_queue_player.Dequeue()
endEvent

event OnActorAction(int code_action, Actor ref_activator, Form form_source, int slot)

endEvent
