################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
helper/%.obj: ../helper/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"E:/ccs11.2/installDir/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt --include_path="H:/Code/dsp/workspace/allDemo" --include_path="H:/Code/dsp/YH_DSP2812_CODE/DSP281x_common/include" --include_path="H:/Code/dsp/YH_DSP2812_CODE/DSP281x_headers/include" --include_path="E:/ccs11.2/installDir/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="helper/$(basename $(<F)).d_raw" --obj_directory="helper" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


