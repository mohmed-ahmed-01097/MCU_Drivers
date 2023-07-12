/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 24, 2023												  */
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

#ifdef	SWC_GPIO

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#if defined(AMIT_KIT)

#define PORT_BUZZER			D
#define PIN_BUZZER			AMIT_BUZZER

#define PORT_LED0			D
#define PIN_LED0			AMIT_LED0

#define PORT_LED1			D
#define PIN_LED1			AMIT_LED1

#define PORT_LED2			D
#define PIN_LED2			AMIT_LED2

#define PORT_RELAY0			D
#define PIN_RELAY0			AMIT_RELAY0

#define PORT_RELAY1			D
#define PIN_RELAY1			AMIT_RELAY1

#define PORT_PUSH0			D
#define PIN_PUSH0			AMIT_PUSH0

#define PORT_PUSH1			D
#define PIN_PUSH1			AMIT_PUSH1

#define PORT_PUSH2			D
#define PIN_PUSH2			AMIT_PUSH2
#elif defined(ETA32_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_BUZZER

#define PORT_LED0			B
#define PIN_LED0			Eta32_LED_R

#define PORT_LED1			A
#define PIN_LED1			Eta32_LED_G

#define PORT_LED2			A
#define PIN_LED2			Eta32_LED_B

#define PORT_RELAY0			C
#define PIN_RELAY0			Eta32_RELAY0

#define PORT_RELAY1			A
#define PIN_RELAY1			Eta32_RELAY1

#define PORT_PUSH0			D
#define PIN_PUSH0			Eta32_Keypad_col0

#define PORT_PUSH1			D
#define PIN_PUSH1			Eta32_Keypad_col1

#define PORT_PUSH2			D
#define PIN_PUSH2			Eta32_Keypad_col2

#elif defined(ETA32_MINI_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_mini_BUZZER

#define PORT_LED0			C
#define PIN_LED0			Eta32_mini_LED_R

#define PORT_LED1			C
#define PIN_LED1			Eta32_mini_LED_G

#define PORT_LED2			C
#define PIN_LED2			Eta32_mini_LED_B

#define PORT_RELAY0			C
#define PIN_RELAY0			Eta32_mini_RELAY0

#define PORT_RELAY1			C
#define PIN_RELAY1			Eta32_mini_RELAY1

#define PORT_PUSH0			D
#define PIN_PUSH0			Eta32_Keypad_col0

#define PORT_PUSH1			D
#define PIN_PUSH1			Eta32_Keypad_col1

#define PORT_PUSH2			D
#define PIN_PUSH2			Eta32_Keypad_col2

#endif

void delay_test(void);
int main(void){

	GPIO_vidInit();

	/** Leds **/
	GPIO_u8SetPinDirection(PORT_LED0, PIN_LED0, PIN_OUTPUT);
	GPIO_u8SetPinValue    (PORT_LED0, PIN_LED0, PIN_Low);
	GPIO_u8SetPinDirection(PORT_LED1, PIN_LED1, PIN_OUTPUT);
	GPIO_u8SetPinValue    (PORT_LED1, PIN_LED1, PIN_Low);
	GPIO_u8SetPinDirection(PORT_LED2, PIN_LED2, PIN_OUTPUT);
	GPIO_u8SetPinValue    (PORT_LED2, PIN_LED2, PIN_Low);

	/** Buzzer **/
	GPIO_u8SetPinDirection(PORT_BUZZER, PIN_BUZZER, PIN_OUTPUT);
	GPIO_u8SetPinValue    (PORT_BUZZER, PIN_BUZZER, PIN_Low);

	delay_test();

	u8 u8LedNum = 2;
	while(1){
		switch(u8LedNum = ++u8LedNum % 3){
		case 0 :
			GPIO_u8SetPinValue(PORT_LED0, PIN_LED0, PIN_High);
			GPIO_u8SetPinValue(PORT_LED2, PIN_LED2, PIN_Low);
			break;
		case 1 :
			GPIO_u8SetPinValue(PORT_LED1, PIN_LED1, PIN_High);
			GPIO_u8SetPinValue(PORT_LED0, PIN_LED0, PIN_Low);
			break;
		case 2 :
			GPIO_u8SetPinValue(PORT_LED2, PIN_LED2, PIN_High);
			GPIO_u8SetPinValue(PORT_LED1, PIN_LED1, PIN_Low);
			break;
		default :
			GPIO_u8SetPinValue(PORT_LED0, PIN_LED0, PIN_Low);
			GPIO_u8SetPinValue(PORT_LED1, PIN_LED1, PIN_Low);
			GPIO_u8SetPinValue(PORT_LED2, PIN_LED2, PIN_Low);
		}
		if(u8LedNum == 2){
			GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_High);
			vidMyDelay_ms(500);
			GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_Low);
		}else{
			vidMyDelay_ms(500);
		}

	}
	return 0;
}

void delay_test(void){
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_High);
	vidMyDelay_ms(1000);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_Low);
	vidMyDelay_ms(1500);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_High);
	DELAY_LOOP_MS(1000);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_Low);
	DELAY_LOOP_MS(1500);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_High);
	DELAY_MS(1000);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_Low);
	DELAY_MS(1500);
}

#endif

/*************************** E N D (main.c) ******************************/
