/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4x7_eth.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tcpip.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/*--------------- Tasks Priority -------------*/
#define LED_TASK_PRIO    ( tskIDLE_PRIORITY + 1 )

TaskHandle_t xTask2Handle = NULL;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void ToggleGreen(void * pvParameters);
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
   STM_EVAL_LEDInit( LED1 );
#ifdef SERIAL_DEBUG
  DebugComPort_Init();
#endif

   /* Start toogleLed4 task : Toggle LED4  every 250ms */
   xTaskCreate( ToggleGreen, "LEDGreen", configMINIMAL_STACK_SIZE, NULL,
         LED_TASK_PRIO, NULL );
   xTaskCreate( vTask1, "Task1", 1000, NULL, 2, NULL );
   xTaskCreate( vTask2, "Task2", 1000, NULL, 1, &xTask2Handle );

   /* Start scheduler */
   vTaskStartScheduler();
   /* We should never get here as control is now taken by the scheduler */
   for(;;)
      ;

}

void vTask2( void *pvParameters )
{
   UBaseType_t uxPriority;

   uxPriority = uxTaskPriorityGet( NULL );

   for(;;)
   {
      printf( "Task 2 is running\r\n" );
      printf( "About to lower the Task 2 priority\r\n" );
      STM_EVAL_LEDToggle( LED1 );
      vTaskPrioritySet( NULL, (uxPriority - 2) );
   }
}

/**
 *
 */
void vTask1( void *pvParameters )
{
   UBaseType_t uxPriority;

   uxPriority = uxTaskPriorityGet( NULL );

   for(;;)
   {
      printf( "Task 1 is running\r\n" );
      printf( "About to raise the Task 2 priority\r\n" );
      vTaskPrioritySet( xTask2Handle, (uxPriority + 1) );
   }
}

/**
  * @brief  Toggle Led4 task
  * @param  pvParameters not used
  * @retval None
  */
void ToggleGreen(void * pvParameters)
{
  const TickType_t xDelay250ms = pdMS_TO_TICKS( 250 );
  for( ;; )
  {
    /* Toggle LED4 each 250ms */
    STM_EVAL_LEDToggle(LED1);
    //STM_EVAL_LEDToggle(LED2);
    //STM_EVAL_LEDToggle(LED3);
    //STM_EVAL_LEDToggle(LED4);
    vTaskDelay( xDelay250ms );
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
