################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/freertos.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_tim.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c \
../Src/usb_host.c \
../Src/usbh_conf.c \
../Src/usbh_platform.c 

OBJS += \
./Src/freertos.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_tim.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o \
./Src/usb_host.o \
./Src/usbh_conf.o \
./Src/usbh_platform.o 

C_DEPS += \
./Src/freertos.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_tim.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d \
./Src/usb_host.d \
./Src/usbh_conf.d \
./Src/usbh_platform.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_UART_DMA/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

