Scriptname doticu_npcp_queue extends ObjectReference

; Private Constants
doticu_npcp_data    p_DATA              =  none
int                 p_BUFFER_MAX        =    -1
float               p_INTERVAL_DEFAULT  =  -1.0
string              p_EVENT_DEFAULT     =    ""
string[]            p_MESSAGES          =  none
float[]             p_INTERVALS         =  none
string[]            p_EVENTS            =  none

; Private Variables
bool                p_is_created        = false
int                 p_buffer_write      =     0
int                 p_buffer_read       =     0
int                 p_buffer_used       =     0
string              p_str_message       =    ""
string              p_str_event         =    ""
string              p_str_rush          =    ""
string              p_str_rush_event    =    ""
bool                p_will_update       = false
bool                p_will_rush         = false

; Friend Methods
function f_Create(doticu_npcp_data DATA, string str_namespace, int message_max = 32, float interval_default = 0.15)
    p_DATA = DATA
    p_BUFFER_MAX = message_max
    p_INTERVAL_DEFAULT = interval_default
    p_EVENT_DEFAULT = p_Get_Event(str_namespace)
    p_MESSAGES = Utility.CreateStringArray(p_BUFFER_MAX, "")
    p_INTERVALS = Utility.CreateFloatArray(p_BUFFER_MAX, 0.0)
    p_EVENTS = Utility.CreateStringArray(p_BUFFER_MAX, "")
    
    p_is_created = true
endFunction

function f_Destroy()
    self.Flush()
    self.Disable()
    self.Delete()

    p_is_created = false
endFunction

function f_Register()
endFunction

; Private Methods
string function p_Get_Event(string str_namespace = "__def__")
    if str_namespace == "__def__" && p_EVENT_DEFAULT
        return p_EVENT_DEFAULT
    elseIf str_namespace
        return "doticu_npcp_queue" + "_" + str_namespace
    else
        return "doticu_npcp_queue"
    endIf
endFunction

function p_Write(string str_message, float float_wait_before = -1.0, string str_namespace = "__def__")
    if Is_Full()
        return
    endIf

    p_MESSAGES[p_buffer_write] = str_message
    p_INTERVALS[p_buffer_write] = float_wait_before
    p_EVENTS[p_buffer_write] = p_Get_Event(str_namespace)

    p_buffer_write += 1
    if p_buffer_write == p_BUFFER_MAX
        p_buffer_write = 0
    endIf

    p_buffer_used += 1
endFunction

int function p_Read()
    if Is_Empty()
        return -1
    endIf

    int idx_buffer = p_buffer_read

    p_buffer_read += 1
    if p_buffer_read == p_BUFFER_MAX
        p_buffer_read = 0
    endIf

    p_buffer_used -= 1

    return idx_buffer
endFunction

bool function p_Has_Message(string str_message)
    if Is_Empty()
        return false
    endIf

    ; should we check p_str_rush?

    int idx = p_buffer_read
    while idx < p_buffer_write
        if p_MESSAGES[idx] == str_message
            return true
        endIf
        idx += 1
    endWhile

    return false
endFunction

bool function p_Has_Rush()
    return p_str_rush != ""
endFunction

bool function p_Send_Queue()
    int handle = ModEvent.Create(p_str_event)

    if !handle
        return false
    endIf

    ModEvent.PushString(handle, p_str_message)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Public Methods
bool function Exists()
    return p_is_created
endFunction

bool function Is_Empty()
    return p_buffer_used == 0
endFunction

bool function Is_Full()
    return p_buffer_used == p_buffer_max
endFunction

; for the registers, if we keep track of the objects, we can unregister for them on Destroy()
function Register_Form(Form ref_form, string str_handler, string str_namespace = "__def__")
    if Exists() && ref_form && str_handler
        ref_form.RegisterForModEvent(p_Get_Event(str_namespace), str_handler)
    endIf
endFunction

function Register_Alias(ReferenceAlias ref_alias, string str_handler, string str_namespace = "__def__")
    if Exists() && ref_alias && str_handler
        ref_alias.RegisterForModEvent(p_Get_Event(str_namespace), str_handler)
    endIf
endFunction

function Register_Effect(ActiveMagicEffect ref_effect, string str_handler, string str_namespace = "__def__")
    if Exists() && ref_effect && str_handler
        ref_effect.RegisterForModEvent(p_Get_Event(str_namespace), str_handler)
    endIf
endFunction

function Enqueue(string str_message, float float_wait_before = -1.0, string str_namespace = "__def__", bool allow_repeat = false)
    if Is_Full()
        return
    endIf

    if str_message == ""
        return
    endIf

    if !allow_repeat && p_Has_Message(str_message)
        return
    endIf

    if float_wait_before <= 0.0
        float_wait_before = p_INTERVAL_DEFAULT
    endIf

    p_Write(str_message, float_wait_before, str_namespace)

    if !p_will_update
        Dequeue()
    endIf
endFunction

function Dequeue()
    if p_Has_Rush()
        p_will_update = true
        p_will_rush = true
        p_str_message = p_str_rush
        p_str_event = p_str_rush_event
        p_str_rush = ""
        p_str_rush_event = ""
        RegisterForSingleUpdate(0.0)
    elseIf Is_Empty()
        p_will_update = false
        p_will_rush = false
        p_str_message = ""
        p_str_event = ""
        p_str_rush = ""
        p_str_rush_event = ""
    else
        int idx_buffer = p_Read()
        p_will_update = true
        p_will_rush = false
        p_str_message = p_MESSAGES[idx_buffer]
        p_str_event = p_EVENTS[idx_buffer]
        RegisterForSingleUpdate(p_INTERVALS[idx_buffer])
    endIf
endFunction

function Rush(string str_rush, string str_namespace = "__def__")
    if str_rush == ""
        return
    endIf

    while p_Has_Rush()
        ; if we completely block here, we could create a deadlock
        Utility.Wait(0.01)
    endWhile

    p_will_rush = true
    p_str_rush = str_rush
    p_str_rush_event = p_Get_Event(str_namespace)

    if !p_will_update
        Dequeue()
    endIf

    while p_will_rush
        ; we need to wait for the Rush message to finish
        Utility.Wait(0.01)
    endWhile
endFunction

function Flush()
    p_buffer_write = 0
    p_buffer_read = 0
    p_buffer_used = 0

    UnregisterForUpdate()

    if p_will_update
        ; let an existing last message finish
        Utility.Wait(0.01)
    endIf

    p_will_rush = false
    p_will_update = false
    p_str_rush_event = ""
    p_str_rush == ""
    p_str_event = ""
    p_str_message = ""
endFunction

; Update Methods
function u_0_1_4(doticu_npcp_data DATA)
    p_DATA = DATA
endFunction

; Events
event OnUpdate()
    while !p_Send_Queue()
        Utility.Wait(p_INTERVAL_DEFAULT)
    endWhile
endEvent
