################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lcd16x2/lcd16x2.c 

OBJS += \
./lcd16x2/lcd16x2.o 

C_DEPS += \
./lcd16x2/lcd16x2.d 


# Each subdirectory must supply rules for building sources it contributes
lcd16x2/%.o: ../lcd16x2/%.c lcd16x2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/github/Converter-AC-AC/Software/inverter/app" -I"C:/github/Converter-AC-AC/Software/inverter/libs" -I"C:/github/Converter-AC-AC/Software/inverter/lcd16x2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

