/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"
#include "party.h"

#include "mcm/mcm_main.h"

namespace doticu_npcp { namespace MCM {

    using namespace Papyrus;

    class Members_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Members_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable();
        Variable_t* Members_Variable();
        Variable_t* Members_Slice_Variable();
        Variable_t* Current_Member_Variable();
        Variable_t* Members_Member_Variable();
        Variable_t* Filter_Members_Member_Variable();
        Variable_t* Do_Previous_Member_Variable();
        Variable_t* Do_Next_Member_Variable();
        Variable_t* Page_Index_Variable();
        Variable_t* Page_Count_Variable();
        Variable_t* Options_Offset_Variable();
        Variable_t* Title_Option_Variable();
        Variable_t* Back_Option_Variable();
        Variable_t* Previous_Option_Variable();
        Variable_t* Next_Option_Variable();

        Int_t Current_View();
        Array_t* Members();
        Array_t* Members_Slice();
        Party::Member_t* Current_Member();
        Bool_t Do_Previous_Member();
        Bool_t Do_Next_Member();
        Int_t Page_Index();
        Int_t Page_Count();
        Int_t Members_Per_Page();

        Bool_t Is_Valid_Member(Party::Member_t* member);
        void Review_Members();
        void Review_Filter_Members();
        String_t Format_Title(Int_t member_count, Int_t page_idx, Int_t page_count);
        void Build_Page();

        Party::Member_t* Previous_Member();
        Party::Member_t* Next_Member();
    public:
        static void Register_Me(Registry_t* registry);
    };

}}
