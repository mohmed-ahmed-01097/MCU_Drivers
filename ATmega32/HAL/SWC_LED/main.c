/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 8, 2023												  */
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

#ifdef	SWC_LED

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_cfg.h"
#include "LED_int.h"


int main(void){

	LED_vidInit(LED0);
	LED_vidInit(LED1);
	LED_vidInit(LED2);
#ifdef ETA32_KIT
	LED_vidInit(LED3);
#endif

   	while(1){
   		LED_u8SetON(LED0);
   		LED_u8SetON(LED1);
   		LED_u8SetON(LED2);
#ifdef ETA32_KIT
   		LED_u8Toggle(LED3);
#endif
	    vidMyDelay_ms(500);
	    LED_u8SetOFF(LED0);
	    LED_u8SetOFF(LED1);
	    LED_u8SetOFF(LED2);
#ifdef ETA32_KIT
	    LED_u8Toggle(LED3);
#endif
	    vidMyDelay_ms(500);
    }
   	return 0;
}
#endif

/*************************** E N D (main.c) ******************************/
