/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Papyrus {

    class Handle {
    private:
        VMClassRegistry * p_ptr_registry;
        IObjectHandlePolicy *p_ptr_policy;
        UInt32 p_type;
        UInt64 p_hnd;

    public:
        // ctors, dtors
        Handle(VMClassRegistry *ptr_registry, IObjectHandlePolicy *ptr_policy, UInt32 type, void *data) {
            p_ptr_registry = ptr_registry;
            p_ptr_policy = ptr_policy;
            p_type = type;
            p_hnd = p_ptr_policy->Create(p_type, data);
        }
        Handle(UInt32 type, void *data) {
            p_ptr_registry = (*g_skyrimVM)->GetClassRegistry();
            p_ptr_policy = p_ptr_registry->GetHandlePolicy();
            p_type = type;
            p_hnd = p_ptr_policy->Create(p_type, data);
        }
        Handle() {
            p_ptr_registry = (*g_skyrimVM)->GetClassRegistry();
            p_ptr_policy = p_ptr_registry->GetHandlePolicy();
            p_type = 0;
            p_hnd = p_ptr_policy->GetInvalidHandle();
        }
        ~Handle() {
            if (Exists()) {
                p_ptr_policy->Release(p_hnd);
            }
        }

        // getters
        UInt64 Val() {
            return p_hnd;
        }
        VMClassRegistry *Registry() {
            return p_ptr_registry;
        }
        IObjectHandlePolicy *Policy() {
            return p_ptr_policy;
        }

        // bools
        bool Exists() {
            return p_hnd != p_ptr_policy->GetInvalidHandle();
        }

        // Overloads
        operator UInt64() const {
            return p_hnd;
        }
    };

    class Value {
    private:
        Handle * p_hnd_object;
        BSFixedString p_str_value;
        VMValue p_vm_value;

    public:
        // ctors, dtors
        Value(Handle *hnd_object, const char *str_value) {
            p_hnd_object = hnd_object;
            p_str_value = BSFixedString(str_value);
            if (!p_hnd_object || !p_hnd_object->Exists()) {
                return;
            }

            class Functor : public IForEachScriptObjectFunctor {
            private:
                BSFixedString * p_str_value;
                VMScriptInstance *p_ptr_script;
                SInt32 p_idx_value = -1;
            public:
                Functor(BSFixedString *str_value) {
                    p_str_value = str_value;
                }
                virtual bool Visit(VMScriptInstance *ptr_script, void *) {
                    // this function seems to be consistent only if there is one script on the object?
                    if (ptr_script) {
                        SInt32 idx_value = CALL_MEMBER_FN(ptr_script->classInfo, GetVariable)(p_str_value);
                        if (idx_value > -1) {
                            p_ptr_script = ptr_script;
                            p_idx_value = idx_value;
                            return false; // stop iterating
                        }
                        return true; // keep iterating
                    } else {
                        return true; // keep iterating
                    }
                }
                VMScriptInstance *Script() {
                    return p_ptr_script;
                }
                SInt32 Idx() {
                    return p_idx_value;
                }
            } functor(&p_str_value);

            p_hnd_object->Registry()->VisitScripts(p_hnd_object->Val(), &functor);

            VMScriptInstance *ptr_script = functor.Script();
            if (!ptr_script) {
                _MESSAGE("not a script, %s:%d", __FILE__, __LINE__);
                return;
            }

            SInt32 idx_value = functor.Idx();
            if (idx_value < 0) {
                _MESSAGE("not a variable, %s:%d", __FILE__, __LINE__);
                return;
            }

            p_hnd_object->Registry()->ExtractValue(p_hnd_object->Val(), &ptr_script->classInfo->name, idx_value, &p_vm_value);
        }

        // bools
        bool Exists() {
            return p_vm_value.GetUnmangledType() != VMValue::kType_None;
        }

        // getters
        bool As_Bool() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Bool) {
                _MESSAGE("not a bool, %s:%d", __FILE__, __LINE__);
                return false;
            } else {
                return p_vm_value.data.b;
            }
        }
        SInt32 As_Int() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Int) {
                _MESSAGE("not an int, %s:%d", __FILE__, __LINE__);
                return -1;
            } else {
                return p_vm_value.data.i;
            }
        }
        Actor *As_Actor() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Identifier) {
                _MESSAGE("not an actor, %s:%d", __FILE__, __LINE__);
                return NULL;
            } else if (!p_vm_value.data.id) {
                return NULL;
            } else {
                return (Actor *)p_hnd_object->Policy()->Resolve(kFormType_Character, p_vm_value.data.id->GetHandle());
            }
        }
        BGSBaseAlias *As_Alias() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Identifier) {
                _MESSAGE("not an alias, %s:%d", __FILE__, __LINE__);
                return NULL;
            } else if (!p_vm_value.data.id) {
                return NULL;
            } else {
                return (BGSBaseAlias *)p_hnd_object->Policy()->Resolve(kFormType_Alias, p_vm_value.data.id->GetHandle());
            }
        }
        TESObjectREFR *As_Object() {
            if (p_vm_value.GetUnmangledType() != VMValue::kType_Identifier) {
                _MESSAGE("not an object, %s:%d", __FILE__, __LINE__);
                return NULL;
            } else if (!p_vm_value.data.id) {
                return NULL;
            } else {
                return (TESObjectREFR *)p_hnd_object->Policy()->Resolve(kFormType_Reference, p_vm_value.data.id->GetHandle());
            }
        }
    };

    struct Scripts : public IForEachScriptObjectFunctor {
        Papyrus::Handle handle;
        std::vector<const char *> vec_names;
        std::vector<VMScriptInstance *> vec_scripts;

        Scripts(TESQuest *quest) {
            handle = Papyrus::Handle(kFormType_Quest, quest);
            handle.Registry()->VisitScripts(handle, this);
        }

        Scripts(BGSBaseAlias *alias) {
            handle = Papyrus::Handle(kFormType_Alias, alias);
            handle.Registry()->VisitScripts(handle, this);
        }

        virtual bool Visit(VMScriptInstance *script, void *) {
            vec_names.push_back(script->classInfo->name.data);
            vec_scripts.push_back(script);
            //_MESSAGE("%s", script->classInfo->name.data);
            return true;
        }

        VMScriptInstance *Get(const char *script_name) {
            for (u64 idx = 0, size = vec_names.size(); idx < size; idx += 1) {
                if (_stricmp(script_name, vec_names[idx]) == 0) {
                    return vec_scripts[idx];
                }
            }

            return NULL;
        }
    };

    template <typename Type>
    VMResultArray<Type> Slice_Array(VMArray<Type> *arr, UInt32 idx_from, UInt32 idx_to_ex, Type val_null) {
        VMResultArray<Type> vec_slice;
        UInt32 len_forms = arr->Length();

        if (idx_from < 0) {
            idx_from = 0;
        }
        if (idx_from > len_forms) {
            idx_from = len_forms;
        }
        if (idx_to_ex > len_forms || idx_to_ex < 0) {
            idx_to_ex = len_forms;
        }

        s64 num_elems = idx_to_ex - idx_from;
        if (num_elems < 1) {
            return vec_slice;
        }

        Type elem;
        vec_slice.reserve(num_elems);
        for (u64 idx = idx_from, idx_end = idx_to_ex; idx < idx_end; idx += 1) {
            arr->Get(&elem, idx);
            vec_slice.push_back(elem);
        }

        return vec_slice;
    }

    template <typename Type>
    VMResultArray<Type> Slice_Vector(VMResultArray<Type> vec, UInt32 from, UInt32 to_exclusive)
    {
        u64 vec_size = vec.size();
        VMResultArray<Type> slice;

        if (from < 0)
        {
            from = 0;
        }
        if (from > vec_size)
        {
            from = vec_size;
        }
        if (to_exclusive > vec_size || to_exclusive < 0)
        {
            to_exclusive = vec_size;
        }

        s64 slice_size = to_exclusive - from;
        if (slice_size > 0)
        {
            slice.reserve(slice_size);
            for (u64 idx = from; idx < to_exclusive; idx += 1)
            {
                slice.push_back(vec[idx]);
            }
        }

        return slice;
    }

}}

namespace doticu_npcp { namespace Papyrus { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
