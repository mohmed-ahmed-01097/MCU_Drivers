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

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "KPAD_cfg.h"
#include "KPAD_int.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
const u8 pu8ROW_PINs_GLB[] = {KPAD_ROW0, KPAD_ROW1, KPAD_ROW2, KPAD_ROW3};
const u8 pu8COL_PINs_GLB[] = {KPAD_COL0, KPAD_COL1, KPAD_COL2, KPAD_COL3};
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
void KPAD_vidInit(void){
#ifdef KPAD_ROW_DIR_OUTPUT
	GPIO_u8SetMaskDirection	(KPAD_ROW_PORT, KPAD_ROW_MASK, PORT_OUTPUT);
	GPIO_u8SetMaskValue		(KPAD_ROW_PORT, KPAD_ROW_MASK, PORT_High);

	GPIO_u8SetMaskDirection	(KPAD_COL_PORT, KPAD_COL_MASK, PORT_INPUT);
#endif
#ifdef KPAD_COL_DIR_OUTPUT
	GPIO_u8SetMaskDirection	(KPAD_COL_PORT, KPAD_COL_MASK, PORT_OUTPUT);
	GPIO_u8SetMaskValue		(KPAD_COL_PORT, KPAD_COL_MASK, PORT_High);

	GPIO_u8SetMaskDirection	(KPAD_ROW_PORT, KPAD_ROW_MASK, PORT_INPUT);
#endif
}

/* ************************************************************************** */
/* Description :    Keypad Get Push Press Number							  */
/* Input       :	void													  */
/* Return      :	u8														  */
/* ************************************************************************** */
u8 KPAD_u8GetKeyNum(void){
	u8 u8RetValue = LBTY_u8MAX;

	for(u8 i = 0 ; i<KPAD_ROW_NUM ; i++){
#ifdef KPAD_ROW_DIR_OUTPUT
		GPIO_u8SetPinValue(KPAD_ROW_PORT, pu8ROW_PINs_GLB[i], PIN_Low);
#endif
#ifdef KPAD_COL_DIR_OUTPUT
		GPIO_u8SetPinValue(KPAD_COL_PORT, pu8COL_PINs_GLB[i], PIN_Low);
#endif
		for(u8 j = 0 ; j<KPAD_COL_NUM ; j++){
#ifdef KPAD_ROW_DIR_OUTPUT
			GPIO_u8GetPinValue(KPAD_COL_PORT, pu8COL_PINs_GLB[j], &u8RetValue);
#endif
#ifdef KPAD_COL_DIR_OUTPUT
			GPIO_u8GetPinValue(KPAD_ROW_PORT, pu8ROW_PINs_GLB[j], &u8RetValue);
#endif
			if(u8RetValue == KPAD_KEY_RELEASED){
				u8RetValue = LBTY_u8MAX;
				continue;
			}else{
				u8RetValue = j + (i * KPAD_MAX_COL);
				break;
			}
		}
#ifdef KPAD_ROW_DIR_OUTPUT
		GPIO_u8SetPinValue(KPAD_ROW_PORT, pu8ROW_PINs_GLB[i], PIN_High);
#endif
#ifdef KPAD_COL_DIR_OUTPUT
		GPIO_u8SetPinValue(KPAD_COL_PORT, pu8COL_PINs_GLB[i], PIN_High);
#endif
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
u8 KPAD_u8GetInputChar(void){
	u8 u8RetValue = LBTY_u8MAX;
	switch(KPAD_u8GetKeyNum()){
		case 0:
			u8RetValue = KPAD_KEY00;
			break;
		case 1:
			u8RetValue = KPAD_KEY01;
			break;
		case 2:
			u8RetValue = KPAD_KEY02;
			break;
		case 3:
			u8RetValue = KPAD_KEY03;
			break;

		case 4:
			u8RetValue = KPAD_KEY10;
			break;
		case 5:
			u8RetValue = KPAD_KEY11;
			break;
		case 6:
			u8RetValue = KPAD_KEY12;
			break;
		case 7:
			u8RetValue = KPAD_KEY13;
			break;

		case 8:
			u8RetValue = KPAD_KEY20;
			break;
		case 9:
			u8RetValue = KPAD_KEY21;
			break;
		case 10:
			u8RetValue = KPAD_KEY22;
			break;
		case 11:
			u8RetValue = KPAD_KEY23;
			break;

		case 12:
			u8RetValue = KPAD_KEY30;
			break;
		case 13:
			u8RetValue = KPAD_KEY31;
			break;
		case 14:
			u8RetValue = KPAD_KEY32;
			break;
		case 15:
			u8RetValue = KPAD_KEY33;
			break;
	}

	return u8RetValue;
}

/*************************** E N D (KEYPAD_prg.c) ******************************/
