/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : USART_int.h												  */
/* Author      : MAAM														  */
/* Version     : v01														  */
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
	USART_Speed_x1 = (u8)0u,
	USART_Speed_x2,
}USART_tenumSpeed;

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

typedef enum{
	USART_BuadRate_1200 	= 1200u,
	USART_BuadRate_2400 	= 2400u,
	USART_BuadRate_4800 	= 4800u,
	USART_BuadRate_9600 	= 9600u,
	USART_BuadRate_14400 	= 14400u,
	USART_BuadRate_19200 	= 19200u,
	USART_BuadRate_28800 	= 28800u,
	USART_BuadRate_38400 	= 38400u,
	USART_BuadRate_57600 	= 57600u,
	USART_BuadRate_76600 	= 76600u,
	USART_BuadRate_115200 	= 115200u,
	USART_BuadRate_230400 	= 230400u,
	USART_BuadRate_250000 	= 250000u,
	USART_BuadRate_500000 	= 500000u,
	USART_BuadRate_1000000	= 1000000u,
}USART_tenumBuadRate;

typedef struct{
//	USART_tenumModeSelect	m_Mode;
//	USART_tenumSpeed		m_Speed;
//	USART_tenumClockPolarity m_Polarity;
/** frame **/
	USART_tenumBuadRate		m_BuadRate;
	USART_tenumCharSize		m_Size;
	USART_tenumParityMode	m_Parity;
	USART_tenumStopBit		m_Stop;
/** TX/RX Status **/
	LBTY_tenuFlagStatus		m_TXEN;
	LBTY_tenuFlagStatus		m_RXEN;

	LBTY_tenuFlagStatus		m_TXIE;
	LBTY_tenuFlagStatus		m_RXIE;
	LBTY_tenuFlagStatus		m_Empty;
}USART_tstrConfiguration;

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

void USART_vidSetConfig(USART_tstrConfiguration const* const pstrConfig);
void USART_vidResetConfig(USART_tstrConfiguration* const pstrConfig);

void UART_vidInit(void);

void USART_vidTransmitterEnable(void);
void USART_vidTransmitterDisable(void);
void USART_vidReceiverEnable(void);
void USART_vidReceiverDisable(void);

u8 USART_u8Get_UBRRH(void);
u8 USART_u8Get_UCSRC(void);

LBTY_tenuErrorStatus USART_u8SetStopBit(USART_tenumStopBit u8Stop);
LBTY_tenuErrorStatus USART_u8SetParityMode(USART_tenumParityMode u8Parity);
LBTY_tenuErrorStatus USART_u8SetCharSize(USART_tenumCharSize u8CharSize);
LBTY_tenuErrorStatus USART_u8SetBuadRate(USART_tenumBuadRate u32BuadRate);

/********************************************************************************************************************/

u8 USART_u8Available(void);
void USART_vidFlush(void);

LBTY_tenuErrorStatus USART_u8SetTransmit(u16* pu16Transmit);
LBTY_tenuErrorStatus USART_u8GetTransmit(u16* pu16Receive);

void USART_vidSetChar(u8 u8Char);
void USART_vidGetChar(u8* pu8Char);

void USART_vidSetStr(u8* pu8Transmit);
void USART_vidGetStr(u8* pu8Receive);

LBTY_tenuErrorStatus USART_u8SendBuffer(u8* pu8Data, u8 u8Size);
LBTY_tenuErrorStatus USART_u8ReceiveBuffer(u8* pu8Data, u8 u8Size);

/********************************************************************************************************************/

void USART_vidEnableReceiveCompleteINT(void);
void USART_vidEnableTransmitCompleteINT(void);
void USART_vidEnableDataRegEmptyINT(void);

void USART_vidDisableReceiveCompleteINT(void);
void USART_vidDisableTransmitCompleteINT(void);
void USART_vidDisableDataRegEmptyINT(void);

void USART_vidSetCallBack_Empty(void (*pCallBack)(void));
void USART_vidSetCallBack_TX   (void (*pCallBack)(void));
void USART_vidSetCallBack_RX   (void (*pCallBack)(void));

#endif /* USART_INT_H_ */
/*************************** E N D (USART_int.h) ******************************/
