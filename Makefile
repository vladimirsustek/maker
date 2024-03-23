CC=C:\avr-gcc\bin\avr-g++.exe

CFLAGS=-c -Wall -mmcu=atmega328p -O2 -DF_CPU=16000000UL -g
INC_DIRS = -IC:\WinAVR\avr\include
LIB_DIRS=-LC:\avr-gcc\avr
LDFLAGS=-mmcu=atmega328p -Wl,-Map=
LDFLAGS2=,--cref
SOURCES=main.cpp function.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET_NAME=Maker
EXECUTABLE=$(TARGET_NAME).elf
MAP_FILE=$(TARGET_NAME).map
OBJ_COPY=C:\avr-gcc\bin\avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex
OBJ_DUMP=C:\avr-gcc\bin\avr-objdump -h -S $(EXECUTABLE) > $(TARGET_NAME).lss
all: $(SOURCES) $(EXECUTABLE)


#cmd /c "avr-objdump -h -S bin\Debug\rda5807m_radio.elf > bin\Debug\rda5807m_radio.lss"
#avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex bin\Debug\rda5807m_radio.elf bin\Debug\rda5807m_radio.hex
#avr-objcopy --no-change-warnings -j .eeprom --change-section-lma .eeprom=0 -O ihex bin\Debug\rda5807m_radio.elf bin\Debug\rda5807m_radio.eep


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LIB_DIRS) -o $@ $(OBJECTS) $(LDFLAGS)$(MAP_FILE)$(LDFLAGS2)
	$(OBJ_DUMP)
	$(OBJ_COPY) $(EXECUTABLE) $(TARGET_NAME).hex

.cpp.o:
	$(CC) $(CFLAGS) $(INC_DIRS) $< -o $@

clean:
	rm -rf *.o
