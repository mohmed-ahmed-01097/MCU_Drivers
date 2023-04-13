/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LED_cfg.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LED_CFG_H_
#define LED_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef struct{
	u8 u8PortNum;
	u8 u8PinNum;
	u8 u8Connection;
}LED_tstrConfiguration;

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if 	AMIT_KIT

#define LED0			0
#define LED0_PORT		D
#define LED0_PIN		AMIT_LED0

#define LED1			1
#define LED1_PORT		D
#define LED1_PIN		AMIT_LED1

#define LED2			2
#define LED2_PORT		D
#define LED2_PIN		AMIT_LED2

#elif	ETA32_KIT

#define LED0			0
#define LED0_PORT		B
#define LED0_PIN		Eta32_LED_R

#define LED1			1
#define LED1_PORT		A
#define LED1_PIN		Eta32_LED_G

#define LED2			2
#define LED2_PORT		A
#define LED2_PIN		Eta32_LED_B

#define LED3			3
#define LED3_PORT		A
#define LED3_PIN		Eta32_LED_Y

#else

#define LED0			0
#define LED0_PORT		B
#define LED0_PIN		0

#define LED1			1
#define LED1_PORT		B
#define LED1_PIN		1

#define LED2			2
#define LED2_PORT		B
#define LED2_PIN		2

#define LED3			3
#define LED3_PORT		B
#define LED3_PIN		0

#define LED4			4
#define LED4_PORT		B
#define LED4_PIN		4

#define LED5			5
#define LED5_PORT		B
#define LED5_PIN		5

#define LED6			6
#define LED6_PORT		B
#define LED6_PIN		6

#define LED7			7
#define LED7_PORT		B
#define LED7_PIN		7

#endif

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* LED_CFG_H_ */
/*************************** E N D (LED_cfg.h) ******************************/
