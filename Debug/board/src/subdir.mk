################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/src/board.c \
../board/src/clock_config.c 

OBJS += \
./board/src/board.o \
./board/src/clock_config.o 

C_DEPS += \
./board/src/board.d \
./board/src/clock_config.d 


# Each subdirectory must supply rules for building sources it contributes
board/src/%.o: ../board/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\board" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\source" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\CMSIS" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\drivers" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\startup" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\utilities" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\amazon-freertos\FreeRTOS\portable" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\freertos\portable" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\amazon-freertos\include" -I"C:\Users\User\Documents\Maestria Iot\Semestre 2021-2\RTOS\Entrega2\Proyecto2_RTOS\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


