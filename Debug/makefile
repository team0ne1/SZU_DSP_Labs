################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/ccs11.2/installDir/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./DSP281x_GlobalVariableDefs.obj" \
"./main.obj" \
"./demos/demo1.obj" \
"./demos/demo2.obj" \
"./demos/demo3.obj" \
"./demos/demo4.obj" \
"./demos/demo5.obj" \
"./demos/demo6.obj" \
"./demos/demo7.obj" \
"./demos/demo8.obj" \
"./helper/helper.obj" \
"./source/DSP281x_Adc.obj" \
"./source/DSP281x_CSMPasswords.obj" \
"./source/DSP281x_CodeStartBranch.obj" \
"./source/DSP281x_CpuTimers.obj" \
"./source/DSP281x_DBGIER.obj" \
"./source/DSP281x_DefaultIsr.obj" \
"./source/DSP281x_ECan.obj" \
"./source/DSP281x_Ev.obj" \
"./source/DSP281x_Gpio.obj" \
"./source/DSP281x_InitPeripherals.obj" \
"./source/DSP281x_MemCopy.obj" \
"./source/DSP281x_PieCtrl.obj" \
"./source/DSP281x_PieVect.obj" \
"./source/DSP281x_Sci.obj" \
"./source/DSP281x_Spi.obj" \
"./source/DSP281x_SysCtrl.obj" \
"./source/DSP281x_XIntrupt.obj" \
"./source/DSP281x_Xintf.obj" \
"./source/DSP281x_XintfBootReset.obj" \
"./source/DSP281x_usDelay.obj" \
"../DSP281x_Headers_nonBIOS.cmd" \
"../F2812_YHDSP_RAM_lnk.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include demos/subdir_vars.mk
-include helper/subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include demos/subdir_rules.mk
-include helper/subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
allDemo.out \

EXE_OUTPUTS__QUOTED += \
"allDemo.out" \

BIN_OUTPUTS += \
allDemo.hex \

BIN_OUTPUTS__QUOTED += \
"allDemo.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "allDemo.out"

# Tool invocations
allDemo.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"E:/ccs11.2/installDir/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/cl2000" -v28 -ml -mt -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"allDemo.map" --warn_sections -i"E:/ccs11.2/installDir/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/lib" -i"E:/ccs11.2/installDir/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="allDemo_linkInfo.xml" --rom_model -o "allDemo.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

allDemo.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: C2000 Hex Utility'
	"E:/ccs11.2/installDir/ccs/tools/compiler/ti-cgt-c2000_21.6.0.LTS/bin/hex2000" --diag_wrap=off -o "allDemo.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "DSP281x_GlobalVariableDefs.obj" "main.obj" "demos\demo1.obj" "demos\demo2.obj" "demos\demo3.obj" "demos\demo4.obj" "demos\demo5.obj" "demos\demo6.obj" "demos\demo7.obj" "demos\demo8.obj" "helper\helper.obj" "source\DSP281x_Adc.obj" "source\DSP281x_CSMPasswords.obj" "source\DSP281x_CodeStartBranch.obj" "source\DSP281x_CpuTimers.obj" "source\DSP281x_DBGIER.obj" "source\DSP281x_DefaultIsr.obj" "source\DSP281x_ECan.obj" "source\DSP281x_Ev.obj" "source\DSP281x_Gpio.obj" "source\DSP281x_InitPeripherals.obj" "source\DSP281x_MemCopy.obj" "source\DSP281x_PieCtrl.obj" "source\DSP281x_PieVect.obj" "source\DSP281x_Sci.obj" "source\DSP281x_Spi.obj" "source\DSP281x_SysCtrl.obj" "source\DSP281x_XIntrupt.obj" "source\DSP281x_Xintf.obj" "source\DSP281x_XintfBootReset.obj" "source\DSP281x_usDelay.obj" 
	-$(RM) "DSP281x_GlobalVariableDefs.d" "main.d" "demos\demo1.d" "demos\demo2.d" "demos\demo3.d" "demos\demo4.d" "demos\demo5.d" "demos\demo6.d" "demos\demo7.d" "demos\demo8.d" "helper\helper.d" "source\DSP281x_Adc.d" "source\DSP281x_CpuTimers.d" "source\DSP281x_DefaultIsr.d" "source\DSP281x_ECan.d" "source\DSP281x_Ev.d" "source\DSP281x_Gpio.d" "source\DSP281x_InitPeripherals.d" "source\DSP281x_MemCopy.d" "source\DSP281x_PieCtrl.d" "source\DSP281x_PieVect.d" "source\DSP281x_Sci.d" "source\DSP281x_Spi.d" "source\DSP281x_SysCtrl.d" "source\DSP281x_XIntrupt.d" "source\DSP281x_Xintf.d" 
	-$(RM) "source\DSP281x_CSMPasswords.d" "source\DSP281x_CodeStartBranch.d" "source\DSP281x_DBGIER.d" "source\DSP281x_XintfBootReset.d" "source\DSP281x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

