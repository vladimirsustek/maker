
AVR_GCC_DIR = C:\avr-gcc
#AVR_GCC_DIR = home/vlasus/avr-gcc

print-%  : ; @echo $* = $($*)

#OS equal to 'Windows_NT' for Windows machines
ifdef OS
CXX = $(AVR_GCC_DIR)\bin\avr-g++.exe
CXXLD = $(AVR_GCC_DIR)\bin\avr-g++.exe
OBJ_COPY =$(AVR_GCC_DIR)\bin\avr-objcopy.exe
OBJ_DUMP =$(AVR_GCC_DIR)\bin\avr-objdump.exe
INC_DIRS = -I$(AVR_GCC_DIR)\avr\include
LIB_DIRS=-L$(AVR_GCC_DIR)\avr
AVRDUDESS =C:\AVRDUDESS\avrdude.exe
else
CXX = $(AVR_GCC_DIR)\bin\avr-g++
CXXLD = $(AVR_GCC_DIR)\bin\avr-g++
OBJ_COPY =$(AVR_GCC_DIR)\bin\avr-objcopy
OBJ_DUMP =$(AVR_GCC_DIR)\bin\avr-objdump
AVRDUDESS =C:\AVRDUDESS\avrdude.exe
INC_DIRS = -I$(AVR_GCC_DIR)\avr\include
LIB_DIRS=-L$(AVR_GCC_DIR)\avr
endif

#USB Port
USB_PORT =COM9
PORT_SPEED =57600
FLASH_MCU =m328p
PROGRAMMER =arduino



OBJ_COPY_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature -O ihex
OBJ_DUMP_FLAG = -h -S

MCU_NAME =atmega328p
MCU_CLOCK =16000000
OPTIMIZATIONS =-O0

#-c stands for "only compiler, no linking"
CFLAGS=-c -Wall -mmcu=$(MCU_NAME) $(OPTIMIZATIONS) -DF_CPU=$(MCU_CLOCK) -g
LD_FLAGS_1 =-mmcu=$(MCU_NAME) -Wl,-Map=
LD_FLAGS_2 = ,--cref

OBJDIR =obj
BINDIR =bin

# := means the assigment is executed only once (not again)
# ?= means that assigment is executed when not yet assigned, so
MCU_NAME ?=this_will_not_cause_error
# MCU_NAME =this_will_cause_error

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))
INC_DIRS += -I$(CURDIR)

TARGET_NAME=Maker
EXECUTABLE=bin/$(TARGET_NAME).elf
MAP_FILE=bin/$(TARGET_NAME).map

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

# '| build_directory' means that build_directory is called before 
# "EXECUTABLES" is created (MUST BE).
$(EXECUTABLE): $(OBJECTS) | build_directory
	$(CXXLD) $(LIB_DIRS) -o $@ $(OBJECTS) $(LD_FLAGS_1)$(MAP_FILE)$(LD_FLAGS_2)
	$(OBJ_DUMP) $(OBJ_DUMP_FLAG) $(EXECUTABLE) > $(BINDIR)/$(TARGET_NAME).lss
	$(OBJ_COPY) $(OBJ_COPY_FLAGS) $(EXECUTABLE) $(BINDIR)/$(TARGET_NAME).hex


# A pattern, how to create .o file(s) in the OBJDIR.
# The '%' is a wildcard -> so it says for anny .cpp make an .o
# The '| object_directory' says, that the method is called before building.
$(OBJECTS): $(OBJDIR)/%.o: %.cpp | object_directory
# $< automatic variable representing prerequisite (source file) => %.cpp.
# $@ automatic variable representing object file => %.o
	$(CXX) $(CFLAGS) $(INC_DIRS) $< -o $@

object_directory:
ifdef OS
	IF exist $(OBJDIR) (echo "$(OBJDIR) exists") ELSE (mkdir $(OBJDIR))
else
#if [! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); else echo "$(OBJDIR)" exists; fi
endif

build_directory:
ifdef OS
	IF exist $(BINDIR) (echo "$(BINDIR) exists") ELSE (mkdir $(BINDIR))
else
#if [! -d "$(BINDIR)" ]; then mkdir $(BINDIR); else echo "$(BINDIR)" exists; fi
endif

.PHONY: flash
flash: $(BINDIR)/$(TARGET_NAME).hex
	$(AVRDUDESS) -u -c $(PROGRAMMER) -p $(FLASH_MCU) -P $(USB_PORT) -b $(PORT_SPEED) -V -U flash:w:"$(BINDIR)/$(TARGET_NAME).hex":a 

.PHONY: clean
clean:
ifdef OS
	@echo off
	IF exist $(OBJDIR) (rmdir /s /q $(OBJDIR)) ELSE (echo "$(OBJDIR) does not exist")
	IF exist $(BINDIR) (rmdir /s /q $(BINDIR)) ELSE (echo "$(BINDIR) does not exist")
	@echo on
else
	@if [-d "$(OBJDIR)" ]; then rm -r $(OBJDIR); else echo "$(OBJDIR) does not exists"; fi
	@if [-d "$(BINDIR)" ]; then rm -r $(BINDIR); else echo "$(BINDIR) does not exists"; fi
endif

rebuild: clean | all
