#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stime.h"
#include "event.h"

uint8_t flag_addr = E_DISABLE;

void led_task(void) {
    printf("led on\n");
    flag_addr = E_ENABLE;
}

void led_task2(void) {
    if(event_delet("lhb") == E_ERROR) {
        printf("event delet faild\n");
    } else {
        printf("event delet ok\n");
    }
}

void ev_call(void *p) {
    printf("lev_call\n");
}

int main () {
    printf("event start \n");
    event_init();
    stime_init();

    event_create("lhb",&flag_addr,ET_ONCE,ev_call,null,null);
    stime_create("time1",10,ST_ONCE,led_task);
    stime_create("time2",5,ST_ONCE,led_task2);
    if(stime_delet("hh")  == E_ERROR) {
        printf("time delet faild\n");
    } else {
        printf("time delet ok\n");
    }
    /* Do busy work. */
    while(1) {
        event_loop();
        stime_loop();
    }
    return 0;
}
