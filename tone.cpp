#include "tone.hpp"

Tone::Tone(Tim & timer):
    timerDevice(timer)
    {
        timerDevice.configureBeepPins();
        timerDevice.enableBeep(true);
        noteLength = 1200;
    }

void Tone::playTone(Note note, Duration duration)
{
    timerDevice.enableBeep(true);
    timerDevice.setBeepFrequency(static_cast<uint16_t>(note));
    timerDevice.msDelay(noteLength/static_cast<uint16_t>(duration));
    timerDevice.enableBeep(false);
}

void Tone::playTone(Note note, uint16_t duration)
{
    timerDevice.enableBeep(true);
    timerDevice.setBeepFrequency(static_cast<uint16_t>(note));
    timerDevice.msDelay(static_cast<uint32_t>(duration));
    timerDevice.enableBeep(false);
}

void Tone::setToneLength(uint16_t ms)
{
    noteLength = ms;
}
