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

#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LCD_int.h"
#include "LCD_cfg.h"

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

#ifdef	SWC_LCD

#include "ADC_int.h"
#include "ADC_cfg.h"

void vid_LcdWelcome(void);
void vid_LcdShifting(void);
void vid_LcdCursor(void);
void vid_LcdDisplay(void);

void vid_LcdIntRise(void);
void vid_LcdFloatRise(void);

int main(void){

	LCD_vidInit();

	vid_LcdWelcome();
	vid_LcdShifting();
	vid_LcdCursor();
	vid_LcdDisplay();

	LCD_u8ClrDisplay();

	vid_LcdIntRise();
	vid_LcdFloatRise();

	LCD_u8ClrDisplay();
	LCD_u8Home();

#ifdef AMIT_KIT
    GPIO_u8SetPinDirection(D, AMIT_LED0, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED0, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED1, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED1, PIN_Low);
    GPIO_u8SetPinDirection(D, AMIT_LED2, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (D, AMIT_LED2, PIN_Low);

    ADC_vidInit();
    ADC_u8CofigChannel(ADC_CH1);

    u16 u16AdcReadValue = 0;
    f32 f32Volt = 0.0f;

   	while(1){
   		ADC_u8ReadChannel(ADC_CH1, &u16AdcReadValue);
  		u16AdcReadValue = (u8)(u16AdcReadValue * 7u / 1023.0);
  		f32Volt = ADC_f32GetVoltage() * 100;

	    GPIO_u8SetPinValue(D, AMIT_LED0, GET_BIT(u16AdcReadValue, 0));
	    GPIO_u8SetPinValue(D, AMIT_LED1, GET_BIT(u16AdcReadValue, 1));
	    GPIO_u8SetPinValue(D, AMIT_LED2, GET_BIT(u16AdcReadValue, 2));

		LCD_u8SetFloat(f32Volt, 0, 0);
		LCD_u8SetFloat_Rise(f32Volt, 0, 1);
  		vidMyDelay_ms(LCD_DELAY_WAIT);

  		f32 f32LcdRead = 0.0f;
  		LCD_u8GetFloat(&f32LcdRead, 0, 1);
  		LCD_u8SetFloat(f32LcdRead, 8, 0);

	    GPIO_u8SetPinValue(D, AMIT_LED0, 0);
	    GPIO_u8SetPinValue(D, AMIT_LED1, 0);
	    GPIO_u8SetPinValue(D, AMIT_LED2, 0);

    }
#endif
#ifdef ETA32_KIT
    GPIO_u8SetPinDirection(A, Eta32_LED_G, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_G, PIN_Low);
    GPIO_u8SetPinDirection(A, Eta32_LED_B, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_B, PIN_Low);
    GPIO_u8SetPinDirection(A, Eta32_LED_Y, PIN_OUTPUT);
    GPIO_u8SetPinValue	  (A, Eta32_LED_Y, PIN_Low);

    ADC_vidInit();
    ADC_u8CofigChannel(ADC_CH1);

    u16 u16AdcReadValue = 0;
    f32 f32Volt = 0.0f;

   	while(1){
   		ADC_u8ReadChannel(ADC_CH1, &u16AdcReadValue);
  		u16AdcReadValue = (u8)(u16AdcReadValue * 7u / 1023.0);
  		f32Volt = ADC_f32GetVoltage() * 100;

	    GPIO_u8SetPinValue(A, Eta32_LED_G, GET_BIT(u16AdcReadValue, 0));
	    GPIO_u8SetPinValue(A, Eta32_LED_B, GET_BIT(u16AdcReadValue, 1));
	    GPIO_u8SetPinValue(A, Eta32_LED_Y, GET_BIT(u16AdcReadValue, 2));

		LCD_u8SetFloat(f32Volt, 0, 0);
		LCD_u8SetFloat_Rise(f32Volt, 0, 1);
  		vidMyDelay_ms(LCD_DELAY_WAIT);

	    GPIO_u8SetPinValue(A, Eta32_LED_G, PIN_Low);
	    GPIO_u8SetPinValue(A, Eta32_LED_B, PIN_Low);
	    GPIO_u8SetPinValue(A, Eta32_LED_Y, PIN_Low);
    }
#endif

   	return 0;
}

void vid_LcdWelcome(void){
	LCD_u8SetString((u8*)"4-<\"  MAAM  \">", 0, 3);
	LCD_u8SetSpecialChar(0, 14, 3);
	LCD_u8SetSpecialChar(1, 15, 3);
	LCD_u8SetString((u8*)"3-<\"  MAAM  \">", 0, 2);
	LCD_u8SetSpecialChar(2, 14, 2);
	LCD_u8SetSpecialChar(3, 15, 2);
	LCD_u8SetString((u8*)"2-<\"  MAAM  \">", 0, 1);
	LCD_u8SetSpecialChar(4, 14, 1);
	LCD_u8SetSpecialChar(5, 15, 1);
	LCD_u8SetString((u8*)"1-<\"  MAAM  \">", 0, 0);
	LCD_u8SetSpecialChar(6, 14, 0);
	LCD_u8SetSpecialChar(7, 15, 0);
	vidMyDelay_ms(2000);
}

void vid_LcdShifting(void){
	for(u8 i = 16 ; i-- ; ){
		LCD_u8ShiftMode(LCD_Display_Shift_Right);
		vidMyDelay_ms(100);
	}
	for(u8 i = 16 ; i-- ; ){
		LCD_u8ShiftMode(LCD_Display_Shift_Left);
		vidMyDelay_ms(100);
	}
}

void vid_LcdCursor(void){
	LCD_u8GoTo_XY(0, 0);
	LCD_u8DisplayMode(LCD_Cursor_OFF_Blink);
	vidMyDelay_ms(1000);
	LCD_u8DisplayMode(LCD_Cursor_UnderLine_Blinking);
	vidMyDelay_ms(1000);
	LCD_u8DisplayMode(LCD_Cursor_UnderLine);
	vidMyDelay_ms(1000);
}

void vid_LcdDisplay(void){
	LCD_u8DisplayMode(LCD_Display_OFF);
	vidMyDelay_ms(1000);
	LCD_u8DisplayMode(LCD_Cursor_OFF);
	vidMyDelay_ms(1000);
	LCD_u8DisplayMode(LCD_Display_OFF);
	vidMyDelay_ms(1000);
	LCD_u8DisplayMode(LCD_Cursor_OFF);
	vidMyDelay_ms(1000);
}

void vid_LcdIntRise(void){
	s32 s32Num;

	LCD_u8SetString((u8*)"1- -585", 0, 0);

	s32Num = -590;
	LCD_u8SetNum(s32Num, 10, 0);
	s32Num = +1090;
	LCD_u8SetNum(s32Num, 10, 1);

	vidMyDelay_ms(1000);

	LCD_u8GetNum(&s32Num, 10, 0);
	LCD_u8SetNum(s32Num, 3, 0);
	vidMyDelay_ms(1000);

	LCD_u8GetNum(&s32Num, 10, 1);
	LCD_u8SetNum(s32Num, 3, 1);
	vidMyDelay_ms(1000);

	while(LCD_u8SetNum_Rise(111,  3, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
	while(LCD_u8SetNum_Rise(-999, 3, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
	while(LCD_u8SetNum_Rise(0,    3, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
}

void vid_LcdFloatRise(void){
	f32 f32Num;

	LCD_u8SetFloat(-999.9999f, 0, 0);
	LCD_u8SetFloat(0.0205f, 10, 0);
	vidMyDelay_ms(1000);

	LCD_u8GetFloat(&f32Num, 0, 0);
	LCD_u8SetFloat(f32Num, 0, 1);
	LCD_u8GetFloat(&f32Num, 10, 0);
	LCD_u8SetFloat(f32Num, 10, 1);
	vidMyDelay_ms(1000);

	while(LCD_u8SetFloat_Rise(0.0f,  0, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	while(LCD_u8SetFloat_Rise(0.0f, 10, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);

	while(LCD_u8SetFloat_Rise(0.051f,  0, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	while(LCD_u8SetFloat_Rise(0.051f, 10, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);

	while(LCD_u8SetFloat_Rise(-f32Num,  0, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	while(LCD_u8SetFloat_Rise(-f32Num, 10, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
	while(LCD_u8SetFloat_Rise(10.01f,  0, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	while(LCD_u8SetFloat_Rise(10.01f, 10, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
	while(LCD_u8SetFloat_Rise(-100.1f,  0, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	while(LCD_u8SetFloat_Rise(-100.1f, 10, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
	while(LCD_u8SetFloat_Rise(10000.001f,  0, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	while(LCD_u8SetFloat_Rise(10000.001f, 10, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
	while(LCD_u8SetFloat_Rise(1.0f, 0, 1))vidMyDelay_ms(LCD_DELAY_WAIT);
	vidMyDelay_ms(1000);
}

#endif

/*************************** E N D (main.c) ******************************/
