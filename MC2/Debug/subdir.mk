################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app2.c \
../buzzer.c \
../dcmotor.c \
../eeprom.c \
../gpio.c \
../lcd.c \
../mc2.c \
../pwm.c \
../timer.c \
../twi.c \
../uart.c 

OBJS += \
./app2.o \
./buzzer.o \
./dcmotor.o \
./eeprom.o \
./gpio.o \
./lcd.o \
./mc2.o \
./pwm.o \
./timer.o \
./twi.o \
./uart.o 

C_DEPS += \
./app2.d \
./buzzer.d \
./dcmotor.d \
./eeprom.d \
./gpio.d \
./lcd.d \
./mc2.d \
./pwm.d \
./timer.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


