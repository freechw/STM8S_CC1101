#include "drv_timer1.h"

#include "drv_CC1101.h"

uint16_t millisecond = 0;
uint16_t microsecond = 0;

void drv_timer1_init(  )  //us
{
//  TIM1_DeInit();//��λTIM1���в���  
//  TIM1_TimeBaseInit(TIM1_PRESCALER_16,TIM1_COUNTERMODE_DOWN,Timer1Time,0);  
//  //TIM1��Ԥ��Ƶ������һ����16λ�Ĵ���  
//  //ѡ��16��Ƶ 16M/16=1M  ����Ϊ1us   
//  TIM1_Cmd(ENABLE);//ʹ�ܼ�ʱ��  
//  TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);//ʹ��TIM1�ж�
  //�����ڲ�����ʱ��16MΪ��ʱ��  
  //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);  
  TIM1_DeInit();//��λTIM1���в���  
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);
  TIM1_TimeBaseInit(CLK_PRESCALER_HSIDIV1,TIM1_COUNTERMODE_UP,16000,0);  
  //TIM1��Ԥ��Ƶ������һ����16λ�Ĵ���  
  //ѡ��1��Ƶ f = 16M  ����Ϊ 1/16 us ;1ms����һ���ж�  
  drv_timer1_disable();
}

void drv_timer1_enable(void)
{
  TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);
  TIM1_Cmd(ENABLE);//ʹ�ܼ�ʱ��
  
}
void drv_timer1_disable(void)
{
  TIM1_Cmd(DISABLE);//���ܼ�ʱ��
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
