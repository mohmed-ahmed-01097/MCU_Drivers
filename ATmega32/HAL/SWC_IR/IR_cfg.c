/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : IR_cfg.c													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : May 3, 2023												  */
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

extern IR_tstrFram strReceiveFram_GLB;
static volatile u8*const kpu8FramBytes_GLB = (u8*)&strReceiveFram_GLB.strFrame;

static volatile u8 au8ReceiveBuffer_GLB[IR_CMD_QUEUE_LENGTH];
static volatile u8 u8BufferIndex_GLB = LBTY_u8ZERO;
static volatile u8 u8BufferEnd_GLB   = LBTY_u8ZERO;

static IR_tstrFrameData u8PrevFram_GLB;

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void vid_IrWriteBuffer(u8 u8CMD){
	if(++u8BufferEnd_GLB >= IR_CMD_QUEUE_LENGTH)		u8BufferEnd_GLB = LBTY_u8ZERO;

	au8ReceiveBuffer_GLB[u8BufferEnd_GLB] = u8CMD;

	if(u8BufferEnd_GLB == u8BufferIndex_GLB){
		if(++u8BufferIndex_GLB >= IR_CMD_QUEUE_LENGTH)	u8BufferIndex_GLB = LBTY_u8ZERO;
	}
}

void vid_IrReadBuffer(u8* pu8CMD){
	if((u8BufferEnd_GLB - u8BufferIndex_GLB) > LBTY_u8ZERO ||
	   (IR_CMD_QUEUE_LENGTH + u8BufferEnd_GLB - u8BufferIndex_GLB) < IR_CMD_QUEUE_LENGTH){
		*pu8CMD = au8ReceiveBuffer_GLB[u8BufferIndex_GLB];
		if(++u8BufferIndex_GLB >= IR_CMD_QUEUE_LENGTH)	u8BufferIndex_GLB = LBTY_u8ZERO;
	}else{
		*pu8CMD = LBTY_u8MAX;
	}
}

void vid_IrReadFram(u32* pu32Fram){
	IR_tstrFrameData* tempFram = (IR_tstrFrameData*)pu32Fram;
	tempFram->m_u8Rec_Address    = u8PrevFram_GLB.m_u8Rec_Address;
	tempFram->m_u8Rec_AddressInv = u8PrevFram_GLB.m_u8Rec_AddressInv;
	tempFram->m_u8Command        = u8PrevFram_GLB.m_u8Command;
	tempFram->m_u8CommandInv     = u8PrevFram_GLB.m_u8CommandInv;
}

void vid_IrBitStep(void){
	if(++strReceiveFram_GLB.m_u8ReadBit >= IR_CMD_MAX_LENGTH){
		strReceiveFram_GLB.m_u8ReadBit = LBTY_u8ZERO;
		if(++strReceiveFram_GLB.m_u8ReadByte >= IR_FRAM_LENGTH){
			strReceiveFram_GLB.m_u8State= IR_WaitStopBit;
		}
	}
}

void vid_IrLeadHigh(u16 u16TempTime){

	if(strReceiveFram_GLB.m_u8Edge == INT_Rising_Edge){
		if(IR_CHECK_TIME(u16TempTime, IR_HIGH_LEAD_TIME)){
			strReceiveFram_GLB.m_u8State= IR_ValidateLeadLow;
			strReceiveFram_GLB.m_u8Edge = INT_Falling_Edge;
			INT_vidSetSenseControl(IR_INT_PIN, strReceiveFram_GLB.m_u8Edge);
		}else{		// error in Lead High
			IR_Reset();
		}
	}else{
		strReceiveFram_GLB.m_u8Edge = INT_Rising_Edge;
		INT_vidSetSenseControl(IR_INT_PIN, strReceiveFram_GLB.m_u8Edge);
	}
}

void vid_IrLeadLow(u16 u16TempTime){

	if(IR_CHECK_TIME(u16TempTime, IR_LOW0_LEAD_TIME)){
		strReceiveFram_GLB.m_u8State= IR_ReceiveBits;
		strReceiveFram_GLB.m_u8Edge = INT_Rising_Edge;
		INT_vidSetSenseControl(IR_INT_PIN, strReceiveFram_GLB.m_u8Edge);

		strReceiveFram_GLB.m_u8ReadBit  = LBTY_u8ZERO;
		strReceiveFram_GLB.m_u8ReadByte = LBTY_u8ZERO;

	}else if(IR_CHECK_TIME(u16TempTime, IR_LOW1_LEAD_TIME)){
		if(strReceiveFram_GLB.m_u8Repeat){
			vid_IrWriteBuffer(u8PrevFram_GLB.m_u8Command);
		}else{
			if(++strReceiveFram_GLB.m_u8RepeatCount >= IR_REPEAT_MAX)	strReceiveFram_GLB.m_u8Repeat = LBTY_SET;
		}
		IR_Reset();
	}else{		// error in Lead Low
		IR_Reset();
	}
}

void vid_IrReceiveBits(u16 u16TempTime){

	if(strReceiveFram_GLB.m_u8Edge == INT_Rising_Edge){
		if(IR_CHECK_TIME(u16TempTime, IR_HIGH_BIT_TIME)){
			strReceiveFram_GLB.m_u8Edge = INT_Falling_Edge;
			INT_vidSetSenseControl(IR_INT_PIN, strReceiveFram_GLB.m_u8Edge);
		}else{		// error in Bit Beg
			IR_Reset();
		}
	}else{
		strReceiveFram_GLB.m_u8Edge = INT_Rising_Edge;
		INT_vidSetSenseControl(IR_INT_PIN, strReceiveFram_GLB.m_u8Edge);

		if(IR_CHECK_TIME(u16TempTime, IR_HIGH_BIT_TIME)){
			vid_IrBitStep();
		}else if(IR_CHECK_TIME(u16TempTime, IR_LOW_BIT_TIME)){
			SET_BIT(kpu8FramBytes_GLB[strReceiveFram_GLB.m_u8ReadByte], strReceiveFram_GLB.m_u8ReadBit);
			vid_IrBitStep();
		}else{		// error in read bit
			IR_Reset();
		}
	}
}

void vid_IrStop(void){

	if(strReceiveFram_GLB.m_u8Edge == INT_Rising_Edge){
		if(strReceiveFram_GLB.strFrame.m_u8Command == (u8)~strReceiveFram_GLB.strFrame.m_u8CommandInv){

			vid_IrWriteBuffer(strReceiveFram_GLB.strFrame.m_u8Command);
			u8PrevFram_GLB.m_u8Command = strReceiveFram_GLB.strFrame.m_u8Command;
			strReceiveFram_GLB.m_u8Repeat     = LBTY_u8ZERO;
			strReceiveFram_GLB.m_u8RepeatCount= LBTY_u8ZERO;
			IR_Reset();
		}
	}
}


/*************************** E N D (IR_cfg.c) ******************************/
