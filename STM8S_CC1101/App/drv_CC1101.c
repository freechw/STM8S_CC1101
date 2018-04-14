/**
******************************************************************************
* @author  ��ҫ�Ƽ� ASHINING
* @version V3.0
* @date    2016-10-08
* @brief   CC1101����C�ļ�
******************************************************************************
* @attention
*
* ����	:	http://www.ashining.com
* �Ա�	:	https://shop105912646.taobao.com
* ����Ͱ�:	https://cdzeyao.1688.com
******************************************************************************
*/


#include "drv_CC1101.h"
#include "drv_delay.h"
#include "main.h"

uint8_t ACK_Flag = 0;


extern uint16_t RXtimer_begin = 0;
extern uint16_t RXtimer_end = 0;

extern uint16_t TXtimer_begin = 0;
extern uint16_t TXtimer_end = 0;


//10, 7, 5, 0, -5, -10, -15, -20, dbm output power, 0x12 == -30dbm
const uint8_t PaTabel[ ] = { 0xc0, 0xC8, 0x84, 0x60, 0x68, 0x34, 0x1D, 0x0E};
static const uint8_t CC1101InitData[ 22 ][ 2 ]= 
{
  { CC1101_IOCFG0,      0x06 },
  { CC1101_FIFOTHR,     0x47 },/////0x47
  { CC1101_PKTCTRL0,    0x05 },
  { CC1101_CHANNR,      0x96 },	//430M   0x96
  { CC1101_FSCTRL1,     0x06 },
  { CC1101_FREQ2,       0x0F },//0x0F    10
  { CC1101_FREQ1,       0x62 },//0x62    89
  { CC1101_FREQ0,       0x76 },//0x76    D9
  { CC1101_MDMCFG4,     0x8C },////////��ʼ  G4=F6��G3=43������1���ֽ�ʱ��Ϊ20ms   500k = 0xFE 0x3B   100k = 0xFB  0xFB     def 115.2k = 8C  22
  { CC1101_MDMCFG3,     0x22 },///////�޸�   40k = G4=FA��G3=9D������1���ֽ�ʱ��Ϊ1ms     Ĭ��ֵFC ��22��ʱ��0.3ms�����շ���Ӧ����
  { CC1101_MDMCFG2,     0x75 },/////////0x13
  { CC1101_DEVIATN,     0x15 },
  { CC1101_MCSM0,       0x18 },////0x18   08��У׼
  { CC1101_FOCCFG,      0x16 },
  { CC1101_WORCTRL,     0xFB },
  { CC1101_FSCAL3,      0xE9 },
  { CC1101_FSCAL2,      0x2A },
  { CC1101_FSCAL1,      0x00 },
  { CC1101_FSCAL0,      0x1F },
  { CC1101_TEST2,       0x81 },
  { CC1101_TEST1,       0x35 },
  { CC1101_MCSM1,       0x3E },//0x32    02
};


/**
* @brief :CC1101д����
* @param :
*			@Command������
* @note  :��
* @retval:��
*/
void CC1101_Write_Cmd( uint8_t Command )
{
  CC1101_SET_CSN_LOW( );					//SPIƬѡ���������иú�����������SPIƬѡ
  
  drv_spi_read_write_byte( Command );		//д����
  
  CC1101_SET_CSN_HIGH( );					//SPIȡ��Ƭѡ���������иú�����������ȡ��SPIƬѡ					
}

/**
* @brief :CC1101д�Ĵ���
* @param :
*			@Addr����ַ
*			@WriteValue��д��������ֽ�
* @note  :��
* @retval:��
*/
void CC1101_Write_Reg( uint8_t Addr, uint8_t WriteValue )
{
  CC1101_SET_CSN_LOW( );					
  
  drv_spi_read_write_byte( Addr );		//д��ַ
  drv_spi_read_write_byte( WriteValue );	//д����
  
  CC1101_SET_CSN_HIGH( );					
}

/**
* @brief :CC1101����д�Ĵ���
* @param :
*			@Addr����ַ
*			@pWriteBuff��д������ݴ��׵�ַ
*			@WriteSize��д������ݸ���
* @note  :��
* @retval:��
*/
void CC1101_Write_Multi_Reg( uint8_t Addr, uint8_t *pWriteBuff, uint8_t WriteSize )
{
  uint8_t i;
  
  CC1101_SET_CSN_LOW( );					
  
  drv_spi_read_write_byte( Addr | WRITE_BURST );	//����д���� ���׵�ַ
  for( i = 0; i < WriteSize; i ++ )
  {
    drv_spi_read_write_byte( *( pWriteBuff + i ) );	//����д������
  }
  
  CC1101_SET_CSN_HIGH( );					
}

/**
* @brief :CC1101���Ĵ���
* @param :
*			@Addr����ַ
* @note  :��
* @retval:�Ĵ���ֵ
*/
uint8_t CC1101_Read_Reg( uint8_t Addr )
{
  uint8_t l_RegValue = 0;
  
  CC1101_SET_CSN_LOW( );
  
  drv_spi_read_write_byte( Addr | READ_SINGLE );	//���������� ����ַ
  l_RegValue = drv_spi_read_write_byte( 0xFF );	//��ȡ�Ĵ���
  
  CC1101_SET_CSN_HIGH( );
  
  return l_RegValue;
}

/**
* @brief :CC1101��һ���Ĵ���״̬
* @param :
*			@Addr����ַ
* @note  :��
* @retval:�Ĵ���״̬
*/
uint8_t CC1101_Read_Status( uint8_t Addr )
{
  uint8_t l_RegStatus = 0;
  
  CC1101_SET_CSN_LOW( );
  
  drv_spi_read_write_byte( Addr | READ_BURST );	//���������� ����ַ
  l_RegStatus = drv_spi_read_write_byte( 0xFF );	//��ȡ״̬
  
  CC1101_SET_CSN_HIGH( );
  
  return l_RegStatus;
}

/**
* @brief :CC1101�������Ĵ���
* @param :
*			@Addr����ַ
*			@pReadBuff����ȡ���ݴ���׵�ַ
*			@ReadSize����ȡ���ݵĸ���
* @note  :��
* @retval:��
*/
void CC1101_Read_Multi_Reg( uint8_t Addr, uint8_t *pReadBuff, uint8_t ReadSize )
{
  uint8_t i = 0, j = 0;
  
  CC1101_SET_CSN_LOW( );
  
  drv_spi_read_write_byte( Addr | READ_BURST);	//���������� ���׵�ַ
  for( i = 0; i < ReadSize; i ++ )
  {
    for( j = 0; j < 20; j ++ );
    *( pReadBuff + i ) = drv_spi_read_write_byte( 0xFF );	//������ȡ����
  }
  
  CC1101_SET_CSN_HIGH( );
}

/**
* @brief :CC1101���ͽ���ģʽ����
* @param :
*			@Mode��TX_MODE������ģʽ RX_MODE������ģʽ
* @note  :��
* @retval:�Ĵ���״̬
*/
void CC1101_Set_Mode( CC1101_ModeType Mode )
{
  //uint8_t i,j;
  if( Mode == TX_MODE )			//����ģʽ
  {
    //CC1101_Write_Reg( CC1101_IOCFG0,0x46 );
    //CC1101_Write_Reg( CC1101_IOCFG2,0x00 );
    
    
//    
//    uint16_t mcs = drv_timer1_get_mcs();
//    uint8_t temp[4];
//    temp[0] = (TXtimer_begin - TXtimer_end) >> 8;
//    temp[1] = (TXtimer_begin - TXtimer_end) & 0x00ff;
//    temp[2] = mcs >> 8;
//    temp[3] = mcs & 0x00ff;
//    drv_uart_tx_bytes(temp ,4);
//    drv_delay_ms(1000);
    
    
    //TXtimer_begin = tc1;
    //TXtimer_begin = drv_timer1_get_ms();
    
//    uint8_t temp[2];
//    temp[0] = (TXtimer_begin - TXtimer_end) >> 8;
//    temp[1] = (TXtimer_begin - TXtimer_end) & 0x00ff;
//    drv_uart_tx_bytes(temp ,2);
    TXtimer_begin = drv_timer1_get_ms();
//    uint8_t temp[2];
//    temp[0] = (TXtimer_begin - TXtimer_end) >> 8;
//    temp[1] = (TXtimer_begin - TXtimer_end) & 0x00ff;
//    drv_uart_tx_bytes(temp ,2);
    
    CC1101_Write_Cmd( CC1101_STX );//CC1101_SFSTXON    CC1101_STX
    
    
/*
    uint16_t tc1 = drv_timer1_get_ms();

    while( 0 != CC1101_GET_GDO0_STATUS( ))		//�ȴ����� �� ���տ�ʼ
    {
//      for(i=0;i<10;i++)
//        for(j=0;j<50;j++)
//          ;
      uint16_t tc2 = drv_timer1_get_ms();
      if( 2 < (tc2 - tc1) )
      {
        //drv_uart_tx_bytes("*",1);
        break; 
      } 
    }
    */
  }
  else if( Mode == RX_MODE )		//����ģʽ
  {
    CC1101_Write_Reg( CC1101_IOCFG0,0x00);
    CC1101_Write_Reg( CC1101_IOCFG2,0x46 );
    CC1101_Write_Cmd( CC1101_SRX );
    
//    uint16_t tc1 = drv_timer1_get_ms();
//    RXtimer_begin = tc1;
    
//    uint16_t mcs = drv_timer1_get_mcs();
//    uint8_t temp[4];
//    temp[0] = (RXtimer_begin - RXtimer_end) >> 8;
//    temp[1] = (RXtimer_begin - RXtimer_end) & 0x00ff;
//    temp[2] = mcs >> 8;
//    temp[3] = mcs & 0x00ff;
//    drv_uart_tx_bytes(temp ,4);
    
//    while( 0 != CC1101_GET_GDO2_STATUS( ))		//�ȴ����� �� ���տ�ʼ
//    {
//      uint16_t tc2 = drv_timer1_get_ms();
//      if( 1 < (tc2 - tc1) )
//      {
    
    
        //drv_uart_tx_bytes("*",1);
//        RXtimer_end = drv_timer1_get_ms();
//        uint16_t mcs = drv_timer1_get_mcs();
//        uint8_t temp[4];
//        temp[0] = (RXtimer_end - RXtimer_begin) >> 8;
//        temp[1] = (RXtimer_end - RXtimer_begin) & 0x00ff;
//        temp[2] = mcs >> 8;
//        temp[3] = mcs & 0x00ff;
//        drv_uart_tx_bytes(temp ,4);
    
    
//        break;
//      }
    
    
//      drv_delay_ms( 1 );
//      if( 100 == WaitTimeOut++ )
//      {
//        //drv_uart_tx_bytes("RXMODE",6);
//        break; 
//      } 
    //}
  }
  
  
}

/**
* @brief :CC1101�������ģʽ
* @param :��
* @note  :��
* @retval:��
*/ 
void CC1101_Set_Idle_Mode( void )
{
  CC1101_Write_Cmd( CC1101_SIDLE );
}

/**
* @brief :CC1101���õ�ַ
* @param :
*			@Address�����õ��豸��ֵַ
*			@AddressMode����ַ���ģʽ
* @note  :��
* @retval:��
*/
void CC1101_Set_Address( uint8_t Address, CC1101_AddrModeType AddressMode)
{
  uint8_t btmp = 0;
  
  btmp = CC1101_Read_Reg( CC1101_PKTCTRL1 ) & ~0x03;	//��ȡCC1101_PKTCTRL1�Ĵ�����ʼֵ
  CC1101_Write_Reg( CC1101_ADDR, Address );			//�����豸��ַ
  
  if( AddressMode == BROAD_ALL )     { }				//������ַ
  else if( AddressMode == BROAD_NO  )
  { 
    btmp |= 0x01;									//����ַ ���ǲ����㲥
  }
  else if( AddressMode == BROAD_0   )
  { 
    btmp |= 0x02;									//0x00Ϊ�㲥
  }
  else if( AddressMode == BROAD_0AND255 ) 
  {
    btmp |= 0x03; 									//0x00 0xFFΪ�㲥
  } 
  
  CC1101_Write_Reg( CC1101_PKTCTRL1, btmp);			//д���ַģʽ	
}

/**
* @brief :CC1101����ͬ���ֶ�
* @param :��
* @note  :��
* @retval:��
*/
void CC1101_Set_Sync( uint16_t Sync )
{
  CC1101_Write_Reg( CC1101_SYNC1, 0xFF & ( Sync >> 8 ) );
  CC1101_Write_Reg( CC1101_SYNC0, 0xFF & Sync ); 	//д��ͬ���ֶ� 16Bit
}

/**
* @brief :CC1101��շ��ͻ�����
* @param :��
* @note  :��
* @retval:��
*/ 
void CC1101_Clear_TxBuffer( void )
{
  CC1101_Set_Idle_Mode( );					//���Ƚ���IDLEģʽ
  CC1101_Write_Cmd( CC1101_SFTX );			//д���巢�ͻ���������		
}

/**
* @brief :CC1101��ս��ջ�����
* @param :��
* @note  :��
* @retval:��
*/
void CC1101_Clear_RxBuffer( void )
{
  CC1101_Set_Idle_Mode();						//���Ƚ���IDLEģʽ
  CC1101_Write_Cmd( CC1101_SFRX );			//д������ջ���������
}

/**
* @brief :CC1101�������ݰ�
* @param :
*			@pTxBuff���������ݻ�����
*			@TxSize���������ݳ���
*			@DataMode������ģʽ
* @note  :��
* @retval:��
*/ 
extern uint8_t write = 0;
void CC1101_Tx_Packet( uint8_t *pTxBuff, uint8_t TxSize, CC1101_TxDataModeType DataMode )
{  
  uint8_t Address;//,i,j;
  
  
  
  if( DataMode == BROADCAST )             
  {
    Address = 0; 
  }
  else if( DataMode == ADDRESS_CHECK )    
  { 
    Address = CC1101_Read_Reg( CC1101_ADDR ); 
  }
  
  //CC1101_Clear_TxBuffer( );
  
  if(( CC1101_Read_Reg( CC1101_PKTCTRL1 ) & 0x03 ) != 0 )	
  {
    CC1101_Write_Reg( CC1101_TXFIFO, TxSize + 1 );		
    CC1101_Write_Reg( CC1101_TXFIFO, Address );			//д�볤�Ⱥ͵�ַ ���ڶ�һ���ֽڵ�ַ��ʱ����Ӧ�ü�1
  }
  else
  {
    CC1101_Write_Reg( CC1101_TXFIFO, TxSize );			//ֻд���� ������ַ
  }
  
  //CC1101_Read_Reg( CC1101_PKTCTRL1 );
  //CC1101_Write_Reg( CC1101_TXFIFO, TxSize );			//ֻд���� ������ַ
  
  CC1101_Write_Multi_Reg( CC1101_TXFIFO, pTxBuff, TxSize );	//д������
//  CC1101_SET_CSN_LOW( );
//  drv_spi_read_write_byte( CC1101_TXFIFO | WRITE_BURST);		//д��ַ
//  drv_spi_read_write_byte( TxSize );	//д����
//  //drv_spi_read_write_byte( CC1101_TXFIFO );//| WRITE_BURST );	//����д���� ���׵�ַ
//  drv_spi_read_write_byte( *pTxBuff );	//����д������
//  CC1101_SET_CSN_HIGH( );
  
  //TXtimer_begin = drv_timer1_get_ms();
  
  //////////////////////////////
  //drv_uart_tx_bytes(&Address, 1);
  //u8 rx_counter = CC1101_Get_TxCounter();
  //drv_uart_tx_bytes(&rx_counter, 1);
//while(1)
//{
  
  CC1101_Set_Mode( TX_MODE );				//����ģʽ
  //enableInterrupts();
  
  uint16_t tc1 = drv_timer1_get_ms();
  while(write == 0)
  {
    uint16_t tc2 = drv_timer1_get_ms();
    if(1 < tc2 - tc1)
    {
      break;
    }
  }
  write = 0;
/*
  while( 0 == CC1101_GET_GDO0_STATUS( ))		//�ȴ��������
  {
//    for(i=0;i<10;i++)
//      for(j=0;j<50;j++)
//        ;
    uint16_t tc2 = drv_timer1_get_ms();
    if( 1 < (tc2 -tc1) )
    {
      drv_uart_tx_bytes("*",1);
      //CC1101_Init( );
      break; 
    }
  }
  */
  
//  TXtimer_end = drv_timer1_get_ms();
//  uint8_t temp[2];
//  temp[0] = (TXtimer_end - TXtimer_begin) >> 8;
//  temp[1] = (TXtimer_end - TXtimer_begin) & 0x00ff;
//  drv_uart_tx_bytes(temp ,2);
//}
  
}

/**
* @brief :CC1101��ȡ���յ����ֽ���
* @param :��
* @note  :��
* @retval:���յ������ݸ���
*/
uint8_t CC1101_Get_RxCounter( void )
{
  return ( CC1101_Read_Status( CC1101_RXBYTES ) & BYTES_IN_RXFIFO );	
}

/**
* @brief :CC1101��ȡTX�е��ֽ���
* @param :��
* @note  :��
* @retval:���յ������ݸ���
*/
uint8_t CC1101_Get_TxCounter( void )
{
  return ( CC1101_Read_Status( CC1101_TXBYTES ) & BYTES_IN_TXFIFO );	
}

/**
* @brief :CC1101�������ݰ�
* @param :
*			@RxBuff���������ݻ�����
* @note  :��
* @retval�����յ����ֽ�����0��ʾ������
*/
extern uint8_t read = 0;
uint8_t CC1101_Rx_Packet( uint8_t *RxBuff )
{
  uint8_t l_PktLen = 0;
  uint8_t l_Status[ 2 ] = { 0 };
  //uint8_t i,j;
  //uint16_t l_RxWaitTimeout = 0;
  
  CC1101_Clear_RxBuffer( );
  CC1101_Set_Mode( RX_MODE );
  //enableInterrupts();
  uint16_t tc1 = drv_timer1_get_ms(); 
  RXtimer_begin = tc1;

  /*
  uint16_t tc1 = drv_timer1_get_ms();  
  
  while( 1 == CC1101_GET_GDO2_STATUS( ))		//�ȴ��������
  {
//    for(i=0;i<30;i++)
//        for(j=0;j<100;j++)
//          ;
    uint16_t tc2 = drv_timer1_get_ms();
      if( 1 < (tc2 - tc1) )
      {
        //drv_timer1_disable();
        //drv_uart_tx_bytes("***RX***",8);
//        RXtimer_end = drv_timer1_get_ms();
//        uint16_t mcs = drv_timer1_get_mcs();
//        uint8_t temp[4];
//        temp[0] = (RXtimer_end - RXtimer_begin) >> 8;
//        temp[1] = (RXtimer_end - RXtimer_begin) & 0x00ff;
//        temp[2] = mcs >> 8;
//        temp[3] = mcs & 0x00ff;
//        drv_uart_tx_bytes(temp ,4);
        //RXtimer_begin = drv_timer1_get_ms();
        break;
      }
    
//    drv_delay_ms( 1 );
//    if( 100 == l_RxWaitTimeout++ )
//    {
//      l_RxWaitTimeout = 0;
//      //CC1101_Init( );
//      //drv_uart_tx_bytes("RX",2);
//      break; 
//    } 
  }
  //return 0;
  //drv_timer1_disable();

  
  //u8 rx_counter = CC1101_Get_RxCounter();
  //drv_uart_tx_bytes(&rx_counter, 1);
  */
  
  
  while(read == 0)
  {
    uint16_t tc2 = drv_timer1_get_ms();
    if( 3 <= (tc2 - tc1) )
    {
      //disableInterrupts();
      RXtimer_end = drv_timer1_get_ms();
      break;
    }
  }
  if(read == 1)
  {
    read = 0;
    if( 0 != CC1101_Get_RxCounter())//rx_counter)
    {
      l_PktLen = CC1101_Read_Reg( CC1101_RXFIFO );           // ��ȡ������Ϣ
      
      if( ( CC1101_Read_Reg( CC1101_PKTCTRL1 ) & 0x03 ) != 0 )
      {
        CC1101_Read_Reg( CC1101_RXFIFO );					//������ݰ��а�����ַ��Ϣ �����ȡ��ַ��Ϣ
        l_PktLen--; 		//��ȥһ����ַ�ֽ�
      }
      if( l_PktLen == 0 )           
      {
        return 0;			//������
      }
      //    else 
      //    {
      //      l_PktLen--; 		//��ȥһ����ַ�ֽ�
      //    }
      CC1101_Read_Multi_Reg( CC1101_RXFIFO, RxBuff, l_PktLen ); 	//��ȡ����
      CC1101_Read_Multi_Reg( CC1101_RXFIFO, l_Status, 2 );		//��ȡ���ݰ�������������ֽڣ���һ��ΪCRC��־λ
      
      CC1101_Clear_RxBuffer( );
      
      //return l_PktLen;
      
      if( l_Status[ 1 ] & CRC_OK )
      {   
        return l_PktLen; 
      }
      else
      {   
        return 0; 
      }
    }
    else   
    {  
      //CC1101_Set_Idle_Mode();
      return 0; 
    }
  }
  else
  {
    read = 0;
    //CC1101_Set_Idle_Mode();
    return 0; 
  }
}

/**
* @brief :CC1101��λ
* @param :��
* @note  :��
* @retval:��
*/
void CC1101_Reset( void )
{
  CC1101_SET_CSN_HIGH( );
  CC1101_SET_CSN_LOW( );
  CC1101_SET_CSN_HIGH( );
  drv_delay_ms( 1 );
  CC1101_Write_Cmd( CC1101_SRES );
}

/**
* @brief :CC1101���ų�ʼ��
* @param :��
* @note  :��
* @retval:��
*/ 
static void CC1101_Gpio_Init( void )
{
  //GDO0 GDO2����Ϊ��������
#ifdef __CC1101_TX_TEST__
  GPIO_Init( CC1101_GDO0_GPIO_PORT, CC1101_GDO0_GPIO_PIN, GPIO_MODE_IN_PU_IT  );
  GPIO_Init( CC1101_GDO2_GPIO_PORT, CC1101_GDO2_GPIO_PIN, GPIO_MODE_IN_PU_NO_IT  );
#else
  GPIO_Init( CC1101_GDO0_GPIO_PORT, CC1101_GDO0_GPIO_PIN, GPIO_MODE_IN_PU_NO_IT  );
  GPIO_Init( CC1101_GDO2_GPIO_PORT, CC1101_GDO2_GPIO_PIN, GPIO_MODE_IN_PU_IT  );
#endif
}

/**
* @brief :CC1101��ʼ��
* @param :��
* @note  :��
* @retval:��
*/
void CC1101_Init( void )
{
  uint8_t i = 0;
  
  CC1101_Gpio_Init( );
  CC1101_Reset( );    
  
  for( i = 0; i < 22; i++ )
  {
    CC1101_Write_Reg( CC1101InitData[i][0], CC1101InitData[i][1] );
  }
  CC1101_Set_Address( 0x05, BROAD_ALL  );	//�豸��ַ �� ��ַ���ģʽ����  BROAD_0AND255
  CC1101_Set_Sync( 0x8799 );					//ͬ���ֶ�����
  CC1101_Write_Reg(CC1101_MDMCFG1, 0x22);//0x72		//���ƽ��������
  
  CC1101_Write_Multi_Reg( CC1101_PATABLE, (uint8_t*)PaTabel, 8 );
}


//////////////////////////////////////
/**
* @brief :CC1101����WOR����
* @param :��
* @note  :��
* @retval:��
*/ 
void CC1101_Set_Sleep(void)
{
  
  CC1101_Set_Idle_Mode();
  //CC1101_Write_Cmd( CC1101_SWOR );		//����˯��
  CC1101_Write_Cmd( CC1101_SPWD );		//����˯��
  
}

/**
* @brief :CC1101��˯�߻���
* @param :��
* @note  :��
* @retval:��
*/ 
void CC1101_Wakeup(void)
{
  //u8 status;
  
  //status = CC1101_Read_Status(CC1101_MARCSTATE);
  //drv_uart_tx_bytes(&status, 1);
  
  //if(status != 0x00)
  //{
  //return;//�������˯��״̬��ֱ�ӷ���
  //}
  uint8_t i,j;
  CC1101_SET_CSN_LOW();//initiate wakeup
  CC1101_SET_CSN_LOW();//initiate wakeup
  //drv_delay_ms( 1 );//waite for xsoc is stable
  CC1101_SET_CSN_HIGH( );//wakeup complete
  CC1101_SET_CSN_HIGH( );//wakeup complete
  
  CC1101_Set_Idle_Mode();//enter IDLE mode
  
  for(i=0;i<160;i++)
    for(j=0;j<100;j++)
      ;
  //status = CC1101_Read_Status(CC1101_MARCSTATE);
  //drv_uart_tx_bytes(&status, 1);
  
  //  drv_delay_ms( 10 );
  //  CC1101_Write_Cmd( CC1101_SWOR );		//����˯��
  //  drv_delay_ms( 100 );
  
}


void CC1101_Rx_INT_Handler(void)
{
//  uint8_t l_PktLen = 0;
//  uint8_t l_Status[ 2 ] = { 0 };
//  uint8_t RxBuff[64];
//  uint8_t Address;
//
//  //CC1101_Clear_RxBuffer( );
//  //CC1101_Set_Mode( RX_MODE );
//
//
//  
//  //u8 rx_counter = CC1101_Get_RxCounter();
//  //drv_uart_tx_bytes(&rx_counter, 1);
//  if( 0 != CC1101_Get_RxCounter())//rx_counter)
//  {
//    l_PktLen = CC1101_Read_Reg( CC1101_RXFIFO );           // ��ȡ������Ϣ
//    
//    if( ( CC1101_Read_Reg( CC1101_PKTCTRL1 ) & 0x03 ) != 0 )
//    {
//      Address = CC1101_Read_Reg( CC1101_RXFIFO );					//������ݰ��а�����ַ��Ϣ �����ȡ��ַ��Ϣ
//      Address = Address + Address - Address;
//      l_PktLen--; 		//��ȥһ����ַ�ֽ�
//    }
//    if( l_PktLen == 0 )           
//    {
//      CC1101_Set_Mode( RX_MODE );
//      return;			//������
//    }
//    CC1101_Read_Multi_Reg( CC1101_RXFIFO, RxBuff, l_PktLen ); 	//��ȡ����
//    CC1101_Read_Multi_Reg( CC1101_RXFIFO, l_Status, 2 );		//��ȡ���ݰ�������������ֽڣ���һ��ΪCRC��־λ
//    
//    CC1101_Clear_RxBuffer( );
//    
//    if( l_Status[ 1 ] & CRC_OK )
//    {   
//      led_green_flashing( );
//      //��������
//      if(l_PktLen >= 3 && RxBuff[0]=='C' && RxBuff[1]=='M'&& RxBuff[2]=='D' )
//      {
//#ifdef	__CC1101_TX_TEST__
//        disableInterrupts();
//        SetACK();
//        drv_uart_tx_bytes( RxBuff, l_PktLen );	//������յ����ֽ�
//#else
//        CC1101_Tx_Packet( "CMD", 3 , BROADCAST );
//        CC1101_Set_Mode( RX_MODE );
//        drv_uart_tx_bytes( RxBuff, l_PktLen );	//������յ����ֽ�
//#endif
//      }
//      else
//      {
//        //��ӡ����
//      drv_uart_tx_bytes( RxBuff, l_PktLen );	//������յ����ֽ�
//      CC1101_Set_Mode( RX_MODE );
//      
//      }
//      
//    }
//  }
                     
}


void CC1101_Rx_INT_Init(void)
{
  disableInterrupts();
   GPIO_Init(CC1101_GDO2_GPIO_PORT, (GPIO_Pin_TypeDef)CC1101_GDO2_GPIO_PIN, GPIO_MODE_IN_PU_IT);
/*
 GPIO MODE:
 *GPIO_MODE_IN_FL_NO_IT           Input floating, no external interrupt
 *GPIO_MODE_IN_PU_NO_IT           Input pull-up, no external interrupt
 *GPIO_MODE_IN_FL_IT              Input floating, external interrupt
 *GPIO_MODE_IN_PU_IT              Input pull-up, external interrupt
 *GPIO_MODE_OUT_OD_LOW_FAST       Output open-drain, low level, no slope control
 *GPIO_MODE_OUT_PP_LOW_FAST       Output push-pull, low level, no slope control
 *GPIO_MODE_OUT_OD_LOW_SLOW       Output open-drain, low level, slow slope
 *GPIO_MODE_OUT_PP_LOW_SLOW       Output push-pull, low level, slow slope
 *GPIO_MODE_OUT_OD_HIZ_FAST       Output open-drain, high-impedance level, no slope control
 *GPIO_MODE_OUT_PP_HIGH_FAST      Output push-pull, high level, no slope control
 *GPIO_MODE_OUT_OD_HIZ_SLOW       Output open-drain, high-impedance level, slow slope
 *GPIO_MODE_OUT_PP_HIGH_SLOW      Output push-pull, high level, slow slope
 */
  EXTI_DeInit();
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC ,EXTI_SENSITIVITY_RISE_ONLY);
/*
 *EXTI Sensitivity values for PORTA to PORTE
 *EXTI_SENSITIVITY_FALL_LOW     Interrupt on Falling edge and Low level
 *EXTI_SENSITIVITY_RISE_ONLY    Interrupt on Rising edge only
 *EXTI_SENSITIVITY_FALL_ONLY    Interrupt on Falling edge only
 *EXTI_SENSITIVITY_RISE_FALL    Interrupt on Rising and Falling edges
 */
  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_RISE_ONLY);
/*
 *EXTI Sensitivity values for TLI
 *EXTI_TLISENSITIVITY_FALL_ONLY         Top Level Interrupt on Falling edge only
 *EXTI_TLISENSITIVITY_RISE_ONLY         Top Level Interrupt on Rising edge only
 */
 CC1101_Clear_RxBuffer( );
 
}


void SetACK(void)
{
  ACK_Flag = 1;
}
void DesetACK(void)
{
  ACK_Flag = 0;
}
uint8_t GetACK(void)
{
  return ACK_Flag;
}