/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : USART_int.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
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
	USART_Parity_Reserved,
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

/********************************************************************************************************************/

/** @brief : type define of structure for UART/USART Configuration            */
/** <b>Type</b> : struct <b>Unit</b> : None                                   */
typedef struct{
/* HW Config */
	USART_tenumModeSelect	 m_Mode;				/*!< Sync or Async Mode */
	USART_tenumClockPolarity m_Polarity;			/*!< Clock Polarity */
	USART_tenumSpeed		 m_Speed;				/*!< Speed Gain */
/* frame */
	USART_tenumBuadRate		 m_BuadRate;			/*!< BaudRate Register Value */
	USART_tenumCharSize		 m_Size;				/*!< Data Register Size */
	USART_tenumParityMode	 m_Parity;				/*!< Parity Bit */
	USART_tenumStopBit		 m_Stop;				/*!< Stop Bit */
/* TX/RX Status */
	LBTY_tenuFlagStatus		 m_TXEN;				/*!< TX Enable Flag */
	LBTY_tenuFlagStatus		 m_RXEN;				/*!< RX Enable Flag */
/* TX/RX Interrupt */
	LBTY_tenuFlagStatus		 m_TXIE;				/*!< TX Interrupt Enable Flag */
	LBTY_tenuFlagStatus		 m_RXIE;				/*!< RX Interrupt Enable Flag */
	LBTY_tenuFlagStatus		 m_Empty;			/*!< EmptyInterrupt Enable Flag */
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

extern void USART_vidSetConfig(USART_tstrConfiguration const* const pstrConfig);
extern void USART_vidResetConfig(USART_tstrConfiguration* const pstrConfig);

extern void UART_vidInit(void);

extern void USART_vidTransmitterEnable(void);
extern void USART_vidTransmitterDisable(void);
extern void USART_vidReceiverEnable(void);
extern void USART_vidReceiverDisable(void);

extern LBTY_tenuErrorStatus USART_u8SetBuadRate(USART_tenumBuadRate u32BuadRate);
extern LBTY_tenuErrorStatus USART_u8SetCharSize(USART_tenumCharSize u8CharSize);
extern LBTY_tenuErrorStatus USART_u8SetParityMode(USART_tenumParityMode u8Parity);
extern LBTY_tenuErrorStatus USART_u8SetStopBit(USART_tenumStopBit u8Stop);

/********************************************************************************************************************/

extern u8 USART_u8Available(void);
extern void USART_vidFlush(void);

extern LBTY_tenuErrorStatus USART_u8SetTransmit(void* pvidTransmit);
extern LBTY_tenuErrorStatus USART_u8GetTransmit(void* pvidTransmit);

extern void USART_vidSetChar(u8 u8Char);
extern void USART_vidGetChar(u8* pu8Char);

extern void USART_vidSetStrLine(u8* pu8Transmit);
extern void USART_vidSetStr(u8* pu8Transmit);
extern void USART_vidGetStr(u8* pu8Receive);

extern LBTY_tenuErrorStatus USART_u8SendBuffer(u8* pu8Data, u8 u8Size);
extern LBTY_tenuErrorStatus USART_u8ReceiveBuffer(u8* pu8Data, u8 u8Size);

/********************************************************************************************************************/

extern void USART_vidEnableReceiveCompleteINT(void);
extern void USART_vidEnableTransmitCompleteINT(void);
extern void USART_vidEnableDataRegEmptyINT(void);

extern void USART_vidDisableReceiveCompleteINT(void);
extern void USART_vidDisableTransmitCompleteINT(void);
extern void USART_vidDisableDataRegEmptyINT(void);

extern void USART_vidSetCallBack_Empty(void (*pCallBack)(void));
extern void USART_vidSetCallBack_TX   (void (*pCallBack)(void));
extern void USART_vidSetCallBack_RX   (void (*pCallBack)(void));

#endif /* USART_INT_H_ */
/*************************** E N D (USART_int.h) ******************************/
