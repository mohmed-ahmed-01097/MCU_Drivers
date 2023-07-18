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

#ifdef	SWC_ADC

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LCD_int.h"
#include "LCD_cfg.h"

#include "INTP.h"

#include "ADC_int.h"
#include "ADC_cfg.h"

int main(void){

	LCD_vidInit();

    //MCU_vidEnableGlobalInterrupt();

    ADC_vidInit();
    ADC_u8CofigChannel(ADC_CH0);

    u16 u16AdcReadValue = 0;
    f32 f32Volt = 0.0f;
    f32 f32LcdRead = 0.0f;
   	while(1){

//   		ADC_vidSetChannel(ADC_CH1);
//   		ADC_vidStartConversion();
//   		ADC_vidWaitConversion();
   		while(1){
   			ADC_u8ReadChannel(ADC_CH0, &u16AdcReadValue);
   			f32Volt = ADC_f32GetVoltage() * 100;

   			LCD_u8SetFloat(f32Volt, 0, 0);
   			LCD_u8SetNum(u16AdcReadValue, 8, 0);

   			while(LCD_u8SetFloat_Rise(f32Volt, 0, 1)){
   				LCD_u8GetFloat(&f32LcdRead, 0, 1);
   				LCD_u8SetFloat(f32LcdRead, 8, 1);
   			}
   			vidMyDelay_ms(LCD_DELAY_WAIT);
   			if(f32Volt == 0.0f)			break;
   		}
   		LCD_u8ClrDisplay();
   		while(1){
   			ADC_u8SetChannel(ADC0_ADC1_1X);
   			ADC_vidStartConversion();
   			ADC_vidWaitConversion();
   			f32Volt = ADC_f32GetVoltage();

   			LCD_u8SetFloat(f32Volt, 0, 0);

   			ADC_u8ReadChannel(ADC0, &u16AdcReadValue);
   			LCD_u8SetNum(u16AdcReadValue, 0, 1);

   			ADC_u8ReadChannel(ADC1, &u16AdcReadValue);
   			LCD_u8SetNum(u16AdcReadValue, 8, 1);

   			vidMyDelay_ms(LCD_DELAY_WAIT);
   			if(f32Volt == 0.0f)			break;
   		}
   		LCD_u8ClrDisplay();

    }
   	return 0;
}

#endif

/*************************** E N D (main.c) ******************************/
