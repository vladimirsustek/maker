#include "tone.hpp"

Tone* Tone::instance = nullptr;

Tone* Tone::getInstance(Tim* timer)
{
    if(instance == nullptr)
    {
        static Tone singletonTone;
        instance = &singletonTone;
        instance->timerDevice = timer;
        instance->timerDevice->configureBeepPins();
        instance->timerDevice->enableBeep(true);
        instance->setToneLength(1200);
    }

    return instance;
}

void Tone::playTone(Note note, Duration duration)
{
    instance->timerDevice->enableBeep(true);
    instance->timerDevice->setBeepFrequency(static_cast<uint16_t>(note));
    instance->timerDevice->msDelay(noteLength/static_cast<uint16_t>(duration));
    instance->timerDevice->enableBeep(false);
}

void Tone::playTone(uint16_t freq, uint16_t duration)
{
    instance->timerDevice->enableBeep(true);
    instance->timerDevice->setBeepFrequency(freq);
    instance->timerDevice->msDelay(static_cast<uint32_t>(duration));
    instance->timerDevice->enableBeep(false);
}

void Tone::setToneLength(uint16_t ms)
{
    noteLength = ms;
}
