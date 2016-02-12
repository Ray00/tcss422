################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IO_x.c \
../IO_x_.c \
../cpu.c \
../discontinuities.c \
../fifoqueue.c \
../fifoqueue_test.c \
../pcb.c \
../pcb_test.c \
../priorityqueue.c \
../priorityqueue_test.c \
../stack.c \
../timer.c 

OBJS += \
./IO_x.o \
./IO_x_.o \
./cpu.o \
./discontinuities.o \
./fifoqueue.o \
./fifoqueue_test.o \
./pcb.o \
./pcb_test.o \
./priorityqueue.o \
./priorityqueue_test.o \
./stack.o \
./timer.o 

C_DEPS += \
./IO_x.d \
./IO_x_.d \
./cpu.d \
./discontinuities.d \
./fifoqueue.d \
./fifoqueue_test.d \
./pcb.d \
./pcb_test.d \
./priorityqueue.d \
./priorityqueue_test.d \
./stack.d \
./timer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


