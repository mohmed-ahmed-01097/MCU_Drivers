/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LED_cfg.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 8, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LED_CFG_H_
#define LED_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if defined(AMIT_KIT)

#define LED0			0
#define LED0_PORT		D
#define LED0_PIN		AMIT_LED0
#define LED0_CON		LED_Forward

#define LED1			1
#define LED1_PORT		D
#define LED1_PIN		AMIT_LED1
#define LED1_CON		LED_Forward

#define LED2			2
#define LED2_PORT		D
#define LED2_PIN		AMIT_LED2
#define LED2_CON		LED_Forward

#elif defined(ETA32_KIT)

#define LED0			0
#define LED0_PORT		B
#define LED0_PIN		Eta32_LED_R
#define LED0_CON		LED_Forward

#define LED1			1
#define LED1_PORT		A
#define LED1_PIN		Eta32_LED_G
#define LED1_CON		LED_Forward

#define LED2			2
#define LED2_PORT		A
#define LED2_PIN		Eta32_LED_B
#define LED2_CON		LED_Forward

#define LED3			3
#define LED3_PORT		A
#define LED3_PIN		Eta32_LED_Y
#define LED3_CON		LED_Forward

#elif defined(ETA32_MINI_KIT)

#define LED0			0
#define LED0_PORT		C
#define LED0_PIN		Eta32_mini_LED_R
#define LED0_CON		LED_Forward

#define LED1			1
#define LED1_PORT		C
#define LED1_PIN		Eta32_mini_LED_G
#define LED1_CON		LED_Forward

#define LED2			2
#define LED2_PORT		C
#define LED2_PIN		Eta32_mini_LED_B
#define LED2_CON		LED_Forward

#else

#define LED0			0
#define LED0_PORT		B
#define LED0_PIN		0
#define LED0_CON		LED_Forward

#define LED1			1
#define LED1_PORT		B
#define LED1_PIN		1
#define LED1_CON		LED_Forward

#define LED2			2
#define LED2_PORT		B
#define LED2_PIN		2
#define LED2_CON		LED_Forward

#define LED3			3
#define LED3_PORT		B
#define LED3_PIN		3
#define LED3_CON		LED_Forward

#define LED4			4
#define LED4_PORT		B
#define LED4_PIN		4
#define LED4_CON		LED_Forward

#define LED5			5
#define LED5_PORT		B
#define LED5_PIN		5
#define LED5_CON		LED_Forward

#define LED6			6
#define LED6_PORT		B
#define LED6_PIN		6
#define LED6_CON		LED_Forward

#define LED7			7
#define LED7_PORT		B
#define LED7_PIN		7
#define LED7_CON		LED_Forward

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
