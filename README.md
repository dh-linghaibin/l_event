# l_event
小型系统 单片机的 软件事件框架 软件定时  基于事件驱动


###STM8 使用 示例

 定时器初始化 1ms 时基

```c
void stime_init(void) {
    CLK_CKDIVR=0x00;
    TIM2_PSCR=0x04;//1/4prescale
    TIM2_ARRH=0x3;
    TIM2_ARRL=0xE8;
    TIM2_CNTRH=0x00;
    TIM2_CNTRL=0x00;
    TIM2_CR1=MASK_TIM2_CR1_ARPE|MASK_TIM2_CR1_CEN;
    TIM2_IER=0x01;
    asm("rim");
}
```
    中断时间扫描 处理

```c
#pragma vector=TIM2_OVR_UIF_vector
__interrupt void Tim2_Overflow(void) {

    TIM2_SR1=0;//清楚中断标志位
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
```


