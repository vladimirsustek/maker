CCXX =C:\avr-gcc\bin\avr-g++.exe
OBJ_COPY =C:\avr-gcc\bin\avr-objcopy
OBJ_DUMP =C:\avr-gcc\bin\avr-objdump

INC_DIRS = -IC:\WinAVR\avr\include
LIB_DIRS=-LC:\avr-gcc\avr

OBJ_COPY_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature -O ihex
OBJ_DUMP_FLAG = -h -S

MCU_NAME =atmega328p
MCU_CLOCK =16000000
OPTIMIZATIONS =-O0

CFLAGS=-c -Wall -mmcu=$(MCU_NAME) $(OPTIMIZATIONS) -DF_CPU=$(MCU_CLOCK) -g
LD_FLAGS_1 =-mmcu=$(MCU_NAME) -Wl,-Map=
LD_FLAGS_2 = ,--cref

OBJDIR =obj
BINDIR =bin
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

TARGET_NAME=Maker
EXECUTABLE=bin/$(TARGET_NAME).elf
MAP_FILE=bin/$(TARGET_NAME).map

.PHONY: all
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | build_directory
	$(CCXX) $(LIB_DIRS) -o $@ $(OBJECTS) $(LD_FLAGS_1)$(MAP_FILE)$(LD_FLAGS_2)
	$(OBJ_DUMP) $(OBJ_DUMP_FLAG) $(EXECUTABLE) > $(BINDIR)/$(TARGET_NAME).lss
	$(OBJ_COPY) $(OBJ_COPY_FLAGS) $(EXECUTABLE) $(BINDIR)/$(TARGET_NAME).hex

$(OBJECTS): $(OBJDIR)/%.o: %.cpp | object_directory
	$(CCXX) $(CFLAGS) $(INC_DIRS) $< -o $@

object_directory:
	mkdir $(OBJDIR)

build_directory:
	mkdir $(BINDIR)

.PHONY: clean
clean: 
	del obj -Recurse -Force
	del bin -Recurse -Force

