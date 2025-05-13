################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Backup/accelerometer.c \
../Core/Src/Backup/gyroscope.c 

OBJS += \
./Core/Src/Backup/accelerometer.o \
./Core/Src/Backup/gyroscope.o 

C_DEPS += \
./Core/Src/Backup/accelerometer.d \
./Core/Src/Backup/gyroscope.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Backup/%.o Core/Src/Backup/%.su Core/Src/Backup/%.cyclo: ../Core/Src/Backup/%.c Core/Src/Backup/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/STM32L476G-Discovery" -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/Components/l3gd20" -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/Components/Common" -I"C:/Users/bzdun/OneDrive/Dokumenter/Qt/pong/prj/STM/Drivers/BSP/Components/lsm303c" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Backup

clean-Core-2f-Src-2f-Backup:
	-$(RM) ./Core/Src/Backup/accelerometer.cyclo ./Core/Src/Backup/accelerometer.d ./Core/Src/Backup/accelerometer.o ./Core/Src/Backup/accelerometer.su ./Core/Src/Backup/gyroscope.cyclo ./Core/Src/Backup/gyroscope.d ./Core/Src/Backup/gyroscope.o ./Core/Src/Backup/gyroscope.su

.PHONY: clean-Core-2f-Src-2f-Backup

