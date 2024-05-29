#Compiler and linker
CXX =C:\avr-gcc\bin\avr-g++.exe
CXXLD =C:\avr-gcc\bin\avr-g++.exe
#Converts .elf into hex
OBJ_COPY =C:\avr-gcc\bin\avr-objcopy
#To see code sections
OBJ_DUMP =C:\avr-gcc\bin\avr-objdump

#FLASH Utility
AVRDUDESS =C:\AVRDUDESS\avrdude.exe

#USB Port
USB_PORT =COM9
PORT_SPEED =57600
FLASH_MCU =m328p
PROGRAMMER =arduino

#atmega328p headers
INC_DIRS = -IC:\WinAVR\avr\include
#atmega328 library
LIB_DIRS=-LC:\avr-gcc\avr

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
	IF exist $(OBJDIR) (echo "$(OBJDIR) exists") ELSE (mkdir $(OBJDIR))

build_directory:
	IF exist $(BINDIR) (echo "$(BINDIR) exists") ELSE (mkdir $(BINDIR))


.PHONY: flash
flash: $(BINDIR)/$(TARGET_NAME).hex
	$(AVRDUDESS) -u -c $(PROGRAMMER) -p $(FLASH_MCU) -P $(USB_PORT) -b $(PORT_SPEED) -V -U flash:w:"$(BINDIR)/$(TARGET_NAME).hex":a 

.PHONY: clean
clean:
	@echo off
	IF exist $(OBJDIR) (rmdir /s /q $(OBJDIR)) ELSE (echo "$(OBJDIR) does not exist")
	IF exist $(BINDIR) (rmdir /s /q $(BINDIR)) ELSE (echo "$(BINDIR) does not exist")
	@echo on

rebuild: clean | all
