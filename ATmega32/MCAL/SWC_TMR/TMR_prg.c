/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_prg.c												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */
#include "ATMega32.h"

#include "LBTY_int.h"
#include "LBIT_int.h"

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

static volatile u8  TMR0_u8Reload_GLB  = TMR0_COUNTER_INIT;
static volatile u8  TMR2_u8Reload_GLB  = TMR2_COUNTER_INIT;
static volatile u16 TMR1_u16Reload_GLB = TMR1_COUNTER_INIT;

/* ************************************************************************** */
/* **************************** FUNCTION SECTION **************************** */
/* ************************************************************************** */

void TMR0_vidInit(void){
	//S_SFIOR->sBits.m_PSR10 = LBTY_SET;
#if TMR0
	S_TMR0->m_TCCR0.sBits.m_CSx   = TMR0_CLOCK_SOURCE;
	if(TMR0_CLOCK_SOURCE == TMRx_ExternalClock_FallingEdge || TMR0_CLOCK_SOURCE == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
	S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMR0_MODE_INIT, TMRx_WGMx0_MASK);
	S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMR0_MODE_INIT, TMRx_WGMx1_MASK);
	S_TMR0->m_TCCR0.sBits.m_COMx  = TMR0_COMPARE_OUTPUT_MODE;
	S_TMR0->m_TCCR0.sBits.m_FOCx  = LBTY_RESET;

	S_TMR0->m_OCR0 = TMR0_OUTPUT_COMPARE_INIT;
	S_TMR0->m_TCNT0 = TMR0_COUNTER_INIT;
#elif PWM0
	TMR0_vidEnable();
	TMR0_u8SetMode(TMR0_MODE_INIT);
	TMR0_u8SetOutputMode(TMR0_COMPARE_OUTPUT_MODE);

	PWM_u8SetFreq_OC0(PWM0_FREQ_INIT);
	PWM_u8SetDuty_OC0(PWM0_DUTY_INIT);
	PWM_vidDisable_OC0();
#endif

	S_TIMSK->sBits.m_OCIE0 = TMR0_COMPARE_MATCH_INTERRUPT_INIT_STATE;
	S_TIMSK->sBits.m_TOIE0 = TMR0_OVERFLOW_INTERRUPT_INIT_STATE;

	S_TIFR->sBits.m_OCF0   = LBTY_RESET;
	S_TIFR->sBits.m_TOV0   = LBTY_RESET;
}

void TMR0_vidEnable(void){
	S_TMR0->m_TCCR0.sBits.m_CSx = TMR0_CLOCK_SOURCE;
	if(TMR0_CLOCK_SOURCE == TMRx_ExternalClock_FallingEdge || TMR0_CLOCK_SOURCE == TMRx_ExternalClock_RisinfEdge){
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
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR0_u8SetOutputCompare(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		S_TMR0->m_OCR0 = u8Reload;
	}else{
		S_TMR0->m_OCR0 = LBTY_u8ZERO;
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR0_u8SetCounter(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		TMR0_u8Reload_GLB = u8Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	S_TMR0->m_TCNT0 = TMR0_u8Reload_GLB;
	return u8RetErrorState;
}

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
//		u16TimerValue = (u16)(LBTY_u8MAX - (u32)(F_CPU / ((f32)u16Freq * TMR0_u8GetPrescaler())));
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
	return TMR0_u8SetOutputCompare((u8)((f32)u8Duty / 100.0 * (LBTY_u8MAX - TMR0_u8Reload_GLB)) +  TMR0_u8Reload_GLB);
}

#endif


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
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){
	pFuncCallBack_TMR0_CompareMatch();
	TMR0_vidClrCompareMatch_Flag();
}
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void){
	S_TMR0->m_TCNT0 = TMR0_u8Reload_GLB;
	pFuncCallBack_TMR0_OverFlow();
	TMR0_vidClrOverFlow_Flag();
}

/********************************************************************************************************************/

void TMR2_vidInit(void){
	//S_SFIOR->sBits.m_PSR2 = LBTY_SET;

	// Asynchronous Timer/Counter2
	S_TMR2->m_ASSR.sBits.m_AS2 = TMR2_ASYNCHRONOUS_CLOCK;

	if(TMR2_ASYNCHRONOUS_CLOCK == TMR2_TOSC_Clock){
		GPIO_u8SetPinDirection(TMR_OSC1_PORT, TMR_OSC1_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_OSC2_PORT, TMR_OSC2_PIN, PIN_INPUT);
	}

#if TMR2
	// Timer/Counter Control Register2 Update Busy
	while(S_TMR2->m_ASSR.sBits.m_TCR2UB);
	S_TMR2->m_TCCR2.sBits.m_CSx   = TMR2_CLOCK_SOURCE;
	if(TMR2_CLOCK_SOURCE == TMRx_ExternalClock_FallingEdge || TMR2_CLOCK_SOURCE == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
	S_TMR2->m_TCCR2.sBits.m_WGMx0 = GET_BIT(TMR2_MODE_INIT, TMRx_WGMx0_MASK);
	S_TMR2->m_TCCR2.sBits.m_WGMx1 = GET_BIT(TMR2_MODE_INIT, TMRx_WGMx1_MASK);
	S_TMR2->m_TCCR2.sBits.m_COMx  = TMR2_COMPARE_OUTPUT_MODE;
	S_TMR2->m_TCCR2.sBits.m_FOCx  = LBTY_RESET;

	// Output Compare Register2 Update Busy
	while(S_TMR2->m_ASSR.sBits.m_OCR2UB);
	S_TMR2->m_OCR2 = TMR2_OUTPUT_COMPARE_INIT;

	// Timer/Counter2 Update Busy
	while(S_TMR2->m_ASSR.sBits.m_TCN2UB);
	S_TMR2->m_TCNT2 = TMR2_COUNTER_INIT;
#elif PWM2
	TMR2_vidEnable();
	TMR2_u8SetMode(TMR2_MODE_INIT);
	TMR2_u8SetOutputMode(TMR2_COMPARE_OUTPUT_MODE);

	PWM_u8SetFreq_OC2(PWM2_FREQ_INIT);
	PWM_u8SetDuty_OC2(PWM2_DUTY_INIT);
	PWM_vidDisable_OC2();
#endif

	S_TIMSK->sBits.m_OCIE2 = TMR2_COMPARE_MATCH_INTERRUPT_INIT_STATE;
	S_TIMSK->sBits.m_TOIE2 = TMR2_OVERFLOW_INTERRUPT_INIT_STATE;

	S_TIFR->sBits.m_OCF2   = LBTY_RESET;
	S_TIFR->sBits.m_TOV2   = LBTY_RESET;
}

void TMR2_vidEnable(void){
	S_TMR2->m_TCCR2.sBits.m_CSx = TMR2_CLOCK_SOURCE;
	if(TMR2_CLOCK_SOURCE == TMRx_ExternalClock_FallingEdge || TMR2_CLOCK_SOURCE == TMRx_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
}

void TMR2_vidDisable(void){
	S_TMR2->m_TCCR2.sBits.m_CSx = TMRx_NoClockSource_Disable;
}

LBTY_tenuErrorStatus TMR2_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
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
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR2->m_TCCR2.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR2->m_TCCR2.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
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
				case TMRx_u8_FastPWM_Clear_on_Match:S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_FastPWM_Clear_on_Match;	break;
					break;
				case TMRx_u8_FastPWM_Set_on_Match:	S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_FastPWM_Set_on_Match;		break;			break;
				default:	u8RetErrorState = LBTY_WRITE_ERROR;		break;
			}
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}
	if(u8RetErrorState == LBTY_OK){
		GPIO_u8SetPinDirection(TMR_OC2_PORT, TMR_OC2_PIN, PIN_OUTPUT);
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8SetOutputCompare(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		// Output Compare Register2 Update Busy
		while(S_TMR2->m_ASSR.sBits.m_OCR2UB);
		S_TMR2->m_OCR2 = u8Reload;
	}else{
		S_TMR2->m_OCR2 = LBTY_u8ZERO;
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR2_u8SetCounter(u8 u8Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u8Reload <= LBTY_u8MAX){
		TMR2_u8Reload_GLB = u8Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	// Timer/Counter2 Update Busy
	while(S_TMR2->m_ASSR.sBits.m_TCN2UB);
	S_TMR2->m_TCNT2 = TMR2_u8Reload_GLB;
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
//		u16TimerValue = (u16)(LBTY_u8MAX - (u32)(F_CPU / ((f32)u16Freq * TMR2_u8GetPrescaler())));
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
	return TMR2_u8SetOutputCompare((u8)((f32)u8Duty / 100.0 * (LBTY_u8MAX - TMR2_u8Reload_GLB)));
}

#endif

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
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void){
	pFuncCallBack_TMR2_CompareMatch();
	TMR2_vidClrCompareMatch_Flag();
}
void __vector_5 (void) __attribute__((signal));
void __vector_5 (void){
	S_TMR2->m_TCNT2 = TMR2_u8Reload_GLB;
	pFuncCallBack_TMR2_OverFlow();
	TMR2_vidClrOverFlow_Flag();
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
