/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SEG_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "SEG_int.h"
#include "SEG_cfg.h"

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

extern const u8 kau8SegPins[];
extern const u8 kau8SegDigits[];
extern const u8 kau8SegDecoderPort[];

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :    7-Seg initialization									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidInit(void){

#ifdef SEG_PIN_COM0
	GPIO_u8SetPinDirection(SEG_PORT_COM0, SEG_PIN_COM0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_COM0, SEG_PIN_COM0, PIN_Low);
#endif

#ifdef SEG_PIN_COM1
    GPIO_u8SetPinDirection(SEG_PORT_COM1, SEG_PIN_COM1, PIN_OUTPUT);
    GPIO_u8SetPinValue    (SEG_PORT_COM1, SEG_PIN_COM1, PIN_Low);
#endif

#ifdef SEG_PIN_COM2
    GPIO_u8SetPinDirection(SEG_PORT_COM2, SEG_PIN_COM2, PIN_OUTPUT);
    GPIO_u8SetPinValue    (SEG_PORT_COM2, SEG_PIN_COM2, PIN_Low);
#endif

#ifdef SEG_PIN_COM3
    GPIO_u8SetPinDirection(SEG_PORT_COM3, SEG_PIN_COM3, PIN_OUTPUT);
    GPIO_u8SetPinValue    (SEG_PORT_COM3, SEG_PIN_COM3, PIN_Low);
#endif

#ifdef	SEG_DECODER
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_A, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_A, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_B, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_B, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_C, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_C, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_D, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_D, PIN_Low);
#else
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_a, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_a, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_b, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_b, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_c, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_c, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_d, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_d, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_e, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_e, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_f, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_f, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_g, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_g, PIN_Low);
    GPIO_u8SetPinDirection(SEG_PORT_DATA, SEG_h, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (SEG_PORT_DATA, SEG_h, PIN_Low);
#endif

}

/* ************************************************************************** */
/* Description :    7-Seg Display Num Value									  */
/* Input       :	u16NumValue, 											  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDisplayNum(u16 u16NumValue){
#ifdef SEG_PIN_COM0
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM0, SEG_PIN_COM0);
#endif

#ifdef SEG_PIN_COM1
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM1, SEG_PIN_COM1);
#endif

#ifdef SEG_PIN_COM2
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM2, SEG_PIN_COM2);
#endif

#ifdef SEG_PIN_COM3
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM3, SEG_PIN_COM3);
#endif

}

/* ************************************************************************** */
/* Description :    7-Seg Display Dot 										  */
/* Input       :	u8DotDigit	 											  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDisplayDot(u8 u8DotDigit){
	switch(u8DotDigit){
#ifdef SEG_PIN_COM0
		case 0:
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_COM0, SEG_PIN_COM0, PIN_High);
			vidMyDelay_ms(DOT_DELAY);
			GPIO_u8SetPinValue 	(SEG_PORT_COM0, SEG_PIN_COM0, PIN_Low);
			break;
#endif

#ifdef SEG_PIN_COM1
		case 1:
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_COM1, SEG_PIN_COM1, PIN_High);
			vidMyDelay_ms(DOT_DELAY);
			GPIO_u8SetPinValue 	(SEG_PORT_COM1, SEG_PIN_COM1, PIN_Low);
			break;
#endif

#ifdef SEG_PIN_COM2
		case 2:
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_COM2, SEG_PIN_COM2, PIN_High);
			vidMyDelay_ms(DOT_DELAY);
			GPIO_u8SetPinValue 	(SEG_PORT_COM2, SEG_PIN_COM2, PIN_Low);
			break;
#endif

#ifdef SEG_PIN_COM3
		case 3:
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_COM3, SEG_PIN_COM3, PIN_High);
			vidMyDelay_ms(DOT_DELAY);
			GPIO_u8SetPinValue 	(SEG_PORT_COM3, SEG_PIN_COM3, PIN_Low);
			break;
#endif
	}
	GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_Low);
}

/* ************************************************************************** */
/* Description :    7-Seg Display Digit										  */
/* Input       :	u8DigitValue, u8PortCom, u8PinCom						  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDispalyDigit(u8 u8DigitValue, u8 u8PortCom, u8 u8PinCom){

#ifdef	SEG_DECODER
	u8 u8PortValue_LOC = 0;
	GPIO_u8GetPortValue(SEG_PORT_DATA, &u8PortValue_LOC);
	for(u8 i = SEG_PINS ; i-- ; ){
		GPIO_u8SetPinValue 	(SEG_PORT_DATA, kau8SegDecoderPort[i], GET_BIT(u8DigitValue, i));
	}
#else
	GPIO_u8SetPortValue(SEG_PORT_DATA, kau8SegDigits[u8DigitValue]);
#endif

    GPIO_u8SetPinValue (u8PortCom, u8PinCom, PIN_High);
	vidMyDelay_ms(SEG_DELAY);
    GPIO_u8SetPinValue (u8PortCom, u8PinCom, PIN_Low);
}


/*************************** E N D (SEG_prg.c) ******************************/
