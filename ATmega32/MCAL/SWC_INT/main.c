/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01.1														  */
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

u8 u8INT_Flag = LBTY_RESET;

void Push_ISR(void);

int main(void){

    GPIO_voidInit();


    /** Buzzer **/
    GPIO_u8SetPinDirection(D, AMIT_BUZZER, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_BUZZER, PIN_Low);

    GPIO_u8SetPinDirection(D, AMIT_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED0, PIN_Low);

    INT_vidInit(INT_AMIT_PUSH2);
    INT_vidSetCallBack(INT_AMIT_PUSH2, Push_ISR);

    INTP_vidEnable();

   	while(1){
   		if(u8INT_Flag){
   			u8INT_Flag = LBTY_RESET;
			GPIO_u8SetPinValue(D, AMIT_BUZZER, PIN_High);
		    GPIO_u8SetPinValue(D, AMIT_LED0  , PIN_High);
			vidMyDelay_ms(500);
			GPIO_u8SetPinValue(D, AMIT_BUZZER, PIN_Low);
		    GPIO_u8SetPinValue(D, AMIT_LED0  , PIN_Low);
   		}
    }
   	return 0;
}

void Push_ISR(void){
	u8INT_Flag = LBTY_SET;
}

#endif

/*************************** E N D (main.c) ******************************/
