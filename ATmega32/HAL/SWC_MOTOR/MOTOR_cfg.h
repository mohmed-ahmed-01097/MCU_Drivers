/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : MOTOR_cfg.h												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

#define MOTOR_CHANNELS		4u
#define MOTOR_EN_CONTROL	MOTOR_CTRL_ON_OFF
#define MOTOR_EN_FREQ		1000u

#if MOTOR_CHANNELS >= 1u

#define MOTOR_PORT_ENA		B
#define MOTOR_PIN_ENA		3u

#define MOTOR_PORT_INA1		A
#define MOTOR_PIN_INA1		0u
#define MOTOR_PORT_INA2		A
#define MOTOR_PIN_INA2		1u

#endif
#if MOTOR_CHANNELS >= 2u

#define MOTOR_PORT_ENB		D
#define MOTOR_PIN_ENB		7u

#define MOTOR_PORT_INB1		A
#define MOTOR_PIN_INB1		2u
#define MOTOR_PORT_INB2		A
#define MOTOR_PIN_INB2		3u

#endif
#if MOTOR_CHANNELS >= 3u

#define MOTOR_PORT_ENC		D
#define MOTOR_PIN_ENC		5u

#define MOTOR_PORT_INC1		A
#define MOTOR_PIN_INC1		4u
#define MOTOR_PORT_INC2		A
#define MOTOR_PIN_INC2		5u

#endif
#if MOTOR_CHANNELS >= 4u

#define MOTOR_PORT_END		D
#define MOTOR_PIN_END		4u

#define MOTOR_PORT_IND1		A
#define MOTOR_PIN_IND1		6u
#define MOTOR_PORT_IND2		A
#define MOTOR_PIN_IND2		7u

#endif

#define MOTOR_DELAY			5u
#define MOTOR_NUM_DELAY		25u
#define MOTOR_NUM_RATE		20u	//40u

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */


#endif /* MOTOR_CFG_H_ */
/*************************** E N D (MOTOR_cfg.h) ******************************/
