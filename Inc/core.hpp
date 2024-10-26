extern "C"
{
    #include <avr/io.h>
}

class Core
{
public:
    Core() = default;
    static void enableInterrupts() { sei(); }
    static void disableInterruts() { cli(); }
    static void softwareReset() { /*TBD*/ asm("nop");}
};