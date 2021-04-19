#ifndef _tim_H
#define _tim_H
#include "IERG3810_System_Init.h"
#include "IERG3810_Delay.h"
void tim3_pwm_init(u32 arr,u32 pre);
void TIM3_Init(u32 arr,u32 psc);
void TIM3_IRQHandler(void);
void tim5_input1_init(u32 arr,u32 pre);
extern u8 TIM5CH1_CAPTURE_STA;
extern u16 TIM5CH1_CAPTURE_VAL;

#endif
