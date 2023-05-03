/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : IR_priv.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : May 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef IR_PRIV_H_
#define IR_PRIV_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef struct{
		//volatile u16 m_u16Ext_Address;		// device extended address, 0 if it is not used
		volatile u8  m_u8Rec_Address;
		volatile u8  m_u8Rec_AddressInv;
		volatile u8  m_u8Command;
		volatile u8  m_u8CommandInv;
}IR_tstrFrameData;

typedef struct{
	IR_tstrFrameData strFrame;
	volatile u8  m_u8State;
	volatile u8  m_u8Edge;
	volatile u8  m_u8Stop;

	volatile u8  m_u8Repeat;
	volatile u8  m_u8RepeatCount;

	volatile u8  m_u8ReadBit;
	volatile u8  m_u8ReadByte;

	volatile u16 m_u16Time;
}IR_tstrFram;

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

void vid_IrWriteBuffer(u8 u8CMD);

void vid_IrReadBuffer(u8* pu8CMD);

void vid_IrReadFram(u32* pu32Fram);

void vid_IrBitStep(void);

void vid_IrLeadHigh(u16 u16TempTime);
void vid_IrLeadLow(u16 u16TempTime);
void vid_IrReceiveBits(u16 u16TempTime);
void vid_IrStop(void);


#endif /* IR_PRIV_H_ */
/*************************** E N D (IR_priv.h) ******************************/
