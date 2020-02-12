;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_outfits extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
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
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return p_DATA.MODS.FUNCS.NPCS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA          =  none

; Private Variables
bool                    p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
endFunction

function f_Unregister()
endFunction

; Private Methods
doticu_npcp_outfit function p_Create(Container form_container, string str_name, int code_create = 0)
    doticu_npcp_outfit ref_outfit = CONSTS.MARKER_STORAGE.PlaceAtMe(CONSTS.CONTAINER_OUTFIT, 1, false, false) as doticu_npcp_outfit

    if VARS.fill_outfits && form_container != CONSTS.CONTAINER_OUTFIT
        ; there is a horrible bug where a container that spawns with a leveled list inside
        ; miscounts GetItemCount when the player is not in the same cell it spawned in. so
        ; we spawn items in variant outfits in a temp container and move them to the outfit
        ObjectReference ref_temp = CONSTS.ACTOR_PLAYER.PlaceAtMe(form_container, 1, false, false)
        Utility.Wait(0.1); trying this to see if it spawns all items now
        ref_temp.RemoveAllItems(ref_outfit, false, true)
    endIf

    ref_outfit.f_Create(p_DATA, str_name, code_create)
    ref_outfit.f_Register()

    return ref_outfit
endFunction

; Public Methods
doticu_npcp_outfit function Create(string str_name = "Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name)
endFunction

doticu_npcp_outfit function Create_Settler(string str_name = "Settler Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_SETTLER, str_name)
endFunction

doticu_npcp_outfit function Create_Thrall(string str_name = "Thrall Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_THRALL, str_name)
endFunction

doticu_npcp_outfit function Create_Immobile(string str_name = "Immobile Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_IMMOBILE, str_name)
endFunction

doticu_npcp_outfit function Create_Follower(string str_name = "Follower Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT_FOLLOWER, str_name)
endFunction

doticu_npcp_outfit function Create_Vanilla(string str_name = "Vanilla Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name, CODES.OUTFIT_VANILLA)
endFunction

doticu_npcp_outfit function Create_Default(string str_name = "Default Outfit")
    return p_Create(CONSTS.CONTAINER_OUTFIT, str_name, CODES.OUTFIT_DEFAULT)
endFunction

function Destroy(doticu_npcp_outfit ref_outfit)
    if ref_outfit
        ref_outfit.f_Destroy()
    endIf
endFunction

ObjectReference function Get_Default_Cache(Actor ref_actor, Outfit outfit_default)
    ; the point of this function is to have a goto container that
    ; has most of the loose outfit items on an npc. it's intended
    ; to be created the first time they are added into the system.
    ; part of the reason we are doing this is because some npcs
    ; don't have default outfits, especially follower mods.
    ; sometimes they have unplayable equipment, and this is removed
    ; in unvanilla outfits because the player can't manipulate them

    int idx_forms
    Form form_item
    int num_items
    ObjectReference ref_item
    ObjectReference ref_outfit = CONTAINERS.Create_Temp()
    ObjectReference ref_cache = CONTAINERS.Create_Temp()

    if outfit_default
        ; we cache because if anything in actor inventory is in here, we can
        ; ignore it as we use the outfit_default itself in the outfit algorithm
        idx_forms = outfit_default.GetNumParts()
        while idx_forms > 0
            idx_forms -= 1
            form_item = outfit_default.GetNthPart(idx_forms)
            ref_outfit.AddItem(form_item, 1, true); will expand LeveledItems!
        endWhile
    endIf

    ; we basically want every item in the inventory that is not an outfit item yet equips
    idx_forms = ref_actor.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item
            ; we need to work with this form before it might be changed
            num_items = ref_actor.GetItemCount(form_item)
            ref_item = form_item as ObjectReference
            if ref_item
                ; we cannot risk removing a quest item, etc.
                form_item = ref_item.GetBaseObject()
            endIf
            if ref_outfit.GetItemCount(form_item) < 1
                if form_item as Armor || form_item as Weapon || form_item as Ammo
                    ; we don't bother with Light, or other possible equips
                    ref_cache.AddItem(form_item, num_items, true)
                endIf
            endIf
        endIf
    endWhile

    return ref_cache
endFunction

function Outfit_Vanilla(Actor ref_actor, Outfit outfit_vanilla)
    if !ref_actor || !outfit_vanilla
        return
    endIf

    int idx_forms
    Form form_item
    int num_items
    ObjectReference ref_item
    ObjectReference ref_weapons = CONTAINERS.Create_Temp()
    ObjectReference ref_temp = CONTAINERS.Create_Temp()
    bool is_teammate = ref_actor.IsPlayerTeammate()

    ; we need to cache weapons because crash prevention deletes them
    idx_forms = ref_actor.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item
            ; we need to work with this form before it might be changed
            num_items = ref_actor.GetItemCount(form_item)
            ref_item = form_item as ObjectReference
            if ref_item
                ; we cannot risk removing a quest item, etc.
                form_item = ref_item.GetBaseObject()
            endIf
            if form_item as Weapon || form_item as Ammo
                ref_weapons.AddItem(form_item, num_items, true)
            endIf
        endIf
    endWhile

    ; seems to prevent crashes with clones and weapons...?
    ref_actor.RemoveAllItems(ref_temp, false, false)
    ref_temp.RemoveAllItems(ref_actor, false, false)

    ; this will stop the actor from rendering while we manage its inventory
    ref_actor.SetPlayerTeammate(false, false)
    
    ref_actor.SetOutfit(CONSTS.OUTFIT_TEMP)
    ref_actor.SetOutfit(outfit_vanilla)

    ; add weapons back before render
    idx_forms = ref_weapons.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_weapons.GetNthForm(idx_forms)
        ref_actor.AddItem(form_item, ref_weapons.GetItemCount(form_item), true)
    endWhile

    ; doing this allows us to render all at once, which is far more efficient
    ref_actor.SetPlayerTeammate(true, true)
    ref_actor.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_actor.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)

    ; make sure to restore render status
    if !is_teammate
        ref_actor.SetPlayerTeammate(false, false)
    endIf
endFunction

function Outfit_Clone(Actor ref_clone, Actor ref_actor)
    if !ref_clone || !ref_actor
        return
    endIf

    int idx_forms
    Form form_item
    int num_items
    ObjectReference ref_item
    bool is_equipped
    ObjectReference ref_junk = CONTAINERS.Create_Temp()
    bool is_teammate = ref_clone.IsPlayerTeammate()
    Outfit outfit_vanilla = ACTORS.Get_Base_Outfit(ref_clone)

    ; this will stop the actor from rendering while we manage its inventory
    ref_clone.SetPlayerTeammate(false, false)

    ; this way no items will automatically be added back when we remove them
    ref_clone.SetOutfit(CONSTS.OUTFIT_TEMP)

    ; it's error prone to remove items from actor unless they are cached
    idx_forms = ref_clone.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_clone.GetNthForm(idx_forms)
        if form_item && !(form_item as ObjectReference)
            ; we completely avoid any references and leave them alone.
            if form_item.IsPlayable() || ref_clone.IsEquipped(form_item)
                ; any playable item is fair game, but only equipped unplayables are accounted for
                ref_junk.AddItem(form_item, ref_clone.GetItemCount(form_item), true)
            endIf
        endIf
    endWhile

    ; cleaning up the inventory of any junk is essential to controlling the outfit
    idx_forms = ref_junk.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_junk.GetNthForm(idx_forms)
        ref_clone.RemoveItem(form_item, ref_junk.GetItemCount(form_item), true, ref_junk)
    endWhile

    ; we just need what's currently equipped on actor
    idx_forms = ref_actor.GetNumItems()
    while idx_forms > 0
        idx_forms -= 1
        form_item = ref_actor.GetNthForm(idx_forms)
        if form_item
            ; we need to work with this form before it might be changed
            num_items = ref_actor.GetItemCount(form_item)
            is_equipped = ref_actor.IsEquipped(form_item)
            ref_item = form_item as ObjectReference
            if ref_item
                ; we cannot risk removing a quest item, etc.
                form_item = ref_item.GetBaseObject()
            endIf
            if is_equipped
                ref_clone.AddItem(form_item, num_items - ref_clone.GetItemCount(form_item), true)
            endIf
        endIf
    endWhile

    ; doing this allows us to render all at once, which is far more efficient
    ref_clone.SetPlayerTeammate(true, true)
    ref_clone.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_clone.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)

    ; make sure to restore render status
    if !is_teammate
        ref_clone.SetPlayerTeammate(false, false)
    endIf

    ; make sure that the base is set to have the vanilla algorithm in place
    ACTORS.Set_Base_Outfit(ref_clone, outfit_vanilla)
endFunction

function Restore_Actor(Actor ref_actor)
    if ACTORS.Is_Alive(ref_actor)
        ; we could make an option to set the default or the vanilla outfit.
        ;Outfit outfit_default = NPCS.Get_Default_Outfit(ref_actor)
        Outfit outfit_vanilla = ACTORS.Get_Base_Outfit(ref_actor)
        if outfit_vanilla
            ref_actor.SetOutfit(CONSTS.OUTFIT_TEMP)
            ref_actor.SetOutfit(outfit_vanilla)
        endIf
    endIf
endFunction
