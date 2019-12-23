Scriptname doticu_npcp_vars extends Quest

; Private Constants
doticu_npcp_consts  p_CONSTS                =  none

; Private Variables
int                 p_version_large         =     0
int                 p_version_small         =     0
int                 p_version_bug           =     0
bool                p_force_clone_unique    = false
bool                p_force_clone_generic   = false
bool                p_force_unclone_unique  = false
bool                p_force_unclone_generic = false
bool                p_auto_resurrect        = false
int                 p_auto_style            =    -1
int                 p_auto_vitality         =    -1
bool                p_is_mcm_open           = false

; Public Variables
int property key_open_mcm                   =  -1 auto hidden;
int property key_resurrect                  = 200 auto hidden; Up Arrow
int property key_member                     =  -1 auto hidden;
int property key_unmember                   =  -1 auto hidden;
int property key_clone                      =  -1 auto hidden;
int property key_unclone                    =  -1 auto hidden;
int property key_access                     =  -1 auto hidden;
int property key_outfit                     =  24 auto hidden; O
int property key_settle                     =  -1 auto hidden;
int property key_unsettle                   =  -1 auto hidden;
int property key_immobilize                 =  -1 auto hidden;
int property key_mobilize                   =  -1 auto hidden;
int property key_enthrall                   =  -1 auto hidden;
int property key_unthrall                   =  -1 auto hidden;
int property key_style_default              =  -1 auto hidden;
int property key_style_warrior              =  -1 auto hidden;
int property key_style_mage                 =  -1 auto hidden;
int property key_style_archer               =  -1 auto hidden;
int property key_follow                     =  -1 auto hidden;
int property key_unfollow                   =  -1 auto hidden;
int property key_sneak                      =  -1 auto hidden;
int property key_unsneak                    =  -1 auto hidden;
int property key_summon_followers           =  -1 auto hidden;
int property key_summon_followers_mobile    =  -1 auto hidden;
int property key_summon_followers_immobile  =  -1 auto hidden;
int property key_toggle_member              =  78 auto hidden; NUM+
int property key_toggle_clone               =  -1 auto hidden;
int property key_toggle_settler             =  82 auto hidden; NUM0
int property key_toggle_immobile            =  83 auto hidden; NUM.
int property key_toggle_enthrall            =  73 auto hidden; NUM9
int property key_toggle_follower            =  55 auto hidden; NUM*
int property key_toggle_sneak               =  74 auto hidden; NUM-
int property key_cycle_style                =  43 auto hidden; Back Slash

int property version_large hidden
    int function Get()
        return p_version_large
    endFunction
    function Set(int val)
        if p_version_large < val
            p_version_large = val
        endIf
    endFunction
endProperty

int property version_small hidden
    int function Get()
        return p_version_small
    endFunction
    function Set(int val)
        if p_version_small < val
            p_version_small = val
        endIf
    endFunction
endProperty

int property version_bug hidden
    int function Get()
        return p_version_bug
    endFunction
    function Set(int val)
        if p_version_bug < val
            p_version_bug = val
        endIf
    endFunction
endProperty

bool property force_clone_unique hidden
    bool function Get()
        return p_force_clone_unique
    endFunction
    function Set(bool val)
        p_force_clone_unique = val
        if p_force_clone_unique
            p_CONSTS.GLOBAL_FORCE_CLONE_UNIQUE.SetValue(1)
        else
            p_CONSTS.GLOBAL_FORCE_CLONE_UNIQUE.SetValue(0)
        endIf
    endFunction
endProperty

bool property force_clone_generic hidden
    bool function Get()
        return p_force_clone_generic
    endFunction
    function Set(bool val)
        p_force_clone_generic = val
        if p_force_clone_generic
            p_CONSTS.GLOBAL_FORCE_CLONE_GENERIC.SetValue(1)
        else
            p_CONSTS.GLOBAL_FORCE_CLONE_GENERIC.SetValue(0)
        endIf
    endFunction
endProperty

bool property force_unclone_unique hidden
    bool function Get()
        return p_force_unclone_unique
    endFunction
    function Set(bool val)
        p_force_unclone_unique = val
        if p_force_unclone_unique
            p_CONSTS.GLOBAL_FORCE_UNCLONE_UNIQUE.SetValue(1)
        else
            p_CONSTS.GLOBAL_FORCE_UNCLONE_UNIQUE.SetValue(0)
        endIf
    endFunction
endProperty

bool property force_unclone_generic hidden
    bool function Get()
        return p_force_unclone_generic
    endFunction
    function Set(bool val)
        p_force_unclone_generic = val
        if p_force_unclone_generic
            p_CONSTS.GLOBAL_FORCE_UNCLONE_GENERIC.SetValue(1)
        else
            p_CONSTS.GLOBAL_FORCE_UNCLONE_GENERIC.SetValue(0)
        endIf
    endFunction
endProperty

bool property auto_resurrect hidden
    bool function Get()
        return p_auto_resurrect
    endFunction
    function Set(bool val)
        p_auto_resurrect = val
    endFunction
endProperty

int property auto_style hidden
    int function Get()
        return p_auto_style
    endFunction
    function Set(int val)
        p_auto_style = val
    endFunction
endProperty

int property auto_vitality hidden
    int function Get()
        return p_auto_vitality
    endFunction
    function Set(int val)
        p_auto_vitality = val
    endFunction
endProperty

bool property is_mcm_open hidden
    bool function Get()
        return p_is_mcm_open
    endFunction
    function Set(bool val)
        p_is_mcm_open = val
    endFunction
endProperty

; Friend Methods
function f_Initialize(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS

    version_large = p_CONSTS.VERSION_LARGE
    version_small = p_CONSTS.VERSION_SMALL
    version_bug = p_CONSTS.VERSION_BUG

    force_clone_unique = false
    force_clone_generic = true
    force_unclone_unique = false
    force_unclone_generic = true
    auto_resurrect = true
    auto_style = DATA.CODES.IS_DEFAULT; IS_DEFAULT, IS_WARRIOR, IS_MAGE, IS_ARCHER
    auto_vitality = DATA.CODES.IS_PROTECTED; IS_MORTAL, IS_PROTECTED, IS_ESSENTIAL, IS_INVULNERABLE
endFunction
