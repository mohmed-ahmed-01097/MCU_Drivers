/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : task_IF_ETA32_MINI.c										  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Aug 1, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#if defined(ETA32_MINI_KIT)

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"
#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_int.h"
#include "LED_cfg.h"
#include "LED_priv.h"
#include "SEG_int.h"
#include "SEG_cfg.h"
#include "LCD_int.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

#include "WDT_cfg.h"
#include "WDT_int.h"

#include "IR_int.h"
#include "IR_priv.h"
#include "KPAD_int.h"
#include "KPAD_cfg.h"

#include "ADC_int.h"
#include "ADCIF_int.h"
#include "ADCIF_cfg.h"
#include "ANA_int.h"

#include "USART_int.h"
#include "I2C_int.h"
#include "EEI2C_int.h"
#include "EEI2C_cfg.h"

#include <stdio.h>
//#include <stdlib.h>

#include "task.h"
#include "task_IF.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
#define DIO_DELAY_TOG			400u
#define DELAY_TOG				500u
#define DELAY_WAIT				50u
/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void _vidDioTask(void){
	for(u8 i = LED_Num ; i-- ; ){	LED_u8SetON(i);		}
	GPIO_u8SetPinValue(PORT_RELAY0, PIN_RELAY0, PIN_High);
	GPIO_u8SetPinValue(PORT_RELAY1, PIN_RELAY1, PIN_High);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_High);
	vidMyDelay_ms(DIO_DELAY_TOG);
	for(u8 i = LED_Num ; i-- ; ){	LED_u8SetOFF(i);	}
	GPIO_u8SetPinValue(PORT_RELAY0, PIN_RELAY0, PIN_Low);
	GPIO_u8SetPinValue(PORT_RELAY1, PIN_RELAY1, PIN_Low);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_Low);
	vidMyDelay_ms(DIO_DELAY_TOG);
}

void _vidSegTask(void){
	WDT_vidInit();
	for(u8 i = 0 ; i<100 ; i++){
		WDT_vidReset();
		for(u8 j = SEG_NUM_RATE ; --j ; ){
			SEG_vidDisplayNum_Blink(i);
			vidMyDelay_ms(SEG_DELAY);
		}
		LCD_vidInit();
		LCD_u8SetNum(i, 0, 0);
	}
	LCD_u8SetString((u8*)"Reset", 0, 0);
	while(1){
		LCD_u8CHAR_W('.');
		vidMyDelay_ms(DELAY_WAIT);
	}
}

void _vidAdcTask(void){
	f32 f32SensorsRead[SENSOR_NUM];
	ADC_vidEnable();
	SENSOR_u8GetData(f32SensorsRead);

	LCD_u8ClrDisplay();

	for(u8 i = SENSOR_NUM ; i-- ; ){
		LBTY_tenuErrorStatus u8RetErrorState = LCD_u8SetFloat(f32SensorsRead[i], (LCD_COL_NUM/2)*(i%2), i/2);
		if(u8RetErrorState == LBTY_OK)
			LCD_u8CHAR_W(katstrSensorConfig_GLB[i].m_Unit);
	}
	vidMyDelay_ms(DELAY_TOG);
}

void _vidComTask(void){
	u8 u8Output;
	ANA_vidGetOutput(&u8Output);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, u8Output);
	vidMyDelay_ms(DELAY_WAIT);
}

void _vidUartTask(void){
	u8 u8Char, u8index = LBTY_u8ZERO;
	if(USART_u8Available()){
//		USART_vidGetStr(str);
//		USART_vidSetStr(str);
//		u8Char = *str;
//		USART_u8GetTransmit((void*)&u8Char);
//		USART_u8SetTransmit((void*)&u8Char);
		USART_vidGetChar(&u8Char);
		USART_vidSetChar(u8Char);
		LCD_u8SetChar(u8Char, u8index++, 0);
	}
}

void _vidIRTask(void){
	u8 u8CMD;
	IR_tstrPacket strIRPacket;
	IR_tstrFram strIRFram;
	IR_GetCmd(&u8CMD);
	LCD_u8SetNum(u8CMD, 12, 1);

	IR_GetPacket(&strIRPacket);
	vid_IrReadFram(&strIRFram);

	LCD_u8SetNum(strIRPacket.m_u8Rec_Address,     0, 0);
	LCD_u8SetNum(strIRPacket.m_u8Rec_AddressInv,  4, 0);
	LCD_u8SetNum(strIRPacket.m_u8Command,         8, 0);
	LCD_u8SetNum(strIRPacket.m_u8CommandInv,     12, 0);

	LCD_u8SetNum(strIRFram.m_u8ReadBit,      1, 1);
	LCD_u8SetNum(strIRFram.m_u8ReadByte,     4, 1);
	LCD_u8SetNum(strIRFram.m_u8Repeat,       7, 1);
	LCD_u8SetNum(strIRFram.m_u8RepeatCount, 10, 1);

	LCD_u8SetChar('b', 0, 1);
	LCD_u8SetChar('B', 3, 1);
	LCD_u8SetChar('R', 6, 1);
	LCD_u8SetChar('C', 9, 1);
}

void _vidEEI2CTask(void){
	u8 u8char;
//	I2C_vidEnable();
//	I2C_vidDisableINT();
	EEI2C_u8GetChar(&u8char, EE_SLAVE_ADDRESS);
	LCD_u8SetNum(u8char, 0, 0);
	EEI2C_u8SetChar(++u8char, EE_SLAVE_ADDRESS);
//	I2C_vidDisable();

	vidMyDelay_ms(DELAY_TOG);
}

void _vidTmrTask(void){

}

void _vidPwmTask(void){

}

void _vidMotorTask(void){

}

#endif
/*************************** E N D (task_IF_ETA32_MINI.c) ******************************/
