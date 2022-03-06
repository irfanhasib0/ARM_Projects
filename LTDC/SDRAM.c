#include "SDRAM.h"
#include "stm32f4xx_hal.h"

/* #define SDRAM_MEMORY_WIDTH                    FMC_SDRAM_MEM_BUS_WIDTH_8 */
#define SDRAM_MEMORY_WIDTH                       FMC_SDRAM_MEM_BUS_WIDTH_16
/* #define SDCLOCK_PERIOD                        FMC_SDRAM_CLOCK_PERIOD_2 */
#define SDCLOCK_PERIOD                           FMC_SDRAM_CLOCK_PERIOD_3
#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)
#define REFRESH_COUNT                            ((uint32_t)0x056A)   /* SDRAM refresh counter (90MHz SDRAM clock) */

SDRAM_HandleTypeDef sdram;
FMC_SDRAM_TimingTypeDef timing;
FMC_SDRAM_CommandTypeDef command;

void SDRAM_init(void)
{
	/* Timing configuration for 90 MHz of SDRAM clock frequency (180MHz/2) */
	/* TMRD: 2 Clock cycles */
	timing.LoadToActiveDelay    = 2;
	/* TXSR: min=70ns (6x11.90ns) */
	timing.ExitSelfRefreshDelay = 7;
	/* TRAS: min=42ns (4x11.90ns) max=120k (ns) */
	timing.SelfRefreshTime      = 4;
	/* TRC:  min=63 (6x11.90ns) */
	timing.RowCycleDelay        = 7;
	/* TWR:  2 Clock cycles */
	timing.WriteRecoveryTime    = 2;
	/* TRP:  15ns => 2x11.90ns */
	timing.RPDelay              = 2;
	/* TRCD: 15ns => 2x11.90ns */
	timing.RCDDelay             = 2;

	sdram.Instance = FMC_SDRAM_DEVICE;
	sdram.Init.SDBank = FMC_SDRAM_BANK2;
	sdram.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
	sdram.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
	sdram.Init.MemoryDataWidth = SDRAM_MEMORY_WIDTH;
	sdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
	sdram.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
	sdram.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
	sdram.Init.SDClockPeriod = SDCLOCK_PERIOD;
	sdram.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
	sdram.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;

	/* initialize FMC-SDRAM controller */
	HAL_SDRAM_Init(&sdram, &timing);

	/* SDRAM initialization sequence */
	__IO uint32_t tmpmrd =0;
	/* Step 3:  Configure a clock configuration enable command */
	command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdram, &command, 0x1000);

	/* Step 4: Insert 100 ms delay */
	HAL_Delay(100);

	/* Step 5: Configure a PALL (precharge all) command */
	command.CommandMode = FMC_SDRAM_CMD_PALL;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdram, &command, 0x1000);

	/* Step 6 : Configure a Auto-Refresh command */
	command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber = 4;
	command.ModeRegisterDefinition = 0;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdram, &command, 0x1000);

	/* Step 7: Program the external memory mode register */
	tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
			SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
			SDRAM_MODEREG_CAS_LATENCY_3           |
			SDRAM_MODEREG_OPERATING_MODE_STANDARD |
			SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
	command.AutoRefreshNumber = 1;
	command.ModeRegisterDefinition = tmpmrd;

	/* Send the command */
	HAL_SDRAM_SendCommand(&sdram, &command, 0x1000);

	/* Step 8: Set the refresh rate counter */
	/* (15.62 us x Freq) - 20 */
	/* Set the device refresh counter */
	HAL_SDRAM_ProgramRefreshRate(&sdram, REFRESH_COUNT);
}
