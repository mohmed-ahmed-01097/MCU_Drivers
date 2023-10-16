/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : STEPPER_prg.c												  */
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

#include "STEPPER_cfg.h"
#include "STEPPER_int.h"
#include "STEPPER_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

extern const GPIO_tstrPinConfig kau8STEPPERConfiguration_LGB[STEPPER_NUM];

#if (STEPPER_COIL_STEP == STEPPER_Half_Step)
extern const u8 kau8StepperStep[STEPPER_NUM];
#elif (STEPPER_COIL_STEP == STEPPER_Full_Step)
extern const u8 kau8StepperStep[STEPPER_NUM * 2u];
#endif
extern const u8 ku8StepperNum;

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Description :    Stepper initialization									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void STEPPER_vidInit(void){
	for(u8 i = STEPPER_NUM ; i-- ; ){
		GPIO_tstrPinConfig* pTemp = (GPIO_tstrPinConfig*)&kau8STEPPERConfiguration_LGB[i];
		GPIO_u8PinInit(*pTemp);
		GPIO_u8SetPinValue(pTemp->m_Port, pTemp->m_Pin, pTemp->m_Value);
	}
}

/* ************************************************************************** */
/* Description :    Stepper Run One Cycle									  */
/* Input       :	u16DelayValue, u8Direction								  */
/* Return      :	void													  */
/* ************************************************************************** */
void STEPPER_vidCycle(u16 u16DelayValue, u8 u8Direction){
	switch (u8Direction){
		case STEPPER_WithClockWise :
		case STEPPER_OppositClockWise :
			for(u16 i = (360u / STEPPER_STEP_ANGLE) ; i-- ; ){
				STEPPER_vidStep(u16DelayValue, u8Direction);
			}
			break;
		case STEPPER_Stop :
		default:
			return;
	}
}

/* ************************************************************************** */
/* Description :    Stepper Run Value										  */
/* Input       :	u16DelayValue, u8Direction								  */
/* Return      :	void													  */
/* ************************************************************************** */
void STEPPER_vidStep(u16 u16DelayValue, u8 u8Direction){
	static u8 u8Coil;

	switch (u8Direction){
		case STEPPER_WithClockWise :
			u8Coil = (u8Coil + 1) % ku8StepperNum;
			break;
		case STEPPER_OppositClockWise :
			u8Coil = u8Coil ? (u8Coil - 1) : (ku8StepperNum - 1);
			break;
		case STEPPER_Stop :
		default:
			u8Coil = LBTY_u8ZERO;
			return;
	}

	u8 u8Temp = kau8StepperStep[u8Coil];
	GPIO_tstrPinConfig* pTemp = (GPIO_tstrPinConfig*)kau8STEPPERConfiguration_LGB;
	for(u8 i = STEPPER_NUM ; i-- ; pTemp++){
		GPIO_u8SetPinValue(pTemp->m_Port, pTemp->m_Pin, ((u8Temp & (1<<i)) ? STEPPER_COIL_Set : STEPPER_COIL_Reset));
	}

	vidMyDelay_ms(u16DelayValue);
}


/*************************** E N D (STEPPER_prg.c) ******************************/
