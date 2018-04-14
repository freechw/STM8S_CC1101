#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__


#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_tim1.h"



void drv_timer1_init( void );
void drv_timer1_enable(void);
void drv_timer1_disable(void);
void TIM1_handler();
void drv_timer1_deinit_counter();
uint16_t drv_timer1_get_mcs(void);
uint16_t drv_timer1_get_ms(void);
//void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );
//uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );



#endif