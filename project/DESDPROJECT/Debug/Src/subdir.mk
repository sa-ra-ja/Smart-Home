################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/itm.c \
../Src/led.c \
../Src/main.c \
../Src/sensors.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/ultrasonic.c 

OBJS += \
./Src/itm.o \
./Src/led.o \
./Src/main.o \
./Src/sensors.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/ultrasonic.o 

C_DEPS += \
./Src/itm.d \
./Src/led.d \
./Src/main.d \
./Src/sensors.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/itm.cyclo ./Src/itm.d ./Src/itm.o ./Src/itm.su ./Src/led.cyclo ./Src/led.d ./Src/led.o ./Src/led.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/sensors.cyclo ./Src/sensors.d ./Src/sensors.o ./Src/sensors.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f4xx.cyclo ./Src/system_stm32f4xx.d ./Src/system_stm32f4xx.o ./Src/system_stm32f4xx.su ./Src/ultrasonic.cyclo ./Src/ultrasonic.d ./Src/ultrasonic.o ./Src/ultrasonic.su

.PHONY: clean-Src

