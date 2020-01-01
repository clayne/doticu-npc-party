Scriptname doticu_npcp_outfit extends ObjectReference

; Private Constants
doticu_npcp_data    p_DATA      = none
Outfit              p_OUTFIT    = none
LeveledItem         p_LEVELED   = none
int                 p_MAX_ITEMS =   64

; Public Constants
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
    endFunction
endProperty
doticu_npcp_outfits property OUTFITS hidden
    doticu_npcp_outfits function Get()
        return p_DATA.MODS.FUNCS.OUTFITS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty

; Friend Methods
function f_Create(doticu_npcp_data DATA, Outfit form_outfit, string str_name)
    p_DATA = DATA
    p_OUTFIT = form_outfit
    p_LEVELED = form_outfit.GetNthPart(0) as LeveledItem
    self.SetDisplayName(str_name, true)
    self.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())
endFunction

function f_Destroy()
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)
    self.Disable()
    self.Delete()
endFunction

; Public Methods
string function Get_Name()
    return self.GetDisplayName()
endFunction

function Set_Name(string str_name)
    self.SetDisplayName(str_name, true)
endFunction

int function Count_Items()
    return self.Count_Items()
endFunction

int function Count_Item(Form form_item)
    return self.Count_Item(form_item)
endFunction

function Put()
    self.Activate(CONSTS.ACTOR_PLAYER)
endFunction

function Get(Actor ref_actor)
    int num_forms
    int idx_forms
    Form ref_form
    int num_items

    ; we refresh the cache
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)
    p_LEVELED.Revert()

    ; then copy what is valid and equipped, which is how we define outfit, instead of using GetOutfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if OUTFITS.Is_Valid_Item(ref_form) && ref_actor.IsEquipped(ref_form)
            num_items = ref_actor.GetItemCount(ref_form)
            self.AddItem(ref_form, num_items, true)
            p_LEVELED.AddForm(ref_form, 1, num_items)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Set(Actor ref_actor, bool do_force = false)
    int num_forms
    int idx_forms
    Form ref_form
    int num_items
    bool do_bail

    ; if don't force, check to make sure outfit is now different, else bail
    ; I would also like this to be able to check if the actor has additional items they shouldn't
    if !do_force && p_LEVELED.GetNumForms() == self.GetNumItems()
        num_forms = p_LEVELED.GetNumForms()
        idx_forms = 0
        do_bail = true
        while do_bail && idx_forms < num_forms
            ref_form = p_LEVELED.GetNthForm(idx_forms)
            num_items = p_LEVELED.GetNthCount(idx_forms)
            if num_items != self.GetItemCount(ref_form)
                do_bail = false
            elseIf num_items != ref_actor.GetItemCount(ref_form)
                do_bail = false
            endIf
            idx_forms += 1
        endWhile

        if do_bail
            return
        endIf
    endIf

    ; updating the leveled list, which is attached to Outfit form, is what gives the engine the actual items
    p_LEVELED.Revert()
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        p_LEVELED.AddForm(ref_form, 1, self.GetItemCount(ref_form))
        idx_forms += 1
    endWhile

    ; the engine will ignore this call if it's the same outfit already equipped, so we use a different one
    ref_actor.SetOutfit(CONSTS.OUTFIT_EMPTY)

    ; the engine will actually apply the outfit in the correct way now, which we cannot do manually
    ref_actor.SetOutfit(p_OUTFIT)

    ; prevents the game from crashing or freezing around the next step
    Utility.Wait(0.2); still getting crashes and freezes. This seems like it's just not going to work. I don't think we can detect when rendering is done here

    ; we remove everything playable, then one of each outfit item is reapplied by engine, thus removing any possible dupes
    ref_actor.RemoveAllItems(none, false, true); maybe instead of removing everything, we can just remove weapons and reapply them.

    ; add back any discrepencies because the engine only automatically adds back one of each item
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        num_items = self.GetItemCount(ref_form)
        if num_items > 1
            ref_actor.AddItem(ref_form, num_items - 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; need to make sure that a clone doesn't get the same outfit. so check actor playables. if no match, send through func again with do_force == true

    ; make sure everything is equipped and rendered
    ACTORS.Update_Equipment(ref_actor)
endFunction

function Remove_Inventory(Actor ref_actor, ObjectReference ref_container = none)
    Form[] arr_leveled
    int num_forms
    int idx_forms
    Form ref_form
    int num_items

    ; So we can determine what items are in the currently equipped outfit
    num_forms = p_LEVELED.GetNumForms()
    arr_leveled = Utility.CreateFormArray(num_forms, none)
    idx_forms = 0
    while idx_forms < num_forms
        arr_leveled[idx_forms] = p_LEVELED.GetNthForm(idx_forms)
        idx_forms += 1
    endWhile

    ; remove inventory minus current outfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if !ref_form.IsPlayable()
            idx_forms += 1
        elseIf arr_leveled.Find(ref_form) > -1
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form) - 1, true, ref_container); no 1, do leveled count
            idx_forms += 1
        else
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, ref_container)
            num_forms -= 1
        endIf
    endWhile

    ; because stacked items stick, we get the engine to automatically add back only one. removes only playable
    ref_actor.RemoveAllItems(none, false, true)

    ; and then we add back any discrepencies in the outfit
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        num_items = self.GetItemCount(ref_form)
        if num_items > 1
            ref_actor.AddItem(ref_form, num_items - 1, true)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Unset(Actor ref_actor)
    ObjectReference ref_container_temp = CONTAINERS.Create_Temp()

    self.RemoveAllItems(ref_container_temp, false, true)
    Set(ref_actor)
    ref_container_temp.RemoveAllItems(self, false, true)
endFunction

; Update Methods
function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if self.GetNumItems() >= p_MAX_ITEMS
        LOGS.Create_Note("Can only have upto "+ p_MAX_ITEMS +" items in an outfit.")
    elseIf !OUTFITS.Is_Valid_Item(form_item)
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Can only add armor or weapons to an outfit.")
    endIf
endEvent
