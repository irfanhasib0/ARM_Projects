################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Inc/ros_lib/duration.cpp \
../Inc/ros_lib/time.cpp 

OBJS += \
./Inc/ros_lib/duration.o \
./Inc/ros_lib/time.o 

CPP_DEPS += \
./Inc/ros_lib/duration.d \
./Inc/ros_lib/time.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/ros_lib/%.o: ../Inc/ros_lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU G++ Compiler'
	@echo $(PWD)
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/irfan_hasib/Desktop/ARM_ws/Disco/DISC_TFT_ROS/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fno-exceptions -fno-rtti -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


