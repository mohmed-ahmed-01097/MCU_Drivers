/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : task.c														  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Aug 1, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LCTY_int.h"

#include "DELAY.h"
#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "LED_int.h"
#include "LED_cfg.h"
#include "SEG_int.h"
#include "LCD_int.h"
#include "LCD_cfg.h"

#include "ADC_int.h"
#include "ADCIF_int.h"

#if defined(AMIT_KIT)
#include "PUSH_int.h"
#include "PUSH_cfg.h"
#include "INT_int.h"
#include "INT_cfg.h"

#include "EEPROM_int.h"
#elif (defined(ETA32_KIT) || defined(ETA32_MINI_KIT))
#include "IR_int.h"
#include "KPAD_int.h"
#include "KPAD_cfg.h"

#include "ANA_int.h"

#include "USART_int.h"
#include "SPI_int.h"
#include "I2C_int.h"
#endif

#include <stdio.h>

#include "task.h"
#include "task_IF.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */
extern const u8 ETA32[][8];
/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */
u8 str[LCD_COL_NUM];

#if defined(AMIT_KIT)
static u8 u8PUSH_INT_LAST = LBTY_u8MAX;
static u8 u8PUSH_INT_COUNT;
volatile u8 u8PUSH_INT_Flag;
void Push_ISR(void){
	if(! u8PUSH_INT_Flag){
		u8PUSH_INT_COUNT = (u8PUSH_INT_COUNT + 1) % 3;
	}else{
		u8PUSH_INT_LAST = LBTY_u8MAX;
	}
	u8PUSH_INT_Flag = LBTY_RESET;
}
#elif defined(ETA32_KIT)
LCTY_INLINE void LCD_Bar(u8 u8Row){
	LCD_u8SetString((u8*)"====================", 0, u8Row);
}
#elif defined(ETA32_MINI_KIT)
#endif

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void Kit_vidInit(void){

	GPIO_u8SetPinDirection(PORT_BUZZER, PIN_BUZZER, PIN_OUTPUT);
	GPIO_u8SetPinValue    (PORT_BUZZER, PIN_BUZZER, PIN_Low);
	GPIO_u8SetPinDirection(PORT_RELAY0, PIN_RELAY0, PIN_OUTPUT);
	GPIO_u8SetPinValue    (PORT_RELAY0, PIN_RELAY0, PIN_Low);
	GPIO_u8SetPinDirection(PORT_RELAY1, PIN_RELAY1, PIN_OUTPUT);
	GPIO_u8SetPinValue    (PORT_RELAY1, PIN_RELAY1, PIN_Low);

	LED_vidInitAll();
	SEG_vidInit();
	LCD_vidInit();
	SENSOR_vidInit();

#if defined(AMIT_KIT)
	PUSH_vidInitAll();
    INT_vidInit(INT_PUSH);
    INT_vidSetCallBack(INT_PUSH, Push_ISR);

	EEPROM_vidInit();
#elif (defined(ETA32_KIT) || defined(ETA32_MINI_KIT))
	KPAD_vidInit();

	IR_vidInit();

    ANA_vidInit();

	UART_vidInit();
//	USART_vidSetCallBack_RX(RX_MSG);
//	USART_vidEnableReceiveCompleteINT();

//	SPI_vidInit();
//	SPI_vidSetCallBack_OverFlow(SPI_vidINT);

//	I2C_vidInit();
//	I2C_vidSetCallBack_OverFlow(I2C_vidINT);
#endif

	INTP_vidEnable();
}

void Kit_vidWlcome(void){

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

void Kit_vidLcdUpdate(void){

#if defined(AMIT_KIT)

	if(u8PUSH_INT_COUNT != u8PUSH_INT_LAST){
		u8PUSH_INT_LAST = u8PUSH_INT_COUNT;
		LCD_u8ClrDisplay();
		switch(u8PUSH_INT_COUNT){
			case 2:		LCD_u8SetString((u8*)"0:ADC   1:EEPROM", 0, 0);		break;
			case 1:		LCD_u8SetString((u8*)"0:Relay 1:7Segs" , 0, 0);		break;
			case 0:
			default:	LCD_u8SetString((u8*)"0:Buzzer 1:LEDs" , 0, 0);		break;
		}
		LCD_u8SetString((u8*)"2:Next Page", 0, 1);
	}
	Kit_vidTask(u8PUSH_INT_LAST);

#elif defined(ETA32_KIT)

	u8 u8Index = KPAD_u8GetKeyNum();
	if(u8Index != LBTY_u8MAX){
		LCD_u8ClrDisplay();
		LCD_Bar(0);
		LCD_Bar(3);
		sprintf ((char*)str, "SW (%1u) pressed", (u8Index+1));
		switch(u8Index){
			case  0:
			case  1:
			case  2:
			case  3:
			case  4:
			case  5:
				LCD_u8SetString((u8*)str, 3, 2);
				break;
			default:
				break;
		}
		USART_vidSetStrLine((u8*)str);
		Kit_vidTask(u8Index);
	}

#elif defined(ETA32_MINI_KIT)

	u8 u8Index = KPAD_u8GetKeyNum();
	if(u8Index != LBTY_u8MAX){
		LCD_u8ClrDisplay();
		sprintf ((char*)str, "SW %02u is pressed", ((u8Index+1)%100u));
		LCD_u8SetString((u8*)"Eta32mini Kit",    1, 0);
		LCD_u8SetString((u8*)str, 0, 1);
		USART_vidSetStrLine((u8*)str);
		Kit_vidTask(u8Index);
	}

#endif

}

void Kit_vidTask(u8 u8func){
#if defined(AMIT_KIT)

	u8 u8State ;
	PUSH_u8GetPushState(PUSH0, &u8State);
	if(u8State){
		LCD_u8ClrDisplay();
		u8PUSH_INT_Flag = LBTY_SET;
		switch(u8func){
			case 2:		Task((u8*)"       ADC      ", _vidAdcTask);		break;
			case 1:		Task((u8*)"     RELAYs     ", _vidRelayTask);	break;
			case 0:
			default:	Task((u8*)"     BUZZERs    ", _vidBuzzerTask);	break;
		}
	}
	PUSH_u8GetPushState(PUSH1, &u8State);
	if(u8State){
		LCD_u8ClrDisplay();
		u8PUSH_INT_Flag = LBTY_SET;
		switch(u8func){
			case 2:		Task((u8*)"     EEPROM     ", _vidEepromTask);	break;
			case 1:		Task((u8*)"      7Segs     ", _vidSegTask);		break;
			case 0:
			default:	Task((u8*)"      LEDs      ", _vidLedTask);		break;
		}
	}

#elif defined(ETA32_KIT)
	while(KPAD_u8GetKeyNum() != LBTY_u8MAX);
	switch(u8func){
		case  0: LCD_u8SetString((u8*)"Yellow LED Test", 3, 1);	LED_u8Toggle(LED3);	break;
		case  1: LCD_u8SetString((u8*)"Blue LED Test", 3, 1);	LED_u8Toggle(LED2);	break;
		case  2: LCD_u8SetString((u8*)"Green LED Test", 3, 1);	LED_u8Toggle(LED1);	break;
		case  3: LCD_u8SetString((u8*)"Red LED Test", 3, 1);	LED_u8Toggle(LED0);	break;
		case  4: LCD_u8SetString((u8*)"Relay1 Test", 3, 1);	GPIO_u8TogglePinValue(PORT_RELAY0, PIN_RELAY0);	break;
		case  5: LCD_u8SetString((u8*)"Relay2 Test", 3, 1);	GPIO_u8TogglePinValue(PORT_RELAY1, PIN_RELAY1);	break;
		case  6: Task((u8*)" 7 Segment display  ", _vidSegTask);		break;
		case  7: Task((u8*)"   24C08 Testing    ", _vidEEI2CTask);		break;
		case  8: Task((u8*)"  Time 00:00:00 AM  ", _vidRtcTask);		break;
		case  9: Task((u8*)"  Serial Receiving  ", _vidUartTask);		break;
		case 10: Task((u8*)"  VR1 &VR2 Testing  ", _vidVarTask);		break;
		case 11: Task((u8*)" LDR & LM35 Testing ", _vidTempTask);		break;
		case 12: Task((u8*)"  DC Motor Testing  ", _vidMotorTask);		break;
		case 13: Task((u8*)" Analog Out Testing ", _vidPwmTask);		break;
		case 14: Task((u8*)"     IR Testing     ", _vidIRTask);			break;
		case 15: Task((u8*)"  Outputs testing   ", _vidDioTask);		break;
		default:	break;
	}
#elif defined(ETA32_MINI_KIT)
	while(KPAD_u8GetKeyNum() != LBTY_u8MAX);
	switch(u8func){
		case  0: GPIO_u8TogglePinValue(PORT_RELAY0, PIN_RELAY0);	break;
		case  1: GPIO_u8TogglePinValue(PORT_RELAY1, PIN_RELAY1);	break;
		case  2: LED_u8Toggle(LED2);	break;
		case  3: LED_u8Toggle(LED1);	break;
		case  4: LED_u8Toggle(LED0);	break;
		case  5: Task((u8*)"   7Seg Test    ", _vidSegTask);		break;
		case  6: Task((u8*)"    ADC Test    ", _vidAdcTask);		break;
		case  7: Task((u8*)"   USART Test   ", _vidUartTask);		break;
		case  8: Task((u8*)"IR Receiver Test", _vidIRTask);			break;
		case  9: Task((u8*)"EEPROM  I2C Test", _vidEEI2CTask);		break;
		case 10: Task((u8*)"  Counter Test  ", _vidTmrTask);		break;
		case 11: Task((u8*)"Analog Out. Test", _vidPwmTask);		break;
		case 12: Task((u8*)"Comparator  Test", _vidComTask);		break;
		case 13: Task((u8*)"  DC Motor Test ", _vidMotorTask);		break;
		case 14: GPIO_u8TogglePinValue(PORT_BUZZER, PIN_BUZZER);	break;
		case 15: Task((u8*)"  Outputs Test  ", _vidDioTask);		break;
		default:	break;
	}
#endif
}
/*************************** E N D (task.c) ******************************/
