/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : SERVO_prg.c												  */
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
#include "GPIO_priv.h"
#include "TMR_int.h"

#include "SERVO_cfg.h"
#include "SERVO_int.h"
#include "SERVO_priv.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

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

void TMR0_ISR(void){

}
void TMR1_ISR(void){

}
void TMR2_ISR(void){

}

/* ************************************************************************** */
/* Description :    Servo initialization									  */
/* Input       :	void													  */
/* Return      :	void													  */
/* ************************************************************************** */
void Servo_Init(void){ // OC1A ==>D5
#if defined(PWM0)
	TMR0_tstrConfig strTMR0_CFG = {
			.m_TMR_Freq      = 1u/SERVO_INIT_PERIOD,
			.m_TMR_Duty      = SERVO_ZERO_ANGLE,
			.m_TMR_Prescalar = TMR0_Fosc_Prescaler_64,
			.m_TMR_Mode      = TMRx_u8_PWM_Fase_Mode,
			.m_TMR_OutputMode= TMRx_u8_FastPWM_Clear_on_Match,
			.m_TMR_FOC       = LBTY_RESET,
			.m_TMR_OVIE      = LBTY_SET,
			.m_TMR_OCIE      = LBTY_RESET
	};

	TMR0_vidSetConfig((TMR0_tstrConfig* const)&strTMR0_CFG);
	TMR0_vidSetCallBack_OverFlow(TMR0_ISR);
	PWM_vidEnable_OC0();
#elif defined(PWM2)
	TMR2_tstrConfig strTMR2_CFG = {
			.m_TMR_Freq      = 1u/SERVO_INIT_PERIOD,
			.m_TMR_Duty      = SERVO_ZERO_ANGLE,
			.m_TMR_Prescalar = TMR2_Fosc_Prescaler_128,
			.m_TMR_Mode      = TMRx_u8_PWM_Fase_Mode,
			.m_TMR_OutputMode= TMRx_u8_FastPWM_Clear_on_Match,
			.m_TMR_FOC       = LBTY_RESET,
			.m_TMR_OVIE      = LBTY_SET,
			.m_TMR_OCIE      = LBTY_RESET,
			.m_TMR_AsyClock  = TMR2_IO_Clock
	};

	TMR2_vidSetConfig((TMR2_tstrConfig* const)&strTMR2_CFG);
	TMR2_vidSetCallBack_OverFlow(TMR2_ISR);
	PWM_vidEnable_OC2();
#elif defined(PWM1)
	TMR1_tstrConfig strTMR1_CFG = {
		.m_TMR_Freq        = 1u/SERVO_INIT_PERIOD,
		.m_TMR_Duty_A      = SERVO_ZERO_ANGLE,
		.m_TMR_Duty_B      = SERVO_ZERO_ANGLE,
		.m_TMR_Prescalar   = TMR1_Fosc_Prescaler_64,
		.m_TMR_Mode        = TMR1_PWM_Fase_Mode_ICR1,
		.m_TMR_OutputModeA = TMR1_COM_Disconnected,
		.m_TMR_OutputModeB = TMR1_FastPWM_Clear_on_Match,
		.m_TMR_FOCA        = LBTY_RESET,
		.m_TMR_FOCB        = LBTY_RESET,
		.m_TMR_TICIE       = LBTY_RESET,
		.m_TMR_OCIEA       = LBTY_RESET,
		.m_TMR_OCIEB       = LBTY_RESET,
		.m_TMR_TOIE        = LBTY_SET,
		.m_TMR_InputNoise  = LBTY_SET,
		.m_TMR_InputEdge   = TMR1_Capture_Rising_Edge,
	};

	TMR1_vidSetConfig((TMR1_tstrConfig* const)&strTMR1_CFG);
	TMR1_vidSetCallBack_OverFlow(TMR1_ISR);
	PWM_vidEnable_OC1x();
#else
	GPIO_u8SetPinDirection(SERVO_PORT, SERVO_PIN, PIN_OUTPUT);
	GPIO_u8SetPinValue(SERVO_PORT, SERVO_PIN, PIN_Low);
#endif
}

/* ************************************************************************** */
/* Description :    Servo Write Angle										  */
/* Input       :	u8Angle													  */
/* Return      :	void													  */
/* ************************************************************************** */
void Servo_WriteAngle(u16 u16Angle){
	if(u16Angle > SERVO_MAX_ANGLE){
		u16Angle = SERVO_MAX_ANGLE;// takes from 0 to 180
	}
	static u16 u16Duty;
	u16Duty = SERVO_ZERO_ANGLE + (++u16Angle * SERVO_ANGLE_RATIO);

#if defined(PWM0)
	PWM_u8SetDuty_OC0(u16Duty);
#elif defined(PWM2)
	PWM_u8SetDuty_OC2(u16Duty);
#elif defined(PWM1)
	PWM_u8SetDuty_OC1B(u16Duty);
#else
	TOG_BIT(SERVO_PORT_REG->m_PORT.u_Reg, SERVO_PIN);
	DELAY_LOOP_US(u16Duty - 350);
	TOG_BIT(SERVO_PORT_REG->m_PORT.u_Reg, SERVO_PIN);
#endif
}


/*************************** E N D (SERVO_prg.c) ******************************/
