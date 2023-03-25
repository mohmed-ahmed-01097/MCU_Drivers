/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : KEYPAD_cfg.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if 	AMIT_KIT

#elif	ETA32_KIT

#define KP_ROW_NUM			4u
#define KP_ROW_PORT			C
#define KP_ROW0				Eta32_Keypad_Row0
#define KP_ROW1				Eta32_Keypad_Row1
#define KP_ROW2				Eta32_Keypad_Row2
#define KP_ROW3				Eta32_Keypad_Row3

#define KP_COL_NUM			4u
#define KP_COL_PORT			D
#define KP_COL0				Eta32_Keypad_col0
#define KP_COL1				Eta32_Keypad_col1
#define KP_COL2				Eta32_Keypad_col2
#define KP_COL3				Eta32_Keypad_col3

#else

#define KP_ROW_NUM			4u
#define KP_COL_NUM			4u

#define KP_ROW_PORT			C
#define KP_COL_PORT			C

#define KP_ROW_MASK			0x0Fu
#define KP_COL_MASK			0xF0u

#define KP_ROW0				0u
#define KP_ROW1				1u
#define KP_ROW2				2u
#define KP_ROW3				3u

#define KP_COL0				4u
#define KP_COL1				5u
#define KP_COL2				6u
#define KP_COL3				7u

#endif

#define KP_ROW_MASK			(1<<KP_ROW0)|(1<<KP_ROW1)|(1<<KP_ROW2)|(1<<KP_ROW3)
#define KP_COL_MASK			(1<<KP_COL0)|(1<<KP_COL1)|(1<<KP_COL2)|(1<<KP_COL3)

#define KP_KEY00			'1'
#define KP_KEY01			'2'
#define KP_KEY02			'3'
#define KP_KEY03			'A'

#define KP_KEY10			'4'
#define KP_KEY11			'5'
#define KP_KEY12			'6'
#define KP_KEY13			'B'

#define KP_KEY20			'7'
#define KP_KEY21			'8'
#define KP_KEY22			'9'
#define KP_KEY23			'C'

#define KP_KEY30			'*'
#define KP_KEY31			'0'
#define KP_KEY32			'#'
#define KP_KEY33			'D'

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* KEYPAD_CFG_H_ */
/*************************** E N D (KEYPAD_cfg.h) ******************************/
