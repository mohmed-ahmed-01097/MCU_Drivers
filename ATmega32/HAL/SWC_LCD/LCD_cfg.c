/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LCD_cfg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 31, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LCD_int.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

const u8 ETA32[][LCD_CGRAM_LOCATIONS_NUM] = {
	{ 0x1C, 0x1C, 0x0F, 0x0F, 0x0C, 0x0C, 0x00, 0x00},
	{ 0x1C, 0x1C, 0x03, 0x03, 0x03, 0x03, 0x06, 0x06},
	{ 0x06, 0x0C, 0x0C, 0x0C, 0x18, 0x18, 0x1A, 0x0C}
};
//https://maxpromer.github.io/LCD-Character-Creator/

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

LBTY_tenuErrorStatus LCD_u8FunctionSet(void){
	LBTY_tenuErrorStatus u8RetErrorState =  LCD_u8CMD_W(LCD_CURSOR_HOME);

	if(u8RetErrorState == LBTY_OK){
#ifdef LCD_10DOT
#if (LCD_ROW_NUM > LCD_ROW_NUM_1)
#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_2LINE_8BIT_10ROW);
#elif  (LCD_FUNCTION_SET == LCD_FUNCTION_SET_4Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_2LINE_4BIT_10ROW);
#endif
#else
#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_1LINE_8BIT_10ROW);
#elif  (LCD_FUNCTION_SET == LCD_FUNCTION_SET_4Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_1LINE_4BIT_10ROW);
#endif
#endif

#else

#if (LCD_ROW_NUM > LCD_ROW_NUM_1)
#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_2LINE_8BIT_5ROW);
#elif  (LCD_FUNCTION_SET == LCD_FUNCTION_SET_4Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_2LINE_4BIT_5ROW);
#endif
#else
#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_1LINE_8BIT_5ROW);
#elif  (LCD_FUNCTION_SET == LCD_FUNCTION_SET_4Bits)
		u8RetErrorState = LCD_u8CMD_W(LCD_CONFIG_1LINE_4BIT_5ROW);
#endif
#endif

#endif
	}
	return u8RetErrorState;
}

void LCD_vidInitPins(void){
	vidMyDelay_ms(LCD_DELAY_POWER_ON);		// Delay Power On

	GPIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_EN, PIN_OUTPUT);
	GPIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_RS, PIN_OUTPUT);
#ifdef LCD_RW
	GPIO_u8SetPinDirection(LCD_CONTROL_PORT, LCD_RW, PIN_OUTPUT);
#endif

	LCD_vidDirection(PIN_OUTPUT);
}

void LCD_vidDirection(u8 u8PinDir){
#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D0, u8PinDir);
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D1, u8PinDir);
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D2, u8PinDir);
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D3, u8PinDir);
#endif
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D4, u8PinDir);
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D5, u8PinDir);
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D6, u8PinDir);
	GPIO_u8SetPinDirection(LCD_DATA_PORT, LCD_D7, u8PinDir);
}

void LCD_vidTriger(void){
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_High);
	vidMyDelay_ms(LCD_DELAY_CMD);
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_Low);
	vidMyDelay_ms(LCD_DELAY_CMD);
}

LBTY_tenuErrorStatus LCD_u8Write(u8 u8Byte){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	LBTY_tuniPort8 u8LcdByte = (LBTY_tuniPort8)u8Byte;

#ifdef LCD_RW
	u8RetErrorState = GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW, LCD_RW_WRITE);
#endif

	LCD_vidDirection(PIN_OUTPUT);

#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_4Bits)
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D4, u8LcdByte.sBits.m_u8b4);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D5, u8LcdByte.sBits.m_u8b5);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D6, u8LcdByte.sBits.m_u8b6);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D7, u8LcdByte.sBits.m_u8b7);
	LCD_vidTriger();
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D4, u8LcdByte.sBits.m_u8b0);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D5, u8LcdByte.sBits.m_u8b1);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D6, u8LcdByte.sBits.m_u8b2);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D7, u8LcdByte.sBits.m_u8b3);
	LCD_vidTriger();
#elif (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D0, u8LcdByte.sBits.m_u8b0);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D1, u8LcdByte.sBits.m_u8b1);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D2, u8LcdByte.sBits.m_u8b2);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D3, u8LcdByte.sBits.m_u8b3);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D4, u8LcdByte.sBits.m_u8b4);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D5, u8LcdByte.sBits.m_u8b5);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D6, u8LcdByte.sBits.m_u8b6);
	GPIO_u8SetPinValue(LCD_DATA_PORT, LCD_D7, u8LcdByte.sBits.m_u8b7);
	LCD_vidTriger();
#endif
	return u8RetErrorState;
}

LBTY_tenuErrorStatus LCD_u8Read(u8* pu8Byte){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_NOK;

#ifdef LCD_RW
	LBTY_tuniPort8* pu8LcdByte = (LBTY_tuniPort8*)pu8Byte;
	u8 u8ReadValue;

	u8RetErrorState = GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RW, LCD_RW_READ);

	LCD_vidDirection(PIN_INPUT);

#if (LCD_FUNCTION_SET == LCD_FUNCTION_SET_4Bits)
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_High);
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D4, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b4 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D5, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b5 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D6, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b6 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D7, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b7 = u8ReadValue;
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_Low);
	vidMyDelay_ms(LCD_DELAY_CMD);
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_High);
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D4, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b0 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D5, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b1 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D6, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b2 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D7, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b3 = u8ReadValue;
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_Low);
#elif (LCD_FUNCTION_SET == LCD_FUNCTION_SET_8Bits)
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_High);
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D0, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b0 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D1, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b1 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D2, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b2 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D3, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b3 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D4, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b4 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D5, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b5 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D6, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b6 = u8ReadValue;
	GPIO_u8GetPinValue(LCD_DATA_PORT, LCD_D7, &u8ReadValue);
	pu8LcdByte->sBits.m_u8b7 = u8ReadValue;
	GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_EN, PIN_Low);
#endif

#endif
	return u8RetErrorState;
}

LBTY_tenuErrorStatus LCD_u8CMD_W(u8 u8CMD){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
#ifdef LCD_RW
	while(LCD_u8GetBusyFlag())		vidMyDelay_ms(LCD_DELAY_CMD);
#else
	vidMyDelay_ms(LCD_DELAY_CMD);
#endif
	u8RetErrorState = GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS, LCD_RS_CMD);
	u8RetErrorState = LCD_u8Write(u8CMD);

	return u8RetErrorState;
}

LBTY_tenuErrorStatus LCD_u8CMD_R(u8* pu8CMD){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	u8RetErrorState = GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS, LCD_RS_CMD);
	u8RetErrorState = LCD_u8Read(pu8CMD);

	return u8RetErrorState;
}

LBTY_tenuErrorStatus LCD_u8CHAR_W(u8 u8Char){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

#ifdef LCD_RW
	while(LCD_u8GetBusyFlag())		vidMyDelay_ms(LCD_DELAY_CMD);
#else
	vidMyDelay_ms(LCD_DELAY_CMD);
#endif
	u8RetErrorState = GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS, LCD_RS_DATA);
	u8RetErrorState = LCD_u8Write(u8Char);

	return u8RetErrorState;
}

LBTY_tenuErrorStatus LCD_u8CHAR_R(u8* pu8Char){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	u8RetErrorState = GPIO_u8SetPinValue(LCD_CONTROL_PORT, LCD_RS, LCD_RS_DATA);
	u8RetErrorState = LCD_u8Read(pu8Char);

	return u8RetErrorState;
}

LBTY_tenuErrorStatus LCD_u8Set_CGRAM_Address(u8 u8Address){
	return LCD_u8CMD_W(LCD_SEND_CGRAM_ADDRESS | GET_MASK(u8Address, LCD_CGRAM_ADDRESS_MASK));
}

LBTY_tenuErrorStatus LCD_u8Set_DDRAM_Address(u8 u8Address){
	return LCD_u8CMD_W(LCD_SEND_DDRAM_ADDRESS | GET_MASK(u8Address, LCD_DDRAM_ADDRESS_MASK));
}

LBTY_tenuErrorStatus LCD_u8Get_DDRAM_Address(u8* pu8Address){
	LBTY_tenuErrorStatus u8RetErrorState = LCD_u8CMD_R(pu8Address);
	*pu8Address = GET_MASK(*pu8Address, LCD_DDRAM_ADDRESS_MASK);
	return u8RetErrorState;
}

u8 LCD_u8GetBusyFlag(void){
	u8 u8RetValue = LBTY_RESET;
	LCD_u8CMD_R(&u8RetValue);
	return GET_BIT(u8RetValue, BUSY_FLAG_BIT);
}


/*************************** E N D (LCD_cfg.c) ******************************/
