/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : EEPROM_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "INTP.h"

#include "EEPROM_int.h"
#include "EEPROM_cfg.h"
#include "EEPROM_priv.h"

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
void (*pfunctionCallBack)(void);
/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :  	Initialization of the EEPROM							  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidInit(void){
	S_EEPROM->m_EEAR = LBTY_u16ZERO;
	S_EEPROM->m_EEDR = LBTY_u8ZERO;

	S_EEPROM->m_EECR.sBits.m_EERIE = EEPROM_INTERRUPT_INIT_STATE;
	S_EEPROM->m_EECR.sBits.m_EEMWE = LBTY_RESET;
	S_EEPROM->m_EECR.sBits.m_EEWE  = LBTY_RESET;
	S_EEPROM->m_EECR.sBits.m_EERE  = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Enable EEPROM Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidEnableInterrupt(void){
	S_EEPROM->m_EECR.sBits.m_EERIE = LBTY_SET;
}

/* ************************************************************************** */
/* Description :  	Disable EEPROM Interrupt								  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidDisableInterrupt(void){
	S_EEPROM->m_EECR.sBits.m_EERIE = LBTY_RESET;
}

/* ************************************************************************** */
/* Description :  	Erase EEPROM with range									  */
/* Input       :	u16StartAdd, u16EndAdd									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8Erase(u16 u16StartAdd, u16 u16EndAdd){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	for(u16 i = u16EndAdd - u16StartAdd ; i-- ; ){
		if(EEPROM_u8WriteChar(u16StartAdd++, LBTY_u8ZERO)){
			u8RetErrorState = LBTY_NOK;
			break;
		}
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Write Char in EEPROM address							  */
/* Input       :	u16Address, u8Data										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8WriteChar(u16 u16Address, u8 u8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Address <= EEPROM_MAX_ADDRESS){
		while(S_EEPROM->m_EECR.sBits.m_EEWE);
		while(S_SPMCR->sBits.m_SPMEN);

		S_EEPROM->m_EEAR = u16Address;
		S_EEPROM->m_EEDR = u8Data;

		INTP_vidDisable();

		S_EEPROM->m_EECR.sBits.m_EEMWE = LBTY_SET;
		S_EEPROM->m_EECR.sBits.m_EEWE  = LBTY_SET;

		INTP_vidEnable();
		
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Write String in EEPROM address							  */
/* Input       :	u16Address												  */
/* Input/Output:	pu8String												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8WriteString(u16 u16Address, u8* pu8String){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	while(*pu8String){
		if(EEPROM_u8WriteChar(u16Address++, *(pu8String++))){
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
		}
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Read Char in EEPROM address								  */
/* Input       :	u16Address												  */
/* Input/Output:	pu8Data													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8ReadChar(u16 u16Address, u8* pu8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Address <= EEPROM_MAX_ADDRESS){
		while(S_EEPROM->m_EECR.sBits.m_EEWE);

		S_EEPROM->m_EEAR = u16Address;
		S_EEPROM->m_EECR.sBits.m_EERE  = LBTY_SET;
		*pu8Data = S_EEPROM->m_EEDR;
	}else{
		u8RetErrorState = LBTY_INDEX_OUT_OF_RANGE;
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Read String in EEPROM address							  */
/* Input       :	u16StartAddress, u16EndAddress							  */
/* Input/Output:	pu8String												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8ReadString(u16 u16StartAddress, u16 u16EndAddress, u8* pu8String){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	for(int i = u16StartAddress ; i<= u16EndAddress ; i++){
		if(EEPROM_u8ReadChar(i, pu8String++)){
			u8RetErrorState = LBTY_READ_ERROR;
			break;
		}
	}
	return u8RetErrorState;
}

/* ************************************************************************** */
/* Description :  	Set EEPROM Interrupt call back							  */
/* Input       :	CallBack												  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidSetCallBack(void (*CallBack)(void)){
	pfunctionCallBack = CallBack;
}

ISR(EE_RDY_vect){
	pfunctionCallBack();
}
/*************************** E N D (EEPROM_prg.c) ******************************/
