################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.c \
../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.c 

OBJS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.o \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.o 

C_DEPS += \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.d \
./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/%.o Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/%.su: ../Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/%.c Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -D__FPU_PRESENT -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"F:/DSP/DSP_ARM/codes/Noise_realtime/CUBEIDE/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-MatrixFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-MatrixFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_add.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_cmplx_mult.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_inverse.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_mult.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_scale.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_sub.su ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.d ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.o ./Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/MatrixFunctions/mat_trans.su

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-DSP_Lib_TestSuite-2f-RefLibs-2f-src-2f-MatrixFunctions

