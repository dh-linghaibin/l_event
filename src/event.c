/*
 * This file is part of the 
 *
 * Copyright (c) 2016-2017 linghaibin
 *
 */

#include "event.h"
#include <string.h>

static event_obj event[BEST_EVENT];

void event_init(void) {
    register int i;
    for(i = 0;i < BEST_EVENT;i++) {
        event[i].is_enable   = E_DISABLE;
        event[i].flag_addr   = null;
        event[i].call_back   = null;
        event[i].call_custom = null;
        event[i].call_dat    = null;
        event[i].name        = null;
    }
}

int event_create(const char *name,
                 uint8_t *flag_addr,
                 event_type_e type,
                 void(*call_back)(void *),
                 void * pd,
                 event_e (*call_custom)(void *)) {
    //assert(flag_addr != null && call_back != null);
    register int i;
    for(i = 0;i < BEST_EVENT;i++) {
        if(event[i].is_enable == E_DISABLE) {
            event[i].flag_addr   = flag_addr;
            event[i].type        = type;
            event[i].call_dat    = pd;
            event[i].call_back   = call_back;
            event[i].call_custom = call_custom;
            event[i].is_enable   = E_ENABLE;
            event[i].name        = (char *)name;
            return i;
        }
    }
    return E_ERROR;
}

int event_delet(const char *name) {
    for(register int i = 0;i < BEST_EVENT;i++) {
        if(event[i].is_enable == E_ENABLE) {
            if(strcmp(name,event[i].name) == 0) {
                event[i].is_enable   = E_DISABLE;
                event[i].flag_addr   = null;
                event[i].call_back   = null;
                event[i].call_custom = null;
                event[i].call_dat    = null;
                return i;
            }
        }
    }
    return E_ERROR;
}

void event_loop(void) {
    register int i;
    for(i = 0;i < BEST_EVENT;i++) {
        if(event[i].is_enable == E_ENABLE) {
            switch(event[i].type) {
                case ET_ONCE: {
                    if(*event[i].flag_addr == E_ENABLE) {
                        event[i].is_enable   = E_DISABLE;
                        if(event[i].call_back != null) {
                            event[i].call_back(event[i].call_dat);
                        }
                    }           
                } break;
                case ET_ALWAYS: {
                    if(*event[i].flag_addr == E_ENABLE) {
                        *event[i].flag_addr = E_DISABLE;
                        if(event[i].call_back != null) {
                            event[i].call_back(event[i].call_dat);
                        }
                    }
                } break;
                case ET_CUSTOM: {
                    if(event[i].call_custom != null) {
                        if(event[i].call_custom(null) == E_ENABLE) {
                            event[i].is_enable   = E_DISABLE;
                            if(event[i].call_back != null) {
                                event[i].call_back(event[i].call_dat);
                            }
                        }
                    }
                } break;
            }
        }
    }
}
