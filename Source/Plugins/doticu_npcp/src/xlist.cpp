/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "xlist.h"
#include "form.h"
#include "object_ref.h"

namespace doticu_npcp { namespace XList {

    XList_t *Create() {
        XList_t *xlist = (XList_t *)Heap_Allocate(sizeof(XList_t));
        ASSERT(xlist);

        xlist->m_data = NULL;

        xlist->m_presence = (XList_t::PresenceBitfield *)Heap_Allocate(sizeof(XList_t::PresenceBitfield));
        ASSERT(xlist->m_presence);

        u64 *bits = (u64 *)xlist->m_presence->bits;
        bits[0] = 0;
        bits[1] = 0;
        bits[2] = 0;

        xlist->m_lock = BSReadWriteLock();

        return xlist;
    }

    // this does copy count
    XList_t *Copy(XList_t *xlist) {
        if (!xlist) {
            _ERROR("XList_t::Copy: Invalids args.");
            return NULL;
        }
        if (Get_Count(xlist) < 1) {
            return NULL;
        }
        if (!Can_Copy(xlist)) {
            return NULL;
        }

        XList_t *xlist_new = Create();

        for (XData_t *xdata = xlist->m_data; xdata != NULL; xdata = xdata->next) {
            if (xdata->GetType() == kExtraData_Health) {
                xlist_new->Add(kExtraData_Health, XData::Copy_Health((ExtraHealth *)xdata));
            } else if (xdata->GetType() == kExtraData_Enchantment) {
                xlist_new->Add(kExtraData_Enchantment, XData::Copy_Enchantment((ExtraEnchantment *)xdata));
            } else if (xdata->GetType() == kExtraData_Charge) {
                xlist_new->Add(kExtraData_Charge, XData::Copy_Charge((ExtraCharge *)xdata));
            } else if (xdata->GetType() == kExtraData_Count) {
                xlist_new->Add(kExtraData_Count, XData::Copy_Count((ExtraCount *)xdata));
            }
        }

        return xlist_new;
    }

    UInt32 Get_Count(XList_t *xlist) {
        if (!xlist) {
            return 0;
        }

        ExtraCount *xcount = (ExtraCount *)xlist->GetByType(kExtraData_Count);
        if (xcount) {
            return xcount->count;
        } else {
            // it's always assumed to be one if there is no count.
            return 1;
        }
    }

    void Set_Count(XList_t *xlist, UInt32 count) {
        if (!xlist || count < 1) {
            // if the count < 1, then the xlist should be deleted.
            _ERROR("XList_t::Set_Count: Invalids args.");
            return;
        }

        ExtraCount *xcount = (ExtraCount *)xlist->GetByType(kExtraData_Count);
        if (xcount) {
            xcount->count = count;
        } else {
            // it's always assumed to be one if there is no count.
            if (count > 1) {
                xlist->Add(kExtraData_Count, XData::Create_Count(count));
            }
        }
    }

    void Inc_Count(XList_t *xlist, UInt32 inc) {
        if (!xlist || inc < 1) {
            return;
        }

        ExtraCount *xcount = (ExtraCount *)xlist->GetByType(kExtraData_Count);
        if (xcount) {
            xcount->count += inc;
        } else {
            // it's always assumed to be one if there is no count.
            xlist->Add(kExtraData_Count, XData::Create_Count(inc + 1));
        }
    }

    bool Is_Same(XList_t *xlist_a, XList_t *xlist_b) {
        if (!xlist_a || !xlist_b) {
            return false;
        }

        if (!XData::Is_Same_Health(
            (ExtraHealth *)xlist_a->GetByType(kExtraData_Health),
            (ExtraHealth *)xlist_b->GetByType(kExtraData_Health))) {
            return false;
        }
        if (!XData::Is_Same_Enchantment(
            (ExtraEnchantment *)xlist_a->GetByType(kExtraData_Enchantment),
            (ExtraEnchantment *)xlist_b->GetByType(kExtraData_Enchantment))) {
            return false;
        }
        if (!XData::Is_Same_Charge(
            (ExtraCharge *)xlist_a->GetByType(kExtraData_Charge),
            (ExtraCharge *)xlist_b->GetByType(kExtraData_Charge))) {
            return false;
        }

        return true;
    }

    bool Can_Copy(XList_t *xlist) {
        return xlist->HasType(kExtraData_Health) || xlist->HasType(kExtraData_Enchantment) || xlist->HasType(kExtraData_Charge);
    }

    bool Is_Worn(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        return xlist->HasType(kExtraData_Worn) || xlist->HasType(kExtraData_WornLeft);
    }

    bool Is_Outfit_Item(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        return xlist->HasType(kExtraData_OutfitItem);
    }

    bool Is_Leveled_Item(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        return xlist->HasType(kExtraData_LeveledItem);
    }

    bool Is_Quest_Item(XList_t *xlist) {
        if (!xlist || !xlist->HasType(kExtraData_ReferenceHandle)) {
            return false;
        }

        ExtraReferenceHandle *xref = (ExtraReferenceHandle *)xlist->GetByType(kExtraData_ReferenceHandle);
        if (!xref) {
            return false;
        }

        TESObjectREFR *ref = xref->GetReference();
        if (!ref) {
            return false;
        }

        return Object_Ref::Is_Quest_Item(ref);
    }

    // the idea here is to have a way to recognize items that are part of a doticu_npcp_outfit.
    // every item that is come from the outfit2 will be an xlist with an ownership to the player
    // unless we figure out something better. I don't know how to accurately test setting owner
    // to a base form like blank armor, it could crash the game otherwise I'd do it.
    void Add_Outfit2_Flag(XList_t *xlist) {
        if (!xlist) {
            _ERROR("XList_t::Add_Outfit2_Flag: Invalids args.");
            return;
        }
        
        ExtraOwnership *xownership = (ExtraOwnership *)xlist->GetByType(kExtraData_Ownership);
        if (xownership) {
            xownership->owner = (*g_thePlayer)->baseForm;
        } else {
            xlist->Add(kExtraData_Ownership, XData::Create_Ownership((*g_thePlayer)->baseForm));
        }
    }
    bool Has_Outfit2_Flag(XList_t *xlist) {
        if (!xlist) {
            return false;
        }

        ExtraOwnership *xownership = (ExtraOwnership *)xlist->GetByType(kExtraData_Ownership);
        
        return xownership && xownership->owner == (*g_thePlayer)->baseForm;
    }

    void Log(XList_t *xlist, const std::string str_indent) {
        if (!xlist) {
            return;
        }

        u64 idx_xdata = 0;
        for (XData_t *xdata = xlist->m_data; xdata != NULL; xdata = xdata->next, idx_xdata += 1) {
            if (xdata->GetType() == kExtraData_Count) {
                _MESSAGE("%sxdata idx: %i, type: %s, count: %i",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata),
                         ((ExtraCount *)xdata)->count);
            } else if (xdata->GetType() == kExtraData_Ownership) {
                _MESSAGE("%sxdata idx: %i, type: %s, owner: %s",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata),
                         Form::Get_Name(((ExtraOwnership *)xdata)->owner));
            } else if (xdata->GetType() == kExtraData_ReferenceHandle) {
                TESObjectREFR *object = ((ExtraReferenceHandle *)xdata)->GetReference();
                if (object) {
                    _MESSAGE("%sxdata idx: %i, type: %s, name: %s, quest-item: %s, off-limits: %s",
                             str_indent.c_str(),
                             idx_xdata,
                             XData::Get_Type_String(xdata),
                             Object_Ref::Get_Name(object),
                             Object_Ref::Is_Quest_Item(object) ? "t" : "f",
                             Object_Ref::Is_Off_Limits(object) ? "t" : "f");
                    XList::Log(&object->extraData, std::string(str_indent).append("    "));
                } else {
                    _MESSAGE("%sxdata idx: %i, type: %s, (null)",
                             str_indent.c_str(),
                             idx_xdata,
                             XData::Get_Type_String(xdata));
                }
            } else {
                _MESSAGE("%sxdata idx: %i, type: %s",
                         str_indent.c_str(),
                         idx_xdata,
                         XData::Get_Type_String(xdata));
            }
        }
    }

}}
