################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cpu.c \
../fifoqueue.c \
../fifoqueue_test.c \
../pcb.c \
../pcb_test.c \
../priorityqueue.c \
../priorityqueue_test.c 

OBJS += \
./cpu.o \
./fifoqueue.o \
./fifoqueue_test.o \
./pcb.o \
./pcb_test.o \
./priorityqueue.o \
./priorityqueue_test.o 

C_DEPS += \
./cpu.d \
./fifoqueue.d \
./fifoqueue_test.d \
./pcb.d \
./pcb_test.d \
./priorityqueue.d \
./priorityqueue_test.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


