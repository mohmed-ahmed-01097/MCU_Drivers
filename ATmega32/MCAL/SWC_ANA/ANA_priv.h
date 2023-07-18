/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ANA_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : May 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef ANA_PRIV_H_
#define ANA_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of Union bit field of "ADC Control and Status Reg A" */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__I  u8        : 7;			/*!< Reversed */
    	__IO u8 m_ADEN : 1;			/*!< ADC Enable */
    }sBits;
}ADCSRA_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "ADC Multiplexer Selection Reg"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_MUX  : 5;			/*!< Analog Channel and Gain Selection Bits */
    	__IO u8        : 3;			/*!< Reversed */
    }sBits;
}ADMUX_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "Analog Comparator Control and Status"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_ACIS : 2;			/*!< Analog Comparator Interrupt Mode Select */
    	__IO u8 m_ACIC : 1;			/*!< Analog Comparator Input Capture Enable */
    	__IO u8 m_ACIE : 1;			/*!< Analog Comparator Interrupt Enable */
    	__IO u8 m_ACI  : 1;			/*!< Analog Comparator Interrupt Flag */
        __I  u8 m_ACO  : 1;			/*!< Analog Comparator Output */
        __IO u8 m_ACBG : 1;			/*!< Analog Comparator Bandgap Select */
        __IO u8 m_ACD  : 1;			/*!< Analog Comparator Disable */
    }sBits;
}ACSR_type;

/*************************************************************************/

/** @brief : Analog Comparator Registers                                      */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
    __IO ADCSRA_type  m_ADCSRA;		/*!< ADC Control and Status Reg A */
    __IO ADMUX_type   m_ADMUX;		/*!< ADC Multiplexer Selection Reg */
    __IO ACSR_type    m_ACSR;		/*!< Analog Comparator Control and Status Reg */
}ADC_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "Special Function I/O Register"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8        : 3;			/*!< Reversed */
    	__IO u8 m_ACME : 1;     	/*!< Analog Comparator Multiplexer Enable */
    	__IO u8        : 4;			/*!< Reversed */
    }sBits;
}SFIOR_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define ADC_PORT					A
#define ANA_PORT					B
#define ANA_PIN_AIN0				GPIO_AIN0
#define ANA_PIN_AIN1				GPIO_AIN1

/** Analog Digital Converter **/
#define S_ADC           ((ADC_type* const)0x26U)
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
