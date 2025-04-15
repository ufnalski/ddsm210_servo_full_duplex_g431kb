/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

//#define USE_LCD

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "crc.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ddsm210_servo.h"

#ifdef USE_LCD
#include "st7789.h"
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DRIVE_1 1
#define NUMBER_OF_DIFFERENT_MSGS 2
#define VELOCITY_REF -15.0f
#define ACCELERATION_TIME 10
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

COM_InitTypeDef BspCOMInit;

/* USER CODE BEGIN PV */
uint8_t rx_data[10];
uint8_t ddsm_data_received_flag = 0;
char lcd_line[32];
DDSM_ResponseTypeDef ddsm_response;
uint8_t msg_count = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */

#ifdef USE_LCD
	ST7789_Init();
	ST7789_BLK_On();
	ST7789_Fill_Color(WHITE);
	ST7789_DrawImage(4 + 40, 99, 232, 42,
			(uint16_t*) image_data_ufnalski_edu_pl_gta);
	ST7789_WriteString(55, 15, "DDSM210 Direct Drive", Font_11x18, BLUE, WHITE);
	ST7789_WriteString(15, 40, "Servo Motor from Waveshare", Font_11x18, BLUE,
	WHITE);
	ST7789_WriteString(120, 75, "demo by", Font_11x18, BLUE, WHITE);
#endif

  /* USER CODE END 2 */

  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
  BspCOMInit.BaudRate   = 115200;
  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
  BspCOMInit.StopBits   = COM_STOPBITS_1;
  BspCOMInit.Parity     = COM_PARITY_NONE;
  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN BSP */

	/* -- Sample board code to send message over COM1 port ---- */
	printf("Welcome to direct drive world!\r\n\r\n");

  /* USER CODE END BSP */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	DDSM_SetVelocity(DRIVE_1, VELOCITY_REF, ACCELERATION_TIME, DDSM_BRAKE_OFF);
	HAL_UART_Receive_DMA(&huart1, rx_data, DDSM_MSG_LENGTH);
	while (1)
	{

		if (ddsm_data_received_flag == 1)
		{
			ddsm_data_received_flag = 0;
			DDSM_MessageDecode(DRIVE_1, rx_data, &ddsm_response);

#ifdef USE_LCD
			sprintf(lcd_line, "Velocity:    %.1f rpm    ",
					ddsm_response.velocity);
			ST7789_WriteString(15, 155, lcd_line, Font_11x18, BLUE,
			WHITE);
#else
			printf("Velocity:    %.1f rpm\r\n", ddsm_response.velocity);
#endif
#ifdef USE_LCD
			sprintf(lcd_line, "Position:    %.0f deg    ",
					ddsm_response.position);
			ST7789_WriteString(15, 175, lcd_line, Font_11x18, BLUE,
			WHITE);
#else
			printf("Position:    %.0f deg\r\n", ddsm_response.position);
#endif
#ifdef USE_LCD
			sprintf(lcd_line, "Mileage:     %li laps    ",
					ddsm_response.mileage);
			ST7789_WriteString(15, 195, lcd_line, Font_11x18, BLUE,
			WHITE);
#else
			printf("Mileage:     %li laps\r\n", ddsm_response.mileage);
#endif
#ifdef USE_LCD
			sprintf(lcd_line, "Temperature: %d deg. C    ",
					ddsm_response.temperature);
			ST7789_WriteString(15, 215, lcd_line, Font_11x18, BLUE,
			WHITE);
#else
			printf("Temperature: %d deg. C\r\n\r\n", ddsm_response.temperature);
			HAL_Delay(200);
#endif

			msg_count = (msg_count + 1) % NUMBER_OF_DIFFERENT_MSGS;
			switch (msg_count)
			{
			case 0:
				DDSM_SetVelocity(DRIVE_1, VELOCITY_REF, ACCELERATION_TIME,
						DDSM_BRAKE_OFF);
				break;
			case 1:
				DDSM_AskForMileage(DRIVE_1);
				break;
			default:
				__NOP();
			}
			HAL_UART_Receive_DMA(&huart1, rx_data, DDSM_MSG_LENGTH);
		}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		if (DDSM_CheckCRC(rx_data) == DDSM_CRC_OK)
		{
			ddsm_data_received_flag = 1;
		}
		else
		{
			HAL_UART_Receive_DMA(&huart1, rx_data, DDSM_MSG_LENGTH);
		}
	}
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

//#define USE_LCD

/* USER CODE END Header */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
