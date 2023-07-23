/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : UART_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 9, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "USART_int.h"
#include "USART_cfg.h"
#include "USART_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

static volatile UCSRC_type strUCSRC;

static void (*pvidfunc_Empty_CallBak)(void) = INTP_vidCallBack;
static void (*pvidfunc_Tx_CallBak)(void)    = INTP_vidCallBack;
static void (*pvidfunc_Rx_CallBak)(void)    = INTP_vidCallBack;

static USART_tstrBuffer strTX_GLB = {								/*!< TX Buffer */
	.m_pu8Data 	= LBTY_NULL,
	.m_u8Size	= LBTY_u8ZERO,
	.m_u8Idx 	= LBTY_u8ZERO,
	.m_u8Status	= TX_IDLE,
};
static USART_tstrBuffer strRX_GLB = {								/*!< RX Buffer */
	.m_pu8Data 	= LBTY_NULL,
	.m_u8Size	= LBTY_u8ZERO,
	.m_u8Idx 	= LBTY_u8ZERO,
	.m_u8Status	= RX_IDLE,
};

static volatile USART_tstrConfiguration strUSART_Config_GLB = {		/*!< General Config */
	.m_Mode 	= USART_OPERATION_MODE,
	.m_Polarity	= USART_OPERATION_POLARITY,
	.m_Speed 	= USART_OPERATION_SPEED,
	.m_BuadRate = USART_BUAD_RATE_INIT,
	.m_Size 	= USART_CHAR_SIZE_INIT,
	.m_Parity 	= USART_PARITY_BIT_INIT,
	.m_Stop 	= USART_STOP_BIT_INIT,
	.m_TXEN 	= USART_TRANSMIT_INIT,
	.m_RXEN 	= USART_RECEIVE_INIT,
	.m_TXIE		= USART_TRANSMIT_COMPLETE_INT,
	.m_RXIE 	= USART_RECEIVE_COMPLETE_INT,
	.m_Empty 	= USART_DATA_REG_EMPTY_INT,
};

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void USART_vidSetConfig(USART_tstrConfiguration const* const pstrConfig){
	if(pstrConfig != LBTY_NULL){
		strUSART_Config_GLB = *pstrConfig;
	}
	UART_vidInit();
}

void USART_vidResetConfig(USART_tstrConfiguration* const pstrConfig){
	strUSART_Config_GLB.m_Mode 		= USART_OPERATION_MODE;
	strUSART_Config_GLB.m_Polarity 	= USART_OPERATION_POLARITY;
	strUSART_Config_GLB.m_Speed 	= USART_OPERATION_SPEED;
	strUSART_Config_GLB.m_BuadRate 	= USART_BUAD_RATE_INIT;
	strUSART_Config_GLB.m_Size 		= USART_CHAR_SIZE_INIT;
	strUSART_Config_GLB.m_Parity 	= USART_PARITY_BIT_INIT;
	strUSART_Config_GLB.m_Stop 		= USART_STOP_BIT_INIT;
	strUSART_Config_GLB.m_TXEN 		= USART_TRANSMIT_INIT;
	strUSART_Config_GLB.m_RXEN 		= USART_RECEIVE_INIT;
	strUSART_Config_GLB.m_TXIE		= USART_TRANSMIT_COMPLETE_INT;
	strUSART_Config_GLB.m_RXIE 		= USART_RECEIVE_COMPLETE_INT;
	strUSART_Config_GLB.m_Empty 	= USART_DATA_REG_EMPTY_INT;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strUSART_Config_GLB;
	}
	UART_vidInit();
}

void UART_vidInit(void){

	strUCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
	strUCSRC.sUCSRC.m_UMSEL = strUSART_Config_GLB.m_Mode;
	strUCSRC.sUCSRC.m_UCPOL = strUSART_Config_GLB.m_Polarity;
	S_USART->m_UCSRC = strUCSRC.u_Reg;

	S_USART->m_UCSRA.sBits.m_MPCM = USART_OPERATION_MULTI_PROCESSOR;
	S_USART->m_UCSRA.sBits.m_U2X  = strUSART_Config_GLB.m_Speed;

	USART_u8SetBuadRate  (strUSART_Config_GLB.m_BuadRate);
	USART_u8SetCharSize  (strUSART_Config_GLB.m_Size);
	USART_u8SetParityMode(strUSART_Config_GLB.m_Parity);
	USART_u8SetStopBit   (strUSART_Config_GLB.m_Stop);

	strUCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
	if(strUCSRC.sUCSRC.m_UMSEL == USART_Synchronous){
		GPIO_u8SetPinDirection(USART_XCK_PORT, USART_XCK_PIN, PIN_OUTPUT);
	}
	GPIO_u8SetPinDirection(USART_PORT    , USART_TX_PIN , PIN_OUTPUT);
	GPIO_u8SetPinDirection(USART_XCK_PORT, USART_RX_PIN , PIN_INPUT );

	S_USART->m_UCSRB.sBits.m_UDRIE = strUSART_Config_GLB.m_Empty;
	S_USART->m_UCSRB.sBits.m_TXCIE = strUSART_Config_GLB.m_TXIE;
	S_USART->m_UCSRB.sBits.m_RXCIE = strUSART_Config_GLB.m_RXIE;

	S_USART->m_UCSRB.sBits.m_TXEN  = strUSART_Config_GLB.m_TXEN;
	S_USART->m_UCSRB.sBits.m_RXEN  = strUSART_Config_GLB.m_RXEN;
}

void USART_vidTransmitterEnable(void){
	S_USART->m_UCSRB.sBits.m_TXEN = strUSART_Config_GLB.m_TXEN = LBTY_SET;
}
void USART_vidTransmitterDisable(void){
	S_USART->m_UCSRB.sBits.m_TXEN = strUSART_Config_GLB.m_TXEN = LBTY_RESET;
}
void USART_vidReceiverEnable(void){
	S_USART->m_UCSRB.sBits.m_RXEN = strUSART_Config_GLB.m_RXEN = LBTY_SET;
}
void USART_vidReceiverDisable(void){
	S_USART->m_UCSRB.sBits.m_RXEN = strUSART_Config_GLB.m_RXEN = LBTY_RESET;
}

LBTY_tenuErrorStatus USART_u8SetBuadRate(USART_tenumBuadRate u32BuadRate){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u16 u16UBRR = LBTY_u16ZERO;

	switch(strUCSRC.sUCSRC.m_UMSEL){
		case USART_Asynchronous:
			switch(S_USART->m_UCSRA.sBits.m_U2X){
				case USART_Speed_x1:
					u16UBRR = (u16)(F_CPU / (16.0f * (u32)u32BuadRate)) - 1;
					break;
				case USART_Speed_x2:
					u16UBRR = (u16)(F_CPU / (8.0f  * (u32)u32BuadRate)) - 1;
					break;
				default:
					u8RetErrorState = LBTY_NOK;
			}
			break;
		case USART_Synchronous:
			u16UBRR = (u16)(USART_OPERATION_FREQ / (2.0f * (u32)u32BuadRate)) - 1;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}
	if(u8RetErrorState == LBTY_OK){
		strUSART_Config_GLB.m_BuadRate = u32BuadRate;

		strUCSRC.sUBRRH.m_URSEL = USART_UBRRH_Reg;
		strUCSRC.sUBRRH.m_UBRR = GET_NIB(u16UBRR, 8);

		S_USART->m_UCSRC = strUCSRC.u_Reg;
		S_USART->m_UBRRL = GET_BYTE(u16UBRR, 0);
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus USART_u8SetCharSize(USART_tenumCharSize u8CharSize){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8CharSize){
		case USART_5_bit:
		case USART_6_bit:
		case USART_7_bit:
		case USART_8_bit:
		case USART_9_bit:
			strUCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
			strUCSRC.sUCSRC.m_UCSZ0 = GET_BIT(u8CharSize, USART_UCSZ0_BIT);
			strUCSRC.sUCSRC.m_UCSZ1 = GET_BIT(u8CharSize, USART_UCSZ1_BIT);
			S_USART->m_UCSRB.sBits.m_UCSZ2  = GET_BIT(u8CharSize, USART_UCSZ2_BIT);

			S_USART->m_UCSRC = strUCSRC.u_Reg;
			strUSART_Config_GLB.m_Size = u8CharSize;
			break;
		default:
			u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

LBTY_tenuErrorStatus USART_u8SetParityMode(USART_tenumParityMode u8Parity){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Parity){
		case USART_Parity_Disable:
		case USART_Parity_Even:
		case USART_Parity_Odd:
			strUCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
			strUCSRC.sUCSRC.m_UPM = strUSART_Config_GLB.m_Parity = u8Parity;
			S_USART->m_UCSRC = strUCSRC.u_Reg;
			break;
		default: u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

LBTY_tenuErrorStatus USART_u8SetStopBit(USART_tenumStopBit u8Stop){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Stop){
		case USART_Stop_1_bit:
		case USART_Stop_2_bit:
			strUCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
			strUCSRC.sUCSRC.m_USBS  = strUSART_Config_GLB.m_Stop = u8Stop;
			S_USART->m_UCSRC = strUCSRC.u_Reg;
			break;
		default: u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

LCTY_INLINE void USART_vidWaitDataRegEmpty(void)    {while(!(S_USART->m_UCSRA.sBits.m_UDRE));}
LCTY_INLINE void USART_vidWaitTransmitComplete(void){while(!(S_USART->m_UCSRA.sBits.m_TXC));}
LCTY_INLINE void USART_vidWaitReceiveComplete(void) {while(!(S_USART->m_UCSRA.sBits.m_RXC));}

LCTY_INLINE u8 USART_u8GetFrameError(void) {return S_USART->m_UCSRA.sBits.m_FE;}
LCTY_INLINE u8 USART_u8GetDataOverRun(void){return S_USART->m_UCSRA.sBits.m_DOR;}
LCTY_INLINE u8 USART_u8GetParityError(void){return S_USART->m_UCSRA.sBits.m_PE;}

u8 USART_u8Available(void){
	return S_USART->m_UCSRA.sBits.m_RXC;
}

void USART_vidFlush(void){
	u8 dummy;
	while(USART_u8Available()){
		dummy = S_USART->m_UDR;
	}
}

LBTY_tenuErrorStatus USART_u8SetTransmit(void* pvidTransmit){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pvidTransmit == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		USART_vidWaitDataRegEmpty();
		S_USART->m_UDR = *((u8*)pvidTransmit);
		if(strUSART_Config_GLB.m_Size == USART_9_bit){
			S_USART->m_UCSRB.sBits.m_TXB8 = GET_BIT(*((u16*)pvidTransmit), 8);
		}
	}
	return u8RetErrorState;
}
LBTY_tenuErrorStatus USART_u8GetTransmit(void* pvidTransmit){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pvidTransmit == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		USART_vidWaitReceiveComplete();
		if(USART_u8GetFrameError() || USART_u8GetDataOverRun() || USART_u8GetParityError()){
			if(strUSART_Config_GLB.m_Size == USART_9_bit){
				*((u16*)pvidTransmit) = LBTY_u16MAX;
			}else{
				*((u8*)pvidTransmit)  = LBTY_u8MAX;
			}
			u8RetErrorState = LBTY_NOK;
		}else{
			if(strUSART_Config_GLB.m_Size == USART_9_bit){
				*((u16*)pvidTransmit) = (u16)S_USART->m_UDR | (u16)(S_USART->m_UCSRB.sBits.m_TXB8 << 8) ;
			}else{
				*((u8*)pvidTransmit)  = S_USART->m_UDR;
			}
		}
	}
	return u8RetErrorState;
}

void USART_vidSetChar(u8 u8Char){
	USART_vidWaitDataRegEmpty();
	S_USART->m_UDR = u8Char;
}
void USART_vidGetChar(u8* pu8Char){
	USART_vidWaitReceiveComplete();
	*pu8Char = S_USART->m_UDR;
}

void USART_vidSetStrLine(u8* pu8Transmit){
	USART_vidSetStr((u8*)pu8Transmit);
	USART_vidSetStr((u8*)"\r\n");
}
void USART_vidSetStr(u8* pu8Transmit){
	while(*pu8Transmit){
		USART_vidSetChar(*(pu8Transmit++));
		USART_vidWaitTransmitComplete();
	}
}
void USART_vidGetStr(u8* pu8Receive){
	do{
		USART_vidGetChar(pu8Receive);
	}while(*pu8Receive++ != '\r');
	*pu8Receive = '\0';
}

LBTY_tenuErrorStatus USART_u8SendBuffer(u8* pu8Data, u8 u8Size){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu8Data == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(strTX_GLB.m_u8Status == TX_IDLE){
			strTX_GLB.m_pu8Data  = pu8Data;
			strTX_GLB.m_u8Size   = u8Size;
			strTX_GLB.m_u8Idx    = LBTY_u8ZERO;
			strTX_GLB.m_u8Status = TX_BUSY;

			if(S_USART->m_UCSRA.sBits.m_UDRE){
				S_USART->m_UDR = strTX_GLB.m_pu8Data[strTX_GLB.m_u8Idx++];
			}
			USART_vidEnableDataRegEmptyINT();
		}else{
			u8RetErrorState = LBTY_NOK;
		}
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus USART_u8ReceiveBuffer(u8* pu8Data, u8 u8Size){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(pu8Data == LBTY_NULL){
		u8RetErrorState = LBTY_NULL_POINTER;
	}else{
		if(strRX_GLB.m_u8Status == RX_IDLE){
			strRX_GLB.m_pu8Data  = pu8Data;
			strRX_GLB.m_u8Size   = u8Size;
			strRX_GLB.m_u8Idx    = LBTY_u8ZERO;
			strRX_GLB.m_u8Status = RX_BUSY;

			USART_vidEnableReceiveCompleteINT();
		}else{
			u8RetErrorState = LBTY_NOK;
		}
	}

	return u8RetErrorState;
}

/********************************************************************************************************************/

void USART_vidEnableReceiveCompleteINT(void) {S_USART->m_UCSRB.sBits.m_RXCIE = LBTY_SET;}
void USART_vidEnableTransmitCompleteINT(void){S_USART->m_UCSRB.sBits.m_TXCIE = LBTY_SET;}
void USART_vidEnableDataRegEmptyINT(void)    {S_USART->m_UCSRB.sBits.m_UDRIE = LBTY_SET;}

void USART_vidDisableReceiveCompleteINT(void) {S_USART->m_UCSRB.sBits.m_RXCIE = LBTY_RESET;}
void USART_vidDisableTransmitCompleteINT(void){S_USART->m_UCSRB.sBits.m_TXCIE = LBTY_RESET;}
void USART_vidDisableDataRegEmptyINT(void)    {S_USART->m_UCSRB.sBits.m_UDRIE = LBTY_RESET;}

void USART_vidSetCallBack_Empty(void (*pCallBack)(void)){
	pvidfunc_Empty_CallBak = pCallBack;
}
void USART_vidSetCallBack_TX(void (*pCallBack)(void)){
	pvidfunc_Tx_CallBak = pCallBack;
}
void USART_vidSetCallBack_RX(void (*pCallBack)(void)){
	pvidfunc_Rx_CallBak = pCallBack;
}

ISR(USART_RXC_vect){
	if((S_USART->m_UCSRA.sBits.m_RXC) && (strRX_GLB.m_u8Idx < strRX_GLB.m_u8Size) && (strRX_GLB.m_u8Status == RX_BUSY)){
		strRX_GLB.m_pu8Data[strRX_GLB.m_u8Idx++] = S_USART->m_UDR;
	}else{
		strRX_GLB.m_u8Status = RX_IDLE;
		//USART_vidDisableReceiveCompleteINT();
		pvidfunc_Rx_CallBak();
	}
}
ISR(USART_UDRE_vect){
	if((S_USART->m_UCSRA.sBits.m_UDRE) && (strTX_GLB.m_u8Idx < strTX_GLB.m_u8Size) && (strTX_GLB.m_u8Status == TX_BUSY)){
		S_USART->m_UDR = strTX_GLB.m_pu8Data[strTX_GLB.m_u8Idx++];
	}else{
		strTX_GLB.m_u8Status = TX_IDLE;
		//USART_vidDisableDataRegEmptyINT();
		pvidfunc_Empty_CallBak();
	}
}
ISR(USART_TXC_vect){
	if(strTX_GLB.m_u8Status == TX_IDLE){
		strTX_GLB.m_u8Status = TX_IDLE;
		//USART_vidDisableTransmitCompleteINT();
		pvidfunc_Tx_CallBak();
	}
}

/*************************** E N D (UART_prg.c) ******************************/
