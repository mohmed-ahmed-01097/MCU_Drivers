/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : PUSH_cfg.h													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 30, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef PUSH_CFG_H_
#define PUSH_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#if defined(AMIT_KIT)

#define PUSH0			0
#define PUSH0_PORT		D
#define PUSH0_PIN		AMIT_PUSH0
#define PUSH0_ACTIVE	PUSH_Active_High

#define PUSH1			1
#define PUSH1_PORT		D
#define PUSH1_PIN		AMIT_PUSH1
#define PUSH1_ACTIVE	PUSH_Active_High

#define PUSH2			2
#define PUSH2_PORT		D
#define PUSH2_PIN		AMIT_PUSH2
#define PUSH2_ACTIVE	PUSH_Active_High

#elif defined(ETA32_KIT)

#define PUSH0			0
#define PUSH0_PORT		D
#define PUSH0_PIN		Eta32_Keypad_col0
#define PUSH0_ACTIVE	PUSH_Active_Low

#define PUSH1			1
#define PUSH1_PORT		D
#define PUSH1_PIN		Eta32_Keypad_col1
#define PUSH1_ACTIVE	PUSH_Active_Low

#define PUSH2			2
#define PUSH2_PORT		D
#define PUSH2_PIN		Eta32_Keypad_col2
#define PUSH2_ACTIVE	PUSH_Active_Low

#define PUSH3			3
#define PUSH3_PORT		D
#define PUSH3_PIN		Eta32_Keypad_col3
#define PUSH3_ACTIVE	PUSH_Active_Low

#elif defined(ETA32_MINI_KIT)

#define PUSH0			0
#define PUSH0_PORT		D
#define PUSH0_PIN		Eta32_mini_Keypad_col0
#define PUSH0_ACTIVE	PUSH_Active_Low

#define PUSH1			1
#define PUSH1_PORT		D
#define PUSH1_PIN		Eta32_mini_Keypad_col1
#define PUSH1_ACTIVE	PUSH_Active_Low

#define PUSH2			2
#define PUSH2_PORT		D
#define PUSH2_PIN		Eta32_mini_Keypad_col2
#define PUSH2_ACTIVE	PUSH_Active_Low

#define PUSH3			3
#define PUSH3_PORT		D
#define PUSH3_PIN		Eta32_mini_Keypad_col3
#define PUSH3_ACTIVE	PUSH_Active_Low

#else

#define PUSH0			0
#define PUSH0_PORT		D
#define PUSH0_PIN		GPIO_INT0
#define PUSH0_ACTIVE	PUSH_Active_High

#define PUSH1			1
#define PUSH1_PORT		D
#define PUSH1_PIN		GPIO_INT1
#define PUSH1_ACTIVE	PUSH_Active_High

#define PUSH2			2
#define PUSH2_PORT		B
#define PUSH2_PIN		GPIO_INT2
#define PUSH2_ACTIVE	PUSH_Active_High

#define PUSH3			3
#define PUSH3_PORT		B
#define PUSH3_PIN		AMIT_B0
#define PUSH3_ACTIVE	PUSH_Active_High

#define PUSH4			4
#define PUSH4_PORT		B
#define PUSH4_PIN		AMIT_B4
#define PUSH4_ACTIVE	PUSH_Active_High

#define PUSH5			5
#define PUSH5_PORT		B
#define PUSH5_PIN		AMIT_B5
#define PUSH5_ACTIVE	PUSH_Active_High

#define PUSH6			6
#define PUSH6_PORT		B
#define PUSH6_PIN		AMIT_B6
#define PUSH6_ACTIVE	PUSH_Active_High

#define PUSH7			7
#define PUSH7_PORT		B
#define PUSH7_PIN		AMIT_B7
#define PUSH7_ACTIVE	PUSH_Active_High

#endif

#define DEBOUNCING_CYCLES_NUM	5
#define DEBOUNCING_DELAY		5

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* PUSH_CFG_H_ */
/*************************** E N D (PUSH_cfg.h) ******************************/
