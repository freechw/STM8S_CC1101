#include "drv_exint.h"
#include "drv_timer1.h"
#include "main.h"
#include "drv_CC1101.h"
extern uint8_t read;
extern uint8_t write;


extern uint16_t RXtimer_begin;
extern uint16_t RXtimer_end;

extern uint16_t TXtimer_begin;
extern uint16_t TXtimer_end;


/*
////TX
#define CC1101_GDO0_GPIO_PORT			GPIOB
#define CC1101_GDO0_GPIO_PIN			GPIO_PIN_4
///RX
#define CC1101_GDO2_GPIO_PORT			GPIOC
#define CC1101_GDO2_GPIO_PIN			GPIO_PIN_3
*/
void drv_init_exint_GOD0(void)
{
  EXTI_DeInit();
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB ,EXTI_SENSITIVITY_RISE_ONLY);
  /*
  *EXTI Sensitivity values for PORTA to PORTE
  *EXTI_SENSITIVITY_FALL_LOW     Interrupt on Falling edge and Low level
  *EXTI_SENSITIVITY_RISE_ONLY    Interrupt on Rising edge only
  *EXTI_SENSITIVITY_FALL_ONLY    Interrupt on Falling edge only
  *EXTI_SENSITIVITY_RISE_FALL    Interrupt on Rising and Falling edges
  */
  //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_RISE_ONLY);
  /*
  *EXTI Sensitivity values for TLI
  *EXTI_TLISENSITIVITY_FALL_ONLY         Top Level Interrupt on Falling edge only
  *EXTI_TLISENSITIVITY_RISE_ONLY         Top Level Interrupt on Rising edge only
*/
}

void drv_GOD0_handler(void)
{
  disableInterrupts();
  //TXtimer_end = drv_timer1_get_ms();
//  if(TXtimer_end - TXtimer_begin < 1)
//  {
//    enableInterrupts();
//    return;
//  }
//  uint16_t mcs = drv_timer1_get_mcs();
//  uint8_t temp[4];
//  temp[0] = (TXtimer_end - TXtimer_begin) >> 8;
//  temp[1] = (TXtimer_end - TXtimer_begin) & 0x00ff;
//  temp[2] = mcs >> 8;
//  temp[3] = mcs & 0x00ff;
//  drv_uart_tx_bytes(temp ,4);
  write = 1;
  enableInterrupts();
}




/****************************************************************************************/

void drv_init_exint_GOD2(void)
{
  //GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_PIN_3, GPIO_MODE_IN_FL_IT);
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
  //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
  /*
  *EXTI Sensitivity values for TLI
  *EXTI_TLISENSITIVITY_FALL_ONLY         Top Level Interrupt on Falling edge only
  *EXTI_TLISENSITIVITY_RISE_ONLY         Top Level Interrupt on Rising edge only
  */
}



void drv_GOD2_handler(void)
{
  //drv_delay_ms(1000);
  //drv_timer1_disable();
  disableInterrupts();
  RXtimer_end = drv_timer1_get_ms();
//  uint16_t mcs = drv_timer1_get_mcs();
//  uint8_t temp[4];
//  temp[0] = (RXtimer_end - RXtimer_begin) >> 8;
//  temp[1] = (RXtimer_end - RXtimer_begin) & 0x00ff;
//  temp[2] = mcs >> 8;
//  temp[3] = mcs & 0x00ff;
//  drv_uart_tx_bytes(temp ,4);
  read=1;

  //enableInterrupts();
  
}
