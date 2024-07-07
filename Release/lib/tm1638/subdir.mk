################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/tm1638/TM1638QYF.c 

OBJS += \
./lib/tm1638/TM1638QYF.o 

C_DEPS += \
./lib/tm1638/TM1638QYF.d 


# Each subdirectory must supply rules for building sources it contributes
lib/tm1638/%.o lib/tm1638/%.su lib/tm1638/%.cyclo: ../lib/tm1638/%.c lib/tm1638/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/user/STM32CubeIDE/workspace_1.14.0/stm32f401_disney_countdown/lib/ugfx_2.9" -I"/Users/user/STM32CubeIDE/workspace_1.14.0/stm32f401_disney_countdown/lib/ugfx_2.9/src" -I"/Users/user/STM32CubeIDE/workspace_1.14.0/stm32f401_disney_countdown/lib/tm1638" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-tm1638

clean-lib-2f-tm1638:
	-$(RM) ./lib/tm1638/TM1638QYF.cyclo ./lib/tm1638/TM1638QYF.d ./lib/tm1638/TM1638QYF.o ./lib/tm1638/TM1638QYF.su

.PHONY: clean-lib-2f-tm1638

