/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_cfg.h"
#include "LED_int.h"


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
int main(void){

#ifdef AMIT_KIT

	LED_vidInit(LED0);
	LED_vidInit(LED1);
	LED_vidInit(LED2);

   	while(1){
   		LED_u8SetON(LED0);
   		LED_u8SetON(LED1);
   		LED_u8SetON(LED2);
	    vidMyDelay_ms(500);
	    LED_u8SetOFF(LED0);
	    LED_u8SetOFF(LED1);
	    LED_u8SetOFF(LED2);
	    vidMyDelay_ms(500);
    }

#endif
#ifdef ETA32_KIT
	LED_vidInit(LED0);
	LED_vidInit(LED1);
	LED_vidInit(LED2);
	LED_vidInit(LED3);
   	while(1){
   		LED_u8SetON(LED0);
   		LED_u8SetON(LED1);
   		LED_u8SetON(LED2);
   		LED_u8Toggle(LED3);
	    vidMyDelay_ms(500);
	    LED_u8SetOFF(LED0);
	    LED_u8SetOFF(LED1);
	    LED_u8SetOFF(LED2);
	    LED_u8Toggle(LED3);
	    vidMyDelay_ms(500);
    }
#endif
   	return 0;
}
#endif

/*************************** E N D (main.c) ******************************/
