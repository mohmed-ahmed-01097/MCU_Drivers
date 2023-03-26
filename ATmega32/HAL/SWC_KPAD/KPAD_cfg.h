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

#ifndef KPAD_CFG_H_
#define KPAD_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */
/*
|     |     |     |
#     #     #     # PULL UP
|     |     |     |
@ --- @ --- @ --- @
|     |     |     |---------- ROW0	}
@ --- @ --- @ --- @					}
|     |     |     |---------- ROW1	}
@ --- @ --- @ --- @ 				}<== OUTPUT
|     |     |     |---------- ROW2	}
@ --- @ --- @ --- @	  				}
|     |     |     |---------- ROW3	}
|     |     |     |
COL0  COL1  COL2  COL3				 <== INPUT
*/
#if 	AMIT_KIT

#define KPAD_ROW_NUM			3u
#define KPAD_COL_NUM			3u

#define KPAD_ROW_PORT			A
#define KPAD_COL_PORT			A

#define KPAD_ROW0				0u
#define KPAD_ROW1				1u
#define KPAD_ROW2				2u
#define KPAD_ROW3				KPAD_ROW0

#define KPAD_COL0				4u
#define KPAD_COL1				5u
#define KPAD_COL2				6u
#define KPAD_COL3				KPAD_COL0

#elif	ETA32_KIT

#define KPAD_ROW_NUM			4u
#define KPAD_ROW_PORT			C
#define KPAD_ROW0				Eta32_Keypad_Row0
#define KPAD_ROW1				Eta32_Keypad_Row1
#define KPAD_ROW2				Eta32_Keypad_Row2
#define KPAD_ROW3				Eta32_Keypad_Row3

#define KPAD_COL_NUM			4u
#define KPAD_COL_PORT			D
#define KPAD_COL0				Eta32_Keypad_col0
#define KPAD_COL1				Eta32_Keypad_col1
#define KPAD_COL2				Eta32_Keypad_col2
#define KPAD_COL3				Eta32_Keypad_col3

#else

#define KPAD_ROW_NUM			4u
#define KPAD_COL_NUM			4u

#define KPAD_ROW_PORT			C
#define KPAD_COL_PORT			C

#define KPAD_ROW0				0u
#define KPAD_ROW1				1u
#define KPAD_ROW2				2u
#define KPAD_ROW3				3u

#define KPAD_COL0				4u
#define KPAD_COL1				5u
#define KPAD_COL2				6u
#define KPAD_COL3				7u

#endif

#define KPAD_MAX_COL			4u
#define KPAD_MAX_ROW			4u

#define KPAD_ROW_DIR_OUTPUT
//#define KPAD_COL_DIR_OUTPUT

#define KPAD_KEY_PRESSED		PIN_Low
#define KPAD_KEY_RELEASED		PIN_High

#define KPAD_ROW_MASK			(1<<KPAD_ROW0)|(1<<KPAD_ROW1)|(1<<KPAD_ROW2)|(1<<KPAD_ROW3)
#define KPAD_COL_MASK			(1<<KPAD_COL0)|(1<<KPAD_COL1)|(1<<KPAD_COL2)|(1<<KPAD_COL3)

/** Row 0 **/
#define KPAD_KEY00				'1'
#define KPAD_KEY01				'2'
#define KPAD_KEY02				'3'
#define KPAD_KEY03				'A'

/** Row 1 **/
#define KPAD_KEY10				'4'
#define KPAD_KEY11				'5'
#define KPAD_KEY12				'6'
#define KPAD_KEY13				'B'

/** Row 2 **/
#define KPAD_KEY20				'7'
#define KPAD_KEY21				'8'
#define KPAD_KEY22				'9'
#define KPAD_KEY23				'C'

/** Row 3 **/
#define KPAD_KEY30				'*'
#define KPAD_KEY31				'0'
#define KPAD_KEY32				'#'
#define KPAD_KEY33				'D'

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* KPAD_CFG_H_ */
/*************************** E N D (KEYPAD_cfg.h) ******************************/
