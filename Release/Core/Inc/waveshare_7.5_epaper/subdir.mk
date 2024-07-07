################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/waveshare_7.5_epaper/gdisp_lld_WAVESHARE75.c 

OBJS += \
./Core/Inc/waveshare_7.5_epaper/gdisp_lld_WAVESHARE75.o 

C_DEPS += \
./Core/Inc/waveshare_7.5_epaper/gdisp_lld_WAVESHARE75.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/waveshare_7.5_epaper/%.o Core/Inc/waveshare_7.5_epaper/%.su Core/Inc/waveshare_7.5_epaper/%.cyclo: ../Core/Inc/waveshare_7.5_epaper/%.c Core/Inc/waveshare_7.5_epaper/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/user/STM32CubeIDE/workspace_1.14.0/stm32f401_disney_countdown/lib/ugfx_2.9" -I"/Users/user/STM32CubeIDE/workspace_1.14.0/stm32f401_disney_countdown/lib/ugfx_2.9/src" -I"/Users/user/STM32CubeIDE/workspace_1.14.0/stm32f401_disney_countdown/lib/tm1638" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-waveshare_7-2e-5_epaper

clean-Core-2f-Inc-2f-waveshare_7-2e-5_epaper:
	-$(RM) ./Core/Inc/waveshare_7.5_epaper/gdisp_lld_WAVESHARE75.cyclo ./Core/Inc/waveshare_7.5_epaper/gdisp_lld_WAVESHARE75.d ./Core/Inc/waveshare_7.5_epaper/gdisp_lld_WAVESHARE75.o ./Core/Inc/waveshare_7.5_epaper/gdisp_lld_WAVESHARE75.su

.PHONY: clean-Core-2f-Inc-2f-waveshare_7-2e-5_epaper

