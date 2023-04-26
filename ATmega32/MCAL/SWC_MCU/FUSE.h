/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : FUSE.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef FUSE_H_
#define FUSE_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

#define FUSE_MEMORY_SIZE 		2

/*************************************************************************/

typedef enum{
    External_Clock               = (u8)0u,

    Internal_RC_Oscillator_1MHz  = (u8)1u,      //default
    Internal_RC_Oscillator_2MHz  = (u8)2u,
    Internal_RC_Oscillator_4MHz  = (u8)3u,
    Internal_RC_Oscillator_8MHz  = (u8)4u,

    External_RC_Oscillator_900KHz  = (u8)5u,
    External_RC_Oscillator_3MHz    = (u8)6u,
    External_RC_Oscillator_8MHz    = (u8)7u,
    External_RC_Oscillator_12Mhz   = (u8)8u,

    External_Low_Freq_Crystal_Oscillator   = (u8)9u,

    /** 12 - 22 C1 and C2 for Use with Crystals (pF) **/
    External_Crystal_Low_Freq0      =(u8)10u,   /** 900kHz Ceramic resonator, slowly rising power **/
    External_Crystal_Low_Freq1      =(u8)11u,   /** 2MHz   Crystal Oscillator, slowly rising power **/
    External_Crystal_Medium_Freq0   =(u8)12u,   /** 3MHz   Ceramic resonator, fast rising power **/
    External_Crystal_Medium_Freq1   =(u8)13u,   /** 8MHz   Crystal Oscillator, fast rising power **/
    External_Crystal_High_Freq0     =(u8)14u,   /** 8MHz   Ceramic resonator, BODenabled **/
    External_Crystal_High_Freq1     =(u8)15u,   /** 16MHz  Crystal Oscillator, BOD enabled **/
}SysClockOption_type;                              // CKSEL[3 0]

typedef union{
    u8 FUSE_L;
    struct {
        u8 CKSEL    : 4;        // SysClockOption_t
        u8 SUT      : 2;        // Select start-up time
        u8 BODEN    : 1;        // Brown-out Detector
        u8 BODLEVEL : 1;        // Brown-out Detector trigger level
    }sBits;
}Fuse_Low_Byte_type;

typedef union{
    u8 FUSE_H;
    struct {
        u8 BOOTRST  : 1;        // Select reset vector
        u8 BOOTSZ   : 2;        // Select Boot Size
        u8 EESAVE   : 1;        // EEPROM memory
        u8 CKOPT    : 1;        // Oscillator options
        u8 SPIEN    : 1;        // Enable SPI Serial Program and Data Downloading
        u8 JTAGEN   : 1;        // Enable JTAG
        u8 OCDEN    : 1;        // Enable OCD
    }sBits;
}Fuse_High_Byte_type;

/*************************************************************************/

typedef struct
{
#if FUSE_MEMORY_SIZE > 3
    u8 byte[FUSE_MEMORY_SIZE];
#else
#if FUSE_MEMORY_SIZE >= 1
    Fuse_Low_Byte_type low;
#endif
#if FUSE_MEMORY_SIZE >= 2
    Fuse_High_Byte_type high;
#endif
#if FUSE_MEMORY_SIZE == 3
    u8 extended;
#endif
#endif
} Fuse_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define FUSEMEM  			__attribute__((section (".fuse")))

#define FUSES 				Fuse_type __fuse FUSEMEM

/* Low Fuse Byte */
#define FUSE_CKSEL0      (unsigned char)~_BV(0)
#define FUSE_CKSEL1      (unsigned char)~_BV(1)
#define FUSE_CKSEL2      (unsigned char)~_BV(2)
#define FUSE_CKSEL3      (unsigned char)~_BV(3)
#define FUSE_SUT0        (unsigned char)~_BV(4)
#define FUSE_SUT1        (unsigned char)~_BV(5)
#define FUSE_BODEN       (unsigned char)~_BV(6)
#define FUSE_BODLEVEL    (unsigned char)~_BV(7)
#define LFUSE_DEFAULT (FUSE_CKSEL1 & FUSE_CKSEL2 & FUSE_CKSEL3 & FUSE_SUT0)

/* High Fuse Byte */
#define FUSE_BOOTRST     (unsigned char)~_BV(0)
#define FUSE_BOOTSZ0     (unsigned char)~_BV(1)
#define FUSE_BOOTSZ1     (unsigned char)~_BV(2)
#define FUSE_EESAVE      (unsigned char)~_BV(3)
#define FUSE_CKOPT       (unsigned char)~_BV(4)
#define FUSE_SPIEN       (unsigned char)~_BV(5)
#define FUSE_JTAGEN      (unsigned char)~_BV(6)
#define FUSE_OCDEN       (unsigned char)~_BV(7)
#define HFUSE_DEFAULT (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN & FUSE_JTAGEN)


/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/*
    FUSES =
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN),
        .extended = EFUSE_DEFAULT,
    };

    __fuse_t __fuse __attribute__((section (".fuse"))) =
    {
        .low = LFUSE_DEFAULT,
        .high = (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_SPIEN & FUSE_JTAGEN)
    };
 */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* FUSE_H_ */
/*************************** E N D (FUSE.h) ******************************/
