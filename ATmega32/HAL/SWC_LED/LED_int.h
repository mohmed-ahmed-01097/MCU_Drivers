/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LED_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LED_INT_H_
#define LED_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	LED_Forward = (u8)0u,
	LED_Reverse
}LED_tenuConnection;

typedef enum{
	LED_OFF = (u8)0u,
	LED_ON
}LED_tenuStatus;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if 	AMIT_KIT
#define LED_NUM		3u
#elif	ETA32_KIT
#define LED_NUM		4u
#else
#define LED_NUM		7u
#endif

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
/* Description : Initialize the LED Button direction						  */
/* Input       :	u8LedNum												  */
/* Return      :	void													  */
/* ************************************************************************** */
extern void LED_vidInit(u8 u8LedNum);

/* ************************************************************************** */
/* Description :    Set the LED ON											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LED_u8SetON(u8 u8LedNum);

/* ************************************************************************** */
/* Description :    Set the LED OFF											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LED_u8SetOFF(u8 u8LedNum);

/* ************************************************************************** */
/* Description :    Set the LED OFF											  */
/* Input       :	u8LedNum												  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
extern LBTY_tenuErrorStatus LED_u8Toggle(u8 u8LedNum);

#endif /* LED_INT_H_ */
/*************************** E N D (LED_int.h) ******************************/
