################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/l3gd20/l3gd20.c 

OBJS += \
./Drivers/BSP/Components/l3gd20/l3gd20.o 

C_DEPS += \
./Drivers/BSP/Components/l3gd20/l3gd20.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/l3gd20/%.o Drivers/BSP/Components/l3gd20/%.su Drivers/BSP/Components/l3gd20/%.cyclo: ../Drivers/BSP/Components/l3gd20/%.c Drivers/BSP/Components/l3gd20/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/STM32L476G-Discovery" -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/Components/l3gd20" -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/Components/Common" -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/Components/lsm303c" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-l3gd20

clean-Drivers-2f-BSP-2f-Components-2f-l3gd20:
	-$(RM) ./Drivers/BSP/Components/l3gd20/l3gd20.cyclo ./Drivers/BSP/Components/l3gd20/l3gd20.d ./Drivers/BSP/Components/l3gd20/l3gd20.o ./Drivers/BSP/Components/l3gd20/l3gd20.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-l3gd20

