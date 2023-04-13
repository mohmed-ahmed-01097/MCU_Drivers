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

#define EEPROM_MAX_ADDRESS					1024u
#define EEPROM_INTERRUPT_INIT_STATE			LBTY_RESET

void EEPROM_vidInit(void){
	S_EEPROM->m_EEAR = LBTY_u16ZERO;
	S_EEPROM->m_EEDR = LBTY_u8ZERO;

	S_EEPROM->m_EECR.sBits.m_EERIE = EEPROM_INTERRUPT_INIT_STATE;
	S_EEPROM->m_EECR.sBits.m_EEMWE = LBTY_RESET;
	S_EEPROM->m_EECR.sBits.m_EEWE  = LBTY_RESET;
	S_EEPROM->m_EECR.sBits.m_EERE;
}

void EEPROM_vidEnableInterrupt(void){
	S_EEPROM->m_EECR.sBits.m_EERIE = LBTY_SET;
}

void EEPROM_vidDisableInterrupt(void){
	S_EEPROM->m_EECR.sBits.m_EERIE = LBTY_RESET;
}

LBTY_tenuErrorStatus EEPROM_u8WriteChar(u16 u16Address, u8 u8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Address <= EEPROM_MAX_ADDRESS){
		while(S_EEPROM->m_EECR.sBits.m_EEWE);
		while(S_SPMCR->sBits.m_SPMEN);

		S_EEPROM->m_EEAR = u16Address;
		S_EEPROM->m_EEDR = u8Data;
		S_EEPROM->m_EECR.sBits.m_EEMWE = LBTY_SET;
		S_EEPROM->m_EECR.sBits.m_EEWE  = LBTY_SET;
	}else{
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus EEPROM_u8WriteString(u16 u16Address, u8* pu8String){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	while(*pu8String){
		if(EEPROM_u8WriteChar(u16Address++, *(pu8String++))){
			u8RetErrorState = LBTY_NOK;
			break;
		}
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus EEPROM_u8ReadChar(u16 u16Address, u8* pu8Data){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Address <= EEPROM_MAX_ADDRESS){
		while(S_EEPROM->m_EECR.sBits.m_EEWE);

		S_EEPROM->m_EEAR = u16Address;
		S_EEPROM->m_EECR.sBits.m_EERE  = LBTY_SET;
		*pu8Data = S_EEPROM->m_EEDR;
	}else{
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus EEPROM_u8ReadString(u16 u16StartAddress, u16 u16EndAddress, u8* pu8String){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	for(int i = u16StartAddress ; i<= u16EndAddress ; i++){
		if(EEPROM_u8ReadChar(i, pu8String++)){
			u8RetErrorState = LBTY_NOK;
			break;
		}
	}
	return u8RetErrorState;
}

/*************************** E N D (EEPROM_prg.c) ******************************/
