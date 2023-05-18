/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c												  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 10, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */


/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

#ifdef	SWC_USART

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"
#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "USART_int.h"
#include "USART_cfg.h"

u8 u8Arr[150];

void TX_MSG(void);
void RX_MSG(void);

int main(void){

#if defined(AMIT_KIT)
    GPIO_u8SetPinDirection(D, AMIT_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED0, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED1, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED1, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED2, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED2, PIN_Low);
#elif defined(ETA32_KIT)
    GPIO_u8SetPinDirection(A, Eta32_LED_G, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_G, PIN_Low);
    GPIO_u8SetPinDirection(A, Eta32_LED_B, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_B, PIN_Low);
    GPIO_u8SetPinDirection(A, Eta32_LED_Y, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_Y, PIN_Low);

#endif

	UART_vidInit();
	USART_vidSetCallBack_TX(TX_MSG);
	USART_vidSetCallBack_RX(RX_MSG);

	INTP_vidEnable();

	USART_vidSetStr((u8*)"Hello MAAM!\n\r");

	USART_u8SendBuffer((u8*)"Hello MAAM!\n\r", 14);

	u8 u8Char = LBTY_u8ZERO;
	while(1){
		USART_u8ReceiveBuffer(&u8Char, 1);
		switch(u8Char){
			case 'a':
			case 'A':
#if defined(AMIT_KIT)
				GPIO_u8TogglePinValue(D, AMIT_LED0);
#elif defined(ETA32_KIT)
				GPIO_u8TogglePinValue(D, Eta32_LED_G);
#endif
				break;
			case 'b':
			case 'B':
#if defined(AMIT_KIT)
				GPIO_u8TogglePinValue(D, AMIT_LED1);
#elif defined(ETA32_KIT)
				GPIO_u8TogglePinValue(D, Eta32_LED_B);
#endif
				break;
			case 'c':
			case 'C':
#if defined(AMIT_KIT)
				GPIO_u8TogglePinValue(D, AMIT_LED2);
#elif defined(ETA32_KIT)
				GPIO_u8TogglePinValue(D, Eta32_LED_Y);
#endif
				break;
			default:
				break;
		}
		u8Char = LBTY_u8ZERO;
	}
	return 0;
}

void TX_MSG(void){
	USART_vidSetStr((u8*)"===========");
}
void RX_MSG(void){
	if(USART_u8Available()){
		USART_vidGetStr(u8Arr);
		USART_vidSetStr(u8Arr);
		USART_vidSetStr((u8*)"---------->Hello MAAM!\n\r");
	}
	USART_vidSetStr((u8*)"\n");
}
#endif


/*************************** E N D (main.c) ******************************/
