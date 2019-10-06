################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


