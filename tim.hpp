extern "C"
{
    /* Standard libraries */
    #include <stdint.h>
    #include <stdbool.h>
    /* AVR libraries */
    #include <avr/io.h>
    #include <avr/interrupt.h>
}


namespace Tone
{
    constexpr uint16_t 	C_0	= 16;
    constexpr uint16_t 	CisDb_0	= 17;
    constexpr uint16_t 	D_0	= 18;
    constexpr uint16_t 	DisEb_0	= 19;
    constexpr uint16_t 	E_0	= 21;
    constexpr uint16_t 	F_0	= 22;
    constexpr uint16_t 	FisGb_0	= 23;
    constexpr uint16_t 	G_0	= 24;
    constexpr uint16_t 	GisAb_0	= 26;
    constexpr uint16_t 	A_0	= 28;
    constexpr uint16_t 	AesBb_0	= 29;
    constexpr uint16_t 	B_0	= 31;
    /* Octave */
    constexpr uint16_t 	C_1	= 33;
    constexpr uint16_t 	CisDb_1	= 35;
    constexpr uint16_t 	D_1	= 37;
    constexpr uint16_t 	DisEb_1	= 39;
    constexpr uint16_t 	E_1	= 41;
    constexpr uint16_t 	F_1	= 44;
    constexpr uint16_t 	FisGb_1	= 46;
    constexpr uint16_t 	G_1	= 49;
    constexpr uint16_t 	GisAb_1	= 52;
    constexpr uint16_t 	A_1	= 55;
    constexpr uint16_t 	AesBb_1	= 58;
    constexpr uint16_t 	B_1	= 62;
    /* Octave */
    constexpr uint16_t 	C_2	= 65;
    constexpr uint16_t 	CisDb_2	= 69;
    constexpr uint16_t 	D_2	= 73;
    constexpr uint16_t 	DisEb_2	= 78;
    constexpr uint16_t 	E_2	= 82;
    constexpr uint16_t 	F_2	= 87;
    constexpr uint16_t 	FisGb_2	= 92;
    constexpr uint16_t 	G_2	= 98;
    constexpr uint16_t 	GisAb_2	= 104;
    constexpr uint16_t 	A_2	= 110;
    constexpr uint16_t 	AesBb_2	= 117;
    constexpr uint16_t 	B_2	= 123;
    /* Octave */
    constexpr uint16_t 	C_3	= 131;
    constexpr uint16_t 	CisDb_3	= 139;
    constexpr uint16_t 	D_3	= 147;
    constexpr uint16_t 	DisEb_3	= 156;
    constexpr uint16_t 	E_3	= 165;
    constexpr uint16_t 	F_3	= 175;
    constexpr uint16_t 	FisGb_3	= 185;
    constexpr uint16_t 	G_3	= 196;
    constexpr uint16_t 	GisAb_3	= 208;
    constexpr uint16_t 	A_3	= 220;
    constexpr uint16_t 	AesBb_3	= 233;
    constexpr uint16_t 	B_3	= 247;
    /* Octave */
    constexpr uint16_t 	C_4	= 262;
    constexpr uint16_t 	CisDb_4	= 277;
    constexpr uint16_t 	D_4	= 294;
    constexpr uint16_t 	DisEb_4	= 311;
    constexpr uint16_t 	E_4	= 330;
    constexpr uint16_t 	F_4	= 349;
    constexpr uint16_t 	FisGb_4	= 370;
    constexpr uint16_t 	G_4	= 392;
    constexpr uint16_t 	GisAb_4	= 415;
    constexpr uint16_t 	A_4	= 440;
    constexpr uint16_t 	AesBb_4	= 466;
    constexpr uint16_t 	B_4	= 494;
    /* Octave */
    constexpr uint16_t 	C_5	= 523;
    constexpr uint16_t 	CisDb_5	= 554;
    constexpr uint16_t 	D_5	= 587;
    constexpr uint16_t 	DisEb_5	= 622;
    constexpr uint16_t 	E_5	= 659;
    constexpr uint16_t 	F_5	= 698;
    constexpr uint16_t 	FisGb_5	= 740;
    constexpr uint16_t 	G_5	= 784;
    constexpr uint16_t 	GisAb_5	= 831;
    constexpr uint16_t 	A_5	= 880;
    constexpr uint16_t 	AesBb_5	= 932;
    constexpr uint16_t 	B_5	= 988;
    /* Octave */
    constexpr uint16_t 	C_6	= 1047;
    constexpr uint16_t 	CisDb_6	= 1109;
    constexpr uint16_t 	D_6	= 1175;
    constexpr uint16_t 	DisEb_6	= 1245;
    constexpr uint16_t 	E_6	= 1319;
    constexpr uint16_t 	F_6	= 1397;
    constexpr uint16_t 	FisGb_6	= 1480;
    constexpr uint16_t 	G_6	= 1568;
    constexpr uint16_t 	GisAb_6	= 1661;
    constexpr uint16_t 	A_6	= 1760;
    constexpr uint16_t 	AesBb_6	= 1865;
    constexpr uint16_t 	B_6	= 1976;
    /* Octave */
    constexpr uint16_t 	C_7	= 2093;
    constexpr uint16_t 	CisDb_7	= 2217;
    constexpr uint16_t 	D_7	= 2349;
    constexpr uint16_t 	DisEb_7	= 2489;
    constexpr uint16_t 	E_7	= 2637;
    constexpr uint16_t 	F_7	= 2794;
    constexpr uint16_t 	FisGb_7	= 2960;
    constexpr uint16_t 	G_7	= 3136;
    constexpr uint16_t 	GisAb_7	= 3322;
    constexpr uint16_t 	A_7	= 3520;
    constexpr uint16_t 	AesBb_7	= 3729;
    constexpr uint16_t 	B_7	= 3951;
    /* Octave */
    constexpr uint16_t 	C_8	= 4186;
    constexpr uint16_t 	CisDb_8	= 4435;
    constexpr uint16_t 	D_8	= 4699;
    constexpr uint16_t 	DisEb_8	= 4978;
    constexpr uint16_t 	E_8	= 5274;
    constexpr uint16_t 	F_8	= 5588;
    constexpr uint16_t 	FisGb_8	= 5920;
    constexpr uint16_t 	G_8	= 6272;
    constexpr uint16_t 	GisAb_8	= 6645;
    constexpr uint16_t 	A_8	= 7040;
    constexpr uint16_t 	AesBb_8	= 7459;
    constexpr uint16_t 	B_8	= 7902;
    /* Octave */
    constexpr uint16_t 	C_9	= 8372;
    constexpr uint16_t 	CisDb_9	= 8870;
    constexpr uint16_t 	D_9	= 9397;
    constexpr uint16_t 	DisEb_9	= 9956;
    constexpr uint16_t 	E_9	= 10548;
    constexpr uint16_t 	F_9	= 11175;
    constexpr uint16_t 	FisGb_9	= 11840;
    constexpr uint16_t 	G_9	= 12544;
    constexpr uint16_t 	GisAb_9	= 13290;
    constexpr uint16_t 	A_9	= 14080;
    constexpr uint16_t 	AesBb_9	= 14917;
    constexpr uint16_t 	B_9	= 15804;

}

class Tim
{
public:
    Tim();
    ~Tim();
    uint32_t getTick();
    void msDelay(uint32_t delay); 
    void configureBeepPins(void);
    void setBeepFrequency(uint16_t frequency);
    void enableBeep(bool enable);

};