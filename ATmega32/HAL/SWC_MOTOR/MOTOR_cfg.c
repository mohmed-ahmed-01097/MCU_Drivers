/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : MOTOR_cfg.c												  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Mar 25, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#include "LBTY_int.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"
#include "TMR_int.h"

#include "MOTOR_int.h"
#include "MOTOR_cfg.h"

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************** MACRO/DEFINE SECTION ************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ***************************** CONST SECTION ****************************** */
/* ************************************************************************** */

const MOTOR_tstrConfig kau8MOTORConfiguration_LGB[] = {
#if MOTOR_CHANNELS >= 1u
	{	.m_EN  = {.m_Port = MOTOR_PORT_ENA , .m_Pin = MOTOR_PIN_ENA , .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN1 = {.m_Port = MOTOR_PORT_INA1, .m_Pin = MOTOR_PIN_INA1, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN2 = {.m_Port = MOTOR_PORT_INA2, .m_Pin = MOTOR_PIN_INA2, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low}
	}
#endif
#if MOTOR_CHANNELS >= 2u
	,{	.m_EN  = {.m_Port = MOTOR_PORT_ENB , .m_Pin = MOTOR_PIN_ENB , .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN1 = {.m_Port = MOTOR_PORT_INB1, .m_Pin = MOTOR_PIN_INB1, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN2 = {.m_Port = MOTOR_PORT_INB2, .m_Pin = MOTOR_PIN_INB2, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low}
	}
#endif
#if MOTOR_CHANNELS >= 3u
	,{	.m_EN  = {.m_Port = MOTOR_PORT_ENC , .m_Pin = MOTOR_PIN_ENC , .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN1 = {.m_Port = MOTOR_PORT_INC1, .m_Pin = MOTOR_PIN_INC1, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN2 = {.m_Port = MOTOR_PORT_INC2, .m_Pin = MOTOR_PIN_INC2, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low}
	}
#endif
#if MOTOR_CHANNELS >= 4u
	,{	.m_EN  = {.m_Port = MOTOR_PORT_END , .m_Pin = MOTOR_PIN_END , .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN1 = {.m_Port = MOTOR_PORT_IND1, .m_Pin = MOTOR_PIN_IND1, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low},
		.m_IN2 = {.m_Port = MOTOR_PORT_IND2, .m_Pin = MOTOR_PIN_IND2, .m_Dir = PIN_OUTPUT, .m_Value = PIN_Low}
	}
#endif
};

/* ************************************************************************** */
/* ***************************** VARIABLE SECTION *************************** */
/* ************************************************************************** */
#if defined(PWM0)
	TMR0_tstrConfig strTMR0_CFG = {
			.m_TMR_Freq      = MOTOR_EN_FREQ,
			.m_TMR_Duty      = LBTY_u16ZERO,
			.m_TMR_Prescalar = TMR0_Fosc_Prescaler_64,
			.m_TMR_Mode      = TMRx_u8_PWM_Fase_Mode,
			.m_TMR_OutputMode= TMRx_u8_FastPWM_Clear_on_Match,
			.m_TMR_FOC       = LBTY_RESET,
			.m_TMR_OVIE      = LBTY_SET,
			.m_TMR_OCIE      = LBTY_RESET
	};
#endif
#if defined(PWM2)
	TMR2_tstrConfig strTMR2_CFG = {
			.m_TMR_Freq      = MOTOR_EN_FREQ,
			.m_TMR_Duty      = LBTY_u16ZERO,
			.m_TMR_Prescalar = TMR2_Fosc_Prescaler_128,
			.m_TMR_Mode      = TMRx_u8_PWM_Fase_Mode,
			.m_TMR_OutputMode= TMRx_u8_FastPWM_Clear_on_Match,
			.m_TMR_FOC       = LBTY_RESET,
			.m_TMR_OVIE      = LBTY_SET,
			.m_TMR_OCIE      = LBTY_RESET,
			.m_TMR_AsyClock  = TMR2_IO_Clock
	};
#endif
#if defined(PWM1)
	TMR1_tstrConfig strTMR1_CFG = {
		.m_TMR_Freq        = MOTOR_EN_FREQ,
		.m_TMR_Duty_A      = LBTY_u16ZERO,
		.m_TMR_Duty_B      = LBTY_u16ZERO,
		.m_TMR_Prescalar   = TMR1_Fosc_Prescaler_64,
		.m_TMR_Mode        = TMR1_PWM_Fase_Mode_ICR1,
		.m_TMR_OutputModeA = TMR1_COM_Disconnected,
		.m_TMR_OutputModeB = TMR1_COM_Disconnected,
		.m_TMR_FOCA        = LBTY_RESET,
		.m_TMR_FOCB        = LBTY_RESET,
		.m_TMR_TICIE       = LBTY_RESET,
		.m_TMR_OCIEA       = LBTY_RESET,
		.m_TMR_OCIEB       = LBTY_RESET,
		.m_TMR_TOIE        = LBTY_SET,
		.m_TMR_InputNoise  = LBTY_SET,
		.m_TMR_InputEdge   = TMR1_Capture_Rising_Edge,
	};
#endif
/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void TMR0_ISR(void){

}
void TMR1_ISR(void){

}
void TMR2_ISR(void){

}

void MOTOR_vidPWM0Init(void){
#if defined(PWM0)
	TMR0_vidSetConfig((TMR0_tstrConfig* const)&strTMR0_CFG);
	TMR0_vidSetCallBack_OverFlow(TMR0_ISR);
	PWM_vidEnable_OC0();
#endif

}
void MOTOR_vidPWM2Init(void){
#if defined(PWM2)
	TMR2_vidSetConfig((TMR2_tstrConfig* const)&strTMR2_CFG);
	TMR2_vidSetCallBack_OverFlow(TMR2_ISR);
	PWM_vidEnable_OC2();
#endif

}
void MOTOR_vidPWM1AInit(void){
#if defined(PWM1)
	strTMR1_CFG.m_TMR_OutputModeA = TMR1_FastPWM_Clear_on_Match;
	TMR1_vidSetConfig((TMR1_tstrConfig* const)&strTMR1_CFG);
	TMR1_vidSetCallBack_OverFlow(TMR1_ISR);
	PWM_vidEnable_OC1x();
#endif

}
void MOTOR_vidPWM1BInit(void){
#if defined(PWM1)
	strTMR1_CFG.m_TMR_OutputModeB = TMR1_FastPWM_Clear_on_Match;
	TMR1_vidSetConfig((TMR1_tstrConfig* const)&strTMR1_CFG);
	TMR1_vidSetCallBack_OverFlow(TMR1_ISR);
	PWM_vidEnable_OC1x();
#endif
}

/*************************** E N D (MOTOR_cfg.c) ******************************/
