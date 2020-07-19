/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "game.h"
#include "party.h"
#include "party.inl"

namespace doticu_npcp { namespace Party {

    String_t Horses_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_horses");
        return class_name;
    }

    Class_Info_t* Horses_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Horses_t* Horses_t::Self()
    {
        static Horses_t* horses = static_cast<Horses_t*>(Game::NPCP_Form(Consts::QUEST_FOLLOWERS));
        return horses;
    }

    Object_t* Horses_t::Object()
    {
        static Object_t* object = Object_t::Fetch(Self(), Class_Name());
        return object;
    }

    Variable_t* Horses_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Range_t<UInt64> Horses_t::Indices()
    {
        return { BEGIN, END };
    }

    Range_t<Horse_t**> Horses_t::Aliases()
    {
        return Aliases_t::Aliases<Horse_t>(BEGIN, END);
    }

    Horse_t* Horses_t::From_ID(Int_t unique_id)
    {
        if (unique_id >= BEGIN && unique_id < END) {
            return Aliases_t::From_ID<Horse_t>(unique_id);
        } else {
            return nullptr;
        }
    }

    Horse_t* Horses_t::From_Actor(Actor_t* actor)
    {
        if (actor) {
            Horse_t* horse = Aliases_t::From_Actor<Horse_t>(actor);
            if (horse) {
                if (horse->id >= BEGIN && horse->id < END) {
                    return horse;
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

}}

#define FORWARD_POINTER(METHOD_) { return self ? self->METHOD_ : nullptr; }
#define FORWARD_BOOL(METHOD_) { return self ? self->METHOD_ : false; }
#define FORWARD_INT(METHOD_) { return self ? self->METHOD_ : 0; }
#define FORWARD_STRING(METHOD_) { return self ? self->METHOD_ : ""; }
#define FORWARD_VECTOR(METHOD_, TYPE_) { return self ? self->METHOD_ : Vector_t<TYPE_>(); }
#define FORWARD_VOID(METHOD_) { self ? self->METHOD_, 1 : 0; }

namespace doticu_npcp { namespace Party { namespace Horses { namespace Exports {

    Bool_t Register(Registry_t* registry)
    {
        return true;
    }

}}}}

#undef FORWARD_POINTER
#undef FORWARD_BOOL
#undef FORWARD_INT
#undef FORWARD_STRING
#undef FORWARD_VECTOR
#undef FORWARD_VOID
