/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : May 3, 2023												  */
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

#ifdef	SWC_ANA

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "ANA_int.h"
#include "ANA_cfg.h"

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

int main(void){

    GPIO_u8SetPinDirection(PORT_LED0, PIN_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (PORT_LED0, PIN_LED0, PIN_Low);

    ANA_vidInit();

	u8 u8Output;
   	while(1){
   	    ANA_vidGetOutput(&u8Output);
	    GPIO_u8SetPinValue(PORT_LED0, PIN_LED0, u8Output);
		vidMyDelay_ms(100);
    }

   	return 0;
}

#endif

/*************************** E N D (main.c) ******************************/
