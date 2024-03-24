extern "C"
{
    #include <avr/io.h>
}

class GPIO
{
public:
    void set(bool state);
    bool get(void);
};