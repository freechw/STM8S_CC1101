/**
******************************************************************************
* @author  ��ҫ�Ƽ� ASHINING
* @version V3.0
* @date    2016-10-08
* @brief   CC1101����H�ļ�
******************************************************************************
* @attention
*
* ����	:	http://www.ashining.com
* �Ա�	:	https://shop105912646.taobao.com
* ����Ͱ�:	https://cdzeyao.1688.com
******************************************************************************
*/



#ifndef __DRV_CC1101_H__
#define __DRV_CC1101_H__

#include "stm8s_conf.h"
#include "drv_spi.h"
#include "drv_CC1101_Reg.h"
#include "stm8s_tim1.h"
#include "stm8s_exti.h"
#include "drv_led.h"
#include "drv_timer1.h"
  
extern uint8_t read;
extern uint8_t write;
#define PA_TABLE 		                {0xc2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,}

/** CC1101Ӳ���ӿڶ��� */
#define CC1101_GDO0_GPIO_PORT			GPIOB
#define CC1101_GDO0_GPIO_PIN			GPIO_PIN_4

#define CC1101_GDO2_GPIO_PORT			GPIOC
#define CC1101_GDO2_GPIO_PIN			GPIO_PIN_3

#define CC1101_CSN_GPIO_PORT			SPI_NSS_GPIO_PORT			//
#define CC1101_CSN_GPIO_PIN			SPI_NSS_GPIO_PIN



/** ���߲����������� */
#define CC1101_SET_CSN_HIGH( )			spi_set_nss_high( )
#define CC1101_SET_CSN_LOW( )			spi_set_nss_low( )
#define CC1101_REV_CSN()                        spi_nss_rev() 

#define CC1101_GET_GDO0_STATUS( )		(( CC1101_GDO0_GPIO_PORT->IDR & (uint32_t)CC1101_GDO0_GPIO_PIN) != CC1101_GDO0_GPIO_PIN ) ? 0 : 1	//GDO0״̬
#define CC1101_GET_GDO2_STATUS( )		(( CC1101_GDO2_GPIO_PORT->IDR & (uint32_t)CC1101_GDO2_GPIO_PIN) != CC1101_GDO2_GPIO_PIN ) ? 0 : 1	//GDO2״̬

/** ö�������� */
typedef enum 
{ 
  TX_MODE, 
  RX_MODE 
}CC1101_ModeType;

typedef enum 
{ 
  BROAD_ALL, 
  BROAD_NO, 
  BROAD_0, 
  BROAD_0AND255 
}CC1101_AddrModeType;

typedef enum 
{ 
  BROADCAST, 
  ADDRESS_CHECK
} CC1101_TxDataModeType;




void CC1101_Write_Cmd( uint8_t Command );                                                       //д������
void CC1101_Write_Reg( uint8_t Addr, uint8_t WriteValue );                                      //д��Ĵ���
void CC1101_Write_Multi_Reg( uint8_t Addr, uint8_t *pWriteBuff, uint8_t WriteSize );            //����д��
uint8_t CC1101_Read_Reg( uint8_t Addr );                                                        //��ȡ�Ĵ�����0x30֮���״̬�Ĵ���ֻ�ܵ�����ȡ
void CC1101_Read_Multi_Reg( uint8_t Addr, uint8_t *pReadBuff, uint8_t ReadSize );               //������ȡ
uint8_t CC1101_Read_Status( uint8_t Addr );                                                     //��ȡ״̬
void CC1101_Set_Mode( CC1101_ModeType Mode );                                                   //����ģʽ
void CC1101_Set_Idle_Mode( void );                                                             //�������ģʽ

void CC1101_Set_Address( uint8_t address, CC1101_AddrModeType AddressMode);                     //��ַ���ˣ������ˡ���Ե㡢0x00�㲥��0x00��0xff�㲥
void CC1101_Set_Sync( uint16_t Sync );                                                          //����ͬ����
void CC1101_Clear_TxBuffer( void );                                                             //���TX FIFO
void CC1101_Clear_RxBuffer( void );                                                             //���RX FIFO
uint8_t CC1101_Get_TxCounter( void );                                                           //��ȡTX FIFO�ֽ���Ŀ
void CC1101_Tx_Packet( uint8_t *pTxBuff, uint8_t TxSize, CC1101_TxDataModeType DataMode );      //�������ݰ�
uint8_t CC1101_Get_RxCounter( void );                                                           //��ȡRX FIFO�ֽ���Ŀ
uint8_t CC1101_Rx_Packet( uint8_t *RxBuff );                                                     //�������ݰ�
void CC1101_Reset( void );                                                                      //����
void CC1101_Init( void );                                                                       //��ʼ��
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CC1101_Set_Sleep(void);
void CC1101_Wakeup(void);
void CC1101_Rx_INT_Handler(void);
void CC1101_Rx_INT_Init(void);
void SetACK(void);
void DesetACK(void);
uint8_t GetACK(void);

#endif
