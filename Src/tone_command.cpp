#include "tone_command.hpp"
#include "tone.hpp"

struct Song
{
    Note note;
    Duration duration;
};

constexpr uint16_t SEDMIKRASKY_LNG = 24;

const Song Sedmikrasky[SEDMIKRASKY_LNG]
{
    /* Hvezdy jsou jak sedmikrasky */
    {Note::F_6, Duration::Quarter},
    {Note::AesBb_6, Duration::Quarter},
    {Note::DisEb_7, Duration::Quarter},
    {Note::CisDb_7, Duration::Quarter},
    {Note::E_7, Duration::Quarter},
    {Note::DisEb_7, Duration::Quarter},
    {Note::CisDb_7, Duration::Quarter},
    {Note::AesBb_6, Duration::Quarter},
    /* nad Brnem */
    {Note::GisAb_6, Duration::Quarter},
    {Note::AesBb_6, Duration::Quarter},
    {Note::F_6, Duration::Half},
    {Note::F_6, Duration::Half},
    {Note::None, Duration::Half},
    /* noc, muj mily */
    {Note::E_6, Duration::Quarter},
    {Note::FisGb_6, Duration::Quarter},
    {Note::AesBb_6, Duration::Quarter},
    {Note::CisDb_7, Duration::Quarter},
    /* dobrou */
    {Note::CisDb_7, Duration::Half},
    {Note::DisEb_7, Duration::Quarter},
    {Note::AesBb_6, Duration::Quarter},
    /* noc */
    {Note::CisDb_7, Duration::Full},
    {Note::CisDb_7, Duration::Half},
    /* -pomlka- */
    {Note::CisDb_7, Duration::Quarter},
    {Note::CisDb_7, Duration::Quarter}
};

uint16_t TonePlay(const uint8_t* const pStrCmd, const uint8_t lng)
{
    if ((CMD_METHOD_LNG + CMD_NAME_LNG +
         CMD_DELIMITER_LNG*3 + CMD_ARG5_LNG*2+
         CMD_EOL_LNG) != lng) {

        return CMD_RET_ERR;
    }

    uint16_t freq = (pStrCmd[CMD_ARG_OFFSET + 0] - '0')*10000;

    freq += (pStrCmd[CMD_ARG_OFFSET + 1] - '0')*1000;
    freq += (pStrCmd[CMD_ARG_OFFSET + 2] - '0')*100;
    freq += (pStrCmd[CMD_ARG_OFFSET + 3] - '0')*10;
    freq += (pStrCmd[CMD_ARG_OFFSET + 4] - '0')*1;

    uint16_t duration = (pStrCmd[CMD_ARG_OFFSET + 6] - '0')*10000;

    duration += (pStrCmd[CMD_ARG_OFFSET + 7] - '0')*1000;
    duration += (pStrCmd[CMD_ARG_OFFSET + 8] - '0')*100;
    duration += (pStrCmd[CMD_ARG_OFFSET + 9] - '0')*10;
    duration += (pStrCmd[CMD_ARG_OFFSET + 10] - '0')*1;

    Tim* timDevice = Tim::getInstance();
    Tone* toneDevice = Tone::getInstance(timDevice);

    toneDevice->playTone(freq, duration);

    return 0;
}

uint16_t PlaySedmikrasky(const uint8_t* const pStrCmd, const uint8_t lng)
{
    if ((CMD_METHOD_LNG + CMD_NAME_LNG +
        CMD_DELIMITER_LNG*1 +
        CMD_EOL_LNG) != lng) {

    return CMD_RET_ERR;
}
    (void)pStrCmd;
    (void)lng;

    Tim* timDevice = Tim::getInstance();
    Tone* toneDevice = Tone::getInstance(timDevice);

    for(uint16_t idx = 0; idx < SEDMIKRASKY_LNG; idx++)
    {
        toneDevice->playTone(Sedmikrasky[idx].note, Sedmikrasky[idx].duration);
    }    
    return 0;
}