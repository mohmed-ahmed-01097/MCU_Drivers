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

#ifdef	SWC_TMR

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "INTP.h"

#include "TMR_int.h"
#include "TMR_cfg.h"

u8 u8INT_Flag = LBTY_RESET;
u8 u8Duty = LBTY_RESET;

void TMR_ISR(void);

int main(void){

    GPIO_voidInit();

    /** Buzzer **/
    GPIO_u8SetPinDirection(D, AMIT_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED0, PIN_Low);

    INTP_vidDisable();

//    TMR0_vidInit();
//    TMR0_vidSetCallBack_OverFlow(TMR_ISR);
//    PWM_vidEnable_OC0();

    TMR2_vidInit();
    TMR2_vidSetCallBack_OverFlow(TMR_ISR);
    PWM_vidEnable_OC2();

    INTP_vidEnable();

   	while(1){
//		    PWM_vidDisable_OC0();
//		    PWM_vidDisable_OC2();
//		    PWM_vidEnable_OC0();
//		    PWM_vidEnable_OC2();

   		if(u8INT_Flag){
//			PWM_u8SetDuty_OC0(u8Duty++);
			PWM_u8SetDuty_OC2(u8Duty++);
   			u8INT_Flag = LBTY_RESET;
		    GPIO_u8SetPinValue(D, AMIT_LED0  , PIN_High);
			vidMyDelay_ms(500);
		    GPIO_u8SetPinValue(D, AMIT_LED0  , PIN_Low);
			vidMyDelay_ms(500);
   		}
    }
   	return 0;
}

void TMR_ISR(void){
	u8INT_Flag = LBTY_SET;
//   GPIO_u8TogglePinValue(D, AMIT_LED0);
}

#endif

/*************************** E N D (main.c) ******************************/
