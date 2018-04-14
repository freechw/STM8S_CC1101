/**
******************************************************************************
* @author  泽耀科技 ASHINING
* @version V3.0
* @date    2016-10-08
* @brief   CC1101配置H文件
******************************************************************************
* @attention
*
* 官网	:	http://www.ashining.com
* 淘宝	:	https://shop105912646.taobao.com
* 阿里巴巴:	https://cdzeyao.1688.com
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

/** CC1101硬件接口定义 */
#define CC1101_GDO0_GPIO_PORT			GPIOB
#define CC1101_GDO0_GPIO_PIN			GPIO_PIN_4

#define CC1101_GDO2_GPIO_PORT			GPIOC
#define CC1101_GDO2_GPIO_PIN			GPIO_PIN_3

#define CC1101_CSN_GPIO_PORT			SPI_NSS_GPIO_PORT			//
#define CC1101_CSN_GPIO_PIN			SPI_NSS_GPIO_PIN



/** 口线操作函数定义 */
#define CC1101_SET_CSN_HIGH( )			spi_set_nss_high( )
#define CC1101_SET_CSN_LOW( )			spi_set_nss_low( )
#define CC1101_REV_CSN()                        spi_nss_rev() 

#define CC1101_GET_GDO0_STATUS( )		(( CC1101_GDO0_GPIO_PORT->IDR & (uint32_t)CC1101_GDO0_GPIO_PIN) != CC1101_GDO0_GPIO_PIN ) ? 0 : 1	//GDO0状态
#define CC1101_GET_GDO2_STATUS( )		(( CC1101_GDO2_GPIO_PORT->IDR & (uint32_t)CC1101_GDO2_GPIO_PIN) != CC1101_GDO2_GPIO_PIN ) ? 0 : 1	//GDO2状态

/** 枚举量定义 */
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




void CC1101_Write_Cmd( uint8_t Command );                                                       //写入命令
void CC1101_Write_Reg( uint8_t Addr, uint8_t WriteValue );                                      //写入寄存器
void CC1101_Write_Multi_Reg( uint8_t Addr, uint8_t *pWriteBuff, uint8_t WriteSize );            //连续写入
uint8_t CC1101_Read_Reg( uint8_t Addr );                                                        //读取寄存器，0x30之后的状态寄存器只能单个读取
void CC1101_Read_Multi_Reg( uint8_t Addr, uint8_t *pReadBuff, uint8_t ReadSize );               //连续读取
uint8_t CC1101_Read_Status( uint8_t Addr );                                                     //读取状态
void CC1101_Set_Mode( CC1101_ModeType Mode );                                                   //设置模式
void CC1101_Set_Idle_Mode( void );                                                             //进入空闲模式

void CC1101_Set_Address( uint8_t address, CC1101_AddrModeType AddressMode);                     //地址过滤：不过滤、点对点、0x00广播、0x00和0xff广播
void CC1101_Set_Sync( uint16_t Sync );                                                          //设置同步字
void CC1101_Clear_TxBuffer( void );                                                             //清空TX FIFO
void CC1101_Clear_RxBuffer( void );                                                             //清空RX FIFO
uint8_t CC1101_Get_TxCounter( void );                                                           //获取TX FIFO字节数目
void CC1101_Tx_Packet( uint8_t *pTxBuff, uint8_t TxSize, CC1101_TxDataModeType DataMode );      //发送数据包
uint8_t CC1101_Get_RxCounter( void );                                                           //获取RX FIFO字节数目
uint8_t CC1101_Rx_Packet( uint8_t *RxBuff );                                                     //接收数据包
void CC1101_Reset( void );                                                                      //重启
void CC1101_Init( void );                                                                       //初始化
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CC1101_Set_Sleep(void);
void CC1101_Wakeup(void);
void CC1101_Rx_INT_Handler(void);
void CC1101_Rx_INT_Init(void);
void SetACK(void);
void DesetACK(void);
uint8_t GetACK(void);

#endif
