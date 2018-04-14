/**
******************************************************************************
* @author  泽耀科技 ASHINING
* @version V3.0
* @date    2016-10-08
* @brief   主函数C文件
******************************************************************************
* @attention
*
* 官网	:	http://www.ashining.com
* 淘宝	:	https://shop105912646.taobao.com
* 阿里巴巴:	https://cdzeyao.1688.com
******************************************************************************
*/




#include "main.h"					//main.h 中含有TX/RX、软件SPI/硬件SPI选择配置选项


extern uint16_t RXtimer_begin;
extern uint16_t RXtimer_end;

extern uint16_t TXtimer_begin;
extern uint16_t TXtimer_end;

extern uint8_t write;


//#if __FLAG__
//#undef __CC1101_TX_TEST__
//#endif

const char *g_Ashining = "1234567890";
uint8_t g_TxMode = 0;
uint8_t g_UartRxBuffer[ 100 ] = { 0 };
uint8_t g_RF24L01RxBuffer[ 32 ] = { 0 }; 

uint8_t RxSleepCounter = 0;


/**
* @brief :主函数 
* @param :无
* @note  :无
* @retval:无
*/ 



int main( void )
{	
  
  uint8_t i = 0, j = 0; 
  uint8_t CMD[3] = {'C','M','D'};  
#ifdef	__CC1101_TX_TEST__
  uint8_t data[4] ={'D','A','T',48}; 
  uint8_t num = 0;
#endif
 
  
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  drv_delay_ms(1000);
  drv_uart_init( 115200 );//串口初始化
  drv_led_init( );//LED初始化
  drv_spi_init( );//SPI初始化
  drv_timer1_init();//TIM1初始化
  
  //CC1101初始化
  CC1101_Init( );
  for( i = 0; i < 6; i++ )
  {
    led_red_flashing( );
    led_green_flashing( );
    drv_delay_ms( 100 );
  }
  //CC1101_Rx_INT_Init();
  //u8 red[64];
  //CC1101_Read_Multi_Reg(CC1101_IOCFG2,red,64);
  //drv_uart_tx_bytes(red,64);
  
#ifdef	__CC1101_TX_TEST__		
  //=========================================================================================//	
  ////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////// 发送 //////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  //=========================================================================================//	
  

  //CC1101_Tx_Packet( CMD, 3 , BROADCAST );
  //CC1101_Rx_Packet( g_RF24L01RxBuffer );

  //CC1101_Clear_TxBuffer( );
  
  drv_init_exint_GOD0();
  //drv_timer1_deinit_counter();
  
  CC1101_Set_Idle_Mode();
  CC1101_Write_Reg( CC1101_IOCFG0,0x46 );
  CC1101_Write_Reg( CC1101_IOCFG2,0x00 );
  
  drv_timer1_enable();
  enableInterrupts();
  while(1)
  {
//    uint8_t sta = CC1101_Read_Status(CC1101_MARCSTATE);
//    drv_uart_tx_bytes(&sta,1);
    
//    CC1101_Set_Idle_Mode();
//    continue;
    
    CC1101_Tx_Packet( &num, 1 , BROADCAST );
//    CC1101_SET_CSN_LOW( );
//    drv_spi_read_write_byte( CC1101_TXFIFO | WRITE_BURST);		//写地址
//    drv_spi_read_write_byte( 1 );	            //写长度
//    drv_spi_read_write_byte( num );            //写数据CC1101_STX
//    CC1101_SET_CSN_HIGH( );
//    
//    CC1101_SET_CSN_LOW( );
//    drv_spi_read_write_byte( CC1101_STX );		//写命令
//    CC1101_SET_CSN_HIGH( );
//    
//    while( write == 0 )
//    {
//      ;
//    }
//    write = 0;
    num++;
    
//    CC1101_Set_Idle_Mode();
//    CC1101_Write_Reg( CC1101_TXFIFO, 3 );
//    CC1101_Write_Multi_Reg( CC1101_TXFIFO, CMD, 3 );	//写入数据
    //led_red_flashing( );
    //num++;
//    CC1101_Set_Mode( TX_MODE );				//发送模式
    //drv_delay_ms(1000);
    
    //uint16_t mcs = drv_timer1_get_mcs();
//    uint8_t temp[2];
//    temp[0] = (TXtimer_end - TXtimer_begin) >> 8;
//    temp[1] = (TXtimer_end - TXtimer_begin) & 0x00ff;
//    drv_uart_tx_bytes(temp ,2);
    //continue;
/*
    //发送
    while(!GetACK())
    {
      CC1101_Tx_Packet( CMD, 3 , BROADCAST );		//模式1发送固定字符,1S一包  ADDRESS_CHECK
      //drv_delay_ms( 100 );
      led_red_flashing( );
      //led_red_flashing( );
      i = CC1101_Rx_Packet( g_RF24L01RxBuffer );		//接收字节个数
      //drv_delay_ms( 100 );
      if( 0 != i )
      {
        led_green_flashing( );
        if(i == 3 && g_RF24L01RxBuffer[0] == 'C'&& g_RF24L01RxBuffer[1] == 'M' && g_RF24L01RxBuffer[2] == 'D' )
        {
          SetACK();
          drv_uart_tx_bytes( "getACK    ", 10 );
        }
        else
        {
          drv_uart_tx_bytes( g_RF24L01RxBuffer, i );	//输出接收到的字节
        }
        
      }
    }
    DesetACK();
    num++;;
    data[3] = num;
    CC1101_Tx_Packet( data, 4 , BROADCAST );
    drv_uart_tx_bytes( "Send DATA", 9 );
    //drv_delay_ms( 1000 );
    led_red_flashing( );	
*/		
  }
  
#else
  //=========================================================================================//	
  /////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////// 接收 //////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////
  //=========================================================================================//	
  
  
  //CC1101_Rx_INT_Init();
  //CC1101_Clear_RxBuffer( );
  //  CC1101_Set_Mode( RX_MODE );
  //  enableInterrupts();
  //  while(1)
  //  {
  //    ;
  //  }
  
  
//  CC1101_Set_Sleep();
//  while(1){}
  drv_uart_tx_bytes("test",4);
  
  //uint16_t ms,us,max=0,nc=0,sum=0,ave=0;
  //drv_timer1_init();//TIM1初始化
  drv_init_exint_GOD2();
  
  CC1101_Set_Idle_Mode();
  CC1101_Write_Reg( CC1101_IOCFG0,0x00 );
  CC1101_Write_Reg( CC1101_IOCFG2,0x46 );
  
  drv_timer1_enable();
  enableInterrupts();
  while( 1 )
  {
//    u8 red[64];
//  CC1101_Read_Multi_Reg(CC1101_IOCFG2,red,64);
//  drv_uart_tx_bytes(red,64);
//  drv_delay_ms(5525);
//  continue;
  
  
//    drv_timer1_deinit_counter();
//    drv_timer1_enable();
//    drv_delay_ms(1000);
//    drv_timer1_disable();
//    CC1101_REV_CSN();
//    drv_timer1_get_time(&ms,&us);
//    
//    continue;
    
    //spi_nss_rev() ;
    //drv_delay_ms(1000);
    //continue;
    
    //CC1101_Tx_Packet( CMD, 3 , BROADCAST );
    //drv_delay_ms(1000);
    //continue;
    //led_green_on();
    //    CC1101_Clear_RxBuffer( );
    //    CC1101_Set_Mode( RX_MODE );
    
    //CC1101_Tx_Packet( CMD, 3 , BROADCAST );
    //CC1101_Set_Idle_Mode();
    
    
    
//    drv_timer1_deinit_counter();
    i = CC1101_Rx_Packet( g_RF24L01RxBuffer );		//接收字节个数
//    if(i!=0)
//    {
//      //drv_uart_tx_bytes( g_RF24L01RxBuffer, i );
//
////      uint8_t temp[4];
////      temp[0] = (RXtimer_end - RXtimer_begin) >> 8;
////      temp[1] = (RXtimer_end - RXtimer_begin) & 0x00ff;
////      drv_uart_tx_bytes(temp ,2);
//    }
//   continue;
      
    //continue;
//    drv_timer1_get_time(&ms,&us);
//    
//    nc++;
//    if(ms > max) max = nc;
//    sum = sum+ms;
//    ave = sum / nc;
//    
//    uint8_t time[8];
//    time[0] = ms >> 8;
//    time[1] = ms & 0x00ff;
//    time[2] = us << 8;
//    time[3] = us & 0x00ff;
//    time[4] = max >> 8;
//    time[5] = max & 0x00ff;
//    time[6] = ave >> 8;
//    time[7] = ave & 0x00ff;
//    
//    drv_uart_tx_bytes(&time[4],4);
    //drv_delay_ms( 500 );
    //drv_delay_ms(10);
    
    //uint8_t sta = CC1101_Read_Status(CC1101_MARCSTATE);
    //drv_uart_tx_bytes(&sta,1);
    //drv_delay_ms( 100 );
    led_green_flashing( );
    if( i != 1 )
    {
//      RXtimer_end = drv_timer1_get_ms();
//      uint16_t mcs = drv_timer1_get_mcs();
//      uint8_t temp[4];
//      temp[0] = (RXtimer_end - RXtimer_begin) >> 8;
//      temp[1] = (RXtimer_end - RXtimer_begin) & 0x00ff;
//      temp[2] = mcs >> 8;
//      temp[3] = mcs & 0x00ff;
//      drv_uart_tx_bytes(temp ,4);
      
      //drv_uart_tx_bytes( g_RF24L01RxBuffer, i );//g_RF24L01RxBuffer
      drv_uart_tx_bytes( "X", 1 );//g_RF24L01RxBuffer
      CC1101_Set_Sleep();
      //drv_delay_ms(2000);
      uint16_t sleep_start = drv_timer1_get_ms();
      uint16_t sleep_end = sleep_start;
      while(1)
      {
        for(i=0;i<30;i++)
          for(j=0;j<100;j++)
            ;
        sleep_end = drv_timer1_get_ms();
        if(1000 < (sleep_end - sleep_start ))
          break;
      }
      CC1101_Wakeup();
      //drv_delay_ms(16000);
      //RXtimer_end = drv_timer1_get_ms();
    }
    else
    {
      drv_uart_tx_bytes( g_RF24L01RxBuffer, i );//g_RF24L01RxBuffer
      //drv_uart_tx_bytes( " " , 1 );//g_RF24L01RxBuffer
      CC1101_Set_Sleep();
      //drv_delay_ms(2000);
      uint16_t sleep_start = drv_timer1_get_ms();
      uint16_t sleep_end = sleep_start;
      while(1)
      {
        for(i=0;i<30;i++)
          for(j=0;j<100;j++)
            ;
        sleep_end = drv_timer1_get_ms();
        if(1000 < (sleep_end - sleep_start ))
          break;
      }
      CC1101_Wakeup();
      //drv_delay_ms(16000);
      //RXtimer_end = drv_timer1_get_ms();
    }
    continue;
    
    
    //drv_uart_tx_bytes( g_RF24L01RxBuffer, i );	//输出接收到的字节
    
    if(i == 3 && g_RF24L01RxBuffer[0] == 'C'&& g_RF24L01RxBuffer[1] == 'M' && g_RF24L01RxBuffer[2] == 'D' )
    {
      drv_uart_tx_bytes( "getCMD and wait data...", 23 );
      RxSleepCounter = 0;
      //while(1)
      CC1101_Tx_Packet( CMD, 3 , BROADCAST );
    }
    else if(0 == i)
    {
      RxSleepCounter++;
    }
    else
    {
      //drv_uart_tx_bytes( g_RF24L01RxBuffer, i );	//输出接收到的字节
      RxSleepCounter = 3;
    }
      
    
    if(RxSleepCounter >= 3)
    {
      RxSleepCounter = 0;
      CC1101_Set_Sleep();
      drv_delay_ms(1000);
      CC1101_Wakeup();
    }
  }
  
  
  
  
  
  
  
  
  
  //        led_green_on();
  //        CC1101_Clear_RxBuffer( );
  //        C1101_WOR_Init();
  
  //CC1101_Set_Sleep();
  
  //        DelayMs(500);
  //        u8 red[47];
  //        CC1101_Read_Multi_Reg(CC1101_IOCFG2,red,47);
  //        //DelayMs(500);
  //        drv_uart_tx_bytes(red,47);
  
  //CC1101_Set_WOR();
  
  
  
  //uint16_t l_RxWaitTimeout = 0;
  
  //	u8 status;
  //        while( 1 )
  //	{
  
  //status = CC1101_Read_Status(CC1101_MARCSTATE);
  //drv_uart_tx_bytes(&status, 1);
  //if(status != 0x00)
  //{
  //u8 rxcounter = CC1101_Get_RxCounter();
  //drv_uart_tx_bytes(&rxcounter, 1);
  //CC1101_Set_Sleep();
  //}
  //CC1101_Wakeup();
  //                  while( 0 == CC1101_GET_GDO2_STATUS( ))		//等待接收完成
  //                  {
  //                        drv_delay_ms( 1 );
  //                        if( 3000 == l_RxWaitTimeout++ )
  //                        {
  //                                l_RxWaitTimeout = 0;
  //                                //CC1101_Init( );
  //                                //CC1101_Set_WOR();
  //                                break; 
  //                        } 
  //                  }
  //
  //                  //CC1101_Set_Mode( RX_MODE );
  //                  //i = CC1101_Rx_Packet( g_RF24L01RxBuffer );		//接收字节
  //                  //DelayMs(1);  //等待接收字节
  //                  i = CC1101_WOR_Rx_Packet( g_RF24L01RxBuffer );
  //                  if( 0 != i )
  //                  {
  //                          //led_green_flashing( );
  //                          drv_uart_tx_bytes( g_RF24L01RxBuffer, i );	//输出接收到的字节
  //                          led_green_flashing( );
  //                          //drv_delay_ms( 500 );
  //                  }
  //                    
  //                  
  //                  //drv_delay_ms( 500 );
  
  
  //                }
  
  
#endif
  
}



#ifdef USE_FULL_ASSERT                           //断言(参考官方)

void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif



//按键初始化
//	drv_button_init( );
//
//	while( 1 )	
//	{
//		//模式切换
//		if( BUTOTN_PRESS_DOWN == drv_button_check( ))
//		{
//			g_TxMode = 1 - g_TxMode;		//模式会在 TX_MODE_1( 0 ),TX_MODE_2( 1 )之间切换
//			
//			//状态显示清零
//			led_green_off( );
//			led_red_off( );
//			
//			if( TX_MODE_1 == g_TxMode )
//			{
//				for( i = 0; i < 6; i++ )		
//				{
//					led_red_flashing( );	//固定发送模式，红灯闪烁3次
//					drv_delay_ms( 500 );		
//				}
//			}
//			else
//			{
//				for( i = 0; i < 6; i++ )
//				{
//					led_green_flashing( );	//串口发送模式，绿灯闪烁3次
//					drv_delay_ms( 500 );
//				}
//			}
//		}

//		//发送
//		if( TX_MODE_1 == g_TxMode )
//		{
//			CC1101_Tx_Packet( (uint8_t *)g_Ashining, 10 , ADDRESS_CHECK );		//模式1发送固定字符,1S一包
//			drv_delay_ms( 1000 );	
//			led_red_flashing( );			
//		}
//		else
//		{	
//			//查询串口数据
//			i = drv_uart_rx_bytes( g_UartRxBuffer );
//			
//			if( 0 != i )
//			{
//				CC1101_Tx_Packet( g_UartRxBuffer, i , ADDRESS_CHECK );
//				led_red_flashing( );
//			}
//		}
//	}


