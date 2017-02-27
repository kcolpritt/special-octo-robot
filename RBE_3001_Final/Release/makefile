################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
RBE_3001_Final.lss \

FLASH_IMAGE += \
RBE_3001_Final.hex \

EEPROM_IMAGE += \
RBE_3001_Final.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: RBE_3001_Final.elf secondary-outputs

# Tool invocations
RBE_3001_Final.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RBE_3001_Final.map -Wl,-u,vfprintf -lprintf_flt –lm -L"C:\Users\Kenneth\workspace\RBELib\Release" -mmcu=atmega644p -o "RBE_3001_Final.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RBE_3001_Final.lss: RBE_3001_Final.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RBE_3001_Final.elf  >"RBE_3001_Final.lss"
	@echo 'Finished building: $@'
	@echo ' '

RBE_3001_Final.hex: RBE_3001_Final.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RBE_3001_Final.elf  "RBE_3001_Final.hex"
	@echo 'Finished building: $@'
	@echo ' '

RBE_3001_Final.eep: RBE_3001_Final.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex RBE_3001_Final.elf  "RBE_3001_Final.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RBE_3001_Final.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega644p RBE_3001_Final.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RBE_3001_Final.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
