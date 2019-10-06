################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/TransformFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/SupportFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/StatisticsFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/MatrixFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/FilteringFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/FastMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/ControllerFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/ComplexMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/CommonTables/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Source/BasicMathFunctions/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_variance_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_sin_cos_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_signal_converge_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_matrix_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_linear_interp_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_graphic_equalizer_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_fir_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/GCC/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_fft_bin_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/GCC/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_dotproduct_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_convolution_example/GCC/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_convolution_example/ARM/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/subdir.mk
-include Drivers/CMSIS/DSP_Lib/Examples/arm_class_marks_example/ARM/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: blinkm.elf

# Tool invocations
blinkm.elf: $(OBJS) $(USER_OBJS) ../STM32F103C8Tx_FLASH.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -specs=nosys.specs -specs=nano.specs -T"../STM32F103C8Tx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "blinkm.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating hex and Printing size information:'
	arm-none-eabi-objcopy -O ihex "blinkm.elf" "blinkm.hex"
	arm-none-eabi-size "blinkm.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
