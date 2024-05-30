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
    timerDevice.setBeepFrequency(static_cast<uint16_t>(note));
    timerDevice.msDelay(noteLength/static_cast<uint16_t>(duration));
}

void Tone::setToneLength(uint16_t ms)
{
    noteLength = ms;
}
