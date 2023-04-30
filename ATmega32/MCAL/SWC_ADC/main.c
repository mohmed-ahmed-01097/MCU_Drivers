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

#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "INTP.h"

#include "ADC_int.h"
#include "ADC_cfg.h"

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

#ifdef	SWC_ADC

int main(void){

#ifdef AMIT_KIT
    GPIO_u8SetPinDirection(D, AMIT_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED0, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED1, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED1, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED2, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED2, PIN_Low);

    //MCU_vidEnableGlobalInterrupt();

    ADC_vidInit();
    ADC_vidCofigChannel(ADC_CH1);
    u16 u16AdcReadValue = 0;

   	while(1){

//   		ADC_vidSetChannel(ADC_CH1);
//   		ADC_vidStartConversion();
//   		ADC_vidWaitConversion();
//   		u16AdcReadValue = (u8)(ADC_u16GetData() * 7u / 1023.0);

   		ADC_u8ReadChannel(ADC_CH1, &u16AdcReadValue);
  		u16AdcReadValue = (u8)(u16AdcReadValue * 7u / 1023.0);

	    GPIO_u8SetPinValue(D, AMIT_LED0, GET_BIT(u16AdcReadValue, 0));
	    GPIO_u8SetPinValue(D, AMIT_LED1, GET_BIT(u16AdcReadValue, 1));
	    GPIO_u8SetPinValue(D, AMIT_LED2, GET_BIT(u16AdcReadValue, 2));
		vidMyDelay_ms(500);
	    GPIO_u8SetPinValue(D, AMIT_LED0, PIN_Low);
	    GPIO_u8SetPinValue(D, AMIT_LED1, PIN_Low);
	    GPIO_u8SetPinValue(D, AMIT_LED2, PIN_Low);
		vidMyDelay_ms(500);
    }
#endif
#ifdef ETA32_KIT
    GPIO_u8SetPinDirection(A, Eta32_LED_G, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_G, PIN_Low);
    GPIO_u8SetPinDirection(A, Eta32_LED_B, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_B, PIN_Low);
    GPIO_u8SetPinDirection(A, Eta32_LED_Y, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_Y, PIN_Low);

    //MCU_vidEnableGlobalInterrupt();

    ADC_vidInit();
    ADC_vidCofigChannel(ADC_CH1);
    u16 u16AdcReadValue = 0;

   	while(1){

//   		ADC_vidSetChannel(ADC_CH1);
//   		ADC_vidStartConversion();
//   		ADC_vidWaitConversion();
//   		u16AdcReadValue = (u8)(ADC_u16GetData() * 7u / 1023.0);

   		ADC_u8ReadChannel(ADC_CH1, &u16AdcReadValue);
  		u16AdcReadValue = (u8)(u16AdcReadValue * 7u / 1023.0);

	    GPIO_u8SetPinValue(A, Eta32_LED_G, GET_BIT(u16AdcReadValue, 0));
	    GPIO_u8SetPinValue(A, Eta32_LED_B, GET_BIT(u16AdcReadValue, 1));
	    GPIO_u8SetPinValue(A, Eta32_LED_Y, GET_BIT(u16AdcReadValue, 2));
		vidMyDelay_ms(500);
	    GPIO_u8SetPinValue(A, Eta32_LED_G, PIN_Low);
	    GPIO_u8SetPinValue(A, Eta32_LED_B, PIN_Low);
	    GPIO_u8SetPinValue(A, Eta32_LED_Y, PIN_Low);
		vidMyDelay_ms(500);
    }
#endif

   	return 0;
}

#endif

/*************************** E N D (main.c) ******************************/
