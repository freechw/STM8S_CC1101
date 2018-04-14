/**
  ******************************************************************************
  * @author  ��ҫ�Ƽ� ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   CC1101�Ĵ��� �����H�ļ�
  ******************************************************************************
  * @attention
  *
  * ����	:	http://www.ashining.com
  * �Ա�	:	https://shop105912646.taobao.com
  * ����Ͱ�:	https://cdzeyao.1688.com
  ******************************************************************************
  */



#ifndef __DRV_CC1101_REG_H__
#define __DRV_CC1101_REG_H__


/** CC1101�Ĵ������� */
//����
#define CC1101_IOCFG2       0x00        // GDO2 �����������
#define CC1101_IOCFG1       0x01        // GDO1 �����������
#define CC1101_IOCFG0       0x02        // GDO0 �����������
#define CC1101_FIFOTHR      0x03        // RX FIFO �� TX FIFO ����
#define CC1101_SYNC1        0x04        // ͬ���֣�INT8U��MSB
#define CC1101_SYNC0        0x05        // ͬ���֣�INT8U��LSB
#define CC1101_PKTLEN       0x06        // ���ݰ�����
#define CC1101_PKTCTRL1     0x07        // ���ݰ��Զ�����
#define CC1101_PKTCTRL0     0x08        // ���ݰ��Զ�����
#define CC1101_ADDR         0x09        // �豸��ַ
#define CC1101_CHANNR       0x0A        // �ŵ���
#define CC1101_FSCTRL1      0x0B        // Ƶ�ʺϳ������ƣ����ֽ�
#define CC1101_FSCTRL0      0x0C        // Ƶ�ʺϳ������ƣ����ֽ�
#define CC1101_FREQ2        0x0D        // Ƶ�ʿ��ƴʻ㣬���ֽ�
#define CC1101_FREQ1        0x0E        // Ƶ�ʿ��ƴʻ㣬�м��ֽ�
#define CC1101_FREQ0        0x0F        // Ƶ�ʿ��ƴʻ㣬���ֽ�
#define CC1101_MDMCFG4      0x10        // ����������
#define CC1101_MDMCFG3      0x11        // ����������
#define CC1101_MDMCFG2      0x12        // ����������
#define CC1101_MDMCFG1      0x13        // ����������
#define CC1101_MDMCFG0      0x14        // ����������
#define CC1101_DEVIATN      0x15        // ��������������  Modem deviation setting
#define CC1101_MCSM2        0x16        // ��ͨ�ſ���״̬������  Main Radio Control State Machine configuration
#define CC1101_MCSM1        0x17        // ��ͨ�ſ���״̬������  Main Radio Control State Machine configuration
#define CC1101_MCSM0        0x18        // ��ͨ�ſ���״̬������  Main Radio Control State Machine configuration
#define CC1101_FOCCFG       0x19        // Ƶ��ƫ�Ʋ�������  Frequency Offset Compensation configuration
#define CC1101_BSCFG        0x1A        // λͬ������  Bit Synchronization configuration
#define CC1101_AGCCTRL2     0x1B        // AGC����  AGC control
#define CC1101_AGCCTRL1     0x1C        // AGC����  AGC control
#define CC1101_AGCCTRL0     0x1D        // AGC����  AGC control
#define CC1101_WOREVT1      0x1E        // ���ֽ�ʱ��0��ͣ High INT8U Event 0 timeout
#define CC1101_WOREVT0      0x1F        // ���ֽ�ʱ��0��ͣ  Low INT8U Event 0 timeout
#define CC1101_WORCTRL      0x20        // ���߿��ƣ�Ҳ�е�Ų��������  Wake On Radio control
#define CC1101_FREND1       0x21        // ǰĩ��RX����  Front end RX configuration
#define CC1101_FREND0       0x22        // ǰĩ��TX����  Front end TX configuration
#define CC1101_FSCAL3       0x23        // Ƶ�ʺϳ���У׼  Frequency synthesizer calibration
#define CC1101_FSCAL2       0x24        // Ƶ�ʺϳ���У׼  Frequency synthesizer calibration
#define CC1101_FSCAL1       0x25        // Ƶ�ʺϳ���У׼  Frequency synthesizer calibration
#define CC1101_FSCAL0       0x26        // Ƶ�ʺϳ���У׼  Frequency synthesizer calibration
#define CC1101_RCCTRL1      0x27        // RC��������  RC oscillator configuration
#define CC1101_RCCTRL0      0x28        // RC��������  RC oscillator configuration
#define CC1101_FSTEST       0x29        // Ƶ�ʺϳ���У׼����  RCFrequency synthesizer calibration control
#define CC1101_PTEST        0x2A        // ��Ʒ����  Production test
#define CC1101_AGCTEST      0x2B        // AGC����  AGC test
#define CC1101_TEST2        0x2C        // ���ֲ�������  Various test settings
#define CC1101_TEST1        0x2D        // ���ֲ�������  Various test settings
#define CC1101_TEST0        0x2E        // ���ֲ�������  Various test settings

// ����
#define CC1101_SRES         0x30        // ����
                                        //Reset chip.
#define CC1101_SFSTXON      0x31        // ������У׼Ƶ�ʺϳ�������MCSM0.FSAUTOCAL=1�� 
                                        //Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        // If in RX/TX: Go to a wait state where only the synthesizer is
                                        // running (for quick RX / TX turnaround).
#define CC1101_SXOFF        0x32        // �رվ�������  
                                        //Turn off crystal oscillator.
#define CC1101_SCAL         0x33        // У׼Ƶ�ʺϳ������ضϣ������������������ڲ������ֶ�У׼ģʽ��MCSM0.FS_AUTOCAL=0��������£�SCAL�ܴӿ���ģʽ�˲���  
                                        //Calibrate frequency synthesizer and turn it off
                                        // (enables quick start).
#define CC1101_SRX          0x34        // ����RX������һ״̬Ϊ������MCSM0.FS_AUTOCAL=1����������У׼��  
                                        //Enable RX. Perform calibration first if coming from IDLE and
                                        // MCSM0.FS_AUTOCAL=1.
#define CC1101_STX          0x35        // ����״̬������TX����MCSM0.FS_AUTOCAL=1��������У׼������RX״̬��CCA���ã����ŵ�Ϊ�������TX  
                                        //In IDLE state: Enable TX. Perform calibration first if
                                        // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        // Only go to TX if channel is clear.
#define CC1101_SIDLE        0x36        // �뿪RX/TX,�ض�Ƶ�ʺϳ������뿪��Ų�����ģʽ������  
                                        //Exit RX / TX, turn off frequency synthesizer and exit
                                        // Wake-On-Radio mode if applicable.
#define CC1101_SAFC         0x37        // ����22.1���г���Ƶ�ʺϳ�����AFC����  
                                        //Perform AFC adjustment of the frequency synthesizer
#define CC1101_SWOR         0x38        // ����27.5���������Զ�RXѡ�����У���Ų����  
                                        //Start automatic RX polling sequence (Wake-on-Radio)
#define CC1101_SPWD         0x39        // ��CSnΪ��ʱ���빦�ʽ���ģʽ��  
                                        //Enter power down mode when CSn goes high.
#define CC1101_SFRX         0x3A        // ��ϴRX FIFO����  
                                        //Flush the RX FIFO buffer.
#define CC1101_SFTX         0x3B        // ��ϴTX FIFO����  
                                        //Flush the TX FIFO buffer.
#define CC1101_SWORRST      0x3C        // ����������ʵʱ��ʱ��  
                                        //Reset real time clock.
#define CC1101_SNOP         0x3D        // �޲�������������Ϊ���򵥵�������˲������Ϊ2�ֽڡ�  No operation. May be used to pad strobe commands to two
                                        // INT8Us for simpler software.

//״̬
#define CC1101_PARTNUM      0x30        // �����Ŀ
#define CC1101_VERSION      0x31        // ��ǰ�汾���
#define CC1101_FREQEST      0x32        // Ƶ��ƫ�ƹ���
#define CC1101_LQI          0x33        // ��·�������������
#define CC1101_RSSI         0x34        // �����ź�ǿ��ָʾ
#define CC1101_MARCSTATE    0x35        // ����״̬��״̬
#define CC1101_WORTIME1     0x36        // WOR ��ʱ�����ֽ�
#define CC1101_WORTIME0     0x37        // WOR ��ʱ�����ֽ�
#define CC1101_PKTSTATUS    0x38        // ��ǰ GDOx ״̬�����ݰ�״̬
#define CC1101_VCO_VC_DAC   0x39        // PLL У׼ģ��ĵ�ǰ����
#define CC1101_TXBYTES      0x3A        // TX FIFO �е�������ֽ���
#define CC1101_RXBYTES      0x3B        // RX FIFO �е�������ֽ���


#define CC1101_PATABLE      0x3E        //PATABLE��ַ��������ѡ�� PA ���ʿ�������
#define CC1101_TXFIFO       0x3F        //TX FIFO��ȡ��ַ��ֻд
#define CC1101_RXFIFO       0x3F        //RX FIFO��ȡ��ַ��ֻ��

#define WRITE_SINGLE       0x00         //д�뵥���ֽ�
#define WRITE_BURST        0x40         //д�����ֽ�

#define READ_SINGLE        0x80		//��ȡ�����ֽ�
#define READ_BURST         0xC0		//��ȡ����ֽ�

#define BYTES_IN_RXFIFO    0x7F  	//���ջ�������Ч�ֽ�
#define BYTES_IN_TXFIFO    0x7F  	//���ͻ�������Ч�ֽ�

#define CRC_OK             0x80 	//CRCУ��ͨ����־λ


#endif
