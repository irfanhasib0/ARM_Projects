################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP_Lib/Examples/arm_sin_cos_example/ARM/arm_sin_cos_example_f32.c 

OBJS += \
./Drivers/CMSIS/DSP_Lib/Examples/arm_sin_cos_example/ARM/arm_sin_cos_example_f32.o 

C_DEPS += \
./Drivers/CMSIS/DSP_Lib/Examples/arm_sin_cos_example/ARM/arm_sin_cos_example_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP_Lib/Examples/arm_sin_cos_example/ARM/%.o: ../Drivers/CMSIS/DSP_Lib/Examples/arm_sin_cos_example/ARM/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F103xB -I"/home/irfan_hasib/Desktop/ARM_ws/blink/blinkm/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/blink/blinkm/Drivers/STM32F1xx_HAL_Driver/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/blink/blinkm/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"/home/irfan_hasib/Desktop/ARM_ws/blink/blinkm/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/irfan_hasib/Desktop/ARM_ws/blink/blinkm/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


