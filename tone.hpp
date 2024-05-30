#ifndef TONE_HPP
#define TONE_HPP

#include "tim.hpp"

enum class Note : uint16_t
{
    None = 0,
    /* Octave 0*/
    C_0	= 16,
    CisDb_0	= 17,
    D_0	= 18,
    DisEb_0	= 19,
    E_0	= 21,
    F_0	= 22,
    FisGb_0	= 23,
    G_0	= 24,
    GisAb_0	= 26,
    A_0	= 28,
    AesBb_0	= 29,
    B_0	= 31,
    /* Octave 1*/
    C_1	= 33,
    CisDb_1	= 35,
    D_1	= 37,
    DisEb_1	= 39,
    E_1	= 41,
    F_1	= 44,
    FisGb_1	= 46,
    G_1	= 49,
    GisAb_1	= 52,
    A_1	= 55,
    AesBb_1	= 58,
    B_1	= 62,
    /* Octave 2*/
    C_2	= 65,
    CisDb_2	= 69,
    D_2	= 73,
    DisEb_2	= 78,
    E_2	= 82,
    F_2	= 87,
    FisGb_2	= 92,
    G_2	= 98,
    GisAb_2	= 104,
    A_2	= 110,
    AesBb_2	= 117,
    B_2	= 123,
    /* Octave 3*/
    C_3	= 131,
    CisDb_3	= 139,
    D_3	= 147,
    DisEb_3	= 156,
    E_3	= 165,
    F_3	= 175,
    FisGb_3	= 185,
    G_3	= 196,
    GisAb_3	= 208,
    A_3	= 220,
    AesBb_3	= 233,
    B_3	= 247,
    /* Octave 4*/
    C_4	= 262,
    CisDb_4	= 277,
    D_4	= 294,
    DisEb_4	= 311,
    E_4	= 330,
    F_4	= 349,
    FisGb_4	= 370,
    G_4	= 392,
    GisAb_4	= 415,
    A_4	= 440,
    AesBb_4	= 466,
    B_4	= 494,
    /* Octave 5*/
    C_5	= 523,
    CisDb_5	= 554,
    D_5	= 587,
    DisEb_5	= 622,
    E_5	= 659,
    F_5	= 698,
    FisGb_5	= 740,
    G_5	= 784,
    GisAb_5	= 831,
    A_5	= 880,
    AesBb_5	= 932,
    B_5	= 988,
    /* Octave 6*/
    C_6	= 1047,
    CisDb_6	= 1109,
    D_6	= 1175,
    DisEb_6	= 1245,
    E_6	= 1319,
    F_6	= 1397,
    FisGb_6	= 1480,
    G_6	= 1568,
    GisAb_6	= 1661,
    A_6	= 1760,
    AesBb_6	= 1865,
    B_6	= 1976,
    /* Octave 7*/
    C_7	= 2093,
    CisDb_7	= 2217,
    D_7	= 2349,
    DisEb_7	= 2489,
    E_7	= 2637,
    F_7	= 2794,
    FisGb_7	= 2960,
    G_7	= 3136,
    GisAb_7	= 3322,
    A_7	= 3520,
    AesBb_7	= 3729,
    B_7	= 3951,
    /* Octave 8*/
    C_8	= 4186,
    CisDb_8	= 4435,
    D_8	= 4699,
    DisEb_8	= 4978,
    E_8	= 5274,
    F_8	= 5588,
    FisGb_8	= 5920,
    G_8	= 6272,
    GisAb_8	= 6645,
    A_8	= 7040,
    AesBb_8	= 7459,
    B_8	= 7902,
    /* Octave 9*/
    C_9	= 8372,
    CisDb_9	= 8870,
    D_9	= 9397,
    DisEb_9	= 9956,
    E_9	= 10548,
    F_9	= 11175,
    FisGb_9	= 11840,
    G_9	= 12544,
    GisAb_9	= 13290,
    A_9	= 14080,
    AesBb_9	= 14917,
    B_9	= 15804

};

enum class Duration
{
    Full	= 1,
    Half	= 2,
    Quarter	= 4,
    Eighth	= 8,
    Sixtennth	= 16
};


class Tone
{
public:
    Tone(Tim & timer);
    ~Tone() = default;
    void playTone(Note note, Duration duration);
    void setToneLength(uint16_t ms);
private:
    Tim & timerDevice;
    uint16_t noteLength;
};

#endif