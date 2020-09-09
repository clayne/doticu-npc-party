; Copyright © 2020 r-neal-kelly, aka doticu

Scriptname doticu_npcp_player extends ReferenceAlias

; Private Variables
bool p_is_in_combat = false

; Native Methods
bool function Is_Party_In_Combat() native
event OnControlDown(string control) native
event OnActorAction(int action_code, Actor ref_actor, Form tool, int tool_slot) native
event On_Cell_Change(Form new_cell, Form old_cell) native

; Friend Methods
function f_Register()
    RegisterForModEvent("doticu_npcp_cell_change", "On_Cell_Change")
    RegisterForControl("Sneak")
    RegisterForControl("Forward")
    RegisterForActorAction(doticu_npcp_codes.ACTION_DRAW_END())
endFunction
