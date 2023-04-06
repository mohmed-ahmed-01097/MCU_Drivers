/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_int.h												  */
/* Author      : MAAM														  */
/* Version     : v00														  */
/* date        : Apr 5, 2023												  */
/* ************************************************************************** */
/* ************************ HEADER FILES INCLUDES **************************  */
/* ************************************************************************** */

#ifndef TMR_INT_H_
#define TMR_INT_H_

/* ************************************************************************** */
/* ********************** TYPE_DEF/STRUCT/ENUM SECTION ********************** */
/* ************************************************************************** */

typedef enum{
	TMRx_NoClockSource_Disable = (u8)0u,
	TMRx_Fosc_Prescaler_1,
	TMRx_Fosc_Prescaler_8,
	TMRx_Fosc_Prescaler_64,
	TMRx_Fosc_Prescaler_256,
	TMRx_Fosc_Prescaler_1024,
	TMRx_ExternalClock_FallingEdge,
	TMRx_ExternalClock_RisinfEdge
}TMRx_tenuClockSource;

typedef enum{
	TMRx_u8_Normal_Mode = (u8)0u,
	TMRx_u8_PWM_PhaseCorrect_Mode,
	TMRx_u8_CTC_Mode_Mode,			//Clear Timer on Compare Match
	TMRx_u8_PWM_Fase_Mode
}TMRx_u8_tenuWaveGenerationMode;

typedef enum{
	TMR1_Normal_Mode = (u8)0u,
	TMR1_PWM_PhaseCorrect_Mode_8bit,
	TMR1_PWM_PhaseCorrect_Mode_9bit,
	TMR1_PWM_PhaseCorrect_Mode_10bit,
	TMR1_CTC_Mode_Mode_ICR1,			//Clear Timer on Compare Match
	TMR1_PWM_Fase_Mode_8bit,
	TMR1_PWM_Fase_Mode_9bit,
	TMR1_PWM_Fase_Mode_10bit,
	TMR1_PWM_Phase_Freq_Correct_Mode_ICR1,
	TMR1_PWM_Phase_Freq_Correct_Mode_ICR1A,
	TMR1_PWM_Phase_Correct_Mode_ICR1,
	TMR1_PWM_Phase_Correct_Mode_ICR1A,
	TMR1_CTC_Mode_Mode_ICR1A,			//Clear Timer on Compare Match
	TMR1_Reserved,
	TMR1_PWM_Fase_Mode_ICR1,
	TMR1_PWM_Fase_Mode_ICR1A,
}TMR1_tenuWaveGenerationMode;

typedef enum{
	// Non PWM Mode
	TMRx_u8_COM_Disconnected = (u8)0u,
	TMRx_u8_COM_Toggle_on_Match,
	TMRx_u8_COM_Clear_on_Match,
	TMRx_u8_COM_Set_on_Match,

	// Fast PWM Mode
	TMRx_u8_FastPWM_Clear_on_Match = (u8)2u,	// Non Inverting Mode
	TMRx_u8_FastPWM_Set_on_Match,				// Inverting Mode

	// Phase PWM Mode
	TMRx_u8_PhasePWM_Clear_on_Match = (u8)2u,	// Low Pulse
	TMRx_u8_PhasePWM_Set_on_Match,				// High Pulse

}TMRx_u8_tenuCompareOutputMode;

typedef enum{
	TMR2_IO_Clock = (u8)0u,
	TMR2_TOSC_Clock
}TMR2_tenuInputCaptureEdgeSelect;

typedef enum{
	// Non PWM Mode
	TMR1_COM_Disconnected = (u8)0u,
	TMR1_COM_Toggle_on_Match,
	TMR1_COM_Clear_on_Match,
	TMR1_COM_Set_on_Match,

	// Fast PWM Mode
	TMR1_FastPWM_ToggleA_on_Match_Mode15 = (u8)1u,
	TMR1_FastPWM_Clear_on_Match = (u8)2u,	// Non Inverting Mode
	TMR1_FastPWM_Set_on_Match,				// Inverting Mode

	// Phase PWM Mode
	TMR1_PhasePWM_ToggleA_on_Match_Mode15 = (u8)1u,
	TMR1_PhasePWM_Clear_on_Match = (u8)2u,	// Low Pulse
	TMR1_PhasePWM_Set_on_Match,				// High Pulse

}TMR1_tenuCompareOutputMode;

typedef enum{
	TMR1_Capture_Falling_Edge = (u8)0u,
	TMR1_Capture_Rising_Edge
}TMR1_tenuInputCaptureEdgeSelect;

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

void TMR0_vidInit(void);

void TMR0_vidEnable(void);
void TMR0_vidDisable(void);

LBTY_tenuErrorStatus TMR0_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode);
LBTY_tenuErrorStatus TMR0_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode);

LBTY_tenuErrorStatus TMR0_u8SetOutputCompare(u8 u8Reload);
LBTY_tenuErrorStatus TMR0_u8SetCounter(u8 u8Reload);

#if PWM0
LBTY_tenuErrorStatus PWM_u8SetFreq_OC0(u16 u16Freq);
LBTY_tenuErrorStatus PWM_u8SetDuty_OC0(u8 u8Duty);

static inline void PWM_vidEnable_OC0(void) {TMR0_vidEnable(); }
static inline void PWM_vidDisable_OC0(void){TMR0_vidDisable();}
#endif

void TMR0_vidSetCallBack_CompareMatch(void (*pCallBack)(void));
void TMR0_vidSetCallBack_OverFlow(void (*pCallBack)(void));

/********************************************************************************************************************/

void TMR2_vidInit(void);

void TMR2_vidEnable(void);
void TMR2_vidDisable(void);

LBTY_tenuErrorStatus TMR2_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode);
LBTY_tenuErrorStatus TMR2_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode);

LBTY_tenuErrorStatus TMR2_u8SetOutputCompare(u8 u8Reload);
LBTY_tenuErrorStatus TMR2_u8SetCounter(u8 u8Reload);

#if PWM2
LBTY_tenuErrorStatus PWM_u8SetFreq_OC2(u16 u16Freq);
LBTY_tenuErrorStatus PWM_u8SetDuty_OC2(u8 u8Duty);

static inline void PWM_vidEnable_OC2(void) {TMR2_vidEnable(); }
static inline void PWM_vidDisable_OC2(void){TMR2_vidDisable();}
#endif

void TMR2_vidSetCallBack_CompareMatch(void (*pCallBack)(void));
void TMR2_vidSetCallBack_OverFlow(void (*pCallBack)(void));

/********************************************************************************************************************/

void TMR1_vidInit(void);

void TMR1_vidEnable(void);
void TMR1_vidDisable(void);

LBTY_tenuErrorStatus TMR1_u8SetMode(TMR1_tenuWaveGenerationMode u8Mode);
LBTY_tenuErrorStatus TMR1_u8SetOutputModeA(TMR1_tenuCompareOutputMode u8OutMode);
LBTY_tenuErrorStatus TMR1_u8SetOutputModeB(TMR1_tenuCompareOutputMode u8OutMode);

LBTY_tenuErrorStatus TMR1_u8SetInputCapture(u16 u16Reload);
LBTY_tenuErrorStatus TMR1_u8SetOutputCompare_A(u16 u16Reload);
LBTY_tenuErrorStatus TMR1_u8SetOutputCompare_B(u16 u16Reload);
LBTY_tenuErrorStatus TMR1_u8SetCounter(u16 u16Reload);

void TMR1_vidSetCallBack_CaptureEvent(void (*pCallBack)(void));
void TMR1_vidSetCallBack_CompareMatch_A(void (*pCallBack)(void));
void TMR1_vidSetCallBack_CompareMatch_B(void (*pCallBack)(void));
void TMR1_vidSetCallBack_OverFlow(void (*pCallBack)(void));

#endif /* TMR_INT_H_ */
/*************************** E N D (TMR_int.h) ******************************/
