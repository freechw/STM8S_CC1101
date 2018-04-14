#ifndef __DRV_EXINT_H__
#define __DRV_EXINT_H__


#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_exti.h"
#include "drv_delay.h"



void drv_init_exint_GOD0(void);
void drv_init_exint_GOD2(void);

void drv_GOD0_handler(void);
void drv_GOD2_handler(void);



#endif