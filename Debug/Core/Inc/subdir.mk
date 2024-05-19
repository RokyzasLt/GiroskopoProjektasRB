################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Statechart.c \
../Core/Inc/mpu6050.c \
../Core/Inc/ssd1306.c \
../Core/Inc/ssd1306_fonts.c 

OBJS += \
./Core/Inc/Statechart.o \
./Core/Inc/mpu6050.o \
./Core/Inc/ssd1306.o \
./Core/Inc/ssd1306_fonts.o 

C_DEPS += \
./Core/Inc/Statechart.d \
./Core/Inc/mpu6050.d \
./Core/Inc/ssd1306.d \
./Core/Inc/ssd1306_fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/%.o Core/Inc/%.su Core/Inc/%.cyclo: ../Core/Inc/%.c Core/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L073xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Inc

clean-Core-2f-Inc:
	-$(RM) ./Core/Inc/Statechart.cyclo ./Core/Inc/Statechart.d ./Core/Inc/Statechart.o ./Core/Inc/Statechart.su ./Core/Inc/mpu6050.cyclo ./Core/Inc/mpu6050.d ./Core/Inc/mpu6050.o ./Core/Inc/mpu6050.su ./Core/Inc/ssd1306.cyclo ./Core/Inc/ssd1306.d ./Core/Inc/ssd1306.o ./Core/Inc/ssd1306.su ./Core/Inc/ssd1306_fonts.cyclo ./Core/Inc/ssd1306_fonts.d ./Core/Inc/ssd1306_fonts.o ./Core/Inc/ssd1306_fonts.su

.PHONY: clean-Core-2f-Inc

