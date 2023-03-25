/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SEG_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
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
/* Seven segment
  Segments:             Pins:
          a a a              0 0 0
        f       b          5       1
        f       b          5       1
        f       b          5       1
          g g g              6 6 6
        e       c          4       2
        e       c          4       2
        e       c          4       2
          d d d   *          3 3 3   7
*/
//                         a  b  c  d  e  f  g  h
const u8 pu8SegPins[]   = {0, 1, 2, 3, 4, 5, 6, 7};
const u8 pu8SegDigits[] = {
		0x3F,			// 0  0  1	1  1  1  1	1  = 	0
		0x06,			// 0  0  0  0  0  1  1	0  =	1
		0x5B,			// 0  1  0  1  1  0  1  1  =	2
		0x4F,			// 0  1  0  0  1  1  1  1  =	3
		0x66, 			// 0  1  1  0  0  1  1  0  =	4
		0x6D,			// 0  1  1  0  1  1  0  1  =	5
		0x7D,			// 0  1  1  1  1  1  0  1  =	6
		0x07,			// 0  0  0  0  0  1  1  1  =	7
		0x7F,			// 0  1  1  1  1  1  1  1  =	8
		0x67,			// 0  1  1  0  0  1  1  1  =	9
		0x77,			// 0  1  1  1  0  1  1  1  =	A
		0x7C,			// 0  1  1  1  1  1  0  0  =	b
		0x39,			// 0  0  1  1  1  0  0  1  =	C
		0x5E,			// 0  1  0  1  1  1  1  0  =	d
		0x79, 			// 0  1  1  1  1  0  0  1  =	E
		0x71			// 0  1  1  1  0  0  0  1  =	F
	 // 0x00 			0b h  g  f  e  d  c  b  a  =	SEG
};

const u8 pu8SegDecoderPort[] = {SEG_A, SEG_B, SEG_C, SEG_D};
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
			GPIO_u8SetPinValue	(SEG_PORT_COM0, SEG_PIN_COM0, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			vidMyDelay_ms(1);
			GPIO_u8SetPinValue 	(SEG_PORT_COM0, SEG_PIN_COM0, PIN_Low);
			break;
#endif

#ifdef SEG_PIN_COM1
		case 1:
			GPIO_u8SetPinValue	(SEG_PORT_COM1, SEG_PIN_COM1, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			vidMyDelay_ms(1);
			GPIO_u8SetPinValue 	(SEG_PORT_COM1, SEG_PIN_COM1, PIN_Low);
			break;
#endif

#ifdef SEG_PIN_COM2
		case 2:
			GPIO_u8SetPinValue	(SEG_PORT_COM2, SEG_PIN_COM2, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			vidMyDelay_ms(1);
			GPIO_u8SetPinValue 	(SEG_PORT_COM2, SEG_PIN_COM2, PIN_Low);
			break;
#endif

#ifdef SEG_PIN_COM3
		case 3:
			GPIO_u8SetPinValue	(SEG_PORT_COM3, SEG_PIN_COM3, PIN_High);
			GPIO_u8SetPinValue	(SEG_PORT_DATA, SEG_h, PIN_High);
			vidMyDelay_ms(1);
			GPIO_u8SetPinValue 	(SEG_PORT_COM3, SEG_PIN_COM3, PIN_Low);
			break;
#endif
	}
}

/* ************************************************************************** */
/* Description :    7-Seg Display Digit										  */
/* Input       :	u8DigitValue, u8PortCom, u8PinCom						  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDispalyDigit(u8 u8DigitValue, u8 u8PortCom, u8 u8PinCom){
    GPIO_u8SetPinValue (u8PortCom, u8PinCom, PIN_High);

#ifdef	SEG_DECODER
	u8 u8PortValue_LOC = 0;
	GPIO_u8GetPortValue(SEG_PORT_DATA, &u8PortValue_LOC);
	GPIO_u8SetMaskValue(SEG_PORT_DATA, (0xFu << SEG_A), (u8DigitValue << SEG_A));
	for(u8 i = SEG_PINS ; --i ; ){
		GPIO_u8SetPinValue 	(SEG_PORT_DATA, pu8SegDecoderPort[i], GET_BIT(u8DigitValue, i));
	}
#else
	GPIO_u8SetPortValue(SEG_PORT_DATA, pu8SegDigits[u8DigitValue]);
#endif

	vidMyDelay_ms(5);
    GPIO_u8SetPinValue (u8PortCom, u8PinCom, PIN_Low);
}


/*************************** E N D (SEG_prg.c) ******************************/
