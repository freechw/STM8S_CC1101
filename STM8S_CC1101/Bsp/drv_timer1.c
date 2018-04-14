#include "drv_timer1.h"

#include "drv_CC1101.h"

uint16_t millisecond = 0;
uint16_t microsecond = 0;

void drv_timer1_init(  )  //us
{
//  TIM1_DeInit();//复位TIM1所有参数  
//  TIM1_TimeBaseInit(TIM1_PRESCALER_16,TIM1_COUNTERMODE_DOWN,Timer1Time,0);  
//  //TIM1的预分频器基于一个由16位寄存器  
//  //选择16分频 16M/16=1M  周期为1us   
//  TIM1_Cmd(ENABLE);//使能计时器  
//  TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);//使能TIM1中断
  //设置内部高速时钟16M为主时钟  
  //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);  
  TIM1_DeInit();//复位TIM1所有参数  
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);
  TIM1_TimeBaseInit(CLK_PRESCALER_HSIDIV1,TIM1_COUNTERMODE_UP,16000,0);  
  //TIM1的预分频器基于一个由16位寄存器  
  //选择1分频 f = 16M  周期为 1/16 us ;1ms触发一次中断  
  drv_timer1_disable();
}

void drv_timer1_enable(void)
{
  TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);
  TIM1_Cmd(ENABLE);//使能计时器
  
}
void drv_timer1_disable(void)
{
  TIM1_Cmd(DISABLE);//禁能计时器
  TIM1_ITConfig(TIM1_IT_UPDATE,DISABLE);
}
void TIM1_handler()
{
  TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
  millisecond++;
  //CC1101_REV_CSN();
  

}

void drv_timer1_deinit_counter()
{
  millisecond=0;
  microsecond =0;
}
uint16_t drv_timer1_get_mcs(void)
{
  TIM1_ITConfig(TIM1_IT_UPDATE,DISABLE);
  microsecond = TIM1_GetCounter() ;/// 4;
  TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);
  return microsecond;

}

uint16_t drv_timer1_get_ms(void)
{
  
  TIM1_ITConfig(TIM1_IT_UPDATE,DISABLE);
  uint16_t temp;
  temp = millisecond;
  TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);
  return temp;
}
