/*
 * This file is part of the 
 *
 * Copyright (c) 2016-2017 linghaibin
 *
 */

#ifndef _EVENT_H_
#define _EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <assert.h>  
#include "fsm.h"

#define BEST_EVENT 30

typedef enum _event_e{
    E_ENABLE    = 1,
    E_DISABLE   = 0,
    E_ERROR     = -1,
}event_e;

typedef enum _event_type_e {
    ET_ONCE     = 1,
    ET_ALWAYS   = 0,
    ET_CUSTOM   = 2,
}event_type_e;
    
typedef struct _event_obj {
    char *name;
    event_e is_enable : 4;
    event_type_e type : 4;
    uint8_t *flag_addr;
    void * call_dat;
    void(*call_back)(void *);
    event_e (*call_custom)(void *);
}event_obj;

void event_init(void);
int event_create(const char *name,
                 uint8_t *flag_addr,
                 event_type_e type,
                 void(*call_back)(void *),
                 void * pd,
                 event_e(*call_custom)(void *) );
int event_delet(const char *name);
void event_loop(void);

#ifdef __cplusplus
}
#endif

#endif
