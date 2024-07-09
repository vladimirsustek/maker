#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"
#include "gpio.hpp"
#include "tone.hpp"
#include "core.hpp"
#include "eeprom.hpp"


extern "C"
{
#include <avr/io.h>
//#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

#include "cmd_dispatcher.hpp"

class InnerDependency
{
public: 
    void ChangeVar(int var) {_var = var;};
    int GetVar(void) {return _var;};
    static InnerDependency* getInstance()
    {
        if (instance == nullptr)
        {
            static InnerDependency newInstance = InnerDependency();
            instance = &newInstance;
            
        }
        return instance;
    }
private:
    int _var;
    static InnerDependency *instance;
    InnerDependency() {_var = 0;};
};

InnerDependency* InnerDependency::instance = nullptr;

class Singleton
{
private:
    static Singleton *instance;
    InnerDependency *_innerDependency;
    Singleton(InnerDependency *innerDependency) {_innerDependency = innerDependency;};
public:
    static Singleton* getInstance(InnerDependency* innerDependency)
    {
        if (instance == nullptr)
        {
            static Singleton newInstance = Singleton(innerDependency);
            instance = &newInstance;
            
        }
        return instance;
    }
    void ChangeVar(int var) {_innerDependency->ChangeVar(var);};
    int GetVar(void) { return _innerDependency->GetVar();};

};

Singleton* Singleton::instance = nullptr;

template <typename T> T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

int main(void)
{

    uint32_t demoNumber = 0;

    /* Initialize 57600baud Uart */
    Uart uart = Uart(true);
    /* After this you might call printf() as you are used to */
    UartPrintf stdPrintf = UartPrintf(uart);

    InnerDependency* pInnerDependency = InnerDependency::getInstance();

    Singleton* singleton1 = Singleton::getInstance(pInnerDependency);
    Singleton* singleton2 = Singleton::getInstance(pInnerDependency);
    Singleton* singleton3 = Singleton::getInstance(pInnerDependency);
    Singleton* singleton4 = Singleton::getInstance(pInnerDependency);

    printf("Addres is: %p\n", singleton1);
    printf("Addres is: %p\n", singleton2);
    printf("Addres is: %p\n", singleton3);
    printf("Addres is: %p\n", singleton4);
    
    printf("Value is is: %d\n", singleton1->GetVar());
    singleton1->ChangeVar(999);
    printf("Value is is: %d\n", singleton1->GetVar());

    printf("myMax %d\n", myMax<int>(3,7));

    /* 1kHz timer used for msDelay*/
    Tim tim = Tim();
    Tone tone = Tone(tim);

    EEPROM eeprom = EEPROM();

    Gpio gpioPB5 = Gpio(GPIO::GpioPort::IO_PORTB, GPIO::GpioPin::Pin5, GPIO::GpioDirection::Output);
    Gpio gpioPC4 = Gpio(GPIO::GpioPort::IO_PORTC, GPIO::GpioPin::Pin4, GPIO::GpioDirection::Output);
    gpioPC4.set(true);

    /* All Simple-MCU-might-use C++ casts showed */
    uart.write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));
    /* Enable all interrupts within Atmega328p*/
    Core::enableInterrupts();

    /* Show up, the printf-UART redirection works */
    printf("The number of the beast is %ld\n", demoNumber++);

    //uint8_t array[64] = "Juch Hody v Zelesicich!\n";
    uint8_t readback[51] = {0};
    //uint16_t length = static_cast<uint16_t>(strlen(reinterpret_cast<char*>(array)));

    //eeprom.write(0, array, length);
    eeprom.read(0u, readback, 50);

    //printf("Readback: %s", const_cast<const char*>(reinterpret_cast<char*>(readback)));

    /* Hvezdy jsou jak sedmikrasky */
    tone.playTone(Note::F_6, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);
#if 0
    tone.playTone(Note::DisEb_7, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);

    tone.playTone(Note::E_7, Duration::Quarter);
    tone.playTone(Note::DisEb_7, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);

    /* nad Brnem */
    tone.playTone(Note::GisAb_6, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);
    tone.playTone(Note::F_6, Duration::Half);
    tone.playTone(Note::F_6, Duration::Half);
    tone.playTone(Note::None, Duration::Half);

    /* noc, muj mily */
    tone.playTone(Note::E_6, Duration::Quarter);
    tone.playTone(Note::FisGb_6, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);

    /* dobrou */
    tone.playTone(Note::CisDb_7, Duration::Half);
    tone.playTone(Note::DisEb_7, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);

    /* noc */
    tone.playTone(Note::CisDb_7, Duration::Full);
    tone.playTone(Note::CisDb_7, Duration::Half);

    /* -pomlka- */
    tone.playTone(Note::CisDb_7, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);
#endif

    uint8_t buffer[64];
    uint16_t length;
    
    Peripherals peripherals =Peripherals();
    peripherals.tone = &tone;

    CommandDispatcher dispatcher = CommandDispatcher(peripherals);

    while(1)
    {
        if((length = uart.readLine(buffer, 1)))
        {
            buffer[length] = 0u;
            //printf("%s", buffer);
            dispatcher.Dispatch(buffer, length);
        }
        
    }

    return 0;
}