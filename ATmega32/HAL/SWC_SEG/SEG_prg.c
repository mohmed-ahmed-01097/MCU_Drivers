/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SEG_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
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

#include "SEG_int.h"
#include "SEG_cfg.h"
#include "SEG_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

static u16 u16NumValue_GLB;
static u8  u8Dot_GLB;

#ifdef	SEG_DECODER
extern const u8 kau8SegDecoderPort[];
#else
extern const u8 kau8SegPins[];
extern const u8 kau8SegDigits[];
#endif
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

#ifdef SEG_PIN_COM4
	GPIO_u8SetPinDirection(SEG_PORT_COM4, SEG_PIN_COM4, PIN_OUTPUT);
	GPIO_u8SetPinValue    (SEG_PORT_COM4, SEG_PIN_COM4, PIN_Low);
#endif

#ifdef SEG_PIN_COM5
	GPIO_u8SetPinDirection(SEG_PORT_COM5, SEG_PIN_COM5, PIN_OUTPUT);
	GPIO_u8SetPinValue    (SEG_PORT_COM5, SEG_PIN_COM5, PIN_Low);
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
#endif

GPIO_u8SetPinDirection(SEG_PORT_DOT, SEG_h, PIN_OUTPUT);
GPIO_u8SetPinValue	  (SEG_PORT_DOT, SEG_h, PIN_Low);

}

/* ************************************************************************** */
/* Description :    7-Seg Display Value										  */
/* Input       :	u16NumValue, u8Dot										  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDisplay(u16 u16NumValue, u8 u8Dot){
#ifdef SEG_PIN_COM0
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM0, SEG_PIN_COM0, (u8Dot == SEG_COM0));
#endif

#ifdef SEG_PIN_COM1
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM1, SEG_PIN_COM1, (u8Dot == SEG_COM1));
#endif

#ifdef SEG_PIN_COM2
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM2, SEG_PIN_COM2, (u8Dot == SEG_COM2));
#endif

#ifdef SEG_PIN_COM3
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM3, SEG_PIN_COM3, (u8Dot == SEG_COM3));
#endif

#ifdef SEG_PIN_COM4
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM4, SEG_PIN_COM4, (u8Dot == SEG_COM4));
#endif

#ifdef SEG_PIN_COM5
	u16NumValue /= 10u;
	SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM5, SEG_PIN_COM5, (u8Dot == SEG_COM5));
#endif

}

/* ************************************************************************** */
/* Description :    7-Seg Display Real Num Value							  */
/* Input       :	f32NumValue, 											  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDisplayFloat(f32 f32NumValue){
	SEG_vidDisplay((u16)(f32NumValue * SEG_FLOAT_MUL), SEG_FLOAT_DOT);
}

void SEG_vidDisplayFloat_Blink(f32 f32NumValue){
	static u8 u8Tick = LBTY_u8ZERO;
	static u8 u8Blink = LBTY_SET;

	if((++u8Tick > SEG_NUM_DELAY)){
		u8Blink = LBTY_RESET;
		if(u8Tick >= SEG_NUM_RATE){
			u8Tick = LBTY_u8ZERO;
			u8Blink = LBTY_SET;
		}
	}

	if(u8Blink){
		SEG_vidDisplay((u16)(f32NumValue * SEG_FLOAT_MUL), SEG_FLOAT_DOT);
	}else{
		vidMyDelay_ms(SEG_DELAY * SEG_NUM * 2);
	}
}

/* ************************************************************************** */
/* Description :    7-Seg Display Num Value									  */
/* Input       :	u16NumValue												  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDisplayNum(u16 u16NumValue){
	SEG_vidDisplay(u16NumValue, LBTY_u8MAX);
}

void SEG_vidDisplayNum_Blink(u16 u16NumValue){
	static u8 u8Tick = LBTY_u8ZERO;
	static u8 u8Blink = LBTY_SET;

	if((++u8Tick > SEG_NUM_DELAY)){
		u8Blink = LBTY_RESET;
		if(u8Tick >= SEG_NUM_RATE){
			u8Tick = LBTY_u8ZERO;
			u8Blink = LBTY_SET;
		}
	}

	if(u8Blink){
		SEG_vidDisplay(u16NumValue, LBTY_u8MAX);
	}else{
		vidMyDelay_ms(SEG_DELAY * SEG_NUM * SEG_DELAY);
	}
}

/* ************************************************************************** */
/* Description :    7-Seg Display Digit	with Dot							  */
/* Input       :	u8DigitValue, u8PortCom, u8PinCom, u8Dot				  */
/* Return      :	void													  */
/* ************************************************************************** */
void SEG_vidDispalyDigit(u8 u8DigitValue, u8 u8PortCom, u8 u8PinCom, u8 u8Dot){

#ifdef	SEG_DECODER
	u8 u8PortValue_LOC = 0;
	GPIO_u8GetPortValue(SEG_PORT_DATA, &u8PortValue_LOC);
	for(u8 i = SEG_PINS ; i-- ; ){
		GPIO_u8SetPinValue 	(SEG_PORT_DATA, kau8SegDecoderPort[i], GET_BIT(u8DigitValue, i));
	}
#else
	GPIO_u8SetPortValue(SEG_PORT_DATA, kau8SegDigits[u8DigitValue] << SEG_a);
#endif

	GPIO_u8SetPinValue (SEG_PORT_DOT, SEG_h, u8Dot);
	GPIO_u8SetPinValue (u8PortCom, u8PinCom, PIN_High);
	vidMyDelay_ms(SEG_DELAY);
	GPIO_u8SetPinValue (u8PortCom, u8PinCom, PIN_Low);
}

/* ************************************************************************** */
/* Description :    7-Seg Display Update Digit								  */
/* Input       :	void													  */
/* Return      :	LBTY_tenuErrorStatus									  */
/* ************************************************************************** */
void SEG_vidSetNum(u16 u16NumValue, u8 u8Dot){
	u16NumValue_GLB = u16NumValue;
	u8Dot_GLB       = u8Dot;
}
LBTY_tenuErrorStatus SEG_u8Update(void){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	static u8 u8Com = LBTY_u8ZERO;

	u16 u16NumValue = u16NumValue_GLB;
	u8 u8Dot        = u8Dot_GLB;

	switch(u8Com){
#ifdef SEG_PIN_COM0
	case SEG_COM0:
		SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM0, SEG_PIN_COM0, (u8Dot == SEG_COM0));
		break;
#endif

#ifdef SEG_PIN_COM1
	case SEG_COM1:
		u16NumValue /= 10u;
		SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM1, SEG_PIN_COM1, (u8Dot == SEG_COM1));
		break;
#endif

#ifdef SEG_PIN_COM2
	case SEG_COM2:
		u16NumValue /= 10u;
		SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM2, SEG_PIN_COM2, (u8Dot == SEG_COM2));
		break;
#endif

#ifdef SEG_PIN_COM3
	case SEG_COM3:
		u16NumValue /= 10u;
		SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM3, SEG_PIN_COM3, (u8Dot == SEG_COM3));
		break;
#endif

#ifdef SEG_PIN_COM4
	case SEG_COM4:
		u16NumValue /= 10u;
		SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM4, SEG_PIN_COM4, (u8Dot == SEG_COM4));
		break;
#endif

#ifdef SEG_PIN_COM5
	case SEG_COM5:
		u16NumValue /= 10u;
		SEG_vidDispalyDigit(u16NumValue % 10u, SEG_PORT_COM5, SEG_PIN_COM5, (u8Dot == SEG_COM5));
		break;
#endif
	default:
		break;
	}
	u8Com = (u8Com + 1) % SEG_NUM;

	if(!u8Com){
		u8RetErrorState = LBTY_NOK;
	}
	return u8RetErrorState;

}

/*************************** E N D (SEG_prg.c) ******************************/
