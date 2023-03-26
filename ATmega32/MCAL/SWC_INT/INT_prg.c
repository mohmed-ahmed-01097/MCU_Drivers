/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : INT_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 26, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "INT_int.h"
#include "INT_priv.h"

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

/* ************************************************************************** */
/* Description : 	Initialize the INT pins direction and SenseControl		  */
/* Input       :	u8INT_Num												  */
/* Return      :	void													  */
/* ************************************************************************** */
void INT_vidInit(u8 u8INT_Num){
	switch(u8INT_Num){
		case INT0:
			GPIO_u8SetPinDirection(INT0_PORT, INT0_PIN, PIN_INPUT);
			INT_vidChangeSenseControl(u8INT_Num, INT0_SC);
			INT_vidEnable(u8INT_Num);
			INT_vidResetFlag(u8INT_Num);
			break;
		case INT1:
			GPIO_u8SetPinDirection(INT1_PORT, INT1_PIN, PIN_INPUT);
			INT_vidChangeSenseControl(u8INT_Num, INT1_SC);
			INT_vidEnable(u8INT_Num);
			INT_vidResetFlag(u8INT_Num);
			break;
		case INT2:
			GPIO_u8SetPinDirection(INT2_PORT, INT2_PIN, PIN_INPUT);
			INT_vidChangeSenseControl(u8INT_Num, INT2_SC);
			INT_vidEnable(u8INT_Num);
			INT_vidResetFlag(u8INT_Num);
			break;
		default:
			break;
	}
}

/* ************************************************************************** */
/* Description :  	Set the SenseControl 									  */
/* Input       :	u8INT_Num, u8INT_SC										  */
/* Return      :	void													  */
/* ************************************************************************** */
void INT_vidChangeSenseControl(u8 u8INT_Num, INT_tenuSenseControl u8INT_SC){
	switch(u8INT_Num){
		case INT0:			S_MCUCR->sBits.m_ISC0  = u8INT_SC;			break;
		case INT1:			S_MCUCR->sBits.m_ISC1  = u8INT_SC;			break;
		case INT2:			S_MCUCSR->sBits.m_ISC2 = u8INT_SC;			break;
		default:			break;
	}
}

/* ************************************************************************** */
/* Description :  	Enable the INT		 									  */
/* Input       :	u8INT_Num, u8INT_SC										  */
/* Return      :	void													  */
/* ************************************************************************** */
void INT_vidEnable(u8 u8INT_Num){
	switch(u8INT_Num){
		case INT0:			S_GICR->sBits.m_INT0E = LBTY_SET;			break;
		case INT1:			S_GICR->sBits.m_INT1E = LBTY_SET;			break;
		case INT2:			S_GICR->sBits.m_INT2E = LBTY_SET;			break;
		default:			break;
	}
}

/* ************************************************************************** */
/* Description :  	Disable the INT		 									  */
/* Input       :	u8INT_Num, u8INT_SC										  */
/* Return      :	void													  */
/* ************************************************************************** */
void INT_vidDisable(u8 u8INT_Num){
	switch(u8INT_Num){
		case INT0:			S_GICR->sBits.m_INT0E = LBTY_RESET;			break;
		case INT1:			S_GICR->sBits.m_INT1E = LBTY_RESET;			break;
		case INT2:			S_GICR->sBits.m_INT2E = LBTY_RESET;			break;
		default:			break;
	}
}

/* ************************************************************************** */
/* Description :  	Set the INT Flag	 									  */
/* Input       :	u8INT_Num, u8INT_SC										  */
/* Return      :	void													  */
/* ************************************************************************** */
void INT_vidSetFlag(u8 u8INT_Num){
	switch(u8INT_Num){
		case INT0:			S_GIFR->sBits.m_INT0F = LBTY_SET;			break;
		case INT1:			S_GIFR->sBits.m_INT1F = LBTY_SET;			break;
		case INT2:			S_GIFR->sBits.m_INT2F = LBTY_SET;			break;
		default:			break;
	}
}

/* ************************************************************************** */
/* Description :  	Reset the INT Flag	 									  */
/* Input       :	u8INT_Num, u8INT_SC										  */
/* Return      :	void													  */
/* ************************************************************************** */
void INT_vidResetFlag(u8 u8INT_Num){
	switch(u8INT_Num){
		case INT0:			S_GIFR->sBits.m_INT0F = LBTY_RESET;			break;
		case INT1:			S_GIFR->sBits.m_INT1F = LBTY_RESET;			break;
		case INT2:			S_GIFR->sBits.m_INT2F = LBTY_RESET;			break;
		default:			break;
	}
}
/*************************** E N D (INT_prg.c) ******************************/
