/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : USART_priv.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 10, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef USART_PRIV_H_
#define USART_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	USART_UBRRH_Reg = (u8)0u,
	USART_UCSRC_Reg,
}USART_tenumRegSelect;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define USART_UCSZ0_BIT				0u
#define USART_UCSZ1_BIT				1u
#define USART_UCSZ2_BIT				2u

#if  F_CPU == 1000000UL

#define USART_BUAD_RATE_2400		25u
#define USART_BUAD_RATE_4800		12u
#define USART_BUAD_RATE_9600		6u
#define USART_BUAD_RATE_14400		3u
#define USART_BUAD_RATE_19200		2u
#define USART_BUAD_RATE_28800		1u
#define USART_BUAD_RATE_38400		1u
#define USART_BUAD_RATE_57600		0u

#elif  F_CPU == 4000000UL

#define USART_BUAD_RATE_2400		103u
#define USART_BUAD_RATE_4800		51u
#define USART_BUAD_RATE_9600		25u
#define USART_BUAD_RATE_14400		16u
#define USART_BUAD_RATE_19200		12u
#define USART_BUAD_RATE_28800		8u
#define USART_BUAD_RATE_38400		6u
#define USART_BUAD_RATE_57600		3u
#define USART_BUAD_RATE_76600		2u
#define USART_BUAD_RATE_115200		1u
#define USART_BUAD_RATE_230400		0u
#define USART_BUAD_RATE_250000		0u

#elif F_CPU == 8000000UL

#define USART_BUAD_RATE_2400		207u
#define USART_BUAD_RATE_4800		103u
#define USART_BUAD_RATE_9600		51u
#define USART_BUAD_RATE_14400		34u
#define USART_BUAD_RATE_19200		25u
#define USART_BUAD_RATE_28800		16u
#define USART_BUAD_RATE_38400		12u
#define USART_BUAD_RATE_57600		8u
#define USART_BUAD_RATE_76600		6u
#define USART_BUAD_RATE_115200		3u
#define USART_BUAD_RATE_230400		1u
#define USART_BUAD_RATE_250000		1u
#define USART_BUAD_RATE_500000		0u

#elif  F_CPU == 16000000UL

#define USART_BUAD_RATE_2400		416u
#define USART_BUAD_RATE_4800		207u
#define USART_BUAD_RATE_9600		103u
#define USART_BUAD_RATE_14400		68u
#define USART_BUAD_RATE_19200		51u
#define USART_BUAD_RATE_28800		34u
#define USART_BUAD_RATE_38400		25u
#define USART_BUAD_RATE_57600		16u
#define USART_BUAD_RATE_76600		12u
#define USART_BUAD_RATE_115200		8u
#define USART_BUAD_RATE_230400		3u
#define USART_BUAD_RATE_250000		3u
#define USART_BUAD_RATE_500000		1u
#define USART_BUAD_RATE_1000000		0u

#elif  F_CPU == 20000000UL

#define USART_BUAD_RATE_2400		520u
#define USART_BUAD_RATE_4800		259u
#define USART_BUAD_RATE_9600		129u
#define USART_BUAD_RATE_14400		86u
#define USART_BUAD_RATE_19200		64u
#define USART_BUAD_RATE_28800		42u
#define USART_BUAD_RATE_38400		32u
#define USART_BUAD_RATE_57600		21u
#define USART_BUAD_RATE_76600		15u
#define USART_BUAD_RATE_115200		10u
#define USART_BUAD_RATE_230400		4u
#define USART_BUAD_RATE_250000		4u

#endif

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

typedef enum{
	USART_BuadRate_2400 = USART_BUAD_RATE_2400,
	USART_BuadRate_4800 = USART_BUAD_RATE_4800,
	USART_BuadRate_9600 = USART_BUAD_RATE_9600,
	USART_BuadRate_14400 = USART_BUAD_RATE_14400,
	USART_BuadRate_19200 = USART_BUAD_RATE_19200,
	USART_BuadRate_28800 = USART_BUAD_RATE_28800,
	USART_BuadRate_38400 = USART_BUAD_RATE_38400,
	USART_BuadRate_57600 = USART_BUAD_RATE_57600,
#ifdef USART_BUAD_RATE_76600
	USART_BuadRate_76600 = USART_BUAD_RATE_76600,
#endif
#ifdef USART_BUAD_RATE_115200
	USART_BuadRate_115200 = USART_BUAD_RATE_115200,
#endif
#ifdef USART_BUAD_RATE_230400
	USART_BuadRate_230400 = USART_BUAD_RATE_230400,
#endif
#ifdef USART_BUAD_RATE_250000
	USART_BuadRate_250000 = USART_BUAD_RATE_250000,
#endif
#ifdef USART_BUAD_RATE_500000
	USART_BuadRate_500000 = USART_BUAD_RATE_500000,
#endif
#ifdef USART_BUAD_RATE_1000000
	USART_BuadRate_1000000 = USART_BUAD_RATE_1000000,
#endif
}USART_tenumBuadRate;

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

static inline u8 USART_u8GetReceiveComplete(void) {return S_USART->m_UCSRA.sBits.m_RXC;}
static inline u8 USART_u8GetTransmitComplete(void){return S_USART->m_UCSRA.sBits.m_TXC;}
static inline u8 USART_u8GetDataRegEmpty(void)    {return S_USART->m_UCSRA.sBits.m_UDRE;}

static inline u8 USART_u8GetFrameError(void) {return S_USART->m_UCSRA.sBits.m_FE;}
static inline u8 USART_u8GetDataOverRun(void){return S_USART->m_UCSRA.sBits.m_DOR;}
static inline u8 USART_u8GetParityError(void){return S_USART->m_UCSRA.sBits.m_PE;}

static inline void USART_vidEnableReceiveCompleteINT(void) {S_USART->m_UCSRB.sBits.m_RXCIE = LBTY_SET;}
static inline void USART_vidEnableTransmitCompleteINT(void){S_USART->m_UCSRB.sBits.m_TXCIE = LBTY_SET;}
static inline void USART_vidEnableDataRegEmptyINT(void)    {S_USART->m_UCSRB.sBits.m_UDRIE = LBTY_SET;}

static inline void USART_vidDisableReceiveCompleteINT(void) {S_USART->m_UCSRB.sBits.m_RXCIE = LBTY_RESET;}
static inline void USART_vidDisableTransmitCompleteINT(void){S_USART->m_UCSRB.sBits.m_TXCIE = LBTY_RESET;}
static inline void USART_vidDisableDataRegEmptyINT(void)    {S_USART->m_UCSRB.sBits.m_UDRIE = LBTY_RESET;}


#endif /* USART_PRIV_H_ */
/*************************** E N D (USART_priv.h) ******************************/
