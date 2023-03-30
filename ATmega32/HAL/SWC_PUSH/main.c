/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 24, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "PUSH_cfg.h"
#include "PUSH_int.h"


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

#ifdef	SWC_PUSH
int main(void){

#ifdef AMIT_KIT

    GPIO_u8SetPinDirection(D, AMIT_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED0, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED1, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED1, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED2, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED2, PIN_Low);

	PUSH_vidInit(PUSH0);
	PUSH_vidInit(PUSH1);
	PUSH_vidInit(PUSH2);

	u8 u8UpState, u8DownState, u8OkState;
   	while(1){
   		PUSH_u8GetPushState(PUSH0, &u8UpState  );
   		PUSH_u8GetPushState(PUSH1, &u8DownState);
   		PUSH_u8GetPushState(PUSH2, &u8OkState  );

   		if(u8UpState){
   			GPIO_u8SetPinValue(D, AMIT_LED0, PIN_High);
   		}
   		if(u8DownState){
   			GPIO_u8SetPinValue(D, AMIT_LED1, PIN_High);
   		}
   		if(u8OkState){
   			GPIO_u8SetPinValue(D, AMIT_LED2, PIN_High);
   		}
	    vidMyDelay_ms(500);
	    GPIO_u8SetPinValue(D, AMIT_LED0, PIN_Low);
	    GPIO_u8SetPinValue(D, AMIT_LED1, PIN_Low);
	    GPIO_u8SetPinValue(D, AMIT_LED2, PIN_Low);
    }

#endif
#ifdef ETA32_KIT
    GPIO_u8SetPinDirection(B, Eta32_LED_R, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (B, Eta32_LED_R, PIN_Low);

    GPIO_u8SetPinDirection(A, Eta32_LED_G, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_G, PIN_Low);

    GPIO_u8SetPinDirection(A, Eta32_LED_B, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_B, PIN_Low);

    GPIO_u8SetPinDirection(A, Eta32_LED_Y, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_Y, PIN_Low);

   	u8 u8Value = 0;

   	KPAD_vidInit();

   	while(1){

   		u8Value = (u8)KPAD_u8GetKeyNum();
        GPIO_u8SetPinValue	  (B, Eta32_LED_R, GET_BIT(u8Value, 0));
        GPIO_u8SetPinValue	  (A, Eta32_LED_G, GET_BIT(u8Value, 1));
        GPIO_u8SetPinValue	  (A, Eta32_LED_B, GET_BIT(u8Value, 2));
        GPIO_u8SetPinValue	  (A, Eta32_LED_Y, GET_BIT(u8Value, 3));

    }
#endif
   	return 0;
}
#endif

/*************************** E N D (main.c) ******************************/
