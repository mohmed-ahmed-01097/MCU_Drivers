/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : IR_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : May 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef IR_INT_H_
#define IR_INT_H_

#ifndef F_CPU
#error "IR Remote Lib : F_CPU not defined"
#endif

#if ((F_CPU !=8000000) && (F_CPU !=12000000) && (F_CPU !=16000000))
#error "IR Remote Lib : Unsupported CPU frequency"
#error "IR remote Lib : Pls use F_CPU = 8MHz,12Mhz or 16MHz"
#endif

#if F_CPU==8000000
	#define TIMER_COMP_VAL 80
#elif F_CPU==12000000
	#define TIMER_COMP_VAL 120
#elif F_CPU==16000000
	#define TIMER_COMP_VAL 160
#endif

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	IR_ValidateLeadHigh = (u8)0u,
	IR_ValidateLeadLow,
	IR_ReceiveAddress,
	IR_ReceiveBits,
	IR_WaitStopBit
}IR_tenuState;

typedef struct{
		//volatile u16 m_u16Ext_Address;		// device extended address, 0 if it is not used
		volatile u8  m_u8Rec_Address;
		volatile u8  m_u8Rec_AddressInv;
		volatile u8  m_u8Command;
		volatile u8  m_u8CommandInv;
}IR_tstrPacket;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void IR_Reset(void);

void IR_vidInit(void);

LBTY_tenuErrorStatus IR_GetCmd(u8* pu8CMD);
LBTY_tenuErrorStatus IR_GetPacket(IR_tstrPacket* pstrPacket);

void IR_INT_ISR(void);

void IR_TMR_ISR(void);


#endif /* IR_INT_H_ */
/*************************** E N D (IR_int.h) ******************************/
