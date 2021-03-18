#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id;

typedef struct led 
{
  uint8_t l_id;
  uint8_t l_time;
}led ;

void thread(void *arg)
{
  uint8_t state = 0;
  struct led *led_on;
  led_on = arg;
  uint8_t l_id = led_on->l_id;
  
  switch (l_id)
  {
      case 1: 
        while(1)
        {
          state ^= LED1;
          LEDWrite(LED1, state);
          osDelay(led_on->l_time);
        } 
      break;
      case 2: 
        while(1)
        {
          state ^= LED2;
          LEDWrite(LED2, state);
          osDelay(led_on->l_time);
        }
      break;
      case 3: 
        while(1)
        {
          state ^= LED3;
          LEDWrite(LED3, state);
          osDelay(led_on->l_time);
        }
      break;
      case 4: 
        while(1)
        {
          state ^= LED4;
          LEDWrite(LED4, state);
          osDelay(led_on->l_time);
       }
       break;
  }    
} // thread


void main(void)
{
  LEDInit(LED2 | LED1 | LED3 | LED4); 
  osKernelInitialize();

  struct led leddy1, leddy2, leddy3, leddy4;
  
  leddy1.l_id = 1;
  leddy1.l_time = 100;
  
  leddy2.l_id = 2;
  leddy2.l_time = 200;
  
  leddy3.l_id = 3;
  leddy3.l_time = 300;
  
  leddy4.l_id = 4;
  leddy4.l_time = 400;
  
  thread1_id = osThreadNew(thread, &leddy1, NULL);
  thread1_id = osThreadNew(thread, &leddy2, NULL);
  thread1_id = osThreadNew(thread, &leddy3, NULL);
  thread1_id = osThreadNew(thread, &leddy4, NULL);


  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
