;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_codes extends Quest

; Public Constants
int property SUCCESS                        =     0 autoReadOnly
int property FAILURE                        =    -1 autoReadOnly
int property STARTED                        =   -10 autoReadOnly
int property STOPPED                        =   -11 autoReadOnly
int property CREATED                        =   -20 autoReadOnly
int property DESTROYED                      =   -21 autoReadOnly
int property READY                          =   -30 autoReadOnly
int property BUSY                           =   -31 autoReadOnly
int property OUT_OF_BOUNDS                  =   -99 autoReadOnly

int property HAS_SPACE                      =  -100 autoReadOnly
int property HAS_ACTOR                      =  -110 autoReadOnly
int property HAS_ALIAS                      =  -120 autoReadOnly
int property HAS_MEMBER                     =  -130 autoReadOnly
int property HAS_SETTLER                    =  -140 autoReadOnly
int property HAS_IMMOBILE                   =  -150 autoReadOnly
int property HAS_FOLLOWER                   =  -160 autoReadOnly
int property HAS_SNEAK                      =  -170 autoReadOnly
int property HAS_MANNEQUIN                  =  -180 autoReadOnly

int property HASNT_SPACE                    =  -200 autoReadOnly
int property HASNT_SPACE_MEMBER             =  -201 autoReadOnly
int property HASNT_SPACE_FOLLOWER           =  -202 autoReadOnly
int property HASNT_ID                       =  -203 autoReadOnly
int property HASNT_MARKER                   =  -204 autoReadOnly
int property HASNT_ACTOR                    =  -210 autoReadOnly
int property HASNT_ALIAS                    =  -220 autoReadOnly
int property HASNT_MEMBER                   =  -230 autoReadOnly
int property HASNT_SETTLER                  =  -231 autoReadOnly
int property HASNT_IMMOBILE                 =  -232 autoReadOnly
int property HASNT_MOBILE                   =  -233 autoReadOnly
int property HASNT_FOLLOWER                 =  -240 autoReadOnly
int property HASNT_SNEAK                    =  -241 autoReadOnly
int property HASNT_NON_SNEAK                =  -242 autoReadOnly
int property HASNT_ALIVE                    =  -243 autoReadOnly
int property HASNT_DEAD                     =  -244 autoReadOnly
int property HASNT_RETREATER                =  -245 autoReadOnly
int property HASNT_NON_RETREATER            =  -246 autoReadOnly
int property HASNT_MANNEQUIN                =  -247 autoReadOnly
int property HASNT_SADDLER                  =  -250 autoReadOnly
int property HASNT_NON_SADDLER              =  -251 autoReadOnly

int property IS_ALIVE                       =  -301 autoReadOnly
int property IS_DEAD                        =  -302 autoReadOnly
int property IS_MORTAL                      =  -303 autoReadOnly
int property IS_PROTECTED                   =  -304 autoReadOnly
int property IS_ESSENTIAL                   =  -305 autoReadOnly
int property IS_INVULNERABLE                =  -306 autoReadOnly
int property IS_ACTOR                       =  -307 autoReadOnly
int property IS_ALIAS                       =  -310 autoReadOnly
int property IS_MEMBER                      =  -320 autoReadOnly
int property IS_SETTLER                     =  -330 autoReadOnly
int property IS_IMMOBILE                    =  -340 autoReadOnly
int property IS_PARALYZED                   =  -341 autoReadOnly
int property IS_MANNEQUIN                   =  -342 autoReadOnly
int property IS_FOLLOWER                    =  -350 autoReadOnly
int property IS_SNEAK                       =  -360 autoReadOnly
int property IS_SADDLER                     =  -365 autoReadOnly
int property IS_THRALL                      =  -370 autoReadOnly
int property IS_DEFAULT                     =  -380 autoReadOnly
int property IS_WARRIOR                     =  -381 autoReadOnly
int property IS_MAGE                        =  -382 autoReadOnly
int property IS_ARCHER                      =  -383 autoReadOnly
int property IS_COWARD                      =  -384 autoReadOnly
int property IS_GREETER                     =  -390 autoReadOnly
int property IS_VAMPIRE                     =  -399 autoReadOnly
int property IS_DISPLAY                     = -3400 autoReadOnly
int property IS_CHILD                       = -3410 autoReadOnly
int property IS_INTERIOR                    = -3800 autoReadOnly
int property IS_EXTERIOR                    = -3810 autoReadOnly

int property ISNT_ACTOR                     =  -400 autoReadOnly
int property ISNT_ALIAS                     =  -410 autoReadOnly
int property ISNT_MEMBER                    =  -420 autoReadOnly
int property ISNT_SETTLER                   =  -430 autoReadOnly
int property ISNT_IMMOBILE                  =  -440 autoReadOnly
int property ISNT_MOBILE                    =  -441 autoReadOnly
int property ISNT_PARALYZED                 =  -442 autoReadOnly
int property ISNT_MANNEQUIN                 =  -443 autoReadOnly
int property ISNT_FOLLOWER                  =  -450 autoReadOnly
int property ISNT_SNEAK                     =  -460 autoReadOnly
int property ISNT_SADDLER                   =  -465 autoReadOnly
int property ISNT_THRALL                    =  -470 autoReadOnly
int property ISNT_CLONE                     =  -480 autoReadOnly
int property ISNT_GREETER                   =  -490 autoReadOnly
int property ISNT_VAMPIRE                   =  -499 autoReadOnly
int property ISNT_DISPLAY                   = -4400 autoReadOnly
int property ISNT_RATING                    = -4500 autoReadOnly

int property CAN_RESURRECT                  =  -500 autoReadOnly

int property CANT_RESURRECT                 =  -600 autoReadOnly
int property CANT_CLONE                     =  -605 autoReadOnly
int property CANT_RENAME                    =  -610 autoReadOnly
int property CANT_CATCH_UP                  =  -615 autoReadOnly

int property DO_SYNC                        =  -700 autoReadOnly
int property DO_ASYNC                       =  -701 autoReadOnly

int property ACTION_WEAPON_SWING            =     0 autoReadOnly
int property ACTION_SPELL_CAST              =     1 autoReadOnly
int property ACTION_SPELL_FIRE              =     2 autoReadOnly
int property ACTION_VOICE_CAST              =     3 autoReadOnly
int property ACTION_VOICE_FIRE              =     4 autoReadOnly
int property ACTION_BOW_DRAW                =     5 autoReadOnly
int property ACTION_BOW_RELEASE             =     6 autoReadOnly
int property ACTION_DRAW_BEGIN              =     7 autoReadOnly
int property ACTION_DRAW_END                =     8 autoReadOnly
int property ACTION_SHEATHE_BEGIN           =     9 autoReadOnly
int property ACTION_SHEATHE_END             =    10 autoReadOnly

int property COMBAT_NO                      =     0 autoReadOnly
int property COMBAT_YES                     =     1 autoReadOnly
int property COMBAT_SEARCHING               =     2 autoReadOnly

int property CRITICAL_NONE                  =     0 autoReadOnly
int property CRITICAL_GOO_BEGIN             =     1 autoReadOnly
int property CRITICAL_GOO_END               =     2 autoReadOnly
int property CRITICAL_DISINTEGRATE_BEGIN    =     3 autoReadOnly
int property CRITICAL_DISINTEGRATE_END      =     4 autoReadOnly

int property GENDER_MALE                    =     0 autoReadOnly
int property GENDER_FEMALE                  =     1 autoReadOnly
int property GENDER_NONE                    =    -1 autoReadOnly

int property MOTION_DYNAMIC                 =     1 autoReadOnly   
int property MOTION_SPHERE_INERTIA          =     2 autoReadOnly
int property MOTION_BOX_INERTIA             =     3 autoReadOnly
int property MOTION_KEY_FRAMED              =     4 autoReadOnly
int property MOTION_FIXED                   =     5 autoReadOnly
int property MOTION_THIN_BOX_INERTIA        =     6 autoReadOnly
int property MOTION_CHARACTER               =     7 autoReadOnly

int property OUTFIT_BASE                    =  -100 autoReadOnly
int property OUTFIT_REFERENCE               =  -200 autoReadOnly

int property OUTFIT2_CURRENT                =  -100 autoReadOnly
int property OUTFIT2_MEMBER                 = -1000 autoReadOnly
int property OUTFIT2_SETTLER                = -2000 autoReadOnly
int property OUTFIT2_THRALL                 = -3000 autoReadOnly
int property OUTFIT2_FOLLOWER               = -4000 autoReadOnly
int property OUTFIT2_IMMOBILE               = -5000 autoReadOnly
int property OUTFIT2_VANILLA                = -7000 autoReadOnly
int property OUTFIT2_DEFAULT                = -8000 autoReadOnly

; STYLE AND VITALITY codes are to replace certain IS_ codes
int property STYLE_DEFAULT                  = -1000 autoReadOnly
int property STYLE_WARRIOR                  = -2000 autoReadOnly
int property STYLE_MAGE                     = -3000 autoReadOnly
int property STYLE_ARCHER                   = -4000 autoReadOnly
int property STYLE_COWARD                   = -5000 autoReadOnly

int property VITALITY_MORTAL                = -1000 autoReadOnly
int property VITALITY_PROTECTED             = -2000 autoReadOnly
int property VITALITY_ESSENTIAL             = -3000 autoReadOnly
int property VITALITY_INVULNERABLE          = -4000 autoReadOnly

int property VIEW_MEMBERS                   = -1000 autoReadOnly
int property VIEW_FOLLOWERS                 = -1100 autoReadOnly
int property VIEW_MEMBERS_MEMBER            = -1200 autoReadOnly
int property VIEW_FOLLOWERS_MEMBER          = -1300 autoReadOnly
int property VIEW_FILTER                    = -2000 autoReadOnly
int property VIEW_FILTER_MEMBERS            = -2010 autoReadOnly
int property VIEW_FILTER_MEMBERS_MEMBER     = -2020 autoReadOnly
int property VIEW_MANNEQUINS                = -3000 autoReadOnly
int property VIEW_MANNEQUINS_CELL           = -3001 autoReadOnly
int property VIEW_MANNEQUINS_MEMBER         = -3002 autoReadOnly
