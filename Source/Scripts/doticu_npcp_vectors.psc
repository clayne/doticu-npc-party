;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_vectors extends Quest

; Public Constants
ObjectReference property MARKER_STORAGE hidden
    ObjectReference function Get()
        return doticu_npcp_consts.Storage_Marker()
    endFunction
endProperty
MiscObject property MISC_VECTOR_FORM hidden
    MiscObject function Get()
        return doticu_npcp_consts.Form_Vector()
    endFunction
endProperty

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create()
    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

; Public Methods
doticu_npcp_vector_form function Create_Form_Vector(int init_max = 0, Form item_fill = none, float grow_rate = 1.5)
    doticu_npcp_vector_form ref_vec = MARKER_STORAGE.PlaceAtMe(MISC_VECTOR_FORM as Form, 1, true, false) as doticu_npcp_vector_form
    ref_vec.f_Create(init_max, item_fill, grow_rate)
    return ref_vec
endFunction

function Destroy_Form_Vector(doticu_npcp_vector_form ref_vec)
    if ref_vec
        ref_vec.f_Destroy()
        ref_vec.Disable()
        ref_vec.Delete()
    endIf
endFunction
