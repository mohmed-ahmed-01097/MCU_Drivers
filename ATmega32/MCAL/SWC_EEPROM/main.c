/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : main.c														  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 30, 2023												  */
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

#ifdef	SWC_EEPROM

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"
#include "INTP.h"

#include "INT_int.h"
#include "INT_cfg.h"

#include "LCD_int.h"
#include "LCD_cfg.h"

#include "EEPROM_int.h"
#include "EEPROM_cfg.h"

volatile u8 u8INT_Flag = LBTY_RESET, u8EEPROM_Flag = LBTY_SET;
u8 u8Num = LBTY_u8ZERO;

void Push_ISR(void);
void EEPROM_ISR(void);

int main(void){

	LCD_vidInit();
	LCD_u8ClrDisplay();
	LCD_u8Home();

	LCD_u8SetNum(u8Num, 0, 0);
	vidMyDelay_ms(1000);

    INT_vidInit(INT_AMIT_PUSH2);
    INT_vidSetCallBack(INT_AMIT_PUSH2, Push_ISR);

    INTP_vidEnable();

	EEPROM_vidInit();
//	EEPROM_vidSetCallBack(EEPROM_ISR);

	EEPROM_u8Erase(0,100);
	EEPROM_u8ReadChar(u8Num, &u8Num);
	u8EEPROM_Flag = LBTY_SET;

	LCD_u8SetNum(u8Num, 0, 0);
	vidMyDelay_ms(1000);

   	while(1){
   		if(u8INT_Flag){
   			u8INT_Flag = LBTY_RESET;
   			while(EEPROM_u8WriteChar(u8Num, u8Num));
   			vidMyDelay_ms(10);
   			u8Num = LBTY_u8ZERO;
   			while(EEPROM_u8ReadChar(u8Num, &u8Num));
   			LCD_u8ClrDisplay();
   			LCD_u8Home();
   			vidMyDelay_ms(1000);
   			LCD_u8SetNum(u8Num, 0, 0);
   		}
    }

   	return 0;
}

void Push_ISR(void){
	u8INT_Flag = LBTY_SET;
	u8Num++;
}

void EEPROM_ISR(void){
	u8EEPROM_Flag = LBTY_RESET;
}

#endif

/*************************** E N D (main.c) ******************************/
