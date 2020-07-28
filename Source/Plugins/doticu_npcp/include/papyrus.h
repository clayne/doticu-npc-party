/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Papyrus {

    // a lot of credit for deciphering these classes goes to Ryan-rsm-McKenzie of CommonLibSSE as well as the SKSE team
    class Handle_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        UInt64 handle = 0;

        template <typename Type>
        Handle_t(Type* instance);
        Handle_t(Form_t* form);
        Handle_t(UInt64 handle);
        Handle_t();

        bool Is_Valid();

        operator UInt64();
    };
    STATIC_ASSERT(sizeof(Handle_t) == 0x8);

    class Class_Info_t;
    class Object_t;
    class Array_t;
    class Type_t;
    class Virtual_Machine_t { // Registry_t
    public:
        static Virtual_Machine_t* Self();
        //template <typename BSObject>
        //static void Send_Event(BSObject* object, String_t event_name, IFunctionArguments* arguments);
    public:
        virtual ~Virtual_Machine_t(); // 00
        virtual void _01(void); // 01
        virtual void _02(void); // 02
        virtual void _03(void); // 03
        virtual void _04(void); // 04
        virtual void _05(void); // 05
        virtual void _06(void); // 06
        virtual void _07(void); // 07
        virtual void _08(void); // 08
        virtual Bool_t Load_Class_Info(String_t* class_name, Class_Info_t** info_out); // 09, call Class_Info_t Free() after use
        virtual Bool_t Load_Class_Info2(Type_ID_t type_id, Class_Info_t** info_out); // 0A, call Class_Info_t Free() after use
        virtual Bool_t Class_Info(String_t* class_name, Class_Info_t** info_out); // 0B, call Class_Info_t Free() after use
        virtual Bool_t Class_Info2(Type_ID_t type_id, Class_Info_t** info_out); // 0C, call Class_Info_t Free() after use
        virtual void _0D(void); // 0D
        virtual void _0E(void); // 0E
        virtual void _0F(void); // 0F
        virtual void _10(void); // 10
        virtual void _11(void); // 11
        virtual void _12(void); // 12
        virtual void _13(void); // 13
        virtual void _14(void); // 14
        virtual Bool_t Create_Object2(String_t* class_name, Object_t** object_out); // 15
        virtual Bool_t Create_Array(Type_t* type, UInt32 count, Array_t** array_out); // 16, SKSE has Variable_t* for first arg?
        virtual void _17(void); // 17
        virtual void _18(void); // 18
        virtual void _19(void); // 19
        virtual void _1A(void); // 1A
        virtual void _1B(void); // 1B
        virtual Bool_t Find_Bound_Object(Handle_t handle, String_t class_name, Object_t** object_out); // 1C
        virtual void _1D(void); // 1D
        virtual void _1E(void); // 1E
        virtual void _1F(void); // 1F
        virtual void _20(void); // 20
        virtual void _21(void); // 21
        virtual void _22(void); // 22
        virtual void _23(void); // 23
        virtual void Send_Event(Handle_t handle, String_t* event_name, IFunctionArguments* arguments); // 24
    };

    class Class_Info_t;
    class Type_t {
    public:
        enum : Type_e {
            NONE = 0,
            OBJECT = 1,
            STRING = 2,
            INT = 3,
            FLOAT = 4,
            BOOL = 5,

            NONE_ARRAY = 10,
            OBJECT_ARRAY = 11,
            STRING_ARRAY = 12,
            INT_ARRAY = 13,
            FLOAT_ARRAY = 14,
            BOOL_ARRAY = 15
        };
    public:
        Type_t();
        Type_t(Type_e type);
        Type_t(Class_Info_t* class_info);

        UInt64 mangled;

        Type_e Unmangled();
        Class_Info_t* Class_Info();
        String_t To_String();

        Bool_t Is_None();
        Bool_t Is_Bool();
        Bool_t Is_Int();
        Bool_t Is_Float();
        Bool_t Is_String();
        Bool_t Is_Object();
        Bool_t Is_Array();
        Bool_t Is_None_Array();
        Bool_t Is_Object_Array();
        Bool_t Is_String_Array();
        Bool_t Is_Int_Array();
        Bool_t Is_Float_Array();
        Bool_t Is_Bool_Array();
    };
    STATIC_ASSERT(sizeof(Type_t) == 0x8);

    class Variable_t;
    class Array_t {
    public:
        static Array_t* Create(Type_t* item_type, UInt32 count);
    public:
        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        Type_t item_type; // 08
        UInt32 count; // 10
        UInt32 pad_14; // 14
        UInt64 lock; // 18
        //Variable_t variables[0]; // 20

        Type_t Array_Type();
        Variable_t* Variables();
        Variable_t* Point(size_t idx);

        // see VMArray, it's a wrapper of this object
        // so you can add similar templated funcs.
    };
    STATIC_ASSERT(sizeof(Array_t) == 0x20);

    class Object_t;
    class Variable_t {
    public:
        static Registry_t* Registry();
        static Policy_t* Policy();

        template <typename Type>
        static Variable_t* Fetch(Type* bsobject,
                                 String_t class_name,
                                 String_t variable_name);
    public:
        Variable_t();

        Type_t type;
        union Variable_u {
            Variable_u();

            void* ptr;
            Bool_t b;
            Int_t i;
            Float_t f;
            String_t str;
            Object_t* obj;
            Array_t* arr;
        } data;

        void Destroy();
        void Copy(Variable_t* other);

        Bool_t Bool();
        Int_t Int();
        Float_t Float();
        String_t String();
        Object_t* Object();
        Array_t* Array();
        Array_t* Object_Array();
        Form_t* Form();
        Actor_t* Actor();
        Alias_Base_t* Alias();
        Faction_t* Faction();
        Misc_t* Misc();
        Reference_t* Reference();

        void None();
        void Bool(Bool_t value);
        void Int(Int_t value);
        void Float(Float_t value);
        void String(String_t value);
        void Object(Object_t* value);
        void Array(Array_t* value);

        template <typename Type>
        void Pack(Type* value);
        template <typename Type>
        void Pack(Vector_t<Type>& values);
    };
    STATIC_ASSERT(sizeof(Variable_t) == 0x10);

    class Class_Info_t {
    public:
        static Class_Info_t* Fetch(String_t class_name);
        static Class_Info_t* Fetch(Type_ID_t type_id);

        struct Setting_Info_t {
            UInt64 unk_00; // 00
        };
        STATIC_ASSERT(sizeof(Setting_Info_t) == 0x8);

        struct Variable_Info_t {
            String_t name; // 00
            Type_t type; // 08
        };
        STATIC_ASSERT(sizeof(Variable_Info_t) == 0x10);

        struct Default_Info_t {
            UInt32 variable_idx; // 00
            UInt32 pad_04; // 04
            Variable_t variable; // 08
        };
        STATIC_ASSERT(sizeof(Default_Info_t) == 0x18);

        struct Property_Info_t {
            String_t name; // 00
            String_t parent_name; // 08
            String_t property_name; // 10
            Type_t type; // 18
            UInt32 flags_20; // 20
            UInt32 unk_24; // 24
            IFunction* getter; // 28
            IFunction* setter; // 30
            UInt32 auto_var_idx; // 38
            UInt32 flags_3C; // 3C
            String_t unk_40; // 40
        };
        STATIC_ASSERT(sizeof(Property_Info_t) == 0x48);

        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        String_t name; // 08
        Class_Info_t* parent; // 10
        String_t unk_18; // 18
        UInt32 flags_20; // 20
        UInt32 flags_24; // 24
        UInt32 flags_28; // 28
        UInt32 pad_2C; // 2C
        UInt8* data; // 30

        UInt64 Count_Setting_Infos();
        UInt64 Count_Variable_Infos();
        UInt64 Count_Default_Infos();
        UInt64 Count_Property_Infos();

        Setting_Info_t* Setting_Infos();
        Variable_Info_t* Variable_Infos();
        Default_Info_t* Default_Infos();
        Property_Info_t* Property_Infos();

        SInt64 Variable_Index(String_t variable_name);
        SInt64 Property_Index(String_t property_name);
        Property_Info_t* Property_Info(String_t property_name);

        void Hold();
        void Free();

        void Log();
        //void Log_Setting_Infos();
        void Log_Variable_Infos();
        void Log_Default_Infos();
        void Log_Property_Infos();
    };
    STATIC_ASSERT(sizeof(Class_Info_t) == 0x38);

    class Object_t {
    public:
        template <typename Type>
        static Object_t* Fetch(Type* bsobject, String_t class_name);

        UInt64 unk_00; // 00
        Class_Info_t* info; // 08
        String_t unk_10; // 10
        void* unk_18; // 18
        volatile Handle_t handle; // 20
        volatile SInt32 lock; // 28
        UInt32 pad_2C; // 2C
        //Variable_t variables[0]; // 30

        void Increment_Lock();
        UInt32 Decrement_Lock();

        Handle_t Handle();
        Variable_t* Property(String_t property_name);
        Variable_t* Variable(String_t variable_name);
        Variable_t* Variables();

        void Log_Variables();
    };
    STATIC_ASSERT(sizeof(Object_t) == 0x30);

    class Function_t {
    public:
    };

    class Scripts : public IForEachScriptObjectFunctor
    {
    public:
        Handle_t handle;
        std::vector<const char *> names;
        std::vector<Script_t *> scripts;

        Scripts(Form_t *form)
        {
            handle = Papyrus::Handle_t(form);
            handle.Registry()->VisitScripts(handle, this);
        }
        Scripts(Alias_Base_t* alias)
        {
            handle = Papyrus::Handle_t(alias);
            handle.Registry()->VisitScripts(handle, this);
        }

        virtual bool Visit(Script_t *script, void *)
        {
            //_MESSAGE("%s", script->classInfo->name.data);
            names.push_back(script->classInfo->name.data);
            scripts.push_back(script);
            return true;
        }

        Script_t *Script(const char *script_name)
        {
            for (u64 idx = 0, size = names.size(); idx < size; idx += 1) {
                if (_stricmp(script_name, names[idx]) == 0) {
                    return scripts[idx];
                }
            }

            return nullptr;
        }
    };

    template <typename Type>
    Vector_t<Type> Slice_Array(VMArray<Type> arr, SInt32 from = 0, SInt32 to_exclusive = -1)
    {
        Vector_t<Type> slice;
        u64 arr_size = arr.Length();

        if (from < 0) {
            from = 0;
        } else if (from > arr_size) {
            from = arr_size;
        }

        if (to_exclusive > arr_size || to_exclusive < 0) {
            to_exclusive = arr_size;
        }

        s64 slice_size = to_exclusive - from;
        if (slice_size > 0) {
            slice.reserve(slice_size);
            for (u64 idx = from, end = to_exclusive; idx < end; idx += 1) {
                Type elem;
                arr.Get(&elem, idx);
                slice.push_back(elem);
            }
        }

        return slice;
    }

    template <typename Type>
    Vector_t<Type> Slice_Vector(Vector_t<Type> vec, SInt32 from = 0, SInt32 to_exclusive = -1)
    {
        Vector_t<Type> slice;
        u64 vec_size = vec.size();

        if (from < 0) {
            from = 0;
        } else if (from > vec_size) {
            from = vec_size;
        }

        if (to_exclusive > vec_size || to_exclusive < 0) {
            to_exclusive = vec_size;
        }

        s64 slice_size = to_exclusive - from;
        if (slice_size > 0) {
            slice.reserve(slice_size);
            for (u64 idx = from, end = to_exclusive; idx < end; idx += 1) {
                slice.push_back(vec[idx]);
            }
        }

        return slice;
    }

}}

namespace doticu_npcp { namespace Papyrus { namespace Exports {

    bool Register(Registry_t *registry);

}}}
