/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   CC1101寄存器 命令定义H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */



#ifndef __DRV_CC1101_REG_H__
#define __DRV_CC1101_REG_H__


/** CC1101寄存器定义 */
//配置
#define CC1101_IOCFG2       0x00        // GDO2 输出引脚配置
#define CC1101_IOCFG1       0x01        // GDO1 输出引脚配置
#define CC1101_IOCFG0       0x02        // GDO0 输出引脚配置
#define CC1101_FIFOTHR      0x03        // RX FIFO 和 TX FIFO 门限
#define CC1101_SYNC1        0x04        // 同步字，INT8U，MSB
#define CC1101_SYNC0        0x05        // 同步字，INT8U，LSB
#define CC1101_PKTLEN       0x06        // 数据包长度
#define CC1101_PKTCTRL1     0x07        // 数据包自动控制
#define CC1101_PKTCTRL0     0x08        // 数据包自动控制
#define CC1101_ADDR         0x09        // 设备地址
#define CC1101_CHANNR       0x0A        // 信道数
#define CC1101_FSCTRL1      0x0B        // 频率合成器控制，高字节
#define CC1101_FSCTRL0      0x0C        // 频率合成器控制，低字节
#define CC1101_FREQ2        0x0D        // 频率控制词汇，高字节
#define CC1101_FREQ1        0x0E        // 频率控制词汇，中间字节
#define CC1101_FREQ0        0x0F        // 频率控制词汇，低字节
#define CC1101_MDMCFG4      0x10        // 调制器配置
#define CC1101_MDMCFG3      0x11        // 调制器配置
#define CC1101_MDMCFG2      0x12        // 调制器配置
#define CC1101_MDMCFG1      0x13        // 调制器配置
#define CC1101_MDMCFG0      0x14        // 调制器配置
#define CC1101_DEVIATN      0x15        // 调制器背离设置  Modem deviation setting
#define CC1101_MCSM2        0x16        // 主通信控制状态机配置  Main Radio Control State Machine configuration
#define CC1101_MCSM1        0x17        // 主通信控制状态机配置  Main Radio Control State Machine configuration
#define CC1101_MCSM0        0x18        // 主通信控制状态机配置  Main Radio Control State Machine configuration
#define CC1101_FOCCFG       0x19        // 频率偏移补偿配置  Frequency Offset Compensation configuration
#define CC1101_BSCFG        0x1A        // 位同步配置  Bit Synchronization configuration
#define CC1101_AGCCTRL2     0x1B        // AGC控制  AGC control
#define CC1101_AGCCTRL1     0x1C        // AGC控制  AGC control
#define CC1101_AGCCTRL0     0x1D        // AGC控制  AGC control
#define CC1101_WOREVT1      0x1E        // 高字节时间0暂停 High INT8U Event 0 timeout
#define CC1101_WOREVT0      0x1F        // 低字节时间0暂停  Low INT8U Event 0 timeout
#define CC1101_WORCTRL      0x20        // 无线控制，也叫电磁波激活控制  Wake On Radio control
#define CC1101_FREND1       0x21        // 前末端RX配置  Front end RX configuration
#define CC1101_FREND0       0x22        // 前末端TX配置  Front end TX configuration
#define CC1101_FSCAL3       0x23        // 频率合成器校准  Frequency synthesizer calibration
#define CC1101_FSCAL2       0x24        // 频率合成器校准  Frequency synthesizer calibration
#define CC1101_FSCAL1       0x25        // 频率合成器校准  Frequency synthesizer calibration
#define CC1101_FSCAL0       0x26        // 频率合成器校准  Frequency synthesizer calibration
#define CC1101_RCCTRL1      0x27        // RC振荡器配置  RC oscillator configuration
#define CC1101_RCCTRL0      0x28        // RC振荡器配置  RC oscillator configuration
#define CC1101_FSTEST       0x29        // 频率合成器校准控制  RCFrequency synthesizer calibration control
#define CC1101_PTEST        0x2A        // 产品测试  Production test
#define CC1101_AGCTEST      0x2B        // AGC测试  AGC test
#define CC1101_TEST2        0x2C        // 各种测试设置  Various test settings
#define CC1101_TEST1        0x2D        // 各种测试设置  Various test settings
#define CC1101_TEST0        0x2E        // 各种测试设置  Various test settings

// 命令
#define CC1101_SRES         0x30        // 重启
                                        //Reset chip.
#define CC1101_SFSTXON      0x31        // 开启和校准频率合成器（若MCSM0.FSAUTOCAL=1） 
                                        //Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        // If in RX/TX: Go to a wait state where only the synthesizer is
                                        // running (for quick RX / TX turnaround).
#define CC1101_SXOFF        0x32        // 关闭晶体振荡器  
                                        //Turn off crystal oscillator.
#define CC1101_SCAL         0x33        // 校准频率合成器并关断（开启快速启动）。在不设置手动校准模式（MCSM0.FS_AUTOCAL=0）的情况下，SCAL能从空闲模式滤波。  
                                        //Calibrate frequency synthesizer and turn it off
                                        // (enables quick start).
#define CC1101_SRX          0x34        // 启用RX。若上一状态为空闲且MCSM0.FS_AUTOCAL=1则首先运行校准。  
                                        //Enable RX. Perform calibration first if coming from IDLE and
                                        // MCSM0.FS_AUTOCAL=1.
#define CC1101_STX          0x35        // 空闲状态：启用TX。若MCSM0.FS_AUTOCAL=1首先运行校准。若在RX状态且CCA启用：若信道为空则进入TX  
                                        //In IDLE state: Enable TX. Perform calibration first if
                                        // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        // Only go to TX if channel is clear.
#define CC1101_SIDLE        0x36        // 离开RX/TX,关断频率合成器并离开电磁波激活模式若可用  
                                        //Exit RX / TX, turn off frequency synthesizer and exit
                                        // Wake-On-Radio mode if applicable.
#define CC1101_SAFC         0x37        // 运行22.1节列出的频率合成器的AFC调节  
                                        //Perform AFC adjustment of the frequency synthesizer
#define CC1101_SWOR         0x38        // 运行27.5节描述的自动RX选举序列（电磁波激活）  
                                        //Start automatic RX polling sequence (Wake-on-Radio)
#define CC1101_SPWD         0x39        // 当CSn为高时进入功率降低模式。  
                                        //Enter power down mode when CSn goes high.
#define CC1101_SFRX         0x3A        // 冲洗RX FIFO缓冲  
                                        //Flush the RX FIFO buffer.
#define CC1101_SFTX         0x3B        // 冲洗TX FIFO缓冲  
                                        //Flush the TX FIFO buffer.
#define CC1101_SWORRST      0x3C        // 重新设置真实时间时钟  
                                        //Reset real time clock.
#define CC1101_SNOP         0x3D        // 无操作。可能用来为更简单的软件将滤波命令变为2字节。  No operation. May be used to pad strobe commands to two
                                        // INT8Us for simpler software.

//状态
#define CC1101_PARTNUM      0x30        // 组件数目
#define CC1101_VERSION      0x31        // 当前版本编号
#define CC1101_FREQEST      0x32        // 频率偏移估计
#define CC1101_LQI          0x33        // 链路质量解调器评估
#define CC1101_RSSI         0x34        // 接收信号强度指示
#define CC1101_MARCSTATE    0x35        // 控制状态机状态
#define CC1101_WORTIME1     0x36        // WOR 定时器高字节
#define CC1101_WORTIME0     0x37        // WOR 定时器低字节
#define CC1101_PKTSTATUS    0x38        // 当前 GDOx 状态和数据包状态
#define CC1101_VCO_VC_DAC   0x39        // PLL 校准模块的当前设置
#define CC1101_TXBYTES      0x3A        // TX FIFO 中的下溢和字节数
#define CC1101_RXBYTES      0x3B        // RX FIFO 中的下溢和字节数


#define CC1101_PATABLE      0x3E        //PATABLE地址，是用来选择 PA 功率控制设置
#define CC1101_TXFIFO       0x3F        //TX FIFO存取地址，只写
#define CC1101_RXFIFO       0x3F        //RX FIFO存取地址，只读

#define WRITE_SINGLE       0x00         //写入单个字节
#define WRITE_BURST        0x40         //写入多个字节

#define READ_SINGLE        0x80		//读取单个字节
#define READ_BURST         0xC0		//读取多个字节

#define BYTES_IN_RXFIFO    0x7F  	//接收缓冲区有效字节
#define BYTES_IN_TXFIFO    0x7F  	//发送缓冲区有效字节

#define CRC_OK             0x80 	//CRC校验通过标志位


#endif
