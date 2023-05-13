/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
/* date        : Apr 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"
#include "LCTY_int.h"

#include "INTP.h"

#include "GPIO_int.h"
#include "GPIO_cfg.h"

#include "TMR_int.h"
#include "TMR_cfg.h"
#include "TMR_priv.h"

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

static void (*pFuncCallBack_TMR0_CompareMatch)(void);
static void (*pFuncCallBack_TMR0_OverFlow)(void);

static void (*pFuncCallBack_TMR2_CompareMatch)(void);
static void (*pFuncCallBack_TMR2_OverFlow)(void);

static void (*pFuncCallBack_TMR1_CaptureEven)(void);
static void (*pFuncCallBack_TMR1_CompareMatch_A)(void);
static void (*pFuncCallBack_TMR1_CompareMatch_B)(void);
static void (*pFuncCallBack_TMR1_OverFlow)(void);

static volatile u16 TMR1_u16Reload_GLB = TMR1_COUNTER_INIT;

#if defined(TMR0) || defined(PWM0)
static volatile TMR0_tstrConfig strTMR0_Config_GLB = {
	.m_TMR_Reload    = TMR0_COUNTER_INIT,
	.m_TMR_Compare   = TMR0_OUTPUT_COMPARE_INIT,
	.m_TMR_Prescalar = TMR0_CLOCK_SOURCE,
	.m_TMR_Mode      = TMR0_MODE_INIT,
	.m_TMR_OutputMode= TMR0_COMPARE_OUTPUT_MODE,
	.m_TMR_FOC       = LBTY_RESET,
	.m_TMR_OVIE      = TMR0_OVERFLOW_INTERRUPT_INIT_STATE,
	.m_TMR_OCIE      = TMR0_COMPARE_MATCH_INTERRUPT_INIT_STATE
};
#endif
#if defined(TMR2) || defined(PWM2)
static volatile TMR2_tstrConfig strTMR2_Config_GLB = {
	.m_TMR_Reload    = TMR2_COUNTER_INIT,
	.m_TMR_Compare   = TMR2_OUTPUT_COMPARE_INIT,
	.m_TMR_Prescalar = TMR2_CLOCK_SOURCE,
	.m_TMR_Mode      = TMR2_MODE_INIT,
	.m_TMR_OutputMode= TMR2_COMPARE_OUTPUT_MODE,
	.m_TMR_FOC       = LBTY_RESET,
	.m_TMR_OVIE      = TMR2_OVERFLOW_INTERRUPT_INIT_STATE,
	.m_TMR_OCIE      = TMR2_COMPARE_MATCH_INTERRUPT_INIT_STATE,
	.m_TMR_AsyClock  = TMR2_ASYNCHRONOUS_CLOCK
};
#endif

static volatile u8  TMR0_u8OverflewNum_GLB  = LBTY_u8ZERO;
static volatile u8  TMR2_u8OverflewNum_GLB  = LBTY_u8ZERO;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void TMR0_vidSetConfig(TMR0_tstrConfig const* const pstrConfig){
	if(pstrConfig != LBTY_NULL){
		strTMR0_Config_GLB = *pstrConfig;
	}
	TMR0_vidInit();
}

void TMR0_vidSRestConfig(TMR0_tstrConfig* const pstrConfig){
	strTMR0_Config_GLB.m_TMR_Reload    = TMR0_COUNTER_INIT;
	strTMR0_Config_GLB.m_TMR_Compare   = TMR0_OUTPUT_COMPARE_INIT;
	strTMR0_Config_GLB.m_TMR_Prescalar = TMR0_CLOCK_SOURCE;
	strTMR0_Config_GLB.m_TMR_Mode      = TMR0_MODE_INIT;
	strTMR0_Config_GLB.m_TMR_OutputMode= TMR0_COMPARE_OUTPUT_MODE;
	strTMR0_Config_GLB.m_TMR_FOC       = LBTY_RESET;
	strTMR0_Config_GLB.m_TMR_OVIE      = TMR0_OVERFLOW_INTERRUPT_INIT_STATE;
	strTMR0_Config_GLB.m_TMR_OCIE      = TMR0_COMPARE_MATCH_INTERRUPT_INIT_STATE;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strTMR0_Config_GLB;
	}
	TMR0_vidInit();
}

void TMR0_vidInit(void){
	//S_SFIOR->sBits.m_PSR10 = LBTY_SET;

	//TMR0_vidEnable();
	S_TMR0->m_TCCR0.sBits.m_CSx   = strTMR0_Config_GLB.m_TMR_Prescalar;
	if(strTMR0_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_FallingEdge ||
	   strTMR0_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
	//TMR0_u8SetMode(TMR0_MODE_INIT);
	S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(strTMR0_Config_GLB.m_TMR_Mode, TMRx_WGMx0_MASK);
	S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(strTMR0_Config_GLB.m_TMR_Mode, TMRx_WGMx1_MASK);
	//TMR0_u8SetOutputMode(TMR0_COMPARE_OUTPUT_MODE);
	S_TMR0->m_TCCR0.sBits.m_COMx  = strTMR0_Config_GLB.m_TMR_OutputMode;
	S_TMR0->m_TCCR0.sBits.m_FOCx  = strTMR0_Config_GLB.m_TMR_FOC;

#if TMR0
	//TMR0_u8SetOutputCompare(TMR0_OUTPUT_COMPARE_INIT);
	S_TMR0->m_OCR0  = strTMR0_Config_GLB.m_TMR_Compare;
	//TMR0_u8SetCounter(TMR0_COUNTER_INIT);
	S_TMR0->m_TCNT0 = strTMR0_Config_GLB.m_TMR_Reload;
#elif PWM0
	PWM_u8SetFreq_OC0(PWM0_FREQ_INIT);
	PWM_u8SetDuty_OC0(PWM0_DUTY_INIT);
	PWM_vidDisable_OC0();
#endif

	S_TIMSK->sBits.m_OCIE0 = strTMR0_Config_GLB.m_TMR_OCIE;
	S_TIMSK->sBits.m_TOIE0 = strTMR0_Config_GLB.m_TMR_OVIE;

	S_TIFR->sBits.m_OCF0   = LBTY_RESET;
	S_TIFR->sBits.m_TOV0   = LBTY_RESET;
}

void TMR0_vidEnable(void){
	S_TMR0->m_TCCR0.sBits.m_CSx = strTMR0_Config_GLB.m_TMR_Prescalar;
	if(strTMR0_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_FallingEdge ||
	   strTMR0_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
}

void TMR0_vidDisable(void){
	S_TMR0->m_TCCR0.sBits.m_CSx = TMRx_NoClockSource_Disable;
}

LBTY_tenuErrorStatus TMR0_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
			S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMRx_u8_Normal_Mode, TMRx_WGMx0_MASK);
			S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMRx_u8_Normal_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_PWM_PhaseCorrect_Mode:
			S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMRx_u8_PWM_PhaseCorrect_Mode, TMRx_WGMx0_MASK);
			S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMRx_u8_PWM_PhaseCorrect_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_CTC_Mode_Mode:
			S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMRx_u8_CTC_Mode_Mode, TMRx_WGMx0_MASK);
			S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMRx_u8_CTC_Mode_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_PWM_Fase_Mode:
			S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMRx_u8_PWM_Fase_Mode, TMRx_WGMx0_MASK);
			S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMRx_u8_PWM_Fase_Mode, TMRx_WGMx1_MASK);
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	if(u8RetErrorState == LBTY_OK){
		strTMR0_Config_GLB.m_TMR_Mode = u8Mode;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR0_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR0->m_TCCR0.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR0->m_TCCR0.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
		case TMRx_u8_CTC_Mode_Mode:
			switch(u8OutMode){
				case TMRx_u8_COM_Toggle_on_Match:	S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_COM_Toggle_on_Match;			break;
				case TMRx_u8_COM_Clear_on_Match:	S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_COM_Clear_on_Match;			break;
				case TMRx_u8_COM_Set_on_Match:		S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_COM_Set_on_Match;			break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMRx_u8_PWM_PhaseCorrect_Mode:
			switch(u8OutMode){
				case TMRx_u8_PhasePWM_Clear_on_Match:S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_PhasePWM_Clear_on_Match;	break;
				case TMRx_u8_PhasePWM_Set_on_Match:	 S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_PhasePWM_Set_on_Match;		break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMRx_u8_PWM_Fase_Mode:
			switch(u8OutMode){
				case TMRx_u8_FastPWM_Clear_on_Match:S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_FastPWM_Clear_on_Match;		break;
				case TMRx_u8_FastPWM_Set_on_Match:	S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_FastPWM_Set_on_Match;		break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	if(u8RetErrorState == LBTY_OK){
		GPIO_u8SetPinDirection(TMR_OC0_PORT, TMR_OC0_PIN, PIN_OUTPUT);
		strTMR0_Config_GLB.m_TMR_OutputMode = u8Mode;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR0_u8SetOutputCompare(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		S_TMR0->m_OCR0 = strTMR0_Config_GLB.m_TMR_Compare = u8Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR0_u8SetCounter(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		S_TMR0->m_TCNT0 = strTMR0_Config_GLB.m_TMR_Reload = u8Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR0_u8GetOutputCompare(u8* pu8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu8Reload != LBTY_NULL){
		*pu8Reload = S_TMR0->m_OCR0;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR0_u8GetCounter(u8* pu8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu8Reload != LBTY_NULL){
		*pu8Reload = S_TMR0->m_TCNT0;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

/** TODO: Phase Correct Freq, and Duty Update **/
#if PWM0
static u16 TMR0_u8GetPrescaler(void){
	u16 u16RetValue;
	switch(S_TMR0->m_TCCR0.sBits.m_CSx){
		case TMRx_NoClockSource_Disable:	u16RetValue = 0;		break;
		case TMRx_Fosc_Prescaler_1:			u16RetValue = 1;		break;
		case TMRx_Fosc_Prescaler_8:			u16RetValue = 8;		break;
		case TMRx_Fosc_Prescaler_64:		u16RetValue = 64;		break;
		case TMRx_Fosc_Prescaler_256:		u16RetValue = 256;		break;
		case TMRx_Fosc_Prescaler_1024:		u16RetValue = 1024;		break;
		default:						u16RetValue = LBTY_u16MAX; 	break;
	}
	return u16RetValue;
}

LBTY_tenuErrorStatus PWM_u8SetFreq_OC0(u16 u16Freq){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR0->m_TCCR0.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR0->m_TCCR0.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
//			u16TimerValue = (u16)(LBTY_u8MAX - (u32)(F_CPU / ((f32)u16Freq * TMR0_u8GetPrescaler())));
			break;
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)(LBTY_u8MAX - (u32)(F_CPU / ((f32)u16Freq * TMR0_u8GetPrescaler())));
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR0_u8SetCounter((u8)u16TimerValue);
}

LBTY_tenuErrorStatus PWM_u8SetDuty_OC0(u8 u8Duty){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR0->m_TCCR0.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR0->m_TCCR0.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
//			u16TimerValue = (u16)((f32)u8Duty / 100.0 * (LBTY_u8MAX - strTMR0_Config_GLB.m_TMR_Reload)) +  strTMR0_Config_GLB.m_TMR_Reload;
			break;
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)((f32)u8Duty / 100.0 * (LBTY_u8MAX - strTMR0_Config_GLB.m_TMR_Reload)) +  strTMR0_Config_GLB.m_TMR_Reload;
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR0_u8SetOutputCompare((u8)u16TimerValue);
}

#endif

void TMR0_vidSetOverflowNum(u8 u8Num){
	TMR0_u8OverflewNum_GLB = u8Num;
}

void TMR0_vidGetOverflowNum(u8* pu8Num){
	*pu8Num = TMR0_u8OverflewNum_GLB;
}

void TMR0_vidGetTicks(u32* pu32Tick){
	*pu32Tick = (u32)(256 - strTMR0_Config_GLB.m_TMR_Reload) * TMR0_u8OverflewNum_GLB + S_TMR0->m_TCNT0;
}

/********************************************************************************************************************/

void TMR0_vidCompareMatch_Enable(void){S_TIMSK->sBits.m_OCIE0 = LBTY_SET;}
void TMR0_vidCompareMatch_Disable(void){S_TIMSK->sBits.m_OCIE0 = LBTY_RESET;}

void TMR0_vidSetCompareMatch_Flag(void){S_TIFR->sBits.m_OCF0   = LBTY_SET;}
void TMR0_vidClrCompareMatch_Flag(void){S_TIFR->sBits.m_OCF0   = LBTY_RESET;}

void TMR0_vidOverFlow_Enable(void) {S_TIMSK->sBits.m_TOIE0 = LBTY_SET;}
void TMR0_vidOverFlow_Disable(void){S_TIMSK->sBits.m_TOIE0 = LBTY_RESET;}

void TMR0_vidSetOverFlow_Flag(void){S_TIFR->sBits.m_TOV0   = LBTY_SET;}
void TMR0_vidClrOverFlow_Flag(void){S_TIFR->sBits.m_TOV0   = LBTY_RESET;}

void TMR0_vidSetCallBack_CompareMatch(void (*pCallBack)(void)){
	pFuncCallBack_TMR0_CompareMatch = pCallBack;
}
void TMR0_vidSetCallBack_OverFlow(void (*pCallBack)(void)){
	pFuncCallBack_TMR0_OverFlow = pCallBack;
}

/*
* 11 	COMP Timer/Counter0 Compare Match
* 12 	OVF Timer/Counter0 Overflow
ISR(TIM0_OVF_vect){
}
ISR(TIM0_COMP_vect){
}
*/
ISR(TIMER0_COMP_vect){
	pFuncCallBack_TMR0_CompareMatch();
	//TMR0_vidClrCompareMatch_Flag();
}
ISR(TIMER0_OVF_vect){
	S_TMR0->m_TCNT0 = strTMR0_Config_GLB.m_TMR_Reload;
	TMR0_u8OverflewNum_GLB++;
	pFuncCallBack_TMR0_OverFlow();
	//TMR0_vidClrOverFlow_Flag();
}

/********************************************************************************************************************/

// Timer/Counter Control Register2 Update Busy
LCTY_INLINE  void TMR2_vidControlUpdateBusy(void){while(S_TMR2->m_ASSR.sBits.m_TCR2UB);}

// Output Compare Register2 Update Busy
LCTY_INLINE  void TMR2_vidCompareUpdateBusy(void){while(S_TMR2->m_ASSR.sBits.m_OCR2UB);}

// Timer/Counter2 Update Busy
LCTY_INLINE  void TMR2_vidTimerUpdateBusy(void){while(S_TMR2->m_ASSR.sBits.m_TCN2UB);}

void TMR2_vidSetConfig(TMR2_tstrConfig const* const pstrConfig){
	if(pstrConfig != LBTY_NULL){
		strTMR2_Config_GLB = *pstrConfig;
	}
	TMR2_vidInit();
}

void TMR2_vidSRestConfig(TMR2_tstrConfig* const pstrConfig){
	strTMR2_Config_GLB.m_TMR_Reload    = TMR2_COUNTER_INIT;
	strTMR2_Config_GLB.m_TMR_Compare   = TMR2_OUTPUT_COMPARE_INIT;
	strTMR2_Config_GLB.m_TMR_Prescalar = TMR2_CLOCK_SOURCE;
	strTMR2_Config_GLB.m_TMR_Mode      = TMR2_MODE_INIT;
	strTMR2_Config_GLB.m_TMR_OutputMode= TMR2_COMPARE_OUTPUT_MODE;
	strTMR2_Config_GLB.m_TMR_FOC       = LBTY_RESET;
	strTMR2_Config_GLB.m_TMR_OVIE      = TMR2_OVERFLOW_INTERRUPT_INIT_STATE;
	strTMR2_Config_GLB.m_TMR_OCIE      = TMR2_COMPARE_MATCH_INTERRUPT_INIT_STATE;
	strTMR2_Config_GLB.m_TMR_AsyClock  = TMR2_ASYNCHRONOUS_CLOCK;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strTMR2_Config_GLB;
	}
	TMR2_vidInit();
}

void TMR2_vidInit(void){
	//S_SFIOR->sBits.m_PSR2 = LBTY_SET;

	// Asynchronous Timer/Counter2
	S_TMR2->m_ASSR.sBits.m_AS2 = strTMR2_Config_GLB.m_TMR_AsyClock;

	if(strTMR2_Config_GLB.m_TMR_AsyClock == TMR2_TOSC_Clock){
		GPIO_u8SetPinDirection(TMR_OSC1_PORT, TMR_OSC1_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_OSC2_PORT, TMR_OSC2_PIN, PIN_INPUT);
	}

	//TMR2_vidEnable();
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_CSx   = strTMR2_Config_GLB.m_TMR_Prescalar;
	if(strTMR2_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_FallingEdge ||
	   strTMR2_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
	//TMR2_u8SetMode(TMR2_MODE_INIT);
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_WGMx0 = GET_BIT(strTMR2_Config_GLB.m_TMR_Mode, TMRx_WGMx0_MASK);
	S_TMR2->m_TCCR2.sBits.m_WGMx1 = GET_BIT(strTMR2_Config_GLB.m_TMR_Mode, TMRx_WGMx1_MASK);
	//TMR2_u8SetOutputMode(TMR2_COMPARE_OUTPUT_MODE);
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_COMx  = strTMR2_Config_GLB.m_TMR_OutputMode;
	S_TMR2->m_TCCR2.sBits.m_FOCx  = strTMR2_Config_GLB.m_TMR_FOC;

#if TMR2
	//TMR2_u8SetOutputCompare(TMR2_OUTPUT_COMPARE_INIT);
	TMR2_vidCompareUpdateBusy();
	S_TMR2->m_OCR2 = strTMR2_Config_GLB.m_TMR_Compare;
	//TMR2_u8SetCounter(TMR2_COUNTER_INIT);
	TMR2_vidTimerUpdateBusy();
	S_TMR2->m_TCNT2 = strTMR2_Config_GLB.m_TMR_Reload;
#elif PWM2
	PWM_u8SetFreq_OC2(PWM2_FREQ_INIT);
	PWM_u8SetDuty_OC2(PWM2_DUTY_INIT);
	PWM_vidDisable_OC2();
#endif

	S_TIMSK->sBits.m_OCIE2 = strTMR2_Config_GLB.m_TMR_OCIE;
	S_TIMSK->sBits.m_TOIE2 = strTMR2_Config_GLB.m_TMR_OVIE;

	S_TIFR->sBits.m_OCF2   = LBTY_RESET;
	S_TIFR->sBits.m_TOV2   = LBTY_RESET;
}

void TMR2_vidEnable(void){
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_CSx = strTMR2_Config_GLB.m_TMR_Prescalar;
	if(strTMR2_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_FallingEdge ||
	   strTMR2_Config_GLB.m_TMR_Prescalar == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
}

void TMR2_vidDisable(void){
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_CSx = TMRx_NoClockSource_Disable;
}

LBTY_tenuErrorStatus TMR2_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	TMR2_vidControlUpdateBusy();
	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
			S_TMR2->m_TCCR2.sBits.m_WGMx0 = GET_BIT(TMRx_u8_Normal_Mode, TMRx_WGMx0_MASK);
			S_TMR2->m_TCCR2.sBits.m_WGMx1 = GET_BIT(TMRx_u8_Normal_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_PWM_PhaseCorrect_Mode:
			S_TMR2->m_TCCR2.sBits.m_WGMx0 = GET_BIT(TMRx_u8_PWM_PhaseCorrect_Mode, TMRx_WGMx0_MASK);
			S_TMR2->m_TCCR2.sBits.m_WGMx1 = GET_BIT(TMRx_u8_PWM_PhaseCorrect_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_CTC_Mode_Mode:
			S_TMR2->m_TCCR2.sBits.m_WGMx0 = GET_BIT(TMRx_u8_CTC_Mode_Mode, TMRx_WGMx0_MASK);
			S_TMR2->m_TCCR2.sBits.m_WGMx1 = GET_BIT(TMRx_u8_CTC_Mode_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_PWM_Fase_Mode:
			S_TMR2->m_TCCR2.sBits.m_WGMx0 = GET_BIT(TMRx_u8_PWM_Fase_Mode, TMRx_WGMx0_MASK);
			S_TMR2->m_TCCR2.sBits.m_WGMx1 = GET_BIT(TMRx_u8_PWM_Fase_Mode, TMRx_WGMx1_MASK);
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	if(u8RetErrorState == LBTY_OK){
		strTMR2_Config_GLB.m_TMR_Mode = u8Mode;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR2->m_TCCR2.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR2->m_TCCR2.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	TMR2_vidControlUpdateBusy();
	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
		case TMRx_u8_CTC_Mode_Mode:
			switch(u8OutMode){
				case TMRx_u8_COM_Toggle_on_Match:	S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_COM_Toggle_on_Match;			break;
				case TMRx_u8_COM_Clear_on_Match:	S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_COM_Clear_on_Match;			break;
				case TMRx_u8_COM_Set_on_Match:		S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_COM_Set_on_Match;			break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMRx_u8_PWM_PhaseCorrect_Mode:
			switch(u8OutMode){
				case TMRx_u8_PhasePWM_Clear_on_Match:S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_PhasePWM_Clear_on_Match;	break;
				case TMRx_u8_PhasePWM_Set_on_Match:	 S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_PhasePWM_Set_on_Match;		break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMRx_u8_PWM_Fase_Mode:
			switch(u8OutMode){
				case TMRx_u8_FastPWM_Clear_on_Match:S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_FastPWM_Clear_on_Match;		break;
				case TMRx_u8_FastPWM_Set_on_Match:	S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_FastPWM_Set_on_Match;		break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	if(u8RetErrorState == LBTY_OK){
		GPIO_u8SetPinDirection(TMR_OC2_PORT, TMR_OC2_PIN, PIN_OUTPUT);
		strTMR2_Config_GLB.m_TMR_OutputMode = u8Mode;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8SetOutputCompare(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		TMR2_vidCompareUpdateBusy();
		S_TMR2->m_OCR2 = strTMR2_Config_GLB.m_TMR_Compare = u8Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8SetCounter(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		TMR2_vidTimerUpdateBusy();
		S_TMR2->m_TCNT2 = strTMR2_Config_GLB.m_TMR_Reload = u8Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8GetOutputCompare(u8* pu8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu8Reload != LBTY_NULL){
		*pu8Reload = S_TMR2->m_OCR2;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8GetCounter(u8* pu8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu8Reload != LBTY_NULL){
		*pu8Reload = S_TMR2->m_TCNT2;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

#if PWM2
static u16 TMR2_u8GetPrescaler(void){
	u16 u16RetValue;
	switch(S_TMR2->m_TCCR2.sBits.m_CSx){
		case TMRx_NoClockSource_Disable:	u16RetValue = 0;		break;
		case TMRx_Fosc_Prescaler_1:			u16RetValue = 1;		break;
		case TMRx_Fosc_Prescaler_8:			u16RetValue = 8;		break;
		case TMRx_Fosc_Prescaler_64:		u16RetValue = 64;		break;
		case TMRx_Fosc_Prescaler_256:		u16RetValue = 256;		break;
		case TMRx_Fosc_Prescaler_1024:		u16RetValue = 1024;		break;
		default:						u16RetValue = LBTY_u16MAX; 	break;
	}
	return u16RetValue;
}

LBTY_tenuErrorStatus PWM_u8SetFreq_OC2(u16 u16Freq){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR2->m_TCCR2.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR2->m_TCCR2.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
//			u16TimerValue = (u16)(LBTY_u8MAX - (u32)(F_CPU / ((f32)u16Freq * TMR2_u8GetPrescaler())));
			break;
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)(LBTY_u8MAX - (u32)(F_CPU / ((f32)u16Freq * TMR2_u8GetPrescaler())));
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR2_u8SetCounter((u8)u16TimerValue);
}

LBTY_tenuErrorStatus PWM_u8SetDuty_OC2(u8 u8Duty){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR2->m_TCCR2.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR2->m_TCCR2.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
//			u16TimerValue = (u16)((f32)u8Duty / 100.0 * (LBTY_u8MAX - strTMR2_Config_GLB.m_TMR_Reload)) +  strTMR2_Config_GLB.m_TMR_Reload;
			break;
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)((f32)u8Duty / 100.0 * (LBTY_u8MAX - strTMR2_Config_GLB.m_TMR_Reload)) +  strTMR2_Config_GLB.m_TMR_Reload;
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR2_u8SetOutputCompare((u8)u16TimerValue);
}

#endif

void TMR2_vidSetOverflowNum(u8 u8Num){
	TMR2_u8OverflewNum_GLB = u8Num;
}

void TMR2_vidGetOverflowNum(u8* pu8Num){
	*pu8Num = TMR2_u8OverflewNum_GLB;
}

void TMR2_vidGetTicks(u32* pu32Tick){
	*pu32Tick = (u32)(256 - strTMR2_Config_GLB.m_TMR_Reload) * TMR2_u8OverflewNum_GLB + S_TMR2->m_TCNT2;
}

/********************************************************************************************************************/

void TMR2_vidCompareMatch_Enable(void) {S_TIMSK->sBits.m_OCIE2 = LBTY_SET;}
void TMR2_vidCompareMatch_Disable(void){S_TIMSK->sBits.m_OCIE2 = LBTY_RESET;}

void TMR2_vidSetCompareMatch_Flag(void){S_TIFR->sBits.m_OCF2   = LBTY_SET;}
void TMR2_vidClrCompareMatch_Flag(void){S_TIFR->sBits.m_OCF2   = LBTY_RESET;}

void TMR2_vidOverFlow_Enable(void) {S_TIMSK->sBits.m_TOIE2 = LBTY_SET;}
void TMR2_vidOverFlow_Disable(void){S_TIMSK->sBits.m_TOIE2 = LBTY_RESET;}

void TMR2_vidSetOverFlow_Flag(void){S_TIFR->sBits.m_TOV2   = LBTY_SET;}
void TMR2_vidClrOverFlow_Flag(void){S_TIFR->sBits.m_TOV2   = LBTY_RESET;}

void TMR2_vidSetCallBack_CompareMatch(void (*pCallBack)(void)){
	pFuncCallBack_TMR2_CompareMatch = pCallBack;
}
void TMR2_vidSetCallBack_OverFlow(void (*pCallBack)(void)){
	pFuncCallBack_TMR2_OverFlow = pCallBack;
}

/*
* 5		COMP Timer/Counter2 Compare Match
* 6  	OVF Timer/Counter2 Overflow
ISR(TIM2_OVF_vect){
}
ISR(TIM2_COMP_vect){
}
*/
ISR(TIMER2_COMP_vect){
	pFuncCallBack_TMR2_CompareMatch();
	//TMR2_vidClrCompareMatch_Flag();
}
ISR(TIMER2_OVF_vect){
	S_TMR2->m_TCNT2 = strTMR2_Config_GLB.m_TMR_Reload;
	TMR2_u8OverflewNum_GLB++;
	pFuncCallBack_TMR2_OverFlow();
	//TMR2_vidClrOverFlow_Flag();
}

/********************************************************************************************************************/

void TMR1_vidInit(void){

	//S_SFIOR->sBits.m_PSR10 = LBTY_SET;

	S_TMR1->m_TCCR1A.sBits.m_WGM10 = GET_BIT(TMR1_MODE_INIT, TMRx_WGMx0_MASK);
	S_TMR1->m_TCCR1A.sBits.m_WGM11 = GET_BIT(TMR1_MODE_INIT, TMRx_WGMx1_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM12 = GET_BIT(TMR1_MODE_INIT, TMRx_WGMx2_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM13 = GET_BIT(TMR1_MODE_INIT, TMRx_WGMx3_MASK);

	S_TMR1->m_TCCR1A.sBits.m_FOC1A = LBTY_RESET;
	S_TMR1->m_TCCR1A.sBits.m_FOC1B = LBTY_RESET;
	S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_COMPARE_OUTPUT_A_MODE;
	S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_COMPARE_OUTPUT_B_MODE;

	S_TMR1->m_TCCR1B.sBits.m_CS1   = TMR1_CLOCK_SOURCE;
	if(TMR1_CLOCK_SOURCE == TMRx_ExternalClock_FallingEdge || TMR1_CLOCK_SOURCE == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
	S_TMR1->m_TCCR1B.sBits.m_ICES1 = TMR1_INPUT_CAPTURE_EDGE_SELECT;
	S_TMR1->m_TCCR1B.sBits.m_ICNC1 = TMR1_INPUT_CAPTURE_NOISE_CANCELER;

	S_TMR1->m_ICR1.u16Reg  = TMR1_INPUT_CAPTURE_INIT;
	S_TMR1->m_OCR1A.u16Reg = TMR1_OUTPUT_COMPARE_A_INIT;
	S_TMR1->m_OCR1B.u16Reg = TMR1_OUTPUT_COMPARE_B_INIT;
	S_TMR1->m_TCNT1.u16Reg = TMR1_COUNTER_INIT;

	S_TIMSK->sBits.m_TICIE1 = TMR1_INPUT_CAPTURE_INTERRUPT_STATE;
	S_TIMSK->sBits.m_OCIE1A = TMR1_COMPARE_A_MATCH_INTERRUPT_STATE;
	S_TIMSK->sBits.m_OCIE1B = TMR1_COMPARE_B_MATCH_INTERRUPT_STATE;
	S_TIMSK->sBits.m_TOIE1  = TMR1_OVERFLOW_INTERRUPT_STATE;

	S_TIFR->sBits.m_ICF1    = LBTY_RESET;
	S_TIFR->sBits.m_OCF1A   = LBTY_RESET;
	S_TIFR->sBits.m_OCF1B   = LBTY_RESET;
	S_TIFR->sBits.m_TOV1    = LBTY_RESET;
}

void TMR1_vidEnable(void){
	S_TMR1->m_TCCR1B.sBits.m_CS1 = TMR1_CLOCK_SOURCE;
	if(TMR1_CLOCK_SOURCE == TMRx_ExternalClock_FallingEdge || TMR1_CLOCK_SOURCE == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
}

void TMR1_vidDisable(void){
	S_TMR1->m_TCCR1B.sBits.m_CS1 = TMRx_NoClockSource_Disable;
}

static void TMR1_vidSetWaveGenerationMode(TMR1_tenuWaveGenerationMode u8Mode){
	S_TMR1->m_TCCR1A.sBits.m_WGM10 = GET_BIT(u8Mode, TMRx_WGMx0_MASK);
	S_TMR1->m_TCCR1A.sBits.m_WGM11 = GET_BIT(u8Mode, TMRx_WGMx1_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM12 = GET_BIT(u8Mode, TMRx_WGMx2_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM13 = GET_BIT(u8Mode, TMRx_WGMx3_MASK);
}

LBTY_tenuErrorStatus TMR1_u8SetMode(TMR1_tenuWaveGenerationMode u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
			TMR1_vidSetWaveGenerationMode(TMRx_u8_Normal_Mode);
			break;
		case TMR1_PWM_PhaseCorrect_Mode_8bit:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_PhaseCorrect_Mode_8bit);
			break;
		case TMR1_PWM_PhaseCorrect_Mode_9bit:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_PhaseCorrect_Mode_9bit);
			break;
		case TMR1_PWM_PhaseCorrect_Mode_10bit:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_PhaseCorrect_Mode_10bit);
			break;
		case TMR1_CTC_Mode_Mode_ICR1:
			TMR1_vidSetWaveGenerationMode(TMR1_CTC_Mode_Mode_ICR1);
			break;
		case TMR1_PWM_Fase_Mode_8bit:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Fase_Mode_8bit);
			break;
		case TMR1_PWM_Fase_Mode_9bit:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Fase_Mode_9bit);
			break;
		case TMR1_PWM_Fase_Mode_10bit:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Fase_Mode_10bit);
			break;
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Phase_Freq_Correct_Mode_ICR1);
			break;
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A);
			break;
		case TMR1_PWM_Phase_Correct_Mode_ICR1:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Phase_Correct_Mode_ICR1);
			break;
		case TMR1_PWM_Phase_Correct_Mode_ICR1A:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Phase_Correct_Mode_ICR1A);
			break;
		case TMR1_CTC_Mode_Mode_ICR1A:
			TMR1_vidSetWaveGenerationMode(TMR1_CTC_Mode_Mode_ICR1A);
			break;
		case TMR1_PWM_Fase_Mode_ICR1:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Fase_Mode_ICR1);
			break;
		case TMR1_PWM_Fase_Mode_ICR1A:
			TMR1_vidSetWaveGenerationMode(TMR1_PWM_Fase_Mode_ICR1A);
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetOutputModeA(TMR1_tenuCompareOutputMode u8OutMode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	TMR1_tenuWaveGenerationMode u8Mode =
			(S_TMR1->m_TCCR1A.sBits.m_WGM10<<TMRx_WGMx0_MASK) | (S_TMR1->m_TCCR1A.sBits.m_WGM11<<TMRx_WGMx1_MASK) |
			(S_TMR1->m_TCCR1B.sBits.m_WGM12<<TMRx_WGMx2_MASK) | (S_TMR1->m_TCCR1B.sBits.m_WGM13<<TMRx_WGMx3_MASK);

	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
		case TMR1_CTC_Mode_Mode_ICR1:
		case TMR1_CTC_Mode_Mode_ICR1A:
			switch(u8OutMode){
				case TMRx_u8_COM_Toggle_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1A = TMRx_u8_COM_Toggle_on_Match;		break;
				case TMRx_u8_COM_Clear_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1A = TMRx_u8_COM_Clear_on_Match;		break;
				case TMRx_u8_COM_Set_on_Match:		S_TMR1->m_TCCR1A.sBits.m_COM1A = TMRx_u8_COM_Set_on_Match;			break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMR1_PWM_PhaseCorrect_Mode_8bit:
		case TMR1_PWM_PhaseCorrect_Mode_9bit:
		case TMR1_PWM_PhaseCorrect_Mode_10bit:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A:
		case TMR1_PWM_Phase_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Correct_Mode_ICR1A:
			switch(u8OutMode){
				case TMR1_PhasePWM_ToggleA_on_Match_Mode15:S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_PhasePWM_ToggleA_on_Match_Mode15;	break;
				case TMR1_PhasePWM_Clear_on_Match:		   S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_PhasePWM_Clear_on_Match;			break;
				case TMR1_PhasePWM_Set_on_Match:	 	   S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_PhasePWM_Set_on_Match;				break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMR1_PWM_Fase_Mode_8bit:
		case TMR1_PWM_Fase_Mode_9bit:
		case TMR1_PWM_Fase_Mode_10bit:
		case TMR1_PWM_Fase_Mode_ICR1:
		case TMR1_PWM_Fase_Mode_ICR1A:
			switch(u8OutMode){
				case TMR1_FastPWM_ToggleA_on_Match_Mode15:S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_FastPWM_ToggleA_on_Match_Mode15;	break;
				case TMR1_FastPWM_Clear_on_Match:		  S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_FastPWM_Clear_on_Match;				break;
				case TMR1_FastPWM_Set_on_Match:			  S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_FastPWM_Set_on_Match;	  			break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	if(u8RetErrorState == LBTY_OK){
		GPIO_u8SetPinDirection(TMR_OC1A_PORT, TMR_OC1A_PIN, PIN_OUTPUT);
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetOutputModeB(TMR1_tenuCompareOutputMode u8OutMode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	TMR1_tenuWaveGenerationMode u8Mode =
			(S_TMR1->m_TCCR1A.sBits.m_WGM10<<TMRx_WGMx0_MASK) | (S_TMR1->m_TCCR1A.sBits.m_WGM11<<TMRx_WGMx1_MASK) |
			(S_TMR1->m_TCCR1B.sBits.m_WGM12<<TMRx_WGMx2_MASK) | (S_TMR1->m_TCCR1B.sBits.m_WGM13<<TMRx_WGMx3_MASK);

	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
		case TMR1_CTC_Mode_Mode_ICR1:
		case TMR1_CTC_Mode_Mode_ICR1A:
			switch(u8OutMode){
				case TMRx_u8_COM_Toggle_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1B = TMRx_u8_COM_Toggle_on_Match;		break;
				case TMRx_u8_COM_Clear_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1B = TMRx_u8_COM_Clear_on_Match;		break;
				case TMRx_u8_COM_Set_on_Match:		S_TMR1->m_TCCR1A.sBits.m_COM1B = TMRx_u8_COM_Set_on_Match;			break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMR1_PWM_PhaseCorrect_Mode_8bit:
		case TMR1_PWM_PhaseCorrect_Mode_9bit:
		case TMR1_PWM_PhaseCorrect_Mode_10bit:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A:
		case TMR1_PWM_Phase_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Correct_Mode_ICR1A:
			switch(u8OutMode){
				case TMR1_PhasePWM_ToggleA_on_Match_Mode15:S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_PhasePWM_ToggleA_on_Match_Mode15;	break;
				case TMR1_PhasePWM_Clear_on_Match:		   S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_PhasePWM_Clear_on_Match;			break;
				case TMR1_PhasePWM_Set_on_Match:	 	   S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_PhasePWM_Set_on_Match;				break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		case TMR1_PWM_Fase_Mode_8bit:
		case TMR1_PWM_Fase_Mode_9bit:
		case TMR1_PWM_Fase_Mode_10bit:
		case TMR1_PWM_Fase_Mode_ICR1:
		case TMR1_PWM_Fase_Mode_ICR1A:
			switch(u8OutMode){
				case TMR1_FastPWM_ToggleA_on_Match_Mode15:S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_FastPWM_ToggleA_on_Match_Mode15;	break;
				case TMR1_FastPWM_Clear_on_Match:		  S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_FastPWM_Clear_on_Match;				break;
				case TMR1_FastPWM_Set_on_Match:			  S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_FastPWM_Set_on_Match;	  			break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	if(u8RetErrorState == LBTY_OK){
		GPIO_u8SetPinDirection(TMR_OC1B_PORT, TMR_OC1B_PIN, PIN_OUTPUT);
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetInputCapture(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		S_TMR1->m_ICR1.u16Reg = u16Reload;
	}else{
		S_TMR1->m_ICR1.u16Reg = LBTY_u16ZERO;
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetOutputCompare_A(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		S_TMR1->m_OCR1A.u16Reg = u16Reload;
	}else{
		S_TMR1->m_OCR1A.u16Reg = LBTY_u16ZERO;
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u16SetOutputCompare_B(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		S_TMR1->m_OCR1B.u16Reg = u16Reload;
	}else{
		S_TMR1->m_OCR1B.u16Reg = LBTY_u16ZERO;
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u16SetCounter(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		TMR1_u16Reload_GLB = u16Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	S_TMR1->m_TCNT1.u16Reg = TMR1_u16Reload_GLB;
	return u8RetErrorState;
}

void TMR1_vidSetCallBack_CaptureEvent(void (*pCallBack)(void)){
	pFuncCallBack_TMR1_CaptureEven = pCallBack;
}
void TMR1_vidSetCallBack_CompareMatch_A(void (*pCallBack)(void)){
	pFuncCallBack_TMR1_CompareMatch_A = pCallBack;
}
void TMR1_vidSetCallBack_CompareMatch_B(void (*pCallBack)(void)){
	pFuncCallBack_TMR1_CompareMatch_B = pCallBack;
}
void TMR1_vidSetCallBack_OverFlow(void (*pCallBack)(void)){
	pFuncCallBack_TMR1_OverFlow = pCallBack;
}

/*
* 7  	CAPT Timer/Counter1 Capture Event
* 8  	COMPA Timer/Counter1 Compare Match A
* 9  	COMPB Timer/Counter1 Compare Match B
* 10 	OVF Timer/Counter1 Overflow
ISR(TIM1_OVF_vect){
}
ISR(TIM1_COMPB_vect){
}
ISR(TIM1_COMPA_vect){
}
ISR(TIM1_CAPT_vect){
}
*/
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void){
	pFuncCallBack_TMR1_CaptureEven();
	S_TIFR->sBits.m_ICF1    = LBTY_RESET;
}
void __vector_7 (void) __attribute__((signal));
void __vector_7 (void){
	pFuncCallBack_TMR1_CompareMatch_A();
	S_TIFR->sBits.m_OCF1A   = LBTY_RESET;
}
void __vector_8 (void) __attribute__((signal));
void __vector_8 (void){
	pFuncCallBack_TMR1_CompareMatch_B();
	S_TIFR->sBits.m_OCF1B   = LBTY_RESET;
}
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void){
	S_TMR1->m_TCNT1.u16Reg  = TMR1_u16Reload_GLB;
	pFuncCallBack_TMR1_OverFlow();
	S_TIFR->sBits.m_TOV1    = LBTY_RESET;
}

/*************************** E N D (TMR_prg.c) ******************************/
