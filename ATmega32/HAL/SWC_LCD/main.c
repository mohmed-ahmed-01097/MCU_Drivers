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

#ifdef	SWC_LCD

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LCD_int.h"
#include "LCD_cfg.h"

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
#define LCD_CGRAM_SECTIONS_NUM 			8u
#define LCD_CGRAM_LOCATIONS_NUM  		8u

const u8 LCD_SpecialChar_Array[][LCD_CGRAM_LOCATIONS_NUM] = {
		{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F},	// Bold
		{0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A},	// Chess
		{0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00},	// UnFilledHeart
		{0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00},	// FilledHeart
		{0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00},	// Bell
		{0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04},	// Plug
		{0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00},	// Face
		{0x04, 0x0E, 0x04, 0x0E, 0x15, 0x0E, 0x11, 0x00},	// Human
		{0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01},	// Silent
		{0x01, 0x03, 0x05, 0x09, 0x09, 0x0B, 0x1B, 0x18},	// Music
};
/* ************************************************************************** */


void LCD_vidInitKit(void);
void LCD_vidInitSpecial(void);
void vid_LcdWelcome(void);
void vid_LcdShifting(void);
void vid_LcdCursor(void);
void vid_LcdDisplay(void);

void vid_LcdIntRise(void);
void vid_LcdFloatRise(void);

int main(void){

	LCD_vidInit();

	while(1){
		LCD_vidInitKit();
		LCD_vidInitSpecial();

		vid_LcdCursor();
		vid_LcdWelcome();
		vid_LcdShifting();
		vid_LcdDisplay();

		LCD_u8ClrDisplay();
		vid_LcdIntRise();
		vid_LcdFloatRise();

	}

	return 0;
}

void LCD_vidInitKit(void){

#if defined(AMIT_KIT)

	LCD_u8SetString((u8*)"Welcome To", 3, 0);
	LCD_u8SetString((u8*)"AMIT"      , 6, 1);
	vidMyDelay_ms(LCD_DELAY_PAGE);
	LCD_u8ClrDisplay();
	LCD_u8SetString((u8*)"Choose a"  , 4, 0);
	LCD_u8SetString((u8*)"Peripheral", 3, 1);
	vidMyDelay_ms(LCD_DELAY_PAGE);
	LCD_u8ClrDisplay();

#elif defined(ETA32_KIT)

	USART_vidSetStrLine((u8*)" FARES PCB Co.  ");
	USART_vidSetStrLine((u8*)"ATMEL AVR Development kit.");
	USART_vidSetStrLine((u8*)"Eta32 kit.");
	USART_vidSetStrLine((u8*)"Arduino IDE compatible.");
	LCD_u8ClrDisplay();

	for(u8 i = 0 ; i<3u ; i++){
		LCD_u8StoreSpecialChar((u8*)ETA32[i], i);
	}

	LCD_u8SetPage((u8*)"====================Educational Products"
				, (u8*)"FARES PCB Co. for   ====================");

	LCD_u8SetPage((u8*)"====================       @32 Kit      "
				, (u8*)"      @@            ====================");

	LCD_u8SetPage((u8*)"====================   Eta32 Test Code  "
				, (u8*)"    ATMEL AVR Kit   ====================");

#elif defined(ETA32_MINI_KIT)

	USART_vidSetStrLine((u8*)" FARES PCB Co.  ");
	USART_vidSetStrLine((u8*)"ATMEL AVR Development kit.");
	USART_vidSetStrLine((u8*)"Eta32mini kit.");
	USART_vidSetStrLine((u8*)"Arduino IDE compatible.");
	LCD_u8ClrDisplay();

	for(u8 i = 0 ; i<3u ; i++){
		LCD_u8StoreSpecialChar((u8*)ETA32[i], i);
	}

	LCD_u8SetPage((u8*)" FARES PCB Co.  "
				, (u8*)"================");

	LCD_u8SetPage((u8*)"    @@          "
				, (u8*)"     @32 mini   ");

	LCD_u8SetPage((u8*)" ATMEL AVR Kit  "
				, (u8*)" Eta32 mini Kit ");

	LCD_u8ClrDisplay();
	LCD_u8SetString((u8*)"Eta32mini Kit",    1, 0);
	LCD_u8SetString((u8*)"SW -- is pressed", 0, 1);

#else

	LCD_u8SetPage((u8*)"=====Welcome===="
				 ,(u8*)"=+ LCD Driver +=");
	vidMyDelay_ms(LCD_DELAY_PAGE);
	LCD_u8ClrDisplay();

#endif

}

void LCD_vidInitSpecial(void){
	LCD_u8ClrDisplay();
	for(u8 i = 0 ; i<LCD_CGRAM_LOCATIONS_NUM ; i++){
		LCD_u8SetNum(i, i, 1);
		LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i], i, 0);
		vidMyDelay_ms(500);
	}
	LCD_u8ClrDisplay();
}

void vid_LcdWelcome(void){
	u8 i = 2;
	LCD_u8GoTo_XY(0, 3);
	LCD_u8DisplayMode(LCD_Cursor_UnderLine);
	vidMyDelay_ms(1000);
	LCD_u8SetString((u8*)"4 - <\" MAAM \">",  0, 3);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 14, 3);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 15, 3);

	LCD_u8GoTo_XY(0, 2);
	LCD_u8DisplayMode(LCD_Cursor_UnderLine_Blinking);
	vidMyDelay_ms(1000);
	LCD_u8SetString((u8*)"3 - <\" MAAM \">",  0, 2);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 14, 2);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 15, 2);

	LCD_u8GoTo_XY(0, 1);
	LCD_u8DisplayMode(LCD_Cursor_OFF_Blink);
	vidMyDelay_ms(1000);
	LCD_u8SetString((u8*)"2 - <\" MAAM \">",  0, 1);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 14, 1);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 15, 1);

	LCD_u8GoTo_XY(0, 0);
	LCD_u8DisplayMode(LCD_Cursor_OFF);
	vidMyDelay_ms(1000);
	LCD_u8SetString((u8*)"1 - <\" MAAM \">", 0, 0);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 14, 0);
	LCD_u8SetSpecialCharArray((u8*)LCD_SpecialChar_Array[i++], 15, 0);
	vidMyDelay_ms(2000);
}

void vid_LcdShifting(void){
	for(u8 i = LCD_COL_NUM ; i-- ; ){
		LCD_u8ShiftMode(LCD_Display_Shift_Right);
		vidMyDelay_ms(100);
	}
	for(u8 i = LCD_COL_NUM ; i-- ; ){
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

	if(! LCD_u8GetNum(&s32Num, 10, 0)){
		LCD_u8SetNum(s32Num, 3, 0);
		vidMyDelay_ms(1000);
	}

	if(! LCD_u8GetNum(&s32Num, 10, 1)){
		LCD_u8SetNum(s32Num, 3, 1);
		vidMyDelay_ms(1000);
	}

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

	if(! LCD_u8GetFloat(&f32Num, 0, 0)){
		LCD_u8SetFloat(f32Num, 0, 1);
		vidMyDelay_ms(1000);
	}

	if(! LCD_u8GetFloat(&f32Num, 10, 0)){
		LCD_u8SetFloat(f32Num, 10, 1);
		vidMyDelay_ms(1000);
	}

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
