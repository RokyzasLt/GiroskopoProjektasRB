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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sc_types.h"
#include "Statechart.h"
#include "Statechart_required.h"

#include "mpu6050.h"

#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

#define PI 3.141592

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

Statechart myStateChart;
MPU6050_t MPU6050;

double Initial_Acc_X = 0, Initial_Acc_Y = 0, Initial_Acc_Z = 0;
double Acc_X[5], Acc_Y[5],Acc_Z[5];
double Average_Acc_X = 0, Average_Acc_Y = 0, Average_Acc_Z = 0;
int iteration = 0;

int ButtonPressed = 0;

double Last_Data[3];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void MX_I2C1_Init(void);
static void MX_TIM7_Init(void);
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */

  statechart_init(&myStateChart);
  statechart_enter(&myStateChart);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000000;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 2097-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 200-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */

  /* USER CODE END TIM7_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim7){
		statechart_raise_timerInterrupt(&myStateChart);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == 8192) { // PC13
		if(ButtonPressed == 0){
			ButtonPressed = 1;
		}
		else{
			char number[5] = {'\0','\0','\0','\0','\0'};

			HAL_UART_Transmit(&huart2, (uint8_t *)"X: ", sizeof("X: "), 10);
			snprintf(number, 5, "%d. ", (int)Last_Data[0]);
			HAL_UART_Transmit(&huart2, (uint8_t *)number, sizeof(number), 10);
			for(int i = 0; i < 5;i++){
				number[i] = '\0';
			}
			HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", sizeof("\r\n"), 10);

			HAL_UART_Transmit(&huart2, (uint8_t *)"Y: ", sizeof("Y: "), 10);
			snprintf(number, 5, "%d. ", (int)Last_Data[1]);
			HAL_UART_Transmit(&huart2, (uint8_t *)number, sizeof(number), 10);
			for(int i = 0; i < 5;i++){
				number[i] = '\0';
			}
			HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n", sizeof("\r\n"), 10);

			HAL_UART_Transmit(&huart2, (uint8_t *)"Z: ", sizeof("Z: "), 10);
			snprintf(number, 5, "%d. ", (int)Last_Data[2]);
			HAL_UART_Transmit(&huart2, (uint8_t *)number, sizeof(number), 10);
			for(int i = 0; i < 5;i++){
				number[i] = '\0';
			}
			HAL_UART_Transmit(&huart2, (uint8_t *)"\r\n\r\n", sizeof("\r\n\r\n"), 10);


		}
	}
}


void statechart_initialize( Statechart* handle){
	ssd1306_Init();
	while (MPU6050_Init(&hi2c1) == 1);
	while(ButtonPressed == 0); //Laukiame mygtuko paspaudimo
	// Nusistatome pradines vertes
	MPU6050_Read_All(&hi2c1, &MPU6050);
	Initial_Acc_X = MPU6050.Ax *180 / PI;
	Initial_Acc_Y = MPU6050.Ay *180 / PI;
	Initial_Acc_Z = MPU6050.Az *180 / PI;

	HAL_TIM_Base_Start_IT(&htim7);
	HAL_Delay(200);
	statechart_raise_buttonPressed(&myStateChart);
}
void statechart_readSensor( Statechart* handle){
	MPU6050_Read_All(&hi2c1, &MPU6050);
	Acc_X[iteration] = MPU6050.Ax *180 / PI;
	Acc_Y[iteration] = MPU6050.Ay *180 / PI;
	Acc_Z[iteration] = MPU6050.Az *180 / PI;
	iteration++;
	if(iteration == 5){
		iteration = 0;
	}

}
void statechart_calculateAverage( Statechart* handle){
	for(int i=0;i<5;i++){
		Average_Acc_X += Acc_X[i];
		Average_Acc_Y += Acc_Y[i];
		Average_Acc_Z += Acc_Z[i];
	}
	Average_Acc_X = (Average_Acc_X/5) - Initial_Acc_X;
	Average_Acc_Y = (Average_Acc_Y/5) - Initial_Acc_Y;
	Average_Acc_Z = (Average_Acc_Z/5) - Initial_Acc_Z;
}
void statechart_display( Statechart* handle){

	char number[5];
	int X_Coord1 = 40;
	int X_Coord2 = 60;
	int Y_Coord = 10;

	ssd1306_Fill(Black);

	ssd1306_SetCursor(X_Coord1,Y_Coord);
	ssd1306_WriteString("X: ", Font_7x10, White);
	snprintf(number,5, "%d", (int)Average_Acc_X);
	ssd1306_SetCursor(X_Coord2,Y_Coord);
	ssd1306_WriteString(number, Font_7x10, White);
	for(int i = 0; i < 5;i++){
		number[i] = '\0';
	}


	ssd1306_SetCursor(X_Coord1,Y_Coord + 15);
	ssd1306_WriteString("Y: ", Font_7x10, White);
	snprintf(number,5, "%d", (int)Average_Acc_Y);
	ssd1306_SetCursor(X_Coord2,Y_Coord + 15);
	ssd1306_WriteString(number, Font_7x10, White);
	for(int i = 0; i < 5;i++){
		number[i] = '\0';
	}


	ssd1306_SetCursor(X_Coord1,Y_Coord + 30);
	ssd1306_WriteString("Y: ", Font_7x10, White);
	snprintf(number,5, "%d", (int)Average_Acc_Z);
	ssd1306_SetCursor(X_Coord2,Y_Coord + 30);
	ssd1306_WriteString(number, Font_7x10, White);
	for(int i = 0; i < 5;i++){
		number[i] = '\0';
	}

	ssd1306_UpdateScreen();

	Last_Data[0] = Average_Acc_X;
	Last_Data[1] = Average_Acc_Y;
	Last_Data[2] = Average_Acc_Z;

	Average_Acc_X = 0;
	Average_Acc_Y = 0;
	Average_Acc_Z = 0;


}
/* USER CODE END 4 */

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
