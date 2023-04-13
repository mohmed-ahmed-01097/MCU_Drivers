/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : UART_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 9, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "USART_priv.h"
#include "USART_cfg.h"
#include "USART_int.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

static u8 USART_pu8TxBuffer_GLB[100];
static u8 USART_pu8RxBuffer_GLB[100];

static u8 USART_u8TxIndex_GLB;
static u8 USART_u8RxIndex_GLB;

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */
void UART_vidInit(void){

	S_USART->m_UCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
	S_USART->m_UCSRC.sUCSRC.m_UCPOL = USART_Transmit_Rising_Receive_Falling;
	S_USART->m_UCSRC.sUCSRC.m_UMSEL = USART_OPERATION_MODE;

	USART_u8SetBuadRate(USART_BUAD_RATE_INIT);

	USART_u8SetCharSize(USART_CHAR_SIZE_INIT);
	USART_u8SetParityMode(USART_PARITY_MODE_INIT);
	USART_u8SetStopBit(USART_STOP_BIT_INIT);

	S_USART->m_UCSRA.sBits.m_MPCM = LBTY_RESET;
	S_USART->m_UCSRA.sBits.m_U2X  = LBTY_RESET;

	S_USART->m_UCSRB.sBits.m_UDRIE = USART_DATA_REG_EMPTY_INT;
	S_USART->m_UCSRB.sBits.m_TXCIE = USART_TRANSMIT_COMPLETE_INT;
	S_USART->m_UCSRB.sBits.m_RXCIE = USART_RECEIVE_COMPLETE_INT;

	S_USART->m_UCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
	if(S_USART->m_UCSRC.sUCSRC.m_UMSEL == USART_Synchronous){
		GPIO_u8SetPinDirection(USART_XCK_PORT, USART_XCK_PIN, PIN_OUTPUT);
	}
	GPIO_u8SetPinDirection(USART_PORT    , USART_TX_PIN , PIN_OUTPUT);
	GPIO_u8SetPinDirection(USART_XCK_PORT, USART_RX_PIN , PIN_INPUT );

	S_USART->m_UCSRB.sBits.m_TXEN = LBTY_SET;
	S_USART->m_UCSRB.sBits.m_RXEN = LBTY_SET;
}

void USART_vidTransmitterEnable(void){
	S_USART->m_UCSRB.sBits.m_TXEN = LBTY_SET;
}
void USART_vidTransmitterDisable(void){
	S_USART->m_UCSRB.sBits.m_TXEN = LBTY_RESET;
}
void USART_vidReceiverEnable(void){
	S_USART->m_UCSRB.sBits.m_RXEN = LBTY_SET;
}
void USART_vidReceiverDisable(void){
	S_USART->m_UCSRB.sBits.m_RXEN = LBTY_RESET;
}
LBTY_tenuErrorStatus USART_u8SetStopBit(USART_tenumStopBit u8Stop){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	S_USART->m_UCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
	switch(u8Stop){
		case USART_Stop_1_bit: S_USART->m_UCSRC.sUCSRC.m_USBS = u8Stop;	break;
		case USART_Stop_2_bit: S_USART->m_UCSRC.sUCSRC.m_USBS = u8Stop;	break;
		default: u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus USART_u8SetParityMode(USART_tenumParityMode u8Parity){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	S_USART->m_UCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
	switch(u8Parity){
		case USART_Parity_Disable: S_USART->m_UCSRC.sUCSRC.m_UPM = u8Parity;	break;
		case USART_Parity_Even   : S_USART->m_UCSRC.sUCSRC.m_UPM = u8Parity;	break;
		case USART_Parity_Odd    : S_USART->m_UCSRC.sUCSRC.m_UPM = u8Parity;	break;
		default: u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus USART_u8SetCharSize(USART_tenumCharSize u8CharSize){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	if(u8CharSize == USART_5_bit || u8CharSize == USART_6_bit || u8CharSize == USART_7_bit ||
	   u8CharSize == USART_8_bit || u8CharSize == USART_9_bit){
		S_USART->m_UCSRC.sUCSRC.m_URSEL = USART_UCSRC_Reg;
		S_USART->m_UCSRC.sUCSRC.m_UCSZ0 = GET_BIT(u8CharSize, USART_UCSZ0_BIT);
		S_USART->m_UCSRC.sUCSRC.m_UCSZ1 = GET_BIT(u8CharSize, USART_UCSZ1_BIT);
		S_USART->m_UCSRB.sBits.m_UCSZ2  = GET_BIT(u8CharSize, USART_UCSZ2_BIT);
	}else{
		u8RetErrorState = LBTY_NOK;
	}

	return u8RetErrorState;
}
LBTY_tenuErrorStatus USART_u8SetBuadRate(u32 u32BuadRate){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u16 u16UBRR;
	if(u32BuadRate > USART_BuadRate_2400){
		u16UBRR = (u16)(F_CPU / (f32)(16 * u32BuadRate)) - 1;
	}else{
		u16UBRR = (u16)u32BuadRate;
	}
	S_USART->m_UCSRC.sUBRRH.m_URSEL = USART_UBRRH_Reg;
	S_USART->m_UCSRC.sUBRRH.m_UBRR = GET_NIB(u16UBRR, 8);
	S_USART->m_UBRRL = GET_BYTE(u16UBRR, 0);

	return u8RetErrorState;
}
void USART_vidSetTransmit(u16 u16Transmit){
	while(!USART_u8GetDataRegEmpty());
	S_USART->m_UDR = GET_BYTE(u16Transmit, 0);
	S_USART->m_UCSRB.sBits.m_TXB8 = GET_BIT(u16Transmit, 8);
}
void USART_vidGetTransmit(u16* pu16Receive){
	while(!USART_u8GetReceiveComplete());
	if(USART_u8GetFrameError() || USART_u8GetDataOverRun() || USART_u8GetParityError()){
		*pu16Receive = LBTY_u16MAX;
	}else{
		*pu16Receive = (u16)S_USART->m_UDR |(S_USART->m_UCSRB.sBits.m_RXB8 << 8);
	}
}
void USART_vidFlush(void){
	u8 dummy;
	while(USART_u8GetReceiveComplete()){
		dummy = S_USART->m_UDR;
	}
}

void USART_vidSetChar(u8 u8Char){
	while(!USART_u8GetDataRegEmpty());
	S_USART->m_UDR = u8Char;
}
void USART_vidGetChar(u8* pu8Char){
	while(!USART_u8GetReceiveComplete());
	*pu8Char = S_USART->m_UDR;
}

void USART_vidSetStr(u8* pu8Transmit){
	while(*pu8Transmit){
		USART_vidSetChar(*(pu8Transmit++));
	}
}
void USART_vidGetStr(u8* pu8Receive){
	do{
		USART_vidGetChar(pu8Receive++);
		USART_vidSetChar('\0');
	}while(USART_u8Available());
	*pu8Receive = '\0';
//	while(*pu8Receive = '\0'){
//		USART_vidGetChar(pu8Receive++);
//	}
}

u8 USART_u8Available(void){
	return USART_u8GetReceiveComplete();
}
u8 USART_u8Get_UBRRH(void){
	return S_USART->m_UCSRC.u_Reg;
}
u8 USART_u8Get_UCSRC(void){
	S_USART->m_UCSRC.u_Reg;
	return S_USART->m_UCSRC.u_Reg;
}

void USART_vidWriteBuffer(void){
	while(!USART_u8GetReceiveComplete());
	if(USART_u8RxIndex_GLB < 100){
		USART_pu8RxBuffer_GLB[USART_u8RxIndex_GLB++] = S_USART->m_UDR;
	}
}
u8 USART_vidReadBuffer(void){
	u8 u8RetValue = LBTY_u8MAX;
	if(USART_u8RxIndex_GLB > LBTY_u8ZERO){
		u8RetValue = USART_pu8RxBuffer_GLB[USART_u8RxIndex_GLB--];
	}
	return u8RetValue;
}
/*************************** E N D (UART_prg.c) ******************************/
