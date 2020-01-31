;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_outfit extends ObjectReference

; Modules
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
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none
Outfit              p_OUTFIT        =  none
LeveledItem         p_LEVELED       =  none
int                 p_MAX_ITEMS     =    -1

; Private Variables
bool                p_is_created    = false
string              p_str_name      =    ""

; Friend Methods
function f_Create(doticu_npcp_data DATA, Outfit outfit_outfit, string str_name)
    p_DATA = DATA
    p_OUTFIT = outfit_outfit
    p_LEVELED = outfit_outfit.GetNthPart(0) as LeveledItem
    p_MAX_ITEMS = 64

    p_is_created = true
    p_str_name = ""
    
    self.SetDisplayName(str_name, true)
    self.SetActorOwner(CONSTS.ACTOR_PLAYER.GetActorBase())

    p_LEVELED.Revert()
endFunction

function f_Destroy()
    p_LEVELED.Revert()
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)
    self.Disable()
    self.Delete()

    p_str_name = ""
    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
bool function p_Has_Changed(Actor ref_actor)
    int num_forms
    int idx_forms
    Form ref_form
    int num_items

    if p_LEVELED.GetNumForms() != self.GetNumItems()
        return true
    endIf

    idx_forms = 0
    num_forms = p_LEVELED.GetNumForms()
    while idx_forms < num_forms
        ref_form = p_LEVELED.GetNthForm(idx_forms)
        num_items = self.GetItemCount(ref_form)
        if p_LEVELED.GetNthCount(idx_forms) != num_items
            return true
        elseIf ref_actor.GetItemCount(ref_form) != num_items
            return true
        endIf
        idx_forms += 1
    endWhile

    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if !ref_form
            return true
        endIf
        if ref_form.IsPlayable() && self.GetItemCount(ref_form) <= 0
            return true
        elseIf !ref_form.IsPlayable() && ref_actor.IsEquipped(ref_form)
            return true
        endIf
        idx_forms += 1
    endWhile

    return false
endFunction

function p_Set_Dead(Actor ref_actor)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items_outfit
    int num_items_actor
    ObjectReference ref_trash = CONTAINERS.Create_Temp()

    ; we copy one of each item, because it's dangerous to remove them within a loop
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form && ref_actor.IsEquipped(ref_form)
            ref_trash.AddItem(ref_form, 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; remove any items no longer in outfit, but the engine won't equip anything new
    idx_forms = 0
    num_forms = ref_trash.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_trash.GetNthForm(idx_forms)
        num_items_outfit = self.GetItemCount(ref_form)
        num_items_actor = ref_actor.GetItemCount(ref_form)
        if num_items_actor > num_items_outfit
            ref_actor.RemoveItem(ref_form, num_items_actor - num_items_outfit, true, ref_trash)
        endIf
        idx_forms += 1
    endWhile
endFunction

; Public Methods
bool function Exists()
    return p_is_created
endFunction

string function Get_Name()
    return p_str_name
endFunction

function Set_Name(string str_name)
    p_str_name = str_name
    self.SetDisplayName(p_str_name, true)
endFunction

int function Get_Items_Count()
    return self.GetNumItems()
endFunction

int function Get_Item_Count(Form form_item)
    return self.GetItemCount(form_item)
endFunction

function Copy(doticu_npcp_outfit ref_outfit)
    CONTAINERS.Copy(self, ref_outfit)
endFunction

function Put()
    self.SetDisplayName(p_str_name, true)
    self.Activate(CONSTS.ACTOR_PLAYER)
    Utility.Wait(0.1)
endFunction

function Get(Actor ref_actor, ObjectReference ref_inventory)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items

    ; should always refresh cache before defining it, but not
    ; the leveled list, because we always do it on a Set
    self.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)

    ; instead of using GetOutfit, we get what is playable and equipped,
    ; and store non-equipment in inventory to separate it from outfit
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form && ref_form.IsPlayable()
            num_items = ref_actor.GetItemCount(ref_form)
            if ref_actor.IsEquipped(ref_form)
                self.AddItem(ref_form, num_items, true)
            else
                ref_inventory.AddItem(ref_form, num_items, true)
            endIf
        endIf
        idx_forms += 1
    endWhile
endFunction

function Set(Actor ref_actor, bool do_force = false)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items
    ObjectReference ref_trash

    if !do_force && !p_Has_Changed(ref_actor)
        return
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

    ; we would get into an infinite loop if we don't handle this case separately
    if ref_actor.IsDead()
        return p_Set_Dead(ref_actor)
    endIf

    ; the engine will actually apply the outfit in the correct way now, which we cannot do manually
    ref_actor.SetOutfit(p_OUTFIT)

    ; the trash container is necessary because it keeps the engine from crashing or freezing when removing actor's items!
    ref_trash = CONTAINERS.Create_Temp()

    ; some items may be duplicates and not match the container's count. we can't remove one manually, so we remove all.
    ref_actor.RemoveAllItems(ref_trash, false, false); maybe move quest items somewhere else? but can't put in temp!

    ; we have to manually delete any non-playable items that are equipped. we leave everything else because they may be tokens
    Delete_Unplayable_Equipment(ref_actor)

    ; add back any discrepencies because the engine only automatically adds back one of each item
    idx_forms = 0
    num_forms = self.GetNumItems()
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        num_items = self.GetItemCount(ref_form)
        if num_items > 1
            ref_actor.AddItem(ref_form, num_items - 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; make sure everything is equipped and rendered.
    ACTORS.Update_Equipment(ref_actor)

    ; need to make sure that a clone doesn't get the same outfit, so send through until it gets its own
    Set(ref_actor)
endFunction

function Delete_Unplayable_Equipment(Actor ref_actor)
    int idx_forms
    int num_forms
    Form ref_form
    int num_items
    ObjectReference ref_trash = CONTAINERS.Create_Temp()

    ; we have to copy one of each unplayable equipped item, because when one is removed, they are all uneqipped
    idx_forms = 0
    num_forms = ref_actor.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form && !ref_form.IsPlayable() && ref_actor.IsEquipped(ref_form)
            ref_trash.AddItem(ref_form, 1, true)
        endIf
        idx_forms += 1
    endWhile

    ; then we can actually remove them
    idx_forms = 0
    num_forms = ref_trash.GetNumItems()
    while idx_forms < num_forms
        ref_form = ref_trash.GetNthForm(idx_forms)
        num_items = ref_actor.GetItemCount(ref_form)
        ref_actor.RemoveItem(ref_form, num_items, true, ref_trash)
        idx_forms += 1
    endWhile
endFunction

function Unset(Actor ref_actor)
    ObjectReference ref_container_temp = CONTAINERS.Create_Temp()

    self.RemoveAllItems(ref_container_temp, false, true)
    Set(ref_actor)
    ref_container_temp.RemoveAllItems(self, false, true)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if !Exists()
        return
    endIf

    if self.GetNumItems() >= p_MAX_ITEMS
        LOGS.Create_Note("Can only have upto "+ p_MAX_ITEMS +" items in an outfit.")
    elseIf !form_item || !form_item.IsPlayable()
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Note("Cannot add that item to an outfit.")
    endIf
endEvent
