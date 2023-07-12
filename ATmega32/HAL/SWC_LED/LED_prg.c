/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LED_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_int.h"
#include "LED_cfg.h"
#include "LED_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
extern const LED_tstrConfig kau8LEDConfiguration_LGB[LED_Num];
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description : Initialize the LED Button direction						  */
/* Input       :	u8LedNum												  */
/* Return      :	void													  */
/* ************************************************************************** */
void LED_vidInit(u8 u8LedNum){
//	LED_tstrConfig* pstrLed =
//			(LED_tstrConfig*)&kau8LEDConfiguration_LGB[u8LedNum];
//	GPIO_u8SetPinDirection(pstrLed->m_PinCfg.m_Port, pstrLed->m_PinCfg.m_Pin, PIN_OUTPUT);
//	GPIO_u8SetPinValue    (pstrLed->m_PinCfg.m_Port, pstrLed->m_PinCfg.m_Pin
//				,(pstrLed->m_Connection == LED_Forward) ? pstrLed->m_PinCfg.m_Value : !pstrLed->m_PinCfg.m_Value);
	GPIO_u8PinInit(kau8LEDConfiguration_LGB[u8LedNum].m_PinCfg);
}

/* ************************************************************************** */
/* Description : Initialize the All LED Button with Configurations			  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void LED_vidInitAll(void){
	for(u8 i = LED_Num ; i-- ; ){
		GPIO_u8PinInit(kau8LEDConfiguration_LGB[i].m_PinCfg);
	}
}

/* ************************************************************************** */
/* Description :    Set the LED ON											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LED_u8SetON(u8 u8LedNum){
	LED_tstrConfig* pstrLed =
			(LED_tstrConfig*)&kau8LEDConfiguration_LGB[u8LedNum];
	return GPIO_u8SetPinValue(pstrLed->m_PinCfg.m_Port, pstrLed->m_PinCfg.m_Pin
			,(pstrLed->m_Connection == LED_Forward) ? LED_Reverse : LED_Forward);
}

/* ************************************************************************** */
/* Description :    Set the LED OFF											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LED_u8SetOFF(u8 u8LedNum){
	LED_tstrConfig* pstrLed =
			(LED_tstrConfig*)&kau8LEDConfiguration_LGB[u8LedNum];
	return GPIO_u8SetPinValue(pstrLed->m_PinCfg.m_Port, pstrLed->m_PinCfg.m_Pin
			,(pstrLed->m_Connection == LED_Forward) ? LED_Forward : LED_Reverse);
}

/* ************************************************************************** */
/* Description :    Toggle the LED											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LED_u8Toggle(u8 u8LedNum){
	LED_tstrConfig* pstrLed =
			(LED_tstrConfig*)&kau8LEDConfiguration_LGB[u8LedNum];
	return GPIO_u8TogglePinValue(pstrLed->m_PinCfg.m_Port, pstrLed->m_PinCfg.m_Pin);
}

/*************************** E N D (LED_prg.c) ******************************/
