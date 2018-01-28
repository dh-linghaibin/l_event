#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stime.h"
#include "event.h"

void led_task(void) {
    printf("led on\n");
}


int main () {
    printf("event start \n");
    event_init();
    stime_init();

    stime_create(5,ST_ONCE,led_task);
    /* Do busy work. */
    while(1) {
        event_loop();
        stime_loop();
    }
    return 0;
}
