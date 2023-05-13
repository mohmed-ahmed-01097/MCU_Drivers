/* ************************************************************************** */
/* ********************** FILE DEFINITION SECTION *************************** */
/* ************************************************************************** */
/* File Name   : TMR_int.h													  */
/* Author      : MAAM														  */
/* Version     : v01														  */
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

/********************************************************************************************************************/
#if defined(TMR0) || defined(PWM0)
typedef struct{
	u8 								m_TMR_Reload;
	u8 								m_TMR_Compare;
	TMRx_tenuClockSource 			m_TMR_Prescalar;
	TMRx_u8_tenuWaveGenerationMode	m_TMR_Mode;
	TMRx_u8_tenuCompareOutputMode	m_TMR_OutputMode;
	LBTY_tenuFlagStatus				m_TMR_FOC;
	LBTY_tenuFlagStatus				m_TMR_OVIE;
	LBTY_tenuFlagStatus				m_TMR_OCIE;
}TMR0_tstrConfig;
#endif
#if defined(TMR2) || defined(PWM2)
typedef struct{
	u8 								m_TMR_Reload;
	u8 								m_TMR_Compare;
	TMRx_tenuClockSource 			m_TMR_Prescalar;
	TMRx_u8_tenuWaveGenerationMode	m_TMR_Mode;
	TMRx_u8_tenuCompareOutputMode	m_TMR_OutputMode;
	LBTY_tenuFlagStatus				m_TMR_FOC;
	LBTY_tenuFlagStatus				m_TMR_OVIE;
	LBTY_tenuFlagStatus				m_TMR_OCIE;
	TMR2_tenuInputCaptureEdgeSelect m_TMR_AsyClock;
}TMR2_tstrConfig;
#endif
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

void TMR0_vidSetConfig(TMR0_tstrConfig const* const pstrConfig);
void TMR0_vidSRestConfig(TMR0_tstrConfig* const pstrConfig);

void TMR0_vidInit(void);

void TMR0_vidEnable(void);
void TMR0_vidDisable(void);

LBTY_tenuErrorStatus TMR0_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode);
LBTY_tenuErrorStatus TMR0_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode);

LBTY_tenuErrorStatus TMR0_u8SetOutputCompare(u8 u8Reload);
LBTY_tenuErrorStatus TMR0_u8SetCounter(u8 u8Reload);

LBTY_tenuErrorStatus TMR0_u8GetOutputCompare(u8* pu8Reload);
LBTY_tenuErrorStatus TMR0_u8GetCounter(u8* pu8Reload);

#if PWM0
LBTY_tenuErrorStatus PWM_u8SetFreq_OC0(u16 u16Freq);
LBTY_tenuErrorStatus PWM_u8SetDuty_OC0(u8 u8Duty);

static inline void PWM_vidEnable_OC0(void) {TMR0_vidEnable(); }
static inline void PWM_vidDisable_OC0(void){TMR0_vidDisable();}
#endif

void TMR0_vidSetOverflowNum(u8 u8Num);
void TMR0_vidGetOverflowNum(u8* pu8Num);
void TMR0_vidGetTicks(u32* pu32Tick);

void TMR0_vidCompareMatch_Enable(void);
void TMR0_vidCompareMatch_Disable(void);

void TMR0_vidSetCompareMatch_Flag(void);
void TMR0_vidClrCompareMatch_Flag(void);

void TMR0_vidOverFlow_Enable(void);
void TMR0_vidOverFlow_Disable(void);

void TMR0_vidSetOverFlow_Flag(void);
void TMR0_vidClrOverFlow_Flag(void);

void TMR0_vidSetCallBack_CompareMatch(void (*pCallBack)(void));
void TMR0_vidSetCallBack_OverFlow(void (*pCallBack)(void));

/********************************************************************************************************************/

void TMR2_vidSetConfig(TMR2_tstrConfig const* const pstrConfig);
void TMR2_vidSRestConfig(TMR2_tstrConfig* const pstrConfig);

void TMR2_vidInit(void);

void TMR2_vidEnable(void);
void TMR2_vidDisable(void);

LBTY_tenuErrorStatus TMR2_u8SetMode(TMRx_u8_tenuWaveGenerationMode u8Mode);
LBTY_tenuErrorStatus TMR2_u8SetOutputMode(TMRx_u8_tenuCompareOutputMode u8OutMode);

LBTY_tenuErrorStatus TMR2_u8SetOutputCompare(u8 u8Reload);
LBTY_tenuErrorStatus TMR2_u8SetCounter(u8 u8Reload);

LBTY_tenuErrorStatus TMR2_u8GetOutputCompare(u8* pu8Reload);
LBTY_tenuErrorStatus TMR2_u8GetCounter(u8* pu8Reload);

#if PWM2
LBTY_tenuErrorStatus PWM_u8SetFreq_OC2(u16 u16Freq);
LBTY_tenuErrorStatus PWM_u8SetDuty_OC2(u8 u8Duty);

static inline void PWM_vidEnable_OC2(void) {TMR2_vidEnable(); }
static inline void PWM_vidDisable_OC2(void){TMR2_vidDisable();}
#endif

void TMR2_vidSetOverflowNum(u8 u8Num);
void TMR2_vidGetOverflowNum(u8* pu8Num);
void TMR2_vidGetTicks(u32* pu32Tick);

void TMR2_vidCompareMatch_Enable(void);
void TMR2_vidCompareMatch_Disable(void);

void TMR2_vidSetCompareMatch_Flag(void);
void TMR2_vidClrCompareMatch_Flag(void);

void TMR2_vidOverFlow_Enable(void);
void TMR2_vidOverFlow_Disable(void);

void TMR2_vidSetOverFlow_Flag(void);
void TMR2_vidClrOverFlow_Flag(void);

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
