/**
  ******************************************************************************
  * @author  ��ҫ�Ƽ� ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   ������H�ļ�
  ******************************************************************************
  * @attention
  *
  * ����	:	http://www.ashining.com
  * �Ա�	:	https://shop105912646.taobao.com
  * ����Ͱ�:	https://cdzeyao.1688.com
  ******************************************************************************
  */



#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm8s_conf.h"
#include "drv_CC1101.h"
#include "drv_uart.h"
#include "drv_button.h"
#include "drv_delay.h"
#include "drv_led.h"
#include "drv_exint.h"
    



//#define 	__CC1101_TX_TEST__							//**@@ ������Է��͹�������Ҫ����ú꣬������Խ�������Ҫ���θú� **@@//
//#define 	__USE_SOFT_SPI_INTERFACE__					//**@@ ���ʹ�����SPI����Ҫ����ú꣬��֮���ʹ��Ӳ��SPI����Ҫ���θú� **@@//


    extern uint16_t RXtimer_begin ;
    extern uint16_t RXtimer_end ;

    extern uint16_t TXtimer_begin;
    extern uint16_t TXtimer_end;



/** ����ģʽ���� */
enum
{
	TX_MODE_1 = 0,		//����ģʽ1�����͹̶����ַ���
	TX_MODE_2			//����ģʽ2�����ʹ��ڽ��յ�������
};


#endif
