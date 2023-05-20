/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : KEYPAD_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "KPAD_cfg.h"
#include "KPAD_int.h"
#include "KPAD_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	KPAD_RELEASED = KPAD_KEY_RES,
	KPAD_PRESSED = !KPAD_KEY_RES
}KPAD_tenuKeyState;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
extern const u8 kau8ROW_PINs_GLB[];
extern const u8 kau8COL_PINs_GLB[];
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
/* Description :    Get the Push Button DeBouncing							  */
/* Input       :	u8PortNum, u8PinNum										  */
/* Input/Output:    pu8Value												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
static LBTY_tenuErrorStatus PUSH_u8GetDebounce(GPIO_tenuPortNum u8PortNum,
		GPIO_tenuPinNum u8PinNum, pu8 pu8Value){
	u8 u8PreValue = LBTY_u8ZERO;
	u8 u8CurValue = LBTY_u8ZERO;
	u8 u8DebouncingCount = LBTY_u8ZERO;

	LBTY_tenuErrorStatus u8RetValue = GPIO_u8GetPinValue(u8PortNum, u8PinNum, &u8PreValue);

	while((u8DebouncingCount < DEBOUNCING_CYCLES_NUM) && (u8RetValue == LBTY_OK)){
		vidMyDelay_ms(5);
		u8RetValue  = GPIO_u8GetPinValue(u8PortNum, u8PinNum, &u8CurValue);

		if(u8PreValue == u8CurValue){
			u8DebouncingCount++;
		}else{
			u8DebouncingCount = 0;
		}
		u8PreValue = u8CurValue;
	}
	*pu8Value = u8CurValue;
	return u8RetValue;
}

/* ************************************************************************** */
/* Description :    Keypad Get Push Press Number							  */
/* Input       :	void													  */
/* Return      :	u8														  */
/* ************************************************************************** */
u8 KPAD_u8GetKeyNum(void){
	u8 u8RetValue = LBTY_u8MAX;

#ifdef KPAD_ROW_DIR_OUTPUT
	for(u8 i = 0 ; i<KPAD_ROW_NUM ; i++){
		GPIO_u8SetPinValue(KPAD_ROW_PORT, kau8ROW_PINs_GLB[i], KPAD_PRESSED);
		for(u8 j = 0 ; j<KPAD_COL_NUM ; j++){
			PUSH_u8GetDebounce(KPAD_COL_PORT, kau8COL_PINs_GLB[j], &u8RetValue);
#endif
#ifdef KPAD_COL_DIR_OUTPUT
	for(u8 i = 0 ; i<KPAD_COL_NUM ; i++){
		GPIO_u8SetPinValue(KPAD_COL_PORT, kau8COL_PINs_GLB[i], KPAD_PRESSED);
		for(u8 j = 0 ; j<KPAD_ROW_NUM ; j++){
			PUSH_u8GetDebounce(KPAD_ROW_PORT, kau8ROW_PINs_GLB[j], &u8RetValue);
#endif
			if(u8RetValue == KPAD_RELEASED){
				u8RetValue = LBTY_u8MAX;
				continue;
			}else{
				u8RetValue = j + (i * KPAD_ROW_NUM);
				break;
			}
		}
#ifdef KPAD_ROW_DIR_OUTPUT
		GPIO_u8SetPinValue(KPAD_ROW_PORT, kau8ROW_PINs_GLB[i], KPAD_RELEASED);
#endif
#ifdef KPAD_COL_DIR_OUTPUT
		GPIO_u8SetPinValue(KPAD_COL_PORT, kau8COL_PINs_GLB[i], KPAD_RELEASED);
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
	u8 u8RetValue = LBTY_u8ZERO;
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
