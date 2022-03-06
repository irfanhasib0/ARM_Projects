################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Components/stmpe811/stmpe811.c 

OBJS += \
./Core/Components/stmpe811/stmpe811.o 

C_DEPS += \
./Core/Components/stmpe811/stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Components/stmpe811/%.o: ../Core/Components/stmpe811/%.c Core/Components/stmpe811/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Components-2f-stmpe811

clean-Core-2f-Components-2f-stmpe811:
	-$(RM) ./Core/Components/stmpe811/stmpe811.d ./Core/Components/stmpe811/stmpe811.o

.PHONY: clean-Core-2f-Components-2f-stmpe811
