/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Follower_t;

    class Horse_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable();
        Variable_t* Follower_Variable();

        Actor_t* Actor();
        Follower_t* Follower();
        Cell_t* Cell();
        String_t Base_Name();
        String_t Reference_Name();
        String_t Name();

        Bool_t Is_Alive();
        Bool_t Is_Dead();

        void Fill(Actor_t* actor, Follower_t* follower);
        void Unfill(Virtual_Callback_i** callback);
        void Create(Actor_t* actor, Follower_t* follower);
        void Destroy();

        Int_t Groom();
        void Enforce_Groom(Actor_t* actor);
        Int_t Ungroom();
        void Enforce_Non_Groom(Actor_t* actor);

        void Enforce();

        void Rename(String_t new_name);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
