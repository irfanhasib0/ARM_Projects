#include "stm32f4xx_hal.h"
#include "LTDC.h"
#include "ILI9341.h"

void system_clock_config(void);

#define SIZE                 110
#define DISPLAY_WIDTH        240
#define DISPLAY_HEIGHT       320
#define ACTIVE_AREA_START_X   30
#define ACTIVE_AREA_START_Y    4

int main(void)
{
	HAL_Init();
	system_clock_config();
	ILI9341_init();
	LTDC_init();

	double x_offset = 10;
	double y_offset = 10;
	double vx = 0.1;
	double vy = 0.1;

	for(;;)
	{
		if (x_offset <= 0 || x_offset + SIZE >= DISPLAY_WIDTH)
			vx = -vx;
		if (y_offset <= 0 || y_offset + SIZE >= DISPLAY_HEIGHT)
			vy = -vy;
		x_offset += vx;
		y_offset += vy;
		LTDC_Layer2->WHPCR = ACTIVE_AREA_START_X + SIZE + (int)x_offset - 1<< LTDC_LxWHPCR_WHSPPOS_Pos | ACTIVE_AREA_START_X + (int)x_offset << LTDC_LxWHPCR_WHSTPOS_Pos;
		LTDC_Layer2->WVPCR = ACTIVE_AREA_START_Y + SIZE + (int)y_offset - 1<< LTDC_LxWVPCR_WVSPPOS_Pos | ACTIVE_AREA_START_Y + (int)y_offset << LTDC_LxWVPCR_WVSTPOS_Pos;
		LTDC->SRCR = LTDC_SRCR_VBR;                      // reload shadow registers on vertical blanking period
		while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)     // wait for next frame
			;
		while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 1)
			;
	}
}

void system_clock_config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /**Activate the Over-Drive mode
    */
  HAL_PWREx_EnableOverDrive();

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 60;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
}



