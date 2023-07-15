/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : PUSH_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
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
#include "PUSH_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
extern const PUSH_tstrConfig kau8PushConfiguration_LGB[PUSH_Num];
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
	//	PUSH_tstrConfig* pstrPush =
	//			(PUSH_tstrConfig*)&kau8PushConfiguration_LGB[u8PushNum];
	//	GPIO_u8SetPinDirection(pstrPush->m_PinCfg.m_Port, pstrPush->m_PinCfg.m_Pin, PIN_INPUT);
	GPIO_u8PinInit(kau8PushConfiguration_LGB[u8PushNum].m_PinCfg);
}

/* ************************************************************************** */
/* Description : Initialize the All Push Button with Configurations			  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void PUSH_vidInitAll(void){
	for(u8 i = PUSH_Num ; i-- ; ){
		GPIO_u8PinInit(kau8PushConfiguration_LGB[i].m_PinCfg);
	}
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

	PUSH_tstrConfig* pstrPush =
			(PUSH_tstrConfig*)&kau8PushConfiguration_LGB[u8PushNum];
	LBTY_tenuErrorStatus u8RetValue  =
			GPIO_u8GetPinValue(pstrPush->m_PinCfg.m_Port, pstrPush->m_PinCfg.m_Pin, &u8PreValue);

	while((u8DebouncingCount < DEBOUNCING_CYCLES_NUM) && (u8RetValue == LBTY_OK)){
		vidMyDelay_ms(DEBOUNCING_DELAY);
		u8RetValue  = GPIO_u8GetPinValue(pstrPush->m_PinCfg.m_Port, pstrPush->m_PinCfg.m_Pin, &u8CurValue);

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

	*pu8State = (*pu8State == kau8PushConfiguration_LGB[u8PushNum].m_Active) ? PUSH_PRESSED : PUSH_RELEASED;
	return u8RetValue;
}

/*************************** E N D (PUSH_prg.c) ******************************/
