/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : GPIO_cfg.h													  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 23, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef SWC_GPIO_GPIO_CFG_H_
#define SWC_GPIO_GPIO_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

#if 	AMIT_KIT
typedef enum {
	AMIT_LCD0 = (u8)0u,
	AMIT_LCD1,
	AMIT_LCD2,
	AMIT_LCD3,
	AMIT_LCD4,
	AMIT_LCD5,
	AMIT_LCD6,
	AMIT_LCD7
}GPIO_tuenuAMIT_PORTA;

typedef enum {
	AMIT_B0 = (u8)0u,
	AMIT_LCD_RS,
	AMIT_LCD_RW,
	AMIT_LCD_EN,
	AMIT_B4,
	AMIT_B5,
	AMIT_B6,
	AMIT_B7
}GPIO_tuenuAMIT_PORTB;

typedef enum {
	AMIT_C0 = (u8)0u,
	AMIT_C1,
	AMIT_7Seg_COM0,
	AMIT_7Seg_COM1,
	AMIT_7Seg_A,
	AMIT_7Seg_B,
	AMIT_7Seg_C,
	AMIT_7Seg_D
}GPIO_tuenuAMIT_PORTC;

typedef enum {
	AMIT_PUSH0 = (u8)0u,
	AMIT_PUSH1,
	AMIT_PUSH2,
	AMIT_RELAY0,
	AMIT_RELAY1,
	AMIT_LED0,
	AMIT_LED1,
	AMIT_LED2,

	AMIT_BUZZER = (u8)4u
}GPIO_tuenuAMIT_PORTD;
#elif	ETA32_KIT
typedef enum {
	Eta32_LDR = (u8)0u,
	Eta32_LM35,
	Eta32_LCD_EN,
	Eta32_LCD_RS,
	Eta32_LED_G,
	Eta32_LED_B,
	Eta32_LED_Y,
	Eta32_RELAY1,

	Eta32_VR1 = (u8)0u,
	Eta32_VR2,
	Eta32_7Seg_COM2,
	Eta32_7Seg_COM3
}GPIO_tuenuEta32_PORTA;

typedef enum {
	Eta32_7Seg_A = (u8)0u,
	Eta32_7Seg_B,
	Eta32_7Seg_C,

	Eta32_7Seg_D = (u8)4,
	Eta32_7Seg_COM1,
	Eta32_7Seg_COM0,
	Eta32_LED_R,

	Eta32_LCD4 = (u8)0u,
	Eta32_LCD5,
	Eta32_LCD6,

	Eta32_LCD7 = (u8)4u,
	Eta32_ISP_MOSI,
	Eta32_ISP_MISO,
	Eta32_ISP_SCK,

	Eta32_DC_Motor_PWM = (u8)3u,

	Eta32_DC_Motor_DIR = (u8)5u,
	Eta32_DC_Motor_ENA = (u8)6u

}GPIO_tuenuEta32_PORTB;

typedef enum {
	Eta32_I2C_SCL = (u8)0u,
	Eta32_I2C_SDA,
	Eta32_JTAG_TCK,
	Eta32_JTAG_TMS,
	Eta32_JTAG_TDO,
	Eta32_JTAG_TDI,
	Eta32_BUZZER,
	Eta32_RELAY0,

	Eta32_Keypad_Row3 = (u8)2u,
	Eta32_Keypad_Row2,
	Eta32_Keypad_Row1,
	Eta32_Keypad_Row0
}GPIO_tuenuEta32_PORTC;

typedef enum {
	Eta32_UART_RX = (u8)0u,
	Eta32_UART_TX,
	Eta32_IR_Receiver,
	Eta32_Keypad_col3,
	Eta32_Analog_Out,
	Eta32_Keypad_col2,
	Eta32_Keypad_col1,
	Eta32_Keypad_col0
}GPIO_tuenuEta32_PORTD;
#else

#endif

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

#endif /* SWC_GPIO_GPIO_CFG_H_ */
/*************************** E N D (GPIO_cfg.h) ******************************/
