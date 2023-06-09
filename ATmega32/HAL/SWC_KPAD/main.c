/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Mar 24, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "KPAD_cfg.h"
#include "KPAD_int.h"

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

#ifdef	SWC_KEYPAD
int main(void){

#if 	AMIT_KIT

    GPIO_u8SetPinDirection(A, 0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, 0, PIN_Low);

    GPIO_u8SetPinDirection(A, 1, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, 1, PIN_Low);

    GPIO_u8SetPinDirection(A, 2, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, 2, PIN_Low);

#elif	ETA32_KIT

    GPIO_u8SetPinDirection(B, Eta32_LED_R, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (B, Eta32_LED_R, PIN_Low);

    GPIO_u8SetPinDirection(A, Eta32_LED_G, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_G, PIN_Low);

    GPIO_u8SetPinDirection(A, Eta32_LED_B, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_B, PIN_Low);

    GPIO_u8SetPinDirection(A, Eta32_LED_Y, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_Y, PIN_Low);

#endif

   	u8 u8Value = 0;

   	KPAD_vidInit();

   	while(1){

   		u8Value = (u8)KPAD_u8GetKeyNum();

#if 	AMIT_KIT

        GPIO_u8SetPinValue	  (A, 0, GET_BIT(u8Value, 0));
        GPIO_u8SetPinValue	  (A, 1, GET_BIT(u8Value, 1));
        GPIO_u8SetPinValue	  (A, 2, GET_BIT(u8Value, 2));

#elif	ETA32_KIT

        GPIO_u8SetPinValue	  (B, Eta32_LED_R, GET_BIT(u8Value, 0));
        GPIO_u8SetPinValue	  (A, Eta32_LED_G, GET_BIT(u8Value, 1));
        GPIO_u8SetPinValue	  (A, Eta32_LED_B, GET_BIT(u8Value, 2));
        GPIO_u8SetPinValue	  (A, Eta32_LED_Y, GET_BIT(u8Value, 3));

#endif

    }
   	return 0;
}
#endif

/*************************** E N D (main.c) ******************************/
