
AVR_GCC_DIR = C:/avr-gcc
LIB_DIRS=-L$(AVR_GCC_DIR)/avr

CXX = $(AVR_GCC_DIR)/bin/avr-g++.exe
CXXLD = $(AVR_GCC_DIR)/bin/avr-g++.exe
OBJ_COPY =$(AVR_GCC_DIR)/bin/avr-objcopy.exe
OBJ_DUMP =$(AVR_GCC_DIR)/bin/avr-objdump.exe
SIZE =$(AVR_GCC_DIR)/bin/avr-size.exe
AVRDUDESS =C:/AVRDUDESS/avrdude.exe
TEXT2INTELHEX = tools/Text2IntelHex/Text2IntelHex.exe

OBJ_COPY_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature -O ihex
OBJ_DUMP_FLAG = -h -S

#USB Port
USB_PORT =COM9
PORT_SPEED =57600
FLASH_MCU =m328p
PROGRAMMER =arduino

MCU_NAME =atmega328p
MCU_CLOCK =16000000
OPTIMIZATIONS =-O0

TEXT2INTELHEX_START_ADR =0000
EEPROM_FILE_PATH_AND_NAME = EEPROM.eep

OUTPUT_DIR :=Debug
EXECUTABLE_NAME = Maker
MAP_FILE= $(OUTPUT_DIR)/$(EXECUTABLE_NAME).map

INCLUDES := \
		$(AVR_GCC_DIR)/avr/include \
		Drivers/atmega328p/Inc/ \
		Application/cmd_dispatcher/stack \
		Application/cmd_dispatcher/this_app/ \
		Application/cmd_dispatcher/this_app/Inc/

SOURCES = \
		$(wildcard Drivers/atmega328p/Src/*.cpp) \
		$(wildcard Application/cmd_dispatcher/stack/*.cpp) \
		$(wildcard Application/cmd_dispatcher/this_app/*.cpp) \
		$(wildcard Application/cmd_dispatcher/this_app/src/*.cpp) \
		main.cpp
			
C_SOURCES = $(SOURCES)

SOURCE_DIRECTORIES = $(foreach item, $(SOURCES), $(dir $(item)))
SOURCE_DIRECTORIES_UNIQ = $(eval _uniq, := $(SOURCE_DIRECTORIES))$(strip $(foreach _,$(_uniq), $(if $(filter $_, $(_uniq)),$(eval _uniq := $(filter-out $_,$(_uniq)))$)))
 
#-c stands for "only compiler, no linking"
CCFLAGS = \
		-c \
		-Wall \
		-mmcu=$(MCU_NAME) \
		$(OPTIMIZATIONS) \
		-DF_CPU=$(MCU_CLOCK) \
		-g \
		-std=gnu++11 \
		-fno-threadsafe-statics

LD_FLAGS_1 = \
		-mmcu=$(MCU_NAME) \
		-Wl,-Map=
		
LD_FLAGS_2 = ,--cref
	 
CCINCLUDES := $(addprefix -I, $(INCLUDES))

# Designed to go through sources with complete path:
# e.g. ../../../../dir/module.c
# Removes all the '../' and returns just the file basename
# consenquently appended with '.o' suffix.
# The '../' removal ensures that once the list of objects
# created out of this rule is used during GCC compiling to create an actual object file, 
# object file will be not located in other than $(OUTPUT_DIR)/ folder.
# In case of not '../' removal, object file appears exactly in the ../../../../dir/.
conv_src_to_obj = $(subst ../,, $(addsuffix .o,$(OUTPUT_DIR)/$(basename $(1))))

# Firstly gets object full path and name e.g.:
# ../../../../dir/module.c -> $(OUTPUT_DIR)/dir/module.o
# than invokes method with dependency file ../../../../dir/module.c
# and folder $(OUTPUT_DIR)/dir/. The method body calls GCC compile with
# the original .c file path ../../../../dir/module.c but .o will be in the $(OUTPUT_DIR)/dir
define C_BUILD_RULE
OBJS += $(call conv_src_to_obj, $(1))
$(call conv_src_to_obj, $(1)) : $(1) | $(dir $(call conv_src_to_obj, $(1)))
	@ $(CXX) $(CCFLAGS) $(CCINCLUDES) $$< -o $$@
	@echo building: $(1)
endef

define SUBDIR_RULE
$(1):
	@ MKDIR -p $$@
endef

define PRINT_OBJ
@echo $(1)
endef

$(foreach src,$(C_SOURCES),$(eval $(call C_BUILD_RULE, $(src))))
$(foreach outdir, $(sort $(dir $(OBJS))), $(eval $(call SUBDIR_RULE, $(dir $(outdir)))))

$(OUTPUT_DIR)/$(EXECUTABLE_NAME).elf: $(OBJS)
	$(foreach object, $(OBJS), $(info linking: $(object)))
	@ $(CXXLD) $(LIB_DIRS) -o $@ $(OBJS) $(LD_FLAGS_1)$(MAP_FILE)$(LD_FLAGS_2)
	@echo linked  as: $(EXECUTABLE_NAME).elf
	
.PHONY: build
build: $(OUTPUT_DIR)/$(EXECUTABLE_NAME).elf
	$(OBJ_DUMP) $(OBJ_DUMP_FLAG) $(OUTPUT_DIR)/$(EXECUTABLE_NAME).elf > $(OUTPUT_DIR)/$(EXECUTABLE_NAME).lss
	$(OBJ_COPY) $(OBJ_COPY_FLAGS) $(OUTPUT_DIR)/$(EXECUTABLE_NAME).elf $(OUTPUT_DIR)/$(EXECUTABLE_NAME).hex
	$(SIZE) $(OUTPUT_DIR)/$(EXECUTABLE_NAME).elf

.PHONY: clean
clean:
	rm -r $(OUTPUT_DIR)
	
.PHONY: rebuild
rebuild: force_build | build

.PHONY: force_build
force_build: 
	@ touch $(SOURCES)
	
.PHONY: flash
flash: $(OUTPUT_DIR)/$(EXECUTABLE_NAME).hex
	$(AVRDUDESS) -u -c $(PROGRAMMER) -p $(FLASH_MCU) -P $(USB_PORT) -b $(PORT_SPEED) -V -U flash:w:"$(OUTPUT_DIR)/$(EXECUTABLE_NAME).hex":a 

.PHONY: eeprom_convert
eeprom_convert: eeprom.txt
	$(TEXT2INTELHEX) eeprom.txt $(TEXT2INTELHEX_START_ADR) > eeprom.eep

.PHONY: eeprom
eeprom: $(EEPROM_FILE_PATH)
	$(AVRDUDESS) -u -c $(PROGRAMMER) -p $(FLASH_MCU) -P $(USB_PORT) -b $(PORT_SPEED) -V -U eeprom:w:"$(EEPROM_FILE_PATH_AND_NAME)":a

print-%  : ; @echo $* = $($*)

	