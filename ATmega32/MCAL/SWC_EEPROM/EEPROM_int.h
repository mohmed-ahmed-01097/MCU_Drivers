/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : EEPROM_int.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_

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
/* Description :  	Initialization of the EEPROM							  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidInit(void);

/* ************************************************************************** */
/* Description :  	Enable EEPROM Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidEnableInterrupt(void);

/* ************************************************************************** */
/* Description :  	Disable EEPROM Interrupt									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidDisableInterrupt(void);

/* ************************************************************************** */
/* Description :  	Erase EEPROM with range									  */
/* Input       :	u16StartAdd, u16EndAdd									  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8Erase(u16 u16StartAdd, u16 u16EndAdd);

/* ************************************************************************** */
/* Description :  	Write Char in EEPROM address							  */
/* Input       :	u16Address, u8Data										  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8WriteChar(u16 u16Address, u8 u8Data);

/* ************************************************************************** */
/* Description :  	Write String in EEPROM address							  */
/* Input       :	u16Address												  */
/* Input/Output:	pu8String												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8WriteString(u16 u16Address, u8* pu8String);

/* ************************************************************************** */
/* Description :  	Read Char in EEPROM address								  */
/* Input       :	u16Address												  */
/* Input/Output:	pu8Data													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8ReadChar(u16 u16Address, u8* pu8Data);

/* ************************************************************************** */
/* Description :  	Read String in EEPROM address							  */
/* Input       :	u16StartAddress, u16EndAddress							  */
/* Input/Output:	pu8String												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus EEPROM_u8ReadString(u16 u16StartAddress, u16 u16EndAddress, u8* pu8String);

/* ************************************************************************** */
/* Description :  	Set EEPROM Interrupt call back							  */
/* Input       :	CallBack												  */
/* Return      :	void													  */
/* ************************************************************************** */
void EEPROM_vidSetCallBack(void (*CallBack)(void));

#endif /* EEPROM_INT_H_ */
/*************************** E N D (EEPROM_int.h) ******************************/
