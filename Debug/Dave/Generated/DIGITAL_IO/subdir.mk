################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dave/Generated/DIGITAL_IO/digital_io.c \
../Dave/Generated/DIGITAL_IO/digital_io_conf.c 

OBJS += \
./Dave/Generated/DIGITAL_IO/digital_io.o \
./Dave/Generated/DIGITAL_IO/digital_io_conf.o 

C_DEPS += \
./Dave/Generated/DIGITAL_IO/digital_io.d \
./Dave/Generated/DIGITAL_IO/digital_io_conf.d 


# Each subdirectory must supply rules for building sources it contributes
Dave/Generated/DIGITAL_IO/%.o: ../Dave/Generated/DIGITAL_IO/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"E:\DAVEv4\DAVE-4.1.4\eclipse\ARM-GCC-49/bin/arm-none-eabi-gcc" -DXMC4700_F144x2048 -I"D:\dholler\Dokumente\uni\bus\xmc\priotest\Libraries\XMCLib\inc" -I"D:\dholler\Dokumente\uni\bus\xmc\priotest/Libraries/CMSIS/Include" -I"D:\dholler\Dokumente\uni\bus\xmc\priotest/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"D:\dholler\Dokumente\uni\bus\xmc\priotest" -I"D:\dholler\Dokumente\uni\bus\xmc\priotest\Dave\Generated" -I"D:\dholler\Dokumente\uni\bus\xmc\priotest\Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo.

