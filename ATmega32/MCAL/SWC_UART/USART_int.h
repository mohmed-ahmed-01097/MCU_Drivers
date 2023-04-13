/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : USART_int.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 10, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef USART_INT_H_
#define USART_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	USART_Asynchronous = (u8)0u,
	USART_Synchronous,
}USART_tenumModeSelect;

typedef enum{
	USART_Transmit_Rising_Receive_Falling = (u8)0u,
	USART_Transmit_Falling_Receive_Rising,
}USART_tenumClockPolarity;

typedef enum{
	USART_5_bit = (u8)0u,
	USART_6_bit,
	USART_7_bit,
	USART_8_bit,
	USART_9_bit = (u8)7u,
}USART_tenumCharSize;

typedef enum{
	USART_Parity_Disable = (u8)0u,
	Reserved,
	USART_Parity_Even,
	USART_Parity_Odd,
}USART_tenumParityMode;

typedef enum{
	USART_Stop_1_bit = (u8)0u,
	USART_Stop_2_bit,
}USART_tenumStopBit;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

//#define USART_vidSetChar		USART_vidSetTransmit
//#define USART_vidGetChar		USART_vidGetTransmit

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void UART_vidInit(void);

void USART_vidTransmitterEnable(void);
void USART_vidTransmitterDisable(void);
void USART_vidReceiverEnable(void);
void USART_vidReceiverDisable(void);

LBTY_tenuErrorStatus USART_u8SetStopBit(USART_tenumStopBit u8Stop);
LBTY_tenuErrorStatus USART_u8SetParityMode(USART_tenumParityMode u8Parity);
LBTY_tenuErrorStatus USART_u8SetCharSize(USART_tenumCharSize u8CharSize);
LBTY_tenuErrorStatus USART_u8SetBuadRate(u32 u32BuadRate);

void USART_vidSetTransmit(u16 u16Transmit);
void USART_vidGetTransmit(u16* pu16Receive);
void USART_vidFlush(void);

void USART_vidSetChar(u8 u8Char);
void USART_vidGetChar(u8* pu8Char);

void USART_vidSetStr(u8* pu8Transmit);
void USART_vidGetStr(u8* pu8Receive);

u8 USART_u8Available(void);
u8 USART_u8Get_UBRRH(void);
u8 USART_u8Get_UCSRC(void);

#endif /* USART_INT_H_ */
/*************************** E N D (USART_int.h) ******************************/
