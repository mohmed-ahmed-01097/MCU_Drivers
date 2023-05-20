/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : May 4, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

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

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

#ifdef	SWC_IR

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "INTP.h"

#include "LCD_int.h"
#include "LCD_cfg.h"

#include "IR_int.h"
#include "IR_cfg.h"
#include "IR_priv.h"

static IR_tstrPacket strIRPacket;
static IR_tstrFram strIRFram;

int main(void){

	IR_vidInit();
	INTP_vidEnable();

	LCD_vidInit();
	LCD_u8ClrDisplay();
	LCD_u8Home();

	u8 u8CMD;

	while(1){
		IR_GetCmd(&u8CMD);
   		LCD_u8SetNum(u8CMD, 12, 1);

   		IR_GetPacket(&strIRPacket);
   		vid_IrReadFram(&strIRFram);

   		LCD_u8SetNum(strIRPacket.m_u8Rec_Address,     0, 0);
   		LCD_u8SetNum(strIRPacket.m_u8Rec_AddressInv,  4, 0);
   		LCD_u8SetNum(strIRPacket.m_u8Command,         8, 0);
   		LCD_u8SetNum(strIRPacket.m_u8CommandInv,     12, 0);

   		LCD_u8SetNum(strIRFram.m_u8ReadBit,      1, 1);
   		LCD_u8SetNum(strIRFram.m_u8ReadByte,     4, 1);
   		LCD_u8SetNum(strIRFram.m_u8Repeat,       7, 1);
   		LCD_u8SetNum(strIRFram.m_u8RepeatCount, 10, 1);

   		LCD_u8SetChar('b', 0, 1);
   		LCD_u8SetChar('B', 3, 1);
   		LCD_u8SetChar('R', 6, 1);
   		LCD_u8SetChar('C', 9, 1);

    }

   	return 0;
}

#endif

/*************************** E N D (main.c) ******************************/
