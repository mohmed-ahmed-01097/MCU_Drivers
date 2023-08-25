/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : task_IF_AMIT.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Aug 1, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#if defined(AMIT_KIT)

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

#include "ADC_int.h"
#include "ADCIF_int.h"
#include "ADCIF_cfg.h"

#include "EEPROM_int.h"

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

#define EEPROM_ADD				0x02
/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void _vidLedTask(void){
	for(u8 i = LED_Num ; i-- ; ){	LED_u8SetON(i);		}
	vidMyDelay_ms(DIO_DELAY_TOG);
	for(u8 i = LED_Num ; i-- ; ){	LED_u8SetOFF(i);	}
	vidMyDelay_ms(DIO_DELAY_TOG);
}

void _vidBuzzerTask(void){
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_High);
	vidMyDelay_ms(DIO_DELAY_TOG);
	GPIO_u8SetPinValue(PORT_BUZZER, PIN_BUZZER, PIN_Low);
	vidMyDelay_ms(DIO_DELAY_TOG);

}

void _vidRelayTask(void){
	GPIO_u8SetPinValue(PORT_RELAY0, PIN_RELAY0, PIN_High);
	GPIO_u8SetPinValue(PORT_RELAY1, PIN_RELAY1, PIN_High);
	vidMyDelay_ms(DIO_DELAY_TOG);
	GPIO_u8SetPinValue(PORT_RELAY0, PIN_RELAY0, PIN_Low);
	GPIO_u8SetPinValue(PORT_RELAY1, PIN_RELAY1, PIN_Low);
	vidMyDelay_ms(DIO_DELAY_TOG);
}

void _vidSegTask(void){
	WDT_vidInit();
	for(u8 i = 0 ; i<10 ; i++){
		LCD_u8ClrDisplay();
		WDT_vidReset();
		LCD_u8SetNum(i, 0, 0);
		for(u8 j = SEG_NUM_RATE ; --j ; ){
//			SEG_vidDisplayNum(i);
//			vidMyDelay_ms(SEG_DELAY);
			SEG_vidDisplayNum_Blink(i);
			vidMyDelay_ms(SEG_DELAY);
		}
	}
	while(1);
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

	for(u8 i = 0 ; i<SENSOR_NUM ; i++){
		LBTY_tenuErrorStatus u8RetErrorState = LCD_u8SetFloat(f32SensorsRead[i], (LCD_COL_NUM/2)*(i%2), i/2);
		if(u8RetErrorState == LBTY_OK)
			LCD_u8CHAR_W(katstrSensorConfig_GLB[i].m_Unit);
	}
	vidMyDelay_ms(DELAY_TOG);
}

void _vidEepromTask(void){
	u8 u8Num;
	while(EEPROM_u8ReadChar(EEPROM_ADD, &u8Num));
	LCD_u8ClrDisplay();
	LCD_u8SetChar('R', 0, 0);
	LCD_u8SetNum(u8Num, 2, 0);
	while(EEPROM_u8WriteChar(EEPROM_ADD, ++u8Num));
	LCD_u8SetChar('W', 0, 1);
	LCD_u8SetNum(u8Num, 2, 1);
	vidMyDelay_ms(DELAY_TOG);
}

#endif
/*************************** E N D (task_IF_AMIT.c) ******************************/
