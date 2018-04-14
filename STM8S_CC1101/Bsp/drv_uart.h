/**
  ******************************************************************************
  * @author  ��ҫ�Ƽ� ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   UART����H�ļ�
  ******************************************************************************
  * @attention
  *
  * ����	:	http://www.ashining.com
  * �Ա�	:	https://shop105912646.taobao.com
  * ����Ͱ�:	https://cdzeyao.1688.com
  ******************************************************************************
  */


#ifndef __DRV_UART_H__
#define __DRV_UART_H__


#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_uart1.h"


//UARTӲ���ӿ�IO����
#define UART_TX_GPIO_PORT			GPIOD
#define UART_TX_GPIO_PIN			GPIO_PIN_5

#define UART_RX_GPIO_PORT			GPIOD
#define UART_RX_GPIO_PIN			GPIO_PIN_6


void drv_uart_init( uint32_t UartBaudRate );
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );
uint8_t drv_uart_rx_bytes( uint8_t* RxBuffer );



#endif



