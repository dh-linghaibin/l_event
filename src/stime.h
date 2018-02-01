/*
 * This file is part of the 
 *
 * Copyright (c) 2016-2017 linghaibin
 *
 */

#ifndef _STIME_H_
#define _STIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "fsm.h"

#define BEST_STIME 30
    
typedef enum _stime_e{
    ST_ENABLE = 1,
    ST_DISABLE = 0,
}stime_e;

typedef enum _stime_type_e{
    ST_ONCE,
    ST_ALWAYS,
}stime_type_e;

typedef struct _stime_obj {
    char *name;
    stime_e is_enable : 4;
    stime_type_e type : 4;
    uint16_t end_t;
    uint16_t time;
    void (*time_up)(void);
}stime_obj;

void stime_init(void);
int stime_create(const char *name,
                 uint16_t sec,
                 stime_type_e type, 
                 void (*time_up)(void));
int stime_delet(const char *name);
void stime_loop(void);

#ifdef __cplusplus
}
#endif

#endif