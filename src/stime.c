/*
 * This file is part of the 
 *
 * Copyright (c) 2016-2017 linghaibin
 *
 */

#include "stime.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

static struct _stime_obj list_time[BEST_STIME];
static uint16_t timeslice = 0;

void timer_handler(int signum) {
    timeslice++;
    register uint8_t i = 0;
    for(i = 0;i < BEST_STIME;i++) {
        if(list_time[i].is_enable == ST_ENABLE) {
            if(list_time[i].end_t > 0) {
               list_time[i].end_t--; 
            }
        }
    }
}

void stime_init(void) {
    struct sigaction sa;
    struct itimerval timer;

    register int i = 0;
    for(i = 0;i < BEST_STIME;i++) {
        list_time[i].is_enable = ST_DISABLE;
    }

    /* Install timer_handler as the signal handler for SIGVTALRM. */
    memset(&sa, 0, sizeof (sa));
    sa.sa_handler = &timer_handler;
    sigaction (SIGVTALRM, &sa, NULL);

    /* Configure the timer to expire after 100 msec... */
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 100000;
    /* ... and every 100 msec after that. */
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 100000;
    /* Start a virtual timer. It counts down whenever this process is
    executing. */

    setitimer (ITIMER_VIRTUAL, &timer, NULL);
}

int stime_create(const char *name,
                 uint16_t sec,
                 stime_type_e type,
                 void (*time_up)(void)) {
    register uint8_t i = 0;
    for(i = 0;i < BEST_STIME;i++) {
        if(list_time[i].is_enable == ST_DISABLE) {
            list_time[i].time_up   = time_up;
            list_time[i].end_t     = sec;
            list_time[i].time      = sec;
            list_time[i].type      = type;
            list_time[i].is_enable = ST_ENABLE;
            list_time[i].name      = (char *)name;
            return i;
        }
    }
    return -1;
}

int stime_delet(const char *name) {
    for(register uint8_t i = 0;i < BEST_STIME;i++) {
        if(list_time[i].is_enable == ST_ENABLE) {
            if(strcmp(name,list_time[i].name) == 0) {
                list_time[i].is_enable = ST_DISABLE;
                return i;
            }
        }
    }
    return -1;
}

void stime_loop(void) {
    register uint8_t i = 0;
    for(i = 0;i < BEST_STIME;i++) {
        if(list_time[i].is_enable == ST_ENABLE) {
            if(list_time[i].end_t == 0) {
                if(list_time[i].time_up != null) {
                    if(list_time[i].type == ST_ONCE) {
                        list_time[i].is_enable = ST_DISABLE;
                    } else {
                        list_time[i].end_t = list_time[i].time;
                    }
                    list_time[i].time_up();
                }
            }
        }
    }
}


// #pragma vector=TIM2_OVR_UIF_vector
// __interrupt void Tim2_Overflow(void) {
//     asm("sim");
    
//     TIM2_SR1=0;//清楚中断标志位
//     timeslice++;
//     register uint8_t i = 0;
//     for(i = 0;i < BEST_STIME;i++) {
//         if(list_time[i].is_enable == ST_ENABLE) {
//             if(list_time[i].end_t > 0) {
//                list_time[i].end_t--; 
//             }
//         }
//     }
    
//     asm("sim");
// }

