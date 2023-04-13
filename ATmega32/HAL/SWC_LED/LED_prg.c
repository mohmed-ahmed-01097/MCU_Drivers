/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LED_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_int.h"
#include "LED_cfg.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	LED_Forward_OFF = (u8)0u,
	LED_Forward_ON,

	LED_Reverse_ON = (u8)0u,
	LED_Reverse_OFF
}LED_tenuStatusConfig;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
extern const LED_tstrConfiguration pu8LEDConfiguration_LGB[LED_NUM];
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
	LED_tstrConfiguration* pstrLed =
			(LED_tstrConfiguration*)&pu8LEDConfiguration_LGB[u8LedNum];
	GPIO_u8SetPinDirection(pstrLed->u8PortNum, pstrLed->u8PinNum, PIN_OUTPUT);
	LED_u8SetOFF(u8LedNum);
}

/* ************************************************************************** */
/* Description :    Set the LED ON											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LED_u8SetON(u8 u8LedNum){
	LED_tstrConfiguration* pstrLed =
			(LED_tstrConfiguration*)&pu8LEDConfiguration_LGB[u8LedNum];
	u8 u8State = LBTY_u8ZERO;
	switch(pstrLed->u8Connection){
		case LED_Forward:			u8State = LED_Forward_ON;			break;
		case LED_Reverse:			u8State = LED_Reverse_ON;			break;
		default :			while(1);
	}
	return GPIO_u8SetPinValue(pstrLed->u8PortNum, pstrLed->u8PinNum, u8State);
}

/* ************************************************************************** */
/* Description :    Set the LED OFF											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LED_u8SetOFF(u8 u8LedNum){
	LED_tstrConfiguration* pstrLed =
			(LED_tstrConfiguration*)&pu8LEDConfiguration_LGB[u8LedNum];
	u8 u8State = LBTY_u8ZERO;
	switch(pstrLed->u8Connection){
		case LED_Forward:			u8State = LED_Forward_OFF;			break;
		case LED_Reverse:			u8State = LED_Reverse_OFF;			break;
		default :			while(1);
	}
	return GPIO_u8SetPinValue(pstrLed->u8PortNum, pstrLed->u8PinNum, u8State);
}

/* ************************************************************************** */
/* Description :    Set the LED OFF											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
LBTY_tenuErrorStatus LED_u8Toggle(u8 u8LedNum){
	LED_tstrConfiguration* pstrLed =
			(LED_tstrConfiguration*)&pu8LEDConfiguration_LGB[u8LedNum];
	u8 u8State = LBTY_u8ZERO;

	GPIO_u8GetPinValue(pstrLed->u8PortNum, pstrLed->u8PinNum, &u8State);
	return GPIO_u8SetPinValue(pstrLed->u8PortNum, pstrLed->u8PinNum, !u8State);
}

/*************************** E N D (LED_prg.c) ******************************/
