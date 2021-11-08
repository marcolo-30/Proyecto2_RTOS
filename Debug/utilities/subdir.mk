################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_io.c \
../utilities/fsl_log.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_io.o \
./utilities/fsl_log.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_io.d \
./utilities/fsl_log.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DFSL_RTOS_FREE_RTOS -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\board" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\source" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\CMSIS" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\drivers" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\startup" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\utilities" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\amazon-freertos\FreeRTOS\portable" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\freertos\portable" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\amazon-freertos\include" -I"C:\Users\Maloa\Documents\MCUXpressoIDE_11.4.0_6224\workspace\Proyecto2\Proyecto2_RTOS\board\src" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


