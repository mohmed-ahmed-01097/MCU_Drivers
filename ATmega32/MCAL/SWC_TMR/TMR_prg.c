/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_prg.c													  */
/* Author      : MAAM														  */
/* Version     : v01.2														  */
/* date        : Apr 3, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

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
const u8 TMRx_RELOAD_DELAY[] = {0, 47, 6, 1, 1, 1, 0, 0};

#if defined(PWM0)
static u8 TMR0_Reload_Delay;
#endif
#if defined(PWM2)
static u8 TMR2_Reload_Delay;
#endif
#if defined(PWM1)
static u8 TMR1_Reload_Delay;
#endif

static void (*pFuncCallBack_TMR0_CompareMatch)(void) = INTP_vidCallBack;
static void (*pFuncCallBack_TMR0_OverFlow)(void) = INTP_vidCallBack;

static void (*pFuncCallBack_TMR2_CompareMatch)(void) = INTP_vidCallBack;
static void (*pFuncCallBack_TMR2_OverFlow)(void) = INTP_vidCallBack;

static void (*pFuncCallBack_TMR1_CaptureEven)(void) = INTP_vidCallBack;
static void (*pFuncCallBack_TMR1_CompareMatch_A)(void) = INTP_vidCallBack;
static void (*pFuncCallBack_TMR1_CompareMatch_B)(void) = INTP_vidCallBack;
static void (*pFuncCallBack_TMR1_OverFlow)(void) = INTP_vidCallBack;

#if defined(TMR0) || defined(PWM0)
static volatile TMR0_tstrConfig strTMR0_Config_GLB = {
#if defined(PWM0)
	.m_TMR_Freq       = PWM0_FREQ_INIT,
	.m_TMR_Duty       = PWM0_DUTY_INIT,
#endif
	.m_TMR_Reload     = TMR0_COUNTER_INIT,
	.m_TMR_Compare    = TMR0_OUTPUT_COMPARE_INIT,
	.m_TMR_Prescalar  = TMR0_CLOCK_SOURCE,
	.m_TMR_Mode       = TMR0_MODE_INIT,
	.m_TMR_OutputMode = TMR0_COMPARE_OUTPUT_MODE,
	.m_TMR_FOC        = LBTY_RESET,
	.m_TMR_OVIE       = TMR0_OVERFLOW_INTERRUPT_INIT_STATE,
	.m_TMR_OCIE       = TMR0_COMPARE_MATCH_INTERRUPT_INIT_STATE
};
#endif
#if defined(TMR2) || defined(PWM2)
static volatile TMR2_tstrConfig strTMR2_Config_GLB = {
#if defined(PWM2)
	.m_TMR_Freq       = PWM2_FREQ_INIT,
	.m_TMR_Duty       = PWM2_DUTY_INIT,
#endif
	.m_TMR_Reload     = TMR2_COUNTER_INIT,
	.m_TMR_Compare    = TMR2_OUTPUT_COMPARE_INIT,
	.m_TMR_Prescalar  = TMR2_CLOCK_SOURCE,
	.m_TMR_Mode       = TMR2_MODE_INIT,
	.m_TMR_OutputMode = TMR2_COMPARE_OUTPUT_MODE,
	.m_TMR_FOC        = LBTY_RESET,
	.m_TMR_OVIE       = TMR2_OVERFLOW_INTERRUPT_INIT_STATE,
	.m_TMR_OCIE       = TMR2_COMPARE_MATCH_INTERRUPT_INIT_STATE,
	.m_TMR_AsyClock   = TMR2_ASYNCHRONOUS_CLOCK
};
#endif
#if defined(TMR1) || defined(PWM1)
static volatile TMR1_tstrConfig strTMR1_Config_GLB ={
#if defined(PWM1)
	.m_TMR_Freq        = PWM1_FREQ_INIT,
	.m_TMR_Duty_A      = PWM1A_DUTY_INIT,
	.m_TMR_Duty_B      = PWM1B_DUTY_INIT,
#endif
	.m_TMR_Reload      = TMR1_COUNTER_INIT,
	.m_TMR_Input       = TMR1_INPUT_CAPTURE_INIT,
	.m_TMR_CompareA    = TMR1_OUTPUT_COMPARE_A_INIT,
	.m_TMR_CompareB    = TMR1_OUTPUT_COMPARE_B_INIT,
	.m_TMR_Prescalar   = TMR1_CLOCK_SOURCE,
	.m_TMR_Mode        = TMR1_MODE_INIT,
	.m_TMR_OutputModeA = TMR1_COMPARE_OUTPUT_A_MODE,
	.m_TMR_OutputModeB = TMR1_COMPARE_OUTPUT_B_MODE,
	.m_TMR_FOCA        = LBTY_RESET,
	.m_TMR_FOCB        = LBTY_RESET,
	.m_TMR_TICIE       = TMR1_INPUT_CAPTURE_INTERRUPT_STATE,
	.m_TMR_OCIEA       = TMR1_COMPARE_A_MATCH_INTERRUPT_STATE,
	.m_TMR_OCIEB       = TMR1_COMPARE_B_MATCH_INTERRUPT_STATE,
	.m_TMR_TOIE        = TMR1_OVERFLOW_INTERRUPT_STATE,
	.m_TMR_InputNoise  = TMR1_INPUT_CAPTURE_NOISE_CANCELER,
	.m_TMR_InputEdge   = TMR1_INPUT_CAPTURE_EDGE_SELECT,
};
#endif

static volatile u16  TMR0_u8CompareNum_GLB  = LBTY_u8ZERO;
static volatile u16  TMR2_u8CompareNum_GLB  = LBTY_u8ZERO;

static volatile u16  TMR0_u8OverflewNum_GLB  = LBTY_u8ZERO;
static volatile u16  TMR2_u8OverflewNum_GLB  = LBTY_u8ZERO;
static volatile u16  TMR1_u8OverflewNum_GLB  = LBTY_u8ZERO;

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
#if defined(PWM0)
	strTMR0_Config_GLB.m_TMR_Freq       = PWM0_FREQ_INIT;
	strTMR0_Config_GLB.m_TMR_Duty       = PWM0_DUTY_INIT;
#endif
	strTMR0_Config_GLB.m_TMR_Reload     = TMR0_COUNTER_INIT;
	strTMR0_Config_GLB.m_TMR_Compare    = TMR0_OUTPUT_COMPARE_INIT;
	strTMR0_Config_GLB.m_TMR_Prescalar  = TMR0_CLOCK_SOURCE;
	strTMR0_Config_GLB.m_TMR_Mode       = TMR0_MODE_INIT;
	strTMR0_Config_GLB.m_TMR_OutputMode = TMR0_COMPARE_OUTPUT_MODE;
	strTMR0_Config_GLB.m_TMR_FOC        = LBTY_RESET;
	strTMR0_Config_GLB.m_TMR_OVIE       = TMR0_OVERFLOW_INTERRUPT_INIT_STATE;
	strTMR0_Config_GLB.m_TMR_OCIE       = TMR0_COMPARE_MATCH_INTERRUPT_INIT_STATE;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strTMR0_Config_GLB;
	}
	TMR0_vidInit();
}

void TMR0_vidInit(void){
	//S_SFIOR->sBits.m_PSR10 = LBTY_SET;

	//TMR0_vidEnable();
	S_TMR0->m_TCCR0.sBits.m_CSx   = strTMR0_Config_GLB.m_TMR_Prescalar;
	if(strTMR0_Config_GLB.m_TMR_Prescalar == TMR0_ExternalClock_FallingEdge ||
	   strTMR0_Config_GLB.m_TMR_Prescalar == TMR0_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
	}
	//TMR0_u8SetMode(TMR0_MODE_INIT);
	S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(strTMR0_Config_GLB.m_TMR_Mode, TMRx_WGMx0_MASK);
	S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(strTMR0_Config_GLB.m_TMR_Mode, TMRx_WGMx1_MASK);
	//TMR0_u8SetOutputMode(TMR0_COMPARE_OUTPUT_MODE);
	S_TMR0->m_TCCR0.sBits.m_COMx  = strTMR0_Config_GLB.m_TMR_OutputMode;
	if(S_TMR0->m_TCCR0.sBits.m_COMx != TMRx_u8_COM_Disconnected)
		GPIO_u8SetPinDirection(TMR_OC0_PORT, TMR_OC0_PIN, PIN_OUTPUT);
	//TMR0_vidResetForceOutputCompare();
	S_TMR0->m_TCCR0.sBits.m_FOCx  = strTMR0_Config_GLB.m_TMR_FOC;

#if defined(TMR0)
	//TMR0_u8SetOutputCompare(TMR0_OUTPUT_COMPARE_INIT);
	S_TMR0->m_OCR0  = strTMR0_Config_GLB.m_TMR_Compare;
	//TMR0_u8SetCounter(TMR0_COUNTER_INIT);
	S_TMR0->m_TCNT0 = strTMR0_Config_GLB.m_TMR_Reload;
#elif defined(PWM0)
	PWM_vidDisable_OC0();
	PWM_u8SetFreq_OC0(strTMR0_Config_GLB.m_TMR_Freq);
	PWM_u8SetDuty_OC0(strTMR0_Config_GLB.m_TMR_Duty);
	TMR0_Reload_Delay = TMRx_RELOAD_DELAY[strTMR0_Config_GLB.m_TMR_Prescalar];
#endif

	S_TIMSK->sBits.m_OCIE0 = strTMR0_Config_GLB.m_TMR_OCIE;
	S_TIMSK->sBits.m_TOIE0 = strTMR0_Config_GLB.m_TMR_OVIE;

	S_TIFR->sBits.m_OCF0   = LBTY_RESET;
	S_TIFR->sBits.m_TOV0   = LBTY_RESET;
}

void TMR0_vidEnable(void){
	S_TMR0->m_TCCR0.sBits.m_CSx = strTMR0_Config_GLB.m_TMR_Prescalar;
	if(strTMR0_Config_GLB.m_TMR_Prescalar == TMR0_ExternalClock_FallingEdge ||
	   strTMR0_Config_GLB.m_TMR_Prescalar == TMR0_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
	}
}
void TMR0_vidDisable(void){
	S_TMR0->m_TCCR0.sBits.m_CSx = TMR0_NoClockSource_Disable;
}

void TMR0_vidSetForceOutputCompare(void){
	S_TMR0->m_TCCR0.sBits.m_FOCx  = strTMR0_Config_GLB.m_TMR_FOC = LBTY_SET;
}

void TMR0_vidResetForceOutputCompare(void){
	S_TMR0->m_TCCR0.sBits.m_FOCx  = strTMR0_Config_GLB.m_TMR_FOC = LBTY_RESET;
}

LBTY_tenuErrorStatus TMR0_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
			S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMRx_u8_Normal_Mode, TMRx_WGMx0_MASK);
			S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMRx_u8_Normal_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_PWM_PhaseCorrect_Mode:
			TMR0_vidResetForceOutputCompare();
			S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMRx_u8_PWM_PhaseCorrect_Mode, TMRx_WGMx0_MASK);
			S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMRx_u8_PWM_PhaseCorrect_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_CTC_Mode_Mode:
			S_TMR0->m_TCCR0.sBits.m_WGMx0 = GET_BIT(TMRx_u8_CTC_Mode_Mode, TMRx_WGMx0_MASK);
			S_TMR0->m_TCCR0.sBits.m_WGMx1 = GET_BIT(TMRx_u8_CTC_Mode_Mode, TMRx_WGMx1_MASK);
			break;
		case TMRx_u8_PWM_Fase_Mode:
			TMR0_vidResetForceOutputCompare();
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
				case TMRx_u8_COM_Disconnected:		S_TMR0->m_TCCR0.sBits.m_COMx = TMRx_u8_COM_Disconnected;			break;
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
		if(u8OutMode != TMRx_u8_COM_Disconnected)
			GPIO_u8SetPinDirection(TMR_OC0_PORT, TMR_OC0_PIN, PIN_OUTPUT);
		strTMR0_Config_GLB.m_TMR_OutputMode = u8OutMode;
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

#if defined(PWM0)
static u16 TMR0_u8GetPrescaler(void){
	u16 u16RetValue;
	switch(strTMR0_Config_GLB.m_TMR_Prescalar){
		case TMR0_NoClockSource_Disable:	u16RetValue = 0;		break;
		case TMR0_Fosc_Prescaler_1:			u16RetValue = 1;		break;
		case TMR0_Fosc_Prescaler_8:			u16RetValue = 8;		break;
		case TMR0_Fosc_Prescaler_64:		u16RetValue = 64;		break;
		case TMR0_Fosc_Prescaler_256:		u16RetValue = 256;		break;
		case TMR0_Fosc_Prescaler_1024:		u16RetValue = 1024;		break;
		default:						u16RetValue = LBTY_u16MAX; 	break;
	}
	return u16RetValue;
}

LBTY_tenuErrorStatus PWM_u8SetFreq_OC0(u32 u32Freq){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR0->m_TCCR0.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR0->m_TCCR0.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
			u16TimerValue = (u16)(TMR_u8MAX - (u32)(F_CPU / ((f32)u32Freq * TMR0_u8GetPrescaler() * 2u)));
			if(u16TimerValue < (u16)((LBTY_u8MAX  - TMRx_RELOAD_DELAY[strTMR0_Config_GLB.m_TMR_Prescalar])))
				u16TimerValue = LBTY_u16ZERO;
			break;
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)(TMR_u8MAX - (u32)(F_CPU / ((f32)u32Freq * TMR0_u8GetPrescaler())));
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR0_u8SetCounter((u8)u16TimerValue);
}

LBTY_tenuErrorStatus PWM_u8SetDuty_OC0(u16 u16Duty){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR0->m_TCCR0.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR0->m_TCCR0.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)((f32)u16Duty / 10000.0 * (TMR_u8MAX - strTMR0_Config_GLB.m_TMR_Reload)) + strTMR0_Config_GLB.m_TMR_Reload - 1;
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR0_u8SetOutputCompare((u8)u16TimerValue);
}

#endif

void TMR0_vidSetCompareNum(u16 u16Num){
	TMR0_u8CompareNum_GLB = u16Num;
}
void TMR0_vidGetCompareNum(u16* pu16Num){
	*pu16Num = TMR0_u8CompareNum_GLB;
}

void TMR0_vidSetOverflowNum(u16 u16Num){
	TMR0_u8OverflewNum_GLB = u16Num;
}
void TMR0_vidGetOverflowNum(u16* pu16Num){
	*pu16Num = TMR0_u8OverflewNum_GLB;
}

void TMR0_vidGetTicks(u32* pu32Tick){
	*pu32Tick = (u32)TMR_u8MAX * TMR0_u8OverflewNum_GLB + S_TMR0->m_TCNT0;
}

/********************************************************************************************************************/

void TMR0_vidCompareMatch_Enable(void){S_TIMSK->sBits.m_OCIE0  = LBTY_SET;}
void TMR0_vidCompareMatch_Disable(void){S_TIMSK->sBits.m_OCIE0 = LBTY_RESET;}

void TMR0_vidSetCompareMatch_Flag(void){S_TIFR->sBits.m_OCF0   = LBTY_SET;}
void TMR0_vidClrCompareMatch_Flag(void){S_TIFR->sBits.m_OCF0   = LBTY_RESET;}

void TMR0_vidOverFlow_Enable(void) {S_TIMSK->sBits.m_TOIE0 = LBTY_SET;}
void TMR0_vidOverFlow_Disable(void){S_TIMSK->sBits.m_TOIE0 = LBTY_RESET;}

void TMR0_vidSetOverFlow_Flag(void){S_TIFR->sBits.m_TOV0   = LBTY_SET;}
void TMR0_vidClrOverFlow_Flag(void){S_TIFR->sBits.m_TOV0   = LBTY_RESET;}

void TMR0_vidSetCallBack_CompareMatch(void (*pCallBack)(void)){
	if(*pCallBack == LBTY_NULL)		return;
	pFuncCallBack_TMR0_CompareMatch = pCallBack;
}
void TMR0_vidSetCallBack_OverFlow(void (*pCallBack)(void)){
	if(*pCallBack == LBTY_NULL)		return;
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
#if defined(TMR_CALLBACK_INT)
ISR(TIMER0_COMP_vect){
	TMR0_u8CompareNum_GLB++;
	pFuncCallBack_TMR0_CompareMatch();
	//TMR0_vidClrCompareMatch_Flag();
}
ISR(TIMER0_OVF_vect){
#if defined(PWM0)
	S_TMR0->m_TCNT0 = strTMR0_Config_GLB.m_TMR_Reload + TMR0_Reload_Delay;
//	if(S_TMR0->m_TCNT0 >= strTMR0_Config_GLB.m_TMR_Compare)
//		TMR0_vidSetCompareMatch_Flag();
#endif
	TMR0_u8OverflewNum_GLB++;
	pFuncCallBack_TMR0_OverFlow();
	//TMR0_vidClrOverFlow_Flag();
}
#endif
/********************************************************************************************************************/

// Timer/Counter Control Register2 Update Busy
LCTY_INLINE  void TMR2_vidControlUpdateBusy(void){while(S_TMR2->m_ASSR.sBits.m_TCR2UB);}

// Output Compare Register2 Update Busy
LCTY_INLINE  void TMR2_vidCompareUpdateBusy(void){while(S_TMR2->m_ASSR.sBits.m_OCR2UB);}

// Timer/Counter2 Update Busy
LCTY_INLINE  void TMR2_vidTimerUpdateBusy(void)  {while(S_TMR2->m_ASSR.sBits.m_TCN2UB);}

void TMR2_vidSetConfig(TMR2_tstrConfig const* const pstrConfig){
	if(pstrConfig != LBTY_NULL){
		strTMR2_Config_GLB = *pstrConfig;
	}
	TMR2_vidInit();
}

void TMR2_vidSRestConfig(TMR2_tstrConfig* const pstrConfig){
#if defined(PWM2)
	strTMR2_Config_GLB.m_TMR_Freq      = PWM2_FREQ_INIT;
	strTMR2_Config_GLB.m_TMR_Duty      = PWM2_DUTY_INIT;
#endif
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

	// TMR2_vidAsync(TMR2_ASYNCHRONOUS_CLOCK);
	S_TIMSK->sBits.m_OCIE2 = LBTY_RESET;
	S_TIMSK->sBits.m_TOIE2 = LBTY_RESET;
	S_TMR2->m_ASSR.sBits.m_AS2 = strTMR2_Config_GLB.m_TMR_AsyClock;

	if(strTMR2_Config_GLB.m_TMR_AsyClock == TMR2_TOSC_Clock){
		GPIO_u8SetPinDirection(TMR_OSC1_PORT, TMR_OSC1_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_OSC2_PORT, TMR_OSC2_PIN, PIN_INPUT);
	}

	//TMR2_vidEnable();
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_CSx   = strTMR2_Config_GLB.m_TMR_Prescalar;
	//TMR2_u8SetMode(TMR2_MODE_INIT);
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_WGMx0 = GET_BIT(strTMR2_Config_GLB.m_TMR_Mode, TMRx_WGMx0_MASK);
	S_TMR2->m_TCCR2.sBits.m_WGMx1 = GET_BIT(strTMR2_Config_GLB.m_TMR_Mode, TMRx_WGMx1_MASK);
	//TMR2_u8SetOutputMode(TMR2_COMPARE_OUTPUT_MODE);
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_COMx  = strTMR2_Config_GLB.m_TMR_OutputMode;
	if(S_TMR2->m_TCCR2.sBits.m_COMx != TMRx_u8_COM_Disconnected)
		GPIO_u8SetPinDirection(TMR_OC2_PORT, TMR_OC2_PIN, PIN_OUTPUT);
	//TMR2_vidSetForceOutputCompare();
	S_TMR2->m_TCCR2.sBits.m_FOCx  = strTMR2_Config_GLB.m_TMR_FOC;

#if defined(TMR2)
	//TMR2_u8SetOutputCompare(TMR2_OUTPUT_COMPARE_INIT);
	TMR2_vidCompareUpdateBusy();
	S_TMR2->m_OCR2 = strTMR2_Config_GLB.m_TMR_Compare;
	//TMR2_u8SetCounter(TMR2_COUNTER_INIT);
	TMR2_vidTimerUpdateBusy();
	S_TMR2->m_TCNT2 = strTMR2_Config_GLB.m_TMR_Reload;
#elif defined(PWM2)
	PWM_vidDisable_OC2();
	PWM_u8SetFreq_OC2(strTMR2_Config_GLB.m_TMR_Freq);
	PWM_u8SetDuty_OC2(strTMR2_Config_GLB.m_TMR_Duty);
	TMR2_Reload_Delay = TMRx_RELOAD_DELAY[strTMR2_Config_GLB.m_TMR_Prescalar];
#endif

	S_TIMSK->sBits.m_OCIE2 = strTMR2_Config_GLB.m_TMR_OCIE;
	S_TIMSK->sBits.m_TOIE2 = strTMR2_Config_GLB.m_TMR_OVIE;

	S_TIFR->sBits.m_OCF2   = LBTY_RESET;
	S_TIFR->sBits.m_TOV2   = LBTY_RESET;
}

void TMR2_vidEnable(void){
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_CSx = strTMR2_Config_GLB.m_TMR_Prescalar;
}

void TMR2_vidDisable(void){
	TMR2_vidControlUpdateBusy();
	S_TMR2->m_TCCR2.sBits.m_CSx = TMR2_NoClockSource_Disable;
}

void TMR2_vidSetForceOutputCompare(void){
	S_TMR2->m_TCCR2.sBits.m_FOCx  = strTMR2_Config_GLB.m_TMR_FOC = LBTY_SET;
}

void TMR2_vidResetForceOutputCompare(void){
	S_TMR2->m_TCCR2.sBits.m_FOCx  = strTMR2_Config_GLB.m_TMR_FOC = LBTY_RESET;
}

LBTY_tenuErrorStatus TMR2_u8Async(TMR2_tenuInputCaptureEdgeSelect u8Async){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;

	switch(u8Async){
		case TMR2_IO_Clock:
		case TMR2_TOSC_Clock:
			S_TIMSK->sBits.m_OCIE2 = LBTY_RESET;
			S_TIMSK->sBits.m_TOIE2 = LBTY_RESET;
			S_TMR2->m_ASSR.sBits.m_AS2 = strTMR2_Config_GLB.m_TMR_AsyClock = u8Async;
			if(u8Async == TMR2_TOSC_Clock){
				GPIO_u8SetPinDirection(TMR_OSC1_PORT, TMR_OSC1_PIN, PIN_INPUT);
				GPIO_u8SetPinDirection(TMR_OSC2_PORT, TMR_OSC2_PIN, PIN_INPUT);
			}
			break;
		default:
			u8RetErrorState = LBTY_WRITE_ERROR;
			break;
	}

	return u8RetErrorState;
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
				case TMRx_u8_COM_Disconnected:		S_TMR2->m_TCCR2.sBits.m_COMx = TMRx_u8_COM_Disconnected;			break;
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
		if(u8OutMode != TMRx_u8_COM_Disconnected)
			GPIO_u8SetPinDirection(TMR_OC2_PORT, TMR_OC2_PIN, PIN_OUTPUT);
		strTMR2_Config_GLB.m_TMR_OutputMode = u8OutMode;
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

#if defined(PWM2)
static u16 TMR2_u8GetPrescaler(void){
	u16 u16RetValue;
	switch(strTMR2_Config_GLB.m_TMR_Prescalar){
		case TMR2_NoClockSource_Disable:	u16RetValue = 0;		break;
		case TMR2_Fosc_Prescaler_1:			u16RetValue = 1;		break;
		case TMR2_Fosc_Prescaler_8:			u16RetValue = 8;		break;
		case TMR2_Fosc_Prescaler_32:		u16RetValue = 32;		break;
		case TMR2_Fosc_Prescaler_64:		u16RetValue = 64;		break;
		case TMR2_Fosc_Prescaler_128:		u16RetValue = 128;		break;
		case TMR2_Fosc_Prescaler_256:		u16RetValue = 256;		break;
		case TMR2_Fosc_Prescaler_1024:		u16RetValue = 1024;		break;
		default:						u16RetValue = LBTY_u16MAX; 	break;
	}
	return u16RetValue;
}

LBTY_tenuErrorStatus PWM_u8SetFreq_OC2(u32 u32Freq){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR2->m_TCCR2.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR2->m_TCCR2.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
			u16TimerValue = (u16)(TMR_u8MAX - (u32)(F_CPU / ((f32)u32Freq * TMR2_u8GetPrescaler() * 2u)));
			if(u16TimerValue < (u16)((LBTY_u8MAX  - TMRx_RELOAD_DELAY[strTMR2_Config_GLB.m_TMR_Prescalar])))
				u16TimerValue = LBTY_u16ZERO;
			break;
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)(TMR_u8MAX - (u32)(F_CPU / ((f32)u32Freq * TMR2_u8GetPrescaler())));
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR2_u8SetCounter((u8)u16TimerValue);
}

LBTY_tenuErrorStatus PWM_u8SetDuty_OC2(u16 u16Duty){
	u16 u16TimerValue = LBTY_u16ZERO;
	TMRx_u8_tenuWaveGenerationMode u8Mode =
			(S_TMR2->m_TCCR2.sBits.m_WGMx0<<TMRx_WGMx0_MASK) | (S_TMR2->m_TCCR2.sBits.m_WGMx1<<TMRx_WGMx1_MASK);
	switch(u8Mode){
		case TMRx_u8_PWM_PhaseCorrect_Mode:
		case TMRx_u8_PWM_Fase_Mode:
			u16TimerValue = (u16)((f32)u16Duty / 10000.0 * (TMR_u8MAX - strTMR2_Config_GLB.m_TMR_Reload)) + strTMR2_Config_GLB.m_TMR_Reload - 1;
			break;
		default:
			break;
	}
	while(u16TimerValue > (u16)LBTY_u8MAX);
	return TMR2_u8SetOutputCompare((u8)u16TimerValue);
}

#endif

void TMR2_vidSetCompareNum(u16 u16Num){
	TMR2_u8CompareNum_GLB = u16Num;
}
void TMR2_vidGetCompareNum(u16* pu16Num){
	*pu16Num = TMR2_u8CompareNum_GLB;
}

void TMR2_vidSetOverflowNum(u16 u16Num){
	TMR2_u8OverflewNum_GLB = u16Num;
}
void TMR2_vidGetOverflowNum(u16* pu16Num){
	*pu16Num = TMR2_u8OverflewNum_GLB;
}

void TMR2_vidGetTicks(u32* pu32Tick){
	*pu32Tick = (u32)TMR_u8MAX * TMR2_u8OverflewNum_GLB + S_TMR2->m_TCNT2;
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
#if defined(TMR_CALLBACK_INT)
ISR(TIMER2_COMP_vect){
	TMR2_u8CompareNum_GLB++;
	pFuncCallBack_TMR2_CompareMatch();
	//TMR2_vidClrCompareMatch_Flag();
}
ISR(TIMER2_OVF_vect){
#if defined(PWM2)
	if(strTMR2_Config_GLB.m_TMR_Reload)
		S_TMR2->m_TCNT2 = strTMR2_Config_GLB.m_TMR_Reload + TMR2_Reload_Delay;
//		if(S_TMR2->m_TCNT2 >= strTMR2_Config_GLB.m_TMR_Compare)
//			TMR2_vidSetCompareMatch_Flag();
#endif
	TMR2_u8OverflewNum_GLB++;
	pFuncCallBack_TMR2_OverFlow();
	//TMR2_vidClrOverFlow_Flag();
}
#endif
/********************************************************************************************************************/

void TMR1_vidSetConfig(TMR1_tstrConfig const* const pstrConfig){
	if(pstrConfig != LBTY_NULL){
		strTMR1_Config_GLB = *pstrConfig;
	}
	TMR1_vidInit();
}

void TMR1_vidSRestConfig(TMR1_tstrConfig* const pstrConfig){
#if defined(PWM1)
	strTMR1_Config_GLB.m_TMR_Freq        = PWM1_FREQ_INIT;
	strTMR1_Config_GLB.m_TMR_Duty_A      = PWM1A_DUTY_INIT;
	strTMR1_Config_GLB.m_TMR_Duty_B      = PWM1B_DUTY_INIT;
#endif
	strTMR1_Config_GLB.m_TMR_Reload      = TMR1_COUNTER_INIT;
	strTMR1_Config_GLB.m_TMR_Input       = TMR1_INPUT_CAPTURE_INIT;
	strTMR1_Config_GLB.m_TMR_CompareA    = TMR1_OUTPUT_COMPARE_A_INIT;
	strTMR1_Config_GLB.m_TMR_CompareB    = TMR1_OUTPUT_COMPARE_B_INIT;
	strTMR1_Config_GLB.m_TMR_Prescalar   = TMR1_CLOCK_SOURCE;
	strTMR1_Config_GLB.m_TMR_Mode        = TMR1_MODE_INIT;
	strTMR1_Config_GLB.m_TMR_OutputModeA = TMR1_COMPARE_OUTPUT_A_MODE;
	strTMR1_Config_GLB.m_TMR_OutputModeB = TMR1_COMPARE_OUTPUT_B_MODE;
	strTMR1_Config_GLB.m_TMR_FOCA        = LBTY_RESET;
	strTMR1_Config_GLB.m_TMR_FOCB        = LBTY_RESET;
	strTMR1_Config_GLB.m_TMR_TICIE       = TMR1_INPUT_CAPTURE_INTERRUPT_STATE;
	strTMR1_Config_GLB.m_TMR_OCIEA       = TMR1_COMPARE_A_MATCH_INTERRUPT_STATE;
	strTMR1_Config_GLB.m_TMR_OCIEB       = TMR1_COMPARE_B_MATCH_INTERRUPT_STATE;
	strTMR1_Config_GLB.m_TMR_TOIE        = TMR1_OVERFLOW_INTERRUPT_STATE;
	strTMR1_Config_GLB.m_TMR_InputNoise  = TMR1_INPUT_CAPTURE_NOISE_CANCELER;
	strTMR1_Config_GLB.m_TMR_InputEdge   = TMR1_INPUT_CAPTURE_EDGE_SELECT;

	if(pstrConfig != LBTY_NULL){
		*pstrConfig = strTMR1_Config_GLB;
	}
	TMR1_vidInit();
}

void TMR1_vidInit(void){

	//S_SFIOR->sBits.m_PSR10 = LBTY_SET;

	// TMR1_u8SetMode(TMR1_MODE_INIT);
	S_TMR1->m_TCCR1A.sBits.m_WGM10 = GET_BIT(strTMR1_Config_GLB.m_TMR_Mode, TMRx_WGMx0_MASK);
	S_TMR1->m_TCCR1A.sBits.m_WGM11 = GET_BIT(strTMR1_Config_GLB.m_TMR_Mode, TMRx_WGMx1_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM12 = GET_BIT(strTMR1_Config_GLB.m_TMR_Mode, TMRx_WGMx2_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM13 = GET_BIT(strTMR1_Config_GLB.m_TMR_Mode, TMRx_WGMx3_MASK);

	// TMR1_u8SetOutputModeA(TMR1_COMPARE_OUTPUT_A_MODE);
	// TMR1_u8SetOutputModeB(TMR1_COMPARE_OUTPUT_B_MODE);
	S_TMR1->m_TCCR1A.sBits.m_FOC1A = strTMR1_Config_GLB.m_TMR_FOCA;
	S_TMR1->m_TCCR1A.sBits.m_FOC1B = strTMR1_Config_GLB.m_TMR_FOCB;
	S_TMR1->m_TCCR1A.sBits.m_COM1A = strTMR1_Config_GLB.m_TMR_OutputModeA;
	S_TMR1->m_TCCR1A.sBits.m_COM1B = strTMR1_Config_GLB.m_TMR_OutputModeB;

	if(strTMR1_Config_GLB.m_TMR_OutputModeA != TMR1_COM_Disconnected)
		GPIO_u8SetPinDirection(TMR_OC1A_PORT, TMR_OC1A_PIN, PIN_OUTPUT);
	if(strTMR1_Config_GLB.m_TMR_OutputModeB != TMR1_COM_Disconnected)
		GPIO_u8SetPinDirection(TMR_OC1B_PORT, TMR_OC1B_PIN, PIN_OUTPUT);

	//TMR1_vidEnable();
	S_TMR1->m_TCCR1B.sBits.m_CS1   = strTMR1_Config_GLB.m_TMR_Prescalar;
	if(strTMR1_Config_GLB.m_TMR_Prescalar == TMR1_ExternalClock_FallingEdge ||
	   strTMR1_Config_GLB.m_TMR_Prescalar == TMR1_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
	//TMR1_vidInitInputCapture();
	S_TMR1->m_TCCR1B.sBits.m_ICNC1 = strTMR1_Config_GLB.m_TMR_InputNoise;
	S_TMR1->m_TCCR1B.sBits.m_ICES1 = strTMR1_Config_GLB.m_TMR_InputEdge;
	if(strTMR1_Config_GLB.m_TMR_InputEdge != TMR1_Capture_Off){
		GPIO_u8SetPinDirection(TMR_ICP1_PORT, TMR_ICP1_PIN, PIN_INPUT);
	}

#if defined(TMR1)
	//TMR1_u8SetInputCapture(TMR1_INPUT_CAPTURE_INIT);
	S_TMR1->m_ICR1.u16Reg  = strTMR1_Config_GLB.m_TMR_Input;
	//TMR1_u8SetOutputCompare_A(TMR1_OUTPUT_COMPARE_A_INIT);
	S_TMR1->m_OCR1A.u16Reg = strTMR1_Config_GLB.m_TMR_CompareA;
	//TMR1_u8SetOutputCompare_B(TMR1_OUTPUT_COMPARE_B_INIT);
	S_TMR1->m_OCR1B.u16Reg = strTMR1_Config_GLB.m_TMR_CompareB;
	//TMR1_u8SetCounter(TMR1_COUNTER_INIT);
	S_TMR1->m_TCNT1.u16Reg = strTMR1_Config_GLB.m_TMR_Reload;
#elif defined(PWM1)
	PWM_vidDisable_OC1x();
	PWM_u8SetFreq_OC1x(strTMR1_Config_GLB.m_TMR_Freq);

	if(strTMR1_Config_GLB.m_TMR_OutputModeA != TMR1_COM_Disconnected)
		PWM_u8SetDuty_OC1A(strTMR1_Config_GLB.m_TMR_Duty_A);
	if(strTMR1_Config_GLB.m_TMR_OutputModeB != TMR1_COM_Disconnected)
		PWM_u8SetDuty_OC1B(strTMR1_Config_GLB.m_TMR_Duty_B);

	TMR1_Reload_Delay = TMRx_RELOAD_DELAY[strTMR1_Config_GLB.m_TMR_Prescalar];
#endif

	S_TIMSK->sBits.m_TICIE1 = strTMR1_Config_GLB.m_TMR_TICIE;
	S_TIMSK->sBits.m_OCIE1A = strTMR1_Config_GLB.m_TMR_OCIEA;
	S_TIMSK->sBits.m_OCIE1B = strTMR1_Config_GLB.m_TMR_OCIEB;
	S_TIMSK->sBits.m_TOIE1  = strTMR1_Config_GLB.m_TMR_TOIE;

	S_TIFR->sBits.m_ICF1    = LBTY_RESET;
	S_TIFR->sBits.m_OCF1A   = LBTY_RESET;
	S_TIFR->sBits.m_OCF1B   = LBTY_RESET;
	S_TIFR->sBits.m_TOV1    = LBTY_RESET;
}

void TMR1_vidEnable(void){
	S_TMR1->m_TCCR1B.sBits.m_CS1 = strTMR1_Config_GLB.m_TMR_Prescalar;
	if(strTMR1_Config_GLB.m_TMR_Prescalar == TMR1_ExternalClock_FallingEdge ||
	   strTMR1_Config_GLB.m_TMR_Prescalar == TMR1_ExternalClock_RisinfEdge){
		GPIO_u8SetPinDirection(TMR_EXT0_PORT, TMR_EXT0_PIN, PIN_INPUT);
		GPIO_u8SetPinDirection(TMR_EXT1_PORT, TMR_EXT1_PIN, PIN_INPUT);
	}
}

void TMR1_vidDisable(void){
	S_TMR1->m_TCCR1B.sBits.m_CS1 = TMR1_NoClockSource_Disable;
}

void TMR1_vidInitInputCapture(void){
	S_TMR1->m_TCCR1B.sBits.m_ICNC1 = strTMR1_Config_GLB.m_TMR_InputNoise;
	S_TMR1->m_TCCR1B.sBits.m_ICES1 = strTMR1_Config_GLB.m_TMR_InputEdge;
	if(strTMR1_Config_GLB.m_TMR_InputEdge != TMR1_Capture_Off){
		GPIO_u8SetPinDirection(TMR_ICP1_PORT, TMR_ICP1_PIN, PIN_INPUT);
	}
}

void TMR1_vidSetForceOutputCompareA(void){
	S_TMR1->m_TCCR1A.sBits.m_FOC1A  = strTMR1_Config_GLB.m_TMR_FOCA = LBTY_SET;
}

void TMR1_vidResetForceOutputCompareA(void){
	S_TMR1->m_TCCR1A.sBits.m_FOC1A  = strTMR1_Config_GLB.m_TMR_FOCA = LBTY_RESET;
}

void TMR1_vidSetForceOutputCompareB(void){
	S_TMR1->m_TCCR1A.sBits.m_FOC1B  = strTMR1_Config_GLB.m_TMR_FOCB = LBTY_SET;
}

void TMR1_vidResetForceOutputCompareB(void){
	S_TMR1->m_TCCR1A.sBits.m_FOC1B  = strTMR1_Config_GLB.m_TMR_FOCB = LBTY_RESET;
}

LCTY_INLINE void TMR1_vidSetWaveGenerationMode(TMR1_tenuWaveGenerationMode u8Mode){
	S_TMR1->m_TCCR1A.sBits.m_WGM10 = GET_BIT(u8Mode, TMRx_WGMx0_MASK);
	S_TMR1->m_TCCR1A.sBits.m_WGM11 = GET_BIT(u8Mode, TMRx_WGMx1_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM12 = GET_BIT(u8Mode, TMRx_WGMx2_MASK);
	S_TMR1->m_TCCR1B.sBits.m_WGM13 = GET_BIT(u8Mode, TMRx_WGMx3_MASK);
	strTMR1_Config_GLB.m_TMR_Mode = u8Mode;
}

LBTY_tenuErrorStatus TMR1_u8SetMode(TMR1_tenuWaveGenerationMode u8Mode){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	switch(u8Mode){
		case TMRx_u8_Normal_Mode:
		case TMR1_PWM_PhaseCorrect_Mode_8bit:
		case TMR1_PWM_PhaseCorrect_Mode_9bit:
		case TMR1_PWM_PhaseCorrect_Mode_10bit:
		case TMR1_CTC_Mode_Mode_ICR1:
		case TMR1_PWM_Fase_Mode_8bit:
		case TMR1_PWM_Fase_Mode_9bit:
		case TMR1_PWM_Fase_Mode_10bit:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A:
		case TMR1_PWM_Phase_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Correct_Mode_ICR1A:
		case TMR1_CTC_Mode_Mode_ICR1A:
		case TMR1_PWM_Fase_Mode_ICR1:
		case TMR1_PWM_Fase_Mode_ICR1A:
			TMR1_vidSetWaveGenerationMode(u8Mode);
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
				case TMR1_COM_Disconnected:		S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_COM_Disconnected;			break;
				case TMR1_COM_Toggle_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_COM_Toggle_on_Match;		break;
				case TMR1_COM_Clear_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_COM_Clear_on_Match;		break;
				case TMR1_COM_Set_on_Match:		S_TMR1->m_TCCR1A.sBits.m_COM1A = TMR1_COM_Set_on_Match;			break;
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
		if(u8OutMode != TMR1_COM_Disconnected)
			GPIO_u8SetPinDirection(TMR_OC1A_PORT, TMR_OC1A_PIN, PIN_OUTPUT);
		strTMR1_Config_GLB.m_TMR_OutputModeA = u8OutMode;
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
				case TMR1_COM_Disconnected:		S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_COM_Disconnected;			break;
				case TMR1_COM_Toggle_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_COM_Toggle_on_Match;		break;
				case TMR1_COM_Clear_on_Match:	S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_COM_Clear_on_Match;		break;
				case TMR1_COM_Set_on_Match:		S_TMR1->m_TCCR1A.sBits.m_COM1B = TMR1_COM_Set_on_Match;			break;
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
		if(u8OutMode != TMR1_COM_Disconnected)
			GPIO_u8SetPinDirection(TMR_OC1B_PORT, TMR_OC1B_PIN, PIN_OUTPUT);
		strTMR1_Config_GLB.m_TMR_OutputModeB = u8OutMode;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetInputCapture(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		S_TMR1->m_ICR1.u16Reg = strTMR1_Config_GLB.m_TMR_Input = u16Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetOutputCompare_A(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		S_TMR1->m_OCR1A.u16Reg = strTMR1_Config_GLB.m_TMR_CompareA = u16Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetOutputCompare_B(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		S_TMR1->m_OCR1B.u16Reg = strTMR1_Config_GLB.m_TMR_CompareB = u16Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8SetCounter(u16 u16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(u16Reload <= LBTY_u16MAX){
		S_TMR1->m_TCNT1.u16Reg = strTMR1_Config_GLB.m_TMR_Reload = u16Reload;
	}else{
		u8RetErrorState = LBTY_WRITE_ERROR;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8GetInputCapture(u16* pu16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu16Reload != LBTY_NULL){
		*pu16Reload = S_TMR1->m_ICR1.u16Reg;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8GetOutputCompare_A(u16* pu16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu16Reload != LBTY_NULL){
		*pu16Reload = S_TMR1->m_OCR1A.u16Reg;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8GetOutputCompare_B(u16* pu16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu16Reload != LBTY_NULL){
		*pu16Reload = S_TMR1->m_OCR1B.u16Reg;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus TMR1_u8GetCounter(u16* pu16Reload){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	if(pu16Reload != LBTY_NULL){
		*pu16Reload = S_TMR1->m_TCNT1.u16Reg;
	}else{
		u8RetErrorState = LBTY_NULL_POINTER;
	}
	return u8RetErrorState;
}

#if defined(PWM1)
static u16 TMR1_u8GetPrescaler(void){
	u16 u16RetValue;
	switch(strTMR1_Config_GLB.m_TMR_Prescalar){
		case TMR1_NoClockSource_Disable:	u16RetValue = 0;		break;
		case TMR1_Fosc_Prescaler_1:			u16RetValue = 1;		break;
		case TMR1_Fosc_Prescaler_8:			u16RetValue = 8;		break;
		case TMR1_Fosc_Prescaler_64:		u16RetValue = 64;		break;
		case TMR1_Fosc_Prescaler_256:		u16RetValue = 256;		break;
		case TMR1_Fosc_Prescaler_1024:		u16RetValue = 1024;		break;
		default:						u16RetValue = LBTY_u16MAX; 	break;
	}
	return u16RetValue;
}

LBTY_tenuErrorStatus PWM_u8SetFreq_OC1x(u32 u32Freq){
	LBTY_tenuErrorStatus u8RetErrorState = LBTY_OK;
	u16 u16TmrTop;
	u32 u32TimerValue = LBTY_u32ZERO;
	TMR1_tenuWaveGenerationMode u8Mode =
				(S_TMR1->m_TCCR1A.sBits.m_WGM10<<TMRx_WGMx0_MASK) | (S_TMR1->m_TCCR1A.sBits.m_WGM11<<TMRx_WGMx1_MASK) |
				(S_TMR1->m_TCCR1B.sBits.m_WGM12<<TMRx_WGMx2_MASK) | (S_TMR1->m_TCCR1B.sBits.m_WGM13<<TMRx_WGMx3_MASK);
	switch(u8Mode){
		case TMR1_PWM_PhaseCorrect_Mode_8bit:
		case TMR1_PWM_PhaseCorrect_Mode_9bit:
		case TMR1_PWM_PhaseCorrect_Mode_10bit:
			if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_8bit)		u16TmrTop = TMR_u8MAX;
			else if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_9bit) 	u16TmrTop = TMR_u9MAX;
			else if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_10bit)	u16TmrTop = TMR_u10MAX;
			u32TimerValue = (u32)(u16TmrTop - (u32)(F_CPU / ((f32)u32Freq * TMR1_u8GetPrescaler() * 2u)));
			if(u32TimerValue < (u16)((u16TmrTop  - TMRx_RELOAD_DELAY[strTMR1_Config_GLB.m_TMR_Prescalar])))
				u32TimerValue = LBTY_u16ZERO;
			u8RetErrorState = TMR1_u8SetCounter((u16)u32TimerValue);
			break;
		case TMR1_PWM_Phase_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1:
			u32TimerValue = (u32)((u32)(F_CPU / ((f32)u32Freq * TMR1_u8GetPrescaler() * 2u))) - 1u;
			u8RetErrorState = TMR1_u8SetInputCapture((u16)u32TimerValue);
			break;
		case TMR1_PWM_Phase_Correct_Mode_ICR1A:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A:
			u32TimerValue = (u32)((u32)(F_CPU / ((f32)u32Freq * TMR1_u8GetPrescaler() * 2u))) - 1u;
			u8RetErrorState = TMR1_u8SetOutputCompare_A((u16)u32TimerValue);
			break;

		case TMR1_PWM_Fase_Mode_8bit:
		case TMR1_PWM_Fase_Mode_9bit:
		case TMR1_PWM_Fase_Mode_10bit:
			if(u8Mode == TMR1_PWM_Fase_Mode_8bit)		u16TmrTop = TMR_u8MAX;
			else if(u8Mode == TMR1_PWM_Fase_Mode_9bit) 	u16TmrTop = TMR_u9MAX;
			else if(u8Mode == TMR1_PWM_Fase_Mode_10bit)	u16TmrTop = TMR_u10MAX;
			u32TimerValue = (u32)(u16TmrTop - (u32)(F_CPU / ((f32)u32Freq * TMR1_u8GetPrescaler())));
			u8RetErrorState = TMR1_u8SetCounter((u16)u32TimerValue);
			break;
		case TMR1_PWM_Fase_Mode_ICR1:
			u32TimerValue = (u32)((u32)(F_CPU / ((f32)u32Freq * TMR1_u8GetPrescaler()))) - 1u;
			u8RetErrorState = TMR1_u8SetInputCapture((u16)u32TimerValue);
			break;
		case TMR1_PWM_Fase_Mode_ICR1A:
			u32TimerValue = (u32)((u32)(F_CPU / ((f32)u32Freq * TMR1_u8GetPrescaler()))) - 1u;
			u8RetErrorState = TMR1_u8SetOutputCompare_A((u16)u32TimerValue);
			break;

		default:
			break;
	}
	return u8RetErrorState;
}

LBTY_tenuErrorStatus PWM_u8SetDuty_OC1A(u16 u16Duty){
	u32 u32TimerValue = LBTY_u32ZERO;
	u16 u16TmrTop = LBTY_u8ZERO;
	TMR1_tenuWaveGenerationMode u8Mode =
				(S_TMR1->m_TCCR1A.sBits.m_WGM10<<TMRx_WGMx0_MASK) | (S_TMR1->m_TCCR1A.sBits.m_WGM11<<TMRx_WGMx1_MASK) |
				(S_TMR1->m_TCCR1B.sBits.m_WGM12<<TMRx_WGMx2_MASK) | (S_TMR1->m_TCCR1B.sBits.m_WGM13<<TMRx_WGMx3_MASK);

	switch(u8Mode){
		case TMR1_PWM_PhaseCorrect_Mode_8bit:
		case TMR1_PWM_PhaseCorrect_Mode_9bit:
		case TMR1_PWM_PhaseCorrect_Mode_10bit:
		case TMR1_PWM_Fase_Mode_8bit:
		case TMR1_PWM_Fase_Mode_9bit:
		case TMR1_PWM_Fase_Mode_10bit:
			if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_8bit || u8Mode == TMR1_PWM_Fase_Mode_8bit) 			u16TmrTop = TMR_u8MAX;
			else if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_9bit || u8Mode == TMR1_PWM_Fase_Mode_9bit) 	u16TmrTop = TMR_u9MAX;
			else if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_10bit || u8Mode == TMR1_PWM_Fase_Mode_10bit)	u16TmrTop = TMR_u10MAX;
			u32TimerValue = (u32)((f32)u16Duty / 10000.0 * (u16TmrTop - strTMR1_Config_GLB.m_TMR_Reload)) +  strTMR1_Config_GLB.m_TMR_Reload - 1;
			if(u32TimerValue >= (u32)u16TmrTop)						u32TimerValue = LBTY_u32ZERO;
			break;
		case TMR1_PWM_Fase_Mode_ICR1:
		case TMR1_PWM_Phase_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1:
			u32TimerValue = (u32)((f32)u16Duty / 10000.0 * S_TMR1->m_ICR1.u16Reg) - 1;
			if(u32TimerValue >= (u32)S_TMR1->m_ICR1.u16Reg)			u32TimerValue = LBTY_u32ZERO;
			break;
		case TMR1_PWM_Fase_Mode_ICR1A:
		case TMR1_PWM_Phase_Correct_Mode_ICR1A:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A:
			while(1);
			break;
		default:
			break;
	}
	return TMR1_u8SetOutputCompare_A((u16)u32TimerValue);
}

LBTY_tenuErrorStatus PWM_u8SetDuty_OC1B(u16 u16Duty){
	u32 u32TimerValue = LBTY_u32ZERO;
	u16 u16TmrTop = LBTY_u8ZERO;
	TMR1_tenuWaveGenerationMode u8Mode =
				(S_TMR1->m_TCCR1A.sBits.m_WGM10<<TMRx_WGMx0_MASK) | (S_TMR1->m_TCCR1A.sBits.m_WGM11<<TMRx_WGMx1_MASK) |
				(S_TMR1->m_TCCR1B.sBits.m_WGM12<<TMRx_WGMx2_MASK) | (S_TMR1->m_TCCR1B.sBits.m_WGM13<<TMRx_WGMx3_MASK);

	switch(u8Mode){
		case TMR1_PWM_PhaseCorrect_Mode_8bit:
		case TMR1_PWM_PhaseCorrect_Mode_9bit:
		case TMR1_PWM_PhaseCorrect_Mode_10bit:
		case TMR1_PWM_Fase_Mode_8bit:
		case TMR1_PWM_Fase_Mode_9bit:
		case TMR1_PWM_Fase_Mode_10bit:
			if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_8bit || u8Mode == TMR1_PWM_Fase_Mode_8bit) 			u16TmrTop = TMR_u8MAX;
			else if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_9bit || u8Mode == TMR1_PWM_Fase_Mode_9bit) 	u16TmrTop = TMR_u9MAX;
			else if(u8Mode == TMR1_PWM_PhaseCorrect_Mode_10bit || u8Mode == TMR1_PWM_Fase_Mode_10bit)	u16TmrTop = TMR_u10MAX;
			u32TimerValue = (u32)((f32)u16Duty / 10000.0 * (u16TmrTop - strTMR1_Config_GLB.m_TMR_Reload)) +  strTMR1_Config_GLB.m_TMR_Reload - 1;
			if(u32TimerValue >= (u32)u16TmrTop)							u32TimerValue = LBTY_u32ZERO;
			break;
		case TMR1_PWM_Fase_Mode_ICR1:
		case TMR1_PWM_Phase_Correct_Mode_ICR1:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1:
			u32TimerValue = (u32)((f32)u16Duty / 10000.0 * S_TMR1->m_ICR1.u16Reg) - 1;
			if(u32TimerValue >= (u32)S_TMR1->m_ICR1.u16Reg)				u32TimerValue = LBTY_u32ZERO;
			break;
		case TMR1_PWM_Fase_Mode_ICR1A:
		case TMR1_PWM_Phase_Correct_Mode_ICR1A:
		case TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A:
			u32TimerValue = (u32)((f32)u16Duty / 10000.0 * S_TMR1->m_OCR1A.u16Reg) - 1;
			if(u32TimerValue >= (u32)S_TMR1->m_OCR1A.u16Reg)			u32TimerValue = LBTY_u32ZERO;
			break;
		default:
			break;
	}
	return TMR1_u8SetOutputCompare_B((u16)u32TimerValue);
}
#endif

void TMR1_vidSetOverflowNum(u16 u16Num){
	TMR1_u8OverflewNum_GLB = u16Num;
}
void TMR1_vidGetOverflowNum(u16* pu16Num){
	*pu16Num = TMR1_u8OverflewNum_GLB;
}

void TMR1_vidGetTicks(u32* pu32Tick){
	*pu32Tick = (u32)TMR_u16MAX * TMR1_u8OverflewNum_GLB + S_TMR1->m_TCNT1.u16Reg;
}

/********************************************************************************************************************/

void TMR1_vidInputCapture_Enable(void) {S_TIMSK->sBits.m_TICIE1 = LBTY_SET;}
void TMR1_vidInputCapture_Disable(void){S_TIMSK->sBits.m_TICIE1 = LBTY_RESET;}

void TMR1_vidSetInputCapture_Flag(void){S_TIFR->sBits.m_ICF1   = LBTY_SET;}
void TMR1_vidClrInputCapture_Flag(void){S_TIFR->sBits.m_ICF1   = LBTY_RESET;}

void TMR1_vidCompareMatch_A_Enable(void) {S_TIMSK->sBits.m_OCIE1A = LBTY_SET;}
void TMR1_vidCompareMatch_A_Disable(void){S_TIMSK->sBits.m_OCIE1A = LBTY_RESET;}

void TMR1_vidSetCompareMatch_A_Flag(void){S_TIFR->sBits.m_OCF1A   = LBTY_SET;}
void TMR1_vidClrCompareMatch_A_Flag(void){S_TIFR->sBits.m_OCF1A   = LBTY_RESET;}

void TMR1_vidCompareMatch_B_Enable(void) {S_TIMSK->sBits.m_OCIE1B = LBTY_SET;}
void TMR1_vidCompareMatch_B_Disable(void){S_TIMSK->sBits.m_OCIE1B = LBTY_RESET;}

void TMR1_vidSetCompareMatch_B_Flag(void){S_TIFR->sBits.m_OCF1B   = LBTY_SET;}
void TMR1_vidClrCompareMatch_B_Flag(void){S_TIFR->sBits.m_OCF1B   = LBTY_RESET;}

void TMR1_vidOverFlow_Enable(void) {S_TIMSK->sBits.m_TOIE1 = LBTY_SET;}
void TMR1_vidOverFlow_Disable(void){S_TIMSK->sBits.m_TOIE1 = LBTY_RESET;}

void TMR1_vidSetOverFlow_Flag(void){S_TIFR->sBits.m_TOV1   = LBTY_SET;}
void TMR1_vidClrOverFlow_Flag(void){S_TIFR->sBits.m_TOV1   = LBTY_RESET;}

void TMR1_vidSetCallBack_CaptureEvent(void (*pCallBack)(void)){
	if(*pCallBack == LBTY_NULL)		return;
	pFuncCallBack_TMR1_CaptureEven = pCallBack;
}
void TMR1_vidSetCallBack_CompareMatch_A(void (*pCallBack)(void)){
	if(*pCallBack == LBTY_NULL)		return;
	pFuncCallBack_TMR1_CompareMatch_A = pCallBack;
}
void TMR1_vidSetCallBack_CompareMatch_B(void (*pCallBack)(void)){
	if(*pCallBack == LBTY_NULL)		return;
	pFuncCallBack_TMR1_CompareMatch_B = pCallBack;
}
void TMR1_vidSetCallBack_OverFlow(void (*pCallBack)(void)){
	if(*pCallBack == LBTY_NULL)		return;
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
#if defined(TMR_CALLBACK_INT)
ISR(TIMER1_CAPT_vect){
	pFuncCallBack_TMR1_CaptureEven();
	//TMR1_vidClrInputCapture_Flag();
}
ISR(TIMER1_COMPA_vect){
	pFuncCallBack_TMR1_CompareMatch_A();
	//TMR1_vidClrCompareMatch_A_Flag();
}
ISR(TIMER1_COMPB_vect){
	pFuncCallBack_TMR1_CompareMatch_B();
	//TMR1_vidClrCompareMatch_B_Flag();
}
ISR(TIMER1_OVF_vect){
#if defined(PWM1)
	S_TMR1->m_TCNT1.u16Reg  = strTMR1_Config_GLB.m_TMR_Reload + TMR1_Reload_Delay;
#endif
	TMR1_u8OverflewNum_GLB++;
	pFuncCallBack_TMR1_OverFlow();
	//TMR1_vidClrOverFlow_Flag();
}
#endif
/*************************** E N D (TMR_prg.c) ******************************/
