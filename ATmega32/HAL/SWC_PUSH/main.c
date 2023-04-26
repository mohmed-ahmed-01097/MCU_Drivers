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
#include "LCTY_int.h"

#include "DELAY.h"
#include "INTP.h"

#include "INT_int.h"
#include "INT_cfg.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_int.h"
#include "LED_cfg.h"

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

u8 u8INT_Flag = LBTY_RESET;

void Push_ISR(void);

int main(void){

#ifdef AMIT_KIT

	PUSH_vidInit(PUSH0);
	PUSH_vidInit(PUSH1);
	PUSH_vidInit(PUSH2);

    INT_vidInit(INT_AMIT_PUSH2);
    INT_vidSetCallBack(INT_AMIT_PUSH2, Push_ISR);

	LED_vidInit(LED0);
	LED_vidInit(LED1);
	LED_vidInit(LED2);

    INTP_vidEnable();
	u8 u8UpState, u8DownState;
   	while(1){

   		if(u8INT_Flag){
			LED_u8SetON(LED0);
			PUSH_u8GetPushState(PUSH0, &u8UpState  );
			PUSH_u8GetPushState(PUSH1, &u8DownState);

			if(u8UpState){
				LED_u8SetON(LED1);
			}
			if(u8DownState){
				LED_u8SetON(LED2);
			}
			vidMyDelay_ms(500);
			LED_u8SetOFF(LED1);
			LED_u8SetOFF(LED2);
   		}
		LED_u8SetOFF(LED0);
    }

#endif
#ifdef ETA32_KIT

	PUSH_vidInit(PUSH0);
	PUSH_vidInit(PUSH1);
	PUSH_vidInit(PUSH2);
	PUSH_vidInit(PUSH3);

	LED_vidInit(LED0);
	LED_vidInit(LED1);
	LED_vidInit(LED2);
	LED_vidInit(LED3);

	u8 u8State0, u8State1, u8State2, u8State3;
   	while(1){
   		PUSH_u8GetPushState(PUSH0, &u8State0);
   		PUSH_u8GetPushState(PUSH1, &u8State1);
   		PUSH_u8GetPushState(PUSH2, &u8State2);
   		PUSH_u8GetPushState(PUSH3, &u8State3);

   		if(u8State0){
   			LED_u8SetON(LED0);
   		}
   		if(u8State1){
   			LED_u8SetON(LED1);
   		}
   		if(u8State2){
   			LED_u8SetON(LED2);
   		}
   		if(u8State3){
   			LED_u8SetON(LED3);
   		}
	    vidMyDelay_ms(500);
	    LED_u8SetOFF(LED0);
	    LED_u8SetOFF(LED1);
	    LED_u8SetOFF(LED2);
	    LED_u8SetOFF(LED3);
    }

#endif
   	return 0;
}

void Push_ISR(void){
	u8INT_Flag ^= LBTY_SET;
}
#endif

/*************************** E N D (main.c) ******************************/
