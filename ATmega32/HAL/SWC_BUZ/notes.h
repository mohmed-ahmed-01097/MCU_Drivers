/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : notes.h												  */
/* Author      : MAAM														  */
/* Version     : v20														  */
/* date        : Sep 2, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef NOTES_H_
#define NOTES_H_

// https://pages.mtu.edu/~suits/notefreqs.html
/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* There are 12 notes in octave + variations (lower case, other names)  */
/* C, C#/Db, D, D#/Eb, E, F, F#/Gb, G, G#/Ab, A, A#/Bb, B */
#define OCTAVE_NUM	8u
/* ************************************************************************** */

#define Note_C_0       16u       /* C0   PWM:   16.00 Hz, note freq:   16.35 Hz, error 2.14% */
#define Note_C_1       33u       /* C1   PWM:   33.00 Hz, note freq:   32.70 Hz, error 0.92% */
#define Note_C_2       65u       /* C2   PWM:   65.00 Hz, note freq:   65.40 Hz, error 0.61% */
#define Note_C_3      131u       /* C3   PWM:  131.01 Hz, note freq:  130.80 Hz, error 0.16% */
#define Note_C_4      261u       /* C4   PWM:  261.03 Hz, note freq:  261.60 Hz, error 0.22% */
#define Note_C_5      523u       /* C5   PWM:  523.01 Hz, note freq:  523.20 Hz, error 0.04% */
#define Note_C_6     1046u       /* C6   PWM: 1046.03 Hz, note freq: 1046.40 Hz, error 0.04% */
#define Note_C_7     2092u       /* C7   PWM: 2092.05 Hz, note freq: 2092.80 Hz, error 0.04% */
#define Note_C_8     4184u        /* C8   PWM: 4184.10 Hz, note freq: 4185.60 Hz, error 0.04% */

#define Note_C_x_0     17u       /* C0x  PWM:   17.00 Hz, note freq:   17.32 Hz, error 1.85% */
#define Note_C_x_1     35u       /* C1x  PWM:   35.00 Hz, note freq:   34.64 Hz, error 1.04% */
#define Note_C_x_2     69u       /* C2x  PWM:   69.00 Hz, note freq:   69.28 Hz, error 0.40% */
#define Note_C_x_3    138u       /* C3x  PWM:  138.01 Hz, note freq:  138.56 Hz, error 0.40% */
#define Note_C_x_4    277u       /* C4x  PWM:  277.01 Hz, note freq:  277.12 Hz, error 0.04% */
#define Note_C_x_5    554u       /* C5x  PWM:  554.02 Hz, note freq:  554.24 Hz, error 0.04% */
#define Note_C_x_6   1108u       /* C6x  PWM: 1108.65 Hz, note freq: 1108.48 Hz, error 0.02% */
#define Note_C_x_7   2217u       /* C7x  PWM: 2217.29 Hz, note freq: 2216.96 Hz, error 0.02% */
#define Note_C_x_8   4420u        /* C8x  PWM: 4424.78 Hz, note freq: 4433.92 Hz, error 0.21% */

#define Note_D_0       18u       /* D0   PWM:   18.00 Hz, note freq:   18.35 Hz, error 1.91% */
#define Note_D_1       37u       /* D1   PWM:   37.00 Hz, note freq:   36.70 Hz, error 0.82% */
#define Note_D_2       73u       /* D2   PWM:   73.00 Hz, note freq:   73.40 Hz, error 0.54% */
#define Note_D_3      147u       /* D3   PWM:  147.02 Hz, note freq:  146.80 Hz, error 0.15% */
#define Note_D_4      294u       /* D4   PWM:  294.03 Hz, note freq:  293.60 Hz, error 0.15% */
#define Note_D_5      587u       /* D5   PWM:  587.20 Hz, note freq:  587.20 Hz, error 0.00% */
#define Note_D_6     1174u       /* D6   PWM: 1175.09 Hz, note freq: 1174.40 Hz, error 0.06% */
#define Note_D_7     2345u       /* D7   PWM: 2347.42 Hz, note freq: 2348.80 Hz, error 0.06% */
#define Note_D_8     4693u        /* D8   PWM: 4694.84 Hz, note freq: 4697.60 Hz, error 0.06% */

#define Note_D_x_0     19u       /* D0x  PWM:   19.00 Hz, note freq:   19.45 Hz, error 2.31% */
#define Note_D_x_1     39u       /* D1x  PWM:   39.00 Hz, note freq:   38.90 Hz, error 0.26% */
#define Note_D_x_2     78u       /* D2x  PWM:   78.00 Hz, note freq:   77.80 Hz, error 0.26% */
#define Note_D_x_3    156u       /* D3x  PWM:  156.01 Hz, note freq:  155.60 Hz, error 0.26% */
#define Note_D_x_4    311u       /* D4x  PWM:  311.04 Hz, note freq:  311.20 Hz, error 0.05% */
#define Note_D_x_5    622u       /* D5x  PWM:  622.28 Hz, note freq:  622.40 Hz, error 0.02% */
#define Note_D_x_6   1245u       /* D6x  PWM: 1245.33 Hz, note freq: 1244.80 Hz, error 0.04% */
#define Note_D_x_7   2487u       /* D7x  PWM: 2487.56 Hz, note freq: 2489.60 Hz, error 0.08% */
#define Note_D_x_8   4975u        /* D8x  PWM: 4975.12 Hz, note freq: 4979.20 Hz, error 0.08% */

#define Note_E_0       21u       /* E0   PWM:   21.00 Hz, note freq:   20.60 Hz, error 1.94% */
#define Note_E_1       41u       /* E1   PWM:   41.00 Hz, note freq:   41.20 Hz, error 0.48% */
#define Note_E_2       82u       /* E2   PWM:   82.00 Hz, note freq:   82.40 Hz, error 0.48% */
#define Note_E_3      165u       /* E3   PWM:  165.02 Hz, note freq:  164.80 Hz, error 0.13% */
#define Note_E_4      330u       /* E4   PWM:  330.03 Hz, note freq:  329.60 Hz, error 0.13% */
#define Note_E_5      659u       /* E5   PWM:  659.20 Hz, note freq:  659.20 Hz, error 0.00% */
#define Note_E_6     1318u       /* E6   PWM: 1319.26 Hz, note freq: 1318.40 Hz, error 0.07% */
#define Note_E_7     2636u       /* E7   PWM: 2638.52 Hz, note freq: 2636.80 Hz, error 0.07% */
#define Note_E_8     5260u        /* E8   PWM: 5263.16 Hz, note freq: 5273.60 Hz, error 0.20% */

#define Note_F_0       22u       /* F0   PWM:   22.00 Hz, note freq:   21.83 Hz, error 0.78% */
#define Note_F_1       44u       /* F1   PWM:   44.00 Hz, note freq:   43.66 Hz, error 0.78% */
#define Note_F_2       87u       /* F2   PWM:   87.00 Hz, note freq:   87.32 Hz, error 0.36% */
#define Note_F_3      175u       /* F3   PWM:  175.01 Hz, note freq:  174.64 Hz, error 0.21% */
#define Note_F_4      349u       /* F4   PWM:  349.04 Hz, note freq:  349.28 Hz, error 0.07% */
#define Note_F_5      698u       /* F5   PWM:  698.32 Hz, note freq:  698.56 Hz, error 0.03% */
#define Note_F_6     1396u       /* F6   PWM: 1396.65 Hz, note freq: 1397.12 Hz, error 0.03% */
#define Note_F_7     2793u       /* F7   PWM: 2793.30 Hz, note freq: 2794.24 Hz, error 0.03% */
#define Note_F_8     5586u        /* F8   PWM: 5586.59 Hz, note freq: 5588.48 Hz, error 0.03% */

#define Note_F_x_0     23u       /* F0x  PWM:   23.00 Hz, note freq:   23.12 Hz, error 0.52% */
#define Note_F_x_1     46u       /* F1x  PWM:   46.00 Hz, note freq:   46.24 Hz, error 0.52% */
#define Note_F_x_2     92u       /* F2x  PWM:   92.00 Hz, note freq:   92.48 Hz, error 0.51% */
#define Note_F_x_3    185u       /* F3x  PWM:  185.01 Hz, note freq:  184.96 Hz, error 0.03% */
#define Note_F_x_4    370u       /* F4x  PWM:  370.10 Hz, note freq:  369.92 Hz, error 0.05% */
#define Note_F_x_5    740u       /* F5x  PWM:  740.19 Hz, note freq:  739.84 Hz, error 0.05% */
#define Note_F_x_6   1479u       /* F6x  PWM: 1479.29 Hz, note freq: 1479.68 Hz, error 0.03% */
#define Note_F_x_7   2955u       /* F7x  PWM: 2958.58 Hz, note freq: 2959.36 Hz, error 0.03% */
#define Note_F_x_8   5915u       /* F8x  PWM: 5917.16 Hz, note freq: 5918.72 Hz, error 0.03% */

#define Note_G_0       24u       /* G0   PWM:   24.00 Hz, note freq:   24.50 Hz, error 2.04% */
#define Note_G_1       49u       /* G1   PWM:   49.00 Hz, note freq:   49.00 Hz, error 0.00% */
#define Note_G_2       98u       /* G2   PWM:   98.00 Hz, note freq:   98.00 Hz, error 0.00% */
#define Note_G_3      196u       /* G3   PWM:  196.00 Hz, note freq:  196.00 Hz, error 0.00% */
#define Note_G_4      392u       /* G4   PWM:  392.00 Hz, note freq:  392.00 Hz, error 0.00% */
#define Note_G_5      784u       /* G5   PWM:  784.31 Hz, note freq:  784.00 Hz, error 0.04% */
#define Note_G_6     1567u       /* G6   PWM: 1567.40 Hz, note freq: 1568.00 Hz, error 0.04% */
#define Note_G_7     3134u       /* G7   PWM: 3134.80 Hz, note freq: 3136.00 Hz, error 0.04% */
#define Note_G_8     6272u        /* G8   PWM: 6289.31 Hz, note freq: 6272.00 Hz, error 0.28% */

#define Note_G_x_0     26u       /* G0x  PWM:   26.00 Hz, note freq:   25.96 Hz, error 0.16% */
#define Note_G_x_1     52u       /* G1x  PWM:   52.00 Hz, note freq:   51.92 Hz, error 0.16% */
#define Note_G_x_2    104u       /* G2x  PWM:  104.00 Hz, note freq:  103.84 Hz, error 0.16% */
#define Note_G_x_3    208u       /* G3x  PWM:  208.03 Hz, note freq:  207.68 Hz, error 0.17% */
#define Note_G_x_4    415u       /* G4x  PWM:  415.11 Hz, note freq:  415.36 Hz, error 0.06% */
#define Note_G_x_5    830u       /* G5x  PWM:  830.56 Hz, note freq:  830.72 Hz, error 0.02% */
#define Note_G_x_6   1661u       /* G6x  PWM: 1661.13 Hz, note freq: 1661.44 Hz, error 0.02% */
#define Note_G_x_7   3322u       /* G7x  PWM: 3322.26 Hz, note freq: 3322.88 Hz, error 0.02% */
#define Note_G_x_8   6645u       /* G8x  PWM: 6666.67 Hz, note freq: 6645.76 Hz, error 0.31% */

#define Note_A_0       27u       /* A0   PWM:   27.00 Hz, note freq:   27.50 Hz, error 1.82% */
#define Note_A_1       55u       /* A1   PWM:   55.00 Hz, note freq:   55.00 Hz, error 0.00% */
#define Note_A_2      110u       /* A2   PWM:  110.01 Hz, note freq:  110.00 Hz, error 0.01% */
#define Note_A_3      220u       /* A3   PWM:  220.02 Hz, note freq:  220.00 Hz, error 0.01% */
#define Note_A_4      440u       /* A4   PWM:  440.14 Hz, note freq:  440.00 Hz, error 0.03% */
#define Note_A_5      880u       /* A5   PWM:  880.28 Hz, note freq:  880.00 Hz, error 0.03% */
#define Note_A_6     1760u       /* A6   PWM: 1760.56 Hz, note freq: 1760.00 Hz, error 0.03% */
#define Note_A_7     3520u       /* A7   PWM: 3521.13 Hz, note freq: 3520.00 Hz, error 0.03% */
#define Note_A_8     7040u        /* A8   PWM: 7042.25 Hz, note freq: 7040.00 Hz, error 0.03% */

#define Note_A_x_0     29u       /* A0x  PWM:   29.00 Hz, note freq:   29.14 Hz, error 0.48% */
#define Note_A_x_1     58u       /* A1x  PWM:   58.00 Hz, note freq:   58.28 Hz, error 0.48% */
#define Note_A_x_2    116u       /* A2x  PWM:  116.01 Hz, note freq:  116.56 Hz, error 0.47% */
#define Note_A_x_3    233u       /* A3x  PWM:  233.05 Hz, note freq:  233.12 Hz, error 0.03% */
#define Note_A_x_4    466u       /* A4x  PWM:  466.20 Hz, note freq:  466.24 Hz, error 0.01% */
#define Note_A_x_5    932u       /* A5x  PWM:  932.84 Hz, note freq:  932.48 Hz, error 0.04% */
#define Note_A_x_6   1864u       /* A6x  PWM: 1865.67 Hz, note freq: 1864.96 Hz, error 0.04% */
#define Note_A_x_7   3729u       /* A7x  PWM: 3731.34 Hz, note freq: 3729.92 Hz, error 0.04% */
#define Note_A_x_8   7459u       /* A8x  PWM: 7462.69 Hz, note freq: 7459.84 Hz, error 0.04% */

#define Note_B_0       31u       /* B0   PWM:   31.00 Hz, note freq:   30.87 Hz, error 0.42% */
#define Note_B_1       62u       /* B1   PWM:   62.00 Hz, note freq:   61.74 Hz, error 0.42% */
#define Note_B_2      123u       /* B2   PWM:  123.00 Hz, note freq:  123.48 Hz, error 0.39% */
#define Note_B_3      247u       /* B3   PWM:  247.04 Hz, note freq:  246.96 Hz, error 0.03% */
#define Note_B_4      494u       /* B4   PWM:  494.07 Hz, note freq:  493.92 Hz, error 0.03% */
#define Note_B_5      987u       /* B5   PWM:  987.17 Hz, note freq:  987.84 Hz, error 0.07% */
#define Note_B_6     1975u       /* B6   PWM: 1976.28 Hz, note freq: 1975.68 Hz, error 0.03% */
#define Note_B_7     3951u       /* B7   PWM: 3952.57 Hz, note freq: 3951.36 Hz, error 0.03% */
#define Note_B_8     7870u       /* B8   PWM: 7874.02 Hz, note freq: 7902.72 Hz, error 0.36% */

/* ************************************************************************** */

/* Pause */
#define P 					1
#define p 					P
#define PAUSE 				P

/* end of notes table */
#define MUSIC_END 			0
/* Default volume, value assigned to TMR */
#define DEFAULT_VOLUME		100

/* ********************************* Octave #0 ****************************** */
#define C0		Note_C_0
#define c0		Note_C_0

#define C0x		Note_C_x_0
#define c0x		Note_C_x_0
#define xC0		Note_C_x_0
#define xc0		Note_C_x_0
#define Cis0	Note_C_x_0
#define cis0	Note_C_x_0

#define D0b		Note_C_x_0
#define d0b		Note_C_x_0

#define D0    	Note_D_0
#define d0    	Note_D_0

#define D0x		Note_D_x_0
#define d0x		Note_D_x_0
#define xD0		Note_D_x_0
#define xd0		Note_D_x_0
#define Dis0	Note_D_x_0
#define dis0	Note_D_x_0

#define E0b		Note_D_x_0
#define e0b		Note_D_x_0

#define E0		Note_E_0
#define e0		Note_E_0

#define F0		Note_F_0
#define f0		Note_F_0

#define F0x		Note_F_x_0
#define f0x		Note_F_x_0
#define xF0		Note_F_x_0
#define xf0		Note_F_x_0
#define Fis0	Note_F_x_0
#define fis0	Note_F_x_0

#define G0b		Note_F_x_0
#define g0b		Note_F_x_0

#define G0		Note_G_0
#define g0		Note_G_0

#define G0x		Note_G_x_0
#define g0x		Note_G_x_0
#define xG0		Note_G_x_0
#define xg0		Note_G_x_0
#define Gis0	Note_G_x_0
#define gis0	Note_G_x_0

#define A0b		Note_G_x_0
#define a0b		Note_G_x_0

#define A0		Note_A_0
#define a0		Note_A_0

#define A0x		Note_A_x_0
#define a0x		Note_A_x_0
#define xA0		Note_A_x_0
#define xa0		Note_A_x_0
#define Ais0	Note_A_x_0
#define ais0	Note_A_x_0

#define B0b		Note_A_x_0
#define b0b		Note_A_x_0

#define H0b		Note_A_x_0
#define h0b		Note_A_x_0
#define bH0		Note_A_x_0
#define bh0		Note_A_x_0

#define B0		Note_B_0
#define b0		Note_B_0

#define H0		Note_B_0
#define h0		Note_B_0


/* ********************************* Octave #1 ****************************** */
#define C1		Note_C_1
#define c1		Note_C_1

#define C1x		Note_C_x_1
#define c1x		Note_C_x_1
#define xC1		Note_C_x_1
#define xc1		Note_C_x_1
#define Cis1	Note_C_x_1
#define cis1	Note_C_x_1

#define D1b		Note_C_x_1
#define d1b		Note_C_x_1

#define D1    	Note_D_1
#define d1    	Note_D_1

#define D1x		Note_D_x_1
#define d1x		Note_D_x_1
#define xD1		Note_D_x_1
#define xd1		Note_D_x_1
#define Dis1	Note_D_x_1
#define dis1	Note_D_x_1

#define E1b		Note_D_x_1
#define e1b		Note_D_x_1

#define E1		Note_E_1
#define e1		Note_E_1

#define F1		Note_F_1
#define f1		Note_F_1

#define F1x		Note_F_x_1
#define f1x		Note_F_x_1
#define xF1		Note_F_x_1
#define xf1		Note_F_x_1
#define Fis1	Note_F_x_1
#define fis1	Note_F_x_1

#define G1b		Note_F_x_1
#define g1b		Note_F_x_1

#define G1		Note_G_1
#define g1		Note_G_1

#define G1x		Note_G_x_1
#define g1x		Note_G_x_1
#define xG1		Note_G_x_1
#define xg1		Note_G_x_1
#define Gis1	Note_G_x_1
#define gis1	Note_G_x_1

#define A1b		Note_G_x_1
#define a1b		Note_G_x_1

#define A1		Note_A_1
#define a1		Note_A_1

#define A1x		Note_A_x_1
#define a1x		Note_A_x_1
#define xA1		Note_A_x_1
#define xa1		Note_A_x_1
#define Ais1	Note_A_x_1
#define ais1	Note_A_x_1

#define B1b		Note_A_x_1
#define b1b		Note_A_x_1

#define H1b		Note_A_x_1
#define h1b		Note_A_x_1
#define bH1		Note_A_x_1
#define bh1		Note_A_x_1

#define B1		Note_B_1
#define b1		Note_B_1

#define H1		Note_B_1
#define h1		Note_B_1


/* ********************************* Octave #2 ****************************** */
#define C2		Note_C_2
#define c2		Note_C_2

#define C2x		Note_C_x_2
#define c2x		Note_C_x_2
#define xC2		Note_C_x_2
#define xc2		Note_C_x_2
#define Cis2	Note_C_x_2
#define cis2	Note_C_x_2

#define D2b		Note_C_x_2
#define d2b		Note_C_x_2

#define D2    	Note_D_2
#define d2    	Note_D_2

#define D2x		Note_D_x_2
#define d2x		Note_D_x_2
#define xD2		Note_D_x_2
#define xd2		Note_D_x_2
#define Dis2	Note_D_x_2
#define dis2	Note_D_x_2

#define E2b		Note_D_x_2
#define e2b		Note_D_x_2

#define E2		Note_E_2
#define e2		Note_E_2

#define F2		Note_F_2
#define f2		Note_F_2

#define F2x		Note_F_x_2
#define f2x		Note_F_x_2
#define xF2		Note_F_x_2
#define xf2		Note_F_x_2
#define Fis2	Note_F_x_2
#define fis2	Note_F_x_2

#define G2b		Note_F_x_2
#define g2b		Note_F_x_2

#define G2		Note_G_2
#define g2		Note_G_2

#define G2x		Note_G_x_2
#define g2x		Note_G_x_2
#define xG2		Note_G_x_2
#define xg2		Note_G_x_2
#define Gis2	Note_G_x_2
#define gis2	Note_G_x_2

#define A2b		Note_G_x_2
#define a2b		Note_G_x_2

#define A2		Note_A_2
#define a2		Note_A_2

#define A2x		Note_A_x_2
#define a2x		Note_A_x_2
#define xA2		Note_A_x_2
#define xa2		Note_A_x_2
#define Ais2	Note_A_x_2
#define ais2	Note_A_x_2

#define B2b		Note_A_x_2
#define b2b		Note_A_x_2

#define H2b		Note_A_x_2
#define h2b		Note_A_x_2
#define bH2		Note_A_x_2
#define bh2		Note_A_x_2

#define B2		Note_B_2
#define b2		Note_B_2

#define H2		Note_B_2
#define h2		Note_B_2


/* ********************************* Octave #3 ****************************** */
#define C3		Note_C_3
#define c3		Note_C_3

#define C3x		Note_C_x_3
#define c3x		Note_C_x_3
#define xC3		Note_C_x_3
#define xc3		Note_C_x_3
#define Cis3	Note_C_x_3
#define cis3	Note_C_x_3

#define D3b		Note_C_x_3
#define d3b		Note_C_x_3

#define D3    	Note_D_3
#define d3    	Note_D_3

#define D3x		Note_D_x_3
#define d3x		Note_D_x_3
#define xD3		Note_D_x_3
#define xd3		Note_D_x_3
#define Dis3	Note_D_x_3
#define dis3	Note_D_x_3

#define E3b		Note_D_x_3
#define e3b		Note_D_x_3

#define E3		Note_E_3
#define e3		Note_E_3

#define F3		Note_F_3
#define f3		Note_F_3

#define F3x		Note_F_x_3
#define f3x		Note_F_x_3
#define xF3		Note_F_x_3
#define xf3		Note_F_x_3
#define Fis3	Note_F_x_3
#define fis3	Note_F_x_3

#define G3b		Note_F_x_3
#define g3b		Note_F_x_3

#define G3		Note_G_3
#define g3		Note_G_3

#define G3x		Note_G_x_3
#define g3x		Note_G_x_3
#define xG3		Note_G_x_3
#define xg3		Note_G_x_3
#define Gis3	Note_G_x_3
#define gis3	Note_G_x_3

#define A3b		Note_G_x_3
#define a3b		Note_G_x_3

#define A3		Note_A_3
#define a3		Note_A_3

#define A3x		Note_A_x_3
#define a3x		Note_A_x_3
#define xA3		Note_A_x_3
#define xa3		Note_A_x_3
#define Ais3	Note_A_x_3
#define ais3	Note_A_x_3

#define B3b		Note_A_x_3
#define b3b		Note_A_x_3

#define H3b		Note_A_x_3
#define h3b		Note_A_x_3
#define bH3		Note_A_x_3
#define bh3		Note_A_x_3

#define B3		Note_B_3
#define b3		Note_B_3

#define H3		Note_B_3
#define h3		Note_B_3


/* ********************************* Octave #4 ****************************** */
#define C4		Note_C_4
#define c4		Note_C_4

#define C4x		Note_C_x_4
#define c4x		Note_C_x_4
#define xC4		Note_C_x_4
#define xc4		Note_C_x_4
#define Cis4	Note_C_x_4
#define cis4	Note_C_x_4

#define D4b		Note_C_x_4
#define d4b		Note_C_x_4

#define D4    	Note_D_4
#define d4    	Note_D_4

#define D4x		Note_D_x_4
#define d4x		Note_D_x_4
#define xD4		Note_D_x_4
#define xd4		Note_D_x_4
#define Dis4	Note_D_x_4
#define dis4	Note_D_x_4

#define E4b		Note_D_x_4
#define e4b		Note_D_x_4

#define E4		Note_E_4
#define e4		Note_E_4

#define F4		Note_F_4
#define f4		Note_F_4

#define F4x		Note_F_x_4
#define f4x		Note_F_x_4
#define xF4		Note_F_x_4
#define xf4		Note_F_x_4
#define Fis4	Note_F_x_4
#define fis4	Note_F_x_4

#define G4b		Note_F_x_4
#define g4b		Note_F_x_4

#define G4		Note_G_4
#define g4		Note_G_4

#define G4x		Note_G_x_4
#define g4x		Note_G_x_4
#define xG4		Note_G_x_4
#define xg4		Note_G_x_4
#define Gis4	Note_G_x_4
#define gis4	Note_G_x_4

#define A4b		Note_G_x_4
#define a4b		Note_G_x_4

#define A4		Note_A_4
#define a4		Note_A_4

#define A4x		Note_A_x_4
#define a4x		Note_A_x_4
#define xA4		Note_A_x_4
#define xa4		Note_A_x_4
#define Ais4	Note_A_x_4
#define ais4	Note_A_x_4

#define B4b		Note_A_x_4
#define b4b		Note_A_x_4

#define H4b		Note_A_x_4
#define h4b		Note_A_x_4
#define bH4		Note_A_x_4
#define bh4		Note_A_x_4

#define B4		Note_B_4
#define b4		Note_B_4

#define H4		Note_B_4
#define h4		Note_B_4


/* ********************************* Octave #5 ****************************** */
#define C5		Note_C_5
#define c5		Note_C_5

#define C5x		Note_C_x_5
#define c5x		Note_C_x_5
#define xC5		Note_C_x_5
#define xc5		Note_C_x_5
#define Cis5	Note_C_x_5
#define cis5	Note_C_x_5

#define D5b		Note_C_x_5
#define d5b		Note_C_x_5

#define D5    	Note_D_5
#define d5    	Note_D_5

#define D5x		Note_D_x_5
#define d5x		Note_D_x_5
#define xD5		Note_D_x_5
#define xd5		Note_D_x_5
#define Dis5	Note_D_x_5
#define dis5	Note_D_x_5

#define E5b		Note_D_x_5
#define e5b		Note_D_x_5

#define E5		Note_E_5
#define e5		Note_E_5

#define F5		Note_F_5
#define f5		Note_F_5

#define F5x		Note_F_x_5
#define f5x		Note_F_x_5
#define xF5		Note_F_x_5
#define xf5		Note_F_x_5
#define Fis5	Note_F_x_5
#define fis5	Note_F_x_5

#define G5b		Note_F_x_5
#define g5b		Note_F_x_5

#define G5		Note_G_5
#define g5		Note_G_5

#define G5x		Note_G_x_5
#define g5x		Note_G_x_5
#define xG5		Note_G_x_5
#define xg5		Note_G_x_5
#define Gis5	Note_G_x_5
#define gis5	Note_G_x_5

#define A5b		Note_G_x_5
#define a5b		Note_G_x_5

#define A5		Note_A_5
#define a5		Note_A_5

#define A5x		Note_A_x_5
#define a5x		Note_A_x_5
#define xA5		Note_A_x_5
#define xa5		Note_A_x_5
#define Ais5	Note_A_x_5
#define ais5	Note_A_x_5

#define B5b		Note_A_x_5
#define b5b		Note_A_x_5

#define H5b		Note_A_x_5
#define h5b		Note_A_x_5
#define bH5		Note_A_x_5
#define bh5		Note_A_x_5

#define B5		Note_B_5
#define b5		Note_B_5

#define H5		Note_B_5
#define h5		Note_B_5

/* ********************************* Octave #6 ****************************** */
#define C6		Note_C_6
#define c6		Note_C_6

#define C6x		Note_C_x_6
#define c6x		Note_C_x_6
#define xC6		Note_C_x_6
#define xc6		Note_C_x_6
#define Cis6	Note_C_x_6
#define cis6	Note_C_x_6

#define D6b		Note_C_x_6
#define d6b		Note_C_x_6

#define D6    	Note_D_6
#define d6    	Note_D_6

#define D6x		Note_D_x_6
#define d6x		Note_D_x_6
#define xD6		Note_D_x_6
#define xd6		Note_D_x_6
#define Dis6	Note_D_x_6
#define dis6	Note_D_x_6

#define E6b		Note_D_x_6
#define e6b		Note_D_x_6

#define E6		Note_E_6
#define e6		Note_E_6

#define F6		Note_F_6
#define f6		Note_F_6

#define F6x		Note_F_x_6
#define f6x		Note_F_x_6
#define xF6		Note_F_x_6
#define xf6		Note_F_x_6
#define Fis6	Note_F_x_6
#define fis6	Note_F_x_6

#define G6b		Note_F_x_6
#define g6b		Note_F_x_6

#define G6		Note_G_6
#define g6		Note_G_6

#define G6x		Note_G_x_6
#define g6x		Note_G_x_6
#define xG6		Note_G_x_6
#define xg6		Note_G_x_6
#define Gis6	Note_G_x_6
#define gis6	Note_G_x_6

#define A6b		Note_G_x_6
#define a6b		Note_G_x_6

#define A6		Note_A_6
#define a6		Note_A_6

#define A6x		Note_A_x_6
#define a6x		Note_A_x_6
#define xA6		Note_A_x_6
#define xa6		Note_A_x_6
#define Ais6	Note_A_x_6
#define ais6	Note_A_x_6

#define B6b		Note_A_x_6
#define b6b		Note_A_x_6

#define H6b		Note_A_x_6
#define h6b		Note_A_x_6
#define bH6		Note_A_x_6
#define bh6		Note_A_x_6

#define B6		Note_B_6
#define b6		Note_B_6

#define H6		Note_B_6
#define h6		Note_B_6


/* ********************************* Octave #7 ****************************** */
#define C7		Note_C_7
#define c7		Note_C_7

#define C7x		Note_C_x_7
#define c7x		Note_C_x_7
#define xC7		Note_C_x_7
#define xc7		Note_C_x_7
#define Cis7	Note_C_x_7
#define cis7	Note_C_x_7

#define D7b		Note_C_x_7
#define d7b		Note_C_x_7

#define D7    	Note_D_7
#define d7    	Note_D_7

#define D7x		Note_D_x_7
#define d7x		Note_D_x_7
#define xD7		Note_D_x_7
#define xd7		Note_D_x_7
#define Dis7	Note_D_x_7
#define dis7	Note_D_x_7

#define E7b		Note_D_x_7
#define e7b		Note_D_x_7

#define E7		Note_E_7
#define e7		Note_E_7

#define F7		Note_F_7
#define f7		Note_F_7

#define F7x		Note_F_x_7
#define f7x		Note_F_x_7
#define xF7		Note_F_x_7
#define xf7		Note_F_x_7
#define Fis7	Note_F_x_7
#define fis7	Note_F_x_7

#define G7b		Note_F_x_7
#define g7b		Note_F_x_7

#define G7		Note_G_7
#define g7		Note_G_7

#define G7x		Note_G_x_7
#define g7x		Note_G_x_7
#define xG7		Note_G_x_7
#define xg7		Note_G_x_7
#define Gis7	Note_G_x_7
#define gis7	Note_G_x_7

#define A7b		Note_G_x_7
#define a7b		Note_G_x_7

#define A7		Note_A_7
#define a7		Note_A_7

#define A7x		Note_A_x_7
#define a7x		Note_A_x_7
#define xA7		Note_A_x_7
#define xa7		Note_A_x_7
#define Ais7	Note_A_x_7
#define ais7	Note_A_x_7

#define B7b		Note_A_x_7
#define b7b		Note_A_x_7

#define H7b		Note_A_x_7
#define h7b		Note_A_x_7
#define bH7		Note_A_x_7
#define bh7		Note_A_x_7

#define B7		Note_B_7
#define b7		Note_B_7

#define H7		Note_B_7
#define h7		Note_B_7

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void Music_Init(void);
void Music_Run(const u16* pMusicNotes, u8 u8Tempo);


#endif /* NOTES_H_ */
/*************************** E N D (notes.h) ******************************/
