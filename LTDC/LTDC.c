#include "stm32f4xx_hal.h"
#include "LTDC.h"
#include "SDRAM.h"
#include "ILI9341.h"
#include "rome.h"
#include "greetings.h"

/* double buffering (RGB888 frame buffer) */
#define FRAMEBUFFER_SIZE                              (DISPLAY_WIDTH * DISPLAY_HEIGHT * BPP)
#define FRAMEBUFFER1_ADDR                             (SDRAM_ADDR)                      // frame buffer 1 address (external RAM)
#define FRAMEBUFFER2_ADDR                             (SDRAM_ADDR + FRAMEBUFFER_SIZE)   // frame buffer 2 address (external RAM)

enum framebuffer
{
	FRAMEBUFFER1,FRAMEBUFFER2
};

static LTDC_HandleTypeDef ltdc;
static enum framebuffer active = FRAMEBUFFER1;

void LTDC_init(void)
{
	/* initialize SDRAM */
	SDRAM_init();

	/* fill framebuffers with black */
	for (int i = 0 ; i < DISPLAY_WIDTH * DISPLAY_HEIGHT * 3 ; i++)
		((volatile uint8_t*)FRAMEBUFFER1_ADDR)[i] = 0x00;
	for (int i = 0 ; i < DISPLAY_WIDTH * DISPLAY_HEIGHT * 3 ; i++)
			((volatile uint8_t*)FRAMEBUFFER2_ADDR)[i] = 0x00;

	/* initialize LTDC */
	HAL_LTDC_MspInit(&ltdc);

	LTDC->GCR &= ~(LTDC_GCR_HSPOL | LTDC_GCR_VSPOL | LTDC_GCR_DEPOL | LTDC_GCR_PCPOL);  // signal polarities
	LTDC->SSCR = 9 << LTDC_SSCR_HSW_Pos | 1 << LTDC_SSCR_VSH_Pos;                       // HSYNC and VSYNC length
	LTDC->BPCR = 29 << LTDC_BPCR_AHBP_Pos | 3 << LTDC_BPCR_AVBP_Pos;            // horizontal and vertical accumulated back porch
	LTDC->AWCR = 269 << LTDC_AWCR_AAW_Pos | 323 << LTDC_AWCR_AAH_Pos;      // accumulated active width and height
	LTDC->TWCR = 279 << LTDC_TWCR_TOTALW_Pos | 327 << LTDC_TWCR_TOTALH_Pos;     // accumulated total width and height
	LTDC->BCCR = 0x00 << LTDC_BCCR_BCRED_Pos | 0xFF << LTDC_BCCR_BCGREEN_Pos | 0x00 << LTDC_BCCR_BCBLUE_Pos;  // background color

	/* configure layer 1 */
	LTDC_Layer1->WHPCR = 269 << LTDC_LxWHPCR_WHSPPOS_Pos | 30 << LTDC_LxWHPCR_WHSTPOS_Pos;  // window horizontal start/stop positions
	LTDC_Layer1->WVPCR = 323 << LTDC_LxWVPCR_WVSPPOS_Pos | 4 << LTDC_LxWVPCR_WVSTPOS_Pos;  // window vertical start/stop positions
	LTDC_Layer1->PFCR = 0x01;   // RGB888 pixel format
	LTDC_Layer1->DCCR = 0xFF << LTDC_LxDCCR_DCALPHA_Pos | 0xFF << LTDC_LxDCCR_DCGREEN_Pos;   // layer default color
	LTDC_Layer1->CFBAR = (uint32_t)rome;                                            // frame buffer start address
	LTDC_Layer1->CFBLR = 240 * 3 << LTDC_LxCFBLR_CFBP_Pos | 240 * 3 + 3 << LTDC_LxCFBLR_CFBLL_Pos;  // frame buffer line length and pitch
	LTDC_Layer1->CFBLNR = 320;         // frame buffer line number
	LTDC_Layer1->CACR = 255;           // constant alpha
	LTDC_Layer1->CR |= LTDC_LxCR_LEN;  // enable Layer1

	/* configure layer 2 */
	LTDC_Layer2->WHPCR = 139 + 20 << LTDC_LxWHPCR_WHSPPOS_Pos | 30 + 20 << LTDC_LxWHPCR_WHSTPOS_Pos;  // window horizontal start/stop positions
	LTDC_Layer2->WVPCR = 113 + 200 << LTDC_LxWVPCR_WVSPPOS_Pos | 4 + 200 << LTDC_LxWVPCR_WVSTPOS_Pos;  // window vertical start/stop positions
	LTDC_Layer2->PFCR = 0x00;   // ARGB8888 pixel format
	LTDC_Layer2->DCCR = 0x00 << LTDC_LxDCCR_DCALPHA_Pos;   // layer default color (transparent black)
	LTDC_Layer2->CFBAR = (uint32_t)greetings;                                            // frame buffer start address
	LTDC_Layer2->CFBLR = 110 * 4 << LTDC_LxCFBLR_CFBP_Pos | 110 * 4 + 3 << LTDC_LxCFBLR_CFBLL_Pos;  // frame buffer line length and pitch
	LTDC_Layer2->CFBLNR = 110;         // frame buffer line number
	LTDC_Layer2->CACR = 255;           // constant alpha
	LTDC_Layer2->CR |= LTDC_LxCR_LEN;  // enable Layer2

	LTDC->SRCR = LTDC_SRCR_IMR;     // immediate shadow registers reload

	LTDC->GCR |= LTDC_GCR_LTDCEN;   // enable LTDC

	/* initialize LTDC with HAL driver */
//	ltdc.Instance = LTDC;
//	ltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
//	ltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
//	ltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;   // inverted with respect to the datasheet
//	ltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
//	ltdc.Init.Backcolor.Red = 0x00;
//	ltdc.Init.Backcolor.Green = 0x00;
//	ltdc.Init.Backcolor.Blue = 0x00;
//	ltdc.Init.HorizontalSync = 9;
//	ltdc.Init.AccumulatedHBP = 29;
//	ltdc.Init.AccumulatedActiveW = 269;
//	ltdc.Init.TotalWidth = 279;
//	ltdc.Init.VerticalSync = 1;
//	ltdc.Init.AccumulatedVBP = 3;
//	ltdc.Init.AccumulatedActiveH = 323;
//	ltdc.Init.TotalHeigh = 327;

	/*
	 * initialize LTDC before initializing layers!
	 * HAL_LTDC_ConfigLayer() uses LTDC register initialized here
	 */
//	HAL_LTDC_Init(&ltdc);  // calls HAL_LTDC_MspInit()

	/* configure and enable layer 1 */
//	LTDC_LayerCfgTypeDef layer1;
//	layer1.Backcolor.Red = 0x00;
//	layer1.Backcolor.Green = 0x00;
//	layer1.Backcolor.Blue = 0x00;
//	layer1.WindowX0 = 0;
//	layer1.WindowX1 = 240;
//	layer1.WindowY0 = 0;
//	layer1.WindowY1 = 320;
//	layer1.Alpha = 255;
//	layer1.ImageWidth = 240;
//	layer1.ImageHeight = 320;
//	layer1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
//	layer1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
//	layer1.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
//	layer1.FBStartAdress = (uint32_t)FRAMEBUFFER1_ADDR;
//	active = FRAMEBUFFER1;  // frame buffer 1 is the front buffer
//	HAL_LTDC_ConfigLayer(&ltdc,&layer1,LTDC_LAYER_1);

	/* configure and enable layer 2 */
//	LTDC_LayerCfgTypeDef layer2;
//	layer2.Backcolor.Red = 0x00;
//	layer2.Backcolor.Green = 0x00;
//	layer2.Backcolor.Blue = 0x00;
//	layer2.WindowX0 = 50;
//	layer2.WindowX1 = 150;
//	layer2.WindowY0 = 20;
//	layer2.WindowY1 = 220;
//	layer2.Alpha = 255;
//	layer2.ImageWidth = 100;
//	layer2.ImageHeight = 100;
//	layer2.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
//	layer2.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
//	layer2.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
//	layer2.FBStartAdress = (uint32_t)image;
//	HAL_LTDC_ConfigLayer(&ltdc,&layer2,LTDC_LAYER_2);

	/* enable LTDC interrupts */

	/* enable register reload interrupt */
//	__HAL_LTDC_ENABLE_IT(&ltdc, LTDC_IT_RR);

	/* enable line interrupt */
//	int last_line = (LTDC->AWCR & 0x7FF) + 1;
//	LTDC->LIPCR = last_line;     // interrupt on last display line
//	__HAL_LTDC_ENABLE_IT(&ltdc, LTDC_IT_LI);
}

void LTDC_switch_framebuffer(void)
{
	if (active == FRAMEBUFFER1)
	{
		LTDC_Layer1->CFBAR = FRAMEBUFFER2_ADDR;
		active = FRAMEBUFFER2;
	}
	else
	{
		LTDC_Layer1->CFBAR = FRAMEBUFFER1_ADDR;
		active = FRAMEBUFFER1;
	}
	LTDC->SRCR = LTDC_SRCR_VBR;
	while ((LTDC->CDSR & LTDC_CDSR_VSYNCS) == 0)
		;
}

volatile uint8_t *LTDC_get_backbuffer_address(void)
{
	if (active == FRAMEBUFFER1)
		return (volatile uint8_t*)FRAMEBUFFER2_ADDR;
	else
		return (volatile uint8_t*)FRAMEBUFFER1_ADDR;
}
