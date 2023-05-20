/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : PUSH_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
/* date        : Mar 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "PUSH_int.h"
#include "PUSH_cfg.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	PUSH_PULL_UP_PRESSED = (u8)0u,
	PUSH_PULL_UP_RELEASED,

	PUSH_PULL_DOWN_RELEASED = (u8)0u,
	PUSH_PULL_DOWN_PRESSED
}PUSH_tenuStatusConfig;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
extern const PUSH_tstrConfiguration kau8PushConfiguration_LGB[PUSH_NUM];
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description : Initialize the Push Button direction						  */
/* Input       :	u8PushNum												  */
/* Return      :	void													  */
/* ************************************************************************** */
void PUSH_vidInit(u8 u8PushNum){
	PUSH_tstrConfiguration* pstrPush =
			(PUSH_tstrConfiguration*)&kau8PushConfiguration_LGB[u8PushNum];
	GPIO_u8SetPinDirection(pstrPush->u8PortNum, pstrPush->u8PinNum, PIN_INPUT);
}

/* ************************************************************************** */
/* Description :    Get the Push Button DeBouncing							  */
/* Input       :	u8PushNum												  */
/* Input/Output:    pu8State												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus PUSH_u8GetDebounce(u8 u8PushNum, u8* pu8State){
	u8 u8PreValue = LBTY_u8ZERO;
	u8 u8CurValue = LBTY_u8ZERO;
	u8 u8DebouncingCount = LBTY_u8ZERO;

	PUSH_tstrConfiguration* pstrPush =
			(PUSH_tstrConfiguration*)&kau8PushConfiguration_LGB[u8PushNum];
	LBTY_tenuErrorStatus u8RetValue  =
			GPIO_u8GetPinValue(pstrPush->u8PortNum, pstrPush->u8PinNum, &u8PreValue);

	while((u8DebouncingCount < DEBOUNCING_CYCLES_NUM) && (u8RetValue == LBTY_OK)){
		vidMyDelay_ms(5);
		u8RetValue  = GPIO_u8GetPinValue(pstrPush->u8PortNum, pstrPush->u8PinNum, &u8CurValue);

		if(u8PreValue == u8CurValue){
			u8DebouncingCount++;
		}else{
			u8DebouncingCount = 0;
		}
		u8PreValue = u8CurValue;
	}
	*pu8State = u8CurValue;
	return u8RetValue;
}

/* ************************************************************************** */
/* Description :    Get the Push Button value								  */
/* Input       :	u8PushNum												  */
/* Input/Output:    pu8State												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus PUSH_u8GetPushState(u8 u8PushNum, u8* pu8State){
	LBTY_tenuErrorStatus u8RetValue  = PUSH_u8GetDebounce(u8PushNum, pu8State);

	switch(kau8PushConfiguration_LGB[u8PushNum].u8Connection){
		case PUSH_PULL_UP:
			*pu8State = (*pu8State == PUSH_PULL_UP_PRESSED) ? PUSH_PRESSED : PUSH_RELEASED;
			break;
		case PUSH_PULL_DOWN:
			*pu8State = (*pu8State == PUSH_PULL_DOWN_PRESSED) ? PUSH_PRESSED : PUSH_RELEASED;
			break;
		default :
			while(1);

	}
	return u8RetValue;
}

/*************************** E N D (PUSH_prg.c) ******************************/
