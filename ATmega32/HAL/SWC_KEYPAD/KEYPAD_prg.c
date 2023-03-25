/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : KEYPAD_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "DELAY.h"

#include "KEYPAD_int.h"
#include "KEYPAD_cfg.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
const u8 pu8RowPins[] = {KP_ROW0, KP_ROW1, KP_ROW2, KP_ROW3};
const u8 pu8ColPins[] = {KP_COL0, KP_COL1, KP_COL2, KP_COL3};
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :    Keypad initialization									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void KP_vidInit(void){

	GPIO_u8SetMaskDirection	(KP_ROW_PORT, KP_ROW_MASK, PORT_OUTPUT);
	GPIO_u8SetMaskValue		(KP_ROW_PORT, KP_ROW_MASK, PORT_High);

	GPIO_u8SetMaskDirection	(KP_COL_PORT, KP_COL_MASK, PORT_INPUT);

}

/* ************************************************************************** */
/* Description :    Keypad Get Push Press Number							  */
/* Input       :	void													  */
/* Return      :	u8														  */
/* ************************************************************************** */
u8 KP_u8GetPressNum(void){
	u8 u8RetValue = LBTY_u8MAX;

	for(u8 i = 0 ; i<KP_ROW_NUM ; i++){
		GPIO_u8SetPinValue(KP_ROW_PORT, pu8RowPins[i], PIN_Low);

		for(u8 j = 0 ; j<KP_COL_NUM ; j++){
			GPIO_u8GetPinValue(KP_COL_PORT, pu8ColPins[j], &u8RetValue);
			if(u8RetValue){
				u8RetValue = LBTY_u8MAX;
				continue;
			}else{
				u8RetValue = j + (i * KP_COL_NUM);
				break;
			}
		}

		GPIO_u8SetPinValue(KP_ROW_PORT, pu8RowPins[i], PIN_High);
		if(u8RetValue == LBTY_u8MAX){
			continue;
		}else{
			break;
		}
	}
	return u8RetValue;
}

/* ************************************************************************** */
/* Description :    Keypad Get Input Char Value								  */
/* Input       :	void													  */
/* Return      :	u8														  */
/* ************************************************************************** */
u8 KP_u8GetInputChar(void){
	u8 u8RetValue = LBTY_u8MAX;
	switch(KP_u8GetPressNum()){
		case 0:
			u8RetValue = KP_KEY00;
			break;
		case 1:
			u8RetValue = KP_KEY01;
			break;
		case 2:
			u8RetValue = KP_KEY02;
			break;
		case 3:
			u8RetValue = KP_KEY03;
			break;

		case 4:
			u8RetValue = KP_KEY10;
			break;
		case 5:
			u8RetValue = KP_KEY11;
			break;
		case 6:
			u8RetValue = KP_KEY12;
			break;
		case 7:
			u8RetValue = KP_KEY13;
			break;

		case 8:
			u8RetValue = KP_KEY20;
			break;
		case 9:
			u8RetValue = KP_KEY21;
			break;
		case 10:
			u8RetValue = KP_KEY22;
			break;
		case 11:
			u8RetValue = KP_KEY23;
			break;

		case 12:
			u8RetValue = KP_KEY30;
			break;
		case 13:
			u8RetValue = KP_KEY31;
			break;
		case 14:
			u8RetValue = KP_KEY32;
			break;
		case 15:
			u8RetValue = KP_KEY33;
			break;
	}

	return u8RetValue;
}

/*************************** E N D (KEYPAD_prg.c) ******************************/
