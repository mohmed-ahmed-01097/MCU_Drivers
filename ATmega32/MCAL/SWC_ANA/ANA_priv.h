/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ANA_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : May 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef ANA_PRIV_H_
#define ANA_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_ADPS : 3;   // ADC Prescaler Select Bits
    	__IO u8 m_ADIE : 1;   // ADC Interrupt Enable
    	__IO u8 m_ADIF : 1;   // ADC Interrupt Flag
    	__IO u8 m_ADATE: 1;   // ADC Auto Trigger Enable
    	__IO u8 m_ADSC : 1;   // ADC Start Conversion
    	__IO u8 m_ADEN : 1;   // ADC Enable
    }sBits;
}ADCSRA_type; // ADC Control and Status Register A

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_MUX  : 5;   // Analog Channel and Gain Selection Bits
    	__IO u8 m_ADLAR: 1;   // ADC Left Adjust Result
    	__IO u8 m_REFS : 2;   // Reference Selection Bits
    }sBits;
}ADMUX_type; // ADC Multiplexer Selection Register

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8 m_ACIS : 2;   // Analog Comparator Interrupt Mode Select
    	__IO u8 m_ACIC : 1;   // Analog Comparator Input Capture Enable
    	__IO u8 m_ACIE : 1;   // Analog Comparator Interrupt Enable
    	__IO u8 m_ACI  : 1;   // Analog Comparator Interrupt Flag
        __I  u8 m_ACO  : 1;   // Analog Comparator Output
        __IO u8 m_ACBG : 1;   // Analog Comparator Bandgap Select
        __IO u8 m_ACD  : 1;   // Analog Comparator Disable
    }sBits;
}ACSR_type; // Analog Comparator Control and Status

/*************************************************************************/

typedef struct{
#if ADC_ADJUSTMENT
    __I  u16                : 6;
    __I  u16          m_ADC : 10;
#else
    __I  u16          m_ADC : 10;
    __I  u16                : 6;
#endif
    __IO ADCSRA_type  m_ADCSRA;
    __IO ADMUX_type   m_ADMUX;
    __IO ACSR_type    m_ACSR;
}ADC_type;

/*************************************************************************/

typedef union{
    u8 u_Reg;
    struct {
    	__IO u8        : 3;
    	__IO u8 m_ACME : 1;        // Analog Comparator Multiplexer Enable
    	__IO u8        : 1;
    	__IO u8 m_ADTS : 3;        // ADC Auto Trigger Source
    }sBits;
}SFIOR_type;   // Special Function I/O Register

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define ANA_PORT					B
#define ANA_PIN_AIN0				GPIO_AIN0
#define ANA_PIN_AIN1				GPIO_AIN1

/** Analog Digital Converter **/
#define S_ADC           ((ADC_type* const)0x24U)
#define ADCL            (*(volatile u8* const)0x24U)
#define ADCH            (*(volatile u8* const)0x25U)
#define ADCSRA          (*(volatile u8* const)0x26U)
#define ADMUX           (*(volatile u8* const)0x27U)
#define ACSR            (*(volatile u8* const)0x28U)

/** Special Function I/O Register **/
#define S_SFIOR         ((SFIOR_type* const)0x50U)
#define SFIOR           (*(volatile u8* const)0x50U)

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* ANA_PRIV_H_ */
/*************************** E N D (ANA_priv.h) ******************************/
