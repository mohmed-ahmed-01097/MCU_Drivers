/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : LCD_cfg.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 31, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define LCD_DELAY_CMD		1u
#define LCD_DELAY_CMD_MAX	4u
#define LCD_DELAY_POWER_ON	40u
#define LCD_DELAY_WAIT		50u
#define LCD_DELAY_TOG		500u
#define LCD_DELAY_PAGE		1000u	//5000u

#if defined(AMIT_KIT)

#define LCD_FUNCTION_SET	LCD_FUNCTION_SET_4Bits

#define LCD_COL_NUM			LCD_COL_NUM_16
#define LCD_ROW_NUM			LCD_ROW_NUM_2

#define LCD_DATA_PORT		A
#define LCD_D4				AMIT_LCD4
#define LCD_D5				AMIT_LCD5
#define LCD_D6				AMIT_LCD6
#define LCD_D7				AMIT_LCD7

#define LCD_CONTROL_PORT	B
#define LCD_RS				AMIT_LCD_RS
#define LCD_RW				AMIT_LCD_RW
#define LCD_EN				AMIT_LCD_EN

#elif defined(ETA32_KIT)

#define LCD_FUNCTION_SET	LCD_FUNCTION_SET_4Bits

#define LCD_COL_NUM			LCD_COL_NUM_20
#define LCD_ROW_NUM			LCD_ROW_NUM_4

#define LCD_DATA_PORT		B
#define LCD_D4				Eta32_LCD4
#define LCD_D5				Eta32_LCD5
#define LCD_D6				Eta32_LCD6
#define LCD_D7				Eta32_LCD7

#define LCD_CONTROL_PORT	A
#define LCD_RS				Eta32_LCD_RS
#define LCD_EN				Eta32_LCD_EN

#elif defined(ETA32_MINI_KIT)

#define LCD_FUNCTION_SET	LCD_FUNCTION_SET_4Bits

#define LCD_COL_NUM			LCD_COL_NUM_16
#define LCD_ROW_NUM			LCD_ROW_NUM_2

#define LCD_DATA_PORT		A
#define LCD_D4				Eta32_mini_LCD4
#define LCD_D5				Eta32_mini_LCD5
#define LCD_D6				Eta32_mini_LCD6
#define LCD_D7				Eta32_mini_LCD7

#define LCD_CONTROL_PORT	A
#define LCD_RS				Eta32_mini_LCD_RS
#define LCD_EN				Eta32_mini_LCD_EN

#else

#define LCD_FUNCTION_SET	LCD_FUNCTION_SET_8Bits

#define LCD_COL_NUM			LCD_COL_NUM_32
#define LCD_ROW_NUM			LCD_ROW_NUM_2

#define LCD_DATA_PORT		A
#define LCD_D0				AMIT_LCD0
#define LCD_D1				AMIT_LCD1
#define LCD_D2				AMIT_LCD2
#define LCD_D3				AMIT_LCD3
#define LCD_D4				AMIT_LCD4
#define LCD_D5				AMIT_LCD5
#define LCD_D6				AMIT_LCD6
#define LCD_D7				AMIT_LCD7

#define LCD_CONTROL_PORT	B
#define LCD_RS				AMIT_LCD_RS
#define LCD_RW				AMIT_LCD_RW
#define LCD_EN				AMIT_LCD_EN

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


#endif /* LCD_CFG_H_ */
/*************************** E N D (LCD_cfg.h) ******************************/
