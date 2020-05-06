################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/system_stm32f0xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f0xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f0xx.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/system_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/system_stm32f0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

