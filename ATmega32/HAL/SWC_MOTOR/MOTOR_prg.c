/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : MOTOR_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "DELAY.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"
#include "TMR_int.h"

#include "MOTOR_cfg.h"
#include "MOTOR_int.h"
#include "MOTOR_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

extern const MOTOR_tstrConfig kau8MOTORConfiguration_LGB[];

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :    Motor initialization									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void MOTOR_vidInit(void){
	for(u8 i = MOTOR_NUM ; i-- ; ){
		GPIO_u8PinInit(kau8MOTORConfiguration_LGB[i].m_IN1);
		GPIO_u8PinInit(kau8MOTORConfiguration_LGB[i].m_IN2);
	}
#if (MOTOR_EN_CONTROL == MOTOR_CTRL_ON_OFF)
	for(u8 i = MOTOR_NUM ; i-- ; ){
		GPIO_u8PinInit(kau8MOTORConfiguration_LGB[i].m_EN);
	}
#elif (MOTOR_EN_CONTROL == MOTOR_CTRL_PWM)
#if MOTOR_CHANNELS >= 1u
	MOTOR_vidPWM0Init();
#endif
#if MOTOR_CHANNELS >= 2u
		MOTOR_vidPWM2Init();
#endif
#if MOTOR_CHANNELS >= 3u
		MOTOR_vidPWM1AInit();
#endif
#if MOTOR_CHANNELS >= 4u
		MOTOR_vidPWM1BInit();
#endif
#endif
}

/* ************************************************************************** */
/* Description :    Motor Run with Direction								  */
/* Input       :	u8Motor, u16Speed, u8Direction							  */
/* Return      :	void													  */
/* ************************************************************************** */
void MOTOR_vidRun(u8 u8Motor, u16 u16Speed, u8 u8Direction){
	if(u8Motor >= MOTOR_NUM)		return;
	MOTOR_tstrConfig *strTemp = (MOTOR_tstrConfig*)&kau8MOTORConfiguration_LGB[u8Motor];

#if (MOTOR_EN_CONTROL == MOTOR_CTRL_ON_OFF)
	GPIO_u8SetPinValue(strTemp->m_EN.m_Port, strTemp->m_EN.m_Pin, u8Direction != MOTOR_Stop);
#elif (MOTOR_EN_CONTROL == MOTOR_CTRL_PWM)
	switch(u8Motor){
#if MOTOR_CHANNELS >= 1u
		case MOTOR_EN0:		PWM_u8SetDuty_OC0(u16Speed);		break;
#endif
#if MOTOR_CHANNELS >= 2u
		case MOTOR_EN1:		PWM_u8SetDuty_OC2(u16Speed);		break;
#endif
#if MOTOR_CHANNELS >= 3u
		case MOTOR_EN2:		PWM_u8SetDuty_OC1A(u16Speed);		break;
#endif
#if MOTOR_CHANNELS >= 4u
		case MOTOR_EN3:		PWM_u8SetDuty_OC1B(u16Speed);		break;
#endif
		default:			break;
	}
#endif

	GPIO_u8SetPinValue(strTemp->m_IN1.m_Port, strTemp->m_IN1.m_Pin, GET_BIT(u8Direction, 0));
	GPIO_u8SetPinValue(strTemp->m_IN2.m_Port, strTemp->m_IN2.m_Pin, GET_BIT(u8Direction, 1));

}

/*************************** E N D (MOTOR_prg.c) ******************************/
