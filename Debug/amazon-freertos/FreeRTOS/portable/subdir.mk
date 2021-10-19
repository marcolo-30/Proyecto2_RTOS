################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/FreeRTOS/portable/heap_4.c \
../amazon-freertos/FreeRTOS/portable/port.c 

OBJS += \
./amazon-freertos/FreeRTOS/portable/heap_4.o \
./amazon-freertos/FreeRTOS/portable/port.o 

C_DEPS += \
./amazon-freertos/FreeRTOS/portable/heap_4.d \
./amazon-freertos/FreeRTOS/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/FreeRTOS/portable/%.o: ../amazon-freertos/FreeRTOS/portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\board" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\source" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\CMSIS" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\drivers" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\startup" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\utilities" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\freertos\portable" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\amazon-freertos\include" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\proyect2_freertos_hello\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


