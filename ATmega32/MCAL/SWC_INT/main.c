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

#ifdef	SWC_INT

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "INTP.h"

#include "INT_int.h"
#include "INT_cfg.h"

#if defined(AMIT_KIT)

#define PORT_BUZZER			D
#define PIN_BUZZER			AMIT_BUZZER

#define PORT_LED0			D
#define PIN_LED0			AMIT_LED0

#elif defined(ETA32_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_BUZZER

#define PORT_LED0			B
#define PIN_LED0			Eta32_LED_R

#elif defined(ETA32_MINI_KIT)

#define PORT_BUZZER			C
#define PIN_BUZZER			Eta32_mini_BUZZER

#define PORT_LED0			C
#define PIN_LED0			Eta32_mini_LED_R

#endif


volatile u8 u8INT_Flag = LBTY_RESET;

void Push_ISR(void);

int main(void){

    GPIO_vidInit();

    /** Buzzer **/
    GPIO_u8SetPinDirection(PORT_BUZZER, PIN_BUZZER, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (PORT_BUZZER, PIN_BUZZER, PIN_Low);

    GPIO_u8SetPinDirection(PORT_LED0, PIN_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (PORT_LED0, PIN_LED0, PIN_Low);

    INT_vidInit(INT_PUSH);
    INT_vidSetCallBack(INT_PUSH, Push_ISR);

    INTP_vidEnable();

   	while(1){
   		if(u8INT_Flag){
   			u8INT_Flag = LBTY_RESET;
			GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_High);
		    GPIO_u8SetPinValue(PORT_LED0, PIN_LED0  , PIN_High);
			vidMyDelay_ms(500);
			GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_Low);
		    GPIO_u8SetPinValue(PORT_LED0, PIN_LED0  , PIN_Low);
   		}
    }
   	return 0;
}

void Push_ISR(void){
	u8INT_Flag = LBTY_SET;
}

#endif

/*************************** E N D (main.c) ******************************/
