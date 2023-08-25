/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : task_IF.c													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Aug 1, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "LCD_int.h"
#include "LCD_cfg.h"

#if defined(AMIT_KIT)

#elif (defined(ETA32_KIT) || defined(ETA32_MINI_KIT))
#include "KPAD_int.h"
#include "KPAD_cfg.h"
#endif

#include "task.h"

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

#if defined(AMIT_KIT)
extern volatile u8 u8PUSH_INT_Flag;
#elif defined(ETA32_KIT)
#elif defined(ETA32_MINI_KIT)
#endif
/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */
void _vidLcdTask(u8* puStr){
#if defined(AMIT_KIT)
	LCD_u8SetString((u8*)"Testing", 5, 0);
	LCD_u8SetString(puStr, 0, 1);
#elif defined(ETA32_KIT) || defined(ETA32_MINI_KIT)
	LCD_u8SetString(puStr, 0, 0);
	vidMyDelay_ms(LCD_DELAY_PAGE);
	for(u8 i = LCD_COL_NUM ; i-- ; ){
		LCD_u8ShiftMode(LCD_Display_Shift_Right);
		vidMyDelay_ms(LCD_DELAY_WAIT);
	}
	LCD_u8ClrDisplay();
#endif
}

void Task(u8* puStr, void(*task)(void)){
#if defined(AMIT_KIT)
	_vidLcdTask(puStr);
	do{
		task();
	}while(u8PUSH_INT_Flag);
#elif defined(ETA32_KIT) || defined(ETA32_MINI_KIT)
	while(KPAD_u8GetKeyNum() != LBTY_u8MAX);
	_vidLcdTask(puStr);
	do{
		task();
	}while(KPAD_u8GetKeyNum() == LBTY_u8MAX);
#endif
}

/*************************** E N D (task_IF.c) ******************************/
