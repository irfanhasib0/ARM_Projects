#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{

}

void HAL_MspDeInit(void)
{

}

void HAL_SPI_MspInit(SPI_HandleTypeDef *spi)
{
	if (spi->Instance == SPI5)
	{
		/* enable GPIO port F clock */
		__HAL_RCC_GPIOF_CLK_ENABLE();

		/* configure GPIO pins */
		GPIO_InitTypeDef gpio_init;
		gpio_init.Pin = GPIO_PIN_7 | GPIO_PIN_9;
		gpio_init.Mode = GPIO_MODE_AF_PP;
		gpio_init.Alternate = GPIO_AF5_SPI5;
		HAL_GPIO_Init(GPIOF,&gpio_init);

		/* enable SPI5 clock */
		__HAL_RCC_SPI5_CLK_ENABLE();
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *spi)
{
	UNUSED(spi);
	// not implemented
}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef *ltdc)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the LTDC clock */
	__HAL_RCC_LTDC_CLK_ENABLE();

	/* Enable GPIOs clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/* GPIOs Configuration */
	/*
			   +------------------------+-----------------------+----------------------------+
			   +                       LCD pins assignment                                   +
			   +------------------------+-----------------------+----------------------------+
			   |  LCD_TFT R2 <-> PC.10  |  LCD_TFT G2 <-> PA.06 |  LCD_TFT B2 <-> PD.06      |
			   |  LCD_TFT R3 <-> PB.00  |  LCD_TFT G3 <-> PG.10 |  LCD_TFT B3 <-> PG.11      |
			   |  LCD_TFT R4 <-> PA.11  |  LCD_TFT G4 <-> PB.10 |  LCD_TFT B4 <-> PG.12      |
			   |  LCD_TFT R5 <-> PA.12  |  LCD_TFT G5 <-> PB.11 |  LCD_TFT B5 <-> PA.03      |
			   |  LCD_TFT R6 <-> PB.01  |  LCD_TFT G6 <-> PC.07 |  LCD_TFT B6 <-> PB.08      |
			   |  LCD_TFT R7 <-> PG.06  |  LCD_TFT G7 <-> PD.03 |  LCD_TFT B7 <-> PB.09      |
			   -------------------------------------------------------------------------------
			            |  LCD_TFT HSYNC <-> PC.06  | LCDTFT VSYNC <->  PA.04 |
			            |  LCD_TFT CLK   <-> PG.07  | LCD_TFT DE   <->  PF.10 |
			             -----------------------------------------------------
	 */

	/* GPIOA configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Alternate= GPIO_AF14_LTDC;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* GPIOB configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIOC configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* GPIOD configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_6;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* GPIOF configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_10;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

	/* GPIOG configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_11;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* GPIOB configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStructure.Alternate= GPIO_AF9_LTDC;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* GPIOG configuration */
	GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_12;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* enable interrupts in NVIC */
//	NVIC_EnableIRQ(LTDC_IRQn);
//	NVIC_SetPriority(LTDC_IRQn,1);
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *ltdc)
{
	/* not implemented */
	UNUSED(ltdc);
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef *sdram)
{
  GPIO_InitTypeDef  GPIO_Init_Structure;

  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO clocks */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  /* Enable FMC clock */
  __HAL_RCC_FMC_CLK_ENABLE();

  /*##-2- Configure peripheral GPIO ##########################################*/
/*-- GPIOs Configuration -----------------------------------------------------*/
/*
 +-------------------+--------------------+--------------------+--------------------+
 +                       SDRAM pins assignment                                      +
 +-------------------+--------------------+--------------------+--------------------+
 | PD0  <-> FMC_D2   | PE0  <-> FMC_NBL0  | PF0  <-> FMC_A0    | PG0  <-> FMC_A10   |
 | PD1  <-> FMC_D3   | PE1  <-> FMC_NBL1  | PF1  <-> FMC_A1    | PG1  <-> FMC_A11   |
 | PD8  <-> FMC_D13  | PE7  <-> FMC_D4    | PF2  <-> FMC_A2    | PG4  <-> FMC_BA0   |
 | PD9  <-> FMC_D14  | PE8  <-> FMC_D5    | PF3  <-> FMC_A3    | PG5  <-> FMC_BA1   |
 | PD10 <-> FMC_D15  | PE9  <-> FMC_D6    | PF4  <-> FMC_A4    | PG8  <-> FMC_SDCLK |
 | PD14 <-> FMC_D0   | PE10 <-> FMC_D7    | PF5  <-> FMC_A5    | PG15 <-> FMC_NCAS  |
 | PD15 <-> FMC_D1   | PE11 <-> FMC_D8    | PF11 <-> FMC_NRAS  |--------------------+
 +-------------------| PE12 <-> FMC_D9    | PF12 <-> FMC_A6    |
                     | PE13 <-> FMC_D10   | PF13 <-> FMC_A7    |
                     | PE14 <-> FMC_D11   | PF14 <-> FMC_A8    |
                     | PE15 <-> FMC_D12   | PF15 <-> FMC_A9    |
 +-------------------+--------------------+--------------------+
 | PB5 <-> FMC_SDCKE1|
 | PB6 <-> FMC_SDNE1 |
 | PC0 <-> FMC_SDNWE |
 +-------------------+

*/

  /* Common GPIO configuration */
  GPIO_Init_Structure.Mode  = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_Init_Structure.Pull  = GPIO_NOPULL;
  GPIO_Init_Structure.Alternate = GPIO_AF12_FMC;

  /* GPIOB configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_5 | GPIO_PIN_6;
  HAL_GPIO_Init(GPIOB, &GPIO_Init_Structure);

  /* GPIOC configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOC, &GPIO_Init_Structure);

  /* GPIOD configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1  | GPIO_PIN_8 |
                            GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
                            GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* GPIOE configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_7 |
                            GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 |
                            GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
                            GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);

  /* GPIOF configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_0  | GPIO_PIN_1 | GPIO_PIN_2 |
                            GPIO_PIN_3  | GPIO_PIN_4 | GPIO_PIN_5 |
                            GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |
                            GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);

  /* GPIOG configuration */
  GPIO_Init_Structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 |
                            GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef *sdram)
{
  UNUSED(sdram);
}


