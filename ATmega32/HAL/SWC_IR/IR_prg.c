/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : IR_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 11, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "INTP.h"

#include "INT_int.h"
#include "TMR_int.h"

#include "IR_int.h"
#include "IR_cfg.h"
#include "IR_priv.h"

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

IR_tstrFram strReceiveFram_GLB;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void IR_Reset(void){
//	strReceiveFram_GLB.strFrame.m_u16Ext_Address   = LBTY_u16ZERO;
	strReceiveFram_GLB.strFrame.m_u8Rec_Address    = LBTY_u8ZERO;
	strReceiveFram_GLB.strFrame.m_u8Rec_AddressInv = LBTY_u8ZERO;
	strReceiveFram_GLB.strFrame.m_u8Command        = LBTY_u8ZERO;
	strReceiveFram_GLB.strFrame.m_u8CommandInv     = LBTY_u8ZERO;

	strReceiveFram_GLB.m_u8State 	  = IR_ValidateLeadHigh;
	strReceiveFram_GLB.m_u8Edge 	  = INT_Falling_Edge;

    INT_vidSetSenseControl(IR_INT_PIN, strReceiveFram_GLB.m_u8Edge);

	TMR0_u8SetMode(TMRx_u8_CTC_Mode_Mode);
    TMR0_u8SetOutputCompare(IR_TMR_1US_COMPARE);
}

void IR_vidInit(void){

    INT_vidInit(IR_INT_PIN);
    INT_vidSetCallBack(IR_INT_PIN, IR_INT_ISR);

    TMR0_vidInit();
    TMR0_vidSetCallBack_CompareMatch(IR_TMR_ISR);

	strReceiveFram_GLB.m_u8Repeat     = LBTY_u8ZERO;
	strReceiveFram_GLB.m_u8RepeatCount= LBTY_u8ZERO;
	strReceiveFram_GLB.m_u8ReadBit    = LBTY_u8ZERO;
	strReceiveFram_GLB.m_u8ReadByte   = LBTY_u8ZERO;
	strReceiveFram_GLB.m_u8Stop 	  = LBTY_u8ZERO;

    IR_Reset();
}

LBTY_tenuErrorStatus IR_GetCmd(u8* pu8CMD){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	vid_IrReadBuffer(pu8CMD);
	if(*pu8CMD == LBTY_u8MAX)		u8RetErrorState = LBTY_IN_PROGRESS;
	return u8RetErrorState;
}

LBTY_tenuErrorStatus IR_GetFram(u32* pu32Fram){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	vid_IrReadFram(pu32Fram);
	if(*pu32Fram == LBTY_u32MAX)	u8RetErrorState = LBTY_IN_PROGRESS;
	return u8RetErrorState;
}

void IR_INT_ISR(void){
	INT_vidDisable  (IR_INT_PIN);
	INT_vidResetFlag(IR_INT_PIN);

	INTP_vidEnable();
	//if(strReceiveFram_GLB.m_u8StopState) return;

    u16 u16TempTime = strReceiveFram_GLB.m_u16Time;
    strReceiveFram_GLB.m_u16Time = LBTY_u16ZERO;
    TMR0_u8SetCounter(LBTY_u8ZERO);

	switch(strReceiveFram_GLB.m_u8State){
		case IR_ValidateLeadHigh:	vid_IrLeadHigh   (u16TempTime); 	break;
		case IR_ValidateLeadLow:	vid_IrLeadLow    (u16TempTime); 	break;
		case IR_ReceiveAddress:			break;
		case IR_ReceiveBits:	 	vid_IrReceiveBits(u16TempTime);	 	break;
		case IR_WaitStopBit:		vid_IrStop();						break;

		default:	IR_Reset();
	}

	INT_vidEnable   (IR_INT_PIN);
}

void IR_TMR_ISR(void){
	strReceiveFram_GLB.m_u16Time++;
}

/*************************** E N D (IR_prg.c) ******************************/
