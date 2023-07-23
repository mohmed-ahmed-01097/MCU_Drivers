/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
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

#if defined(AMIT_KIT)

#define PORT_BUZZER			D
#define PIN_BUZZER			AMIT_BUZZER

#define PORT_LED0			D
#define PIN_LED0			AMIT_LED0

#define PORT_LED1			D
#define PIN_LED1			AMIT_LED1

#define PORT_LED2			D
#define PIN_LED2			AMIT_LED2

#elif defined(ETA32_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_BUZZER

#define PORT_LED0			B
#define PIN_LED0			Eta32_LED_R

#define PORT_LED1			A
#define PIN_LED1			Eta32_LED_G

#define PORT_LED2			A
#define PIN_LED2			Eta32_LED_B

#elif defined(ETA32_MINI_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_mini_BUZZER

#define PORT_LED0			C
#define PIN_LED0			Eta32_mini_LED_R

#define PORT_LED1			C
#define PIN_LED1			Eta32_mini_LED_G

#define PORT_LED2			C
#define PIN_LED2			Eta32_mini_LED_B

#endif

static volatile USART_tstrConfiguration strUSART_CFG = {
	.m_Mode 	= USART_Asynchronous,
	.m_Polarity	= USART_Transmit_Rising_Receive_Falling,
	.m_Speed 	= USART_Speed_x1,
	.m_BuadRate = USART_BuadRate_9600,
	.m_Size 	= USART_8_bit,
	.m_Parity 	= USART_Parity_Even,
	.m_Stop 	= USART_Stop_1_bit,
	.m_TXEN 	= LBTY_SET,
	.m_RXEN 	= LBTY_SET,
	.m_TXIE		= LBTY_SET,
	.m_RXIE 	= LBTY_SET,
	.m_Empty 	= LBTY_SET,
};

void TX_MSG(void);
void RX_MSG(void);

u8 u8Arr[150];
volatile u8 u8Flag = LBTY_RESET;
volatile u8 u8Char = LBTY_u8ZERO;

int main(void){

    GPIO_u8SetPinDirection(PORT_BUZZER, PIN_BUZZER, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (PORT_BUZZER, PIN_BUZZER, PIN_Low   );
    GPIO_u8SetPinDirection(PORT_LED0  , PIN_LED0  , PIN_OUTPUT);
    GPIO_u8SetPinValue	  (PORT_LED0  , PIN_LED0  , PIN_Low   );
    GPIO_u8SetPinDirection(PORT_LED1  , PIN_LED1  , PIN_OUTPUT);
    GPIO_u8SetPinValue	  (PORT_LED1  , PIN_LED1  , PIN_Low   );
    GPIO_u8SetPinDirection(PORT_LED2  , PIN_LED2  , PIN_OUTPUT);
    GPIO_u8SetPinValue	  (PORT_LED2  , PIN_LED2  , PIN_Low   );

	UART_vidInit();
	USART_vidSetCallBack_TX(TX_MSG);
	USART_vidSetCallBack_RX(RX_MSG);
	USART_vidEnableReceiveCompleteINT();

	INTP_vidEnable();

//	USART_vidSetStr((u8*)"Hello MAAM!\n\r");

	USART_u8SendBuffer((u8*)"---------->Hello MAAM!\n\r", 24);

	while(1){
		if(u8Flag){
		switch(u8Char){
			case 'a':
			case 'A':
				GPIO_u8TogglePinValue(PORT_LED0, PIN_LED0);
				USART_vidSetStr((u8*)"---------->LED0\n\r");
				break;
			case 'b':
			case 'B':
				GPIO_u8TogglePinValue(PORT_LED1, PIN_LED1);
				USART_vidSetStr((u8*)"---------->LED1\n\r");
				break;
			case 'c':
			case 'C':
				GPIO_u8TogglePinValue(PORT_LED2, PIN_LED2);
				USART_vidSetStr((u8*)"---------->LED2\n\r");
				break;
			default:
				GPIO_u8TogglePinValue(PORT_BUZZER, PIN_BUZZER);
				USART_vidSetStr((u8*)"---------->BeeB\n\r");
				break;
		}
		u8Flag = LBTY_RESET;
		}
	}
	return 0;
}

void TX_MSG(void){
//	USART_vidSetStr((u8*)"===========");
}
void RX_MSG(void){
	if(USART_u8Available()){
		USART_vidGetStr(u8Arr);
		USART_vidSetStr(u8Arr);
		u8Char = *u8Arr;
//		USART_u8GetTransmit((void*)&u8Char);
//		USART_u8SetTransmit((void*)&u8Char);
		u8Flag = LBTY_SET;
	}
}
#endif


/*************************** E N D (main.c) ******************************/
