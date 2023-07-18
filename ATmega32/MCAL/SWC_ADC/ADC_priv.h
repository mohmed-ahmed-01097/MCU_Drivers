/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : ADC_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 27, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef ADC_PRIV_H_
#define ADC_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/** @brief : Type define of  ADC Pin Number enum                              */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef enum {
#ifdef ADC_CH0
		ADC_0 = (u8)0u			/*!< ADC0 pin */
#endif
#ifdef ADC_CH1
		, ADC_1					/*!< ADC1 pin */
#endif
#ifdef ADC_CH2
		, ADC_2					/*!< ADC2 pin */
#endif
#ifdef ADC_CH3
		, ADC_3					/*!< ADC3 pin */
#endif
#ifdef ADC_CH4
		, ADC_4					/*!< ADC4 pin */
#endif
#ifdef ADC_CH5
		, ADC_5					/*!< ADC5 pin */
#endif
#ifdef ADC_CH6
		, ADC_6					/*!< ADC6 pin */
#endif
#ifdef ADC_CH7
		, ADC_7					/*!< ADC7 pin */
#endif
		, ADC_Num				/*!< ADC Max pin Number */
}ADC_tenuPinNum;

/*************************************************************************/

/** @brief : Type define of Union bit field of "ADC Control and Status Reg A" */
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8 m_ADPS : 3;			/*!< ADC Prescaler Select Bits */
    	__IO u8 m_ADIE : 1;			/*!< ADC Interrupt Enable */
    	__IO u8 m_ADIF : 1;			/*!< ADC Interrupt Flag */
    	__IO u8 m_ADATE: 1;			/*!< ADC Auto Trigger Enable */
    	__IO u8 m_ADSC : 1;			/*!< ADC Start Conversion */
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
    	__IO u8 m_ADLAR: 1;			/*!< ADC Left Adjust Result */
    	__IO u8 m_REFS : 2;			/*!< Reference Selection Bits */
    }sBits;
}ADMUX_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "Analog Comparator Control and Status"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8        : 7;			/*!< Reversed */
        __IO u8 m_ACD  : 1;			/*!< Analog Comparator Disable */
    }sBits;
}ACSR_type;

/*************************************************************************/

/** @brief : Analog to Digital Converter Registers                            */
/** <b>Type</b> : Struct <b>Unit</b> : None                                   */
typedef struct{
#if ADC_ADJUSTMENT
    __I  u16                : 6;	/*!< Reversed */
    __I  u16          m_ADC : 10;	/*!< ADC Read Data */
#else
    __I  u16          m_ADC : 10;	/*!< ADC Read Data */
    __I  u16                : 6;	/*!< Reversed */
#endif
    __IO ADCSRA_type  m_ADCSRA;		/*!< ADC Control and Status Reg A */
    __IO ADMUX_type   m_ADMUX;		/*!< ADC Multiplexer Selection Reg */
    __IO ACSR_type    m_ACSR;		/*!< Analog Comparator Control and Status */
}ADC_type;

/*************************************************************************/

/** @brief : Type define of Union bit field of "Special Function I/O Register"*/
/** <b>Type</b> : Union <b>Unit</b> : None                                    */
typedef union{
    u8 u_Reg;						/*!< Byte */
    struct {
    	__IO u8        : 3;			/*!< Reversed */
    	__IO u8 m_ACME : 1;     	/*!< Analog Comparator Multiplexer Enable */
    	__IO u8        : 1;			/*!< Reversed */
    	__IO u8 m_ADTS : 3;     	/*!< ADC Auto Trigger Source */
    }sBits;
}SFIOR_type;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define IS_CHANNEL(channel)		((channel >= ADC0) && (channel <= ADC7))

#define ADC_PORT				A

#define ADC_MAX					1023u
#define ADC_VBG_1V22			1.22f

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


#endif /* ADC_PRIV_H_ */
/*************************** E N D (ADC_priv.h) ******************************/
