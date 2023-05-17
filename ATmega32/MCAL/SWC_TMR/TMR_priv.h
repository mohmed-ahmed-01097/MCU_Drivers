/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Apr 5, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef TMR_PRIV_H_
#define TMR_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef union{
    u8 u_Reg;
    struct {
        __I  u8 m_TCR2UB : 1;        // Timer/Counter Control Register2 Update Busy
        __I  u8 m_OCR2UB : 1;        // Output Compare Register2 Update Busy
        __I  u8 m_TCN2UB : 1;        // Timer/Counter2 Update Busy
        __IO u8 m_AS2    : 1;        // Asynchronous Timer/Counter2
        __IO u8          : 4;
    }sBits;
}ASSR_type;   // Asynchronous Status Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_CSx  : 3;        // Clock Select
    	__IO u8 m_WGMx1: 1;        // Waveform Generation Mode
    	__IO u8 m_COMx : 2;        // Compare Match Output Mode
    	__IO u8 m_WGMx0: 1;        // Waveform Generation Mode
    	__IO u8 m_FOCx : 1;        // Force Output Compare
    }sBits;
}TCCRx_type;   // Timer/Counter Control Register

/*************************************************************************/

typedef struct{
    __IO ASSR_type  m_ASSR;     // Asynchronous Status Register
    __IO u8         m_OCR2;     // Output Compare Register
    __IO u8         m_TCNT2;    // Timer/Counter Register
    __IO TCCRx_type m_TCCR2;    // Timer/Counter Control Register
}GPTMR2_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef struct{
    __IO u8         m_TCNT0;    // Timer/Counter Register
    __IO TCCRx_type m_TCCR0;    // Timer/Counter Control Register
    __I  u8         REVERSE[8];
    __IO u8         m_OCR0;     // Output Compare Register
}GPTMR0_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_CS1  : 3;        // Clock Select
    	__IO u8 m_WGM12: 1;        // Waveform Generation Mode
    	__IO u8 m_WGM13: 1;        // Waveform Generation Mode
    	__IO u8        : 1;
    	__IO u8 m_ICES1: 1;        // Input Capture Edge Select
    	__IO u8 m_ICNC1: 1;        // Input Capture Noise Canceler
    }sBits;
}TCCR1B_type;   // Timer/Counter Control Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_WGM10: 1;        // Waveform Generation Mode
    	__IO u8 m_WGM11: 1;        // Waveform Generation Mode
    	__IO u8 m_FOC1B: 1;        // Force Output Compare
    	__IO u8 m_FOC1A: 1;        // Force Output Compare
    	__IO u8 m_COM1B: 2;        // Compare Match Output Mode
    	__IO u8 m_COM1A: 2;        // Compare Match Output Mode
    }sBits;
}TCCR1A_type;   // Timer/Counter Control Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_B0 : 1;
    	__IO u8 m_B1 : 1;
    	__IO u8 m_B2 : 1;
    	__IO u8 m_B3 : 1;
    	__IO u8 m_B4 : 1;
    	__IO u8 m_B5 : 1;
    	__IO u8 m_B6 : 1;
    	__IO u8 m_B7 : 1;
    }sBits;
}BYTE_type; // byte bit exchange

/*************************************************************************/

typedef union{
    u16 u16Reg;
    struct {
    	BYTE_type m_u8Low;
    	BYTE_type m_u8High;
    }sBytes;
    struct {
        u8 m_B0 : 1;
        u8 m_B1 : 1;
        u8 m_B2 : 1;
        u8 m_B3 : 1;
        u8 m_B4 : 1;
        u8 m_B5 : 1;
        u8 m_B6 : 1;
        u8 m_B7 : 1;
        u8 m_B8 : 1;
        u8 m_B9 : 1;
        u8 m_B10: 1;
        u8 m_B11: 1;
        u8 m_B12: 1;
        u8 m_B13: 1;
        u8 m_B14: 1;
        u8 m_B15: 1;
    }sBits;
}Word_type;

/*************************************************************************/

typedef struct{
    __IO Word_type   m_ICR1;	 // Output Compare Register
    __IO Word_type   m_OCR1B;	 // Output Compare Register
    __IO Word_type   m_OCR1A;	 // Output Compare Register
    __IO Word_type   m_TCNT1;	 // Output Compare Register
    __IO TCCR1B_type m_TCCR1B;   // Timer/Counter Control Register
    __IO TCCR1A_type m_TCCR1A;   // Timer/Counter Control Register
}GPTMR1_type;    // General Purpose Input Output Registers

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_PSR10: 1;        // Prescaler Reset Timer/Counter1 and Timer/Counter0
    	__IO u8 m_PSR2 : 1;        // Prescaler Reset Timer/Counter2
    	__IO u8 m_PUD  : 1;        // Pull-up disable
    	__IO u8 m_ACME : 1;        // Analog Comparator Multiplexer Enable
    	__IO u8        : 1;
    	__IO u8 m_ADTS : 3;        // ADC Auto Trigger Source
    }sBits;
}SFIOR_type;   // Special Function I/O Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_TOV0 : 1;        // Timer/Counter1 Overflow Flag
    	__IO u8 m_OCF0 : 1;        // Timer/Counter1 Output Compare Match Flag
    	__IO u8 m_TOV1 : 1;        // Timer/Counter1 Overflow Flag
    	__IO u8 m_OCF1B: 1;        // Timer/Counter1 Output Compare Match Flag
    	__IO u8 m_OCF1A: 1;        // Timer/Counter1 Output Compare Match Flag
    	__IO u8 m_ICF1 : 1;        // Timer/Counter1, Input Capture Flag
    	__IO u8 m_TOV2 : 1;        // Timer/Counter2 Overflow Flag
    	__IO u8 m_OCF2 : 1;        // Timer/Counter2 Output Compare Match Flag
    }sBits;
}TIFR_type;   // Timer/Counter Interrupt Flag Register Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_TOIE0 : 1;        // Timer/Counter1 Overflow Interrupt Enable
    	__IO u8 m_OCIE0 : 1;        // Timer/Counter1 Output Compare Match Interrupt Enable
    	__IO u8 m_TOIE1 : 1;        // Timer/Counter1 Overflow Interrupt Enable
    	__IO u8 m_OCIE1B: 1;        // Timer/Counter1 Output Compare Match Interrupt Enable
    	__IO u8 m_OCIE1A: 1;        // Timer/Counter1 Output Compare Match Interrupt Enable
    	__IO u8 m_TICIE1: 1;        // Timer/Counter1, Input Capture Interrupt Enable
    	__IO u8 m_TOIE2 : 1;        // Timer/Counter2 Overflow Interrupt Enable
    	__IO u8 m_OCIE2 : 1;        // Timer/Counter2 Output Compare Match Interrupt Enable
    }sBits;
}TIMSK_type;   // Timer/Counter Interrupt Mask Register

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/** Timer/Counter 0 Register **/
#define S_TMR2          ((GPTMR2_type* const)0x42U)
#define ASSR            (*(volatile u8* const)0x42U)
#define OCR2            (*(volatile u8* const)0x43U)
#define TCNT2           (*(volatile u8* const)0x44U)
#define TCCR2           (*(volatile u8* const)0x45U)

/** Timer/Counter 1 Register **/
#define S_TMR1          ((GPTMR1_type* const)0x46U)
#define ICR1L           (*(volatile u8* const)0x46U)
#define ICR1H           (*(volatile u8* const)0x47U)
#define OCR1BL          (*(volatile u8* const)0x48U)
#define OCR1BH          (*(volatile u8* const)0x49U)
#define OCR1AL          (*(volatile u8* const)0x4AU)
#define OCR1AH          (*(volatile u8* const)0x4BU)
#define TCNT1L          (*(volatile u8* const)0x4CU)
#define TCNT1H          (*(volatile u8* const)0x4DU)
#define TCCR1B          (*(volatile u8* const)0x4EU)
#define TCCR1A          (*(volatile u8* const)0x4FU)

/** Special Function I/O Register **/
#define S_SFIOR         ((SFIOR_type* const)0x50U)
#define SFIOR           (*(volatile u8* const)0x50U)

/** Timer/Counter 0 Register **/
#define S_TMR0          ((GPTMR0_type* const)0x52U)
#define TCNT0           (*(volatile u8* const)0x52U)
#define TCCR0           (*(volatile u8* const)0x53U)

#define OCR0            (*(volatile u8* const)0x5CU)

/** Timer/Counter Interrupt Flag Register **/
#define S_TIFR          ((TIFR_type* const)0x58U)
#define TIFR            (*(volatile u8* const)0x58U)

/** Timer/Counter Interrupt Mask Register **/
#define S_TIMSK         ((TIMSK_type* const)0x59U)
#define TIMSK           (*(volatile u8* const)0x59U)

/* ************************************************************************** */

#define TMRx_WGMx0_MASK		0x0u
#define TMRx_WGMx1_MASK		0x1u
#define TMRx_WGMx2_MASK		0x2u
#define TMRx_WGMx3_MASK		0x3u

#define TMR_EXT0_PORT		B
#define TMR_EXT0_PIN		GPIO_TMR_EXT0_IN
#define TMR_EXT1_PORT		B
#define TMR_EXT1_PIN		GPIO_TMR_EXT1_IN

#define TMR_OC0_PORT		B
#define TMR_OC0_PIN			GPIO_TMR_OC0

#define TMR_OC2_PORT		D
#define TMR_OC2_PIN			GPIO_TMR_OC2

#define TMR_OSC1_PORT		C
#define TMR_OSC1_PIN		GPIO_TMR_OSC1
#define TMR_OSC2_PORT		C
#define TMR_OSC2_PIN		GPIO_TMR_OSC2

#define TMR_ICP1_PORT		D
#define TMR_ICP1_PIN		GPIO_TMR_ICP1
#define TMR_OC1A_PORT		D
#define TMR_OC1A_PIN		GPIO_TMR_OC1A
#define TMR_OC1B_PORT		D
#define TMR_OC1B_PIN		GPIO_TMR_OC1B

#define TMR_u8MAX			(LBTY_u8MAX + 1u)
#define TMR_u16MAX			(LBTY_u16MAX + 1u)

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* TMR_PRIV_H_ */
/*************************** E N D (TMR_priv.h) ******************************/
