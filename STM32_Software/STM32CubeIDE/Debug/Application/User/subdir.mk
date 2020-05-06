################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/action_handler.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/adc.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/bitmaps.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/event_handler.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/font.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/gpio.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/i2c.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/lcd_st7565.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/main.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/rtc.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/state_machine.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/stm32f0xx_hal_msp.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/stm32f0xx_it.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/tim.c \
C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/usart.c 

OBJS += \
./Application/User/action_handler.o \
./Application/User/adc.o \
./Application/User/bitmaps.o \
./Application/User/event_handler.o \
./Application/User/font.o \
./Application/User/gpio.o \
./Application/User/i2c.o \
./Application/User/lcd_st7565.o \
./Application/User/main.o \
./Application/User/rtc.o \
./Application/User/state_machine.o \
./Application/User/stm32f0xx_hal_msp.o \
./Application/User/stm32f0xx_it.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o \
./Application/User/tim.o \
./Application/User/usart.o 

C_DEPS += \
./Application/User/action_handler.d \
./Application/User/adc.d \
./Application/User/bitmaps.d \
./Application/User/event_handler.d \
./Application/User/font.d \
./Application/User/gpio.d \
./Application/User/i2c.d \
./Application/User/lcd_st7565.d \
./Application/User/main.d \
./Application/User/rtc.d \
./Application/User/state_machine.d \
./Application/User/stm32f0xx_hal_msp.d \
./Application/User/stm32f0xx_it.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d \
./Application/User/tim.d \
./Application/User/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/action_handler.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/action_handler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/action_handler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/adc.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/adc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/bitmaps.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/bitmaps.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/bitmaps.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/event_handler.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/event_handler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/event_handler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/font.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/font.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/font.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/gpio.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/gpio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/i2c.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/lcd_st7565.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/lcd_st7565.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/lcd_st7565.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/main.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/rtc.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/rtc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/rtc.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/state_machine.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/state_machine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/state_machine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/stm32f0xx_hal_msp.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/stm32f0xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32f0xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/stm32f0xx_it.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/stm32f0xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/stm32f0xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/syscalls.o: ../Application/User/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/sysmem.o: ../Application/User/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/tim.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/tim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/usart.o: C:/Users/lukas/Documents/GitHub/ETP2_Code/STM32_Software/Core/Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F030x8 -DDEBUG -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/STM32F0xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Application/User/usart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

