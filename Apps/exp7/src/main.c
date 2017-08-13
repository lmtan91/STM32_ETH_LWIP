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

static const char *pcTextForTask1 = "Task 1 is running\r\n";
volatile uint32_t ulIdleCycleCount = 0UL;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void ToggleGreen(void * pvParameters);
void vTaskFunction( void *pvParameters );
void vApplicationIdleHook( void );

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
   xTaskCreate( ToggleGreen, "LED4", configMINIMAL_STACK_SIZE, NULL,
         LED_TASK_PRIO, NULL );
   xTaskCreate( vTaskFunction, "Task1", 1000, pcTextForTask1, 1, NULL );

   /* Start scheduler */
   vTaskStartScheduler();
   /* We should never get here as control is now taken by the scheduler */
   for(;;)
      ;

}

/**
 *
 */
void vApplicationIdleHook( void )
{
   ulIdleCycleCount++;
}

/**
 *
 */
void vTaskFunction( void *pvParameters )
{
   char *pcTaskName;
   const TickType_t xDelay250ms = pdMS_TO_TICKS( 250 );

   pcTaskName = ( char* ) pvParameters;

   for (;;)
   {
      printf( "%s %d\r\n", pcTaskName, ulIdleCycleCount );
      vTaskDelay( xDelay250ms );
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
